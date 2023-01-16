#include <stdio.h>
#include <stdlib.h>
#include "nodes.h"
#include "algo.h"


int main() {

	
	char  letter ='f';
	int V =0;
	Graph* g ;
	int succeed;
	scanf("%c ", &letter);
	int notFirstA = 0;
	while (letter!= 'a'){
		
		if(letter=='A'){
			if(notFirstA){
				freeGraph(g);
				
			}
			scanf("%d", &V);
			g = createGraph(V);
			if(g==NULL){
				freeGraph(g);
				return -1;
			}
			letter ='f';
			if (V!=0){
				succeed = insertInputToGraph(g, &letter);
				if(succeed==-1){
					freeGraph(g);
					return -1;
				}
			}
			else{
				if(scanf("%s",&letter) == EOF){
					letter='a';
				}
			}
			notFirstA=1;

		}
		if(letter=='B'){
			letter ='f';
			succeed = createNode(g,&letter);
			if(succeed==-1){
				freeGraph(g);
				return -1;
			}
		}
		if(letter=='D'){
			letter ='f';
			deleteNode(g);
			if(scanf("%s",&letter) == EOF){
				letter='a';
			}

		}
		if(letter=='S'){
			letter ='f';
			int s, t;
			scanf("%d",&s);
			scanf("%d",&t);	
			int shortest = shortPath(g,s,t);
			printf("Dijsktra shortest path: %d \n",shortest);
			if(scanf("%s",&letter) == EOF ){
				letter='a';
			}

		}
		if(letter=='T'){
			letter ='f';
			TSP(g);
			if(scanf("%s",&letter) == EOF){
				letter='a';
			}

		}
	}
	freeGraph(g);

    return 0;
}





