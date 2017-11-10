#include "BuggyGameServer.h"

/**
Protocol

leading byte:
0 - do nothing
1 - Echo the following 256 bytes
2 - new car position in 5 bytes, sum of first 3 = x value, last 2 = y

*/

BuggyGameServer::BuggyGameServer()
{
}


BuggyGameServer::~BuggyGameServer()
{
	delete playerCar;
}

void BuggyGameServer::setup(std::shared_ptr<KinectProjector> const& k) {
	playerCar = new Buggy(k, ofPoint(300, 200));
}

void BuggyGameServer::threadedFunction()
{
	server.setup(port, true);
	ofLogVerbose(moduleName) << "server open";

	while (isThreadRunning()) {
		listen();
	}

	server.close();
}

void BuggyGameServer::listen()
{
	for (int i = 0; i < server.getLastID(); i++) // getLastID is UID of all clients
	{

		char leadingByte;
		if (server.isClientConnected(i)) { // check and see if it's still around
										   // maybe the client is sending something
			leadingByte = 0;
			server.receiveRawBytes(i, &leadingByte, 1);

			//for protocoll information see comment on top of the page
			switch ((unsigned char)leadingByte) {
			case 0:
				; //do nothing
				break;
			case 1: //echo
			{
				ofLogNotice(moduleName) << "Echo request";
				char data[256];
				int received = 256;
				//string s = server.receive(i);
				while (received > 0) {
					ofLogNotice(moduleName) << "received: " << received;
					received -= server.receiveRawBytes(i, data, received);
				}
				ofLogNotice(moduleName) << "Echoing: " << data;
				//server.sendRawBytes(i, s.c_str(), strlen(s.c_str()));
				server.sendRawBytes(i, data, 256);
			}
			break;
			case 2: //receive new car position
			{
				ofLogVerbose(moduleName) << "getting new car position";

				char data[5];
				int received = 5;
				while (received > 0) {
					received -= server.receiveRawBytes(i, data, received);
				}

				unsigned char* data2 = (unsigned char*)(data);

				int x = data2[0] + data2[1] + data[2];
				int y = data2[3] + data2[4];


				setCarPos(x, y);
			}
			break;
			default:
				ofLogWarning(moduleName) << "Received unknown leading byte: " << int(leadingByte);
				//unknown leading byte
			}
		}
	}
}

void BuggyGameServer::setCarPos(int x, int y) {
	ofLogVerbose(moduleName) << "car at " << x << "," << y;
	playerCar->setLocation(x, y);
}
