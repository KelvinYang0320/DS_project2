#include<iostream>
#include <fstream>
#include <vector>
using namespace std;
int main(){
    fstream fin1;
    fstream fin2;
    fstream fout;
    int r;
    int c;
    int battery;
    int charge_r;
    int charge_c;
    fin1.open("floor.data",ios::in);
    fin2.open("final.path",ios::in);
    fout.open("result.txt",ios::out);
    fin1>>r>>c>>battery;
    //construct map
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
    for(int i=0;i<N+1;i++){
        fin2>>fir>>sec;
        v.push_back(pair<int,int>(fir,sec));
    }
    //recharge pos
    cout<<"R:("<<v[0].first<<","<<v[0].second<<")"<<endl;
    if(v[0].first!=charge_r||v[0].second!=charge_c){
        cout<<"init pos error"<<endl;
        return 0;
    }
    if(v[N].first!=charge_r||v[N].second!=charge_c){
        cout<<"final pos errot"<<endl;
        return 0;
    }
    //測試電力充足和尚未超出地圖
    int cnt=0;
    for(int i=1;i<N+1;i++){
        cnt++;
        if(v[i].first>=r||v[i].first<0||v[i].second>=c||v[i].second<0){
            cout<<"move out of map"<<v[i].first<<","<<v[i].second<<endl;
            return 0 ;
        }
        //cout<<v[i].first<<" "<<v[i].second<<endl;
        if(v[i].first==charge_r&&v[i].second==charge_c){
            cnt = 0;
        }
        if(cnt>=battery){
            cout<<"out of battery"<<v[i].first<<","<<v[i].second<<endl;
            return 0;
        }
    }
    
    //測試移動距離與方式
    for(int i=0;i<N;i++){
        if(v[i].first==v[i+1].first){
            int cmp = v[i].second-v[i+1].second;
            if(cmp>1||cmp<-1){
                cout<<"there are two steps too far"<<v[i].first<<","<<v[i].second<<"vs"<<v[i+1].first<<","<<v[i+1].second<<endl;
                return 0;
            }
        }
        else if(v[i].second==v[i+1].second){
            int cmp = v[i].first-v[i+1].first;
            if(cmp>1||cmp<-1){
                cout<<"there are two steps too far"<<v[i].first<<","<<v[i].second<<"vs"<<v[i+1].first<<","<<v[i+1].second<<endl;
                return 0;
            }
        }else if(v[i].first==v[i+1].first&&v[i].second==v[i+1].second){
            cout<<"there are two steps no move"<<v[i].first<<","<<v[i].second<<"vs"<<v[i+1].first<<","<<v[i+1].second<<endl;
        }
        else if(v[i].second==v[i+1].second && v[i].first==v[i+1].first){
            cout<<"wrong move"<<endl;
            return 0;
        }
    }
    
    //測試清理完畢
    for(int i=0;i<N+1;i++){
        if(map[v[i].first][v[i].second]=='1'){
            cout<<"through wall"<<endl;
            return 0;
        }else{
            map[v[i].first][v[i].second]='C';
        }
        
    }
    cout<<"unclean:"<<endl;
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
        cout<<"none"<<endl;
    }else{
        cout<<"total unclean"<<cnt<<"cells"<<endl;
        return 0;
    }
    cout<<"[PASS]"<<endl;
}