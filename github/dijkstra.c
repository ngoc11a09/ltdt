#include<stdio.h>
#define INF 999999
#define MXN 100

typedef struct {
    int L[MXN][MXN];
    int n,m;
} Graph;

void initGraph(Graph *pG, int n){
    pG->n = n;
    pG->m = 0;
    for (int i=1;i<=n;i++){
        for (int j=1;j<=n;j++){
            pG->L[i][j] = INF;
        }
    }
}
void addEdge(Graph *pG, int u, int v, int w){
    pG->L[u][v] = w;
    pG->m++;
}

#define NO_EDGE -1
int mark[MXN],pi[MXN],p[MXN];
void dijkstra(Graph *pG, int s){
    int i;
    for (i=1;i<=pG->n;i++){
        pi[i]=INF;
        mark[i]=0;
    }
    pi[s]=0;
    p[s]=-1;
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
            if (pG->L[i][j] != NO_EDGE && mark[j] ==0){
                if (pi[i] + pG->L[i][j] < pi[j]) {
                    pi[j] = pi[i] + pG->L[i][j];
                    p[j]=i;
                }
            }
        }
    }
}
int main(){
    freopen("dothi.txt","r",stdin);
    int n,m;
    scanf("%d%d",&n,&m);
    Graph G;
    initGraph(&G,n);
    for (int i=0;i<m;i++){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        addEdge(&G,u,v,w);
    }
    dijkstra(&G,1);
    for (int i=1;i<=G.n;i++){
        printf("pi[%d] = %d, p[%d] = %d\n",i,pi[i],i,p[i]);
    }
    printf("---------------------\n");
    for (int i=1;i<=G.n;i++){
        if (pi[i]==INF) {
            printf("%d ko co duong di den.\n",i);
            return 0;
        }
        int tmp = i;
        while (p[tmp]!=-1){
            printf("%d -> ",tmp);
            tmp = p[tmp];
        }
        printf("%d\n",1);
    }
}
