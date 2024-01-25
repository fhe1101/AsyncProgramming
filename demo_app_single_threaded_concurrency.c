#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "event_loop.h"

event_loop_t el;
static int upload = 0;
static int download = 0;

// simulate context switch in a single thread. realize concurrency
// in a single threaded program
static void upload_fn(void *arg) {

    (void)arg;
    while(upload < 100) {
        upload += 2;
        printf ("upload percent-age = %d\n", upload);
        if (upload % 10 == 0 && upload != 100) {
            // terminate the current task and re-schedule the same task
            task_create_new_job(&el, upload_fn, NULL);
            return;
        }
    }
}

static void download_fn(void *arg) {

    (void)arg;
    while(download < 100) {
        download += 2;
        printf ("download percent-age = %d\n", download);
        if (download % 10 == 0 && download != 100) {
            task_create_new_job(&el, download_fn, NULL);
            return;
        }
    }
}


int main(int argc, char **argv) {

    (void)argc;
    (void)argv;
    event_loop_init(&el);
    event_loop_run(&el);
    sleep(1);

    task_create_new_job(&el, upload_fn, NULL);
    task_create_new_job(&el, download_fn, NULL);

    printf ("End of main\n");
    scanf("\n");
    return 0;
}
