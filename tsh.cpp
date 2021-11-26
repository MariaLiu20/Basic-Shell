#include <tsh.h>
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

void simple_shell::parse_command(char* cmd, char** cmdTokens) {
// TODO: tokenize the command string into arguments
    cmd[strlen(cmd) - 1] = '\0';
    cmdTokens[0] = strtok(cmd, " ");
    int i = 0;
    while (cmdTokens[i] != NULL) {
        i++;
        cmdTokens[i] = strtok(NULL, " ");
    }
}

void simple_shell::exec_command(char** argv) {
    // TODO: fork a child process to execute the command.
    // parent process should wait for the child process to complete and reap it
    sleep(1);
    int pid = fork();
    if (pid < 0) { // usually an error
        cout << "Fork failed to execute\n";
        exit(1);
    }
    else if (pid == 0) { // new process, ‘child’
        if (isQuit(argv[0])) {
            exit(0);
        }
        execvp(argv[0], argv);
    }
    else { // original process, ‘parent’
        wait(NULL);
    }
}

bool simple_shell::isQuit(char* cmd) {
    // TODO: check for the command "quit" that terminates the shell
    if (strcmp(cmd, "quit") == 0) {
        return true;
    }   
    return false;
}