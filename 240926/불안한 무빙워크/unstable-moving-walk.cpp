#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int n, k;
// <내구도,현재 사람이 있는지 여부>
pair<int,int> arr[201];
vector<int> vec;

void print_vec(){
    for(int i=0;i<vec.size();i++){
        cout<<vec[i]<<" ";
    }
}
void delete_vec(){
    for(int i=0;i<vec.size();i++){
        if(n==vec[i]){
            vec.erase(vec.begin()+i);
            return;
        }
    }
}
void rotate(){
    int tmp1 = arr[2*n].first;
    int tmp2 = arr[2*n].second;
    for(int i=2*n;i>1;i--){
        arr[i].first = arr[i-1].first;
        arr[i].second = arr[i-1].second;
    }
    arr[1].first = tmp1;
    arr[1].second = tmp2;

    for(int i=0;i<vec.size();i++){
        vec[i]++;
    }

    if(arr[n].second==1){
        arr[n].second=0;
        delete_vec();
    }
}
void move(){
    for(int i=0;i<vec.size();i++){
        if(vec[i]<2*n && arr[vec[i]+1].first>0 && arr[vec[i]+1].second==0){
            arr[vec[i]+1].first--;
            arr[vec[i]+1].second=1;
            arr[vec[i]].second=0;
            vec[i]++;
        }
        else if(vec[i]==2*n){
            arr[1].first--;
            arr[1].second=1;
            arr[2*n].second=0;
            vec[i] = 1;
        }
    }
    if(arr[n].second==1){
        arr[n].second=0;
        delete_vec();
    }
}
int check(){
    int cnt=0;
    for(int i=1;i<=2*n;i++){
        if(arr[i].first==0){
            cnt++;
        }
    }
    return cnt;
} 
int simulate(){
    int cnt=1;
    while(1){
        rotate();
        move();
        if(arr[1].first>0 && arr[1].second==0){
            vec.push_back(1);
            arr[1].first--;
            arr[1].second=1;
        }  
        int flag = check();
        if(flag>=k){
            return cnt; 
        }
        cnt++;
    }

}
int main() {
    cin>>n>>k;
    for(int i=1;i<=2*n;i++){
        cin>>arr[i].first;
        arr[i].second = 0;
    }

    cout<<simulate();
    return 0;
}