#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;

int N,M,K,sum;
int arr[11][11],cpy[11][11];
int end_r, end_c;
int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};
vector<pair<pair<int,int>,int>> vec;
bool compare(pair<pair<int,int>,int> a, pair<pair<int,int>,int> b){
    if(a.first.first == b.first.first){
        return a.first.second<b.first.second;
    }
    else return a.first.first < b.first.first;
}
int get_dist(int r, int c){
    return abs(end_r-r) + abs(end_c-c);
}
void cand_move(){
    queue<pair<int,pair<int,int>>> q;
    for(int i=0;i<vec.size();i++){
        int r = vec[i].first.first;
        int c = vec[i].first.second;
        int dist = get_dist(r,c);
        int dir=-1;
        for(int j=0;j<4;j++){
            int rr = r+dr[j];
            int cc = c+dc[j];
            if(rr<0 || rr>=N || cc<0 || cc>N) continue;
            if(arr[rr][cc]== 0 && dist>get_dist(rr,cc)){
                dir = j;
                break;
            }
        }
        if(dir!=-1){
            vec[i].first.first = r+dr[dir];
            vec[i].first.second = c+dc[dir];
            vec[i].second += 1;
            if(end_r==vec[i].first.first && end_c==vec[i].first.second){
                q.push({vec[i].second,{vec[i].first.first,vec[i].first.second}});
            }
        }
    }
    while(!q.empty()){
        int r = q.front().second.first;
        int c = q.front().second.second;
        q.pop();
        for(int i=vec.size()-1;i>=0;i--){
            if(vec[i].first.first==r && vec[i].first.second==c){
                sum+=vec[i].second;
                vec.erase(vec.begin()+i);
            }
        }
    }
}
bool check(int row, int col, int lev){
    bool flag[2]={false,false};
    for(int r=row;r<row+lev;r++){
        for(int c=col;c<col+lev;c++){
            if(!flag[0]){
                for(auto v: vec){
                    if(v.first.first==r && v.first.second==c){
                        flag[0] = true;
                        break;
                    }
                }
            }
            if(!flag[1]){
                if(r==end_r && c==end_c){
                    flag[1] =true;
                }
            }
            if(flag[0] && flag[1]) return true;
        }
    }
    return false;
}
pair<int,pair<int,int>> get_squre(){
    for(int lev=2;lev<=N;lev++){
        for(int i=0;i<=N-lev;i++){
            for(int j=0;j<=N-lev;j++){
                if(check(i,j,lev)){
                    return {lev,{i,j}};
                }
            }
        }
    }
}
void copy(){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cpy[i][j] = arr[i][j];
        }
    }
}
void rotate(){
    copy();
    sort(vec.begin(),vec.end(),compare);
    pair<int,pair<int,int>> squre = get_squre();
    int lev = squre.first;
    int row = squre.second.first;
    int col = squre.second.second;
    for(int k=0;k<vec.size();k++){
        int r = vec[k].first.first;
        int c = vec[k].first.second;
        for(int i=0;i<lev;i++){
            for(int j=0;j<lev;j++){
                if(r==row+i && c==col+j){
                    vec[k].first.first = row+j;
                    vec[k].first.second = col+lev-i-1;
                }
            }
        }
    }
    bool flag = false;
    for(int i=0;i<lev;i++){
        for(int j=0;j<lev;j++){
            if(!flag && end_r==row+i && end_c==col+j){
                flag = true;
                end_r = row+j;
                end_c = col+lev-i-1;
            }
            arr[row+j][col+lev-i-1] = cpy[row+i][col+j];
        }
    }
    for(int i=row;i<row+lev;i++){
        for(int j=col;j<col+lev;j++){
            if(arr[i][j]>0) arr[i][j]--;
        }
    }

}
void simulate(){
    for(int k=0;k<K;k++){
        cand_move();
        if(vec.size()==0) return;
        rotate();
    }
    for(int i=0;i<vec.size();i++){
        int d = vec[i].second;
        sum += d;
    }
}
void test(int row, int col, int lev){
    copy();
    for(int i=0;i<lev;i++){
        for(int j=0;j<lev;j++){
            arr[row+j][col+lev-i-1] = cpy[row+i][col+j];
        }
    }
    for(int i=row;i<row+lev;i++){
        for(int j=col; j<col+lev;j++){
            cout<<arr[i][j]<<" ";
        }
        cout<<"\n";
    }
}
int main() {
    cin>>N>>M>>K;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin>>arr[i][j];
        }
    }
    int a,b;
    for(int i=0;i<M;i++){
        cin>>a>>b;
        a--,b--;
        vec.push_back({{a,b},0});
    }
    cin>>end_r>>end_c;
    end_r--, end_c--;

    simulate();
    
    cout<<sum<<"\n"<<end_r+1<<" "<<end_c+1;
    return 0;
}