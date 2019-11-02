#include<iostream>
#include <fstream>
#include <vector>
using namespace std;
int main(){
    fstream fin1;
    fstream fin2;
    int r;
    int c;
    int battery;
    int charge_r;
    int charge_c;
    fin1.open("map.data",ios::in);
    fin2.open("step.output",ios::in);
    fin1>>r>>c>>battery;
    char **map= new char* [r];
    for(int i =0;i<r;i++){
        map[i] = new char [c];
        for(int j=0;j<c;j++){
            fin1>>map[i][j];
            if(map[i][j]=='R'){
                charge_r=i;
                charge_c=j;
            }
        }
    }

    int N;
    int fir;
    int sec;
    vector<pair<int,int>>v;
    fin2>>N;
    for(int i=0;i<N;i++){
        fin2>>fir>>sec;
        v.push_back(pair<int,int>(fir,sec));
    }
    if(v[0].first!=charge_r|v[0].second!=charge_c){
        cout<<"初始位置錯誤"<<endl;
        return 0;
    }
    //測試電力充足和尚未超出地圖
    int cnt;
    for(int i=0;i<N;i++){
        cnt++;
        if(v[i].first>=r||v[i].first<0||v[i].second>=c||v[i].second<0){
            cout<<"移動超出地圖"<<v[i].first<<","<<v[i].second<<endl;
            return 0 ;
        }
        //cout<<v[i].first<<" "<<v[i].second<<endl;
        if(v[i].first==charge_r&&v[i].second==charge_c){
            cnt = 0;
        }
        if(cnt>=battery){
            cout<<"沒電了"<<v[i].first<<","<<v[i].second<<endl;
            return 0;
        }
    }
    //測試移動距離
    for(int i=0;i<N-1;i++){
        if(v[i].first!=v[i+1].first){
            int cmp = v[i].second-v[i+1].second;
            if(cmp>1||cmp<-1){
                cout<<"有其中兩步驟間移動過遠"<<v[i].first<<","<<v[i].second<<"vs"<<v[i+1].first<<","<<v[i+1].second<<endl;
                return 0;
            }
        }
        else if(v[i].second!=v[i+1].second){
            int cmp = v[i].first-v[i+1].first;
            if(cmp>1||cmp<-1){
                cout<<"有其中兩步驟間移動過遠"<<v[i].first<<","<<v[i].second<<"vs"<<v[i+1].first<<","<<v[i+1].second<<endl;
                return 0;
            }
        }else if(v[i].first==v[i+1].first&&v[i].second==v[i+1].second){
            cout<<"有其中兩步驟間沒有移動"<<v[i].first<<","<<v[i].second<<"vs"<<v[i+1].first<<","<<v[i+1].second<<endl;
        }
    }
    for(int i=0;i<N;i++){
        map[v[i].first][v[i].second]='C';
    }
    for(int i =0;i<r;i++){
        for(int j=0;j<c;j++){
            cout<<map[i][j];
        }
        cout<<endl;
    }
    cout<<"未清理:"<<endl;
    cnt=0;
    for(int i =0;i<r;i++){
        for(int j=0;j<c;j++){
            if(map[i][j]=='0'){
                cout<<"["<<i<<","<<j<<"]"<<endl;
                cnt++;
            }
        }
    }
    if(cnt==0){
        cout<<"無"<<endl;
    }else{
        cout<<"共計"<<cnt<<"格"<<endl;
        return 0;
    }
    cout<<"[PASS]"<<endl;
}
