#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


//TODO: modify to take cmd parameters

void execute_pipe(char *commandOne[], char *commandTwo[])
{
    int pipefd[2];
    pid_t processOne, processTwo;
    int status;

    //error checking
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    //run pre fork
    processOne = fork();

    //error checking
    if (processOne < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    //Child Process (pre.c)
    if (processOne == 0) {

        close(pipefd[0]);

        //Send standard output of pre to end of pipe
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }

        close(pipefd[1]);

        //Running pre executable and error checking
        execvp(commandOne[0], commandOne);
        perror("execvp");
        exit(EXIT_FAILURE);
    }

    close(pipefd[1]);

    // Wait for the child(pre) to fully complete
    waitpid(processOne, &status, 0);

    //run sort fork
    processTwo = fork();

    //error checking
    if (processTwo < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    //Second child process(sort.c)
    if (processTwo == 0) {
        close(pipefd[1]);

        // Read end of pipe where output was sent to from pre
        if (dup2(pipefd[0], STDIN_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(pipefd[0]);

        //run sort.c and error checking
        execvp(commandTwo[0], commandTwo);
        perror("execvp");
        exit(EXIT_FAILURE);
    }

    close(pipefd[0]);

    // Wait for the second child (sort) to fully complete
    waitpid(processTwo, &status, 0);

    //sleep(15);
    //return 0;
}

//int main(int argc, char *argv[])
//{
//    if (argc < 3) {
//        fprintf(stderr, "Usage: %s command1 | command2\n", argv[0]);
//        exit(EXIT_FAILURE);
//    }
//    // Command 1 and its arguments
//    char *commandOne[] = { argv[1], NULL };
//
//    // Command 2 and its arguments
//    char *commandTwo[] = { argv[2], NULL };
//
//    execute_pipe(commandOne, commandTwo);
//    return 0;
//}

