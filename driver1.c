
/* Driver Program
 */

#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define MAX_ARGS 4
int main(void) {
    time_t t;
    char s[256];
    int i, j;
    pid_t p, pp;
//
    char* argv[MAX_ARGS];
    argv[0] = "./all_month.csv";    // the file name
    argv[1] = "20000";                // size of data
    argv[2] = "Process #1 ";
    argv[3] = NULL;
//
    t = time(NULL);
    printf("Driver Time: %s\n", ctime(&t));
    p = getpid();
    pp = getppid();
    printf("Driver PID: %d   Driver PPID: %d \n", p, pp);

    p = fork();
    if (p == 0) {
        printf("Child is running, processing 1.\n");
        execv("./main", argv);
    }
    if (p == 0) {
        printf("Driver after fork, child: %d\n", p);
    } else {
        printf("Driver after fork, parent: %d\n", p);
    }



    p = fork();
    argv[2] = "Process #2 ";
    if (p == 0) {
        printf("Child is running, processing 2.\n");
        execv("./main", argv);
    }
    if (p == 0) {
        printf("Driver after fork, child 2: %d\n", p);
    } else {
        printf("Driver after fork, parent 2: %d\n", p);
    }


//    p = fork();
//    argv[2] = "Process #3 ";
//    if (p == 0) {
//        printf("Child is running, processing 3.\n");
//        execv("./main", argv);
//    }
//    if (p == 0) {
//        printf("Driver after fork, child 3: %d\n", p);
//    } else {
//        printf("Driver after fork, parent 3: %d\n", p);
//    }

    t = time(NULL);
    printf("Driver Time again: %s\n", ctime(&t));
    exit(0);
}