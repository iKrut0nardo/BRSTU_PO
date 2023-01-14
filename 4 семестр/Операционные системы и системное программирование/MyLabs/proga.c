#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	//1 process
	pid_t pid;
	printf("Создание процесса 1: PID=%d, PPID=%d\n", getpid(),getppid());
	
	//2 process
	if((pid=fork())==-1){
		printf("Error!\n");
	}
	else if(pid==0){
		printf("Создание процессса 2: PID=%d, PPID=%d\n", getpid(), getppid());
		//3 process
		if((pid=fork())==-1){
                printf("Error!\n");}
		else if(pid==0){
                printf("Создание процессса 3: PID=%d, PPID=%d\n", getpid(), getppid());
			//5 process
			if((pid=fork())==-1){
                	printf("Error!\n");}
                	else if(pid==0){
                	printf("Создание процессса 5: PID=%d, PPID=%d\n", getpid(), getppid());
				//7 process
				if((pid=fork())==-1){
                        	printf("Error!\n");}
                        	else if(pid==0){
                        	printf("Создание процессса 7: PID=%d, PPID=%d\n", getpid(), getppid());
							printf("Завершение процесса 7: PID=%d, PPID=%d\n", getpid(), getppid());
							exit(0);
						}else sleep(1);
				printf("Завершение процесса 5: PID=%d, PPID=%d\n", getpid(), getppid());
				exit(0);
				}else sleep(2);
			printf("Завершение процесса 3: PID=%d, PPID=%d\n", getpid(), getppid());
			exit(0);
		}else sleep(1);
		sleep(3);
		if((pid=fork())==-1){
        printf("Error!\n");}
        else if(pid==0){
        printf("Создание процессса 4: PID=%d, PPID=%d\n", getpid(), getppid());
			//6 process
			if((pid=fork())==-1){
        	printf("Error!\n");}
        	else if(pid==0){
			printf("Создание процессса 6: PID=%d, PPID=%d\n", getpid(), getppid());

			printf("Завершение процесса 6: PID=%d, PPID=%d\n", getpid(), getppid());
			exit(0);
			}else sleep(1);
		printf("Завершение процесса 4: PID=%d, PPID=%d\n", getpid(), getppid());
		exit(0);
		}else sleep(2);

  printf("Завершение процесса 2: PID=%d, PPID=%d\n", getpid(), getppid());
        exit(0);
}else sleep(3);
sleep(4);
printf("Завершение процесса 1: PID=%d, PPID=%d\n", getpid(), getppid());
execl("/bin/pwd", "pwd", NULL);
exit(0);

return 1;
}
