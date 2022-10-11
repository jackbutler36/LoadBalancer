/*
	File containing webserver class
*/

#ifndef REQUEST_CPP
#include "request.cpp"
#endif

class webserver {
	private:
		bool full;
		int startTime;
		char name;
		request req;
		
	public:
		webserver() {
			name = ' ';
			full = false;
			startTime = 0;
		}
		
		webserver(char n) {
			name = n;
			full = false;
			startTime = 0;
		}
		
		webserver(char n, int t) {
			name = n;
			full = false;
			startTime = t;
		}
		
		request getRequest() {
			return req;
		}
		
		int getStartTime() {
			return startTime;
		}
		
		char getName() {
			return name;
		}
		
		bool hasRequest() {
			return full;
		}
		
		bool isFinished(int currTime) {
			if ((startTime + req.timeToProcess) <= currTime) {
				//full = false;
				return true;
			}
			return false;
		}
		
		void addRequest(request currReq, int currTime) {
			req = currReq;
			full = true;
			startTime = currTime;
		}
};