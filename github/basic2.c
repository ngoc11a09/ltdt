#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define MAX_M 100
#define MAX_E 100

typedef struct{
    int a[MAX_E][MAX_E];
    int n,m;
} Graph;

void initGraph(Graph *G, int n){
    G->n = n;
    for (int i=1;i<=G->n;i++){
        for (int j=1;j<=G->n;j++){
            G->a[i][j]=0;
        }
    }
}

void addEdge(Graph *G, int x, int y){
    G->a[x][y]++;
    G->a[y][x]++;
    G->m++;
}

int isAdjacent(Graph G, int x, int y){
    return G.a[x][y]>0;
}

int degree(Graph G, int x){
    int deg = 0;
    for (int i=1;i<=G.n;i++){
        deg+=G.a[x][i];
    }
    return deg+G.a[x][x];
}

void neighbours(Graph G, int u){
    for (int v = 1; v <= G.n; v++){
        if (isAdjacent(G,u,v) != 0)
            printf("%d ",v);
    }
    printf("\n");
}

void in(Graph G){
    for (int i=1;i<=G.n;i++){
        for (int j=1;j<=G.n;j++){
            printf("%d ",G.a[i][j]);
        }
        printf("\n");
    }
}

int main(){
    Graph G;
    int n,m,e;
    freopen("dothi.txt","r",stdin);
    scanf("%d%d",&n,&m);
    initGraph(&G,n);
    int u,v;
    for (int i=1; i<=m;i++){
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
    printf("-------------------------\n");

    in(G);

    return 0;
}

