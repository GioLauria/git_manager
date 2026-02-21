/*
 * Minimal C translation of git_manager.sh
 * Provides commit, optional tag-following and init flow.
 * Note: this program shells out to `git` for repository operations.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static char *run_command_capture(const char *cmd) {
    FILE *fp = popen(cmd, "r");
    if (!fp) return NULL;
    size_t cap = 4096; char *buf = malloc(cap); if (!buf) { pclose(fp); return NULL; }
    size_t len = 0;
    while (!feof(fp)) {
        if (len + 1024 > cap) { cap *= 2; buf = realloc(buf, cap); }
        len += fread(buf+len, 1, 1024, fp);
    }
    pclose(fp);
    if (len == 0) { free(buf); return NULL; }
    buf[len] = '\0';
    return buf;
}

static char *trim_trailing_newlines(char *s) {
    if (!s) return NULL;
    size_t i = strlen(s);
    while (i>0 && (s[i-1]=='\n' || s[i-1]=='\r')) s[--i] = '\0';
    return s;
}

static char *last_nonempty_line(const char *s) {
    if (!s) return NULL;
    const char *p = s + strlen(s)-1;
    while (p>=s && (*p=='\n' || *p=='\r')) p--;
    const char *end = p;
    while (p>=s && *p!='\n' && *p!='\r') p--;
    size_t len = end - p;
    char *res = malloc(len+1);
    memcpy(res, p+1, len);
    res[len] = '\0';
    return res;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s \"commit message\" [-t] [-M|-m|-p] | init\n", argv[0]);
        return 1;
    }
    char *detailed_changes = argv[1];
    char *sw = (argc>2)?argv[2]:"";
    char *release = (argc>3)?argv[3]:"";

    int follow_tags = 0;
    char new_tag_without_build[128] = {0};

    if (sw && strcmp(sw, "-t") == 0) {
        follow_tags = 1;
        char *tags_out = run_command_capture("git tag");
        char *last = last_nonempty_line(tags_out);
        free(tags_out);
        if (!last) { fprintf(stderr, "No tags found\n"); }
        int major=0, minor=0, patch=0;
        if (last) {
            if (last[0]=='v') last++;
            sscanf(last, "%d.%d.%d", &major, &minor, &patch);
        }
        if (strcmp(release, "-M")==0) { minor=0; major=major+1; patch=0; }
        else if (strcmp(release, "-m")==0) { minor=minor+1; patch=0; }
        else if (strcmp(release, "-p")==0) { patch=patch+1; }
        else if (strlen(release)>0) { fprintf(stderr, "Release switch %s not coded\n", release); return 1; }
        snprintf(new_tag_without_build, sizeof(new_tag_without_build), "v%d.%d.%d", major, minor, patch);
    }

    if (strcmp(detailed_changes, "init") == 0) {
        char github_user[128]={0}, project_name[128]={0}, user_name[128]={0}, email[128]={0};
        printf("Enter your gitHub User Name: "); fflush(stdout);
        if (!fgets(github_user, sizeof(github_user), stdin)) { fprintf(stderr, "Failed to read GitHub user\n"); return 1; }
        trim_trailing_newlines(github_user);
        printf("Enter your git repo name: "); fflush(stdout);
        if (!fgets(project_name, sizeof(project_name), stdin)) { fprintf(stderr, "Failed to read project name\n"); return 1; }
        trim_trailing_newlines(project_name);
        printf("Enter your git username for commits: "); fflush(stdout);
        if (!fgets(user_name, sizeof(user_name), stdin)) { fprintf(stderr, "Failed to read user name\n"); return 1; }
        trim_trailing_newlines(user_name);
        printf("Enter your git email for commits: "); fflush(stdout);
        if (!fgets(email, sizeof(email), stdin)) { fprintf(stderr, "Failed to read email\n"); return 1; }
        trim_trailing_newlines(email);
        char remote_project[512]; snprintf(remote_project, sizeof(remote_project), "https://github.com/%s/%s.git", github_user, project_name);
        int rc = system("rm -rf .git");
        if (rc != 0) fprintf(stderr, "Warning: rm -rf .git returned %d\n", rc);
        char cmd[1024];
        snprintf(cmd, sizeof(cmd), "git init && git config user.name \"%s\" && git config user.email %s && git remote add origin %s && git checkout -b main && git add * && git commit -m \"Initial commit\"",
             user_name, email, remote_project);
        rc = system(cmd);
        if (rc != 0) fprintf(stderr, "Warning: init sequence returned %d\n", rc);
        rc = system("_current_head=`git log --oneline | head -n1 | awk '{ print $1 }'`; git tag v0.0.1 $_current_head; git push -u origin main --force --follow-tagging");
        if (rc != 0) fprintf(stderr, "Warning: tagging/push returned %d\n", rc);
        return 0;
    }

    /* Normal commit flow */
    int rc = system("git add -A"); if (rc != 0) fprintf(stderr, "git add returned %d\n", rc);
    char commit_cmd[1024]; snprintf(commit_cmd, sizeof(commit_cmd), "git commit -m \"%s\"", detailed_changes);
    rc = system(commit_cmd); if (rc != 0) fprintf(stderr, "git commit returned %d\n", rc);

    char *old_head_out = run_command_capture("git rev-parse --short HEAD^1 2>/dev/null || echo \"");
    char *current_head = run_command_capture("git rev-parse --short HEAD");
    char *cur_branch = run_command_capture("git rev-parse --abbrev-ref HEAD");
    if (current_head) trim_trailing_newlines(current_head);
    if (cur_branch) trim_trailing_newlines(cur_branch);

    if (old_head_out && current_head && strcmp(trim_trailing_newlines(old_head_out), trim_trailing_newlines(current_head))!=0) {
        if (follow_tags) {
            char tagcmd[256]; snprintf(tagcmd, sizeof(tagcmd), "git tag %s %s", new_tag_without_build, current_head);
            rc = system(tagcmd); if (rc != 0) fprintf(stderr, "git tag returned %d\n", rc);
            rc = system("git tag CURRENT $(git rev-parse --short HEAD) -f"); if (rc != 0) fprintf(stderr, "git tag CURRENT returned %d\n", rc);
            rc = system("./clean_tags || sh clean_tags.sh"); if (rc != 0) fprintf(stderr, "clean_tags returned %d\n", rc);
            rc = system("./automatic_readme_generator || sh automatic_readme_generator.sh"); if (rc != 0) fprintf(stderr, "automatic_readme_generator returned %d\n", rc);
        }
        if (cur_branch && strcmp(cur_branch, "main")!=0) {
            char cmd2[256]; snprintf(cmd2, sizeof(cmd2), "git checkout main && git merge %s", cur_branch);
            rc = system(cmd2); if (rc != 0) fprintf(stderr, "merge returned %d\n", rc);
        }
        rc = system("git push origin --tags -f"); if (rc != 0) fprintf(stderr, "git push --tags returned %d\n", rc);
        rc = system("git push origin"); if (rc != 0) fprintf(stderr, "git push returned %d\n", rc);
    }

    free(old_head_out); free(current_head); free(cur_branch);
    return 0;
}
