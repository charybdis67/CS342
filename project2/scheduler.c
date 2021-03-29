  #include<stdio.h>
  #include<string.h>
  #include<stdlib.h>
  #include <math.h>
  #include <unistd.h>
  #include <pthread.h>

  #ifdef PTHREAD_SYNC
  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_barrier_t barrier;
  #endif

  struct Node
  {
    int data;
    struct Node *next;
  };

  int scheduler(int N, int minB, int avgB, int minA, int avgA, char* ALG)
  {
    int burst_time = rand()/(avgB + 1.0);
    while(burst_time < minB)
    {
      burst_time = rand()/(avgB + 1.0);
    }

    int inter_arrival = rand()/(avgA + 1.0);
    while(inter_arrival < minA)
    {
      inter_arrival = rand()/(avgA + 1.0);
    }

    if(N > 10 || N < 1)
    {
      printf("N cannot be bigger than 10 and cannot be lower than 1\n");
    }
    else
    {
      //FCFS
      if(strcmp(ALG,"FCFS") == 0)
      {

      }
      //SJF
      else if(strcmp(ALG,"SJF") == 0)
      {

      }
      //PRIO
      else if(strcmp(ALG,"PRIO") == 0)
      {

      }
    }
    pthread_exit(NULL);
  }

  void* synchronization(int N, int minB, int avgB, int minA, int avgA, char* ALG)
  {
    int num, val = 0;
    int thread_num = (intptr_t)N + 1; /* Adding 1 to start thread count at 1 instead of 0. */

    for (num = 0; num < 20; num++) {
      if (random() > RAND_MAX/2) {
        usleep(10);
      }

      #ifdef PTHREAD_SYNC
      // Lock mutex
      pthread_mutex_lock(&mutex);
      #endif

      // Critical section
      scheduler(N, minB, avgB, minA, avgA, ALG);

      #ifdef PTHREAD_SYNC
      // Unlock mutex
      pthread_mutex_unlock(&mutex);
      #endif
    }

    #ifdef PTHREAD_SYNC
    // Allow all threads to wait for the last thread to exit the loop.
    pthread_barrier_wait(&barrier);
    #endif

  }

  int main(int argc, char **argv)
  {
    //parameters
    char* N, minB, avgB, minA, avgA, ALG, file_name;
    char file_input[100] = " ";
    FILE *file_command;
    char command[255];
    pthread_t tid;
    int thread_correct;

    if(argc != 7 || argc != 5)
    {
      printf("Not valid command line paramters\n" );
    }
    else
    {
      //from command line
      if(argc == 7)
      {
        //assigning parameters
        N = argv[1];
        minB = argv[2];
        avgB = argv[3];
        minA = argv[4];
        avgA = argv[5];
        ALG = *argv[6];

        int w_thread = atoi(N);
        synchronization(N,minB,avgB, minA, avgA,ALG);

        pthread_exit(NULL);
      }
      //from file
      else if(argc == 5)
      {
        //assigning parameters
        for (int i = 1; i < argc; ++i)
        {
          N = argv[1];

          strcat(file_input, "/");
          strcat(file_input, file_name);
          strcat(file_input, N);
          strcat(file_input, ".txt");

          file_command = fopen(file_input, "r");
          fscanf(file_command, "%s", command);
          fclose(file_command);

          int w_thread = atoi(N);
          //creating thread plus 1 for scheduler thread
          synchronization(N,minB,avgB, minA, avgA,ALG);
          pthread_exit(NULL);
        }
      }
    }

  }
