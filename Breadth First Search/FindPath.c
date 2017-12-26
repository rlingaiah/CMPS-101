//Rhea Lingaiah
//rlingaia
//PA4
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
	while(fgetc(in)!=0){	//while the in file is not null and can get 
		fscanf(in,"%d", &x); //read in the vertex
		fscanf(in,"%d", &y);//read in the vertex
		if(x!=0&& y!=0){
			addEdge(G,x,y); //add the edge of the given verticies
		}
		else
			break;
	}
	printGraph(out,G); //print out the given list
	fprintf(out, "\n" ); //additional line
	int start=0; //start dest of the graph
	int end=0; //end dest of the graph
	//int a=0;
	List L=newList();

	while(fgetc(in)!=0){ //read the file until not null
		fscanf(in,"%d",&start); //read the start destination of the graph
		fscanf(in,"%d",&end);	//read in the end destination of the graph
		if(start!=0&&end!=0){ //check to make sure neither is 0
			BFS(G,start);		//do BFS starting at the start vertex
			getPath(L,G,end);	//getpath will make the path to the end passed vertex

				if(getDist(G,end)==INF){	//if the distance to end is infinity print:
					fprintf(out, "The distance from %d to %d is infinity\n",start, end);
					fprintf(out, "No %d-%d path exists\n\n",start,end);  //print what is on the pdf
				}
				else if(getDist(G,end)!=INF){ //if the distance to end is not infinity print:
					fprintf(out, "The distance from %d to %d is %d\n",start, end,length(L)-1); //additional arg because can't count 1 vertex in length
					fprintf(out, "A shortest %d-%d path is: ",start,end); //this is the shortest path
					printList(out,L); //printing out the list
					fprintf(out, "\n\n"); //so the output is the same with line spacing
				}
				clear(L); //clear the list 		
		}
		else{

			break;
		}
	}
	//------freeing-------	
	freeGraph(&G); //make sure the free the graphs
	freeList(&L); //free list
	fclose(in); //close the files
	fclose(out); //close the files
	return(0);
}