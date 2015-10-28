#include "myBlobManager.hpp"

using namespace ofxCv;
using namespace cv;

void myBlobManager::init () {
    
    threshold = 0;
    blobsManager.normalizePercentage = 0.9;
    blobsManager.giveLowestPossibleIDs = false;
    blobsManager.maxUndetectedTime = 1000;
    blobsManager.minDetectedTime = 500;
    //blobsManager.debugDrawCandidates = true;
}

void myBlobManager::update (ofxCv::ContourFinder contourFinder) {
    blobs.clear();
    for(int i = 0; i < contourFinder.size(); i++) {
        ofPoint center = toOf(contourFinder.getCenter(i));
//        blobs.push_back(myBlob());
        blobs.push_back(ofxCvBlob());
        
//        blobs[i].x = center.x;
//        blobs[i].y = center.y;
        
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
    // draw the incoming, the grayscale, the bg and the thresholded difference
    ofSetHexColor(0xffffff);
    colorImg.draw(20,20);
    grayImage.draw(360,20);
    grayBg.draw(20,280);
    grayDiff.draw(360,280);
    
    // then draw the contours:
    
    ofFill();
    ofSetHexColor(0x333333);
//    ofRect(360,540,320,240);
    ofSetHexColor(0xffffff);
    
    // we could draw the whole contour finder
    //contourFinder.draw(360,540);
    
    // or, instead we can draw each blob individually,
    // this is how to get access to them:
//    for (int i = 0; i < contourFinder.nBlobs; i++){
//        contourFinder.blobs[i].draw(360,540);
//    }
    
    // debug draw the filtered blobs
    blobsManager.debugDraw(20, 20, 1280, 720, 1280, 720);
    //blobsManager.debugDraw(360, 540, 320, 240, 320, 240);
    
    for(int i=0;i<blobsManager.blobs.size();i++)
    {
        ofxCvBlob blob = blobsManager.blobs.at(i);
        ofNoFill();
        ofSetColor(255,0,0);
        ofCircle(blob.centroid.x,blob.centroid.y,40);
    }
    
//    ofEnableAlphaBlending();
//    
//    for(int i=0;i<blobsManager.candidateBlobs.size();i++)
//    {
//        ofxCvBlob candidateBlob = blobsManager.candidateBlobs.at(i);
//        ofNoFill();
//        ofSetColor(255,0,0,50);
//        ofCircle(candidateBlob.centroid.x,candidateBlob.centroid.y,40);
//    }
//    
//    ofDisableAlphaBlending();
    
    // finally, a report:
    
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
