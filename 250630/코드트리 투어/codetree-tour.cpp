#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#define INF 2e9
#define P pair<int,int>
using namespace std;

// 간선 방향 x
// 0부터 시작
int n,m,u,v,w,Q,i,cmd,s;
int id, rev, dst;
map<int,pair<int,P>> product;
vector<P> g[2001];

int dist[2001];
void init(){
    for(i=0;i<2001;i++)
        g[i].clear();
    product.clear();
}

void init_dist(){
    fill(dist,dist+2001,INF);
}

void dijkstra(int start){
    int cost;
    priority_queue<P,vector<P>,greater<P>> pq;
    pq.push({0,start});
    dist[start] = 0;
    while(!pq.empty()){
        int d = pq.top().first;
        int vtx = pq.top().second;
        pq.pop();
        if(dist[vtx]<d) 
            continue;
        for(i=0;i<g[vtx].size();i++){
            cost = g[vtx][i].second + d;
            if(cost<dist[g[vtx][i].first]){
                dist[g[vtx][i].first] = cost;
                pq.push({cost,g[vtx][i].first});
            }
        }
    }
}
void update_product(){
    for(auto& iter : product){
        rev = iter.second.second.first;
        dst = iter.second.second.second;
        iter.second.first = rev-dist[dst];
    }
}
int main() {
    cin>>Q;
    init();
    while(Q--){
        cin>>cmd;
        if(cmd==100){
            cin>>n>>m;
            for(i=0;i<m;i++){
                cin>>v>>u>>w;
                g[u].push_back({v,w});
                g[v].push_back({u,w});
            }
            init_dist();
            dijkstra(0);
        }
        else if(cmd==200){
            cin>>id>>rev>>dst;
            product.insert({id,{rev-dist[dst],{rev,dst}}});
        }
        else if(cmd==300){
            cin>>id;
            product.erase(id);
        }
        else if(cmd==400){
            update_product();
            if(product.empty()){
                cout<<"-1\n";
                continue;
            }

            auto it = product.begin();
            int max_id = -1;
            int max_rev = -INF;
            for(auto& iter : product){
                if(max_rev<iter.second.first){
                    max_rev = iter.second.first;
                    max_id = iter.first;
                }
            }
            if(max_rev>=0){
                cout<<max_id<<"\n";
                product.erase(max_id);
            }
            else{
                cout<<"-1\n";
            }
        }
        else if(cmd==500){
            cin>>s;
            init_dist();
            dijkstra(s);
            update_product();
        }
    }
    return 0;
}