#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
using namespace std;
int R,C,K,dir,ans;
int dr[4]={-1,0,1,0};
int dc[4]={0,1,0,-1};
//  행,열,출구 방향
vector<tuple<int,int,int>> vec;
bool visited[74][74];
bool checked[74][74];
int dp[74][74];
// 아래로 이동 가능한지 여부
bool is_down(int row, int col){
    int dy[3] = {1,2,1};
    int dx[3] = {-1,0,1};
    for(int d=0;d<3;d++){
        int r = row + dy[d];
        int c = col + dx[d];
        if(checked[r][c] || r<1 || r>R || c<1 || c>C){
            return false;
        }
    }
    return true;
}
// 중앙값 하단 이동
void down(int idx){
    get<0>(vec[idx])++;
}
bool is_left(int row, int col){
    int dy[5] = {-1,0,1,1,2};
    int dx[5] = {-1,-2,-1,-2,-1};
    for(int d=0;d<5;d++){
        int r = row + dy[d];
        int c = col + dx[d];
        if(checked[r][c]  || r<1 || r>R || c<1 || c>C){
            return false;
        }
    }
    return true;
}
void left(int idx){
    get<0>(vec[idx])++;
    get<1>(vec[idx])--;
}
bool is_right(int row, int col){
    int dy[5] = {-1,0,1,1,2};
    int dx[5] = {1,2,1,2,1};
    for(int d=0;d<5;d++){
        int r = row + dy[d];
        int c = col + dx[d];
        if(checked[r][c]  || r<1 || r>R || c<1 || c>C){
            return false;
        }
    }
    return true;
}
void right(int idx){
    get<0>(vec[idx])++;
    get<1>(vec[idx])++;
}
void lacate(int idx, int max_row){
    int r = get<0>(vec[idx]);
    int c = get<1>(vec[idx]);
    for(int i=0;i<4;i++){
        int rr = r+dr[i];
        int cc = c+dc[i];
        dp[rr][cc] = max_row;
        checked[rr][cc] = true;
    }
}
void clear_map(){
    for(int i=1;i<=R;i++){
        for(int j=1;j<=C;j++){
            dp[i][j] = 0;
            checked[i][j] = false;
        }
    }
}
int bfs(int row, int col, int mr){
    int max_row = mr;
    for(int i=0;i<4;i++){
        int r = row+dr[i];
        int c = col+dc[i];
        if(dp[r][c]>0){
            max_row = max(max_row, dp[r][c]);
        }
    }
    return max_row;
}

void simulate(){
    for(int i=0;i<vec.size();i++){
        bool flag = false;
        while(1){
            if(get<0>(vec[i])==R-1) break;
            if(is_down(get<0>(vec[i]),get<1>(vec[i]))){
                down(i);
            }
            else if(is_left(get<0>(vec[i]),get<1>(vec[i]))){
                left(i);
                get<2>(vec[i])--;
                if(get<2>(vec[i])==-1) get<2>(vec[i]) = 3;
            }
            else if(is_right(get<0>(vec[i]),get<1>(vec[i]))){
                right(i);
                get<2>(vec[i])++;
                if(get<2>(vec[i])==4) get<2>(vec[i]) = 0;
            }
            else break;
        }
        if(get<0>(vec[i])<4) {
            clear_map();
            continue;
        }
        int d = get<2>(vec[i]);
        int max_row = bfs(get<0>(vec[i])+dr[d], get<1>(vec[i])+dc[d], get<0>(vec[i])-2);
        lacate(i,max_row);
        dp[get<0>(vec[i])][get<1>(vec[i])] = max_row;

        ans += max_row;
    }
}
int main() {
    int a,b;
    cin>>R>>C>>K;
    R+=3;
    for(int i=0;i<K;i++){
        cin>>a>>b;
        vec.push_back({1,a,b});
    }
    simulate();
    // for(int i=1;i<=R;i++){
    //     for(int j=1;j<=C;j++){
    //         cout<<dp[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }
    // for(auto v:vec){
    //     int r = get<0>(v);
    //     int c = get<1>(v);
    //     int d = get<2>(v);
    //     cout<<r<<" "<<c<<" "<<d<<"\n";
    // }
    cout<<ans;
    return 0;
}