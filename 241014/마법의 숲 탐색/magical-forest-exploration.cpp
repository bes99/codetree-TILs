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
bool visited[73][73];
bool checked[73][73];
int dp[73][73];
// 아래로 이동 가능한지 여부
bool is_down(int row, int col){
    int dy[3] = {1,2,1};
    int dx[3] = {-1,0,1};
    for(int d=0;d<3;d++){
        int r = row + dy[d];
        int c = col + dx[d];
        if(checked[r][c] || r<0 || r>=R || c<0 || c>=C){
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
        if(checked[r][c]  || r<0 || r>=R || c<0 || c>=C){
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
        if(checked[r][c]  || r<0 || r>=R || c<0 || c>=C){
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
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            dp[i][j] = 0;
            checked[i][j] = false;
        }
    }
}
int bfs(int row, int col, int mr){
    int max_row = mr;
    bool flag = false;
    for(int i=0;i<4;i++){
        int r = row+dr[i];
        int c = col+dc[i];
        if(checked[r][c]){
            flag =true;
            max_row = max(max_row, dp[r][c]);
        }
    }
    if(flag) return max_row;

    // for(int i=0;i<R;i++){
    //     fill(visited[i],visited[i]+C,false);
    // }
    // queue<pair<int,int>> q;
    // q.push({row,col});
    // visited[row][col] = true;
    // checked[row][col] = true;
    // while(!q.empty()){
    //     int r = q.front().first;
    //     int c = q.front().second;
    //     q.pop();
    //     max_row = max(max_row,r);
    //     for(int i=0;i<4;i++){
    //         int rr = r+dr[i];
    //         int cc = c+dc[i];
    //         if(!visited[rr][cc] && !checked[rr][cc]){
    //             q.push({rr,cc});
    //             visited[rr][cc] = true;
    //             checked[rr][cc] = true;
    //         }
    //     }
    // }
    // return max_row;
}

void simulate(){
    for(int i=0;i<vec.size();i++){
        bool flag = false;
        while(1){
            if(get<0>(vec[i])==R-2) break;
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
        if(get<0>(vec[i])<3) {
            clear_map();
            continue;
        }
        int d = get<2>(vec[i]);
        int max_row = bfs(get<0>(vec[i])+dr[d], get<1>(vec[i])+dc[d], get<0>(vec[i]));
        lacate(i,max_row);
        dp[get<0>(vec[i])][get<1>(vec[i])] = max_row;

        ans += max_row;
    }
}
int main() {
    int a,b;
    cin>>R>>C>>K;
    R+=2;
    for(int i=0;i<K;i++){
        cin>>a>>b;
        a--;
        vec.push_back({0,a,b});
    }
    simulate();
    // for(auto v:vec){
    //     int r = get<0>(v);
    //     int c = get<1>(v);
    //     int d = get<2>(v);
    //     cout<<r<<" "<<c<<" "<<d<<"\n";
    // }
    cout<<ans;
    return 0;
}