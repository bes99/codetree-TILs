#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <tuple>
#include <queue>
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
vector<int> dir,last;
vector<tuple<int,int,int,int>> tp;
// 팩맨 이동 체크 로직
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
    for(int i=0;i<tp.size();i++){
        int r = get<0>(tp[i]);
        int c = get<1>(tp[i]);
        int state = get<3>(tp[i]);
        //cout<<r<<" "<<c<<" "<<state<<"\n";
        if(state==0){
            get<3>(tp[i]) = 1;
            arr[r][c].first.second--;
            arr[r][c].first.first++;
        }
    }
    //cout<<"\n";
}
void simulate(){
    for(int i=0;i<t;i++){
        int size=tp.size();
        max_sum=-1;
        for(int s=0;s<size;s++){
            int r = get<0>(tp[s]);
            int c = get<1>(tp[s]);
            int d = get<2>(tp[s]);
            int state = get<3>(tp[s]);
            //cout<<r<<" "<<c<<" "<<d<<" "<<state<<"\n";
            if(state==1){
                // 몬스터 알 낳기
                tp.push_back({r,c,d,0});
                arr[r][c].first.second++;

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
        mv(pacman.first,pacman.second);
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