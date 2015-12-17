//
//  myBlobManager.hpp
//  pSpace
//
//  Created by x on 25/9/15.
//
//
#include "ofMain.h"
#include "ofxCv.h"
#include "ofxCvBlob.h"
#include "ofxBlobsManager.h"

#ifndef myBlobManager_hpp
#define myBlobManager_hpp

class myBlobManager {
public:
    void init ();
    void update (ofxCv::ContourFinder contourFinder);
    vector<ofxCvBlob> blobs;
    ofxBlobsManager		blobsManager;
    void draw();
    
    int 				threshold;
    ofxCvColorImage			colorImg;
    
    ofxCvGrayscaleImage 	grayImage;
    ofxCvGrayscaleImage 	grayBg;
    ofxCvGrayscaleImage 	grayDiff;
    
    void keyPressed(int key);
};

#endif /* myBlobManager_hpp */
