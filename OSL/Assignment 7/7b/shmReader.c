#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

int main()
{
    int i;
    void *shared_memory;

    key_t key = ftok("shmfile",65);

    int shmid = shmget(key,1024,0666 | IPC_CREAT);

    printf("Key of shared memory is %d\n", shmid);

    shared_memory = shmat(shmid, NULL,0);

    printf("Process attached at %p\n", shared_memory);
    printf("Data read from shared memory is : %s\n", (char *)shared_memory);



}