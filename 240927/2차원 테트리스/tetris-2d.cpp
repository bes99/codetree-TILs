#include <iostream>
using namespace std;
int k,t,x,y,score;
bool arr[10][10];
void red_block(int type, int row){
    int c = 10;
    for(int j=4;j<10;j++){
        if(arr[row][j]){
            c=j;
            break;
        }
    }

    if(type==1){
        if(c-1>3)
            arr[row][c-1] = true;
    }
    else if(type==2){
        if(c-2>3){
            arr[row][c-1] = true;
            arr[row][c-2] = true;
        }
    }

    else if(type==3){
        for(int j=4;j<10;j++){
            if(arr[row][j] || arr[row+1][j]){
                c=j;
                break;
            }
        }
        if(c-1>3){
            arr[row][c-1] = true;
            arr[row+1][c-1] = true;
        }
    }

    for(int j=9;j>=4;j--){
        bool flag = false;
        for(int i=0;i<4;i++){
            if(!arr[i][j]){
                flag = true;
                break;
            }
        }
        if(!flag){
            score++;
            for(int tj=j;tj>4;tj--){
                for(int i=0;i<4;i++){
                    arr[i][tj] = arr[i][tj-1];
                }
            }
            for(int i=0;i<4;i++){
                arr[i][4] = false;
            }
        }
    }

    for(int j=4;j<6;j++){
        bool flag = false;
        for(int i=0;i<4;i++){
            if(arr[i][j]){
                flag = true;
                break;
            }
        }

        if(flag){
            for(int tj=9;tj>4;tj--){
                for(int i=0;i<4;i++){
                    arr[i][tj] = arr[i][tj-1];
                }
            }
            for(int i=0;i<4;i++){
                arr[i][4] = false;
            }
        }
    }
}
void yellow_block(int type, int col){
    int r = 10;
    for(int i=4;i<10;i++){
        if(arr[i][col]){
            r=i;
            break;
        }
    }

    if(type==1){
        if(r-1>3)
            arr[r-1][col] = true;
    }
    else if(type==2){
        for(int i=4;i<10;i++){
            if(arr[i][col] || arr[i][col+1]){
                r=i;
                break;
            }
        }
        if(r-1>3){
            arr[r-1][col] = true;
            arr[r-1][col+1] = true;
        }
    }
    else if(type==3){
        if(r-2>3){
            arr[r-1][col] = true;
            arr[r-2][col] = true;
        }
    }

    for(int i=9;i>=4;i--){
        bool flag = false;
        for(int j=0;j<4;j++){
            if(!arr[i][j]){
                flag = true;
                break;
            }
        }
        if(!flag){
            score++;
            for(int ti=i;ti>4;ti--){
                for(int j=0;j<4;j++){
                    arr[ti][j] = arr[ti-1][j];
                }
            }
            for(int j=0;j<4;j++){
                arr[4][j] = false;
            }
        }
    }

    for(int i=4;i<6;i++){
        bool flag = false;
        for(int j=0;j<4;j++){
            if(arr[i][j]){
                flag = true;
                break;
            }
        }

        if(flag){
            for(int ti=9;ti>4;ti--){
                for(int j=0;j<4;j++){
                    arr[ti][j] = arr[ti-1][j];
                }
            }
            for(int j=0;j<4;j++){
                arr[4][j] = false;
            }
        }
    }
}
void simulate(int type, int row, int col){
    yellow_block(type,col);
    red_block(type,row);
}
int count_block(){
    int cnt=0;
    for(int i=4;i<=9;i++){
        for(int j=0;j<4;j++){
            if(arr[i][j]) cnt++;
        }
    }
    for(int j=4;j<=9;j++){
        for(int i=0;i<4;i++){
            if(arr[i][j]) cnt++;
        }
    }
    return cnt;
}
int main() {
    cin>>k;
    for(int i=0;i<k;i++){
        cin>>t>>x>>y;
        simulate(t,x,y);
    }

    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            if(arr[i][j]){
                cout<<" "<<1;
            }
            else cout<<" "<<0;
        }
        cout<<"\n";
    }
    
    //cout<<score<<"\n"<<count_block();
    return 0;
}