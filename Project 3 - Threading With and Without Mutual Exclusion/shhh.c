#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

//Starter code given by Dr. Xiao Chen at Texas State University, July 10th 2024, "lab.c", (Version 1.0) [Source Code]
int main() {
    char *path, *argv[20], buf[80], n, *p;
    int m, status, inword, continu;

    while (1) {
        inword = 0;
        p = buf;
        m = 0;
        continu = 0;
        printf("\nshhh> ");

        while ((n = getchar()) != '\n' || continu) { // read input character by character until newline
            if (n == ' ') {
                if (inword) {
                    inword = 0;
                    *p++ = 0;
                }
            } else if (n == '\n') { // end of command
                continu = 0;
            } else if (n == '\\' && !inword) {
                continu = 1;
            } else { // add characters to word, if not in word start a new word
                if (!inword) {
                    inword = 1;
                    argv[m++] = p;
                    *p++ = n;
                } else {
                    *p++ = n;
                }
            }
        }
        *p++ = 0;
        argv[m] = 0;

        // No command entered
        if (m == 0) {
            continue;
        }

        // exit
        if (strcmp(argv[0], "exit") == 0) {
            exit(0);
        }


        int input_redirect = 0;
        int output_redirect = 0;
        int num_pipes = 0;
        char *inputFile = NULL;
        char *outputFile = NULL;
        char *commands[10][10]; //2D array to store command with arguments. Each row represent one command with up to 10 arguments
        int command_index = 0, arg_index = 0;

        // Split commands based on pipes, checking for pipes first to group commands better
        for (int i = 0; i < m; i++) {
            if (strcmp(argv[i], "|") == 0) {
                commands[command_index][arg_index] = NULL;
                command_index++;
                arg_index = 0;
            } else {
                commands[command_index][arg_index++] = argv[i];
            }
        }
        commands[command_index][arg_index] = NULL;
        num_pipes = command_index;

        // Checking for input and output redirection
        for (int i = 0; i <= command_index; i++) {
            for (int j = 0; commands[i][j] != NULL; j++) {
                if (strcmp(commands[i][j], "<") == 0) {
                    commands[i][j] = NULL;
                    inputFile = commands[i][j + 1];
                    input_redirect = 1;
                } else if (strcmp(commands[i][j], ">") == 0) {
                    commands[i][j] = NULL;
                    outputFile = commands[i][j + 1];
                    output_redirect = 1;
                }
            }
        }

        // No pipes
        if (num_pipes == 0) {
            if (fork() == 0) {
                if (input_redirect) {
                    int fd = open(inputFile, O_RDONLY);
                    if (fd < 0) {
                        perror("open");
                        exit(1);
                    }
                    dup2(fd, STDIN_FILENO);
                    close(fd);
                }

                if (output_redirect) {
                    int fd = open(outputFile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
                    if (fd < 0) {
                        perror("open");
                        exit(1);
                    }
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                }

                execvp(commands[0][0], commands[0]);
                perror("execvp");
                exit(1);
            }
            wait(&status);

        } else { // If there is a pipe
            int pipe_fds[2 * num_pipes];
            for (int i = 0; i < num_pipes; i++) {
                if (pipe(pipe_fds + i * 2) < 0) {
                    perror("pipe");
                    exit(1);
                }
            }

            //from provided sudo-code sketch.txt
            for (int i = 0; i <= num_pipes; i++) {
                if (fork() == 0) {
                    // Redirect input if not first command
                    if (i > 0) {
                        dup2(pipe_fds[(i - 1) * 2], STDIN_FILENO);
                    }

                    // Redirect output if not last command
                    if (i < num_pipes) {
                        dup2(pipe_fds[i * 2 + 1], STDOUT_FILENO);
                    }

                    // Close all pipes
                    for (int j = 0; j < 2 * num_pipes; j++) {
                        close(pipe_fds[j]);
                    }

                    if (i == 0 && input_redirect) {
                        int fd = open(inputFile, O_RDONLY);
                        if (fd < 0) {
                            perror("open");
                            exit(1);
                        }
                        dup2(fd, STDIN_FILENO);
                        close(fd);
                    }

                    if (i == num_pipes && output_redirect) {
                        int fd = open(outputFile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
                        if (fd < 0) {
                            perror("open");
                            exit(1);
                        }
                        dup2(fd, STDOUT_FILENO);
                        close(fd);
                    }

                    execvp(commands[i][0], commands[i]);
                    perror("execvp");
                    exit(1);
                }
            }

            // Close all parent pipes
            for (int i = 0; i < 2 * num_pipes; i++) {
                close(pipe_fds[i]);
            }

            // Wait for all children pipes to finish
            for (int i = 0; i <= num_pipes; i++) {
                wait(&status);
            }
        }
    }
}




