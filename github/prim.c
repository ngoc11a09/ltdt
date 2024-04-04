#include<stdio.h>
#define MXN 100
#define INF 999999
#define NO_EDGE -1

typedef struct {
    int A[MXN][MXN];
    int n,m;
} Graph;

void initGraph(Graph *pG, int n){
    pG->n = n;
    pG->m = 0;
    for (int i=1;i<=n;i++){
        for (int j=1;j<=n;j++){
            pG->A[i][j] = NO_EDGE;
        }
    }
}
void addEdge(Graph *pG, int u, int v, int w){
    pG->A[u][v] = w;
    pG->A[v][u] = w;
    pG->m++;
}

int mark[MXN],pi[MXN],p[MXN];
int prim(Graph *pG, Graph *pT, int x){
    int i;
    for (i=1;i<=pG->n;i++){
        pi[i]=INF;
        mark[i]=0;
        p[i]=-1;
    }
    pi[x]=0;
    for (int e = 1;e<pG->n;e++) {
        int min_pi = INF;
        for (int j=1;j<=pG->n;j++){
            if (mark[j]==0 && pi[j]<min_pi){
                min_pi=pi[j];
                i=j;
            }
            mark[i]=1;
        }
        for (int j=1;j<=pG->n;j++){
            if (pG->A[i][j] != NO_EDGE && mark[j] ==0){
                if (pG->A[i][j] < pi[j]) {
                    pi[j] = pG->A[i][j];
                    p[j]=i;
                }
            }
        }
    }
    initGraph(pT,pG->n);
    int sum = 0;
    for (int i=1;i<=pG->n;i++){
        if (p[i]!=-1){
            addEdge(pT,p[i],i,pG->A[p[i]][i]);
            sum += pG->A[p[i]][i];
        }
    }
    return sum;
}
int main(){
    freopen("dothi.txt","r",stdin);
    int n,m;
    scanf("%d%d",&n,&m);
    Graph G,T;
    initGraph(&G,n);
    for (int i=0;i<m;i++){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        addEdge(&G,u,v,w);
    }
    int sum = prim(&G,&T,1);
    printf("Cay khung co trong so nho nhat la: %d\n",sum);
    for (int i=1;i<=T.n;i++){
        for (int j=i+1;j<=T.n;j++){
            if (T.A[i][j]!=NO_EDGE)
                printf("%d %d %d\n",i,j,T.A[i][j]);
        }
    }
    return 0;
}
