#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
int ans;
int dr[8] = {-1,-1,0,1,1,1,0,-1};
int dc[8] = {0,-1,-1,-1,0,1,1,1};
int board_info_p[5][5];
int board_info_d[5][5];
int copy_p[15][5][5];
int copy_d[15][5][5];

vector<pair<pair<int,int>,pair<int,int>>> vec;
pair<int,pair<int,int>> tag;
void vec_erase(int row, int col){
    for(int i=0;i<vec.size();i++){
        int r = vec[i].second.first;
        int c = vec[i].second.second;
        if(row==r && col==c){
            board_info_p[r][c] = -1;
            board_info_d[r][c] = -1;
            vec.erase(vec.begin()+i);
            return;
        }
    }
}
void change(int idx, int r, int c, int rr, int cc){

    swap(board_info_p[r][c],board_info_p[rr][cc]);
    swap(board_info_d[r][c],board_info_d[rr][cc]);

    for(int i=0;i<vec.size();i++){
        int target = vec[i].first.first;
        if(target==board_info_p[r][c]){
            //swap(vec[i].first.first, vec[idx].first.first);
            //swap(vec[i].first.second, vec[idx].first.second);
            swap(vec[i].second.first, vec[idx].second.first);
            swap(vec[i].second.second, vec[idx].second.second);
            sort(vec.begin(),vec.end());
            
            return;
        }
    }
    
}
void move_horse(){
    for(int i=0;i<vec.size();i++){
        int p = vec[i].first.first;
        int d = vec[i].first.second;
        int r = vec[i].second.first;
        int c = vec[i].second.second;

        for(int j=0;j<8;j++){
            int dd = (d+j)%8;
            int rr = r+dr[dd];
            int cc = c+dc[dd];
            if(rr<1 || rr>4 || cc<1 || cc>4) continue;
            if(rr==tag.second.first && cc==tag.second.second) continue;
            else{
                board_info_d[r][c] = dd;
                vec[i].first.second = dd;
                change(i,r,c,rr,cc);
                break;
            }
        }
    }
}
void copy(int lev){
    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++){
            copy_p[lev][i][j] = board_info_p[i][j];
            copy_d[lev][i][j] = board_info_d[i][j];
        }
    }
}
void recovery(int r, int c, int lev){
    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++){
            board_info_p[i][j] = copy_p[lev][i][j];
            board_info_d[i][j] = copy_d[lev][i][j];
        }
    }
    vec.push_back({{board_info_p[r][c],board_info_d[r][c]},{r,c}});
    sort(vec.begin(),vec.end());
}
void attack(int d, int row, int col, int sum, int lev){
    for(int i=2;i<4;i++){
        int r = row+(dr[d]*i);
        int c = col+(dc[d]*i);
        if(r>=1 && r<=4 && c>=1 && c<=4 && board_info_p[r][c]>-1){
            move_horse();
            copy(lev);
            int s = board_info_p[r][c];
            int td = board_info_d[r][c];

            //cout<<r<<" "<<c<<" "<<lev<<" "<<td<<"\n";
            ans = max(ans,sum+s);

            // 잡아먹는 로직
            tag.first = td;
            tag.second.first = r;
            tag.second.second = c;
            vec_erase(r,c);

            attack(td, r, c, sum+s,lev+1);
            
            // 복구 로직
            recovery(r, c, lev);
            tag.first = d;
            tag.second.first = row;
            tag.second.second = col;
            
        }
    }
}
int main() {
    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++){
            cin>>board_info_p[i][j]>>board_info_d[i][j];
            board_info_d[i][j]-=1;
            vec.push_back({{board_info_p[i][j], board_info_d[i][j]},{i,j}});
        }
    }

    // for(int i=1;i<=4;i++){
    //     for(int j=1;j<=4;j++){
    //         cout<<board_info_d[i][j]<<" "<<i<<" "<<j<<"\n";
    //     }
    // }

    // tag.first = board_info_d[1][1];
    // tag.second.first =1;
    // tag.second.second=1;
    // vec_erase(1,1);
    // sort(vec.begin(),vec.end());
    // move_horse();
    // for(auto t:vec){
    //     cout<<t.first.first<<" "<<t.first.second<<" "<<t.second.first<<" "<<t.second.second<<"\n";
    // }
    
    int s = board_info_p[1][1];
    tag.first = board_info_d[1][1];
    tag.second.first=1;
    tag.second.second=1;
    vec_erase(1,1);
    sort(vec.begin(),vec.end());
    attack(tag.first,1,1,s,0);

    cout<<ans;
    return 0;
}