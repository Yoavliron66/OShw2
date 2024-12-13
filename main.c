#include "hw2.h"
#include "jobs_fifo.c"

//MUTEXES
static int is_running = 1;
pthread_mutex_t fifo_mutex = PTHREAD_COND_INITIALIZER;
pthread_mutex_t counter_mutex[MAX_NUM_OF_COUNTERS];
pthread_mutex_t running_mutex = PTHREAD_MUTEX_INITIALIZER;
//COND VAR
pthread_cond_t wake_up = PTHREAD_COND_INITIALIZER;

int count_semicolon(char *command)
{
    int counter = 0;
    for (char *c = command; *c != '\0'; c++)
    {
        if (*c == ';') counter++;
    }
    return counter;
}

void parse_command(char* command, char* argv[]){
    int arg_count = counter_semicolon(command);
    char *token = strtok(command, ";");
    argv = (char**)malloc(sizeof(char*)*(arg_count));
    int i = 0;

     while (token != NULL)
    {
        argv[i] = (char*)malloc(strlen(token) + 1); 
        strcpy(argv[i], token);
        i++;
        token = strtok(NULL, ";");
    }
}

// Free the allocated memory for argv
void free_parsed_command(char **argv, int arg_count) {
    for (int i = 0; i < arg_count; i++) {
        free(argv[i]); // Free each string
    }
    free(argv); // Free the array of pointers
}

//Worker increment/decrement x which delta is for -1 or +1
void update_counter_file(char *filename, int delta)
{
    int fd;
    long long val = 0;
    char buffer[64];
    fd = open(filename, "W");
    if(fd == NULL)
    {
        perror("Failed to open counter file");
        return;
    }
    //read current value
    if (read(fd, buffer, sizeof(buffer)>0)) val = atoll(buffer);
    val += delta;
    //write updated value back to file
    lseek(fd,0,SEEK_SET);
    snprinf(buffer,sizeof(buffer),"%lld\n",val);
    write(fd, buffer, strlen(buffer));
    close(fd);
}

void worker_main(void *args)
{
    while (1)
    {
        pthread_mutex_lock(&running_mutex);
        if (!is_running)
        {
            pthread_mutex_unlock(&running_mutex);
            break;
        }
        pthread_mutex_unlock(&running_mutex);
        pthread_mutex_lock(&fifo_mutex);
        while (is_fifo_empty(&fifo_mutex))
        {
            pthread_cond_wait(&wake_up,&fifo_mutex);
        }
        char* command = fifo_pop(fifo);




        pthread_cond_signal(&wake_up);

        pthread_mutex_unlock(&fifo_mutex);
        free_parsed_command(argv); //fix me insert argv
    }

}




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
        pthread_mutex_init(&counter_mutex[i],NULL);
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