
/* Driver Program
 */

#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(void) {
	time_t t;
	char s[256];
	int i, j;
	pid_t p,pp;

   	t = time(NULL);
	printf( "Driver Time: %s\n", ctime(&t));
	p = getpid();
	pp  = getppid();
	printf("Driver PID: %d   Driver PPID: %d \n", p, pp);
	p = fork();
	if (p == 0) {
		/* child */
		printf( "child");
		execv("./u", NULL); 
		pp = fork();
		if (pp == 0)
			execv("./u", NULL); }
	if (p == 0) {
		printf("Driver after fork, child: %d\n", p); 
 	} else {
		printf("Driver after fork, parent: %d\n", p);
	}	
	sleep(10);
      	t = time(NULL);
	printf( "Driver Time again: %s\n", ctime(&t));
	exit(0);
	}
	
