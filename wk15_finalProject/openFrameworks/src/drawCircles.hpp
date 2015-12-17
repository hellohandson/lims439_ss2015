//
//  drawCircles.hpp
//  pSpace
//
//  Created by x on 12/10/15.
//
//

#ifndef drawCircles_hpp
#define drawCircles_hpp

#include "ofMain.h"
#include "circleInfo.hpp"


class drawCircles {
public:
    void setup(ofFbo & _fbo);
    void update (vector<circleInfo> & _circleInfo, float _goRadius);
    void draw ();
    void updateCircleRadius();

private:
    float   width;
    float   height;
    float   displayArea;
    float   pi = 3.1416;
    float radius = 1 ;
    
    ofFbo fbo;
    ofFbo baseFbo, maskFbo;
    vector<circleInfo> circles;
    
    circleInfo& getCircle (int id);
   
    ofPtr<ofVboMesh> circleMesh;
    ofPtr<ofShader>	circleShader;
    ofPtr<ofShader> circleIntersectShader;
    ofPtr<ofVboMesh> stageMesh;  //seperate mesh to draw the intersection areas
    ofTexture tex; //store the point data matrix
    ofBufferObject bufferObject;
    vector<ofMatrix4x4> circlePointsMatrices;
    ofImage     imageToShow;
    ofVideoPlayer myPlayer;

};

#endif /* drawCircles_hpp */
