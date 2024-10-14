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
bool checked[72][72];
bool visited[72][72];
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
        if(checked[r][c] || r<0 || r>=R || c<0 || c>=C){
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
        if(checked[r][c] || r<0 || r>=R || c<0 || c>=C){
            return false;
        }
    }
    return true;
}
void right(int idx){
    get<0>(vec[idx])++;
    get<1>(vec[idx])++;
}
void lacate(int idx){
    int r = get<0>(vec[idx]);
    int c = get<1>(vec[idx]);
    for(int i=0;i<4;i++){
        int rr = r+dr[i];
        int cc = c+dc[i];
        checked[rr][cc] = true;
    }
}
void clear_map(){
    for(int i=0;i<R+2;i++){
        for(int j=0;j<C+2;j++){
            checked[i][j] = false;
        }
    }
}
int bfs(int row, int col){
    for(int i=0;i<R;i++){
        fill(visited[i],visited[i]+C,false);
    }
    int max_row = 0;
    queue<pair<int,int>> q;
    q.push({row,col});
    visited[row][col] = true;
    while(!q.empty()){
        int r = q.front().first;
        int c = q.front().second;
        q.pop();
        max_row = max(max_row,r);
        for(int i=0;i<4;i++){
            int rr = r+dr[i];
            int cc = c+dc[i];
            if(!visited[rr][cc] && checked[rr][cc]){
                q.push({rr,cc});
                visited[rr][cc] = true;
            }
        }
    }
    return max_row;
}

void simulate(){
    for(int i=0;i<6;i++){
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
        if(get<0>(vec[i])<2) {
            clear_map();
            continue;
        }
        lacate(i);
        // 그래프 탐색 로직 추가
        int d = get<2>(vec[i]);
        int max_row = max(get<0>(vec[i]), bfs(get<0>(vec[i])+dr[d], get<1>(vec[i])+dc[d]));
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