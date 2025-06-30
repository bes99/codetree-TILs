#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#define INF 2000000000
#define P pair<int,int>
using namespace std;

struct Product {
    int id;
    int rev;
    int dst;
    int score; // rev - dist[dst]

    bool operator<(const Product& other) const {
        if (score != other.score) return score > other.score; // 내림차순
        return id < other.id;
    }
};

int n, m, u, v, w, Q, i, cmd, s;
int id, rev, dst;
map<int, Product> productMap;
multiset<Product> productSet;
vector<P> g[2001];
int dist[2001];

void init() {
    for (i = 0; i < 2001; i++)
        g[i].clear();
    productMap.clear();
    productSet.clear();
}

void init_dist() {
    fill(dist, dist + 2001, INF);
}

void dijkstra(int start) {
    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push({0, start});
    dist[start] = 0;
    while (!pq.empty()) {
        int d = pq.top().first;
        int vtx = pq.top().second;
        pq.pop();
        if (dist[vtx] < d) continue;
        for (i = 0; i < g[vtx].size(); i++) {
            int cost = d + g[vtx][i].second;
            if (cost < dist[g[vtx][i].first]) {
                dist[g[vtx][i].first] = cost;
                pq.push({cost, g[vtx][i].first});
            }
        }
    }
}

void update_product() {
    multiset<Product> newSet;
    for (auto& kv : productMap) {
        Product& p = kv.second;

        // 이전 항목 제거 후 새로 계산해서 삽입
        p.score = p.rev - dist[p.dst];
        newSet.insert(p);
    }
    productSet = std::move(newSet);  // 기존 productSet 덮어씀
}

int main() {
    cin >> Q;
    init();
    while (Q--) {
        cin >> cmd;
        if (cmd == 100) {
            cin >> n >> m;
            for (i = 0; i < m; i++) {
                cin >> v >> u >> w;
                g[u].push_back({v, w});
                g[v].push_back({u, w});
            }
            init_dist();
            dijkstra(0);
        }
        else if (cmd == 200) {
            cin >> id >> rev >> dst;
            Product p = {id, rev, dst, rev - dist[dst]};
            productMap[id] = p;
            productSet.insert(p);
        }
        else if (cmd == 300) {
            cin >> id;
            auto it = productMap.find(id);
            if (it != productMap.end()) {
                productSet.erase(productSet.find(it->second));  // 정확히 해당 객체 제거
                productMap.erase(it);
            }
        }
        else if (cmd == 400) {
            if (productSet.empty()) {
                cout << "-1\n";
                continue;
            }
            const Product& best = *productSet.begin();
            if (best.score < 0) {
                cout << "-1\n";
            } else {
                cout << best.id << "\n";
                productSet.erase(productSet.begin());
                productMap.erase(best.id);
            }
        }
        else if (cmd == 500) {
            cin >> s;
            init_dist();
            dijkstra(s);
            update_product();  // 전체 product score 갱신
        }
    }
    return 0;
}
