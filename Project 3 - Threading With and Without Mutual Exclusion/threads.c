// This producer and consumer program is to show you how to create threads and use related system calls.
// Your homework will be a different program.

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define TIMES 10
#define CAPACITY 3
#define ITEMSIZE 20

struct Buffer
{
    int item[ITEMSIZE];
    int size;
};

void *aPrinter();
void *bPrinter();

pthread_mutex_t mutex;
pthread_cond_t full_cond;
pthread_cond_t empty_cond;
struct Buffer buffer;

int main()
{
    pthread_t threadA, threadB;
    pthread_create(&threadA, NULL, (void *(*)(void *))aPrinter, NULL);
    pthread_create(&threadB, NULL, (void *(*)(void *))bPrinter, NULL);
    sleep(50);
    pthread_exit(0);
}

void *aPrinter()
{
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 5; j++){
            printf("%d: AAAAAAAAAA\n", i + 1);
        }
        printf("\n");
        sleep(1);
    }
    return NULL;
}

void *bPrinter()
{
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 5; j++){
            printf("%d. BBBBBBBBBB\n", i + 1);
        }
        printf("\n");
        sleep(1);
    }
    return NULL;
}
