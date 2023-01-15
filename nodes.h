#pragma once

struct edge {
	int src, dest, weight;	
};
typedef struct edge Edge;

struct node {
	int name, numEdges;
	Edge* edges;
	int d ;
	struct node * pi;
	int color;

};
typedef struct node Node;

struct graph {
    int V;
    Node* nodes;
};
typedef struct graph Graph;


void freeGraph(Graph *g);
Graph* createGraph(int V);
int insertInputToGraph(Graph* g,char * letter);
Edge* createEdges(int newNodeData[] ,Node* pNode,int name, int numEdges);
char isFineLetter (char str[]);
int createNode(Graph *g, char * letter);
void deleteNode(Graph *g);
