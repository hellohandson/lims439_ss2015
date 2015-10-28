#include "rings.hpp"

void rings::draw(ofFbo& _fbo, ofPoint _point, float _radius, ofColor _color, bool _alpha) {
    _fbo.begin();
        ofPath circlePath;
        circlePath.setFillColor(_color);
        circlePath.setCircleResolution (64);
        if (_alpha) {
            ofEnableAlphaBlending();
        }
    int _noOfRings = 4;
    
    float _radiusStep = _radius / _noOfRings;
        for (int i=1; i< _noOfRings; i++){
            circlePath.arc(_point, _radiusStep*i, _radiusStep*i, 0, 360);
            circlePath.arc(_point, _radiusStep*i-2, _radiusStep*i-2, 0, 360);
            circlePath.close();
            
            circlePath.draw();
//            ofLog(OF_LOG_NOTICE, "rings::draw radius:%f step:%f, i:%i", _radius, _radiusStep ,i );
        }
    
    
    //ofSetColor(52,255,25);
    
    _fbo.end();
    
    
    glDisable(GL_BLEND);
    
    
    ofDrawBitmapString("intimate", _point.x, _point.y);
    ofDrawBitmapString("personal", _point.x+_radiusStep, _point.y+_radiusStep);
    ofDrawBitmapString("social", _point.x+_radiusStep*2, _point.y+_radiusStep*2);
    
}