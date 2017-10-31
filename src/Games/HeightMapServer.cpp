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
	server.setup(port, true);
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

			//for protocoll information see comment on top of the page
			switch ((unsigned char)leadingByte) {
			case 0:
				; //do nothing
				break;
			case 1: //echo
			{
				ofLogNotice(moduleName) << "Echo request" << endl;
				char data[256];
				int received = 256;
				//string s = server.receive(i);
				while (received > 0) {
					ofLogNotice(moduleName) << "received: " << received << endl;
					received -= server.receiveRawBytes(i, data, received);
				}
				ofLogNotice(moduleName) << "Echoing: " << data << endl;
				//server.sendRawBytes(i, s.c_str(), strlen(s.c_str()));
				server.sendRawBytes(i, data, 256);
			}
			break;
			case 2: //send height data
			{
				ofLogNotice(moduleName) << "Height Map request" << endl;

				char* data = getHeightData();
				server.sendRawBytes(i, data, 640 * 480);
				ofLogNotice(moduleName) << "Send Height Map" << endl;
				delete[] data;
			}
			break;
			default:
				ofLogNotice(moduleName) << "Received unknown leading byte: " << int(leadingByte) << endl;
				//unknown leading byte
			}
		}
	}
}

char * HeightMapServer::getHeightData()
// fetches, copies and prepares height data for sending
{
	ofTexture texture = kinectProjector.getTexture();
	ofPixels pixels;
	texture.readToPixels(pixels);

	ofLogNotice(moduleName) << "num of bytes per pixel: " << pixels.getBytesPerPixel()
		<< " num of channels per pixel:" << pixels.getNumChannels()
		<< " length: " << pixels.getTotalBytes();

	/*
	float* mapData = DummyData::generateDummyData();

	char* data = new char[480 * 640];

	for (int i = 0; i < 640 * 480; i++) {
		data[i] = (char)((unsigned char)(mapData[i] * 255));
	}*/

	return 0;
}
