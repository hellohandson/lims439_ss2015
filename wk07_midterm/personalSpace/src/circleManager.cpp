#include "circleManager.hpp"
#include "rings.hpp"
void circleManager::setup () {
    
    collisionManager.setup(rings);
    
    width = ofGetWidth();
    height = ofGetHeight();
    displayArea = width*height;
    
    setupFbo(finalFbo, width, height);
    setupFbo(maskFbo, width, height);
    setupFbo(fbo, width, height);
    setupFbo(circleRingsFbo, width, height);
    
//    for (int i=1; i < rings ; i ++) {
//        //instantiate FBO into vectors
//        innerComp.push_back (ofFbo());
//        innerMain.push_back (ofFbo());
//        innerMask.push_back (ofFbo());
//        collisionCompFbo.push_back(ofFbo());
//        collisionMainFbo.push_back(ofFbo());
//        collisionMaskFbo.push_back(ofFbo());
//        //setup FBO
//        setupFbo(innerComp[i-1] , width, height);
//        setupFbo(innerMain[i-1] , width, height);
//        setupFbo( innerMask[i-1], width, height);
//        setupFbo( collisionCompFbo[i-1], width, height);
//        setupFbo( collisionMainFbo[i-1], width, height);
//        setupFbo( collisionMaskFbo[i-1], width, height);
//    }
    
    drawManager.setup(fbo);
}

void circleManager::update (vector<ofxStoredBlobVO>& _blobs, int _width, int _height) {
    // add check to check current list of circles still exist in blob list
    // if does not exist, set circle to fade out and be removed from list
    
    inputWidth = _width;
    inputHeight = _height;
    
    updateCheckCircleListToRemove(_blobs);
//    ofLog(OF_LOG_NOTICE, "[circleManager] update- circle list size: %i" , circles.size() );
    //check if blob's ID exist in the list of circles
    for (int i = 0; i < _blobs.size(); i++) {
        // check size of circles list
        if ( circles.size() <= 0) {
            //add first circle, set amFirst to true, so it will just show and not split from other places
            circleInfo newCircle = circleInfo();
            newCircle.sWidth = ofGetWidth();
            newCircle.sHeight = ofGetHeight();
            
            newCircle.inputWidth = inputWidth;
            newCircle.inputHeight = inputHeight;
            // if it is the only circle on screen, fade it up instead of doing the split and move
            newCircle.amFirst = true;
            newCircle.rings = rings;
            newCircle.amFollowing = false;
            newCircle.timeStart = ofGetElapsedTimeMillis();
            setCircleInfo (newCircle, _blobs[i]);
            
            circles.push_back(newCircle);
            
            //ofLog(OF_LOG_NOTICE, "[circleManager] update- create: %i, %i" , newCircle.id, _blobs[i].id );
        } else {
            // check if blobID list exist in list of circles
            bool blobExist = checkBlobHasCircle(_blobs[i].id);
//            
            if (blobExist) {
                // update the circle with the blob's new location
                circleInfo& tempCircle = getCircle(_blobs[i].id);
                tempCircle.sWidth = ofGetWidth();
                tempCircle.sHeight = ofGetHeight();
                tempCircle.inputWidth = _width;
                tempCircle.inputHeight = _height;
                tempCircle.setEndPoint(_blobs[i].centroid);
            } else {
                // create new circle for the blob
                circleInfo newCircle = circleInfo();
                newCircle.sWidth = ofGetWidth();
                newCircle.sHeight = ofGetHeight();
                newCircle.inputWidth = _width;
                newCircle.inputHeight = _height;
                setCircleInfo(newCircle, _blobs[i]);
                // set the start time of the new circle to animate
                newCircle.timeStart = ofGetElapsedTimeMillis();
                // set the circle's parent to split from
                newCircle.setParentPoint(_blobs[i-1].centroid);
                
                //ofLog(OF_LOG_NOTICE, "[circleManager] update- blobexist: %s, %f:%f, %f:%f" , blobExist? "true": "false", _blobs[i-1].centroid.x, _blobs[i-1].centroid.y, newCircle.parentPoint.x, newCircle.parentPoint.y );
                // add new circle to list of circles vector
                circles.push_back(newCircle);
            }
        }
    }
    
    //call the update function in every item in the vector without using for loop
    std::for_each(circles.begin(), circles.end(), std::mem_fun_ref( &circleInfo::update ) );
    updateCircleRadius();
    
    collisionManager.update(circles);
    drawManager.update(circles, goRadius);
//    updateCircleDraw();
};

void  circleManager::updateCheckCircleListToRemove (vector<ofxStoredBlobVO>& _blobs) {
    //circleInfo circle = circles.begin();
//    vector<circleInfo>::const_iterator circle = circles.begin();
//    while (circle != circles.end() ) {
//        bool circleExist =checkCircleInBlob(_blobs, circle->id);
//        ofLog(OF_LOG_NOTICE, "[circleManager] updateCheckCircleListToRemove- circleExist: %i, %s" , circle->id, circleExist?"true":"false" );
//    }
    for (int j=0; j< circles.size(); j++) {
        bool circleExist =checkCircleInBlob(_blobs, circles[j].id);
//        ofLog(OF_LOG_NOTICE, "[circleManager] updateCheckCircleListToRemove- circleExist: %i, %s" , circles[j].id, circles[j].amFlagToRemove?"true":"false" );
        if (!circleExist) {
            if (!circles[j].amFlagToRemove) {
                circles[j].timeStartRemove = ofGetElapsedTimeMillis();
            }
            circles[j].amFlagToRemove = true;
        }
    }
    
    vector<circleInfo> circlesNew;
    for (int j=0; j< circles.size(); j++) {
        if (!circles[j].amRemove) {
            circlesNew.push_back(circles[j]);
        }
    }
    std::swap(circles, circlesNew);
};

void circleManager::updateCircleRadius () {
    int _count = circles.size();
    _count = (_count <=0)? 1: _count;
    float individualArea = displayArea /  pow(_count, 2.0) ;
    if (_count<=0)  {
        individualArea = displayArea;
    }
    float _radius = sqrt(individualArea/pi);
    
    if (_radius != endRadius ){
        amChangedRadius = true;
        radius = goRadius;
        endRadius = _radius;
        timeRadiusChanged = ofGetElapsedTimeMillis();
        
        collisionManager.updateRadius(_radius);
    }
    
    if (amChangedRadius) {
        float _time = ofGetElapsedTimeMillis();
        float _timeDiff = _time -timeRadiusChanged;
        if (_timeDiff < animationDuration) {
            float _aniStep = Cubic::easeOut(_timeDiff, 0, 1, animationDuration);
            goRadius = radius + ( (endRadius - radius)* _aniStep  );
        } else {
            //end animation
            amChangedRadius = false;
            radius = endRadius;
            goRadius = endRadius;
        }
        for (int j=0; j< circles.size(); j++) {
            circles[j].radius = endRadius;
        }
    }
   
}

bool circleManager::checkBlobHasCircle (int _id) {
    for (int j=0; j< circles.size(); j++) {
        if (circles[j].id == _id) {
            return true;
        }
    }
    return false;
};
bool circleManager::checkCircleInBlob (vector<ofxStoredBlobVO>& _blobs, int _id) {
    for (int j=0; j< _blobs.size(); j++) {
        if (_blobs[j].id == _id) {
            return true;
        }
    }
    return false;
};
circleInfo& circleManager::getCircle (int id) {
    for (int j=0; j< circles.size(); j++) {
        if (circles[j].id == id) {
            return circles[j];
        }
    }
}

void circleManager::setCircleInfo (circleInfo& circle, ofxStoredBlobVO& _blob) {
    circle.id = _blob.id;
    circle.rings = rings;
    circle.setEndPoint ( _blob.centroid);
}

void circleManager::setCircleRadius(float _radius) {
    if (_radius != endRadius ){
        amChangedRadius = true;
        radius = goRadius;
        endRadius = _radius;
        timeRadiusChanged = ofGetElapsedTimeMillis();
        
        collisionManager.updateRadius(_radius);
    }
    //ofLog(OF_LOG_NOTICE, "setCircleRadius radius:%f change:%s, time:%i", _radius, amChangedRadius?"true":"false", timeRadiusChanged  );
    
}
int circleManager::getCount () {
    return circles.size();
}

void circleManager::updateCircleDraw () {
//    float width = ofGetWidth();
//    float height = ofGetHeight();
//    
//    setupFbo(finalFbo, width, height);
//    setupFbo(maskFbo, width, height);
//    setupFbo(fbo, width, height);
//    setupFbo(circleRingsFbo, width, height);
//    
//    for (int i=1; i < rings ; i ++) {
//        //instantiate FBO into vectors
//        innerComp.push_back (ofFbo());
//        innerMain.push_back (ofFbo());
//        innerMask.push_back (ofFbo());
//        collisionCompFbo.push_back(ofFbo());
//        collisionMainFbo.push_back(ofFbo());
//        collisionMaskFbo.push_back(ofFbo());
//        //setup FBO
//        setupFbo(innerComp[i-1] , width, height);
//        setupFbo(innerMain[i-1] , width, height);
//        setupFbo( innerMask[i-1], width, height);
//        setupFbo( collisionCompFbo[i-1], width, height);
//        setupFbo( collisionMainFbo[i-1], width, height);
//        setupFbo( collisionMaskFbo[i-1], width, height);
//    }
//    clearFbo(finalFbo);
//    clearFbo(maskFbo);
    clearFbo(fbo);
//    clearFbo(circleRingsFbo);
//    for (int i=1; i < rings ; i ++) {
//        clearFbo(innerComp[i-1]);
//        clearFbo(innerMain[i-1] );
//        clearFbo( innerMask[i-1]);
//        clearFbo( collisionCompFbo[i-1]);
//        clearFbo( collisionMainFbo[i-1]);
//        clearFbo( collisionMaskFbo[i-1]);
//    }

}

//
//

void circleManager::draw () {
//    float width = ofGetWidth();
//    float height = ofGetHeight();
    
    drawManager.draw();
//    clearFbo(fbo);
//    
//    
//    
//    glEnable (GL_BLEND);
//    glBlendFunc (GL_ONE, GL_ONE);
//    fbo.draw(0, 0);
//    glDisable(GL_BLEND);
//    
//    drawManager.drawParticles();

//    circleRingsFbo.draw(0,0);

//    
//    glEnable (GL_BLEND);
//    glBlendFunc (GL_ONE, GL_ONE);
//    glDisable(GL_BLEND);
    
    
}
void circleManager::drawCircle (ofFbo & _fbo, ofPoint _point, float _radius, ofColor _color, bool _alpha) {
    //depreciated - moved to drawCircles

}
void circleManager::clearFbo (ofFbo & _fbo) {
    
    _fbo.begin();
    ofClear(0,0,0,0);
    _fbo.end();

}
void circleManager::drawFboMask (ofFbo & _target, ofFbo & _main, ofFbo & _mask) {
    _target.begin(); //start drawing to finalFBO layer
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_COLOR, GL_SRC_COLOR);
    _main.draw(0, 0); //draw main circle to temp Final FBO layer
    glDisable(GL_BLEND);
    glEnable (GL_BLEND); //prep blend modes for FUTURE drawing func
    glBlendFunc (GL_ZERO, GL_ONE_MINUS_SRC_COLOR); //define how openGL should "blend"
    
    _mask.draw(0,0);
    glDisable(GL_BLEND); //disable blend mode, if not future drawing will be affected
    
    _target.end(); //end drawing.
}
void circleManager::setupFbo (ofFbo & _target, float width, float height){
    _target.allocate(width, height,GL_RGBA, 4);
    clearFbo(_target);
}
// depreciated
void circleManager::drawOld () {
    float width = ofGetWidth();
    float height = ofGetHeight();
    finalFbo.allocate(width,height,GL_RGBA);
    maskFbo.allocate(width, height,GL_RGBA, 4);
    fbo.allocate(width, height,GL_RGBA, 4);
    fbo.begin();
    ofClear(0,0,0,0);
    
    for (int i = 0; i < circles.size(); i++) {
        circleInfo circle = circles[i];
        ofEnableAlphaBlending();
        ofPath circlePath;
        ofColor myColor = ofColor (255,255, 255,circle.opacity);
        circlePath.setFillColor(myColor);
        circlePath.setCircleResolution (64);
        float myRadius = (circle.amFlagToRemove)? goRadius- goRadius*circle.animationStep : goRadius;
        circlePath.arc(circle.getPoint(), myRadius, myRadius, 0, 360);
        circlePath.close();
        circlePath.draw();
    }
    glDisable(GL_BLEND);
    fbo.end();
    
    
    drawSecondary ();
    
    finalFbo.begin();
    ofClear(0,0,0,0);
    fbo.draw(0, 0);
    
    glEnable (GL_BLEND);
    glBlendFunc (GL_ZERO, GL_ONE_MINUS_SRC_COLOR);
    
    maskFbo.draw(0,0);
    glDisable(GL_BLEND);
    finalFbo.end();
    
    glEnable (GL_BLEND);
    glBlendFunc (GL_ONE, GL_ONE);
    finalFbo.draw(0,0);
    glDisable(GL_BLEND);
    
}
//depreciated try to make circles an outline
void circleManager::drawSecondary () {
    maskFbo.begin();
    ofClear(0,0,0,0);

    for (int i = 0; i < circles.size(); i++) {
        circleInfo circle = circles[i];
        ofPath circlePath;
        ofColor myColor = ofColor (255,255, 255, circle.opacity);
        circlePath.setFillColor(myColor);
        circlePath.setCircleResolution (64);
        float myRadius = (circle.amFlagToRemove)? goRadius - goRadius*circle.animationStep : goRadius;
        circlePath.arc(circle.getPoint(), myRadius-2, myRadius-2, 0, 360);
        circlePath.close();

        circlePath.draw();
        
    }
    maskFbo.end();
    
}