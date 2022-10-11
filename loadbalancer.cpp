/*
	File containing loadbalancer class
*/

#include "loadbalancer.h"

#include <iostream>
#include <string>
#include <queue>

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
	request req = {"12.23.4", "43.1234.3", 24};
	loadbalancer requestqueue = loadbalancer();
	requestqueue.addRequest(req);
	cout << "Testing queue size: " << requestqueue.queueSize() << endl;
	return 0;
}
