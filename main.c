#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

#define BUF_LEN 80

int mastermind[4];

void generate_random_combination()
{
    int i;
    for(i = 0; i < 4; i++)
    {
        srand(time(NULL));
        int upper = 4;  
        int lower = 1;

        int random_number = (rand() % (upper - lower + 1)) + lower;
        
        mastermind[i] = random_number;

        printf("%d", mastermind[i]);
    }
    printf("\n");
}

int main()
{
    int file_desc;
    int ret_val;
    int simboli[4];

    generate_random_combination();

    /* Open gpio_driver file. */
    file_desc = open("/dev/gpio_driver", O_RDWR);

    if(file_desc < 0)
    {
        printf("Error, 'gpio_driver' not opened\n");
        printf("%d", file_desc);
        return -1;
    }

    ret_val = write(file_desc, mastermind, 4);
    if(ret_val < 4)
    {
        printf("Error writing to file.");
        return -1;
    }

    ret_val = read(file_desc, simboli, 4);


    for(int i = 0; i < 4; i++)
    {
        printf("%d", simboli[i]);
    }
    /* Close gpio_driver file. */
    close(file_desc);
    
    return 0;
}
