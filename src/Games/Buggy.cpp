#include "Buggy.h"



Buggy::Buggy(std::shared_ptr<KinectProjector> const & k, ofPoint slocation)
{
	kinectProjector = k;
	location = slocation;
}

Buggy::~Buggy()
{
}

void Buggy::draw()
{
	if (!onMap)
		return;

	float scale = 10;

	ofPushMatrix();
	ofTranslate(projectorCoord);

	ofSetLineWidth(2.0);
	ofColor c = ofColor(180, 180, 180);
	ofSetColor(c);
	//fish.draw();


	c = ofColor(20,20,20);
	ofSetColor(c);
	ofFill();
	ofDrawCircle(0, 0, scale*0.5);
	c = ofColor(255,255,255);
	ofSetColor(c);
	ofNoFill();
	ofPopMatrix();

}

void Buggy::update() {
	projectorCoord = kinectProjector->kinectCoordToProjCoord(location.x, location.y);
}
