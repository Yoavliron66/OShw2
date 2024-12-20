#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>



#define MAX_NUM_OF_THREADS 4096
#define MAX_NUM_OF_COUNTERS 100
#define NUM_OF_CMD_LINE_ARGS 5
#define MAX_LINE_WIDTH 1024
#define NUM_OF_OUTSTANDING 4096


typedef struct JOBSFIFO
{
    int size;
    char* jobs[NUM_OF_OUTSTANDING];
    int wr_ptr;
    int rd_ptr;
} jobs_fifo;


struct worker_data
{
    FILE** counters_fpp;
    jobs_fifo* fifo;
}typedef worker_data;


