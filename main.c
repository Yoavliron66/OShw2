#include "hw2.h"

//MUTEXES

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
        fprintf(counters_fp[i],"%d",0); //FIXME - check it
    }

    //Create threads

    for (int i = 0; i < num_threads; i++)
    {
        //pthread_create(&thread_id, NULL, thread_function, (void *)arg);
    }
    


    //Read the jobs from the cmdfile


    //Dispatcher commands



    //FIFO



    //Threads


    //Exit Dispatcher:
    //close all files
    //wait for all threads - pthread_join(thread_id, NULL);
}