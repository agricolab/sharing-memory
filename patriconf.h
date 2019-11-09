#include <sys/ipc.h>
#include <sys/shm.h>
#include <stddef.h>
#include <pthread.h>
typedef struct
{

    int fs;

} parms_t;

typedef struct
{
    int address;
    pthread_mutex_t lock;
    parms_t *fluid;
    parms_t stable;
} conf;

extern conf register_conf();
extern void unregister_conf(conf *c);
extern void set_fs(conf *c, int fs);
extern int get_fs(conf *c);
