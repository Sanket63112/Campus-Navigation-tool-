#include<bits/stdc++.h>
using namespace std;

class graph {
    public:
    int node;
    int edges;
    unordered_map<int,list<pair<int,int>>>adj;
    //since using only directed graph no direction used
    void addEdge(int u, int v, int d){
        adj[u].push_back(make_pair(v,d));
        adj[v].push_back(make_pair(u,d));
    }

    void printAdjList(){
        for(auto k:adj){
            cout<<k.first<<"->";
            for(auto m: k.second){
                cout<<"["<<m.first<<","<<m.second<<"], ";
            }
            cout<<endl;
        }
    }
    
};

vector<int> shortest_distance(graph g, int start, int end, vector<int>&parent){
    unordered_map<int,list<pair<int,int>>>adj=g.adj;
    vector<int>dist(g.node,INT_MAX);
    dist[start]=0;  
    set<pair<int,int>>s;// pair<dist, node>
    
    
    s.insert(make_pair(0,start));

    while(!s.empty()){
        auto top=*(s.begin());
        int nodedist=top.first;
        int topnode=top.second;
        s.erase(s.begin());

        for(auto k: adj[topnode]){
            
            if(nodedist+k.second < dist[k.first]){
                auto record=s.find(make_pair(dist[k.first],k.first));
                if(record!=s.end()){
                    s.erase(record);
                }
                dist[k.first]=nodedist+k.second;
                parent[k.first]=topnode;
                s.insert(make_pair(dist[k.first],k.first));
            }
        }
    }
    return dist;

}

int main(){
graph g;
int n;
cout<<"enter number of nodes: "<<endl;
cin>>n;
g.node=n;

cout<<"enter number of edges: "<<endl;
cin>>n;
g.edges=n;
int u,v,d;
cout<<"enter the adj list:"<<endl;
for(int i=0;i<g.edges;i++){
    
    cin>>u>> v>> d;
    g.addEdge(u,v,d);
}
cout<<"adj LIst:"<<endl;
g.printAdjList();

int source,desti;
cout<<"enter the source node: "<<endl;
cin>>source;
cout<<"enter the desti node: "<<endl;
cin>>desti;

vector<int>parent(g.node,-1);

vector<int>ans=shortest_distance(g,source, desti,parent);
for(int i=0;i<g.node;i++){
    cout<< 0 <<" to "<<i<<" shortest path "<<ans[i]<<endl;
}
cout<<endl;
cout<<"parent array"<<endl;
for(int i=0;i<g.node;i++){
    cout<< i<<"'s parent is "<<parent[i]<<endl;
}

vector<int>path;
cout<<"shortest path from " <<source <<" to "<<desti<<endl;
int temp=desti;
while(temp!=source){
    path.push_back(temp);
    temp=parent[temp];
}
path.push_back(source);

for(int i=0;i<path.size();i++){
    cout<<path[i]<<"->";
}

}







/*
58
64
0 1 43
1 2 90
1 3 51
1 16 85
2 4 68
4 5 31
16 14 55
14 15 66
14 13 16
13 12 37
13 36 119
12 11 44
11 10 57
10 9 114
10 22 46
9 8 48
8 7 93
7 5 77
7 58 45
5 6 81
6 39 24
17 19 35
17 18 37
17 58 74
19 20 55
19 23 46
18 21 48
18 58 54
22 31 30
31 30 34
31 32 44
30 34 23
30 26 42
30 35 67
34 32 41
34 45 77
25 24 41
25 26 48
25 45 69
26 27 47
27 28 34
28 29 46
32 33 77
33 36 83
33 48 23
37 38 144
40 39 112
40 41 52
41 42 62
42 43 73
43 44 52
44 45 83
45 46 64
46 47 38
46 57 91
48 49 49
48 52 67
49 50 48
50 51 33
52 53 42
53 54 63
54 55 59
55 57 38
56 57 19

*/