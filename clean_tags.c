/* clean_tags.c - remove non-current patch tags similarly to clean_tags.sh */
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

int main(void) {
    char *tags_out = run_command_capture("git tag");
    if (!tags_out) return 0;
    char *last_tag = last_nonempty_line(tags_out);
    int major=0, minor=0;
    if (last_tag) {
        if (last_tag[0]=='v') last_tag++;
        sscanf(last_tag, "%d.%d", &major, &minor);
    }
    char new_tag_without_patch[64]; snprintf(new_tag_without_patch, sizeof(new_tag_without_patch), "v%d.%d", major, minor);

    char *saveptr = NULL;
    char *line = strtok_r(tags_out, "\n", &saveptr);
    while (line) {
        if (strstr(line, ".0") != NULL || strcmp(line, "CURRENT")==0 || strcmp(line, new_tag_without_patch)==0) {
            /* skip */
        } else {
            char cmd[256]; snprintf(cmd, sizeof(cmd), "git tag -d %s", line);
            int rc = system(cmd); if (rc != 0) fprintf(stderr, "git tag -d %s returned %d\n", line, rc);
            char cmd2[256]; snprintf(cmd2, sizeof(cmd2), "git push --delete origin %s", line);
            rc = system(cmd2); if (rc != 0) fprintf(stderr, "git push --delete origin %s returned %d\n", line, rc);
        }
        line = strtok_r(NULL, "\n", &saveptr);
    }
    free(tags_out);
    return 0;
}
