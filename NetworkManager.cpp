/*
* NetworkManager.cpp
*
*  Created on: Oct 13, 2017
*      Author: jan
*/
#include "NetworkManager.h"

NetworkManager::NetworkManager() {
	server.setup(9966, true);
	ofLog(OF_LOG_NOTICE, "server open");

}

NetworkManager::~NetworkManager() {
	server.close();
}

void NetworkManager::listen() {
	for (int i = 0; i < server.getLastID(); i++) // getLastID is UID of all clients
	{

		if (server.isClientConnected(i)) { // check and see if it's still around
										   // maybe the client is sending something
										   //		  string str = server.receive(i);
										   //		  if (str != ""){
										   //		  	  ofLog(OF_LOG_NOTICE,"Received: "+str);
										   //		  }
			char data[256];
			server.receiveRawBytes(i, data, 255);
			printf("Here is the message: %s\n", data);
			server.send(i, "You sent: " + string(data));
		}
	}
}

void NetworkManager::sendArray(char * data, int length) {
	server.sendRawBytesToAll(data, length);
}



