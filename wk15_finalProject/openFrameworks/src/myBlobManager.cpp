//
//  myBlobManager.cpp
//  pSpace
//
//  Created by x on 25/9/15.
//
//

#include "myBlobManager.hpp"

using namespace ofxCv;
using namespace cv;

void myBlobManager::init () {
    
    threshold = 0;
    blobsManager.normalizePercentage = 0.9;
    blobsManager.giveLowestPossibleIDs = false;
    blobsManager.maxUndetectedTime = 1000;
    blobsManager.minDetectedTime = 500;
}

void myBlobManager::update (ofxCv::ContourFinder contourFinder) {
    blobs.clear();
    for(int i = 0; i < contourFinder.size(); i++) {
        ofPoint center = toOf(contourFinder.getCenter(i));
        blobs.push_back(ofxCvBlob());        
        blobs[i].area = contourFinder.getContourArea(i);
        blobs[i].length = contourFinder.getArcLength(i);
        blobs[i].boundingRect = toOf( contourFinder.getBoundingRect(i));
        blobs[i].centroid = center;
        
        vector<cv::Point> blobPoints = contourFinder.getContour(i);
        for(int j = 0; j < blobPoints.size(); j++) {
            blobs[i].pts.push_back( toOf(blobPoints[j]));
        }
        
        blobs[i].nPts = blobs[i].pts.size();
    }
    
    blobsManager.update(blobs);
}

void myBlobManager::draw () {
    ofSetHexColor(0xffffff);
    colorImg.draw(20,20);
    grayImage.draw(360,20);
    grayBg.draw(20,280);
    grayDiff.draw(360,280);
    
    ofFill();
    ofSetHexColor(0x333333);
    ofSetHexColor(0xffffff);
        
    blobsManager.debugDraw(20, 20, 1280, 720, 1280, 720);
    
    for(int i=0;i<blobsManager.blobs.size();i++)
    {
        ofxCvBlob blob = blobsManager.blobs.at(i);
        ofNoFill();
        ofSetColor(255,0,0);
        ofCircle(blob.centroid.x,blob.centroid.y,40);
    }
        
    ofSetHexColor(0xffffff);
    char reportStr[1024];
    sprintf(reportStr, "bg subtraction and blob detection\npress ' ' to capture bg\nthreshold %i (press: +/-)\nnum blobs found %i, fps: %f", threshold, blobs.size(), ofGetFrameRate());
    ofDrawBitmapString(reportStr, 20, 600);
}
//--------------------------------------------------------------
void myBlobManager::keyPressed(int key){
    
    switch (key){
        case '+':
            threshold ++;
            if (threshold > 255) threshold = 255;
            break;
        case '-':
            threshold --;
            if (threshold < 0) threshold = 0;
            break;
    }
}
