#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>

#define set_nice_inc 351
int parent;
int main(){
	int f = 0;
	int i = 0;
        printf("Parent process %d\n", getpid());
		parent = getpid();
	for(i = 0; i<2; i++)
		f = fork();
	if(f==0){
		id_t pid;
		id_t ppid;
		int nice;
		int pnice;
		int flag;
		int ret;
		pid = getpid();
		ppid = getppid();
		flag = PRIO_PROCESS;
		nice = getpriority(flag, pid);
		pnice = getpriority(flag, ppid);
		printf("First generation child %d parent %d\n", pid, ppid);
		printf("First generation: My nice value %d, parent's nice value %d\n", nice, pnice);
		ret = syscall(set_nice_inc, pid, 3);
		printf("nice_inc of %d changed to 3\n", pid);
		//for(i = 0; i<2; i++)
			f = fork();
		if(f==0){
			pid = getpid();
			ppid = getppid();
			flag = PRIO_PROCESS;
			nice = getpriority(flag, pid);
			pnice = getpriority(flag, ppid);
			printf("Second generation child %d parent %d\n", pid, ppid);
			printf("Second generation: My nice value %d, parent's nice value %d\n", nice, pnice);
			ret = syscall(set_nice_inc, pid, 3);
			printf("nice_inc of %d changed to 3\n", pid);
			//for(i = 0; i<2; i++)
				f = fork();
			if(f==0){
				pid = getpid();
				ppid = getppid();
				flag = PRIO_PROCESS;
				nice = getpriority(flag, pid);
				pnice = getpriority(flag, ppid);
				printf("Third generation child %d parent %d\n", pid, ppid);
				printf("Third generation: My nice value %d, parent's nice value %d\n", nice, pnice);
				ret = syscall(set_nice_inc, pid, 3);
				printf("nice_inc of %d changed to 3\n", pid);
			}
			else{
				while(3);
			}
		}else{
			
			while(getppid()==parent);
			printf("Reparenting!\n");
			printf("My id %d parent id %d\n", getpid(), getppid());
			printf("My nice value %d, parent's nice value %d\n", getpriority(PRIO_PROCESS, getpid()), getpriority(PRIO_PROCESS, getppid()));
			while(3);
		}
	}
	else{
		while(3);
	}
	return 0;
}
