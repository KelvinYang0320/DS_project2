#include<iostream>
#include <fstream>
#include <vector>
using namespace std;
int main(){
    
    fstream fout;
    fstream fin_student;
    int r;
    int c;
    int battery;
    int charge_r;
    int charge_c;
    vector<pair<int,int>>v;
    //fin1.open("floor.data",ios::in);
    int score=70;
    fout.open("result.txt",ios::out);

    
    fin_student.open("student.testcase",ios::in);
    for(int iii=0;iii<70;iii++){//testcase_all
    v.clear();
    fstream fin1;
    fstream fin2;
    string id = "106000240";
    fin_student>>id;
    fout<<"student id:"<<id<<endl;
    cout<<id<<endl;
    fin1.open("Project2_Testcase/"+id+"_Testcase/floor.data",ios::in);
    fin2.open("output/"+id+".path",ios::in);
    int flag=0;

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
    
    fin2>>N;
    for(int i=0;i<N+1;i++){
        fin2>>fir>>sec;
        v.push_back(pair<int,int>(fir,sec));
    }
    //recharge pos
    fout<<"R:("<<v[0].first<<","<<v[0].second<<")"<<endl;
    if(v[0].first!=charge_r||v[0].second!=charge_c){
        fout<<"init pos error"<<endl;
        flag=1;
    }
    if(v[N].first!=charge_r||v[N].second!=charge_c){
        fout<<"final pos errot"<<endl;
        flag=1;
    }
    //測試電力充足和尚未超出地圖
    int cnt=0;
    for(int i=1;i<N+1;i++){
        cnt++;
        if(v[i].first>=r||v[i].first<0||v[i].second>=c||v[i].second<0){
            fout<<"move out of map"<<v[i].first<<","<<v[i].second<<endl;
            flag=1 ;
        }
        //cout<<v[i].first<<" "<<v[i].second<<endl;
        if(v[i].first==charge_r&&v[i].second==charge_c){
            cnt = 0;
        }
        if(cnt>=battery){
            fout<<"out of battery"<<v[i].first<<","<<v[i].second<<endl;
            flag=1;
        }
    }
    
    //測試移動距離與方式
    for(int i=0;i<N;i++){
        if(v[i].first==v[i+1].first){
            int cmp = v[i].second-v[i+1].second;
            if(cmp>1||cmp<-1){
                fout<<"there are two steps too far"<<v[i].first<<","<<v[i].second<<"vs"<<v[i+1].first<<","<<v[i+1].second<<endl;
                flag=1;
            }
        }
        else if(v[i].second==v[i+1].second){
            int cmp = v[i].first-v[i+1].first;
            if(cmp>1||cmp<-1){
                fout<<"there are two steps too far"<<v[i].first<<","<<v[i].second<<"vs"<<v[i+1].first<<","<<v[i+1].second<<endl;
                flag=1;
            }
        }else if(v[i].first==v[i+1].first&&v[i].second==v[i+1].second){
            fout<<"there are two steps no move"<<v[i].first<<","<<v[i].second<<"vs"<<v[i+1].first<<","<<v[i+1].second<<endl;
        }
        else if(v[i].second==v[i+1].second && v[i].first==v[i+1].first){
            fout<<"wrong move"<<endl;
            flag=1;
        }
    }
    
    //測試清理完畢
    for(int i=0;i<N+1;i++){
        if(map[v[i].first][v[i].second]=='1'){
            fout<<"through wall"<<endl;
            flag=1;
        }else{
            map[v[i].first][v[i].second]='C';
        }
        
    }
    fout<<"unclean:"<<endl;
    cnt=0;
    for(int i =0;i<r;i++){
        for(int j=0;j<c;j++){
            if(map[i][j]=='0'){
                fout<<"["<<i<<","<<j<<"]"<<endl;
                cnt++;
            }
        }
    }
    if(cnt==0){
        fout<<"none"<<endl;
    }else{
        fout<<"total unclean"<<cnt<<"cells"<<endl;
        flag=1;
    }
    if(flag==0)fout<<"[PASS]"<<endl;
    else{
        fout<<"[NON-PASS]"<<endl; 
        score=score-1;
    }

    }
    fout<<"Your socre "<<score<<"/70";
}