#include<stdio.h>
#define Max_Length 20

typedef struct {
    int u,v;
} edge;

typedef struct {
    int n,m;
    edge data[Max_Length];
} graph;

typedef struct {
    int data[Max_Length];
    int size;
} list;

void makeNull(list *L){
    L->size = 0;
}
int elementAt(list L, int x){
    return L.data[x];
}
void pushList(list *L, int x){
    L->data[L->size]=x;
    L->size++;
}
void initGraph(graph *G,int n){
    G->n = n;
    G->m = 0;
    printf("Do thi G duoc khoi tao voi so dinh n = %d va so canh m = %d\n",G->n,G->m);
}
void addEdge(graph *G, int u, int v){
    for (int i=0;i<G->m;i++){
        if ((G->data[i].u == u && G->data[i].v==v)){
            printf("Canh da co trong do thi\n");
            return;
        }
    }
    G->data[G->m].u=u;
    G->data[G->m].v=v;
    G->m++;
    printf("Do thi da them vao canh %d %d\n",G->data[G->m-1].u, G->data[G->m-1].v);
}
int adjacent(graph G, int u, int v){
    for (int i=0;i<=G.m;i++){
        if ((G.data[i].u==u && G.data[i].v==v))
            return 1;
    }
    return 0;
}
void degree(graph G, int x){
    int cnt=0;
    for (int i=0;i<=G.m;i++){
        if (adjacent(G,x,i)) cnt++;
    }
    printf("Bac cua canh %d la: %d\n",x,cnt);
}
list neighbors(graph G, int x){
    list listVertex;
    makeNull(&listVertex);
    for (int i=1;i<=G.n;i++){
        if (adjacent(G,x,i)==1) pushList(&listVertex,i);
    }
    return listVertex;
}
////DFS dequy/////
int mark[100];
void traversal(graph G, int x){
    if(mark[x]==1) return;
    printf("Duyet %d\n",x);
    mark[x]=1;
    list L = neighbors(G,x);
    for (int j=0; j<L.size;j++){
        int e = elementAt(L,j);
        traversal(G,e);
    }
}
void dfs(graph G){
    for (int i=1;i<=G.n;i++) mark[i]=0;
    traversal(G,1);
}
//////STRONG CONNECT/////
typedef struct {
    int data[100];
    int size;
} stack;
void makeNullStack(stack *S){
    S->size=0;
}
void push(stack *S, int x){
    S->data[S->size]=x;
    S->size++;
}
void pop(stack *S){
    S->size--;
}
int top(stack S){
    return S.data[S.size-1];
}
int empty(stack S){
    return S.size==0;
}
#define min(a,b) (a>b ? b : a)

int num[100], min_num[100], on_stack[100],k;
stack S;

void strongConnect(graph G, int x){
    num[x]=k;
    min_num[x]=k;
    k++;
    push(&S,x);
    on_stack[x]=1;
    list L=neighbors(G,x);
    for (int j=0;j<L.size;j++){
        int e = elementAt(L,j);
        if(num[e] < 0){
            strongConnect(G,e);
            min_num[x] = min(min_num[x], min_num[e]);
        } else {
            if (on_stack[e]) min_num[x] = min(min_num[x],num[e]);
        }
    }
    printf("min_num[%d] = %d\n",x,min_num[x]);
    if(num[x]==min_num[x]){
        printf("%d la dinh khop\n",x);
        int w;
        do{
            w=top(S);
            pop(&S);
            on_stack[w]=0;
        } while(w!=x);
    }
}
int main(){
    freopen("dothi.txt","r",stdin);
    int n,m,u,v;
    scanf("%d%d",&n,&m);
    graph G;
    initGraph(&G,n);
    for (int i=1; i<=m;i++){
        scanf("%d%d",&u,&v);
        addEdge(&G,u,v);
    }
    dfs(G);
    for (int i=1;i<=n;i++){
        num[i]=-1;
        on_stack[i]=0;
    }
    k=1;
    makeNullStack(&S);
    for (int i=1; i<=n;i++){
        if(num[i]==-1){
            strongConnect(G,i);
        }
    }
    return 0;
}
