#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/file.h>
#include <unistd.h>

#define WRITE 1
#define READ 0


int main() {
	int cmd12[2];
	int cmd23[2];
	int pids1;
	int pids2;
	char *ls_args[] = {"ls", "-l -a", NULL};
 	char *grep_args[] = {"grep", "3376", NULL};
 	char *wc_args[] = {"wc", "-l", NULL};
	pipe(cmd12);

	if ((pids1 = fork()) == -1) {
		perror("Error creating pipe");
		return(255);
	}
	if (pids1 == 0) {
		dup2(cmd12[WRITE], WRITE);
		close(cmd12[READ]);
		close(cmd12[WRITE]);
		execvp(*ls_args, ls_args);
	}
	else {
		pipe(cmd23);
		if ((pids2 = fork()) == -1) {
			perror("Error makin pipe");
			return(255);
		}
		if (pids2 != 0) {
			dup2(cmd12[READ], READ);
			dup2(cmd23[WRITE], WRITE);
			close(cmd12[READ]);
			close(cmd12[WRITE]);
			close(cmd23[READ]);
			close(cmd23[WRITE]);
			execvp(*grep_args, grep_args);
		}
		else {
			dup2(cmd23[READ], READ);
			close(cmd12[READ]);
			close(cmd12[WRITE]);
			close(cmd23[READ]);
			close(cmd23[WRITE]);
			execvp(*wc_args, wc_args);
		}
	}
	return(0);
}
