//
//  circleManager.cpp
//  pSpace
//
//  Created by x on 27/9/15.
//
//

#include "circleManager.hpp"

void circleManager::setup () {
    
    collisionManager.setup(rings);
    
    width = ofGetWidth();
    height = ofGetHeight();
    displayArea = width*height;
    
    setupFbo(finalFbo, width, height);
    setupFbo(maskFbo, width, height);
    setupFbo(fbo, width, height);
    setupFbo(circleRingsFbo, width, height);
    
    drawManager.setup(fbo);
}

void circleManager::update (vector<ofxStoredBlobVO>& _blobs, int _width, int _height) {
    
    inputWidth = _width;
    inputHeight = _height;
    
    updateCheckCircleListToRemove(_blobs);
    //check if blob's ID exist in the list of circles
    for (int i = 0; i < _blobs.size(); i++) {
        // check size of circles list
        if ( circles.size() <= 0) {
            circleInfo newCircle = circleInfo();
            newCircle.sWidth = ofGetWidth();
            newCircle.sHeight = ofGetHeight();
            newCircle.inputWidth = inputWidth;
            newCircle.inputHeight = inputHeight;
            newCircle.amFirst = true;
            newCircle.rings = rings;
            newCircle.amFollowing = false;
            newCircle.timeStart = ofGetElapsedTimeMillis();
            setCircleInfo (newCircle, _blobs[i]);
            circles.push_back(newCircle);
            
        } else {
            // check if blobID list exist in list of circles
            bool blobExist = checkBlobHasCircle(_blobs[i].id);           
            if (blobExist) {
                circleInfo& tempCircle = getCircle(_blobs[i].id);
                tempCircle.sWidth = ofGetWidth();
                tempCircle.sHeight = ofGetHeight();
                tempCircle.inputWidth = _width;
                tempCircle.inputHeight = _height;
                tempCircle.setEndPoint(_blobs[i].centroid);
            } else {
                circleInfo newCircle = circleInfo();
                newCircle.sWidth = ofGetWidth();
                newCircle.sHeight = ofGetHeight();
                newCircle.inputWidth = _width;
                newCircle.inputHeight = _height;
                setCircleInfo(newCircle, _blobs[i]);
                newCircle.timeStart = ofGetElapsedTimeMillis();
                newCircle.setParentPoint(_blobs[i-1].centroid);

                circles.push_back(newCircle);
            }
        }
    }
    
    std::for_each(circles.begin(), circles.end(), std::mem_fun_ref( &circleInfo::update ) );
    updateCircleRadius();
    
    collisionManager.update(circles);
    drawManager.update(circles, goRadius);

};

void  circleManager::updateCheckCircleListToRemove (vector<ofxStoredBlobVO>& _blobs) {
    
    for (int j=0; j< circles.size(); j++) {
        bool circleExist =checkCircleInBlob(_blobs, circles[j].id);
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
 
    
}
int circleManager::getCount () {
    return circles.size();
}


void circleManager::draw () {

    drawManager.draw();
    
}

void circleManager::clearFbo (ofFbo & _fbo) {
    
    _fbo.begin();
    ofClear(0,0,0,0);
    _fbo.end();

}
void circleManager::drawFboMask (ofFbo & _target, ofFbo & _main, ofFbo & _mask) {
    _target.begin();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_COLOR, GL_SRC_COLOR);
    _main.draw(0, 0);
    glDisable(GL_BLEND);
    glEnable (GL_BLEND);
    glBlendFunc (GL_ZERO, GL_ONE_MINUS_SRC_COLOR);
    _mask.draw(0,0);
    glDisable(GL_BLEND);
    
    _target.end(); 
}
void circleManager::setupFbo (ofFbo & _target, float width, float height){
    _target.allocate(width, height,GL_RGBA, 4);
    clearFbo(_target);
}

