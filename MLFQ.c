{\rtf1\ansi\ansicpg1252\deff0\nouicompat\deflang1033{\fonttbl{\f0\fnil\fcharset0 Calibri;}}
{\*\generator Riched20 10.0.17763}\viewkind4\uc1 
\pard\sa200\sl276\slmult1\f0\fs22\lang9 #include <bits/stdc++.h>\par
using namespace std;\par
\par
struct Process_Data\par
\{\par
\par
\tab int arrival;\par
\tab int burst;\par
\tab int Num;\par
\tab int Pid;\par
\tab int Priority;\par
\tab int finish;\par
\tab int remain;\par
\tab int wait;\par
\tab int start;\par
\tab int Restart;\par
\par
\};\par
\par
struct Process_Data current;\par
typedef struct Process_Data P_d ;\par
\par
bool idsort(const P_d& x , const P_d& y)\par
\{\par
\tab return x.Pid < y.Pid;\par
\}\par
/** Sorting on the base of arrival time if that match then on Priority of Priority also  match than on the base of Process Id**/\par
bool arrivalsort( const P_d& x ,const P_d& y)\par
\{\par
\tab if(x.arrival < y.arrival)\par
\tab\tab return true;\par
\tab else if(x.arrival > y.arrival)\par
\tab\tab return false;\par
\tab if(x.Priority < y.Priority)\par
\tab\tab return true;\par
\tab else if(x.Priority > y.Priority)\par
\tab\tab return false;\par
\tab if(x.Pid < y.Pid)\par
\tab\tab return true;\par
\par
\tab return false;\par
\}\par
\par
\par
bool Numsort( const P_d& x ,const P_d& y)\par
\{\par
\tab return x.Num < y.Num;\par
\}\par
/*Sorting on the base of Priority if that same then on the base of PID*/\par
struct comPare\par
\{\par
\tab bool operator()(const P_d& x ,const P_d& y)\par
\tab\{\par
\tab\tab if( x.Priority > y.Priority )\par
\tab\tab\tab return true;\par
\tab\tab else if( x.Priority < y.Priority )\par
\tab\tab\tab return false;\par
\tab\tab if( x.Pid > y.Pid )\par
\tab\tab\tab return true;\par
\par
\tab\tab return false;\par
\par
\tab\}\par
\par
\};\par
\par
/**To check the Input **/\par
void my_check(vector<P_d> mv)\par
\{\par
\tab for(unsigned int i= 0; i < mv.size() ;i++)\par
\tab\{\par
\tab\tab cout<<" Pid :"<<mv[i].Pid<<" _time : "<<mv[i].arrival<<" burst : "<<mv[i].burst<<" Priority : "<<mv[i].Priority<<endl;\par
\tab\}\par
\par
\}\par
\par
int main()\par
\{\par
\tab int i;\par
\tab vector< P_d > input;\par
\tab vector<P_d> input_copy;\par
\tab P_d temp;\par
\tab int pq_process = 0; // for PQ process\par
\tab int rq_process = 0; // for RQ process\par
\tab int arrival;\par
\tab int burst;\par
\tab int Pid;\par
\tab int Priority;\par
\tab int n;\par
\tab int clock;\par
\tab int total_exection_time = 0;\par
\tab cin>>n;\par
\tab for( i= 0; i< n; i++ )\par
\tab\{\par
\tab\tab cin>>Pid>>arrival>>burst>>Priority;\par
\tab\tab temp.Num = i+1;\par
\tab\tab temp.arrival = arrival;\par
\tab\tab temp.burst = burst;\par
\tab\tab temp.remain = burst;\par
\tab\tab temp.Pid = Pid;\par
\tab\tab temp.Priority = Priority;\par
\tab\tab input.push_back(temp);\par
\tab\}\par
\tab input_copy = input;\par
\tab sort( input.begin(), input.end(), arrivalsort );\par
    //cout<<"arrivalsort : "<<endl;\par
    //my_check( input ); // To check the sort unomment it\par
    total_exection_time = total_exection_time + input[0].arrival;\par
    for( i= 0 ;i< n; i++ )\par
    \{\par
    \tab if( total_exection_time >= input[i].arrival )\par
    \tab\{\par
    \tab\tab total_exection_time = total_exection_time +input[i].burst;\par
    \tab\}\par
    \tab else\par
    \tab\{\par
    \tab\tab int diff = (input[i].arrival - total_exection_time);\par
    \tab\tab total_exection_time = total_exection_time + diff + burst;\par
\par
    \tab\}\par
    \}\par
\par
\tab int Ghant[total_exection_time]=\{0\}; //Ghant Chart\par
\tab for( i= 0; i< total_exection_time; i++ )\par
\tab\{\par
\tab\tab Ghant[i]=-1;\par
\tab\}\par
\tab //cout<<"total_exection_time : "<<total_exection_time<<endl;\par
\par
\tab priority_queue < P_d ,vector<Process_Data> ,comPare> pq; //Priority Queue PQ\par
\par
\tab queue< P_d > rq; //Round Robin Queue RQ\par
\tab int cpu_state = 0; //idle if 0 then Idle if 1 the Busy\par
\tab int quantum = 4 ; //Time Quantum\par
\tab current.Pid = -2;\par
\tab current.Priority = 999999;\par
\par
\tab for ( clock = 0; clock< total_exection_time; clock++ )\par
\tab\{\par
\tab\tab /**Insert the process with same Arrival time in Priority Queue**/\par
\tab\tab for( int j = 0; j< n ; j++ )\par
\tab\tab\{\par
\tab\tab\tab if(clock == input[j].arrival)\par
\tab\tab\tab\{\par
\tab\tab\tab\tab pq.push(input[j]);\par
\tab\tab\tab\}\par
\tab\tab\}\par
\par
\par
\tab\tab if(cpu_state == 0) //If CPU idle\par
\tab\tab\{\par
\tab\tab\tab if(!pq.empty())\par
\tab\tab\tab\{\par
\tab\tab\tab\tab current = pq.top();\par
\tab\tab\tab\tab cpu_state = 1;\par
\tab\tab\tab\tab pq_process = 1;\par
\tab\tab\tab\tab pq.pop();\par
\tab\tab\tab\tab quantum = 4;\par
\tab\tab\tab\}\par
\tab\tab\tab else if(!rq.empty())\par
\tab\tab\tab\{\par
\tab\tab\tab\tab current = rq.front();\par
\tab\tab\tab\tab cpu_state = 1;\par
\tab\tab\tab\tab rq_process = 1;\par
\tab\tab\tab\tab rq.pop();\par
\tab\tab\tab\tab quantum = 4;\par
\tab\tab\tab\}\par
\tab\tab\}\par
\tab\tab else if(cpu_state == 1) //If cpu has any procss\par
\tab\tab\{\par
\tab\tab\tab if(pq_process == 1 && (!pq.empty()))\par
\tab\tab\tab\{\par
\tab\tab\tab\tab if(pq.top().Priority < current.Priority ) //If new process has high priority\par
\tab\tab\tab\tab\{\par
\tab\tab\tab\tab\tab rq.push(current); //push current in RQ\par
\tab\tab\tab\tab\tab current = pq.top();\par
\tab\tab\tab\tab\tab pq.pop();\par
\tab\tab\tab\tab\tab quantum = 4;\par
\tab\tab\tab\tab\}\par
\tab\tab\tab\}\par
\tab\tab\tab else if(rq_process == 1 && (!pq.empty())) //If process is from RQ and new process come  in PQ\par
\tab\tab\tab\{\par
\tab\tab\tab\tab rq.push(current);\par
\tab\tab\tab\tab current = pq.top();\par
\tab\tab\tab\tab pq.pop();\par
\tab\tab\tab\tab rq_process = 0;\par
\tab\tab\tab\tab pq_process = 1;\par
\tab\tab\tab\tab quantum = 4 ;\par
\tab\tab\tab\}\par
\par
\par
\tab\tab\}\par
\par
\par
\tab\tab if(current.Pid != -2) // Process Execution\par
\tab\tab\{\par
\tab\tab\tab current.remain--;\par
\tab\tab\tab quantum--;\par
\tab\tab\tab Ghant[clock] = current.Pid;\par
\tab\tab\tab if(current.remain == 0) //If process Finish\par
\tab\tab\tab\{\par
\tab\tab\tab\tab cpu_state = 0 ;\par
\tab\tab\tab\tab quantum = 4 ;\par
\tab\tab\tab\tab current.Pid = -2;\par
\tab\tab\tab\tab current.Priority = 999999;\par
\tab\tab\tab\tab rq_process = 0;\par
\tab\tab\tab\tab pq_process = 0;\par
\tab\tab\tab\}\par
\tab\tab\tab else if(quantum == 0 ) //If time Qunatum of a current running process Finish\par
\tab\tab\tab\{\par
\tab\tab\tab\tab rq.push(current);\par
\tab\tab\tab\tab current.Pid = -2;\par
\tab\tab\tab\tab current.Priority = 999999;\par
\tab\tab\tab\tab rq_process = 0;\par
\tab\tab\tab\tab pq_process = 0;\par
\tab\tab\tab\tab cpu_state=0;\par
\par
\tab\tab\tab\}\par
\par
\tab\tab\}\par
\par
\tab\}\par
\par
\par
\tab sort( input.begin(), input.end(), idsort );\par
\par
\tab for(int i=0;i<n;i++)\par
\tab\{\par
\tab\tab for(int k=total_exection_time;k>=0;k--)\par
\tab\tab\{\par
\tab\tab\tab if(Ghant[k]==i+1)\par
\tab\tab\tab\{\par
\tab\tab\tab\tab input[i].finish=k+1;\par
\tab\tab\tab\tab break;\par
\par
\tab\tab\tab\}\par
\tab\tab\}\par
\tab\}\par
\tab for(int i=0;i<n;i++)\par
\tab\{\par
\tab\tab for(int k=0;k<total_exection_time;k++)\par
\tab\tab\{\par
\par
\tab\tab\tab if(Ghant[k]==i+1)\par
\tab\tab\tab\{\par
\tab\tab\tab\tab input[i].start=k;\par
\tab\tab\tab\tab break;\par
\tab\tab\tab\}\par
\tab\tab\}\par
\tab\}\par
\par
\tab sort( input.begin(), input.end(), Numsort );\par
\par
\tab for(int i=0;i<n;i++)\par
\tab\{\par
\tab\tab input[i].Restart=input[i].start-input[i].arrival;\par
\tab\tab input[i].wait=(input[i].finish-input[i].arrival)-input[i].burst;\par
\par
\tab\}\par
\par
\tab for(int i=0;i<n;i++)\par
\tab\{\par
\tab\tab cout<<input[i].Pid<<" "<<input[i].Restart<<" "<<input[i].finish<<" "<<input[i].wait<<endl;\par
\par
\tab\}\par
\tab return 0;\par
\}\par
}
 