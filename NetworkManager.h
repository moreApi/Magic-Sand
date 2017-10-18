/*
* NetworkManager.h
*
*  Created on: Oct 13, 2017
*      Author: jan
*/

#ifndef SRC_NETWORKMANAGER_H_
#define SRC_NETWORKMANAGER_H_

#include <ofMain.h>
#include <ofxNetwork.h>


class NetworkManager {
public:
	NetworkManager();
	virtual ~NetworkManager();
	void listen();
	void sendArray(char * data, int length);

private:
	ofxTCPServer server;
};

#endif /* SRC_NETWORKMANAGER_H_ */