#include <iostream>
#include <queue>
#include <list>

using namespace std;

// struct that represents a process, contains all necessary attributes of a process
struct process{
	int id;
	int burst_time;
	int remaining_burst_time;
	int arrival_time;
	int response_time;
	int waiting_time;
	int start_time;
	int end_time;
};

// main function starts here
int main(){
	
	// 3 queue declarations for multilevel-feedback queue system
	queue<process> q0, q1, q2;
	
	/*
	2 list declarations,
	process_list contains all new processes, 
	finished_list contains all the processes that have completed their execution
	*/
	list<process> process_list, finished_list;
	
	// all necessary variables are declared here
	int num_of_processes;
	int total_burst_time = 0;
	int total_waiting_time = 0;
	int total_response_time = 0;
	int total_turnaround_time = 0;
	int time = 0;
	double average_waiting_time;
	double average_response_time;
	double average_turnaround_time;
	double throughput;
	
	// user input for number of processes
	cout << "Enter number of processes: ";
	cin >> num_of_processes;
	
	// for loop to take user input(burst time and arrival time) for all processes
	for(int i = 0; i < num_of_processes; i++){
		process p;
		p.id = i + 1;
		cout << "\n\t\t** Enter information for process " << p.id << " **\n";
		cout << "\nEnter burst time: ";
		cin >> p.burst_time;
		p.remaining_burst_time = p.burst_time;
		total_burst_time += p.burst_time;
		cout << "\nEnter arrival time: ";
		cin >> p.arrival_time;
		process_list.push_back(p);
	}
	
	/*
	while loop to stimulate working of kernel
	stops when process_list and all 3 queues are empty
	*/
	while(!process_list.empty() || !q0.empty() || !q1.empty() || !q2.empty()){
		
		// while loop that adds processes in first queue according to their arrival time
		while(!process_list.empty() && process_list.front().arrival_time <= time){
			q0.push(process_list.front());
			process_list.pop_front();
		}
		
		// logic to stimulate working of kernel
		if(!q0.empty()){
			process p = q0.front();
			q0.pop();
			
			if(p.remaining_burst_time > 8){
				p.response_time = time;
				p.start_time = time;
				time += 8;
				p.remaining_burst_time -= 8;
				q1.push(p);
			}else{
				p.response_time = time;
				time += p.remaining_burst_time;
				p.waiting_time = time - p.arrival_time - p.burst_time;
				p.end_time = time;
				finished_list.push_back(p);
			}
		}else if(!q1.empty()){
			process p = q1.front();
			q1.pop();
			
			if(p.remaining_burst_time > 16){
				time += 16;
				p.remaining_burst_time -= 16;
				q2.push(p);
			}else{
				time += p.remaining_burst_time;
				p.waiting_time = time - p.arrival_time - p.burst_time;
				p.end_time = time;
				finished_list.push_back(p);
			}
		}else if(!q2.empty()){
			process p = q2.front();
			q2.pop();
			time += p.remaining_burst_time;
			p.waiting_time = time - p.arrival_time - p.burst_time;
			p.end_time = time;
			finished_list.push_back(p);
		}else{
			time++;
		}
	} // outer while loop ends here
	
	cout << "\n\t\t\t*** Simulation Ended ***\n\n";
	
	// for loop that displays information of finished processes 
	for (list<process>::iterator it = finished_list.begin(); it != finished_list.end(); ++it) {
    	
    	cout << "\t\t** Process " << it->id << " information **\n\n";
    	cout << "Arrival time: " << it->arrival_time << " ms\n";
    	cout << "Start time: " << it->start_time << " ms\n";
    	cout << "Waiting time: " << it->waiting_time << " ms\n";
    	total_waiting_time += it->waiting_time;
    	cout << "Response time: " << it->response_time << " ms\n";
    	total_response_time += it->response_time;
    	cout << "Turnaround time: " << it->end_time - it->arrival_time << " ms\n";
    	total_turnaround_time += it->end_time - it->arrival_time;
   		cout << "End time: " << it->end_time << " ms\n\n";
	}
	
	// calculating throughput, average waiting time, average turnaround time and average response time
	throughput = total_burst_time * 1.0/ num_of_processes;
	average_waiting_time = total_waiting_time * 1.0/ num_of_processes;
	average_response_time = total_response_time * 1.0/ num_of_processes;
	average_turnaround_time = total_turnaround_time * 1.0/ num_of_processes;
	
	// displaying throughput, average waiting time, average turnaround time and average response time
	cout << "\nThroughput: " << throughput << "\n";
	cout << "Average waiting time: " << average_waiting_time << "\n";
	cout << "Average response time: " << average_response_time << "\n";
	cout << "Average turnaround time: " << average_turnaround_time;
	
} // main function ends here