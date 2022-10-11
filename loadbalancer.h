/*
	Header file containing loadbalancer class
*/

#ifndef LOADBALANCER_H
#define LOADBALANCER_H
#include "webserver.cpp"

#include <queue>

class loadbalancer {
	private:
		int sysTime;
		queue<request> requests;
		
	public:
		loadbalancer();
		bool isEmpty();
		int getTime();
		request getRequest();
		void passTime();
		void addRequest(request req);
		int queueSize();
};

#endif