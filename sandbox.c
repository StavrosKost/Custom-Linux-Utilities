#include "kernel/types.h"
#include "user/user.h"
#include "kernel/syscall.h"

int main(int argc, char* argv[]){
    if (argc < 3){
        printf("Usage <mask> - <path>\n");
        exit(1);
    }

    if (strcmp(argv[2],"-")){
        printf("The third argument must always be -\n");
        exit(1);
    }
    int mask = atoi(argv[1]);
    interpose(mask, argv[2]);
    char* path = argv[3];
    printf("Mask is %d and path is %s\n", mask, path);
    exec(argv[3],argv + 3);

    exit(0);
}
