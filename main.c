#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{
    business,
    economy,
    standard
} class;
typedef enum{
    diplomat,
    veteran,
    nopri
} priority;
int lineCount(const char *filename)
{
    int ch = 0;
    int count = 1;
    FILE *fileHandle;

    if ((fileHandle = fopen(filename, "r")) == NULL) {
        return -1;
    }

    do {
        ch = fgetc(fileHandle);
        if ( ch == '\n')
            count++;
    } while (ch != EOF);

    fclose(fileHandle);

    return count;
}
typedef struct {
    char *name;
    int closed;
    int standard;
    int business;
    int economy;

} flight;
typedef struct node {
    char *name;
    class c;
    priority p;
    char *given;
    char *wanted;
    struct node* next;

} passenger;
passenger*  newNode(char* name, priority priority, class c , char* flight){
    passenger* temp = (passenger*)malloc(sizeof(passenger));
    temp->name = name;
    temp->c = c;
    temp->p = priority;
    temp->next =NULL;
    temp->wanted = flight;
    return temp;
}
void pushque(passenger** head, char* name, priority p, class c, char *f)
{

    passenger* start = (*head);

    passenger* temp = newNode(name, p, c, f);

    if(c == business){

        if (p == diplomat){
            if((*head)->p == diplomat){
                while(start->next->p==diplomat && start->next != NULL){
                    start=start->next;
                }
                temp->next = start->next;
                start->next = temp;

            }else{

                temp->next = *head;
                (*head) = temp;
            }
        }else{

            while(start->next !=NULL && start->next->c == business && start->next->p == nopri){
                start = start->next;
            }
            temp->next = start->next;
            start->next = temp;
        }
    }
    else if(c == economy){

        while(start->next != NULL && start->next->c == business ){
            start = start->next;
        }/* start burda business sonunu tutuyor*/

        if(p== veteran){

            if(start->next->p == veteran){
                while(start->next->next !=NULL && start->next->next->p==veteran){
                    start->next = start->next->next;
                }
                temp->next = start->next->next;
                start->next->next = temp;
            }else{
                temp->next = start->next;
                start->next = temp;
            }

        }else{

            while(start->next!=NULL && start->next->c == economy && start->next->p == nopri){
                start = start->next;
            }
            temp->next = start->next;
            start->next = temp;

        }
    }else{
        while(start->next!=NULL){
            start = start->next;
        }
        temp->next = start->next;
        start->next = temp;
    }


}
void popque(passenger** head)
{
    passenger* temp = *head;
    (*head) = (*head)->next;
    free(temp);
}
int isEmptyque(passenger** head)
{
    return (*head) == NULL;
}

/*
 *
 *
 *
 *
 *
 *
 * */




typedef struct  {
    int top;
    int capacity;
    char** array;
}stack;

stack* createStack(int capacity){


        stack* seats = (stack*)malloc(sizeof(stack));
        seats->capacity = capacity;
        seats->top = -1;
        seats->array = (char **) malloc(seats->capacity * sizeof(char));
        return seats;

}

int isFull(stack* stack){return stack->top == stack->capacity - 1;}
int isEmpty(stack* stack){return stack->top == -1;}

void push(stack* stack, char* item, unsigned capacity){
    if (isFull(stack)){
        stack->array = (char ** )realloc(stack->array, sizeof(char*)*capacity);
    }
//    if(capacity > stack->capacity){
//
//    }

    stack->array[++stack->top] = item;
//    printf("%s pushed to stack\n", item);
}
char* pop(stack* stack){
    if (isEmpty(stack))
        return NULL;
    return stack->array[stack->top--];
}

int findIndex(char *name, flight *fArr, int fSize){
    int i;
    for (i = 0; i <fSize ; i++) {
        if(strcmp(fArr[i].name, name)==0){
            return i;
        }
        else{
            return -76;
        }
    }

}
flight addseat(char *name, char *type, int count, flight *farr, int index, int fSize ){
    if(farr[index].closed != 1){
        int i;
        i = findIndex(name, farr, fSize);
        if(i == -76){
            farr[index].name = name;
            farr[index].business = 0;
            farr[index].economy = 0;
            farr[index].standard = 0;
        }
        if(strcmp(type, "business")==0)
            farr[index].business += count;
        else if(strcmp(type, "economy")==0)
            farr[index].economy += count;
        else if(strcmp(type, "standard")==0)
            farr[index].standard +=count;

    }

    return farr[index];
};


int enqueue(int);
int sell(int);
int close(int);
int report(int);
int info(int);


/*
 *
 *
 * FUNCTIONS DONE
 * MAIN FUNCTION START
 *
 *
 * */

int main(int argc, char *argv[]) {
    FILE *fp, *out;
    char *input, *output;
    input = argv[1];
    output = argv[2];
    fp = fopen(input, "r");
    out= fopen(output, "w");
    int lineNum = lineCount(input);


    char **commandArray=NULL;


    int i;
    commandArray =(char **)malloc(sizeof(char)*lineNum);
    for (i = 0; i< lineNum; i++) {
        commandArray[i] = (char *)malloc(50 * sizeof(char));
    }

    int j =0;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *command;
    int flightCount = 0;
    while ((read = getline(&line, &len, fp)) != -1) {

        commandArray[j++] = strdup(line);
        command = strtok(line," ");
        if(strcmp(command, "addseat") == 0){
            flightCount++;
        }
    }
    flightCount = flightCount/3;
    /*
     *
     *
     *
     *
     *
     * FONKSIYON DEFINITIONS
     *
     *
     *
     *
     *
     *
     *
     * */

    int index=0;
    flight *fligthArray = (flight *) malloc(sizeof(flight) * flightCount);
    int k;
    flight f;
    int bstack_exist = 0;
    int estack_exist = 0;
    int sstack_exist = 0;
    int capacity = 0;
    stack* bStack =NULL;
    stack* eStack =NULL;
    stack* sStack =NULL;
    char *ch, *name, *class;

    passenger* pq =NULL;
    for ( k = 0; k <lineNum; k++) {

        ch = strtok(commandArray[k], " ");
        if(strcmp(ch, "addseat") == 0){
            name = strtok(NULL, " ");
            class = strtok(NULL, " ");
            int number = atoi( strtok(NULL, " "));
            capacity += number;
            int found = findIndex(name, fligthArray, flightCount);
            if(found == -76){
                f = addseat(name, class, number, fligthArray, index, flightCount);
            }else{
                f = addseat(name, class, number, fligthArray, found, flightCount);
            }
            fprintf(out, "addseats %s %d %d %d\n", f.name, f.business, f.economy, f.standard);

            int t;
            int old_sizeb;
            int old_sizes;
            int old_sizee;
            if(strcmp(class, "business") == 0){
                if(bstack_exist == 0){
                    bStack = createStack(f.business);
                    bstack_exist = 1;
                    for ( t = 0; t < f.business; t++) {
                        push(bStack,"business", f.business);
                    }
                    old_sizeb = f.business;
                }else{
                    for (t = old_sizeb; t < f.business ; t++) {
                        push(bStack,"business", f.business);
                    }
                }
            }
            else if(strcmp(class, "economy") == 0){
                if(estack_exist == 0){
                    eStack = createStack(f.economy);
                    estack_exist = 1;
                    for ( t = 0; t < f.economy; t++) {
                        push(eStack,"economy", f.economy);
                    }
                    old_sizee = f.economy;
                }else{
                    for ( t = old_sizee; t < f.economy ; t++) {
                        push(eStack,"economy", f.economy);
                    }
                }
            }
            else if(strcmp(class, "standard") == 0){
                if(sstack_exist == 0){
                    sStack = createStack(f.standard);
                    sstack_exist = 1;
                    old_sizes = f.standard;
                    for ( t = 0; t < f.standard; t++) {
                        push(sStack,"standard", f.standard);
                    }

                }else{
/////burda kaldık
                    for ( t = old_sizes; t <f.standard ; t++) {
                        push(sStack,"standard", f.standard);
                    }
                }
            }

            index++;

        }
        if(strcmp(ch, "enqueue") == 0){

            char* flight = strtok(NULL, " ");
            char* cl =  strtok(NULL, " ");
            int class;
            if(strcmp(cl, "business") == 0)
                class = business;
            if(strcmp(cl, "standard") == 0)
                class = standard;
            if(strcmp(cl, "economy")== 0)
                class = economy;

            char* pName =  strtok(NULL, " ");
            char *prio = strtok(strtok(NULL, " "),"\n");
            int prior;
            if(prio==NULL){
                pName=strtok(pName,"\n");
                prior = nopri;
            }else{
                if(strcmp(prio,"veteran")==0)
                    prior = veteran;
                else if(strcmp(prio,"diplomat")==0)
                    prior = diplomat;
            }
            if(pq == NULL ){

                pq= newNode(pName, prior, class, flight);
            }else{

                pushque(&pq, pName, prior, class, flight);

            }




        }




    }
    while(!isEmptyque(&pq)){
        printf("%s\n", pq->name);
        popque(&pq);
    }






    return 0;
}
