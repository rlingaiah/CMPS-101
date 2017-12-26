//Rhea Lingaiah
//rlingaia
//PA5

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

typedef struct NodeObj {
   int data;
   struct NodeObj* next;
   struct NodeObj* prev;
} NodeObj;

typedef NodeObj* Node;

typedef struct ListObj {
   Node front;
   Node back;
   Node cursor;
   int length;
   int index;
} ListObj;

// Creates a Node with int data, Node prev, and Node next.
Node newNode(int data, Node prev, Node next) {
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->prev = prev;
   N->next = next;
   return(N);
}
// Free memory for the Node.
void freeNode(Node* pN) {
   if(pN != NULL && *pN != NULL) {
      free(*pN);
      *pN = NULL;
   }
}

// Creates a new empty List.
List newList(void){
   List L= malloc(sizeof(ListObj));
   L->front = NULL;
   L->back = NULL;
   L->cursor=NULL;
   L->length = 0;
   L->index = -1;
   return(L);
}

void freeList(List* pL) {
   if (pL != NULL && *pL != NULL) {
      while( length(*pL) > 0 ) {
         deleteBack(*pL);   
      }
      free(*pL);
      *pL = NULL;
   }
}

int length(List L) {
   if(L == NULL) { //check exception
      printf("can't call length on NULL List");
      exit(1);
   }
   return L->length;
}


int index(List L) {
   if(L == NULL) { //check exception
      printf("can't call index on null list");
      exit(1);
   }
   return L->index;
}


int front(List L) {
   if(L == NULL) {//check exception
      printf("can't calling front on null list");
      exit(1);
   }
   else if(L->length < 1) {//check exception
      printf("can't call front on empty List ");
      exit(1);
   }
   return L->front->data;
}


int back(List L) {
   if(L == NULL) {//check exception
      printf("can't call back on NULL List ");
      exit(1);
   }
   else if(L->length < 1) {//check exception
      printf("can't call back on empty List r");
      exit(1);
   }
   return L->back->data;
}

//get data
int get(List L) {
   if(L == NULL) {//check exception
      printf("can't get on NULL List ");
      exit(1);
   }
   else if(L->index < 0||L->length < 1) {//check exception
      printf("can't call get with an undefined index or can't call get on empty List ");
      exit(1);
   }
   return L->cursor->data;
}

//checking if 2 lists are equal
int equals(List A, List B) {
	int flag = 1;
	if(A == NULL || B == NULL) { //check exception
		printf("can't call equals on NULL List");
	}
	Node N = A->front;
	Node M = B->front;
	if(A->length != B->length) {
		return 0;
	}
	while(flag && N != NULL) { //if the flag is true go into loop
		flag=(N->data == M->data); //check if the data is the same
		N=N->next; //move next in the list
		M=M->next;
	}
	return flag; //return the flag
}
//clear the entire list
void clear(List L) {
   if(L == NULL) {//check exception
      printf("can't call clear on NULL List");
      exit(1);
   }
   Node temp = L->front; 
   while(temp != NULL) {
      Node N = temp;
      temp = temp->next; //go through the temp and free each node
      free(N);
   }
   L->front =NULL;
   L->back = NULL;
   L->cursor =NULL;
   L->length =0; //set the length to null
   L->index=-1; //set the index to null
}

//move the cursor to the front of list
void moveFront(List L) {
   if(L == NULL) {//check exception
      printf("can't call moveFront on NULL List ");
      exit(1);
   }
   if(L->length > 0) {
      L->cursor = L->front; //move the cursor the front
      L->index=0;
   }
}
//move the cursor the back of list
void moveBack(List L) {
   if(L == NULL) {//check exception
      printf("can't call moveBack on NULL List");
      exit(1);
   }
   if(L->length > 0) {
      L->cursor = L->back; //move the cursor back
      L->index = L->length - 1;
   }
}
//move the cursor prev
void movePrev(List L) {
   if(L == NULL) { //check exception
      printf("can't call movePrev on null List");
      exit(1);
   }
   if(L->cursor != NULL && L->index != 0) {
      L->cursor = L->cursor->prev; //if the cursor isn't the front
      L->index--; //decrement the index
   }
   else if(L->cursor != NULL && L->index == 0) {
      L->cursor = NULL; //if the cursor is at the front
      L->index = -1; //index is null
   }
}
//move the cursor next
void moveNext(List L) {
   if(L == NULL) { //check exception
      printf("can't call moveNext on null List");
      exit(1);
   }
   if(L->cursor != NULL && L->index != L->length - 1) {
      L->cursor = L->cursor->next; //move the cursor to next
      ++L->index; //increase the index
   }
   else if(L->cursor != NULL && L->index == L->length - 1) {
      L->cursor = NULL;  //if at the back of the list
      L->index = -1; //index stays null
   }
}
//inserts the node before
void prepend(List L, int data) {
   if(L == NULL) { //list exception check
      printf("can't call prepend on null List");
      exit(1);
   }
   Node N = newNode(data, NULL, L->front);
   if(L->front == NULL)
      L->back = N;    //set the back
   else if(L->front!=NULL){
      L->front->prev = N;
   }
   L->front = N;
   L->index++;       //increase the index
   L->length++;      //increase the index
}
//inserts the node after
void append(List L, int data){
   if(L==NULL){
      printf("can't call append on null list");
      exit(1);
   }
	Node N = newNode(data,L->back, NULL);
	if(L->length == 0){ 
		L->front = L->back = N; //if the length is 0 then set the front and back to N
	}else{
		Node P;
		P = L->back;
		L->back->next= N; //set the back to next
		L->back=N;
		N->prev =P;
		P->next =N;
		}
	L->length++;     //increment the length
	}
//inserts before the cursor
void insertBefore(List L, int data) {
   if(L == NULL) { //exception check
      printf("can't call insertBefore on null List");
      exit(1);
   }
   else if(L->index < 0||L->length < 1) { //exception check
      printf("can't call insertBefore on null index or can't call insertBefore called on an empty List");
      exit(1);
   }
   Node N = newNode(data, L->cursor->prev, L->cursor);
   if(L->cursor->prev != NULL)
      L->cursor->prev->next = N;  //insert the node before
   else{
      L->front = N;
   }
   L->cursor->prev = N; //insert the node before
   L->length++;      //increment the length
   L->index++;       //increment the index
}
//inserts after the cursor
void insertAfter(List L, int data) {
   if(L==NULL) { //exception check
      printf("cant call insertafter on Null list");
      exit(1);
   }
   else if(L->length<1||L->index<0) { //exception check
      printf("can't call insertAfter when length is 0 or cant call insertafter on null index");
      exit(1);
   }
   Node N = newNode(data, L->cursor, L->cursor->next);
   if(L->cursor->next != NULL)   //check if the next is null
      L->cursor->next->prev=N;  
   else if(L->cursor->next == NULL){
      L->back=N;
   }
   L->cursor->next = N;
   L->length++; //increase the length
}
//deletes the front element
void deleteFront(List L){
	if(L->length < 1){//exception check
		printf( "cant call deleteFront when the length is less than 1");
		exit(1);
	}
	Node N=L->front;
	if(length(L)>1){	
		L->front=L->front->next;	
		L->front->prev=NULL; //set the front prev null
		L->index--;
	}else{
		L->front = NULL;
		L->back = NULL;
		L->index = -1;
		}
	L->length--; //decrement the length and index because deleted an element
	freeNode(&N);
	}
//deletes the back element
void deleteBack(List L){
   if(length(L)<1){ //exception to check deletes
   	printf("deleteBack can't be called if the length is less than 1");
   	exit(1);
   }
   Node N = L->back;
   if(length(L) == 1){
      L->front = L->back = NULL;
      L->index = -1;
   }
   else if( index(L)!=length(L)-1&&length(L)>1){ //if the cursor is in the back
      L->back=L->back->prev;
      L->back->next=NULL; //set to null
   }
   else if(length(L)>1 && index(L)==length(L)-1){
   	L->back = L->back->prev;
   	L->back->next = NULL; //move the next element to null
   	L->index = -1;
   }
   L->length--; //decrement the length
   freeNode(&N); //free
}

void delete(List L) {
	if(L == NULL) { //exception to check deletes
		printf("can't call delete on a null list");
		exit(1);
		}
	else if(index(L) == -1) { //exception to check deletes
		printf("delete on undefined list that is null");
		exit(1);
	} else if (length(L) == 0) {
		printf("delete on empty List");
		exit(1);
	}
	if (L->cursor == L->back) {
      deleteBack(L); //if the cursor is in the back delete the back
   } else if(L->cursor == L->front) {
	  deleteFront(L); //if the cursor is in the front delete the front
	}
   else{
   	Node left = L->cursor->prev;
   	Node right = L->cursor->next;
   	Node N = L->cursor;
   	left->next = right;
   	right->prev = left;
   	L->cursor = NULL; //set the cursor to null
   	L->index = -1; //set the index to null
   	L->length--; //dec the length since removing a node
   	freeNode(&N); //free
	}
}

//printing the list of nodes out
void printList(FILE* out, List L) {
    if(L == NULL) {
        printf("can't call printList on null List");
        exit(1);
    }
    Node N = L->front;
    int i = 0;
    while(N != NULL) {
      if(i != 0)
        	fprintf(out, " %d", N->data); //print the data of the node
      else 
        	fprintf(out, "%d", N->data); //print the data of the node
      N = N->next; //go onto the next node
      i++;
    }
}
//copy into the new list
List copyList(List L) {
   List A = newList();
   Node N = L->front;
   while(N != NULL) {
      append(A, N->data); //copy the values into the new list
      N = N->next;
   }
   return A;
}
