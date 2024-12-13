#include "hw2.h"

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


