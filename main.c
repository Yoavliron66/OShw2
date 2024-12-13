#include "hw2.h"
#include "jobs_fifo.c"

//MUTEXES
pthread_mutex_t fifo_mutex = PTHREAD_COND_INITIALIZER;
pthread_mutex_t counter_mutex[MAX_NUM_OF_COUNTERS];

//COND VAR
pthread_cond_t wake_up = PTHREAD_COND_INITIALIZER;
//Dispatcher code

main(int argc, char* argv[])
{
    //Analyze the command line arguments
    assert((argc != NUM_OF_CMD_LINE_ARGS));

    int num_counters = (int) strtol(argv[3],'\0',10);
    int num_threads = (int) strtol(argv[2],'\0',10);
    FILE* cmd_file_fp = fopen(argv[1],"r");
    assert (cmd_file_fp);
    
    //Create counters - creates num_counts of counters as txt file, each initialized to 0
    char* counters_names [MAX_NUM_OF_COUNTERS];
    for (int i = 0; i < num_counters; i++)
    {
        sprintf(counters_names,"counter%2d.txt",i);
    }
    
    FILE* counters_fp [MAX_NUM_OF_COUNTERS];
    for (int i = 0; i < num_counters; i++)
    {
        counters_fp[i] = fopen(counters_names[i],"w");
        assert (counters_fp[i]);
        fprintf(counters_fp[i],"%lld",0); //FIXME - check it
        close(counters_fp[i]);
    }

    //Create threads
    pthread_t workers[MAX_NUM_OF_THREADS];

    for (int i = 0; i < num_threads; i++)
    {
        pthread_create(&workers[i], NULL, worker_function, (void *)); //FIXME - add an arguments
    }
    


    //Read the jobs from the cmdfile
    char job[MAX_LINE_WIDTH];

    while (fgets(job,MAX_LINE_WIDTH,cmd_file_fp)){
    //Parsing
    char* token = strtok(job," ");
    assert (token);

    if (strcmp(token,"dispatcher"))
    {
        
    }

    if (strcmp(token,"worker"))
    {
        /* worker code - wake up*/
    }

    }    

    //Dispatcher commands

    //Statistics

    //Exit Dispatcher:
    //close all files
    //wait for all threads - pthread_join(thread_id, NULL);
}