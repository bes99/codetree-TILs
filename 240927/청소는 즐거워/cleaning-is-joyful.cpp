#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
int ans;
int dr[4][9]={
    {-2,-1,-1,-1,0,1,1,1,2},
    {0,1,0,-1,2,1,0,-1,0},
    {-2,-1,-1,-1,0,1,1,1,2},
    {0,-1,0,1,-2,-1,0,1,0}
};
int dc[4][9] ={
    {0,-1,0,1,-2,-1,0,1,0},
    {-2,-1,-1,-1,0,1,1,1,2},
    {0,1,0,-1,2,1,0,-1,0},
    {2,1,1,1,0,-1,-1,-1,-2}
};
int n;
int arr[500][500];
double conv[9] = {0.02, 0.1, 0.07, 0.01, 0.05, 0.1, 0.07, 0.01, 0.02};
void calc(int d, int row, int col){
    int curr = arr[row][col];
    for(int i=0;i<9;i++){
        int val = floor(curr * conv[i]);
        arr[row][col]-=val;

        int r = row+dr[d][i];
        int c = col+dc[d][i];
        if(r<0 || r>=n || c<0 || c>=n){
            ans+=val;
            continue;
        }
        arr[r][c] += val;
    }
    //cout<<d<<" "<<col-1<<"\n";
    if(d==0 && col-1>=0){
        arr[row][col-1] += arr[row][col];
    }
    else if(d==1 && row+1<n){
        arr[row+1][col] += arr[row][col];
    }
    else if(d==2 && col+1<n){
        arr[row][col+1] += arr[row][col];
    }
    else if(d==3 && row-1>=0){
        arr[row-1][col] += arr[row][col];
    }
    else{
        ans += arr[row][col];
    }
    arr[row][col] = 0;
}
void print(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<arr[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";
}
void simulate(int row, int col){
    int lev=0;
    int r = row;
    int c = col;

    while(r!=0 && c!=0){
        lev++;
        for(int j=0;j<lev;j++){
            c--;
            calc(0,r,c);
            //print();
        }
        for(int j=0;j<lev;j++){
            r++;
            calc(1,r,c);
            //print();
        }
        lev++;
        for(int j=0;j<lev;j++){
            c++;
            calc(2,r,c);
            //print();
        }

        for(int j=0;j<lev;j++){
            r--;
            calc(3,r,c);
        }
    }
    for(int j=0;j<lev;j++){
        c--;
        calc(0,r,c);    
    }
}
int main() {
    cin>>n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>arr[i][j];
        }
    }
    simulate(n/2,n/2);
    cout<<ans;
    return 0;
}