// gcc -O0 -g -no-pie heap5.c -o heap5
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>
#include <alloca.h>

void die(char *msg){
    puts(msg);
    exit(-1);
}

#define   MAX_PTRS 8

void *ptrs[MAX_PTRS];
int sizes[MAX_PTRS];



int get_int(){
    char buf[0x10] = {0};
    read(0, buf, 0x0f);
    return atoi(buf);
}

int menu(){
    puts("1. add");
    puts("2. rm");
    puts("3. show");
    puts("4. edit");
    puts("5. exit");
    printf("input your choice : ");
    return get_int();
}

unsigned int get_idx(){
    printf("input idx plz : ");
    unsigned int idx = get_int();
    if (MAX_PTRS <= idx ) die("wrong idx");
    return idx;
}

unsigned int get_size(){
    printf("input size plz : ");
    unsigned int size = get_int();
    if (size  <= 0x80) die("wrong size");
    return size;
}


int main(){
    setbuf(stdin, 0);
    setbuf(stdout, 0);
    setbuf(stderr, 0);
    // test_chunk();
    int choice;

    while ((choice = menu()) != 5) {
        if (choice == 1) {
            int idx     = get_idx();
            int size    = get_size();
            void *ptr   = malloc(size);
            if (ptr == NULL) die("malloc error");
            ptrs[idx]   = ptr;
            sizes[idx]  = size;
        } else if (choice == 2) {
            int idx     = get_idx();
            free(ptrs[idx]);
        } else if (choice == 3){
            int idx     = get_idx();
            if (0x10 <= idx ) die("wrong idx");
            puts(ptrs[idx]);
        } else if (choice == 4){
            int idx     = get_idx();
            printf("input content plz : ");
            if (read(0, ptrs[idx], sizes[idx]) < 0) die("read error");
        } else {
            puts("wrong choice");
        }
    }
    return 0;
}