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
            if (fs > 1000)
            {
                fs = 0;
            }
            set_fs(&c, fs);
            fs = get_fs(&c);
            printf("%d \n", fs);
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
