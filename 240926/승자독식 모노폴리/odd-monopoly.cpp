#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <queue>
using namespace std;
int n,m,k;
pair<int,int> arr[21][21], cpy[21][21];
int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};
vector<pair<pair<int,int>, pair<int,int>>> vec;
vector<pair<int,pair<int,int>>> order;
queue<int> q;
// board 정보 pair(사람 idx, 남은 턴) ok
// 사람 벡터 (사람 idx, 사람 dir, row, col) ok
// 사람, 방향별 우선순위 저장 벡터 (사람 idx, (방향,우선순위))
// 이동 시 우선순위에 따른 이동 방향 반환 로직 함수.
// 여러 개 이동 가능할 때 우선순위 높은 것만 적용하여 이동.
// 사람이 겹치는 경우는 빈 칸에 동시에 들어가는 경우만 있음. 이때 사람 인덱스가 작은 것 외 삭제시킨다.

// 사람번호, 현재방향 줬을 때 우선순위 반환
int find_pre(int idx, int dir, int lev){
    for(int i=0;i<order.size();i++){
        int f = order[i].first;
        int d = order[i].second.first;
        if(f==idx && d==dir){
            return order[i+lev].second.second;
        }
    }
}

// 이동 칸에 사람 있는지 체크
bool is_person(int row, int col){
    for(int i=0;i<vec.size();i++){
        int idx = vec[i].first.first;
        int r = vec[i].second.first;
        int c = vec[i].second.second;
        if(row==r && col==c){
            return true;
        }
    }
    return false;
}

// 현재 칸의 좌표를 줬을 때 이동 가능한지 판단해서 이동. 
void move(int idx, int d, int row, int col){
    for(int i=0;i<4;i++){
        int dir = find_pre(idx,d,i);
        int r = row+dr[dir];
        int c = col+dc[dir];
        if(r<0 || r>=n || c<0 || c>=n) continue;
        if(cpy[r][c].second==0){
            // 업데이트 로직
            int tmp = arr[r][c].first;
            if(is_person(r,c)){
                int max_idx = max(tmp, idx);
                arr[r][c].first = min(tmp,idx);
                q.push(max_idx);
            }
            else{
                arr[r][c].first = idx;
            }
            arr[r][c].second = k;
            vec[idx].second.first=r;
            vec[idx].second.second=c;
            return;
        }
    }

    for(int i=0;i<4;i++){
        int dir = find_pre(idx,d,i);
        int r = row+dr[dir];
        int c = col+dc[dir];
        if(r<0 || r>=n || c<0 || c>=n) continue;
        if(cpy[r][c].first==idx){
            // 업데이트 로직
            arr[r][c].second = k;
            vec[idx].second.first=r;
            vec[idx].second.second=c;
            return;
        }
    }

}
void copy(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cpy[i][j].first = arr[i][j].first;
            cpy[i][j].second = arr[i][j].second;
        }
    }
}

void minus_turn(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(arr[i][j].second>0){
                arr[i][j].second--;
                if(arr[i][j].second==0){
                    arr[i][j].first = 500;
                }
            }
        }
    }
}
void delete_person(){
    while(!q.empty()){
        int del = q.front();
        for(int i=0;i<vec.size();i++){
            int idx = vec[i].first.first;
            if(idx==del){
                vec.erase(vec.begin()+i);
            }
        }
        q.pop();
    }
}
int simulate(){
    for(int t=1;t<1000;t++){
        copy();
        for(int i=0;i<vec.size();i++){
            int idx = vec[i].first.first;
            int d = vec[i].first.second;
            int r = vec[i].second.first;
            int c = vec[i].second.second;
            move(idx,d,r,c);
        }
        // 각 칸에서 남은 턴 줄이는 로직
        minus_turn();
        // vec에서 사람 삭제 로직
        delete_person();

        if(vec.size()==1){
            return t;
        }
    }
    return -1;
}
int main() {
    int val;
    cin>>n>>m>>k;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>val;
            if(val==0){
                arr[i][j].first = 500;
                arr[i][j].second=0;        
            }
            else{
                vec.push_back({{val,-1},{i,j}});
                arr[i][j].first = val;
                arr[i][j].second = k;
            }
        }
    }
    sort(vec.begin(),vec.end());
    for(int i=0;i<vec.size();i++){
        cin>>vec[i].first.second;
        vec[i].first.second--;
    }


    for(int i=0;i<m*4;i++){
        for(int j=0;j<4;j++){
            cin>>val;
            order.push_back({i/4+1,{i%4,val-1}});   
        }
    }

    // move(1,3,1,0);
    // move(4,2,0,4);
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++){
    //         cout<<arr[i][j].first<<" ";
    //     }
    //     cout<<"\n";
    // }
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++){
    //         cout<<arr[i][j].second<<" ";
    //     }
    //     cout<<"\n";
    // }
    cout<<simulate();
    // for(int i=0;i<order.size();i++){
    //     int idx = order[i].first;
    //     int dir = order[i].second.first;
    //     int pre = order[i].second.second;
    //     cout<<idx<<" "<<dir<<" "<<pre<<"\n";
    // }
    return 0;
}