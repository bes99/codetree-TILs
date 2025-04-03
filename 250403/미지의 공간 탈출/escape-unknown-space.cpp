#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

#define PII pair<int,int>
using namespace std;

int N,M,F,cnt,sr,sc;
// 큐브 탈출 좌표
int gr,gc;
// 탈출 좌표
int goal_idx, connect_dim, connect_dir;
int board[21][21];
int time_wall[5][19][19];
vector<pair<int,PII>> idx_vec;

int dr[4] = {-1,0,1,0};
int dc[4] = {0,1,0,-1};

vector<pair<PII,PII>> abnormal;
vector<int> abnormal_v;
bool checked[21][21];
vector<vector<int>> g;
void input(){
    cin>>N>>M>>F;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin>>board[i][j];
            if(board[i][j]==0){
                idx_vec.push_back({5,{i,j}});
                cnt++;
            }
            else if(board[i][j]==4){
                idx_vec.push_back({5,{i,j}});
                goal_idx = cnt;
                cnt++;
            }
        }
    }

    for(int i=0;i<M;i++){
        for(int j=0;j<M;j++){
            cin>>time_wall[1][i][j];
            if(time_wall[1][i][j]==0){
                idx_vec.push_back({1,{i,j}});
                cnt++;
            }
        }
    }
    for(int i=0;i<M;i++){
        for(int j=0;j<M;j++){
            cin>>time_wall[3][i][j];
            if(time_wall[3][i][j]==0){
                idx_vec.push_back({3,{i,j}});
                cnt++;
            }
        }
    }
    for(int i=0;i<M;i++){
        for(int j=0;j<M;j++){
            cin>>time_wall[2][i][j];
            if(time_wall[2][i][j]==0){
                idx_vec.push_back({2,{i,j}});
                cnt++;
            }
        }
    }
    for(int i=0;i<M;i++){
        for(int j=0;j<M;j++){
            cin>>time_wall[0][i][j];
            if(time_wall[0][i][j]==0){
                idx_vec.push_back({0,{i,j}});
                cnt++;
            }
        }
    }
    for(int i=0;i<M;i++){
        for(int j=0;j<M;j++){
            cin>>time_wall[4][i][j];
            if(time_wall[4][i][j]==0){
                idx_vec.push_back({4,{i,j}});
                cnt++;
            }
            else if(time_wall[4][i][j]==2){
                idx_vec.push_back({4,{i,j}});
                cnt++;
                sr=i;
                sc=j;
            }
        }
    }

    int r,c,d,v;
    for(int i=0;i<F;i++){
        cin>>r>>c>>d>>v;
        abnormal.push_back({{r,c},{d,v}});
        abnormal_v.push_back(v);
        checked[r][c] = true;
    }
}
pair<PII, PII> find_escape_rc(){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(board[i][j]==0){
                if(board[i+1][j]==3){
                    return {{0,2},{i,j}};
                }
                else if(board[i][j-1]==3){
                    return {{1,3},{i,j}};
                }
                else if(board[i-1][j]==3){
                    return {{2,0},{i,j}};
                }
                else if(board[i][j+1]==3){
                    return {{3,1},{i,j}};
                }
            }
        }
    }

}
int find_idx_by_rc(int dim, int r, int c){
    for(int i=0;i<idx_vec.size();i++){
        int d = idx_vec[i].first;
        int rr = idx_vec[i].second.first;
        int cc = idx_vec[i].second.second;
        if(d==dim && r==rr && c ==cc){
            return i;
        }
    }
    cout<<dim<<" "<<r<<" "<<c;
    exit(0);
}
void init(){
    g.assign(cnt+1,vector<int>(4,-1));
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(board[i][j]==0){
                int idx = find_idx_by_rc(5,i,j);
                for(int d=0;d<4;d++){
                    int r = i+dr[d];
                    int c = j+dc[d];
                    if(r<0 || r>=N || c<0 || c>=N) 
                        continue;
                    if(board[r][c]==0 || board[r][c]==4){
                        g[idx][d] = find_idx_by_rc(5,r,c);
                    }
                }
            }
        }
    }

    for(int d=0;d<4;d++){
        for(int i=0;i<M;i++){
            for(int j=0;j<M;j++){
                if(time_wall[d][i][j]==0){
                    int idx = find_idx_by_rc(d,i,j);
                    for(int dir=0;dir<4;dir++){
                        int dim = d;
                        int r = i+dr[dir];
                        int c = j+dc[dir];
                        if(r<0 && d==0){
                            r = 0;
                            c = M-c-1;
                        }
                        else if(r<0 && d==1){
                            r = M-c-1;
                            c = M-1;
                        }
                        else if(r<0 && d==2){
                            r = M-1;
                        }
                        else if(r<0 && d==3){
                            r = c;
                            c=0;
                        }
                        else if(r>=M){
                            continue;
                        }
                        else if(c<0){
                            dim = (dim+1)%4;
                            c = M-1;
                        }
                        else if(c>=M){
                            dim -= 1;
                            if(dim==-1) dim=3;
                            c=0;
                        }
                        if(time_wall[dim][r][c]==0){
                            g[idx][dir] = find_idx_by_rc(dim,r,c);
                        }
                    }
                }
            }
        }
    }

    for(int i=0;i<M;i++){
        for(int j=0;j<M;j++){
            if(time_wall[4][i][j]==0 || time_wall[4][i][j]==2){
                int idx = find_idx_by_rc(4,i,j);
                for(int d=0;d<4;d++){
                    int dim = 4;
                    int r = i+dr[d];
                    int c = j+dc[d];
                    if(r<0){
                        dim = 0;
                        r = 0;
                        c = M-c-1;
                    }
                    else if(r>=M){
                        dim = 2;
                        r = 0;
                    }
                    else if(c<0){
                        dim = 3;
                        c = r;
                        r = 0;
                    }
                    else if(c>=M){
                        dim = 1;
                        c = M-r-1;
                        r=0;
                    }
                    if(time_wall[dim][r][c]==0){
                        g[idx][d] = find_idx_by_rc(dim,r,c);
                    }
                }
            }
        }
    }
    
    pair<PII,PII> escape_rc = find_escape_rc();
    connect_dim = escape_rc.first.first;
    connect_dir  = escape_rc.first.second;
    gr = escape_rc.second.first;
    gc = escape_rc.second.second;
    int board_idx= find_idx_by_rc(5,gr,gc);
    
    int count=M-1;
    int cube_r = M-1;
    int cube_c;
    if(connect_dim==0){
        int tr = gr+1;
        int tc = gc;
        while(board[tr][tc+1]==3){
            tc++;
            count--;
        }
        cube_c = count;
    }
    else if(connect_dim==1){
        int tr = gr;
        int tc = gc-1;
        while(board[tr-1][tc]==3){
            tr--;
            count--;
        }
        cube_c = count;
    }
    else if(connect_dim==2){
        int tr = gr-1;
        int tc = gc;
        while(board[tr][tc+1]==3){
            tc++;
            count--;
        }
        cube_c = count;
    }
    else if(connect_dim==3){
        int tr = gr;
        int tc = gc+1;
        while(board[tr+1][tc]==3){
            tr++;
            count--;
        }
        cube_c = count;
    }
    int cube_idx = find_idx_by_rc(connect_dim,cube_r,cube_c);
    g[board_idx][connect_dir] = cube_idx;

    g[cube_idx][(connect_dir+2)%4] = board_idx;
}
void disconnect(int row, int col){
    for(int i=0;i<4;i++){
        int r = row+dr[i];
        int c = col+dc[i];
        if(r<0||r>=N || c<0 || c>=N || board[r][c]!=0) continue;
        int prev_idx=find_idx_by_rc(5,r,c);
        g[prev_idx][(i+2)%4]=-1;
    }
}
void abnormal_spread(){
    queue<pair<PII,PII>> tmp;
    for(int i=0;i<abnormal.size();i++){
        int r = abnormal[i].first.first;
        int c = abnormal[i].first.second;
        int d = abnormal[i].second.first;
        abnormal[i].second.second--;
        if(abnormal[i].second.second==0){
            abnormal[i].second.second = abnormal_v[i];
            if(d==0 && !checked[r][c+1] && board[r][c+1]==0){
                checked[r][c+1] = true;
                tmp.push({{r,c+1},{d,abnormal_v[i]}});
                disconnect(r,c+1);
            }
            else if(d==1 && !checked[r][c-1] && board[r][c-1]==0){
                checked[r][c-1] = true;
                tmp.push({{r,c-1},{d,abnormal_v[i]}});
                disconnect(r,c-1);
            }
            else if(d==2 && !checked[r+1][c] && board[r+1][c]==0){
                checked[r+1][c] = true;
                tmp.push({{r+1,c},{d,abnormal_v[i]}});
                disconnect(r+1,c);
            }
            else if(d==3 && !checked[r-1][c] && board[r-1][c]==0){
                checked[r-1][c] =true;
                tmp.push({{r-1,c},{d,abnormal_v[i]}});
                disconnect(r-1,c);
            }
        }
    }
    while(!tmp.empty()){
        int r = tmp.front().first.first;
        int c = tmp.front().first.second;
        int d = tmp.front().second.first;
        int v = tmp.front().second.second;
        tmp.pop();
        abnormal.push_back({{r,c},{d,v}});
        abnormal_v.push_back(v);
    }
}
int bfs(){
    for(int i=0;i<abnormal.size();i++){
        int r = abnormal[i].first.first;
        int c = abnormal[i].first.second;
        disconnect(r,c);
    }
    queue<PII> q;
    int idx = find_idx_by_rc(4,sr,sc);
    q.push({0,idx});
    vector<bool> visited(cnt+1, false);
    while(!q.empty()){
        int sec = q.front().first;
        int curr = q.front().second;
        q.pop();
        if(curr==goal_idx){
            return sec;
        }
        abnormal_spread();
        for(int i=0;i<4;i++){
            int next = g[curr][i];
            if(g[curr][i]!=-1 && !visited[next]){
                q.push({sec+1,next});
                visited[next] = true;
            }
        }
    }
    return -1;
}
void simulate(){
    init();
    cout<< bfs();
}
int main() {
    input();
    simulate();
    return 0;
}