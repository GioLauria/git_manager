/* automatic_readme_generator.c - generate README notes from tags and commits (C translation) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static char *run_command_capture(const char *cmd) {
    char fullcmd[1024];
    snprintf(fullcmd, sizeof(fullcmd), "%s 2>&1", cmd);
    FILE *fp = popen(fullcmd, "r");
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

    /* append command and its output to dump.txt */
    FILE *dump = fopen("dump.txt","a");
    if (dump) {
        fprintf(dump, "=== CMD: %s ===\n", cmd);
        fwrite(buf, 1, len, dump);
        fprintf(dump, "\n=== END CMD: %s ===\n\n", cmd);
        fclose(dump);
    }
    return buf;
}

static char *trim(char *s) {
    if(!s) return s;
    while(*s && (*s=='\n' || *s=='\r')) s++;
    char *e = s + strlen(s) - 1;
    while(e >= s && (*e=='\n' || *e=='\r')) *e-- = '\0';
    return s;
}

int main(void) {
    /* wipe dump file at start */
    FILE *dw = fopen("dump.txt","w"); if (dw) fclose(dw);
    /* get tags sorted by creation date (oldest first) */
    char *tags_out = run_command_capture("git for-each-ref --sort=creatordate --format=%(refname:short) refs/tags");
    if (!tags_out) {
        /* no tags: we'll still collect commits into an "Unreleased" section */
    }
    char **tags = NULL; size_t tcount = 0;
    if (tags_out) {
        char *saveptr = NULL;
        char *line = strtok_r(tags_out, "\n", &saveptr);
        while (line) {
            if (strcmp(line, "CURRENT")!=0 && strlen(line)>0) {
                tags = realloc(tags, sizeof(char*)*(tcount+1));
                tags[tcount++] = strdup(line);
            }
            line = strtok_r(NULL, "\n", &saveptr);
        }
    }

    char *first_commit = run_command_capture("git rev-list --max-parents=0 HEAD");
    char *remote_out = run_command_capture("git remote -v");
    char repo_url[512] = "";
    if (remote_out) {
        char *p = strstr(remote_out, "(push)");
        if (p) {
            /* find line start */
            char *ln = p;
            while (ln > remote_out && *ln != '\n') {
                ln--;
            }
            ln++; /* move to beginning of the line */
            char url[512] = {0}; sscanf(ln, "%*s %511s", url);
            snprintf(repo_url, sizeof(repo_url), "%s", url);
            size_t L = strlen(repo_url); if (L>4 && strcmp(repo_url+L-4, ".git")==0) repo_url[L-4]='\0';
        }
    }

    /* Build Markdown content */
    size_t notes_cap = 32768; char *notes = malloc(notes_cap); if (!notes) return 0; notes[0]='\0';

    /* Title and metadata */
    char repo_name[256] = "repository";
    if (repo_url[0]) {
        /* extract last path component */
        char *p = repo_url + strlen(repo_url) - 1;
        while (p > repo_url && *p == '/') *p-- = '\0';
        while (p > repo_url && *p != '/' && *p != ':') p--;
        if (*p == '/' || *p == ':') p++;
        snprintf(repo_name, sizeof(repo_name), "%s", p);
    }

    /* header */
    char header[1024];
    time_t now = time(NULL);
    struct tm tm;
#if defined(_WIN32) || defined(_WIN64)
    {
        struct tm *tmp = localtime(&now);
        if (tmp) tm = *tmp; else memset(&tm, 0, sizeof(tm));
    }
#else
    localtime_r(&now, &tm);
#endif
    char datestr[128]; strftime(datestr, sizeof(datestr), "%Y-%m-%d %H:%M:%S %z", &tm);
    if (repo_url[0]) snprintf(header, sizeof(header), "# %s\n\nRepository: %s\n\n_Generated: %s_\n\n## Release Notes\n\n", repo_name, repo_url, datestr);
    else snprintf(header, sizeof(header), "# %s\n\n_Generated: %s_\n\n## Release Notes\n\n", repo_name, datestr);
    strncat(notes, header, notes_cap - strlen(notes) - 1);

    /* Collect all commits (oldest first) */
    char *all_commits = run_command_capture("git log --pretty=oneline --reverse --no-decorate");
    size_t section_count = tcount + 1; /* extra section for Unreleased/untagged */
    char ***commit_lists = calloc(section_count, sizeof(char**));
    size_t *commit_counts = calloc(section_count, sizeof(size_t));

    if (all_commits && strlen(all_commits) > 0) {
        char *saveptr2 = NULL;
        char *cline = strtok_r(all_commits, "\n", &saveptr2);
        while (cline) {
            char id[128]; if (sscanf(cline, "%127s", id) < 1) { cline = strtok_r(NULL, "\n", &saveptr2); continue; }
            /* find tags that contain this commit */
            char cmd_cont[256]; snprintf(cmd_cont, sizeof(cmd_cont), "git tag --contains %s", id);
            char *contains = run_command_capture(cmd_cont);

            int assigned = (int)tcount; /* default: Unreleased (last index) */
            if (contains && tcount > 0) {
                /* parse contains into exact tag names */
                char *csave = NULL;
                char *ctok = strtok_r(contains, "\n", &csave);
                while (ctok) {
                    char *ct_trim = trim(ctok);
                    for (int ti = (int)tcount - 1; ti >= 0; ti--) {
                        if (strcmp(ct_trim, tags[ti]) == 0) { assigned = ti; break; }
                    }
                    if (assigned != (int)tcount) break;
                    ctok = strtok_r(NULL, "\n", &csave);
                }
            }

            /* append line to commit_lists[assigned] */
            commit_lists[assigned] = realloc(commit_lists[assigned], sizeof(char*) * (commit_counts[assigned] + 1));
            commit_lists[assigned][commit_counts[assigned]++] = strdup(cline);

            if (contains) free(contains);
            cline = strtok_r(NULL, "\n", &saveptr2);
        }
    }

    /* Print sections for each tag (and Unreleased last) */
    for (size_t i = 0; i < tcount; i++) {
        char section[1024]; snprintf(section, sizeof(section), "### %s\n\n", tags[i]);
        strncat(notes, section, notes_cap - strlen(notes) - 1);
        if (commit_counts[i] == 0) {
            strncat(notes, "- (no commits)\n\n", notes_cap - strlen(notes) - 1);
        } else {
            for (size_t j = 0; j < commit_counts[i]; j++) {
                char *s = commit_lists[i][j]; char cid[64]; if (sscanf(s, "%63s", cid) < 1) continue; char *rest = s + strlen(cid); while (*rest == ' ') rest++;
                char item[1024]; if (repo_url[0]) snprintf(item, sizeof(item), "- [%s](%s/commit/%s) - %s\n", cid, repo_url, cid, rest); else snprintf(item, sizeof(item), "- %s - %s\n", cid, rest);
                strncat(notes, item, notes_cap - strlen(notes) - 1);
            }
            strncat(notes, "\n", notes_cap - strlen(notes) - 1);
        }
    }

    /* Unreleased / commits not in any tag */
    char unreleased_header[128]; snprintf(unreleased_header, sizeof(unreleased_header), "### Unreleased\n\n");
    strncat(notes, unreleased_header, notes_cap - strlen(notes) - 1);
    if (commit_counts[tcount] == 0) {
        strncat(notes, "- (no commits)\n\n", notes_cap - strlen(notes) - 1);
    } else {
        for (size_t j = 0; j < commit_counts[tcount]; j++) {
            char *s = commit_lists[tcount][j]; char cid[64]; if (sscanf(s, "%63s", cid) < 1) continue; char *rest = s + strlen(cid); while (*rest == ' ') rest++;
            char item[1024]; if (repo_url[0]) snprintf(item, sizeof(item), "- [%s](%s/commit/%s) - %s\n", cid, repo_url, cid, rest); else snprintf(item, sizeof(item), "- %s - %s\n", cid, rest);
            strncat(notes, item, notes_cap - strlen(notes) - 1);
        }
        strncat(notes, "\n", notes_cap - strlen(notes) - 1);
    }

    /* free commit lists */
    for (size_t i = 0; i < section_count; i++) {
        if (commit_lists[i]) {
            for (size_t j = 0; j < commit_counts[i]; j++) free(commit_lists[i][j]);
            free(commit_lists[i]);
        }
    }
    free(commit_lists); free(commit_counts);
    if (all_commits) free(all_commits);

    /* Overwrite README.md with generated Markdown */
    FILE *outf = fopen("README.md.tmp","w");
    if (!outf) { fprintf(stderr, "failed to open README.md.tmp for write\n"); free(notes); return 0; }
    fputs(notes, outf);
    fclose(outf);
    remove("README.md"); rename("README.md.tmp","README.md");

    if (tags) { for (size_t i=0;i<tcount;i++) free(tags[i]); free(tags); }
    free(tags_out); if (first_commit) free(first_commit); if (remote_out) free(remote_out); free(notes);
    return 0;
}
