// Zaid Kaleem
// 103-619-897
// 60-256
// Assignment 6

#include <stdio.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include <unistd.h>

void action(){};
void child(char *);
int input;

int main(int argc, char *argv[]){
    int i=6, s, pid;
    pid_t pid1, pid2, pid3;

    FILE *fp; 

    // Need to write each player's score in file and then read to check if equal to input

    void (*oldHandler1)(); // to save default handlers
    void (*oldHandler2)(); // for ctr-c and ctr-z
    oldHandler1=signal(SIGINT, SIG_IGN); // ignore ctr-c
    oldHandler2=signal(SIGTSTP, SIG_IGN); // ignore ctr-z

    printf("\nProgram running...CTR-C and CTR-Z disabled...\n");
    
    printf("\nHello this is a 3-players game with a referee\n");
    printf("Please enter the winning total score below: ");
    scanf("%d",&input);
    
    if((pid1=fork()) == 0)
        child("TOTO");
    
    if((pid2=fork()) == 0)
        child("TITI");

    if((pid3=fork()) == 0)
        child("TSTS");
    
    sleep(1);
    while(1){
        printf("\nReferee: TOTO plays\n\n");
        kill(pid1, 16);
        signal(16, action);
        pause();
        
        printf("\n\nReferee: TITI plays\n\n");
        kill(pid2, 16);
        signal(16, action);
        pause();
        
        printf("\n\nReferee: TSTS plays\n\n");
        kill(pid3, 16);
        signal(16, action);
        pause();
        
    }
}

void child(char *s){
    int points=0;
    int dice;
    long int ss=0;
    
    while(1){
        signal(16, action);
        pause();
        printf("%s: playing my dice\n", s);
        dice =(int) time(&ss)%10 + 1;
        printf("%s: got %d points\n", s, dice);
        points+=dice;
        printf("%s: Total so far %d\n\n", s, points);
        sleep(2);
        if(points >= input){
            printf("%s: game over I won\n", s);
            kill(0, SIGTERM);
        }
        kill(getppid(), 16);
    }
}