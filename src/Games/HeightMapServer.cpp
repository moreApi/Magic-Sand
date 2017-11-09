#include "HeightMapServer.h"

/**
Protocol

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
	server.setup(port, true);
	ofLogVerbose(moduleName) << "server open";

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

			//for protocoll information see comment on top of the page
			switch ((unsigned char)leadingByte) {
			case 0:
				; //do nothing
				break;
			case 1: //echo
			{
				ofLogNotice(moduleName) << "Echo request" ;
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
			case 2: //send height data
			{
				ofLogVerbose(moduleName) << "Height Map request";
				
				char* data = getHeightData();
				server.sendRawBytes(i, data, 640 * 480);
				ofLogVerbose(moduleName) << "Send Height Map";
				delete[] data;
			}
			break;
			default:
				ofLogWarning(moduleName) << "Received unknown leading byte: " << int(leadingByte);
				//unknown leading byte
			}
		}
	}
}

char * HeightMapServer::getHeightData()
// fetches, copies and prepares height data for sending
{
	KinectProjector* kp = kinectProjector.get();
	ofPixels tmpPix = kp->getPixels();

	ofVec3f baseplaneNormal = kp->getBasePlaneNormal();
	float baseplaneOffset = kp->getBasePlaneOffset().z;

	char* data = new char[480 * 640];


	for (int y = 0; y < 480; y++) {
			for (int x = 0; x < 640; x++){
				int i = y * 640 + x;
				unsigned char height = tmpPix.getData()[i];
				if (height == 0 || height == 0){
					//out of RoI
					data[i] = 0;
				} else {
					//need to add baseplane to height
					float dist = (baseplaneNormal.x * (x/640.0f) + baseplaneNormal.y * (y/480.0f)) / baseplaneNormal.z;
					int base = dist * baseplaneOffset /2; //ugly guess but i don't know what the scale of the height values is
 					data[i] = (char)(min(height + base,255));
				}
			}
		}

	return data;
}
