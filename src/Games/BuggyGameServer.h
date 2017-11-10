/*
Actually more a client than server. But a conection from unity to here is allready made for the height map. 
So it's easy to do a second in the same direction.
	
*/

#pragma once

#include "ofMain.h"
#include <ofxNetwork.h>
#include <memory>
#include "KinectProjector.h"

#include "Buggy.h"

class BuggyGameServer : public ofThread
{
public:
	BuggyGameServer();
	~BuggyGameServer();

	void setup(std::shared_ptr<KinectProjector> const& k);
	void threadedFunction();
	void draw(){playerCar->draw();}
	void update(){playerCar->update();}

	void setPort(int portnum) { port = portnum; }

private:
	string moduleName = "BuggyGameServer";
	int port = 9967; //default port
	ofxTCPServer server;

	Buggy* playerCar;

	void listen();
	void setCarPos(int x, int y);
};

