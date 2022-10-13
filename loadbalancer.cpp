/*
	File containing loadbalancer class
*/

#include "loadbalancer.h"

#include <iostream>
#include <string>
#include <queue>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

/**
* loadbalancer default constructor
*/
loadbalancer::loadbalancer() {
	sysTime = 0;
}

/**
* isEmpty function returns whether the current request queue is empty
* @return true if request queue is empty
* @return false otherwise
*/
bool loadbalancer::isEmpty() {
	return requests.empty();
}

/**
* getTime accessor function returns the loadbalancer's private variable for current time
* @return sysTime the current system's time
*/
int loadbalancer::getTime() {
	return sysTime;
}

/**
* getRequest function pops the next request off of the request queue if it is not empty
* @return req the next request to be processed on queue, if queue not empty
*/
request loadbalancer::getRequest() {
	if (!requests.empty()) {
		request req = requests.front();
		requests.pop();
		return req;
	}
}

/**
* passTime mutator function controls the overall time structure for processing requests by incrementing private variable
*/
void loadbalancer::passTime() {
	sysTime++;
}

/**
* addRequest function adds a given request to the request queue
* @param req the request to be pushed to the request queue
*/
void loadbalancer::addRequest(request req) {
	requests.push(req);
}

/**
* queueSize function returns the current size of request queue
* @return the current number of requests in the request queue
*/
int loadbalancer::queueSize() {
	return requests.size();
}

/**
* randomRequest function creates and returns a request with randomly generated attributes
* @return temp_request the randomly generated request
*/
request randomRequest() {
	int rand1 = rand() % 100;
	int rand2 = rand() % 100;
	int rand3 = rand() % 100;
	int rand4 = rand() % 100;
	string ip1 = to_string(rand1) + "." + to_string(rand2) + "." + to_string(rand3) + "." + to_string(rand4);
	int rand5 = rand() % 100;
	int rand6 = rand() % 100;
	int rand7 = rand() % 100;
	int rand8 = rand() % 100;
	int randTimeToRun = rand() % 1000 + 1;
	string ip2 = to_string(rand5) + "." + to_string(rand6) + "." + to_string(rand7) + "." + to_string(rand8);
	request temp_request = {ip1, ip2, randTimeToRun};
	return temp_request;
}

/**
* main function contains program that sets up the number of servers (user input), 
* the time you want to run the load balancer (user input), 
* and generates a full queue (usually servers * 2, 100 in this case to reflect peak usage).
* @param argc the number of command line arguments
* @param argv the list of command line arguments
* @return 0 on successful execution of program
*/
int main(int argc, char *argv[]) {
	
	loadbalancer requestqueue = loadbalancer();
	srand(time(NULL)); // Ensures random seed on each run
	
	int num_servers = 10; // Sets default num servers
	int time_to_run = 10000; // Sets default time to run
	
	if (argc == 3) { // Gets num servers and time to run from user input on command line
		num_servers = atoi(argv[1]);
		time_to_run = atoi(argv[2]);
	}
	
	int num_requests = 100; // num_servers * 2; (Analyzing peak usage)
	for (int i = 0; i < num_requests; i++) {
		request temp_request = randomRequest();
		requestqueue.addRequest(temp_request);
	}
	
	int names [num_servers]; // Used in last while loop
	webserver servers[num_servers];
	char server_name = 'a';
	for (int i = 0; i < num_servers; i++) {
		webserver temp = webserver(server_name);
		servers[i] = temp;
		names[i] = 0;
		server_name++;
	}
	
	cout << "Starting request queue size: " << requestqueue.queueSize() << endl;
	cout << "Number of servers: " << num_servers << endl;
	cout << "Total time to run: " << time_to_run << endl;
	cout << "Time range for each task: 1-1000 seconds" << endl << endl;
	
	int count = 0; // Used for initial population of webservers
	int countProcessed = 0; // Used to track number of processed requests
	int countRandom = 0; // Used to track number of randomly created/ added requests
	while (requestqueue.getTime() < time_to_run) {
		
		if (count < num_servers) { //Initial population of requests to empty webservers
			servers[count].addRequest(requestqueue.getRequest(), requestqueue.getTime());
			count++;
			requestqueue.passTime();
			continue;
		}
		count++;
		
		for (int i = 0; i < num_servers; i++) {
			// 
			if ((!servers[i].hasRequest() || servers[i].isFinished(requestqueue.getTime())) && !requestqueue.isEmpty()) {
				request currRequest = servers[i].getRequest();
				cout << "Server " << servers[i].getName() << " received at time " << servers[i].getStartTime() << 
				" and finished at time " << requestqueue.getTime() << " of process time " << currRequest.timeToProcess << " took " << 
				requestqueue.getTime() - servers[i].getStartTime() << " from " << currRequest.ip_in << " to " << currRequest.ip_out << endl;
				servers[i].addRequest(requestqueue.getRequest(), requestqueue.getTime());
				countProcessed++;
				
				if ((rand() % 3) == 1) { // 1/3 chance to generate and add random request 
					countRandom++;
					request temp_request = randomRequest();
					requestqueue.addRequest(temp_request);
					cout << "Added random request. Total number of requests now: " << countRandom + num_requests << endl;
				}
			}
			
			// Clears processes still in webservers once queue is empty until time limit reached
			if ((requestqueue.isEmpty()) && (servers[i].isFinished(requestqueue.getTime())) && (names[i] != 1)) {
				request currRequest = servers[i].getRequest();
				servers[i].clearRequest();
				cout << "Server " << servers[i].getName() << " received at time " << servers[i].getStartTime() << 
				" and finished at time " << requestqueue.getTime() << " of process time " << currRequest.timeToProcess << " took " << 
				requestqueue.getTime() - servers[i].getStartTime() << " from " << currRequest.ip_in << " to " << currRequest.ip_out << endl;
				names[i] = 1; // Ensures each webserver only cleared once
				countProcessed++;
			}
			
			requestqueue.passTime();
		}
		
	}
	
	cout << endl << "Ending request queue size: " << requestqueue.queueSize() << endl;
	cout << "Total requests processed and completed: " << countProcessed << endl;
	
	if ((countProcessed < num_requests + countRandom) && (num_requests + countRandom - countProcessed <= num_servers))
		cout << "Total of " << num_requests + countRandom - countProcessed << " unprocessed requests remain in webservers" << endl << endl;
	else if (countProcessed < num_requests + countRandom)
		cout << "Total of " << num_requests + countRandom - countProcessed << " unprocessed requests remain in request queue and webservers" << endl << endl;
	
	/*
	Checks if requests currently in each webserver are finished after time limit reached
	0: not finished yet --> not processed
	1: finished
	*/
	// for (int i = 0; i < num_servers; i++) {
		// cout << "server " << servers[i].getName() << ": " << servers[i].isFinished(requestqueue.getTime()) << endl;
	// }
	
	
	return 0;
}
