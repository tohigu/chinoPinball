//
//  Lever.h
//  chinoPinball
//
//  Created by Kuba on 03/01/14.
//
//

#pragma once

#include "SimpleObject.h"

class Lever : public SimpleObject {

public:

	virtual void setup(ofxBulletWorldRigid &world, ofVec3f setPosition, int setDirection);

	virtual void update();
	virtual void draw();
	void rotate(float degrees);
    
	ofxBulletCustomShape	body;
	ofxAssimpModelLoader	assimpModel;
    ofMaterial				material;    
    
	ofVec3f         position;
    int             direction; // rotation direction: 1 - clockwise, 0 - counter clockwise
    
    btQuaternion    rotation;
    
    float angle; // degrees
	float lowerLimit;
	float upperLimit;
    float speed;
    float axisX;
    
	void keyPressed(ofKeyEventArgs& key);
	void keyReleased(ofKeyEventArgs& key);
    bool isKeyPressed;

};