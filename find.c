#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"
#include "kernel/param.h"

char* find_files(char* path){
    static char buf[DIRSIZ+1];
    char *p;

    // Find first character after last slash.
    for(p=path+strlen(path); p >= path && *p != '/'; p--)
        ;
    p++;

    // Return blank-padded name.
    if(strlen(p) >= DIRSIZ)
        return p;
    memmove(buf, p, strlen(p));
    memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
    buf[sizeof(buf)-1] = '\0';
    return buf;
}

void find(char* path, char* filename){
    char buf[512];
    char* p;
    struct dirent de;
    struct stat st;
    int fd;
    fd = open(path, O_RDONLY);
    fstat(fd,&st);

    switch(st.type){
        case T_FILE:
            if (strcmp(find_files(path),filename)){
                printf("%s\n",path);
            }
            break;
        case T_DIR:   
            strcpy(buf,path);
            p = buf + strlen(buf);
            *p++ = '/'; 
            while(read(fd,&de, sizeof(de))==sizeof(de)){
                if (de.inum == 0){
                    continue;
                }
                if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0) {
                    continue;
                }
                memmove(p, de.name, DIRSIZ);
                p[DIRSIZ] = 0;
                if(stat(buf, &st) < 0){
                    printf("ls: cannot stat %s\n", buf);
                    continue;
                }
                if (st.type == T_DIR){
                    find(buf, filename);
                }else if(st.type == T_FILE && strcmp(de.name, filename) == 0) {
                    printf("%s\n", buf);
                }
            }
            break;
    }
    close(fd);
}

int main(int argc, char* argv[]){
    if (argc < 3){
        printf("Usage: find {directory} {filename}\n");
        exit(1);
    }

    if (argc > 3){
        char** arguments = argv + 4;
        int fd = fork();
        int status;
        if (fd == 0){
            if (!strcmp(argv[3],"-exec")){
                exec(argv[4],arguments);
            }
            exit(1);
        }else{
            wait(&status);
        }
    }
    find(argv[1], argv[2]);
    exit(0);
}
