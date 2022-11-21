#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

int main()
{
    int i;
    void *shared_memory;
    char buffer[100];
    int shmid;
    // ftok to generate unique key
    key_t key = ftok("shmfile", 65);

    // create shared memory segment with key, having size 1024 bytes.
    //  IPC_CREAT is used to create the shared segment if it does not exist. 0666 are the permisions on the shared segment
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    printf("Key of shared memory is %d\n", shmid);
    shared_memory = shmat(shmid, NULL,0);
    printf("Process attached at %p\n",shared_memory);
    //get some input from user
    printf("Enter some data to write to shared memory\n");
    read(0,buff,100);
    //data written to shared memory
    strcpy(shared_memory,buff);
    printf("You wrote : %s\n", (char *)shared_memory);


}