#include<iostream>
#include <fstream>
using namespace std;
class cell_state{
    private:
        int c;
        int r;
        char status;
        int rank;
    /*
    '1':wall 
    '0':free sapce 
    'R' indicates where the robot is placed initially. This is also where the robot can be recharged.  
    'C': space that have been cleaned
    */
        cell_state* left;
        cell_state* right;
        cell_state* up;
        cell_state* down;
    public:
        
        cell_state():c(-1),r(-1),status('0'),left(nullptr),right(nullptr),up(nullptr),down(nullptr){};
        cell_state(int p1, int p2, char s):r(p1),c(p2),status(s){};

        void showpos(){
            cout<<r<<" "<<c;
        }
        void showstatus(){
            cout<<status;
        }
        int getc(){
            return c;
        }
        int getr(){
            return r;
        }
        void setrank(int newrank){
            rank = newrank;
        }
        char getstatus(){
            return status;
        }
        void changestate(char news){
            status = news;
        }
};
class Map{
    private:
        int unclean;
        char* R;
        int col_num;
        int row_num;
        int max_step;
        int index_R;
        int index_C;
    public:
        Map(fstream &fin){
            unclean=0;
            fin>>row_num;
            fin>>col_num;
            fin>>max_step;
            R = new char [row_num*col_num];
            for(int i =0;i<row_num;i++){
                for(int j =0;j<col_num;j++){
                    fin>>R[i*col_num+j];
                    if(R[i*col_num+j]=='0')unclean++;
                    if(R[i*col_num+j]=='R'){
                        index_R = i;
                        index_C = j;
                    }
                }
            }
        }
        Map():unclean(0),R(nullptr){};
        int getmax_step(){
            return max_step;
        }
        int getrow_num(){
            return row_num;
        }
        int getcol_num(){
            return col_num;
        }
        void show_whole_map(){
            for(int i =0;i<row_num;i++){
                for(int j =0;j<col_num;j++){
                    cout<<R[i*col_num+j]<<" ";
                }
                cout<<endl;
            }
        }
        void show_unclean(){
            cout<<"unclean:"<<unclean<<endl;
        }
        void show_maxstep(){
            cout<<"maxstep:"<<max_step<<endl;
        }
        void where_is_R(){
            cout<<"R("<<index_R<<","<<index_C<<")";
        }
        int R_indr(){
            return index_R;
        }
        int R_indc(){
            return index_C;
        }
        char what(int r, int c){
            return R[r*col_num+c];
        }
        cell_state* construct_graph(cell_state* root){
            if(root->getstatus()=='1'){
                return new cell_state();
            }
        }
};
int main(){
    fstream fin;
    fstream fout;
    Map *m;
    cell_state *R;
    fin.open("map.data",ios::in);
    fout.open("step.output",ios::out);
    m=new Map(fin);
    m->show_whole_map();
    m->show_unclean();
    m->show_maxstep();
    m->where_is_R();
    cout<<m->what(6,4);
    R = new cell_state(m->R_indr(), m->R_indc(), 'R');
    
    return 0;

}