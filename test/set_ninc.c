#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#define set_nice_inc 351

int main(int argc, char *argv[]){
	int ret = -1;
	int pid = atoi(argv[1]);
	int value = atoi(argv[2]);
	ret = syscall(set_nice_inc, pid, value);
	if(ret==0)
		printf("nice_inc of process %d changed to %d\n", pid, value);
	return ret;
	
}
