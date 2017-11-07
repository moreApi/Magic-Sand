#pragma once

#include "ofMain.h"
#include <ofxNetwork.h>
#include <memory>
#include "KinectProjector.h"

class HeightMapServer : public ofThread
{
public:
	HeightMapServer();
	virtual ~HeightMapServer();

	void threadedFunction();

	void setPort(int portnum) { port = portnum; }

	std::shared_ptr<KinectProjector> kinectProjector;


private:
	string moduleName = "HeightMapServer";
	int port = 9966; //default port
	ofxTCPServer server;

	void listen();
	char* getHeightData();
};

