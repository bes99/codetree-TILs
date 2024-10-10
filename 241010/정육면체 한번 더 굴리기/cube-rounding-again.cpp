#include <iostream>
#include <queue>
#include <utility>
#include <tuple>
using namespace std;

int arr[21][21];
// 우,하,좌,상
int dr[4] = {0,1,0,-1};
int dc[4] = {1,0,-1,0};
int dv=6;
int row=0,col=0;
int u=1,f=2,r=3;
int n,m,d,ans;
bool visited[21][21];
int bfs(int dy, int dx){
    int cnt=1;
    queue<pair<int,int>> q;
    q.push({dy,dx});
    visited[dy][dx] = true;
    while(!q.empty()){
        int r = q.front().first;
        int c = q.front().second;
        q.pop();
        for(int i=0;i<4;i++){
            int rr = r+dr[i];
            int cc = c+dc[i];
            if(rr<0 || rr>=n || cc<0 || cc>=n) continue;
            if(!visited[rr][cc] && arr[rr][cc]==arr[dy][dx]){
                visited[rr][cc] = true;
                q.push({rr,cc});
                cnt++;
            }
        }
    }
    for(int i=0;i<n;i++){
        fill(visited[i],visited[i]+n,false);
    }
    return cnt*arr[dy][dx];
}
void simulate(){
    for(int i=0;i<m;i++){
        int r = row + dr[d];
        int c = col + dc[d];
        // 격자 밖으로 나갔을 때 반대로 나가는 로직
        if(r<0){
            r=1;
            d=1;
        }
        else if(r>=n){
            r = n-2;
            d=3;
        }
        else if(c<0){
            c = 1;
            d=0;
        }
        else if(c>=n){
            c = n-2;
            d=2;
        }

        row = r;
        col = c;
        ans += bfs(row,col);
        
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

        if(down>arr[row][col]){
            d++;
            if(d==4) d=0;
        }
        else if(down<arr[row][col]){
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