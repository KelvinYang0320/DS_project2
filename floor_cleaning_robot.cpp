#include<iostream>
#include <fstream>
#include <iomanip>
using namespace std;
template<class T>
class Node 
{
    public:
        void setdata(T d){data=d;}
        T getdata(){return data;}
        void setlink(Node* l){link=l;}
        Node* getlink(){return link;}
    private: 
        T data; 
        Node* link; 
}; 

template<class T>
class Queue 
{
    private: 
        Node<T> *fro;
        Node<T> *rear;
    public:
        Queue(){
            fro=nullptr;
            rear=nullptr;
        }
        ~Queue(){
            Node<T> *temp = fro;
            Node<T> *kill;
            if(fro!=nullptr){
                while (temp->getlink() != fro) 
                { 
                    kill = temp;
                    temp = temp->getlink(); 
                    delete kill;
                } 
                delete temp;
            } 
            fro = nullptr;
            rear = nullptr;
             
        }
        void setfront(Node<T>* f){fro=f;}
        void setrear(Node<T>* r){rear=r;}
        Node<T>* getfront(){return fro;}
        Node<T>* getrear(){return rear;}
        // Function to create Circular queue 
        void push(T d){
            Node<T> *temp = new Node<T>; 
            temp->setdata(d); 
            if (fro == nullptr) 
                fro = temp; 
            else
            rear->setlink(temp); 
            rear = temp; 
            rear->setlink(fro); 
        }
        int find(T d){ //1 do find 0 not find
            Node<T> *temp = fro;
            if(fro==nullptr){
                return 0;
            } 
            while (temp->getlink() != fro) 
            { 
                if(temp->getdata()==d){
                    return 1;
                } 
                temp = temp->getlink(); 
            } 
            if(temp->getdata()==d){
                    return 1;
            }
            return 0;
        }
        // Function to delete element from Circular Queue 
        void pop_t() 
        {   
            if (fro == nullptr) 
            { 
                throw "[ERROR]pop from empty queue"; 
            } 
    
            // If this is the last node to be deleted 
            T value; // Value to be dequeued 
            if (fro == rear) 
            { 
                value = fro->getdata(); 
                delete fro;
                fro = nullptr; 
                rear = nullptr; 
            } 
            else  // There are more than one nodes 
            { 
                Node<T> *temp = fro; 
                value = temp->getdata(); 
                fro = fro->getlink(); 
                rear->setlink(fro); 
                delete temp; 
            } 
        } 
        void pop(){
            try{
                pop_t();
            }
            catch(char const*e){
                cout<<e<<endl;
            }
        }
        T front(){
            return fro->getdata();
        }
        T back(){
            return rear->getdata();
        }
        bool isEmpty(){
            if(fro==nullptr) return 1;
            else return 0;
        }
        void displayQueue() 
        { 
            Node<T> *temp = fro;
            if(fro==nullptr){
                cout<<"[msg]Queue is empty."<<endl;
                return;
            } 
            cout<<"Elements in Circular Queue are: "; 
            while (temp->getlink() != fro) 
            { 
                cout<<temp->getdata()<<" "; 
                temp = temp->getlink(); 
            } 
            cout<<temp->getdata()<<endl; 
        } 
}; 
class Pair{
    public:
        Pair():first(-1),second(-1){};
        Pair(int f, int s):first(f),second(s){};
        int first;
        int second;
        bool operator==(const Pair &comp) const
        {
            if (this->first == comp.first&&this->second == comp.second) return true;
            else return false;
        }
};
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
    'L': robot current position
    */
    public:
        
        cell_state():c(-1),r(-1),status('0'),rank(-1){};
        cell_state(int p1, int p2, char s):r(p1),c(p2),status(s),rank(-1){};

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
        int getrank(){
            return rank;
        }
        void changestate(char news){
            status = news;
        }
        void setc(int c){
            this->c = c;
        }
        void setr(int r){
            this->r = r;
        }
};
class Map{
    private:
        int unclean;
        cell_state* R;
        int col_num;
        int row_num;
        int max_step;
        int index_R;
        int index_C;
        int L_r;
        int L_c;
    public:
        Map(fstream &fin){
            char s;
            unclean=0;
            fin>>row_num;
            fin>>col_num;
            fin>>max_step;
            R = new cell_state[row_num*col_num];
            for(int i =0;i<row_num;i++){
                for(int j =0;j<col_num;j++){
                    fin>>s;
                    R[i*col_num+j].changestate(s);
                    if(s=='0')unclean++;
                    if(s=='R'){
                        index_R = i;
                        L_r = i;
                        index_C = j;
                        L_c = j;
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
                    cout<<R[i*col_num+j].getstatus()<<" ";
                }
                cout<<endl;
            }
        }
        void show_each_rank(){
            for(int i =0;i<row_num;i++){
                for(int j =0;j<col_num;j++){
                    if(R[i*col_num+j].getrank()-10<0&&R[i*col_num+j].getrank()!=-1){
                        cout<<" "<<R[i*col_num+j].getrank()<<" ";
                    }
                    else
                        cout<<R[i*col_num+j].getrank()<<" ";
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
        void R_where(){
            cout<<"R("<<index_R<<","<<index_C<<")";
        }
        int R_indr(){
            return index_R;
        }
        int R_indc(){
            return index_C;
        }
        int getL_r(){
            return L_r;
        }
        int getL_c(){
            return L_c;
        }
        char whatstatus(int r, int c){
            return R[r*col_num+c].getstatus();
        }
        int whatrank(int r, int c){
            return R[r*col_num+c].getrank();
        }
        void setrank(int r, int c, int rk){
            R[r*col_num+c].setrank(rk);
        }
        void construct_order(int r, int c, int n){
            int next_n=n;
            Queue<Pair> *q = new Queue<Pair>;
            Queue<Pair> *q_next = new Queue<Pair>;
            Queue<Pair> *q_record = new Queue<Pair>;
            q_next->push(Pair(r,c));
            while(1){
                delete q;
                q = q_next;
                q_next = new Queue<Pair>;
                if(q->isEmpty()==1)return;
                next_n=next_n+1;
                while(q->isEmpty()==0){
                    int r_tmp = q->front().first;
                    int c_tmp = q->front().second;
                    
                    if(whatrank(r_tmp, c_tmp)==-1&&whatstatus(r_tmp,c_tmp)!='1'){
                        setrank(r_tmp, c_tmp, next_n);
                    }
                    q_record->push(q->front());
                    q->pop();
                    //down
                    if((r_tmp+1<row_num)){
                        if(q_record->find(Pair(r_tmp+1, c_tmp))==0&&whatstatus(r_tmp+1,c_tmp)!='1')q_next->push(Pair(r_tmp+1, c_tmp));
                    }
                    //up
                    if((r_tmp-1)>=0){
                        if(q_record->find(Pair(r_tmp-1, c_tmp))==0&&whatstatus(r_tmp-1,c_tmp)!='1')q_next->push(Pair(r_tmp-1, c_tmp));
                    } 
                    //left
                    if((c_tmp-1)>=0){
                        if(q_record->find(Pair(r_tmp, c_tmp-1))==0&&whatstatus(r_tmp,c_tmp-1)!='1'){
                            q_next->push(Pair(r_tmp, c_tmp-1));
                        }
                    }
                    if((c_tmp+1)<col_num){
                        if(q_record->find(Pair(r_tmp, c_tmp+1))==0&&whatstatus(r_tmp,c_tmp+1)!='1')q_next->push(Pair(r_tmp, c_tmp+1));
                    }   
                } 
            }
        }
};
int main(){
    fstream fin;
    fstream fout;
    Map *m;
    fin.open("map.data",ios::in);
    fout.open("step.output",ios::out);
    m=new Map(fin);
    m->show_whole_map();
    m->show_unclean();
    m->show_maxstep();
    m->R_where();
    cout<<endl;
    m->show_each_rank();
    cout<<endl;
    m->construct_order(m->getL_r(), m->getL_c(), 0);
    m->show_each_rank();

    return 0;
}