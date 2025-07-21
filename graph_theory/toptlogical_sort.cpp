#include <bits/stdc++.h>
using namespace std;
//used for directed acyclic trees;

void toposort(int node, stack<int>&stk, unordered_map<int,bool>&visited,unordered_map<int,list<int>>&adj){
        visited[node]=true;
        for(auto k: adj[node]){
            if(!visited[k]){
                toposort(k,stk,visited,adj);
            }
        }
        stk.push(node);
}

vector<int> topological_sort(vector<vector<int>>&edges,int v,int e){
    //e =no of edges and v= no of nodes
    unordered_map<int,list<int>>adj;
    for( int i=0;i<e;i++ ){
        adj[edges[i][0]].push_back(edges[i][1]);
    }

    //callihng dfs topolocialsort for different components;
    unordered_map<int,bool>visited;
    stack<int>stk;
    for(int i=0;i<v;i++ ){
        if(!visited[i]){
            toposort(i,stk,visited,adj);

        }
    }
    vector<int>ans;
    while(!stk.empty()){
        ans.push_back(stk.top());
        stk.pop();
    }
    return ans;
}


vector<int>kahn_algo(vector<vector<int>>edges,int v ,int e){
    unordered_map<int, list<int>>adj;
    for(int i=0;i<e;i++){
        adj[edges[i][0]].push_back(edges[i][1]);
    }    
    queue<int>q;
    vector<int>indegree;
    for(auto k:adj){
        for(auto m:k.second){
            indegree[m]++;
        }
    }

    for(int i=0;i<v;i++){
         if(indegree[i]==0)
         q.push(i);
    }
    vector<int>ans;
    while(!q.empty()){
        int front=q.front();
        ans.push_back(front);
        q.pop();
        for(auto k:adj[front]){
            indegree[k]--;
            if(indegree[k]==0)q.push(k);
        }
    }
    return ans;

}