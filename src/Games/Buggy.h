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

	void setLocation(int x, int y) { 
		if (0 < x < 640 && 0 < y < 480) {
			location.x = x; 
			location.y = y;
			onMap = true;
		}
		else {
			onMap = false;
		}
	}

private:
	std::shared_ptr<KinectProjector> kinectProjector;

	bool onMap = false;

	ofPoint location;
	ofVec2f projectorCoord;
};

