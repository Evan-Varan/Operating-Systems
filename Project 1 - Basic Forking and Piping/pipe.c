#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t pre, sort;
    int status;

    //error checking
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    //run pre fork
    pre = fork();

    //error checking
    if (pre < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    //Child Process (pre.c)
    if (pre == 0) {

        close(pipefd[0]);

        //Send standard output of pre to end of pipe
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }

        close(pipefd[1]);

        //Running pre executable and error checking
        execl("./pre", "pre", (char *)NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    }

    close(pipefd[1]);

    // Wait for the child(pre) to fully complete
    waitpid(pre, &status, 0);

    //run sort fork
    sort = fork();

    //error checking
    if (sort < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    //Second child process(sort.c)
    if (sort == 0) {
        close(pipefd[1]);

        // Read end of pipe where output was sent to from pre
        if (dup2(pipefd[0], STDIN_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(pipefd[0]);

        //run sort.c and error checking
        execl("./sort", "sort", (char *)NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    }

    close(pipefd[0]);

    // Wait for the second child (sort) to fully complete
    waitpid(sort, &status, 0);

sleep(15);
    return 0;
}
