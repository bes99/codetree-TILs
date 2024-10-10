#include <iostream>
#include <queue>
#include <utility>
#include <tuple>
using namespace std;

int arr[21][21];
// 우,하,좌,상
int dr[4] = {0,1,0,-1};
int dc[4] = {1,0,-1,0};
int row=0,col=0;
int u=1,f=2,r=3;
int n,m,d,ans;
bool visited[21][21];
int bfs(int dy, int dx){
    int sum=0;
    queue<pair<int,int>> q;
    q.push({dy,dx});
    visited[dy][dx] = true;
    while(!q.empty()){
        int r = q.front().first;
        int c = q.front().second;
        sum += arr[r][c];
        q.pop();
        for(int i=0;i<4;i++){
            int rr = r+dr[i];
            int cc = c+dc[i];
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
        int rr = row + dr[d];
        int cc = col + dc[d];
        // 격자 밖으로 나갔을 때 반대로 나가는 로직
        if(rr<0 || rr>=n || cc<0 || cc>=n){
            d = d<2 ? d+2 : d-2;
            rr += dr[d];
            cc += dc[d];
        }

        row = rr;
        col = cc;
        ans += bfs(row,col);
        //cout <<row<<" "<<col<<"\n";
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