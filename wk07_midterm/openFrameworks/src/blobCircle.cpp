//
//  blobCircle.cpp
//  pSpace
//
//  Created by x on 1/10/15.
//
//


#include "blobCircle.hpp"

void blobCircle::setup(ofPoint _point, int _id, int _initTime) {
    time 		= 0;
    beginning	= 0;
    change 		= 255;
    duration 	= 5000;
    
    point = _point;
    id = _id;
    initTime = _initTime;
    
    //ofLog(OF_LOG_NOTICE, "init id: %i, %i " , id, _initTime);
}

void blobCircle::draw () {
//    ofPoint center = toOf(contourFinder.getCenter(i));
    int itemDiameter = 100;
    
    int currentTime = ofGetElapsedTimeMillis() - 500;
    int timeDiff = currentTime - initTime;
    
    
    if (timeDiff < duration) {
        opacity = Cubic::easeOut(timeDiff, beginning, change, duration);
    } else {
        opacity = 255;
    }
    
    ofEnableAlphaBlending();
    ofPushMatrix();
    ofPath circle;
    ofColor myColor = ofColor (255,255,255,opacity);
    circle.setFillColor(myColor);
    circle.setCircleResolution (64);
    circle.arc(point, itemDiameter, itemDiameter, 0, 360);
    circle.close();
    circle.arc(point, itemDiameter-2, itemDiameter-2, 0, 360);
    circle.draw();
    
//
    ofPopMatrix();
    ofDisableAlphaBlending();
}