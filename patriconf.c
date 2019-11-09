#include "patriconf.h"
extern conf register_conf()
{
    conf c;
    key_t key = ftok("configuration", 65);                      // get key
    c.address = shmget(key, sizeof(parms_t), 0666 | IPC_CREAT); // create memory
    c.fluid = (parms_t *)shmat(c.address, (void *)0, 0);        // attach memory
    c.stable = *(c.fluid);
    return c;
};
void unregister_conf(conf *c)
{
    shmdt((void *)c->fluid);            // detach memory
    shmctl(c->address, IPC_RMID, NULL); // destroy memory
};

extern void set_fs(conf *c, int fs)
{
    pthread_mutex_lock(&(c->lock));
    c->fluid->fs = fs;
    pthread_mutex_unlock(&(c->lock));
};

static void update_conf(conf *c)
{
    int ret = pthread_mutex_trylock(&(c->lock));
    if (ret != 0)
    {

        c->stable = *(c->fluid);

        pthread_mutex_unlock(&(c->lock));
    }
};

extern int get_fs(conf *c)
{
    update_conf(c);
    return c->stable.fs;
}