#ifndef git_h
#define git_h

#include <git2.h>
#include <stdio.h>
#include <string.h>

#define REPO_NAME_LEN 128

struct git
{
        git_repository *repo;
        const char *repodir;
        git_revwalk *walk;
        const char *revrange;
        git_status_list *status;
        git_status_options statusopt;
        int diffcommit;
};

void open_repository (struct git *g);
void fetch_repository (struct git *g);
void check_diff_revision (struct git *g);
void close_repository (struct git *g);
void get_status (struct git *g);

#endif
