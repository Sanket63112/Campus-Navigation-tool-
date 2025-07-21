#include <bits/stdc++.h>
#include <fstream>
#include "./json-develop/single_include/nlohmann/json.hpp" // Include the JSON library

using json = nlohmann::json;
using namespace std;

class graph {
public:
    int node;
    int edges;
    unordered_map<int, list<pair<int, int>>> adj;

    void addEdge(int u, int v, int d) {
        adj[u].push_back(make_pair(v, d));
        adj[v].push_back(make_pair(u, d)); // If undirected
    }

    void printAdjList() {
        for (auto k : adj) {
            cout << k.first << "->";
            for (auto m : k.second) {
                cout << "[" << m.first << "," << m.second << "], ";
            }
            cout << endl;
        }
    }
};
vector<int> primsalgo(int n,int source,graph g){
    unordered_map<int,list<pair<int,int>>>adj=g.adj;
    vector<int>key(n+1);
    vector<bool>mst(n+1);
    vector<int>parent(n+1);
    for(int i=0;i<=n;i++){
        key[i]=INT_MAX;
        mst[i]=false;
        parent[i]=-1;
    }
    key[source]=0;
    parent[source]=-1;

    for(int i=source;i<=n;i++){
        int mini=INT_MAX;
        int u;

        for(int v=source;v<=n;v++){
            if(mst[v]==false && key[v]<mini){
                u=v;
                mini=key[v];
            }
        }
        mst[u]=true;
        

        for(auto it:adj[u]){
            int v=it.first;
            int w=it.second;
            if(mst[v]==false && w<key[v]){
                parent[v]=u;
                key[v]=w;
            }
        }
        
    }
    return parent ; 

}

int main() {
    
    graph g;
    int n;
    cout << "Enter number of nodes: " << endl;
    cin >> n;
    g.node = n;

    cout << "Enter number of edges: " << endl;
    cin >> n;
    g.edges = n;

    //creating map
    map<string,int>roads;
    roads["start"]=0;
    roads["karavali"]=52;
    roads["aravali"]=53;
    roads["vindhya"]=54;
    roads["satpura"]=55;
    roads["nilgiri"]=56;
    roads["new_pg_hostel"]=49;
    roads["pushpagiri"]=50;
    roads["ncc"]=48;
    roads["sja/ccc"]=32;
    roads["foodcourt"]=34;
    roads["cids"]=30;
    roads["met_dept"]=26;
    roads["sbi_atm/cdc"]=45;
    roads["lhc_a"]=35;
    roads["macs_dept"]=25;
    roads["central_lib"]=23;
    roads["pavilion"]=29;
    roads["main_building"]=17;
    roads["nitk_exitgate"]=20;
    roads["lhc_c"]=42;
    roads["health_care"]=36;
    roads["sac"]=11;
    roads["boys_co_op"]=46;
    roads["mech_dept"]=2;
    roads["girls_block/applied_math_dept"]=4;
    roads["civil_dept"]=5;
    roads["mining_dept"]=58; 
    roads["nitk_main_gate"]=6;
    roads["nitk_west_gate"]=39;
    roads["nitk_beach"]=38;
    roads["ece_dept"]=40;
    roads["ee_dept/it_dept"]=41;
    roads["chem_dept"]=16;
    roads["tennis_court"]=1;
    roads["chemical_reserach_ctr"]=9;
    roads["mega_tower"]=47;
    roads["swimming_pool"]=15;


    int u, v, d;
    cout << "Enter the adjacency list (u v d):" << endl;
    for (int i = 0; i < g.edges; i++) {
        cin >> u >> v >> d;
        g.addEdge(u, v, d);
    }
    cout << "Adjacency List:" << endl;
    g.printAdjList();

    int source, desti;
    string sour,des;
    inputs:
    cout << "Enter the source : " << endl;
    cin >> sour;
    cout << "Enter the destination: " << endl;
    cin >> des;
    
    if(roads.find(sour)==roads.end()|| roads.find(des)==roads.end()){
        cout<<"****  Invalid Inputs ****"<<endl;
        cout<< "Please enter valid source or destination "<<endl;
        goto inputs;
        
    }

    source=roads[sour];
    desti=roads[des];

    vector<int> ans = primsalgo(desti,source,g);
    vector<pair<int,int>>min_edges;
    for(int i=1;i<ans.size();i++){
        if(ans[i]!=-1){min_edges.push_back({i,ans[i]});};

    }
    
    json output;
    for (auto& edge : min_edges) {
        output["edges"].push_back({{"u", edge.first}, {"v", edge.second}});
    }

    ofstream file("mst_edges.json");
    file << output.dump(4); // Pretty-print JSON with an indentation of 4 spaces
    file.close();

    cout << "MST edges saved to mst_edges.json" << endl;
    system("python visualize_mst.py");

    return 0;
}
