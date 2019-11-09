#include "patriconf.h"
static void bind_conf(conf *c);

extern conf register_conf()
{
    conf c;
    bind_conf(&c);
    return c;
};
void unregister_conf(conf *c)
{
    shmdt((void *)c->params);           // detach memory
    shmctl(c->address, IPC_RMID, NULL); // destroy memory
};

static void bind_conf(conf *c)
{
    key_t key = ftok("configuration", 65);                    // get key
    c->address = shmget(key, sizeof(conf), 0666 | IPC_CREAT); // create memory
    c->params = (parms_t *)shmat(c->address, (void *)0, 0);   // attach memory
};

extern void set_fs(conf *c, int fs)
{
    c->params->fs = fs;
};

extern void set_frequency(conf *c, float freq)
{
    c->params->freq = freq;
};
extern void set_phase(conf *c, float phase)
{
    c->params->phase = phase;
};
extern int get_fs(conf *c)
{
    return c->params->fs;
};
extern float get_frequency(conf *c)
{
    return c->params->fs;
};
extern float get_phase(conf *c)
{
    return c->params->phase;
};
