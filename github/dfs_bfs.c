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
        if ((G->data[i].u == u && G->data[i].v==v) || (G->data[i].u==v && G->data[i].v==u)){
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
        if ((G.data[i].u==u && G.data[i].v==v) || (G.data[i].u==v && G.data[i].v==u))
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
////////////STACK/////////////
typedef struct {
    int data[100];
    int size;
} stack;

void makeNullStack(stack *S){
    S->size = 0;
}
void push(stack *S, int x){
    S->data[S->size] = x;
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
/////DFS/////
void dfs(graph G){
    printf("\nDuyet DFS:\n");
    stack S;
    int mark[100];
    makeNullStack(&S);

    for (int i=1;i<=G.n;i++){
        mark[i]=0;
    }
    for (int i=1;i<=G.n;i++){
        if(mark[i]==0){
            push(&S,i);
            while(!empty(S)){
                int x = top(S);
                pop(&S);
                if (mark[x]!=0) continue;
                printf("Duyet %d\n",x);
                mark[x]=1;
                list L = neighbors(G,x);
                for (int j=0;j<L.size;j++){
                    int e = elementAt(L,j);
                    push(&S,e);
                }
            }
            printf("\n");
        }
    }
}
//////QUEUE///////
typedef struct {
    int data[100];
    int front,rear;
} queue;

void makeNullQueue(queue *Q){
    Q->front=0;
    Q->rear=-1;
}
void pushQ(queue *Q, int x){
    Q->rear++;
    Q->data[Q->rear]=x;
}
int topQ(queue Q){
    return Q.data[Q.front];
}
void popQ(queue *Q){
    Q->front++;
}
int emptyQ(queue Q){
    return Q.front > Q.rear;
}
void bfs(graph G){
    printf("\nDuyet BFS:\n");
    queue Q;
    int mark[100];
    makeNullQueue(&Q);

    for (int i=1;i<=G.n;i++){
        mark[i]=0;
    }
    for (int i=0;i<=G.n;i++){
        if (mark[i]==0) {
            pushQ(&Q,i);
            printf("Duyet %d\n",i);
            mark[i]=1;
            while(!emptyQ(Q)) {
                int x = topQ(Q);
                popQ(&Q);
                list L = neighbors(G,x);
                for (int j=0;j<L.size;j++){
                    int e = elementAt(L,j);
                    if (mark[e]==0){
                        printf("Duyet %d\n",e);
                        mark[e]=1;
                        pushQ(&Q,e);
                    }
                }
            }
            printf("\n");
        }
    }
}
int main(int  argc, char const *argv[]){
    freopen("dothi.txt","r",stdin);
    int n,m,u,v;
    scanf("%d%d",&n,&m);
    graph G;
    initGraph(&G,n);
    for (int i=1; i<=m;i++){
        scanf("%d%d",&u,&v);
        addEdge(&G,u,v);
    }
    for (int i=1;i<=n;i++){
        degree(G,i);
    }
    for (int i=1;i<=n;i++){
        list L = neighbors(G,i);
        printf("neighbors(%d): ",i);
        for (int j=0;j<L.size;j++){
            printf("%d ",elementAt(L,j));
        }
        printf("\n");
    }
    dfs(G);
    bfs(G);
    return 0;
}
