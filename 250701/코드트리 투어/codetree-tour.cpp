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
struct Product{
    int id;
    int rev;
    int dst;
    int cost;

    Product(int ID, int r, int d, int c){
        id = ID;
        rev = r;
        dst = d;
        cost = c;
    };
    
    bool operator<(const Product& b) const{
        if(cost!=b.cost) return cost>b.cost;
        return id<b.id;
    }
};
int n,m,u,v,w,Q,i,cmd,s;
int id, rev, dst;
map<int,Product> product;
multiset<Product> productSet;
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
    multiset<Product> newSet;
    for(auto& iter : product){
        iter.second.cost = iter.second.rev - dist[iter.second.dst];
        newSet.insert({iter.second.id,iter.second.rev,iter.second.dst,iter.second.cost});
    }
    productSet = newSet;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
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
            Product p = Product(id,rev,dst,rev-dist[dst]);
            product.insert({id,p});
            productSet.insert(p);
        }
        else if(cmd==300){
            cin>>id;
            auto it = product.find(id);
            if (it != product.end()) {
                productSet.erase(productSet.find(it->second));  
                product.erase(it);
            }
        }
        else if(cmd==400){
            if (productSet.empty()) {
                cout << "-1\n";
                continue;
            }
            
            Product best = *productSet.begin();
            if (best.cost < 0) {
                cout << "-1\n";
            } else {
                cout << best.id << "\n";
                productSet.erase(productSet.begin());
                product.erase(best.id);
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