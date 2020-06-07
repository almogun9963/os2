//
// Created by Ariel Yechezkel and Almog Amiga
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define max_number 5
int bool = 1;
int pipe_arr[2];

void sigusr1(int signal_number);
void stop(int sig_num);
void parent(pid_t child_pid);
void child();

void sigusr1(int signal_number) {
    signal(SIGUSR1, sigusr1);
}

void stop(int signal_number) {
    signal(SIGUSR2, stop);
    bool = 0;
}

void parent(pid_t child_pid) {
    signal(SIGUSR1, sigusr1);
    signal(SIGUSR2, stop);
    pause();
    while (bool){
        int data;
        read(pipe_arr[0], &data, sizeof(int));
        printf("%d\n",data);
        if (data >= max_number){
            sleep(1);
            kill(child_pid, SIGUSR2);
            return;
        }
        data++;
        write(pipe_arr[1], &data, sizeof(int));
        sleep(1);
        kill(child_pid, SIGUSR1);
        pause();
    }
}

void child() {
    signal(SIGUSR1, sigusr1);
    signal(SIGUSR2, stop);
    int data = 0;
    write(pipe_arr[1], &data, sizeof(int));
    pid_t ppid = getppid();
    kill(ppid, SIGUSR1);
    pause();
    while (bool){
        int data;
        read(pipe_arr[0], &data, sizeof(int));
        printf("%d\n",data);

        if (data >= max_number){
            sleep(1);
            kill(ppid, SIGUSR2);
            return;
        }
        data++;
        write(pipe_arr[1], &data, sizeof(int));
        sleep(1);
        kill(ppid, SIGUSR1);
        pause();
    }
}

int main() {
    signal(SIGUSR1, sigusr1);
    signal(SIGUSR2, stop);
    pipe(pipe_arr);
    pid_t pid = fork();
    if (pid < 0){
        printf("ERROR: pid < 0\n");
        return -1;
    }
    if (pid == 0){
        child();
    }
    else{
        parent(pid);
    }

    if(pid == 0){
        printf("Child is going to be terminated\n");

    }
    else{
        printf("Parent is going to be terminated\n");
    }

    close(pipe_arr[0]);
    close(pipe_arr[1]);

    return 0;
}
