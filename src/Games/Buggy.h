/* Player Vehicle

*/
#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"

#include "ctime"

#include "../KinectProjector/KinectProjector.h"

class Buggy
{
public:
	Buggy(std::shared_ptr<KinectProjector> const& k,
		ofPoint slocation);

	~Buggy();

	void draw();
	void update();

	void setLocation(int x, int y) ;

private:
	std::shared_ptr<KinectProjector> kinectProjector;

	bool onMap;

	clock_t lastUpdate;

	ofPoint targetLocation;
	ofPoint currentLocation;
	ofVec2f projectorCoord;
};

