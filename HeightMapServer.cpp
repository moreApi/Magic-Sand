#include "HeightMapServer.h"

/**
Protocoll

leading byte:
0 - do nothing
1 - Echo the following 256 bytes
2 - Request height data


*/

HeightMapServer::HeightMapServer()
{
}


HeightMapServer::~HeightMapServer()
{
}

void HeightMapServer::threadedFunction()
{
	server.setup(port, false);
	ofLog(OF_LOG_NOTICE, "server open");
	while (isThreadRunning()) {
		listen();
	}
	server.close();
}

void HeightMapServer::listen() {
	for (int i = 0; i < server.getLastID(); i++) // getLastID is UID of all clients
	{

		char leadingByte;
		if (server.isClientConnected(i)) { // check and see if it's still around
			// maybe the client is sending something
			leadingByte = 0;
			server.receiveRawBytes(i, &leadingByte, 1);
			
			switch (leadingByte) {
			case 1: //echo
				char data[256];
				int received = 0;
				received -= server.receiveRawBytes(i, data, received);
				ofLogNotice(moduleName) << "Echoing: " << data << endl;
				server.sendRawBytes(i, data, 256);
				break;
			case 2: //send height data
				//TODO
				break;
			default:
				ofLogNotice(moduleName) << "Received unknown leading byte: " << leadingByte << endl;
				//unknown leading byte
			}
		}
	}
}
