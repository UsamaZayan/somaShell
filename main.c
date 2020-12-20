#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
// To install the readline library, open the terminal window and write
// sudo apt-get install libreadline-dev
// you must link with -lreadline
// To Compile file write gcc main.c -lreadline -o test
#include<readline/readline.h>
#include<readline/history.h>
#include <dirent.h>

#define MAX_COMMAND_LENGTH 1000 // max number of letters to be supported
#define MAX_COMMAND_LIST 100 // max number of commands to be supported
#define NORMAL_COLOR  "\x1B[0m"
#define GREEN  "\x1B[32m"
#define BLUE  "\x1B[34m"

// Clearing the shell using escape sequences
#define clear() printf("\033[H\033[J")
// List all the environment strings
extern char **environ;

// Function where the system command is executed
// Forking and execute child process
void execArgs(char **parsed) {
    // Forking a child
    pid_t pid = fork();

    if (pid == -1) {
        printf("\nFailed forking child..");
        return;
    } else if (pid == 0) {
        // execute child process
        if (execvp(parsed[0], parsed) < 0) {
            // failed execute child process
            printf("\nCould not execute command : %s\n", parsed[0]);
        }
        exit(0);
    } else {
        // waiting for child to terminate
        wait(NULL);
        return;
    }
}

// Function to execute piped system
void execArgsPiped(char **parsed, char **parsedPipe) {
    // 0 is read end, 1 is write end
    int pipe_fd[2];
    pid_t p1, p2;

    p1 = fork();
    if (p1 < 0) {
        printf("\nCould not create fork 1");
        return;
    }

    if (p1 == 0) {
        if (pipe(pipe_fd) < 0) {
            printf("\nPipe could not be initialized");
            return;
        }

        p2 = fork();
        if (p2 < 0) {
            printf("\nCould not create fork 2");
            return;
        }

        if (p2 != 0) {
            // Child 1 executing..
            // It only needs to write at the write end
            close(pipe_fd[0]);          // close unused end
            dup2(pipe_fd[1], 1);   // duplicate used end to standard out
            close(pipe_fd[1]);         // close unused end
            if (execlp(*parsed, *parsed, NULL) < 0) {
                printf("\nCould not execute command 1..");
                exit(0);
            }

        } else {
            // Child 2 executing..
            // It only needs to read at the read end
            close(pipe_fd[1]);                  // close unused end
            dup2(pipe_fd[0], 0);            // duplicate used end to standard input
            close(pipe_fd[0]);                  // close unused end
            if (execlp(*parsedPipe, *parsedPipe, NULL) < 0) {
                printf("\nCould not execute command 2..");
                exit(0);
            }
        }
        // wait Child 2
        wait(NULL);
    } else {
        // wait Child 1
        wait(NULL);
    }
}

// Help command builtin
void openHelp() {
    puts("\n***WELCOME TO MY SHELL HELP***"
         "\nCopyright @ Usama Zayan"
         "\n-Use the shell at your own risk..."
         "\nList of Commands supported:"
         "\n>cd"
         "\n>ls"
         "\n>exit"
         "\n>all other general commands available in UNIX shell"
         "\n>pipe handling"
         "\n>improper space handling");
}

// Function to read input and save previous input in the buffer
int readInput(char *inputString) {
    char *buffer;

    buffer = readline(" ");
    if (strlen(buffer) != 0) {
        add_history(buffer);
        strcpy(inputString, buffer);
        return 0;
    } else {
        return 1;
    }
}

void listOfDirectory(char *path) {
    DIR *d = opendir(path); // open the path
    if (d == NULL) return; // if was not able return
    struct dirent *dir; // for the directory entries
    // if we were able to read something from the directory
    while ((dir = readdir(d)) != NULL) {
        if (dir->d_type != DT_DIR) {
            // if the type is not directory just print it with blue
            printf("%s%s\n", BLUE, dir->d_name);
            printf("%s", NORMAL_COLOR);
        } else if (dir->d_type == DT_DIR && strcmp(dir->d_name, ".") != 0 &&
                 strcmp(dir->d_name, "..") != 0) { // if it is a directory
            printf("%s%s\n", GREEN, dir->d_name); // print its name in green
            printf("%s", NORMAL_COLOR);
        }
    }
    closedir(d); // finally close the directory
}

// Function to print list all the environment strings
void printListOfEnv(){
    for (char **env = environ; *env != 0; env++){
        char *thisEnv = *env;
        printf("%s\n", thisEnv);
    }
}

// Function to handler and execute builtin commands
int builtinCommandHandler(char **parsed) {
    int NoOfBuiltinCommands = 8, i, switchArg = 0;
    char *ListOfCommands[NoOfBuiltinCommands];

    // Define builtin commands
    ListOfCommands[0] = "quit";
    ListOfCommands[1] = "cd";
    ListOfCommands[2] = "help";
    ListOfCommands[3] = "clr";
    ListOfCommands[4] = "dir";
    ListOfCommands[5] = "environ";
    ListOfCommands[6] = "pause";


    // Determine builtin command required
    for (i = 0; i < NoOfBuiltinCommands; i++) {
        if (strcmp(parsed[0], ListOfCommands[i]) == 0) {
            switchArg = i + 1;
            break;
        }
    }

    // Execute builtin command required
    switch (switchArg) {
        case 1:
            printf("Thanks for using our Shell\n");
            exit(0);
        case 2:
            chdir(parsed[1]);
            return 1;
        case 3:
            openHelp();
            return 1;
        case 4:
            clear();
            return 1;
        case 5:
            listOfDirectory(parsed[1]);
            return 1;
        case 6:
            printListOfEnv();
            return 1;
        default:
            break;
    }
    // In the case no builtin command required
    return 0;
}

// function for parsing command words
void parseSpace(char *string, char **parsed) {
    for (int i = 0; i < MAX_COMMAND_LIST; i++) {
        parsed[i] = strsep(&string, " ");

        if (parsed[i] == NULL) {
            // stop at end of command word
            break;
        }
        if (strlen(parsed[i]) == 0) {
            // ignore spaces
            i--;
        }
    }
}

// function for finding pipe
int parsePipe(char *inputString, char **stringPiped) {
    // parse pipe in inputString and store result in stringPiped
    for (int i = 0; i < 2; i++) {
        stringPiped[i] = strsep(&inputString, "|");
        if (stringPiped[i] == NULL)
            break;
    }

    // chick if pipe(|) used in command
    if (stringPiped[1] == NULL)
        return 0; // returns zero if no pipe is found.
    else {
        return 1;
    }
}

// process input string
int processString(char *inputString, char **parsed, char **parsedArgsPiped) {
    char *stringPiped[2];
    int piped;

    piped = parsePipe(inputString, stringPiped);

    if (piped) {
        parseSpace(stringPiped[0], parsed);
        parseSpace(stringPiped[1], parsedArgsPiped);

    } else {
        parseSpace(inputString, parsed);
    }

    if (builtinCommandHandler(parsed))
        // Successfully executed the builtin command
        return 0;
    else
        return 1 + piped;
}


int main(int argc, char **argv, char **envp) {
    environ = envp;
    char inputString[MAX_COMMAND_LENGTH], *parsedArgs[MAX_COMMAND_LIST];
    char *parsedArgsPiped[MAX_COMMAND_LIST];
    int executionFlag;
    // Clearing the shell
    clear();
    while (1) {
        // get Username.
        char *username = getenv("USER");

        // get Current Directory.
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));

        // print prompt line
        printf("%c[1m",ESC);  // turn on bold
        printf("%s%s:", GREEN, username);
        printf("%s~%s", BLUE , cwd);
        printf("%c[0m%s$", ESC, NORMAL_COLOR); // turn off bold and reset color

        // read the input
        if (readInput(inputString))
            // in the case not input entered continue
            continue;

        // process the input
        executionFlag = processString(inputString, parsedArgs, parsedArgsPiped);

        // executionFlag returns zero if there is no command
        // or it is a builtin command.

        // execute
        if (executionFlag == 1) {
            // command it is a simple
            execArgs(parsedArgs);
        }
        if (executionFlag == 2) {
            // command it is including a pipe.
            execArgsPiped(parsedArgs, parsedArgsPiped);
        }

    }
}

