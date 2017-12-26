//Rhea Lingaiah
//rlingaia
//PA5
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
	int *discover; //discover array
	int *finish; //finish array
	int *time;
} GraphObj;

/***Constructors-Destructors ***/
Graph newGraph(int n){
	Graph G= malloc(sizeof(GraphObj));
	G->vertices= calloc(n+1,sizeof(List));
	G->color=calloc(n+1,sizeof(int));
	G->parent=calloc(n+1,sizeof(int));
	G->discover=calloc(n+1,sizeof(int));
	G->finish=calloc(n+1, sizeof(int));

	G->order=n;
	G->size=0;
	G->sourceVertex=NIL;
	for(int i=1; i<=n;i++){
		G->vertices[i]=newList();
		G->parent[i]=NIL;
		G->discover[i]=UNDEF;
		G->finish[i]=UNDEF;
		G->color[i]='W'; //created an array of characters for color
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
		free((*pG)->discover);
		free((*pG)->finish);
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
//return the discover of the graph
int getDiscover(Graph G, int u){
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
		return(G->discover[u]);
	}
//return the finish point of the graph
int getFinish(Graph G, int u){
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
		return(G->finish[u]);
}
/*** Manipulation procedures ***/

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
void addArc(Graph G, int u, int v) {
	if(u>=1&&u<=getOrder(G)&& v>=1&&v<=getOrder(G)){
		List list=G->vertices[u];
		moveFront(list);
		while(index(list)!=-1){ 
			if(get(list)<v){//if the v vertex is greater than the one in the list
				moveNext(list); //then movenext
			}
			else
				break;
		}
		if(index(list)!=-1){
			insertBefore(list,v); //if the list is not null then insert BEFORE the vertex
		}
		else if(index(list)==-1){
			append(list,v); //if the list is null the simply append
		}
		G->size++; //increment the size since adding an edge
	}
	else{
		printf("calling add arc with a vertex out of bounds or NUll graph");
	}
}
//helper method of DFS
void Visit(Graph G, List S, int u, int *time) {
	G->discover[u]=++(*time);		//increment the time then set the new time
	G->color[u]='G';
	moveFront(G->vertices[u]);		//move to the front of the list array
	while(index(G->vertices[u])!=-1) {
		int X=get(G->vertices[u]);
		if(G->color[X]== 'W') {	//check if each color is W
			G->parent[X]=u;
			Visit(G,S,X,time);	//recusively call till Gray
		}
		moveNext(G->vertices[u]);
	}
	G->color[u] = 'B';		//set to black because finished
	G->finish[u] =++(*time);	//increment the time then set the address
	prepend(S,u);
}

//preforms depth for search
void DFS(Graph G, List S) {
	if (G==NULL){
		printf("can't call DFS on null graph");
		exit(1);
	}
	if(length(S) != getOrder(G)) {
		printf("can't call dfs with different sizes\n");
		exit(1);
	}
	for(int i = 1;i<=getOrder(G);i++) {
		G->color[i]= 'W';	//sets the color of the graph equal to white
		G->parent[i]= NIL;	//sets the all the parents equal to 0
		G->discover[i]= UNDEF;	//has not been discovered
		G->finish[i]= UNDEF;	//has not been finished
	}
	int time=0;
	moveFront(S);		//move to the front of the list
	while(index(S)!=-1) {	//make sure index is not null
		if(G->color[get(S)]=='W') {
			Visit(G,S,get(S),&time);	//recursively call visit
		}
		if(index(S)!=-1)
			moveNext(S);
	}
	for(int i=0;i<getOrder(G);i++) {
		deleteBack(S);	//delete the back element of the list
	}
}
//transposes the graph operation
Graph transpose(Graph G){
	if(G!=NULL){
		Graph graph=newGraph(getOrder(G)); //creating a new graph the same size as the original graph
		for(int i=1;i<=getOrder(G);i++){
			moveFront(G->vertices[i]); //go through all the neighbors list
			while(index(G->vertices[i])!=-1){
				addArc(graph, get(G->vertices[i]),i); //switch the location and the value to transpose
				moveNext(G->vertices[i]); //go through the entire list
			}
		}
		return graph;
	}
	else{
		printf("can't call transpose on a null graph");
	}
}
//copying graph operation
Graph copyGraph(Graph G){
	if(G!=NULL){
		Graph graph=newGraph(getOrder(G)); //creating a new graph the same size as the original graph
		for(int i=1; i<=getOrder(G);i++){
			moveFront(G->vertices[i]); //move to the front of the neighbors list
			while(index(G->vertices[i])!=-1){		//until the list is null
				addArc(graph,i, get(G->vertices[i]));	//get each neighbor and put it into the new graph
				moveNext(G->vertices[i]);				//go through the entire list
			}
		}
		return graph;
	}
	else{
		printf("error because graph is null");
	}
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