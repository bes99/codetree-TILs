#include <iostream>
#include <queue>
#include <tuple>
#include <utility>
using namespace std;

int arr[21][21];
// 우,하,좌,상
int dr[4] = {0,1,0,-1};
int dc[4] = {1,0,-1,0};
int y=0,x=0;
int u=1,f=2,r=3;
int n,m,d,ans;
bool visited[21][21];
int bfs(int dy, int dx){
    int sum=0;
    queue<pair<int,int>> q;
    q.push({dy,dx});
    visited[dy][dx] = true;
    while(!q.empty()){
        int row = q.front().first;
        int col = q.front().second;
        sum += arr[row][col];
        q.pop();
        for(int i=0;i<4;i++){
            int rr = row+dr[i];
            int cc = col+dc[i];
            if(rr<0 || rr>=n || cc<0 || cc>=n) continue;
            if(!visited[rr][cc] && arr[rr][cc]==arr[dy][dx]){
                visited[rr][cc] = true;
                q.push({rr,cc});
            }
        }
    }
    for(int i=0;i<n;i++){
        fill(visited[i],visited[i]+n,false);
    }
    return sum;
}
void simulate(){
    for(int i=0;i<m;i++){
        int rr = y + dr[d];
        int cc = x + dc[d];
        // 격자 밖으로 나갔을 때 반대로 나가는 로직
        if(rr<0 || rr>=n || cc<0 || cc>=n){
            d = d<2 ? d+2 : d-2;
            rr = y+dr[d];
            cc = x+dc[d];
        }

        y = rr;
        x = cc;
        ans += bfs(y,x);
        if(d==0){
            tie(u,f,r) = make_tuple(7-r,f,u);  
        }
        else if(d==1){
            tie(u,f,r) = make_tuple(7-f,u,r);
        }
        else if(d==2){
            tie(u,f,r) = make_tuple(r,f,7-u);
        }
        else if(d==3){
            tie(u,f,r) = make_tuple(f,7-u,r);
        }
        int down = 7-u; 
        // cout<<y<<" "<<x<<" "<<d<<" "<<down<<"\n";
        if(down>arr[y][x]){
            d++;
            if(d==4) d=0;
        }
        else if(down<arr[y][x]){
            d--;
            if(d<0) d=3; 
        }
    }
}
int main() {
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>arr[i][j];
        }
    }
    simulate();
    cout<<ans;
    return 0;
}