//
// Created by Brick on 7/7/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    //error checking if cmd line arguments are inputted wrong
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [args...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    //fork child process
    pid_t process = fork();

    // error checking
    if (process == -1) {
        perror("forking error");
        exit(EXIT_FAILURE);
    }

    // Child process (second parameter)
    if (process == 0) {

        execvp(argv[1], &argv[1]); //execute command line argument

        // error checking
        perror("execvp");
        exit(EXIT_FAILURE);
    }

    // Parent process (first parameter)
    else
    {
        int status;
        // Wait for the first process to finish
        if (waitpid(process, &status, 0) == -1) {

            // error checking
            perror("waiting error");
            exit(EXIT_FAILURE);
        }

        // Checking to see how process ended
        if (WIFEXITED(status))
        {
            printf("Child process (PID: %d) finished with status %d\n", process, WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
        {
            printf("Child process (PID: %d) terminated by signal %d\n", process, WTERMSIG(status));
        }
        else
        {
            printf("Child process (PID: %d) terminated abnormally\n", process);
        }

        printf("Child process ID: %d\n", getpid());
    }

    return 0;
}