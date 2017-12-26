//Rhea Lingaiah
//rlingaia
//PA4
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"


//GRAPHOBJ
typedef struct GraphObj{
	int size;
	int order;
	int sourceVertex; //source vertex
	List *vertices; //neighbors array
	char *color; //character array 
	int *parent; //previous vertex array
	int *distance; //distance array
} GraphObj;

/***Constructors-Destructors ***/
Graph newGraph(int n){
	Graph G= malloc(sizeof(GraphObj));
	G->vertices= calloc(n+1,sizeof(List));
	G->color=calloc(n+1,sizeof(int));
	G->parent=calloc(n+1,sizeof(int));
	G->distance=calloc(n+1,sizeof(int));

	G->order=n;
	G->size=0;
	G->sourceVertex=NIL;
	for(int i=1; i<=n;i++){
		G->vertices[i]=newList();
		G->parent[i]=NIL;
		G->distance[i]=INF;
		G->color[i]='w'; //created an array of characters for color
	}
	return G;
}
//free all values (verticies,distance, parent, color) and set to null
void freeGraph(Graph* pG){
	if(*pG!=NULL&&pG!=NULL){
		for(int i=1;i<=getOrder(*pG);i++){
			freeList(&((*pG)->vertices[i]));
		}
		free((*pG)->vertices);
		free((*pG)->distance);
		free((*pG)->parent);
		free((*pG)->color);
		free(*pG);
		*pG=NULL;
	}
}
/*** Access functions ***/
//return the order of the graph
int getOrder(Graph G){
	if(G!=NULL){//check to make sure the graph is not NULL
		return (G->order);
	}
	else{
		printf("null amount of vertices");
		return(-1);
		//exit(1);
	}
}
//return the size of the graph
int getSize(Graph G){
	if(G!=NULL){//check to make sure the graph is not NULL
		return (G->size);
	}
	
	printf("null amount of edges");
	return(-1);
		//exit(1);
	
}
//return the source of the graph
int getSource(Graph G)
{
	if(G!=NULL){//check to make sure the graph is not NULL
		return (G->sourceVertex);
	}
	else{
		printf("no last accessed vertex"); //throws exception cuz no last vertex
		return(-1);
		//exit(1);
	}
}
//return the parent of the graph
int getParent(Graph G, int u)
{
	if(G!=NULL){ //check to make sure the graph is not NULL
		return (G->parent[u]);
	}
	else{
		printf("null parent point");
		return(-1);		//need to return some integer
	}
		//exit(1);
}
//return the distance of the graph
int getDist(Graph G, int u){
	if(G==NULL)
	{
		printf("getdist called on a null graph");
		exit(1);
			}
	else if(u<1||u>G->order){
		printf("getdist called on out of bounds");
		exit (1);
	}
	else 
		return(G->distance[u]);
	}
//return the path of the graph G with the passed in list
void getPath(List L, Graph G, int u){
	if(L==NULL||G==NULL){
		printf("Can't getpath of a null ref" );
		exit(1);
	}
	if(getSource(G)==NIL){	//if the source is 0 then exception
		printf("can't call getPath when source=0");
		exit(1);
	}
		else if (G->sourceVertex!=0){
			if (u == G->sourceVertex){//if the source and u is the same then just append
				append(L, u);
			}
			else if (G->parent[u] == NIL){ //if the parent is 0 then append to the new list
				append(L, NIL);
			}
			else{
				getPath(L, G, G->parent[u]); //recursivly call it and append after
				append(L, u);	//append after
			}
		}
}
/*** Manipulation procedures ***/
//deletes and puts everything in null/0 state
void makeNull(Graph G){
	if(G!=NULL){					//check with certain preconditions
		for(int i=1; i<=getOrder(G);i++){
			clear(G->vertices[i]); //clear the neighbors
		}
		G->sourceVertex=0; //set the sources to 0
		G->size=0;		//make size equal to 0
	}
	else
		printf("can't make a null Graph null again");

}
//method to create an edge joining u to v
void addEdge(Graph G, int u, int v){
	if(G!=NULL){
		if(u>=1||u<=G->order||v>=1||v<=G->order){
			addArc(G,u,v);	//call add arc to make one side
			addArc(G,v,u);	//call add arc to make the other side
			G->size--;		//since add Arc is called twice you have to decrememnt the size
		}
	}
	else {
		printf("can't add edge to a null graph");
	}
}
//joins an arc from point u to point v
void addArc(Graph G, int u, int v){
	if(G!=NULL){							//check with certain preconditions
			if(u>=1||u<=G->order||v>=1||v<=G->order){	//check with certain preconditions
			if (length(G->vertices[u])==0){
				append(G->vertices[u], v); //append if the length=0
			}
			else{
				List list=G->vertices[u]; 
	  			moveBack(list);	//move to the back of the list
	  			while(index(list)!=-1){
	  				if(get(list)<v) {
	     				movePrev(list);	//compare the value with v and move prev if greater than
	   				}
	   				else 
	   					break; //otherwise break out of the while loop
	   			}
	   			if(index(list)==-1)
	   		   		append(list, v);//append is null
	 			else 
	      			insertBefore(list, v); //insert before when in the right spot 
				}
			}
			G->size++; //increment the size once with the arc
	}
	else 
		printf("error adding the arc");
		//exit(1);
}

void BFS(Graph G, int s){
	if(G==NULL){			//check with certain preconditions
		printf("can't call on a NULL graph");
		exit(1);
	}
	if(s<=0||s>getOrder(G)){			//check with certain preconditions
		printf("error on out of bounds source vertex s");
		exit(1);
	}
	
	for(int i=1; i<=G->order; i++){
		G->distance[i]=INF;
		G->parent[i]=NIL;	//set all values to 0
		G->color[i]='W';	//set all the values in the color array to white
	}
	G->color[s]='G';		//set the s value to gray (passed through once)
	G->parent[s]=NIL;		//leave the parent as 0
	G->distance[s]=0;
	G->sourceVertex=s;		//set the source as s
	List nlist= newList();
	append(nlist,s);		//append the s into the new list
	
	while(length(nlist)>=1){
		int a=front(nlist);
		deleteFront(nlist);		
		List list= G->vertices[a];
		moveFront(G->vertices[a]); //move to the front of the neighbors array
		while(index(list)!=-1){
			int x= get(G->vertices[a]);
			if(G->color[x]=='W'){		//check if the value in the char array is white
				G->color[x]='G';		//if so set to gray
				G->parent[x]=a;			//set to front of the list
				G->distance[x]=G->distance[a]+1;	//increase the distance by 1
				append(nlist,x);		//append the new vertex
			}
			moveNext(G->vertices[a]);	//keep moving next until the index is NULL
		}
		G->color[a]='B';		//after set the color to BLACK
	}
	freeList(&nlist);			//free the List that we were appending into/ moving through
}

//printing operation
void printGraph(FILE* out, Graph G){
	if(out==NULL){						//check with certain preconditions
		printf("no out file");
		exit(1);
	}
	if(G==NULL){						//check with certain preconditions
		printf("can't call printGraph on a null graph");
		exit(1);
	} 
	for(int i=1; i<=G->order;i++){
		fprintf(out,"%d: ", i);					//printing Graph with #: ___
		printList(out, G->vertices[i]);			//print all the neighbors in the list
		fprintf(out, "\n");
	}
}