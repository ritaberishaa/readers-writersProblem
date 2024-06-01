#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

sem_t x, y;
pthread_t writerthreads[100], readerthreads[100];
int readercount = 0;

void *reader(){
    sem_wait(&x);
    readercount++;
    if (readercount == 1)
        sem_wait(&y);
    sem_post(&x);
    printf("%d reader is inside\n", readercount); usleep(300000); 
    readercount--;
    if (readercount == 0)
    {
        sem_post(&y);
    }
    sem_post(&x);
    printf("%d reader is leaving\n", readercount + 1);
}


void *writer() {
    printf("Writer is trying to enter\n");
    sem_wait(&y);
    printf("Writer has entered\n");
    usleep(300000);
    sem_post(&y);
    printf("Writer is leaving\n");
}

int main()
{
   int n_readers, n_writers, i; 
   printf("Enter the number of readers: "); 
   scanf("%d", &n_readers);
   printf("Enter the number of writers: "); 
   scanf("%d", &n_writers);
   printf("\n");


    sem_init(&x, 0, 1); 
    sem_init(&y, 0, 1);

    for (i = 0; i < n_readers; i++)
    {
        pthread_create(&readerthreads[i], NULL, reader, NULL);
    }

    for (i = 0; i < n_writers; i++) 
    {
        pthread_create(&writerthreads[i], NULL, writer, NULL);
    }

    for (i = 0; i < n_readers; i++) 
    {
        pthread_join(readerthreads[i], NULL); 
    }

    for (i = 0; i < n_writers; i++) 
    {
        thread_join(writerthreads[i], NULL); 
    }

    sem_destroy(&x); 
    sem_destroy(&y);

    return 0; 

}