#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;

void* printA() {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);
        for (int j = 0; j < 5; j++) {
            printf("%d: AAAAAAAAA\n",i + 1);
        }
        printf("\n");
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}

void* printB() {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);
        for (int j = 0; j < 5; j++) {
            printf("%d: BBBBBBBBB\n",i + 1);
        }
        printf("\n");
        pthread_mutex_unlock(&mutex);
        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t threadA, threadB;
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&threadA, NULL, printA, NULL);
    pthread_create(&threadB, NULL, printB, NULL);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}
