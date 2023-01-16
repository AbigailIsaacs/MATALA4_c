#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "nodes.h"
#include "algo.h"


int shortPath (Graph* g,int s,int t){
	
	Node *toPrint = NULL;

	for (int i = 0; i< g->V ; i++){
		if(g->nodes[i].name == s){
			g->nodes[i].d = 0;
		}	
		else{
			g->nodes[i].d = INT_MAX;
		}
		g->nodes[i].pi = NULL;
		g->nodes[i].color = 1;
	}

	Node *start = NULL;
	int notDone = 1;
	Node *toRelax = NULL;
	while(notDone){
		int min = INT_MAX;
		for (int i = 0; i< g->V ; i++){
			if(g->nodes[i].name != t && g->nodes[i].color==1){
				if(g->nodes[i].d<= min){
					min = g->nodes[i].d;
					start = &(g->nodes[i]);
				}
			}
	
		}
		for(int i=0; i< start->numEdges; i++){
			
			for(int j=0; j<g->V;j++){
				if(start->edges[i].dest == g->nodes[j].name){
					if( g->nodes[j].color==0){
						break;
					}
					toRelax = &(g->nodes[j]);
				}
			}
			if(start->d != INT_MAX){
				if(toRelax->d > start->edges[i].weight + start->d){
					toRelax->d = start->edges[i].weight + start->d;
					toRelax->pi = start;
				}
			}

		}
		start->color =0;
		notDone = 0;
		for(int i=0; i< g->V; i++){
			if(g->nodes[i].name == t){
				toPrint= &(g->nodes[i]);
			}
			if(g->nodes[i].color !=0 && g->nodes[i].name != t){
				notDone = 1;
			}
		}

	}
	if(toPrint->d == INT_MAX){
		return -1;
	}
	else{
		return (toPrint->d);
	}	
}

void TSP(Graph* g){

	int size= 0;;
	scanf("%d",&size);
	int *array = (int*)malloc(size * sizeof(int));
	if(array==NULL){
		exit(-1);
	}
	for (int i=0; i<size;i++){
		scanf("%d", &array[i]);
	}
	int numComb = 0;
	int min= INT_MAX;
	int **matrix= allComb(size,array,&numComb);
	for (int i=0;i<numComb;i++){
		int currentsum=0;
		int isPath= 1;
		for (int j=0; j<size-1;j++){
			int currentpath = shortPath(g,matrix[i][j],matrix[i][j+1]);
			if(currentpath == -1){
				isPath= 0;
				break;
			}
			currentsum+=currentpath;
		}
		if(currentsum<min && isPath){
			min=currentsum;
		}
	}



	free(array);
	for (int i = 0; i < numComb; i++) {
	free(matrix[i]);
	}
	free(matrix);
	if(min==INT_MAX){
		min = -1;
	}
	printf("TSP shortest path: %d \n",min);



}

int** allComb(int size,int array[],int *numComb){
	int k = size;
	
	int num_combinations = 1;
	for (int i = 1; i <= k; i++) {
		num_combinations *= i;
	}
	*numComb =num_combinations;
	int** matrix = (int**)malloc(num_combinations * sizeof(int*));
	if(matrix==NULL){
		exit(-1);
	}
	for (int i = 0; i < num_combinations; i++) {
		matrix[i] = (int*)malloc(k * sizeof(int));
		if(matrix[i]==NULL){
			exit(-1);
		}
	}

	int row = 0;
	print_combinations(array, size, k, 0, matrix, &row);


	return matrix;

}

void print_combinations(int array[], int size, int k, int index, int** matrix, int* row) {
	if (index == k) {
		for (int i = 0; i < k; i++) {
	    		matrix[*row][i] = array[i];
		}	
		(*row)++;
		return;
	}
	for (int i = index; i < size; i++) {
		int temp = array[index];
		array[index] = array[i];
		array[i] = temp;
		print_combinations(array, size, k, index + 1, matrix, row);
		temp = array[index];
		array[index] = array[i];
		array[i] = temp;
	}
}




