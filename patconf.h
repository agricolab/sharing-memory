#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <stddef.h>

typedef struct
{
    int fs;
    float freq;
    float phase;
} parms_t;

typedef struct
{
    int address;
    parms_t *params;
} conf;

extern conf register_conf();
extern void unregister_conf(conf *c);
extern void set_fs(conf *c, int fs);
extern void set_frequency(conf *c, float freq);
extern void set_phase(conf *c, float phase);
extern int get_fs(conf *c);
extern float get_frequency(conf *c);
extern float get_phase(conf *c);