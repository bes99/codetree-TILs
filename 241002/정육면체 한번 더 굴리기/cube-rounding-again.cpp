#include <iostream>
#include <queue>
using namespace std;

int arr[21][21];
// 우,하,좌,상
int dr[4] = {0,1,0,-1};
int dc[4] = {1,0,-1,0};
int dv=6;
int row=0,col=0;
int dice[7][4] = {
    {0,0,0,0},
    {3,5,4,2},
    {3,4,6,5},
    {1,2,4,5},
    {6,2,1,5},
    {3,6,4,1},
    {3,2,4,5}
};
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
    row += dr[d];
    col += dc[d];
    dv = dice[dv][d];
    ans += bfs(row,col);
    
    for(int i=1;i<m;i++){
        if(dv>arr[row][col]){
            d++;
            if(d==4) d=0;
        }
        else if(dv<arr[row][col]){
            d--;
            if(d<0) d=3; 
        }

        row += dr[d];
        col += dc[d];
        // 격자 밖으로 나갔을 때 반대로 나가는 로직
        if(row<0){
            row=1;
            d=1;
        }
        else if(row>=n){
            row = n-2;
            d=3;
        }
        if(col<0){
            col = 1;
            d=0;
        }
        else if(col>=n){
            col = n-2;
            d=2;
        }
        dv = dice[dv][d];
        
        ans += bfs(row,col);
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