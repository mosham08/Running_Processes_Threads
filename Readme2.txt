
There are two different "driver" examples.
One does a traditional "fork()" then "exec()", the second does two fork() calls.

They are only example programs to show the use of the two system calls fork() and exec().
Note that there are many different versions of "exec()", including: execl, execle, execlp, 
execv, execve, execvp, and more, but they are really calling the same OS system call 
with different arrangements of arguments. 

Note that the "utility" example program is renamed to "u" in the call from the driver,
you can use any name you wish (you must either rename a.out to "u" or compile with 
cc -o <something> ) (see: https://gcc.gnu.org/onlinedocs/gcc/Option-Summary.html 
for more details)

By the way, this is what a "fork bomb" looks like:

#include <stdio.h> 
#include <sys/types.h> 
int main() { while(1) fork(); }