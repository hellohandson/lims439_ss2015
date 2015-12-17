//
//  circleManager.hpp
//  pSpace
//
//  Created by x on 27/9/15.
//
//

#ifndef circleManager_hpp
#define circleManager_hpp

#include "ofMain.h"
#include "Cubic.h"
#include "ofxBlobsManager.h"
#include "circleInfo.hpp"
#include "ofxStoredBlobVO.h"
#include "cCollisionManager.hpp"
#include "drawCircles.hpp"

class circleManager {

public:
    void setup();
    void update (vector<ofxStoredBlobVO>& _blobs, int _width, int _height);
    
    void draw();
    int getCount();
    void setCircleRadius (float _radius);
private:
    ofFbo fbo;
    ofFbo maskFbo;
    ofFbo finalFbo;
    ofFbo circleRingsFbo;
    vector<ofFbo> innerComp;
    vector<ofFbo> innerMain;
    vector<ofFbo> innerMask;
    vector<ofFbo> collisionCompFbo;
    vector<ofFbo> collisionMainFbo;
    vector<ofFbo> collisionMaskFbo;
    float inputWidth = 100;
    float inputHeight = 100;
    
    
    drawCircles drawManager;
    
    vector<circleInfo> circles;
    
    float   width;
    float   height;
    float   displayArea;
    float   pi = 3.1416;
    
    int rings = 4; 
    float amChangedRadius = false;
    float radius = 1 ;
    float goRadius = 1;
    float endRadius = 1;
    int timeRadiusChanged;
    int animationDuration = 500;
    
    bool checkBlobHasCircle (int _id);
    bool checkCircleInBlob (vector<ofxStoredBlobVO>& _blobs, int _id);
    circleInfo& getCircle (int id);
    cCollisionManager collisionManager;
    
    void setCircleInfo (circleInfo& circle, ofxStoredBlobVO& _blob);
    void updateCheckCircleListToRemove (vector<ofxStoredBlobVO>& _blobs);
    void updateCircleRadius ();


    void clearFbo (ofFbo & _fbo);
    void drawFboMask (ofFbo & _target, ofFbo & _main, ofFbo & _mask);
    void setupFbo (ofFbo & _target, float width, float height);
    
    
};

#endif /* circleManager_hpp */
