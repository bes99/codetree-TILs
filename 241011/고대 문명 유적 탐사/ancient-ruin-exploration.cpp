#include <iostream>
#include <algorithm>
#include <utility>
#include <tuple>
#include <queue>
#include <vector>
#define P pair<int,int>
using namespace std;
int K,M,ans;
int arr[6][6],cpy[6][6];
bool visited[6][6];
int dr[4] = {0,0,1,-1};
int dc[4] = {1,-1,0,0};
queue<int> piece;
vector<P> del;
bool compare1(pair<P,P> a, pair<P,P> b){
    if(a.first.first==b.first.first){
        if(a.first.second==b.first.second){
            if(a.second.first==b.second.first){
                return a.second.second<b.second.second;
            }
            else return a.second.first<b.second.first;
        }
        else return a.first.second<b.first.second;
    }
    else return a.first.first>b.first.first;
}
bool compare2(P a, P b){
    if(a.second==b.second){
        return a.first>b.first;
    }
    else return a.second<b.second;
}
void copy_arr(){
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            cpy[i][j] = arr[i][j];
        }
    }
}
void init(){
    for(int i=0;i<5;i++){
        fill(visited[i],visited[i]+5,false);
    }
}
int bfs(int row, int col, int val, int flag){
    int cnt=0;
    queue<P> q;
    q.push({row,col});
    visited[row][col] = true;
    while(!q.empty()){
        int r = q.front().first;
        int c = q.front().second;
        q.pop();
        if(flag==1)
            del.push_back({r,c});
        cnt++;
        for(int i=0;i<4;i++){
            int rr = r+dr[i];
            int cc = c+dc[i];
            if(rr<0 || rr>=5 || cc<0 || cc>=5) continue;
            if(!visited[rr][cc] && arr[rr][cc]==val){
                visited[rr][cc] = true;
                q.push({rr,cc});
            }
        }
    }
    return cnt;   
}
int count(int flag){
    init();
    int sum = 0;
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            if(!visited[i][j]){
                int cnt = bfs(i,j,arr[i][j],flag);
                if(cnt>=3) sum+=cnt;
                else if(flag==1 && cnt<3){
                    for(int z=0;z<cnt;z++){
                        del.pop_back();
                    }
                }
            }
        }
    }
    return sum;
}
void rotate(int row, int col){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            arr[row+j][col+3-i-1] = cpy[row+i][col+j];
        }
    }
}
void twice(int row, int col){
    for(int t=0;t<2;t++){
        copy_arr();
        rotate(row,col);
    }
}
void third(int row, int col){
    for(int t=0;t<3;t++){
        copy_arr();
        rotate(row,col);
    }
}
void pick_squre(){
    vector<pair<P,P>> t;
    int row,col,val,rot;
    int max_cnt = 0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            int tmp[6][6];

            for(int a=0;a<5;a++){
                for(int b=0;b<5;b++){
                    tmp[a][b] = arr[a][b];
                }
            }

            copy_arr();
            rotate(i,j);
            int a1 = count(0);
            for(int a=0;a<5;a++){
                for(int b=0;b<5;b++){
                    arr[a][b] = tmp[a][b];
                }
            }
            t.push_back({{a1,0},{i,j}});

            twice(i,j);
            int b = count(0);
            for(int a=0;a<5;a++){
                for(int b=0;b<5;b++){
                    arr[a][b] = tmp[a][b];
                }
            }
            t.push_back({{b,1},{i,j}});

            third(i,j);
            int c = count(0);
            for(int a=0;a<5;a++){
                for(int b=0;b<5;b++){
                    arr[a][b] = tmp[a][b];
                }
            }
            t.push_back({{c,2},{i,j}});
        }
    }

    sort(t.begin(),t.end(),compare1);
    tie(val,rot) = t[0].first;
    tie(row,col) = t[0].second;
    if(rot==0){
        copy_arr();
        rotate(row,col);
    }
    else if(rot==1){
        twice(row,col);
    }
    else if(rot==2){
        third(row,col);
    }
}
void create_piece(){
    sort(del.begin(),del.end(),compare2);

    for(int i=0;i<del.size();i++){
        int r = del[i].first;
        int c = del[i].second;
        if(piece.empty()) return; 
        int val = piece.front();
        piece.pop();
        arr[r][c] = val;
    }
    del.clear();
}
void simulate(){
    for(int i=0;i<K;i++){
        pick_squre();
        int sum=0;
        while(count(0)>0){
            sum+=count(1);
            create_piece();
        }
        if(sum==0) return;
        cout<<sum<<" ";
    }
}
int main() {
    int input;
    cin>>K>>M;
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            cin>>arr[i][j];
        }
    }
    for(int i=0;i<M;i++){
        cin>>input;
        piece.push(input);
    }

    // pick_squre();
    // for(int i=0;i<5;i++){
    //     for(int j=0;j<5;j++){
    //         cout<<arr[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }
    // pick_squre();
    // cout<<count(1)<<"\n";
    // create_piece();
    

    simulate();
    // rotate(0,0);
    // for(int i=0;i<5;i++){
    //     for(int j=0;j<5;j++){
    //         cout<<arr[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }
    return 0;
}