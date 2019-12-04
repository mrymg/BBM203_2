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

typedef struct node {
    char *name;
    class c;
    priority p;
    char *given;
    char *wanted;
    struct node* next;

} passenger;
passenger*  newNode(char* name, priority priority, class c , char* flight, FILE* out, int b, int e, int s ){
    passenger* temp = (passenger*)malloc(sizeof(passenger));
    temp->name = name;
    temp->c = c;
    temp->p = priority;
    temp->next =NULL;
    temp->wanted = flight;
    char* cl;
    int count = 0;
    if(c== business){cl = "business"; count = b;}
    else if(c==economy){cl = "economy"; count= e;}
    else { cl="standard"; count =s;}

    fprintf(out, "queue %s %s %s %d\n", flight,name, cl, count );
    return temp;
}
passenger*  newNodew(char* name, priority priority, class c , char* flight){
    passenger* temp = (passenger*)malloc(sizeof(passenger));
    temp->name = name;
    temp->c = c;
    temp->p = priority;
    temp->next =NULL;
    temp->wanted = flight;
    char* cl;

    if(c== business){cl = "business"; }
    else if(c==economy){cl = "economy"; }
    else { cl="standard"; }


    return temp;
}
void pushque(passenger** head, char* name, priority p, class c, char *f, FILE* out, int b, int e, int s )
{

    passenger* start = (*head);

    passenger* temp = newNode(name, p, c, f,out,b,e,s);

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
void pushquew(passenger** head, char* name, priority p, class c, char *f )
{

    passenger* start = (*head);

    passenger* temp = newNodew(name, p, c, f);

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

stack* createStack(int capacity ){


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
typedef struct {
    char *name;
    int closed;
    int standard;
    int business;
    int economy;
    stack *b;
    stack *e;
    stack *s;
    passenger* que;
    passenger* wque;
    passenger* *passengers;


} flight;


int findIndex(char *name, flight *fArr, int fSize){
    int i;
    int j=0;


    for (i = 0; i <fSize ; i++) {
        if(strcmp(fArr[i].name, name) == 0){
            j=i;
            break;

        }
        else{
            j = -76;
            break;
        }
    }

    return j;
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








/*
 *
 *
 * FUNCTIONS DONE
 * MAIN FUNCTION START
 *
 *
 * */
void sell(char* name, flight *farr, int fSize, FILE* out  ){
    int i = findIndex(name, farr, fSize);
    passenger* pq = farr[i].que;
    stack* sb = farr[i].b;
    stack* se = farr[i].e;
    stack* ss = farr[i].s;
    passenger* wq= NULL;

    int cb = farr[i].business;
    int ce = farr[i].economy;
    int cs = farr[i].standard;
    int counter = 0;

    farr[i].passengers = (passenger**)malloc(sizeof(passenger*)*(cb+ce+cs));
    while(!isEmpty(farr[i].b) && !isEmptyque(&farr[i].que)){
        pop(farr[i].b);
        farr[i].que->given = "business";
        farr[i].passengers[counter] = farr[i].que;

        popque(&farr[i].que);
        cb--;
        counter++;
    }

        if(cb==0){
            while(farr[i].que->c == business){
                if(wq == NULL){
                    wq = newNodew(farr[i].que->name,farr[i].que->p,farr[i].que->c,name);
                }else {
                    pushquew(&wq, farr[i].que->name, farr[i].que->p, farr[i].que->c, name);
                }
                popque(&farr[i].que);
            }
        }else{
            while(!isEmpty(farr[i].b)){
                pop(farr[i].b);
                cb--;
                counter++;
            }
        }
        cb = counter;
    while(!isEmpty(farr[i].e) && !isEmptyque(&farr[i].que)){
        pop(farr[i].e);
        farr[i].que->given = "economy";
        farr[i].passengers[counter] = farr[i].que;
        popque(&farr[i].que);
        ce--;
        counter++;
    }
    if(ce==0){
        while(farr[i].que->c == economy){
            if(wq == NULL){
                wq = newNodew(farr[i].que->name,farr[i].que->p,farr[i].que->c,name);
            }else {

                pushquew(&wq, farr[i].que->name, farr[i].que->p, farr[i].que->c, name);
            }
            popque(&farr[i].que);
        }
    }else{
        while(!isEmpty(farr[i].e) && !isEmptyque(&wq)){
            pop(farr[i].e);
            wq->given = "economy";
            farr[i].passengers[counter] = wq;
            popque(&wq);
            ce--;
            counter++;
        }
    }
    ce = counter -cb;
    while(!isEmpty(farr[i].s) && !isEmptyque(&farr[i].que)){
        pop(farr[i].s);
        farr[i].que->given = "standard";
        farr[i].passengers[counter] = farr[i].que;
        popque(&farr[i].que);
        cs--;
        counter++;
    }
    if(cs==0){
        while(farr[i].que != NULL){
            if(wq == NULL){
                wq = newNodew(farr[i].que->name,farr[i].que->p,farr[i].que->c,name);
            }else {

                pushquew(&wq, farr[i].que->name, farr[i].que->p, farr[i].que->c, name);
            }
            popque(&farr[i].que);
        }
    }else{
        while(!isEmpty(farr[i].s) && !isEmptyque(&wq)){
            pop(farr[i].s);
            wq->given = "standard";
            farr[i].passengers[counter] = wq;
            popque(&wq);
            cs--;
            counter++;
        }
    }
    cs = counter-cb-ce;


    farr[i].wque = wq;
//    printf("%s ", farr[i].wque->name);
    free(wq);

    fprintf(out, "sold %s %d %d %d\n", name, cb,ce,cs);
    /* return eklenecek. */
}
void close(char*name, flight* farr, int fSize, FILE* out ){
    int i = findIndex(name, farr, fSize);
    farr[i].closed = 1;
    int total_ticket,waiting;
    int iter = 0;
    passenger* ps =farr[i].wque ;
    passenger* ps2 =farr[i].wque ;
    while(farr[i].passengers[iter] !=NULL){
        iter++;
    }
    total_ticket = iter;

    iter=0;
    while(ps !=NULL){
        popque(&ps);
        iter++;
    }
    waiting = iter;
    fprintf(out, "closed %s %d %d\n", name, total_ticket, waiting);
    while(ps2!=NULL){
        fprintf(out,"waiting %s\n", ps2->name);
        popque(&ps2);
    }
    free(ps2);
    free(ps);


}
void report(char*name, flight* farr, int fSize, FILE* out){
    int i = findIndex(name, farr,fSize);
    fprintf(out, "report %s\n", name);

    int total_ticket;
    int iter = 0;
    while(farr[i].passengers[iter] !=NULL){
        iter++;
    }
    total_ticket = iter;
    int b = 0;
    int e = 0;
    int s = 0;
    int j;
    for (j = 0; j < total_ticket ; j++) {
        if(strcmp(farr[i].passengers[j]->given , "business") == 0){
            b++;
        }
        else if(strcmp(farr[i].passengers[j]->given , "economy") == 0){
            e++;
        }else{
            s++;
        }
    }
    fprintf(out, "business %d\n", b);
    for ( j = 0; j < b; j++) {
        fprintf(out, "%s\n", farr[i].passengers[j]->name);
    }
    fprintf(out, "economy %d\n", e );
    for ( j = 0; j < e; j++) {
        fprintf(out,"%s\n", farr[i].passengers[j+b]->name);
    }
    fprintf(out, "standard %d\n", s );
    for ( j = 0; j <s; j++) {
        fprintf(out, "%s\n", farr[i].passengers[j+b+e]->name);
    }
    fprintf(out, "end of report %s\n", name);
}

void info(char *name, flight *farr, int fSize,FILE* out){

}

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
    flight *flightArray = (flight *) malloc(sizeof(flight) * flightCount);
    int k;

    int bstack_exist = 0;
    int estack_exist = 0;
    int sstack_exist = 0;
    int capacity = 0;
    stack* bStack =NULL;
    stack* eStack =NULL;
    stack* sStack =NULL;
    char *ch, *name, *class;
    int countB = 0;
    int countE = 0;
    int countS = 0;
    flight f;
    for ( k = 0; k <lineNum; k++) {

        ch = strtok(commandArray[k], " ");
        if(strcmp(ch, "addseat") == 0){

            name = strtok(NULL, " ");
            class = strtok(NULL, " ");
            int number = atoi( strtok(NULL, " "));
            capacity += number;
            int found = findIndex(name, flightArray, flightCount);

            if(found == -76){
                f = addseat(name, class, number, flightArray, index, flightCount);
            }else{
                f = addseat(name, class, number, flightArray, found, flightCount);
            }
            fprintf(out, "addseats %s %d %d %d\n", f.name, f.business, f.economy, f.standard);
            int t;
            int old_sizeb;
            int old_sizes;
            int old_sizee;
            int fi = findIndex(name, flightArray, flightCount);

            if(strcmp(class, "business") == 0){
                if(bstack_exist == 0){

                    flightArray[fi].b = createStack(f.business);
                    bstack_exist = 1;
                    for ( t = 0; t < f.business; t++) {
                        push(flightArray[fi].b,"business", f.business);
                    }

                    old_sizeb = f.business;


                }else{

                    for (t = old_sizeb; t < f.business ; t++) {
                        push(flightArray[fi].b,"business", f.business);
                    }
                }
            }
            else if(strcmp(class, "economy") == 0){
                if(estack_exist == 0){
                    flightArray[fi].e= createStack(f.economy);
                    estack_exist = 1;
                    for ( t = 0; t < f.economy; t++) {
                        push(flightArray[fi].e,"economy", f.economy);
                    }
                    old_sizee = f.economy;

                }else{

                    for ( t = old_sizee; t < f.economy ; t++) {
                        push(flightArray[fi].e,"economy", f.economy);
                    }
                }
            }
            else if(strcmp(class, "standard") == 0){
                if(sstack_exist == 0){

                    flightArray[fi].s = createStack(f.standard);
                    sstack_exist = 1;
                    old_sizes = f.standard;

                    for ( t = 0; t < f.standard; t++) {
                        push(flightArray[fi].s,"standard", f.standard);
                    }

                }else{
                    for ( t = old_sizes; t <f.standard ; t++) {
                        push(flightArray[fi].s,"standard", f.standard);
                    }
                }
            }

            index++;

        }
        if(strcmp(ch, "enqueue") == 0){
            passenger* pq =NULL;
            char* flight = strtok(NULL, " ");
            char* cl =  strtok(NULL, " ");
            int class;
            if(strcmp(cl, "business") == 0)
                class = business;
            if(strcmp(cl, "standard") == 0)
                class = standard;
            if(strcmp(cl, "economy")== 0)
                class = economy;
            int found = findIndex(flight, flightArray, flightCount);
            char* pName =  strtok(NULL, " ");
            char *prio = strtok(strtok(NULL, " "),"\r\n");
            int prior;
            if(prio==NULL){
                pName=strtok(pName,"\r\n");
                prior = nopri;
            }else{
                if(strcmp(prio,"veteran")==0)
                    prior = veteran;
                else if(strcmp(prio,"diplomat")==0)
                    prior = diplomat;
            }
            if(class == business)
                countB++;
            else if(class == economy)
                countE++;
            else if(class == standard)
                countS++;

            if(flightArray[found].que == NULL ){

                flightArray[found].que = newNode(pName, prior, class, flight, out,countB,countE,countS);
            }else{

                pushque(&flightArray[found].que, pName, prior, class, flight, out,countB,countE,countS);

            }

        }
        if(strcmp(ch, "sell") == 0){
            char* flight = strtok(strtok(NULL, " "), "\r\n");
            sell(flight, flightArray, flightCount, out);
        }
        if(strcmp(ch, "report") == 0){
            char* flight = strtok(strtok(NULL, " "), "\r\n");
            report(flight, flightArray, flightCount, out);
        }
        if(strcmp(ch, "close") == 0){
            char* flight = strtok(strtok(NULL, " "), "\r\n");
            close(flight, flightArray, flightCount, out);
        }
        if(strcmp(ch, "info") == 0){
            char* name = strtok(strtok(NULL, " "), "\r\n");
            info(name, flightArray, flightCount, out);
        }




    }






    return 0;
}
