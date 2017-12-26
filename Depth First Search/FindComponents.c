//Rhea Lingaiah
//rlingaia
//PA5
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
#include "List.h"

#define Max_LEN 350

int main(int argc, char*argv[]){
	if(argc!=3){	//check if all the arguments have been passed
		printf("make sure to include infile and outfile");
		exit(1);
}
	FILE *in,*out; //get a file in and out

	in= fopen(argv[1],"r");
	out= fopen(argv[2],"w");
	int size=0; //size of the new graph
	if(in==NULL){ //check exception if the in file is null
		printf("can't open %s for reading\n", argv[1]);
		exit(1);
	}
	if(out==NULL){ //check exception if the 2nd arg out file is null
		printf("can't open %s for writing\n", argv[2]);
		exit(1);
	}
	
	fscanf(in,"%d",&size); //scan and point at the size
	Graph G= newGraph(size); //graph will have the size
	int x=0;
	int y=0;
	while(fscanf(in,"%d %d", &x,&y)==2){
		if(x!=0 &&y!=0){ //check each edge to see if the edges are not equal to 0
			addArc(G,x,y);	//if so add the arc
		}
		else
			break;
	}
	fprintf(out, "Adjacency list representation of G: \n"); //print
	printGraph(out,G);
	
	List list=newList();
	List strongList=newList();
	Graph trans=newGraph(size);
	int counter=0;
	int i=0;

	for(i=1;i<=getOrder(G);i++){
		append(list,i);				//add all the values of the graph into the list
	}
	DFS(G,list);					//run DFS on the list and graph
	trans=transpose(G);				//transpose the graph
	DFS(trans,list);				//run DFS on the transposed list
	moveBack(list);					//move to the back of the list since trying to print topographically
	while(index(list)!=-1){
		if(getParent(trans,get(list))==NIL){		//if the parent is 0
			counter=counter+1;						//get the count
		}
		movePrev(list);								//go through the list
	}
	fprintf(out, "\nG contains %d strongly connected components:\n", counter); //print
	moveBack(list);								//move to the back of the list again
	int val=1;
	while(index(list)!=-1){					
		if(getParent(trans,get(list))!=NIL){	//if the parent is not 0
			prepend(strongList, get(list));		//topographically put the element from the original list into the new one	
		}
		else if(getParent(trans,get(list))==NIL){	//if the parent is 0
			fprintf(out, "Component %d: ", val);	
			val=val+1;								//increment the component value
			prepend(strongList,get(list));			//then prepend the next element
			printList(out,strongList);				//print out the new list
			fprintf(out, "\n");
			clear(strongList);						//clear the new list
		}
		if(index(list)!=-1){
			movePrev(list);							//go through the list till null
		}
	}
	fclose(in); //close in file
	fclose(out); //close out file
	//free Graphs and lists------------------------
	freeGraph(&trans);
	freeList(&list);
	freeGraph(&G);
	freeList(&strongList);
}





