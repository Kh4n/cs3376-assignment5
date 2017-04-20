#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/file.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define WRITE 1
#define READ 0

void  parse(char *line, char **argv) {
	while (*line != '\0') {
		while (*line == ' ') { 
			*line = '\0';
			line++;
		}
		*argv = line;
		argv++;
		while (!(*line == '\0' || *line == ' ')) {
			line++;
		}
	}
	*argv = '\0';         
}

void genArgs(char* args[5][9], int, char**);

int main(int argc, char** argv) {
	if (argc < 3 || argc > 6) {
		printf("Please enter between two and five arguments.\n");
		return(1);
	}
	int cmds[argc - 2][2];
	int pids[5];
	char *args[5][9];
	genArgs(args, argc, argv);
	argc = argc - 1;

	for (int i = 0; i < argc; i++) {	
		pipe(cmds[i]);
		if ((pids[i] = fork()) == 0) {
			if (i > 0 && i < argc - 1) {
				dup2(cmds[i - 1][READ], READ);
				dup2(cmds[i][WRITE], WRITE);
			}
			else if (i == argc - 1) {
				dup2(cmds[i - 1][READ], READ);
			}
			else {
				dup2(cmds[i][WRITE], WRITE);
			}
			for (int j = 0; j <= i; j++) {
				close(cmds[j][READ]);
				close(cmds[j][WRITE]);
			}
			execvp(*args[i], args[i]);
			return(1);
		}
		close(cmds[i][WRITE]);
	}
	for (int i = 0; i < argc; i++) {
		int status;
		waitpid(pids[i], &status, 0);
	}
	return(0);
}

void genArgs(char* args[5][9], int count, char** input) {
	for (int i = 1; i < count; i++) {
		parse(input[i], args[i - 1]);
	}	
}
