#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
int arr[21][21];
int n;
vector<int> vec[401];
queue<int> q;
int dr[4] = {0,0,1,-1};
int dc[4] = {1,-1,0,0};
bool compare(pair<int,int> a, pair<int,int> b){
    if(a.first<b.first)
        return a.first<b.first;
    else if(a.first==b.first)
        return a.second<b.second;
    else
        return a.first<b.first;

}
void f3(int idx, vector<pair<int,pair<int,int>>> v){
    vector<pair<int,int>> tmp;
    for(int i=0;i<v.size();i++){
        int r = v[i].second.first;
        int c=  v[i].second.second;
        tmp.push_back({r,c});
    }
    sort(tmp.begin(),tmp.end(),compare);
    
    int r = tmp[0].first;
    int c = tmp[0].second;
    arr[r][c] = idx;
}
void f2(int idx, vector<pair<int,pair<int,int>>> v){
    int max_cnt=0;
    vector<pair<int,pair<int,int>>> tmp;
    for(int i=0;i<v.size();i++){
        int cnt = 0;
        int row = v[i].second.first;
        int col = v[i].second.second;
        for(int d=0;d<4;d++){
            int r = row+dr[d];
            int c = col+dc[d];
            if(r<0 || r>=n || c<0 || c>=n) continue;
            if(arr[r][c]>0) continue;
            if(arr[r][c]==0) cnt++;
        }
        if(max_cnt<=cnt){
            max_cnt = cnt;
            tmp.push_back({cnt,{row,col}});
        }
    }

    sort(tmp.rbegin(),tmp.rend());
    int t = tmp[0].first;
    while(tmp.back().first<t){
        tmp.erase(tmp.end());
    }
    if(tmp.size()==1){
        int r = tmp[0].second.first;
        int c = tmp[0].second.second;
        arr[r][c] = idx;
    }
    else{
        f3(idx, tmp);
    }
}
void f1(int idx, int x, int y, int z, int k){
    int max_cnt=0,cnt;
    vector<pair<int,pair<int,int>>> tmp;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cnt=0;
            for(int d=0;d<4;d++){
                int r = i+dr[d];
                int c = j+dc[d];
                if(r<0 || r>=n || c<0 || c>=n) continue;
                if(arr[i][j]>0) continue;
                if(arr[r][c]==x || arr[r][c]==y || arr[r][c]==z || arr[r][c]==k){
                    cnt++;
                }
            }
            
            if(max_cnt<=cnt && arr[i][j]==0){
                max_cnt = cnt;
                tmp.push_back({cnt,{i,j}});
            }

        }
    }

    sort(tmp.rbegin(),tmp.rend());
    int t = tmp[0].first;
    while(tmp.back().first<t){
        tmp.erase(tmp.end());
    }
    
    if(tmp.size()==1){
        int r = tmp[0].second.first;
        int c = tmp[0].second.second;
        arr[r][c] = idx;
    }
    else{
        f2(idx, tmp);
    }
}
void print(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<arr[i][j]<<" ";
        }
        cout<<"\n";
    }
}
int count_score(){
    int sum=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            int cnt=0;

            int idx = arr[i][j];
            int x = vec[idx][0];
            int y = vec[idx][1];
            int z = vec[idx][2];
            int k = vec[idx][3];

            for(int d=0;d<4;d++){
                int r = i+dr[d];
                int c = j+dc[d];
                if(r<0 || r>=n || c<0 || c>=n) continue;
                if(arr[r][c]==x || arr[r][c]==y || arr[r][c]==z || arr[r][c]==k){
                    cnt++;
                }
            }

            if(cnt==1) sum += 1;
            else if(cnt==2) sum+=10;
            else if(cnt==3) sum+=100;
            else if(cnt==4) sum+=1000;
        }
    }
    return sum;
}
void simulate(){
    while(!q.empty()){
        int idx = q.front();
        q.pop();
        int a = vec[idx][0];
        int b = vec[idx][1];
        int c = vec[idx][2];
        int d = vec[idx][3];

        f1(idx,a,b,c,d);
        //print();
    }
    cout<<count_score();
}
int main() {
    int idx, val;
    cin>>n;
    for(int i=0;i<n*n;i++){
        cin>>idx;
        q.push(idx);
        for(int j=0;j<4;j++){
            cin>>val;
            vec[idx].push_back(val);
        }
    }
    simulate();
    return 0;
}