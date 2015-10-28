#ifndef drawCircles_hpp
#define drawCircles_hpp

#include "ofMain.h"
#include "circleInfo.hpp"
#include "dotParticle.hpp"

class drawCircles {
public:
    void setup(ofFbo & _fbo);
    void update (vector<circleInfo> & _circleInfo, float _goRadius);
    void draw ();
    void drawParticles ();
    ofTrueTypeFont myFont;

private:
    float   width;
    float   height;
    float   displayArea;
    float   pi = 3.1416;
    
    int rings = 4; //number of internal rings
    float radius = 1 ;
    
    ofFbo fbo;
    ofFbo baseFbo, maskFbo;
    vector<circleInfo> circles;
    
    void updateCircleRadius();
    void drawCircle (ofFbo & _fbo, ofPoint _point, float _radius, ofColor _color, bool _alpha = false);
    void clearFbo (ofFbo & _fbo);
    circleInfo& getCircle (int id);
    
    
    void setupParticles ();
    void updateParticles();
    particleMode currentMode;
    
    vector <dotParticle> p;
    vector <ofPoint> attractPoints;
    vector <ofPoint> attractPointsWithMovement;
    
    void drawViaFBO (); //old draw FBO method
    
    // shader stuff
    ofPtr<ofVboMesh> circleMesh;
    ofPtr<ofShader>	circleShader;
};

#endif /* drawCircles_hpp */
