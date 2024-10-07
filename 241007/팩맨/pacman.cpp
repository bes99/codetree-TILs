#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <tuple>
#include <queue>
#include <map>
using namespace std;
// 몬스터,알, 시체, 턴
pair<pair<int,int>,pair<int,int>> arr[5][5],cpy[5][5];
int m,t,max_sum;
pair<int,int> pacman;
// r,c,d,state
// state 0:시체, 1:active, 2: egg
int dy[8] = {-1,-1,0,1,1,1,0,-1};
int dx[8] = {0,-1,-1,-1,0,1,1,1};
int dr[4] = {-1,0,1,0};
int dc[4] = {0,-1,0,1};
vector<int> dir,last;
map<tuple<int,int,int>,int> mons,cmons;
queue<pair<pair<int,int>, pair<int,int>>> q;
void copy(){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            cpy[i][j].first.first = arr[i][j].first.first;
            cpy[i][j].first.second = arr[i][j].first.second;
            cpy[i][j].second.first = arr[i][j].second.first;
            cpy[i][j].second.second = arr[i][j].second.second;
        }
    }
}
void mv(int row, int col){
    int r = row, c = col;
    int max_sum=-1;
    dir.clear();
    for(int i=0;i<4;i++){
        int r2 = r+dr[i];
        int c2 = c+dc[i];
        if(r2<0 || r2>=4 || c2<0 || c2>=4) continue;
        int s1 = arr[r2][c2].first.first;
        arr[r2][c2].first.first = 0;
        dir.push_back(i);
        
        for(int j=0;j<4;j++){
            int r3 = r2+dr[j];
            int c3 = c2+dc[j];
            if(r3<0 || r3>=4 || c3<0 || c3>=4) continue;
            int s2 = s1 + arr[r3][c3].first.first;
            int t2 = arr[r3][c3].first.first;
            arr[r3][c3].first.first = 0;
            dir.push_back(j);

            for(int z=0;z<4;z++){
                int r4 = r3+dr[z];
                int c4 = c3+dc[z];
                if(r4<0 || r4>=4 || c4<0 || c4>=4) continue;
                int s3 = s2+arr[r4][c4].first.first;
                int t3 = arr[r4][c4].first.first;
                arr[r4][c4].first.first = 0;
                dir.push_back(z);

                if(s3>max_sum){
                    max_sum = s3;
                    if(!last.empty()) last.clear();
                    for(int k=0;k<dir.size();k++){
                        last.push_back(dir[k]);
                    }
                }
                dir.pop_back();
                arr[r4][c4].first.first = t3;
            }
            dir.pop_back();
            arr[r3][c3].first.first = t2;
        }
        dir.pop_back();
        arr[r2][c2].first.first = s1;
    }
}
// 펙맨 이동과 시체 업데이트
void update_died(){
    //cout<<last.size()<<"\n";
    for(int i=0;i<last.size();i++){
        pacman.first+=dr[last[i]];
        pacman.second+=dc[last[i]];

        int r = pacman.first;
        int c = pacman.second;
        //cout<<r<<" "<<c<<"\n";
        for(int j=0;j<8;j++){
            mons[{r,c,j}]=0;
        }
        if(arr[r][c].first.first>0){
            arr[r][c].second.first += arr[r][c].first.first;
            arr[r][c].first.first = 0;
            arr[r][c].second.second = 3;
        }
    }

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(arr[i][j].second.second>0){
                arr[i][j].second.second--;
                if(arr[i][j].second.second==0){
                    arr[i][j].second.first=0;
                }
            }
        }
    }
}
void egg(){
    while(!q.empty()){
        int r = q.front().first.first;
        int c = q.front().first.second;
        int dir = q.front().second.first;
        int cnt = q.front().second.second;
        //cout<<r<<" "<<c<<" "<<dir<<" "<<cnt<<"\n";
        q.pop();
        mons[{r,c,dir}]+=cnt;
        arr[r][c].first.first+=cnt;
    }
}
void move_mons(int r, int c){
    for(int d=0;d<8;d++){
        if(cmons[{r,c,d}]>0){
            int td = d;
            int tmp = cmons[{r,c,d}];
            q.push({{r,c},{d,tmp}});
            //cout<<r<<" "<<c<<" "<<d<<" "<<tmp<<"\n";
            int cnt=8;
            while(cnt--){
                int rr = r+dy[td];
                int cc = c+dx[td];
                if(rr<0 || rr>=4 || cc<0 || cc>=4 || (rr == pacman.first && cc==pacman.second) || cpy[rr][cc].second.first>0){
                    td+=1;
                    if(td==8) td = 0;
                }
                else{
                    mons[{r,c,d}] = 0;
                    arr[r][c].first.first-=tmp;
                    mons[{rr,cc,td}] += tmp;
                    arr[rr][cc].first.first += tmp;
                    break;
                }
            }
        }
    }
}
void simulate(){
    for(int i=0;i<t;i++){
        copy();
        cmons = mons;
        for(int r=0;r<4;r++){
            for(int c=0;c<4;c++){
                if(cpy[r][c].first.first>0){
                    move_mons(r,c);
                }
            }
        }
        // 팩맨 이동
        //cout<<pacman.first<<" "<<pacman.second<<"\n";
        mv(pacman.first,pacman.second);
        update_died();
        last.clear();
        egg();
    }
}
int print_ans(){
    int sum = 0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(arr[i][j].first.first>0){
                sum+=arr[i][j].first.first;
            }
        }
    }
    return sum;
}
int main() {
    cin>>m>>t;
    cin>>pacman.first>>pacman.second;
    pacman.first--, pacman.second--;
    int a,b,c;
    for(int i=0;i<m;i++){
        cin>>a>>b>>c;
        a--,b--,c--;
        mons[{a,b,c}]++;
        arr[a][b].first.first++;
        arr[a][b].first.second=0;
        arr[a][b].second.first=0;
        arr[a][b].second.second=0;
    }
    simulate();

    // for(int i=0;i<4;i++){
    //     for(int j=0;j<4;j++){
    //         cout<<arr[i][j].first.first<<" ";
    //     }
    //     cout<<"\n";
    // }
    cout<<print_ans();
    return 0;
}