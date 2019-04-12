#include <bits/stdc++.h>
#include <windows.h>>
using namespace std;

struct info
{
	int proc_num,proc_id,proc_arrival;
	int proc_burst, Priority, proc_Finish, proc_Remaining, proc_Waiting;
	int proc_Start, Reproc_Start;

};

struct info current;
typedef struct info P_d ;

bool idsort(const P_d& x , const P_d& y)
{
	return x.proc_id < y.proc_id;
}

bool arrivalsort( const P_d& x ,const P_d& y)
{
	if(x.proc_arrival < y.proc_arrival)
		return true;
	else if(x.proc_arrival > y.proc_arrival)
		return false;
	if(x.Priority < y.Priority)
		return true;
	else if(x.Priority > y.Priority)
		return false;
	if(x.proc_id < y.proc_id)
		return true;

	return false;
}


bool proc_numsort( const P_d& x ,const P_d& y)
{
	return x.proc_num < y.proc_num;
}

struct comPare
{
	bool operator()(const P_d& x ,const P_d& y)
	{
		if( x.Priority > y.Priority )
			return true;
		else if( x.Priority < y.Priority )
			return false;
		if( x.proc_id > y.proc_id )
			return true;

		return false;

	}

};


void my_check(vector<P_d> mv)
{
	for(unsigned int i= 0; i < mv.size() ;i++)
	{
		cout<<" proc_id :"<<mv[i].proc_id<<" _time : "<<mv[i].proc_arrival<<" proc_burst : "<<mv[i].proc_burst<<" Priority : "<<mv[i].Priority<<endl;
	}

}

int main()
{
    int pass;
    system("Color 2B");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout<<"MLFQ implementation\nImplemented by Nishant\nRoll no. 7\nSection K17QN\n\nEnter the password to begin implementation\n";
    cin>>pass;
    if(pass==11705503) cout<<"\nPass is correct! Granted access\n\n";
    else exit(1);


	int i;
	vector< P_d > input;
	vector<P_d> input_copy;
	P_d temp;
	int pq_process = 0;
	int rq_process = 0;
	int proc_arrival;
	int proc_burst;
	int proc_id;
	int Priority;
	int n;
	int clock;
	int total_exection_time = 0;
	cout<<" Enter the number of processes\n";
	cin>>n;
	for( i= 0; i< n; i++ )
	{
	    cout<<" Enter :-\n#1 Process ID \n#2 Arrival Time \n#3 Burst Time \n#4 Priority\n";
		cin>>proc_id>>proc_arrival>>proc_burst>>Priority;
		temp.proc_num = i+1;
		temp.proc_arrival = proc_arrival;
		temp.proc_burst = proc_burst;
		temp.proc_Remaining  = proc_burst;
		temp.proc_id = proc_id;
		temp.Priority = Priority;
		input.push_back(temp);
	}
	input_copy = input;
	sort( input.begin(), input.end(), arrivalsort );


    total_exection_time = total_exection_time + input[0].proc_arrival;
    for( i= 0 ;i< n; i++ )
    {
    	if( total_exection_time >= input[i].proc_arrival )
    	{
    		total_exection_time = total_exection_time +input[i].proc_burst;
    	}
    	else
    	{
    		int diff = (input[i].proc_arrival - total_exection_time);
    		total_exection_time = total_exection_time + diff + proc_burst;

    	}
    }

	int Ghant[total_exection_time]={0};
	for( i= 0; i< total_exection_time; i++ )
	{
		Ghant[i]=-1;
	}


	priority_queue < P_d ,vector<info> ,comPare> pq;

	queue< P_d > rq;
	int cpu_state = 0;
	int quantum = 4 ;
	current.proc_id = -2;
	current.Priority = 999999;

	for ( clock = 0; clock< total_exection_time; clock++ )
	{

		for( int j = 0; j< n ; j++ )
		{
			if(clock == input[j].proc_arrival)
			{
				pq.push(input[j]);
			}
		}


		if(cpu_state == 0)
		{
			if(!pq.empty())
			{
				current = pq.top();
				cpu_state = 1;
				pq_process = 1;
				pq.pop();
				quantum = 4;
			}
			else if(!rq.empty())
			{
				current = rq.front();
				cpu_state = 1;
				rq_process = 1;
				rq.pop();
				quantum = 4;
			}
		}
		else if(cpu_state == 1)
		{
			if(pq_process == 1 && (!pq.empty()))
			{
				if(pq.top().Priority < current.Priority )
				{
					rq.push(current);
					current = pq.top();
					pq.pop();
					quantum = 4;
				}
			}
			else if(rq_process == 1 && (!pq.empty()))
			{
				rq.push(current);
				current = pq.top();
				pq.pop();
				rq_process = 0;
				pq_process = 1;
				quantum = 4 ;
			}


		}


		if(current.proc_id != -2)
		{
			current.proc_Remaining --;
			quantum--;
			Ghant[clock] = current.proc_id;
			if(current.proc_Remaining  == 0)
			{
				cpu_state = 0 ;
				quantum = 4 ;
				current.proc_id = -2;
				current.Priority = 999999;
				rq_process = 0;
				pq_process = 0;
			}
			else if(quantum == 0 )
			{
				rq.push(current);
				current.proc_id = -2;
				current.Priority = 999999;
				rq_process = 0;
				pq_process = 0;
				cpu_state=0;

			}

		}

	}


	sort( input.begin(), input.end(), idsort );

	for(int i=0;i<n;i++)
	{
		for(int k=total_exection_time;k>=0;k--)
		{
			if(Ghant[k]==i+1)
			{
				input[i].proc_Finish=k+1;
				break;

			}
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int k=0;k<total_exection_time;k++)
		{

			if(Ghant[k]==i+1)
			{
				input[i].proc_Start=k;
				break;
			}
		}
	}

	sort( input.begin(), input.end(), proc_numsort );

	for(int i=0;i<n;i++)
	{
		input[i].Reproc_Start=input[i].proc_Start-input[i].proc_arrival;
		input[i].proc_Waiting=(input[i].proc_Finish-input[i].proc_arrival)-input[i].proc_burst;

	}

	for(int i=0;i<n;i++)
	{
		cout<<input[i].proc_id<<" "<<input[i].Reproc_Start<<" "<<input[i].proc_Finish<<" "<<input[i].proc_Waiting<<endl;

	}
	return 0;
}
