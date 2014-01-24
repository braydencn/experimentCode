#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void err_sys(char* msg)
{
	perror(msg);
	exit(-1);
}	

int
main()
{
	int fd[2]; //write by parent, read by child
	int fd1[2]; //write by child, read by parent 
	int pid;
	if(pipe(fd) < 0)
		err_sys("pipe error");
	if(pipe(fd1) < 0)
		err_sys("pipe1 error");
	if((pid = fork()) < 0)
		err_sys("fork error");
	else if(pid > 0){//parent
		close(fd[0]); //not read fd
		close(fd1[1]); //not write fd1
		if(write(fd[1], "2\n", 2) < 0)
			err_sys("write error");
		char tmp[255];
		int n;
		if((n = read(fd1[0], tmp, 255)) < 0)
			err_sys("read error");
		write(1, "parent:", 7);
		if(write(1, tmp, n) < 0)
			err_sys("write error");
	}else{ //child
//		close(0);
//		close(1);
		close(fd[1]); //not write fd
		close(fd1[0]); //not read fd1
		dup2(fd[0], STDIN_FILENO);//stdin closed first 
		dup2(fd1[1], STDOUT_FILENO);//stdout closed first
		close(fd[0]); 
		close(fd1[1]);
		if(execl("./child", NULL) < 0)
			err_sys("exec error");
	}
	if((waitpid(pid, NULL, 0) < 0))
		err_sys("wait_pid error");
	return 0;
}
