#include "patriconf.h"
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int fs = 0;

    if (argc == 1)
    {
        printf("No args");
        return 1;
    }
    printf("Register configuration\n");
    conf c = register_conf();
    while (1)
    {
        if (*argv[1] == 'w')
        {
            printf("Writing frequency: ");
            fs++;
            set_fs(&c, fs);
            if (fs > 1000)
            {
                fs = 0;
            }
            fs = get_fs(&c);
            printf("%d \n", fs);
        }
        else if (*argv[1] == 't')
        {
            printf("Access frequency: ");
            fs++;
            pthread_mutex_lock(&(c.lock));
            c.fluid->fs = fs;
            if (fs > 1000)
            {
                fs = 0;
            }
            printf("%d", fs);
            fflush(stdout);
            usleep(1 * 1000 * 1000);
            pthread_mutex_unlock(&(c.lock));
            printf(".\n");
        }
        else if (*argv[1] == 'r')
        {
            printf("Reading frequency: ");
            fs = get_fs(&c);
            usleep(.1 * 1000 * 1000);
            printf("%d\n", fs);
        }
    }
    return 0;
};
