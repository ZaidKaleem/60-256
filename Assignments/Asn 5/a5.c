// Zaid Kaleem
// 103619897

// 60-256
// Assignment 5

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int readArgs(char *, char *[]);
int separate(char *, char *[]);
pid_t myFork();

// Function definition for main function
int main(int argc, char *argv[])
{
    pid_t pid;
    char line[255];
    char *commandList[10];
    int nbCommands;
    char *argList[20];
    int ampersand, status, i;
    
    printf("This program will execute commands/programs for you\n");
    
    for(i=0; i<10; i++)
        commandList[i] = (char *)malloc(100);
    
    while(1)
    {
        printf("To exit, enter CTR-C, or\n");
        printf("enter a command List separated by ;> ");
        fgets(line, 255, stdin);
        
        nbCommands = separate(line, commandList);
        
        for(i=0; i < nbCommands; i++)
        {
            strcpy(line, commandList[i]);
            printf("\n Executing %s\n", line);
            sleep(1);
            
            ampersand=readArgs(line, argList);
            
            if((pid = myFork()) == -1)
            {
                perror("impossible to fork");
                exit(1);
            }
            
            if(pid > 0)  // This is parent
                if(ampersand)
                    printf("Process [%d]\n", pid);
                else
                {
                    waitpid(pid, &status, 0);
                    printf("My child has terminated\n");
                }
                else                                // This is the child
                    if(execvp(argList[0], argList)==-1){
                        perror("child Process ");
                        exit(22);
                    }
        }
    }
    
    exit(0);
}


// Function definition for readArgs
int readArgs(char *line, char *argList[])
{
    static int yes=0;
    int i=0, offset=0;
    char name[50];
    int found=0;
    
    while(yes && argList[i] != NULL)
        free(argList[i++]);
    
    i=0;
    
    while(sscanf(line+offset, "%s", name)==1)
    {
        argList[i] = (char *) malloc(strlen(name)+1);
        strcpy(argList[i++], name);
        while(line[offset] == ' ')
            offset++;
        offset += strlen(name);
    }
    
    if(!strcmp(argList[i-1], "&"))
    {
        argList[i-1] = NULL;
        found = 1;
    }
    else
        {
        if(argList[i-1][strlen(argList[i-1])-1] == '&'){
            argList[i-1][strlen(argList[i-1])-1]='\0';
            found = 1;
        }
        argList[i] = NULL;
    }
    
    yes=1;
    return(found);
}


// Function definition for myFork function
pid_t myFork()
{
    static int count=0;
    
    count++;
    if(count <= 20)
        return(fork());
    else
        return(-1);
}


// Function definition for separate function
int separate(char *line, char *commandList[])
{
    int i=0, j=0, k=0;
    
    while(line[i] != '\n'){
        if(line[i] != ';'){
            commandList[j][k] = line[i];
            k++;
        }
        else
            {
                
            commandList[j][k] = '\n';
            commandList[j][k+1] = '\0';
            k=0;
            j++;
            i++;
                
            }
        
        i++;
    }
    
    commandList[j][k] = '\n';
    commandList[j][k+1] = '\0';
    
    return(j+1);
}