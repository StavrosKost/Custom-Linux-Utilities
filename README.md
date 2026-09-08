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
