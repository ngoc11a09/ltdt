#include<stdio.h>
#define length 100

typedef struct {
    int data[length];
    int size;
} List;

void makenullList(List *L){
    L->size=0;
}
int emptyList(List L){
    return L.size==0;
}
int elementAt(List L, int i){
    return L.data[i-1];
}

void push_back(List *L, int x){
    if (L->size+1 == length) return;
    L->data[L->size]=x;
    L->size++;
}
void copyList(List *L1, List *L2){
    makenullList(L1);
    if (emptyList(*L2)) return;
    for (int i=1;i<=L2->size;i++)
        push_back(L1,elementAt(*L2,i));
}
#define MXN 100
typedef struct {
    int A[MXN][MXN];
    int n,m;
} Graph;

void initGraph(Graph *G, int n){
    G->n=n;
    G->m=0;
    for (int i=1;i<=n;i++)
    for (int j=1;j<=n;j++){
        G->A[i][j]=0;
    }
}
void addEdge(Graph *G, int u, int v){
    G->A[u][v]=1;
    G->m++;
}
int r[MXN];
void rank(Graph *G){
    int u,v,d[MXN];
    for (u=1;u<=G->n;u++){
        d[u]=0;
        for (v=1;v<=G->n;v++)
            if (G->A[v][u]>0) d[u]++;
    }
    List L1,L2;
    makenullList(&L1);
    for (u=1;u<=G->n;u++)
        if (d[u]==0) push_back(&L1,u);
    int k=0,i;
    while (!emptyList(L1)){
        makenullList(&L2);
        for (i=1;i<=L1.size;i++){
            u=elementAt(L1,i);
            r[u]=k;
            for (v=1; v<=G->n;v++){
                if(G->A[u][v]>0){
                    d[v]--;
                    if(d[v]==0) push_back(&L2,v);
                }
            }
        }
        copyList(&L1,&L2);
        k++;
    }
}
int main(){
    Graph G;
    int n,m;
    freopen("dothi.txt","r",stdin);
    scanf("%d%d",&n,&m);
    initGraph(&G,n);
    for (int e=1;e<=m;e++){
        int u,v;
        scanf("%d%d",&u,&v);
        addEdge(&G,u,v);
    }
    rank(&G);

    printf("Xep hang dinh cua do thi:\n");

    for (int u=1;u<=G.n;u++)
        printf("rank[%d] = %d\n",u,r[u]);
    return 0;
}
