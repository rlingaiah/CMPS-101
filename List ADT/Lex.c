//Rhea Lingaiah
//rlingaia
//PA2
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"
#define MAX_LEN 160

int main(int argc, char* argv[]) {
    // Throws error if wrong number of args
    if(argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    int counter = 0;
    FILE *in, *out;
    char L[MAX_LEN];
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    //checks if null in/out file
    if(in == NULL) {
        fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if(out == NULL) {
        fprintf(stderr, "Unable to open file %s for writingn\n", argv[2]);
        exit(1);
    }

    while(fgets(L, MAX_LEN, in) != NULL) {
        counter++; //gets the count of the number of lines
    }
    rewind(in); //rewinds reader back to start of input file
    char lines[counter-1][MAX_LEN];
    int l = 0;

    while(fgets(L, MAX_LEN, in) != NULL) {
        strcpy(lines[l++], L);
    }

    // Sort---------------------------------------------------------------------
    List list;
    list= newList();
    int i;
    append(list, 0);
    for(int a = 1;a<counter;a++) {
        i = a-1;
        char *temp = lines[j];
        moveBack(list);
        while(i>= 0 && strcmp(temp,lines[get(list)]) <= 0) {
            movePrev(list);
            i--;
        }
        if(index(list)== -1) {
        prepend(list, a);
        }
        else if(index(list)!=-1){ 
        insertAfter(list, a);
        }
    }
    //--------------------------------------------------------------------------
    moveFront(list);
    while(index(list)!= -1) {
        fprintf(out, "%s",lines[get(list)]);
        moveNext(list);
    }
    freeList(&list);
    fclose(in); //close in file
    fclose(out); //close out file


}
