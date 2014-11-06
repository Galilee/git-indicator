#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "indicator.h"
#include "file.h"
#include "git.h"

void *listen_status(void *ptr);

typedef struct str_thdata
{
        struct git g;
} thdata;

int main (int argc, char **argv)
{
        pthread_t th_gitstatus;
        thdata data;
        int th_gitstatus_return;

        gtk_init (&argc, &argv);

        init_ui();

        th_gitstatus_return = pthread_create (&th_gitstatus, NULL,
                                              (void *) &listen_status,
                                              (void *) &data);
        if (th_gitstatus_return) {
                fprintf (stderr, "Thread failed: %d\n", th_gitstatus_return);
                exit (EXIT_FAILURE);
        }

        gtk_main ();

        return 0;
}

void* listen_status (void *ptr)
{
        thdata *data;
        data = (thdata *) ptr;
        int n, i;
        char **repopath = read_file (".conf", &n);

        for (i = 0; i < n; i++) {
                // Init {todo: make a function}
                data->g.repodir = (char*) malloc (REPO_NAME_LEN);
                strcpy ((char*) data->g.repodir, repopath[i]);
                data->g.revrange = "master..origin/master";
                // -
                
                git_threads_init();
                open_repository (&data->g);
                check_diff_revision (&data->g);
                close_repository (&data->g);

                git_threads_shutdown();
        }
}
