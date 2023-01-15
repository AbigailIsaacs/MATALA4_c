#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nodes.h"
#include "algo.h"
#define MAX_NUMBERALS 10





Graph* createGraph(int V) {
	Graph* g = (Graph*)malloc(sizeof(Graph));
	//if malloc failed
	if(g==NULL){
		printf("memory error");
		return NULL;
	}
	g->V = V;
	g->nodes = (Node*)malloc(V * sizeof(Node));
	//if malloc failed
	if(g->nodes ==NULL){
		printf("memory error");
		return NULL;
	}
	return g;
}

int insertInputToGraph(Graph* g,char * letter) {
	char input[MAX_NUMBERALS];
	int *newNodeData = (int*)malloc((2*(g->V-1)+1)*sizeof(int));
	if(newNodeData == NULL){
		printf("memory error");
		return -1;
	}
    	int i = 0;
	int noWhile = 1;
	scanf("%s", input);// scan n


	while (noWhile  && scanf("%s", input) != EOF ) { // name
		g->nodes[i].name = atoi(input); 
		int j = 0;
		
		while ( noWhile && (scanf("%s", input) != EOF) && (strcmp(input,"n")) ){ // int 
			*letter = isFineLetter(input);
			
			if(*letter>=65 && *letter<=90){
				noWhile=0;
				break;
			}
			int number = atoi(input);
			newNodeData[j++]=number;
			
		}
		g->nodes[i].numEdges = j/2;
		newNodeData[j]='\0';
		if(j!=0){
			g->nodes[i].edges = createEdges(newNodeData,&(g->nodes[i]),g->nodes[i].name,j/2);
			if(g->nodes[i].edges==NULL){
				printf("memory error");
				return -1;
			}
		}
		i++;
		
	}
	
	if(*letter=='f'){
		*letter = 'a';
	}
	free(newNodeData);
	return 0;
}

Edge* createEdges(int newNodeData[] ,Node* pNode,int name, int numEdges){	
	pNode-> edges = (Edge*)malloc(numEdges*sizeof(Edge));
	//if malloc failed
	if(pNode-> edges==NULL){
		printf("memory error");
		return NULL;
	}
	int j=0;
	for(int i=0; i<numEdges ;i++){
		pNode->edges[i].src = name;
		pNode->edges[i].dest = newNodeData[j++];
		pNode->edges[i].weight = newNodeData[j++];
	}
	return pNode-> edges;
	
}

char isFineLetter (char str[]){
	if(str[0]<65 || str[0]>90){
		return 'f';
	}
	return str[0];
	
}


void freeGraph(Graph *g){
	for( int i=0; i<g->V; i++){
		free(g->nodes[i].edges);
	}
	free(g->nodes);
	free(g);
}

int createNode(Graph *g, char * letter){
	int length = g->V;	
	int newName;
	int alreadyNode=0;
	int noWhile = 1;
	char input[MAX_NUMBERALS];
	int *newNodeData = (int*)malloc((2*(g->V)+1)*sizeof(int));
	if(newNodeData == NULL){
		printf("memory error");
		return -1;
	}
	scanf("%d ",&newName);
	int j = 0;
	while(noWhile && (scanf("%s", input) != EOF)){
		*letter = isFineLetter(input);
		if(*letter>=65 && *letter<=90){
			noWhile=0;
			break;
		} 
		int number = atoi(input);
		newNodeData[j++]=number;
	}
		
	newNodeData[j]='\0';
	for(int i = 0; i< length; i++){
		if(g->nodes[i].name == newName){
			free(g->nodes[i].edges);
			g->nodes[i].numEdges = j/2;
			if(j!=0){
				g->nodes[i].edges =createEdges(newNodeData,&(g->nodes[i]),g->nodes[i].name,j/2);
				if(g->nodes[i].edges==NULL){
					printf("memory error");
					return -1;
				}
			}
			alreadyNode= 1;
			break;
		}
		
	}
	if(!alreadyNode){
		Node* n ;
		n = (Node*)realloc(g->nodes, (length+1)* sizeof(Node));
		if (n==NULL){
			return -1;
		}
		g->nodes = n;
		g->V = length+1;
		g->nodes[length].name = newName; 
		g->nodes[length].numEdges = j/2;
		if(j!=0){
			g->nodes[length].edges = createEdges(newNodeData,&(g->nodes[length]),g->nodes[length].name,j/2);
			if(g->nodes[length].edges==NULL){
				printf("memory error");
				return -1;
			}
		}
	}
	if(*letter=='f'){
		*letter = 'a';
	}
	free(newNodeData);
	return 0;	

}

void deleteNode(Graph *g){
	int length = g->V;
	int deleteName;
	scanf("%d ", &deleteName);
	for(int i = 0; i< length; i++){
		if(g->nodes[i].name == deleteName){
			g->nodes[i].name = g->nodes[length-1].name;
			g->nodes[i].numEdges = g->nodes[length-1].numEdges;
			free(g->nodes[i].edges);
			g->nodes[i].edges = g->nodes[length-1].edges;
			g->nodes= (Node*)realloc(g->nodes, (length-1)* sizeof(Node));
			g->V = length-1 ;
			break;	
		}

	}	
	for (int i=0; i<length-1;i++){
		int numEdges = g->nodes[i].numEdges;
		for(int j=0 ; j< numEdges ; j++){
			if(g->nodes[i].edges[j].dest == deleteName){
				
				g->nodes[i].edges[j].dest = g->nodes[i].edges[numEdges-1].dest;
				g->nodes[i].edges[j].weight = g->nodes[i].edges[numEdges-1].weight;
				g->nodes[i].edges = (Edge*)realloc(g->nodes[i].edges, (numEdges-1)* sizeof(Edge));
				g->nodes[i].numEdges-- ;
				break;
			}
		}
	}

}	















