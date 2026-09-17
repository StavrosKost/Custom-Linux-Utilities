# Custom-Linux-Utilities

In this project i will upload some/all the codes i develop when trying to complete the 6.1810 labs from MIT. The code i will upload is entirely developed by me.
This was created in order for me to understand in a deep level how do Operating Systems work and how to develop them in C.

## Find Command

So to understand how find works, when need to see what we want it to do.
We want it to find a particular file inside a directory and all directories inside that specified directory
Format: find {path} {filename}

I will also try to explain how the code works in the best of my ability:
- Initially we check the amount of arguments since we need at least 3, if less is provided we fail the program
- The check about more that 3 arguments will be explain later
- Then we call the function find which has the main functionality, where we provide the first 2 arguments, argv[1] and argv[2] where they have the path and filename accordingly
- Inside the function we open the path lets say for example "." which is the directory we are currently in. Then we use fstat to get the information of that directory
- If it is a file then we compare the name of the files inside the directory with the file name provided from argv[2], if they match we print it
- If it is a directory firstly we copy the path to the buf and then attaches "/" to the path,then with the read we will check every file/directory, check if that directory is empty if so skip it, compare if it is "." or ".." to prevent infinite loop, and then get the stats of that and if it a directory then we recursively call it to see if the file exists inside that directory or else compare the fila and the filename to see if they match
- Lastly i will explain the argc>3, this was to add a custom command specifically "-exec" which stands for execute, so it will execute a command right after that for example
```
find . hello -exec echo hi
```
Should do the search and also print hi

## Sandbox Command

So the second part is to make a sandbox that will execute based on the mask and if its SYS_open value is 1 it will and if it is 0 it will not execute, lets explai nthe code slowly

Initially we check if it has less than 3 arguments we fail, and we always want the second argument to be "-", we use atoi(Ascii to Integer) in order to convert the second argument into an integer, then we call interpose(will be explained shortly after), then we take the path which will be executed for example "cat" or "echo" and then we execute then using exec which is execv in linux. 

So what does interpose do?
Well it is a syscall that i had to customly make, it was this:
```
uint64 sys_interpose(void){
  int mask;
  argint(0, &mask);
  myproc()->mask = mask;
  return myproc()->mask;
}
```
From argint we take the first number as input and then put it inside a variable in the process, and then return the value

So inside the syscall we will use the value and use right shifting to check each time if it can be done and if it can't then we fail
```
struct proc *p = myproc();
  num = p->trapframe->a7;
  int fail = p->mask & ( 1 << num);

  //something

  if (!fail){
    do syscall
  }else{
    don't do
  }

```
This took a long while because i was stuck on how to get the integer from the interpose in main to the sys_interpose but it turned out simpler than expected

