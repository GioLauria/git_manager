/* automatic_readme_generator.c - generate README notes from tags and commits */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static char *trim(char *s) { if(!s) return s; while(*s && (*s=='\n' || *s=='\r')) s++; char *e = s + strlen(s)-1; while(e>=s && (*e=='\n' || *e=='\r')) *e--='\0'; return s; }

int main(void) {
    char *tags_out = run_command_capture("git tag");
    if (!tags_out) return 0;
    /* build list of tags excluding CURRENT */
    char **tags = NULL; size_t tcount = 0;
    char *saveptr = NULL;
    char *line = strtok_r(tags_out, "\n", &saveptr);
    while (line) {
        if (strcmp(line, "CURRENT")!=0 && strlen(line)>0) {
            tags = realloc(tags, sizeof(char*)*(tcount+1));
            tags[tcount++] = strdup(line);
        }
        line = strtok_r(NULL, "\n", &saveptr);
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

    /* Build notes string */
    size_t notes_cap = 8192; char *notes = malloc(notes_cap); notes[0]='\0';
    for (size_t i=0;i<tcount;i++) {
        if (i==0) {
            char buf[1024]; snprintf(buf, sizeof(buf), "<b><a href=\"%s/tree/%s\">%s</a></b><br>-----------------------------<br>", repo_url, tags[i], tags[i]);
            strncat(notes, buf, notes_cap-strlen(notes)-1);
            /* commits for first tag: show commit message with "Commit of" if present */
            if (first_commit) {
                char cmd[256]; snprintf(cmd, sizeof(cmd), "git log %s --oneline | grep \"Commit of\"", trim(first_commit));
                char *out = run_command_capture(cmd);
                if (out) { strncat(notes, out, notes_cap-strlen(notes)-1); free(out); }
            }
        } else {
            char buf[1024]; snprintf(buf, sizeof(buf), "<br>-----------------------------<br><b><a href=\"%s/tree/%s\">%s</a></b><br>-----------------------------<br>", repo_url, tags[i], tags[i]);
            strncat(notes, buf, notes_cap-strlen(notes)-1);
            char cmd[512]; snprintf(cmd, sizeof(cmd), "git log %s..%s --oneline | grep \"Commit of\"", tags[i-1], tags[i]);
            char *out = run_command_capture(cmd);
            if (out) {
                /* convert commit ids to links */
                char *s = strtok(out, "\n"); int first = 1;
                while (s) {
                    char id[64]; sscanf(s, "%63s", id);
                    char link[256]; if (first) snprintf(link, sizeof(link), "<a href=\"%s/commit/%s\">%s</a>", repo_url, id, id);
                    else snprintf(link, sizeof(link), "<br><a href=\"%s/commit/%s\">%s</a>", repo_url, id, id);
                    strncat(notes, link, notes_cap-strlen(notes)-1);
                    first = 0; s = strtok(NULL, "\n");
                }
                free(out);
            }
        }
    }

    /* Replace README.md content after marker 'rlsnts' */
    FILE *in = fopen("README.md","r");
    if (!in) { fprintf(stderr, "README.md not found\n"); return 0; }
    FILE *tmp = fopen("README.md.tmp","w");
    char bufline[4096]; int found = 0;
    while (fgets(bufline, sizeof(bufline), in)) {
        fputs(bufline, tmp);
        if (strstr(bufline, "rlsnts") && !found) { found = 1; break; }
    }
    if (found) {
        fputs(notes, tmp);
    }
    /* copy rest if needed (none) */
    fclose(in); fclose(tmp);
    remove("README.md"); rename("README.md.tmp","README.md");

    if (tags) { for (size_t i=0;i<tcount;i++) free(tags[i]); free(tags); }
    free(tags_out); if (first_commit) free(first_commit); if (remote_out) free(remote_out); free(notes);
    return 0;
}
