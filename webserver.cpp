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
		
		/**
		* webserver default constructor
		*/
		webserver() {
			name = ' ';
			full = false;
			startTime = 0;
		}
		
		/**
		* overloaded webserver constructor with an added name argument
		* @param n name of the webserver
		*/
		webserver(char n) {
			name = n;
			full = false;
			startTime = 0;
		}
		
		/**
		* overloaded webserver constructor with added name and start time arguments
		* @param n name of the webserver
		* @param t start time of the webserver request
		*/
		webserver(char n, int t) {
			name = n;
			full = false;
			startTime = t;
		}
		
		/**
		* getRequest accessor function returns the private variable for webserver's request
		* @return req request of the webserver request
		*/
		request getRequest() {
			return req;
		}
		
		/**
		* getStartTime accessor function returns the private variable for webserver's start time
		* @return startTime the start time of the webserver request
		*/
		int getStartTime() {
			return startTime;
		}
		
		/**
		* getName accessor function returns the private variable for webserver's name
		* @return name the name of the webserver
		*/
		char getName() {
			return name;
		}
		
		/**
		* hasRequest accessor function returns the private variable for if webserver is full
		* @return full the boolean value if webserver has a request
		*/
		bool hasRequest() {
			return full;
		}
		
		/**
		* isFinished function checks if request in webserver is currently finished
		* @param currTime the current time of the system
		* @return true if the request is finished processing
		* @return false otherwise
		*/
		bool isFinished(int currTime) {
			if ((startTime + req.timeToProcess) <= currTime) {
				return true;
			}
			return false;
		}
		
		/**
		* addRequest function adds a new request to the webserver
		* @param currReq the current request to be added to the webserver
		* @param currTime the current time of the system to set the start time of webserver request
		*/
		void addRequest(request currReq, int currTime) {
			req = currReq;
			full = true;
			startTime = currTime;
		}
		
		/**
		* clearRequest function controls the webserver's private boolean variable of whether it contains request
		*/
		void clearRequest() {
			full = false;
		}
};