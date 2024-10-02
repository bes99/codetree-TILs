#include <iostream>
#include <vector>
using namespace std;
int n,m,d,p;
int arr[16][16];
int dr[8] = {0,-1,-1,-1,0,1,1,1};
int dc[8] = {1,1,0,-1,-1,-1,0,1};
vector<pair<int,int>> vec,dp;
bool checked[16][16];
void next_nut(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(arr[i][j]>=2 && !checked[i][j]){
                arr[i][j]-=2;
                vec.push_back({i,j});
            }
            else if(checked[i][j]){
                checked[i][j] = false;
            }
        }
    }
}
void move_nut(){
    vector<pair<int,int>> tmp;
    for(int i=0;i<vec.size();i++){
        int r = vec[i].first;
        int c = vec[i].second;

        for(int k=0;k<p;k++){
            r+=dr[d];
            if(r<0) r = n-1;
            else if(r>=n) r=0;
        }
        for(int k=0;k<p;k++){
            c+=dc[d];
            if(c<0) c = n-1;
            else if(c>=n) c=0;
        }

        checked[r][c] = true;
        arr[r][c]++;
        tmp.push_back({r,c});
    }

    for(int i=0;i<tmp.size();i++){
        int r = tmp[i].first;
        int c = tmp[i].second;
        int cnt=0;
        for(int j=1;j<8;j+=2){
            int rr = r+dr[j];
            int cc = c+dc[j];
            if(rr<0 || rr>=n || cc<0 || cc>=n) continue;
            if(arr[rr][cc]>0) cnt++;
        }
        arr[r][c]+=cnt;
    }
    vec.clear();
}

int count_tree(){
    int cnt=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            //cout<<arr[i][j]<<" ";
            if(arr[i][j]>0)
                cnt+=arr[i][j];
        }
        //cout<<"\n";
    }
    return cnt;
}
void simulate(){
    for(int i=0;i<m;i++){
        d = dp[i].first;
        p = dp[i].second;
        move_nut();
        next_nut();
    }
    cout<<count_tree();
}
int main() {
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>arr[i][j];
        }
    }
    for(int i=0;i<m;i++){
        int a,b;
        cin>>a>>b;
        dp.push_back({a-1,b});
    }
    vec.push_back({n-2,0});
    vec.push_back({n-2,1});
    vec.push_back({n-1,0});
    vec.push_back({n-1,1});
    simulate();
    return 0;
}