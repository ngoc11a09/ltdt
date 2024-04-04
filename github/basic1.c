#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define MAX_M 100

typedef struct {
    int x,y;
} Edge;

typedef struct {
    int n,m;
    Edge edges[MAX_M];
} Graph;

void initGraph(Graph *G, int n){
    G->n = n;
    G->m = 0;
}

void addEdge(Graph *G, int u, int v){
    G->edges[G->m].x = u;
    G->edges[G->m].y = v;
    (G->m)++;
}

int isAdjacent(Graph G, int x, int y){
    for (int i = 0; i < G.m; i++){
        if ((G.edges[i].x == x && G.edges[i].y == y) || (G.edges[i].x == y && G.edges[i].y == x))
            return 1;
    }
    return 0;
}

int degree(Graph G, int x){
    int deg = 0;
    for (int i = 0; i < G.m; i++){
        if (G.edges[i].x == x) deg++;
        if (G.edges[i].y == x) deg++;
    }
    return deg;
}

void neighbours(Graph G, int u){
    for (int v = 1; v <= G.m; v++){
        if (isAdjacent(G,u,v) != 0)
            printf("%d ",v);
    }
    printf("\n");
}

int main(){
    Graph G;
    int n,m,e;
    freopen("test.txt","r",stdin);
    scanf("%d%d",&n,&m);
    initGraph(&G,n);
    for (int i=1; i<=m;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        addEdge(&G,u,v);
    }
    for (int i=1;i<=G.n;i++)
        printf("Degree(%d): %d\n", i, degree(G, i));
    printf("-------------------------------\n");

    for (int i=1;i<=G.n;i++)
        for (int j=1;j<=G.n;j++){
            if (isAdjacent(G,i,j)==1) {
                printf("%d ke %d\n",i,j);
            } else {
                printf("%d khong ke %d\n",i,j);
            }
        }

    printf("-------------------------\n");

    for (int i=1; i<=G.n;i++){
        printf("Neighbours cua %d la: ",i);
        neighbours(G,i);
        printf("\n");
    }
    return 0;
}
