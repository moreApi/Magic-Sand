#pragma once

#include "ofMain.h"
#include <ofxNetwork.h>
#include "KinectProjector.h"

class HeightMapServer : public ofThread
{
public:
	HeightMapServer();
	virtual ~HeightMapServer();

	void threadedFunction();

	void setPort(int portnum) { port = portnum; }



private:
	string moduleName = "HeightMapServer";
	int port = 9966; //default port
	ofxTCPServer server;
	KinectProjector kinectProjector;

	void listen();
	char* getHeightData();
};

