#include <stdio.h>

typedef struct {
char *name;
int closed;
int standard;
int business;
int economy;
} flight;
typedef struct {
    char *name;
    char *type;
    char *wanted;
} passenger;


int findIndex(int);
int addseat(int);
int enqueue(int);
int sell(int);
int close(int);
int report(int);
int info(int);

int main(int argc, char *argv[]) {
    FILE *input, *output;
    input = fopen(argv[1], "r");


    output = fopen(argv[2], "r");

    printf("Hell, o, World!\n");
    return 0;
}