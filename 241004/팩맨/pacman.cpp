#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <tuple>
using namespace std;
// 몬스터,알, 시체, 턴
pair<pair<int,int>,pair<int,int>> arr[5][5];
int m,t,max_sum;
pair<int,int> pacman;
// r,c,d,state
// state 0:시체, 1:active, 2: egg
int dy[8] = {-1,-1,0,1,1,1,0,-1};
int dx[8] = {0,-1,-1,-1,0,1,1,1};
int dr[4] = {-1,0,1,0};
int dc[4] = {0,-1,0,1};
bool visited[5][5];
vector<int> dir,last;
vector<tuple<int,int,int,int>> tp;
// 팩맨 이동 체크 로직
void move_pacman(int row, int col, int sum, int lev, int rr, int cc){
    if(lev==3 && max_sum<sum){
        max_sum = sum;
        //cout<<sum<<"\n";
        // 시체 생성
        if(!last.empty()) last.clear();
        for(int i=0;i<dir.size();i++){
            last.push_back(dir[i]);
        }
        return;
    }
    for(int i=0;i<4;i++){
        int r = row + dr[i];
        int c = col + dc[i];
        if(r<0 || r>=4 || c<0 || c>=4) continue;
        if(!visited[r][c]){
            visited[r][c] = true;
            dir.push_back(i);
            move_pacman(r,c,sum + arr[r][c].first.first,lev+1,rr,cc);
            dir.pop_back();
            visited[r][c] = false;
        }
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
        //sort(tp.begin(),tp.end());
        for(int j=tp.size()-1;j>=0;j--){
            int tr = get<0>(tp[j]);
            int tc = get<1>(tp[j]);
            int state = get<3>(tp[j]);
            //cout<<tr<<" "<<tc<<"\n";
            if(tr==r && tc==c && state==1){
                tp.erase(tp.begin()+j);
            }
        }
        if(arr[r][c].first.first>0){
            arr[r][c].second.first += arr[r][c].first.first;
            arr[r][c].first.first = 0;
            arr[r][c].second.second = 3;
        }
    }

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(arr[i][j].second.first>1 && arr[i][j].second.second>0){
                arr[i][j].second.second--;
                if(arr[i][j].second.second==0){
                    arr[i][j].second.first=0;
                }
            }
        }
    }
}
void egg(){
    for(int i=0;i<tp.size();i++){
        int r = get<0>(tp[i]);
        int c = get<1>(tp[i]);
        int d = get<2>(tp[i]);
        int state = get<3>(tp[i]);
        if(state==0){
            get<3>(tp[i]) = 1;
            arr[r][c].first.second--;
            arr[r][c].first.first++;
        }
    }
}
void simulate(){
    for(int i=0;i<t;i++){
        int size=tp.size();
        max_sum=0;
        for(int s=0;s<size;s++){
            int r = get<0>(tp[s]);
            int c = get<1>(tp[s]);
            int d = get<2>(tp[s]);
            int state = get<3>(tp[s]);
            //cout<<r<<" "<<c<<" "<<d<<" "<<state<<"\n";
            if(state==1){
                // 몬스터 알 낳기
                if(arr[r][c].second.second==0){
                    tp.push_back({r,c,d,0});
                    arr[r][c].first.second++;
                }
                // 몬스터 이동
                int cnt=8;
                while(cnt--){
                    int rr = r+dy[d];
                    int cc = c+dx[d];
                    if(rr<0 || rr>=4 || cc<0 || cc>=4 || (rr == pacman.first && cc==pacman.second) || arr[rr][cc].second.first>0){
                        d+=1;
                        if(d==8) d = 0;
                    }
                    else{
                        get<0>(tp[s]) = rr;
                        get<1>(tp[s]) = cc;
                        get<2>(tp[s]) = d;
                        arr[rr][cc].first.first += 1;
                        arr[r][c].first.first--;
                        break;
                    }
                }
                
            }
        }
        // 팩맨 이동
        move_pacman(pacman.first,pacman.second,0,0,pacman.first,pacman.second);
        update_died();
        last.clear();
        egg();
        //cout<<pacman.first<<" "<<pacman.second<<"\n";
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
        tp.push_back({a,b,c,1});
        arr[a][b].first.first++;
        arr[a][b].first.second=0;
        arr[a][b].second.first=0;
        arr[a][b].second.second=0;
    }

    simulate();
    // sort(tp.begin(),tp.end());
    // for(int i=0;i<tp.size();i++){

    //     cout<<get<0>(tp[i])<<" "<<get<1>(tp[i])<<" "<<get<2>(tp[i])<<" "<<get<3>(tp[i])<<"\n";
    // }

    // for(int i=0;i<4;i++){
    //     for(int j=0;j<4;j++){
    //         cout<<arr[i][j].first.first<<" ";
    //     }
    //     cout<<"\n";
    // }
    cout<<print_ans();
    return 0;
}