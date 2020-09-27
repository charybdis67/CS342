#include <stdio.h> 
#include <stdlib.h> 
#include <sys/time.h>

struct Node { 
    int insertedData; 
    struct Node* nextData; 
}; 

int main() 
{ 
    struct timeval start_time;
    gettimeofday(&start_time, NULL);
    struct Node* head = (struct Node*)malloc(sizeof(struct Node)); 
    //does it constructed right?
    if(head == NULL)
    { 
        perror( "malloc for for node failed" );
        exit( EXIT_FAILURE );
    }
    //first head inserted
    head->nextData = NULL;
    head->insertedData = rand()%100;
    //copy the head to create others
    struct Node *root = head;

    for (int i=1; i<1000; i++)
    {
        root->nextData = malloc( sizeof( struct Node ) );
        if( !(root->nextData) )
        {
            perror( "malloc failed" );
            exit( EXIT_FAILURE );
        }

        root = root->nextData;
        root->insertedData = rand()%100;
    }
    struct timeval finish_time;
    gettimeofday(&finish_time, NULL);
    printf("it took %ld micro seconds.\n", finish_time.tv_usec-start_time.tv_usec);
    return 0; 
} 
