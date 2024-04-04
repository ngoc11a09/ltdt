#include<stdio.h>
#define MXN 100

typedef struct {
    int u,v,w;
} Edge;

typedef struct {
    Edge edges[MXN];
    int n,m;
} Graph;

void initGraph(Graph *G, int n){
    G->n = n;
    G->m = 0;
}

void addEdge(Graph *G, int u, int v, int w){
    G->edges[G->m].u = u;
    G->edges[G->m].v = v;
    G->edges[G->m].w = w;
    G->m++;
}
int parent[MXN];
int findRoot(int u){
    if (parent[u]==u) return u;
    return findRoot(parent[u]);
}
int kruskal(Graph *G, Graph *T){
    int u,v,w,e;
    for ( u=0;u<G->m;u++){
        for ( v=u+1;v<G->m;v++)
        if (G->edges[u].w>G->edges[v].w){
            Edge T = G->edges[u];
            G->edges[u] = G->edges[v];
            G->edges[v] = T;
        }
    }
    initGraph(T,G->n);
    for (u=1;u<=G->n;u++) parent[u] = u;
    int sum =0;
    for ( e=0;e<G->m;e++){
        u = G->edges[e].u;
        v = G->edges[e].v;
        w = G->edges[e].w;

        int root_u = findRoot(u), root_v = findRoot(v);
        if (root_u != root_v){
            addEdge(T,u,v,w);
            parent[root_v] = root_u;
            sum +=w;
        }
    }
    return sum;
}
int main(){
    Graph T,G;
    int n,m;
    freopen("dothi.txt","r",stdin);
    scanf("%d%d",&n,&m);
    initGraph(&G,n);
    for (int e=1;e<=m;e++){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        addEdge(&G,u,v,w);
    }
    int sum=kruskal(&G,&T);
    printf("Cay khung co trong so nho nhat la %d\n",sum);
    for (int e=0;e<T.m;e++)
        printf("%d %d %d\n",T.edges[e].u,T.edges[e].v,T.edges[e].w);
    return 0;
}
