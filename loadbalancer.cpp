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

loadbalancer::loadbalancer() {
	sysTime = 0;
}

bool loadbalancer::isEmpty() {
	return requests.empty();
}

int loadbalancer::getTime() {
	return sysTime;
}

request loadbalancer::getRequest() {
	if (!requests.empty()) {
		request req = requests.front();
		requests.pop();
		return req;
	}
}

void loadbalancer::passTime() {
	sysTime++;
}

void loadbalancer::addRequest(request req) {
	requests.push(req);
}

int loadbalancer::queueSize() {
	return requests.size();
}

int main(int argc, char *argv[]) {
	
	loadbalancer requestqueue = loadbalancer();
	srand(time(NULL));
	
	int num_requests = 200;
	for (int i = 0; i < num_requests; i++) {
		int rand1 = rand() % 100;
		int rand2 = rand() % 100;
		int rand3 = rand() % 100;
		int rand4 = rand() % 100;
		string ip1 = to_string(rand1) + "." + to_string(rand2) + "." + to_string(rand3) + "." + to_string(rand4);
		int rand5 = rand() % 100;
		int rand6 = rand() % 100;
		int rand7 = rand() % 100;
		int rand8 = rand() % 100;
		int randTimeToRun = rand() % 1200;
		string ip2 = to_string(rand5) + "." + to_string(rand6) + "." + to_string(rand7) + "." + to_string(rand8);
		request temp_request = {ip1, ip2, randTimeToRun};
		requestqueue.addRequest(temp_request);
	}
	cout << "queue size: " << requestqueue.queueSize() << endl;
	
	int num_servers = 15;
	int time_to_run = 10000;
	if (argc == 3) {
		num_servers = atoi(argv[1]);
		time_to_run = atoi(argv[2]);
	}
	
	webserver servers[num_servers];
	char server_name = 'a';
	for (int i = 0; i < num_servers; i++) {
		webserver temp = webserver(server_name);
		cout << "server " << server_name << " created." << endl;
		servers[i] = temp;
		server_name++;
	}
	return 0;
}
