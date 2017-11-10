/* Player Vehicle

*/
#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"

#include "../KinectProjector/KinectProjector.h"

class Buggy
{
public:
	Buggy(std::shared_ptr<KinectProjector> const& k,
		ofPoint slocation);

	~Buggy();

	void draw();
	void update();

	void setLocation(int x, int y) { location.x = x; location.y = y; }

private:
	std::shared_ptr<KinectProjector> kinectProjector;

	ofPoint location;
	ofVec2f projectorCoord;
};

