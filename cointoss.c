#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <stdbool.h>

#define TOSSES 99999
#define THREAD_COUNT 10

_Atomic int heads;
_Atomic int tails;
_Atomic int total;

void *coin_toss(void *);

int main() {
    total = 0;
    pthread_t t[THREAD_COUNT];
    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_create(&t[i], NULL, coin_toss, NULL);
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(t[i], NULL);
    }

    if (total != (TOSSES * THREAD_COUNT)) {
        printf("ERROR: Coins tossed and Threads mismatch\n");
        return 1;
    }
    
    bool outcome = heads > tails;
    printf("The coins say: %s\n", outcome ? "HEADS" : "TAILS");
    return 0;
}

void * coin_toss(void * n) {
    srand(time(NULL));
    int t;
    for (int i = 0; i < TOSSES; i++) {
        t = rand() % 2;
        if (t) {
            heads++;
        } else {
            tails++;
        }
        total++;
    }
    return NULL;
}

