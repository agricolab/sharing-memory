#include "patriconf.h"
#include <stdio.h>

#define MUTEXNAME "krabby"
extern conf register_conf()
{
    conf c;
    // get key
    key_t key = ftok("configuration", 65);
    // initialize shared lock

    c.lock = shared_mutex_init(MUTEXNAME);
    if (c.lock.created == 1)
    {
        printf("Created ");
    }
    else
    {
        printf("Opened ");
    }
    printf("mutex called %s\n", c.lock.name);

    // create memory
    c.address = shmget(key, sizeof(parms_t), 0666 | IPC_CREAT);
    // attach memory
    c.fluid = (parms_t *)shmat(c.address, (void *)0, 0);
    // copy fluid content to stable content
    c.stable = *(c.fluid);
    return c;
};

void unregister_conf(conf *c)
{
    struct shared_mutex_t mutex = shared_mutex_init(MUTEXNAME);
    shared_mutex_destroy(mutex);

    shmdt((void *)c->fluid);            // detach memory
    shmctl(c->address, IPC_RMID, NULL); // destroy memory
};

extern void set_fs(conf *c, int fs)
{
    pthread_mutex_lock((c->lock.ptr));
    printf("In lock");
    c->fluid->fs = fs;
    pthread_mutex_unlock((c->lock.ptr));
    printf("Out lock");
};

static void update_conf(conf *c)
{
    int ret = pthread_mutex_trylock((c->lock.ptr));
    if (ret != 0)
    {
        c->stable = *(c->fluid);
        pthread_mutex_unlock((c->lock.ptr));
    }
    else
    {
        printf("Stable: ");
    }
};

extern int get_fs(conf *c)
{
    update_conf(c);
    return c->stable.fs;
}