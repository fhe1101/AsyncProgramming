/*
 * =====================================================================================
 *
 *       Filename:  event_loop.h
 *
 *    Description: This file declares the structures defining the event loop
 *
 *        Version:  1.0
 *        Created:  12/18/2021 03:37:42 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  ABHISHEK SAGAR (), sachinites@gmail.com
 *   Organization:  Cisco Systems
 *
 * =====================================================================================
 */

#ifndef __EV_LOOP__
#define __EV_LOOP__

#include <pthread.h>

// data type aliases
typedef struct task_ task_t;
typedef struct event_loop_ event_loop_t;

// function pointer for event callback
typedef void (*event_cbk)(void *);

// doubly linked-list
struct task_ {

    event_cbk cbk;
    void *arg;
    struct task_ *left, *right;
};

// states of an event loop
typedef enum {

    EV_LOOP_IDLE,
    EV_LOOP_BUSY
} EV_LOOP_STATE;

struct event_loop_ {

    /* head to the start of the task array */
    struct task_ *task_array_head;

    /* Mutex to enforce Mutual exclusion enqueue/Deque
     * Operation in task array. Also used to update event loop
     * attributes in mutual exclusive way
     */
    pthread_mutex_t ev_loop_mutex;

    /* State of event loop */
    EV_LOOP_STATE ev_loop_state;

    /* CondVar to suspend event loop thread */
    pthread_cond_t ev_loop_cv;

    /*  Event loop thread - an execution unit */
    pthread_t *thread;

    /* Current task which event loop thread is executing.
     * NULL if event loop is resting in peace*/
    struct task_ *current_task;
};

/* Initialize the member of event loop */
void event_loop_init(event_loop_t *el);

/* Run the event loop thread */
void event_loop_run(event_loop_t *el);

task_t *task_create_new_job(event_loop_t *el, event_cbk cbk, void *arg);

void task_cancel_job(event_loop_t *el, task_t *task);

#endif /* __EV_LOOP__ */
