
#include<iostream>
#include <fstream>
#include <time.h>
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
class Stack
{
    private:
        Node<T>* t = nullptr;
    public:
        void push(T val) {
            Node<T>* newnode = new Node<T>; 
            newnode->setdata(val); 
            newnode->setlink(t); 
            t = newnode; 
        }
        void pop() {
            if(t==nullptr)
                cout<<"Stack Underflow"<<endl;
            else {
                Node<T> *kill = t;
                t = t->getlink();
                delete kill;
            }
        }
        void display() {
            Node<T>* ptr;
            int cnt = 0;
            if(t==nullptr)
                cout<<"stack is empty";
            else {   
                
                ptr = t; 
                cout<<"Stack elements are: "<<endl;
                while (ptr != NULL) { 
                    cnt ++;
                    cout<< ptr->getdata(); 
                    ptr = ptr->getlink(); 
                } 
            }
            cout<<"element number:"<<cnt;
            cout<<endl;
        }
        bool isEmpty(){
            if(t==nullptr)return true;
            else return false;
        }
        bool find(T d) {
            Node<T>* ptr;
            if(t==nullptr)
                return false;
            else {   
                ptr = t; 
                while (ptr != NULL) { 
                    if(ptr->getdata()==d)return true; 
                    ptr = ptr->getlink(); 
                } 
            }
            return false;
        }
        T top(){
            return t->getdata();
        }
        void remove(T d){
            Node<T>* ptr;
            Node<T>* pre = nullptr;
            if(t==nullptr)
                return;
            else {   
                ptr = t; 
                while (ptr != NULL) { 
                    if(ptr->getdata()==d){
                        if(pre==nullptr){
                            pop();
                        }else{
                            pre->setlink(ptr->getlink());
                            delete ptr;
                        }
                        return;
                    } 
                    pre = ptr;
                    ptr = ptr->getlink(); 
                } 
            }
            return;
        }
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
        bool find(T d){ //1 do find 0 not find
            Node<T> *temp = fro;
            if(fro==nullptr){
                return false;
            } 
            while (temp->getlink() != fro) 
            { 
                if(temp->getdata()==d){
                    return true;
                } 
                temp = temp->getlink(); 
            } 
            if(temp->getdata()==d){
                    return true;
            }
            return false;
        }
        void pop(){
            if(isEmpty())return;
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
        void display() 
        { 
            Node<T> *temp = fro;
            if(fro==nullptr){
                cout<<"[msg]Queue is empty."<<endl;
                return;
            } 
            cout<<"Elements in Circular Queue are: "<<endl; 
            while (temp->getlink() != fro) 
            { 
                cout<<temp->getdata(); 
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
        ostream& operator<<(ostream& os)
        {
            os << first << " " << second <<" "<< endl;
            return os;
        }
};
ostream& operator<<(ostream& os, const Pair&n)
{
    os << n.first << " " << n.second <<" "<< endl;
    return os;
}
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
            fin>>row_num;
            fin>>col_num;
            fin>>max_step;
            R = new cell_state[row_num*col_num];
            for(int i =0;i<row_num;i++){
                for(int j =0;j<col_num;j++){
                    fin>>s;
                    R[i*col_num+j].changestate(s);
                    if(s=='R'){
                        index_R = i;
                        L_r = i;
                        index_C = j;
                        L_c = j;
                    }
                }
            }
        }
        void map_out(fstream &fout){
            for(int i =0;i<row_num;i++){
                for(int j =0;j<col_num;j++){
                    fout<<R[i*col_num+j].getstatus()<<" ";
                }
                fout<<endl;
            }
        
        }
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

        void show_maxstep(){
            cout<<"maxstep:"<<max_step<<endl;
        }
        void R_where(){
            cout<<"R("<<index_R<<","<<index_C<<")";
        }
        void L_where(){
            cout<<"L("<<L_r<<","<<L_c<<")";
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
        char whatstatus_pair(Pair p){
            return R[p.first*col_num+p.second].getstatus();
        }
        int whatrank_pair(Pair p){
            return R[p.first*col_num+p.second].getrank();
        }
        int whatrank(int r, int c){
            return R[r*col_num+c].getrank();
        }
        void setrank(int r, int c, int rk){
            R[r*col_num+c].setrank(rk);
        }
        void AfterClean(Pair p){
            R[p.first*col_num+p.second].changestate('C');
        }
        Stack<Pair>* construct_order(){
            int next_n=0;
            Queue<Pair> *q = new Queue<Pair>;
            Queue<Pair> *q_next = new Queue<Pair>;
            Stack<Pair> *s_record = new Stack<Pair>;
            q_next->push(Pair(L_r,L_c));
            while(1){
                delete q;
                q = q_next;
                q_next = new Queue<Pair>;
                if(q->isEmpty()==1)break;
                
                while(q->isEmpty()==0){
                    int r_tmp = q->front().first;
                    int c_tmp = q->front().second;
                    setrank(r_tmp, c_tmp, next_n);
                    s_record->push(q->front());
                    q->pop();
                    //down
                    if((r_tmp+1<row_num)){
                        if(q_next->find(Pair(r_tmp+1, c_tmp))==0 &&whatrank(r_tmp+1, c_tmp)==-1&&whatstatus(r_tmp+1,c_tmp)!='1')
                            q_next->push(Pair(r_tmp+1, c_tmp));
                    }
                    //up
                    if((r_tmp-1)>=0){
                        if(q_next->find(Pair(r_tmp-1, c_tmp))==0 &&whatrank(r_tmp-1, c_tmp)==-1&&whatstatus(r_tmp-1,c_tmp)!='1')
                            q_next->push(Pair(r_tmp-1, c_tmp));
                    } 
                    //left
                    if((c_tmp-1)>=0){
                        if(q_next->find(Pair(r_tmp, c_tmp-1))==0 &&whatrank(r_tmp, c_tmp-1)==-1&&whatstatus(r_tmp,c_tmp-1)!='1')
                            q_next->push(Pair(r_tmp, c_tmp-1));
                    }
                    //right
                    if((c_tmp+1)<col_num){
                        if(q_next->find(Pair(r_tmp, c_tmp+1))==0 &&whatrank(r_tmp, c_tmp+1)==-1&&whatstatus(r_tmp,c_tmp+1)!='1')
                            q_next->push(Pair(r_tmp, c_tmp+1));
                    }   
                } 
                next_n=next_n+1;
                //cout<<">>"<<next_n<<endl;
            }
            delete q;
            delete q_next;
            return s_record;
        }
        void setL(Pair p){
            L_r = p.first;
            L_c = p.second;
            R[L_r*col_num+L_c].changestate('L');
        }
};
int abs(int a){
    if(a<0) return -a;
    else return a;
}
int pos_dist(Pair a, Pair b){
    return (abs(a.first-b.first)+abs(a.second-b.second));
}
class soln{
    public:
        Queue<Pair> q;
        int step;
        void push(Pair p){
            q.push(p);
            step=step+1;
        }
        void display(){
            q.display();
        }
};
Stack<Pair> * Farthest(Stack<Pair> *s_filthy, Map *m){
    Stack<Pair> *path = new Stack<Pair>;
    
    path->push(s_filthy->top());
    s_filthy->pop();
    int ind1 = path->top().first;
    int ind2 = path->top().second;
    
    while(!(ind1==m->R_indr()&&ind2==m->R_indc()))
    {
        Pair output_pos = Pair(-1,-1);
        int output_pos_d =-1;
        int tmp_rank = m->whatrank(ind1,ind2);
        //cout<<ind1<<","<<ind2<<endl;
        //up
        if(ind1-1>=0){
            char sta = m->whatstatus(ind1-1,ind2);
            if(sta!='1' && sta!='C' && m->whatrank(ind1-1,ind2)<tmp_rank){
                if(output_pos_d==-1){
                    output_pos = Pair(ind1-1,ind2);
                    output_pos_d = pos_dist(Pair(ind1-1,ind2), Pair(m->R_indr(), m->R_indc()));
                }else{
                    if(output_pos_d >pos_dist(Pair(ind1-1,ind2), Pair(m->R_indr(), m->R_indc()))){
                        output_pos = Pair(ind1-1,ind2);
                        output_pos_d = pos_dist(Pair(ind1-1,ind2), Pair(m->R_indr(), m->R_indc()));
                    }
                }
            }
        }
        //down
        if(ind1+1<m->getrow_num()){
            char sta = m->whatstatus(ind1+1,ind2);
            if(sta!='1' && sta!='C'&& m->whatrank(ind1+1,ind2)<tmp_rank){
                if(output_pos_d==-1){
                    output_pos = Pair(ind1+1,ind2);
                    output_pos_d = pos_dist(Pair(ind1+1,ind2), Pair(m->R_indr(), m->R_indc()));
                }else{
                    if(output_pos_d >pos_dist(Pair(ind1+1,ind2), Pair(m->R_indr(), m->R_indc()))){
                        output_pos = Pair(ind1+1,ind2);
                        output_pos_d = pos_dist(Pair(ind1+1,ind2), Pair(m->R_indr(), m->R_indc()));
                    }
                }
            }
        }
        //left
        if(ind2-1>=0){
            char sta = m->whatstatus(ind1,ind2-1);
            if(sta!='1' && sta!='C'&& m->whatrank(ind1,ind2-1)<tmp_rank){
                if(output_pos_d==-1){
                    output_pos = Pair(ind1,ind2-1);
                    output_pos_d = pos_dist(Pair(ind1,ind2-1), Pair(m->R_indr(), m->R_indc()));
                }else{
                    if(output_pos_d >pos_dist(Pair(ind1,ind2-1), Pair(m->R_indr(), m->R_indc()))){
                        output_pos = Pair(ind1,ind2-1);
                        output_pos_d = pos_dist(Pair(ind1,ind2-1), Pair(m->R_indr(), m->R_indc()));
                    }
                }
            }
        }
        //right
        if(ind2+1<m->getcol_num()){
            char sta = m->whatstatus(ind1,ind2+1);
            if(sta!='1' && sta!='C'&& m->whatrank(ind1,ind2+1)<tmp_rank){
                if(output_pos_d==-1){
                    output_pos = Pair(ind1,ind2+1);
                    output_pos_d = pos_dist(Pair(ind1,ind2+1), Pair(m->R_indr(), m->R_indc()));
                }else{
                    if(output_pos_d >pos_dist(Pair(ind1,ind2+1), Pair(m->R_indr(), m->R_indc()))){
                        output_pos = Pair(ind1,ind2+1);
                        output_pos_d = pos_dist(Pair(ind1,ind2+1), Pair(m->R_indr(), m->R_indc()));
                    }
                }
            }
        }
        
        if(output_pos_d==-1){
            if(ind1-1>=0){
                if(m->whatstatus(ind1-1,ind2)!='1'&& m->whatrank(ind1-1,ind2)<tmp_rank){
                    if(output_pos_d==-1){
                        output_pos = Pair(ind1-1,ind2);
                        output_pos_d = pos_dist(Pair(ind1-1,ind2), Pair(m->R_indr(), m->R_indc()));
                    }else{
                        if(output_pos_d >pos_dist(Pair(ind1-1,ind2), Pair(m->R_indr(), m->R_indc()))){
                            output_pos = Pair(ind1-1,ind2);
                            output_pos_d = pos_dist(Pair(ind1-1,ind2), Pair(m->R_indr(), m->R_indc()));
                        }
                    }
                    
                }
            }
            //down
            if(ind1+1<m->getrow_num()){
                if(m->whatstatus(ind1+1,ind2)!='1'&& m->whatrank(ind1+1,ind2)<tmp_rank){
                    if(output_pos_d==-1){
                        output_pos = Pair(ind1+1,ind2);
                        output_pos_d = pos_dist(Pair(ind1+1,ind2), Pair(m->R_indr(), m->R_indc()));
                    }else{
                        if(output_pos_d >pos_dist(Pair(ind1+1,ind2), Pair(m->R_indr(), m->R_indc()))){
                            output_pos = Pair(ind1+1,ind2);
                            output_pos_d = pos_dist(Pair(ind1+1,ind2), Pair(m->R_indr(), m->R_indc()));
                        }
                    }
                    
                }
            }
            //left
            if(ind2-1>=0){
                if(m->whatstatus(ind1,ind2-1)!='1'&& m->whatrank(ind1,ind2-1)<tmp_rank){
                    
                    if(output_pos_d==-1){
                        output_pos = Pair(ind1,ind2-1);
                        output_pos_d = pos_dist(Pair(ind1,ind2-1), Pair(m->R_indr(), m->R_indc()));
                    }else{
                        if(output_pos_d >pos_dist(Pair(ind1,ind2-1), Pair(m->R_indr(), m->R_indc()))){
                            output_pos = Pair(ind1,ind2-1);
                            output_pos_d = pos_dist(Pair(ind1,ind2-1), Pair(m->R_indr(), m->R_indc()));
                        }
                    }
                    
                }
            }
            //right
            if(ind2+1<m->getcol_num()){
                if(m->whatstatus(ind1,ind2+1)!='1'&& m->whatrank(ind1,ind2+1)<tmp_rank){
                    
                    if(output_pos_d==-1){
                        output_pos = Pair(ind1,ind2+1);
                        output_pos_d = pos_dist(Pair(ind1,ind2+1), Pair(m->R_indr(), m->R_indc()));
                    }else{
                        if(output_pos_d >pos_dist(Pair(ind1,ind2+1), Pair(m->R_indr(), m->R_indc()))){
                            output_pos = Pair(ind1,ind2+1);
                            output_pos_d = pos_dist(Pair(ind1,ind2+1), Pair(m->R_indr(), m->R_indc()));
                        }
                    }
                    
                }
            }    
        }
        path->push(output_pos);
        ind1=path->top().first;
        ind2=path->top().second;
        m->AfterClean(output_pos);
    }
    return path;
}
void ansout(soln &ans, fstream &fout){
    fout<<ans.step;
    fout<<endl;
    while(ans.q.isEmpty()==0){
        fout<<ans.q.front();
        ans.q.pop();
    }
}

Pair next_step(int &battery, Map*m){
    int ind1=m->getL_r();
    int ind2=m->getL_c();
    int rank_L = m->whatrank(ind1,ind2);
    Queue<Pair> *dir = new Queue<Pair>;
    int elem_num=0;
    battery--;
    bool r=0;
    bool d=0;
    bool u=0;
    bool l=0;
    if(rank_L+1<=battery){
        //rank up
        //up
        if(ind1-1>=0&&m->whatstatus(ind1-1,ind2)!='C'){
            
            if(m->whatrank(ind1-1,ind2)>rank_L){
                dir->push(Pair(ind1-1, ind2));
                elem_num++;
            }
        }
        //down
        if(ind1+1<m->getrow_num()&&m->whatstatus(ind1+1,ind2)!='C'){
            if(m->whatrank(ind1+1,ind2)>rank_L){
                dir->push(Pair(ind1+1, ind2));
                elem_num++;
            }
        }
        //left
        if(ind2-1>=0&&m->whatstatus(ind1,ind2-1)!='C'){
            if(m->whatrank(ind1,ind2-1)>rank_L){
                dir->push(Pair(ind1, ind2-1));
                elem_num++;
            }
        }
        //right
        if(ind2+1<m->getcol_num()&&m->whatstatus(ind1,ind2+1)!='C'){
            if(m->whatrank(ind1,ind2+1)>rank_L){
                dir->push(Pair(ind1, ind2+1));
                elem_num++;
            }
        }
        if(elem_num>=1){
            Pair tmp=dir->front();
            if(elem_num!=1){
                int cmp = pos_dist(dir->front(), Pair(m->R_indr(),m->R_indc()));
                while(dir->isEmpty()==0){
                    if(pos_dist(dir->front(), Pair(m->R_indr(),m->R_indc()))>cmp)
                        tmp = dir->front();
                    dir->pop();
                }
            }
            delete dir;
            return tmp;
        }
    }
    
    //rank down
    //up
    if(ind1-1>=0&&m->whatrank(ind1-1,ind2)<rank_L&&m->whatstatus(ind1-1,ind2)!='1'){
        u =1;
        if(m->whatstatus(ind1-1,ind2)!='C'){
            dir->push(Pair(ind1-1, ind2));
            elem_num++;
        }
    }
    //down
    if(ind1+1<m->getrow_num() && m->whatrank(ind1+1,ind2)<rank_L && m->whatstatus(ind1+1,ind2)!='1'){
        d=1;
        if(m->whatstatus(ind1+1,ind2)!='C'){
            dir->push(Pair(ind1+1, ind2));
            elem_num++;
        }
    }
    //left
    if(ind2-1>=0 && m->whatrank(ind1,ind2-1)<rank_L && m->whatstatus(ind1,ind2-1)!='1'){
        l=1;
        if(m->whatstatus(ind1,ind2-1)!='C'){
            dir->push(Pair(ind1, ind2-1));
            elem_num++;
        }
    }
    //right
    if(ind2+1<m->getcol_num() &&m->whatrank(ind1,ind2+1)<rank_L&&m->whatstatus(ind1,ind2+1)!='1'){
        r=1;
        if(m->whatstatus(ind1,ind2+1)!='C'){
            dir->push(Pair(ind1, ind2+1));
            elem_num++;
        }
    }
    if(elem_num>=1){
        Pair tmp=dir->front();
        if(elem_num!=1){
            int cmp = pos_dist(dir->front(), Pair(m->R_indr(),m->R_indc()));
            while(dir->isEmpty()==0){
                if(pos_dist(dir->front(), Pair(m->R_indr(),m->R_indc()))>cmp)
                    tmp = dir->front();
                dir->pop();
            }
        }
        delete dir;
        return tmp;   
    }
    //rank down without 'C'
    //up
    if(u){
        dir->push(Pair(ind1-1, ind2));
        elem_num++;
        
    }
    //down
    if(d){
        dir->push(Pair(ind1+1, ind2));
        elem_num++;
        
    }
    //left
    if(l){
        dir->push(Pair(ind1, ind2-1));
        elem_num++;
    }
    //right
    if(r){
        dir->push(Pair(ind1, ind2+1));
        elem_num++;
    }
    if(elem_num>=1){
        Pair tmp=dir->front();
        if(elem_num!=1){
            int cmp = pos_dist(dir->front(), Pair(m->R_indr(),m->R_indc()));
            while(dir->isEmpty()==0){
                if(pos_dist(dir->front(), Pair(m->R_indr(),m->R_indc()))<cmp)
                    tmp = dir->front();
                dir->pop();
            }
        }
        delete dir;
        return tmp;   
    }
    
    return Pair(-1,-1);
}
int main(){
    //double START,END;
    //double START_all, END_all;
    //START_all = clock();
    /*---要計算的程式效率區域---*/

    /*for test_all
    fstream fin_student;
    fin_student.open("student.testcase",ios::in);
    for(int iii=0;iii<70;iii++){//testcase_all
    string id = "106000240";
    fin_student>>id;
    */
    fstream fin;
    fstream fout;
    fstream fout2;
    Stack<Pair> *s_filthy;
    Map *m;
    /*for test_all
    cout<<id<<endl;
    fin.open("Project2_Testcase/"+id+"_Testcase/floor.data",ios::in);
    fout.open("output/"+id+".path",ios::out);
    */
    fin.open("floor.data",ios::in);
    fout.open("final.path",ios::out);
    //fout2.open("map.output",ios::out);
    m=new Map(fin);
    //m->show_whole_map();
    //m->show_maxstep();
    //m->R_where();
    //m->L_where();
    std::cout<<endl;
    cout<<"[construct_order]"<<endl;
    s_filthy=m->construct_order();
    cout<<"[construct_order]done"<<endl;
    //m->show_each_rank();
    //init ans
    soln ans;
    ans.step = -1;
    ans.push(Pair(m->R_indr(),m->R_indc()));
    //________
    int battery;
    
    while(s_filthy->isEmpty()==0)
    {
        battery=m->getmax_step();
        //cout<<s_filthy->top();
        //cout<<"status:"<<m->whatstatus_pair(s_filthy->top())<<endl;
        battery = battery - m->whatrank_pair(s_filthy->top());

        cout<<"[Farthest]"<<endl;
        //START = clock();//test speed
        Stack<Pair> *path = Farthest(s_filthy,m);
        //start position pop()
        
        if(path->top().first==m->R_indr()&& path->top().second==m->R_indc()){
            path->pop();
        }
        while(path->isEmpty()==0){
            ans.push(path->top());
            //s_filthy->remove(path->top());//change_1111
            path->pop();
        }
        delete path;
        //END = clock();
        //cout << (END - START) / CLOCKS_PER_SEC <<"s"<< endl;
       
        cout<<"[nextstep]"<<endl;
        //START = clock();//test speed
        Pair nextp;
        m->AfterClean(Pair(m->getL_r(),m->getL_c()));
        m->setL(ans.q.back());
        do{
            nextp=next_step(battery,m);
            if(nextp==Pair(-1,-1))break;
            m->AfterClean(Pair(m->getL_r(),m->getL_c()));
            m->setL(nextp);
            ans.push(nextp);
        }while(!((m->getL_r()==m->R_indr()&&m->getL_c()==m->R_indc())));//del battery==0 change_1112
    
        //END = clock();
        //cout << (END - START) / CLOCKS_PER_SEC <<"s"<< endl;
        //return 0;//test speed
        while(s_filthy->isEmpty()==0&&m->whatstatus_pair(s_filthy->top())!='0'){
            s_filthy->pop();
        }
        

    }
    
    cout<<"[output]"<<endl;
    //START = clock();
    ansout(ans, fout);
    //m->map_out(fout2);
    //END = clock();
    //cout << (END - START) / CLOCKS_PER_SEC <<"s"<< endl;
    //END_all = clock();
    //cout << "total time:"<<(END_all - START_all) / CLOCKS_PER_SEC <<"s"<< endl;
    /*for test_a;;
    delete m;//testcase_all
    }//testcase_all
    */
    return 0;
}
