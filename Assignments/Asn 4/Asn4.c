/*
 
 Zaid Kaleem
 103619897
 
 60-256
 Assignment 4
 
 */


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int childFunction(char *string);

char input;
char *string = &input;
char str[100];
int status;
int pid;


int main (void)
{
    printf("This program makes simple arithmetics\n");
    
    while(1)    // Infinite loop
    {
        write(1,"Enter an arithmetic statement\n",31); //printf("Enter an arithmetic statement, e.g., 34 + 132\n");
        input = scanf ("%[^\n]%*c", str);   // Getting an input line from keyboard. I couldn't figure out how to use read() to get 1 input line from keyboard
        
        pid = fork();   // Creating a copy of the process
        
        if (pid == -1)   // Error creating child process
        {
            perror("Impossible to fork\n");
            exit(0);
        }
        
        else if (pid == 0)    // Child process
            childFunction(str);
        
        else
        {
            if (pid > 0)  // Parent process
            {
                write(1,"\nCreated a child to make your operation, waiting\n",49); //printf("Created a child to make your operation, waiting\n");
                wait(&status);  // Waiting for the status signal from child process
                
                if (WEXITSTATUS(status) == 50)  // If exit status from child is 50 then print...
                    printf("Wrong Statement\n\n");
                
                else if (WEXITSTATUS(status) == 100)    // If exit status from child is 100 then print...
                    printf("Division by zero\n\n");
                
                else
                    if (WEXITSTATUS(status) == 200) // If exit status from child is 200 then print...
                        printf("Wrong operator\n\n");
            }
        }
        
    }
    
    return (0);
}


// Function to check the formatting of the input string and perform calculations
int childFunction(char *string)
{
    int n1, n2;
    char op;
    float div = n1/n2;
    
    write(1,"I am a child working for my parent\n",36); //printf("I am a child working for my parent\n");
    sscanf(string, "%d %c %d", &n1, &op, &n2);  // Matching the input string to a specific format: num op num
    
    sleep(1);
    
    if ((sscanf(string,"%d %c %d", &n1, &op, &n2)) != 3)    // Checking if format of input is correct
        exit(50);
    
    if (op == '/' && n2 == 0)   // Checking for division by zero
        exit(100);
    
    switch (op) // Checking if the operator is valid
    {
        case '+':
            printf("%d %c %d = %d\n\n", n1, op, n2, n1+n2);break;
            
        case '-':
            printf("\n%d %c %d = %d\n\n", n1, op, n2, n1-n2);break;
            
        case '/':
            printf("\n%d %c %d = %f\n\n", n1, op, n2, div);break;
            
        case '*':
            printf("\n%d %c %d = %d\n\n", n1, op, n2, n1*n2);break;
            
        default:
            exit(200);break;
    }
    exit(0);
    
}