#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <asm/errno.h>

asmlinkage long sys_set_nice_inc(pid_t pid, int value){
	struct task_struct *my_process = find_task_by_vpid(pid);
        if(my_process != NULL){
		if( value>0 ){
                    my_process->nice_inc = value;
                    return 0;
		}
                return -EINVAL;
	}
        return -ESRCH;
}
