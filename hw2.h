#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>



#define MAX_NUM_OF_THREADS 4096
#define MAX_NUM_OF_COUNTERS 100
#define NUM_OF_CMD_LINE_ARGS 4
#define MAX_LINE_WIDTH 1024
#define NUM_OF_OUTSTANDING 4096