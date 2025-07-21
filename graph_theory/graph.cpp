#include<bits/stdc++.h>
using namespace std;

class graph {
    public:
    int node;
    int edges;
    map<int,list<int>>adj;
    //since using only directed graph no direction used
    void addEdge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void printAdjList(){
        for(auto k:adj){
            cout<<k.first<<"->";
            for(auto m: k.second){
                cout<<m<<", ";
            }
            cout<<endl;
        }
    }
};

// without weights

vector<int> bfs_traversal(graph &g){
    map<int,bool>visited(g.node,0);
    vector<int>ans;
    queue<int>q;
    map<int,list<int>>Adj=g.adj;
    q.push(0);
    while(!q.empty()){
        int front=q.front();
        q.pop();

        ans.push_back(front);
        visited[front]=true;
        
        for(auto M:Adj[front]){
            if(visited[M]==false){
                q.push(visited[M]);
                visited[M]=1;
            }
        }
        
    }

    return ans;
}

//dfs 
void dfs(int node,map<int,bool>&visited, vector<int>&result,map<int,list<int>>Adj){
result.push_back(node);
for(auto k: Adj[node]){
    if(!visited[k]){
        visited[k]=1;
        dfs(k,visited,result,Adj);
    }
}
}
void dfs_traversal(graph g){
    map<int,list<int>>Adj=g.adj;
    map<int,bool>visited(g.node, 0);
    vector<int>result;
    dfs(0,visited,result,Adj);
}

int main(){
    int n,m;  // n->no of nodes,  m-> no of edges
    cout<<"Enter the number of nodes: "<<endl;
    cin>>n;
    cout<<"Enter the number of edges: "<<endl;
    cin>>m;
    graph g;
    g.node=n;
    g.edges=m;
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        g.addEdge(u,v);
    }

    g.printAdjList();

}
