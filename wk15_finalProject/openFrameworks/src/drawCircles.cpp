//
//  drawCircles.cpp
//  pSpace
//
//  Created by x on 12/10/15.
//
//

#include "drawCircles.hpp"
#include <math.h>

void drawCircles::setup(ofFbo & _fbo){

    width = ofGetWidth();
    height = ofGetHeight();
    fbo = _fbo;
    
    circleShader = ofPtr<ofShader>(new ofShader());
    circleShader->load("pattern.vert", "pattern.frag");

    circleShader->begin();
    circleShader->setUniformTexture("tex",tex,0);
    circleShader->end();

    circleIntersectShader = ofPtr<ofShader>(new ofShader());
    circleIntersectShader->load("intersect.vert", "intersect.frag");
    ofPath rectPath;
    rectPath.rectangle(ofPoint(0, 0), ofGetWidth(), ofGetHeight());

    stageMesh = ofPtr<ofVboMesh>(new ofVboMesh(rectPath.getTessellation()));
    circlePointsMatrices.resize(10); //number of blobs detected

    bufferObject.allocate();
    bufferObject.bind(GL_TEXTURE_BUFFER);
    bufferObject.setData(circlePointsMatrices,GL_STREAM_DRAW);
    tex.allocateAsBufferTexture(bufferObject,GL_RGBA32F);

  //  imageToShow.load("text2.jpg");
    myPlayer.load("matrix.mp4");
    myPlayer.play();
    
    circleIntersectShader->begin();
    circleIntersectShader->setUniformTexture("tex",tex,0);
    circleIntersectShader->setUniformTexture("tex1", myPlayer.getTexture(), 1 );
   // circleIntersectShader->setUniformTexture("tex1", imageToShow, 1 );
    circleIntersectShader->end();

};

void drawCircles::update (vector<circleInfo>  & _circleInfo, float _goRadius){
    
    myPlayer.update();
    circles = _circleInfo;
    
    // if current radius is not equal
    if (radius != _goRadius) {
    }
    radius = _goRadius;
    
    //update Buffer object stuff
    circlePointsMatrices.resize(circles.size());
    for(size_t i=0;i<circlePointsMatrices.size();i++){
        circleInfo & circle = circles[i];
        ofPoint myPoint = circle.getPoint();
        circlePointsMatrices[i] = ofMatrix4x4 (myPoint.x, myPoint.y, circle.getOpacity(), circle.id, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    }
    bufferObject.updateData(0,circlePointsMatrices);

    circleIntersectShader->begin();
    circleIntersectShader->setUniform2f("u_circleDimension", radius, radius);
    circleIntersectShader->setUniform1i("u_pointCount", circlePointsMatrices.size() );
    circleIntersectShader->setUniformTexture("tex1", myPlayer.getTexture(), 1 );
    //circleIntersectShader->setUniformTexture("tex1", imageToShow, 1 );
    circleIntersectShader->end();

    circleShader->begin();
    circleShader->setUniform2f("u_circleDimension", radius, radius);
    circleShader->setUniform1i("u_pointCount", circlePointsMatrices.size() );
    circleShader->end();
    
};

void drawCircles::updateCircleRadius () {

}

void drawCircles::draw () {
    
    glEnable (GL_BLEND);
    circleShader->begin();
    circleShader->setUniform1f("time", ofGetElapsedTimef());
    circleShader->setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
    circleShader->setUniform1f("u_time", ofGetElapsedTimef());
    circleShader->setUniform2f("u_circleDimension", radius, radius);
    stageMesh->drawInstanced(OF_MESH_FILL, 1);
    circleShader->end();
    glDisable(GL_BLEND);

    glEnable (GL_BLEND);
    circleIntersectShader->begin();
    circleIntersectShader->setUniform1f("time", ofGetElapsedTimef());
    circleIntersectShader->setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
    circleIntersectShader->setUniform1f("u_time", ofGetElapsedTimef());
    stageMesh->drawInstanced(OF_MESH_FILL, 1); //comment this line to remove intersect image
    circleIntersectShader->end();
    glDisable(GL_BLEND);
   
}

circleInfo& drawCircles::getCircle (int id) {
    for (int j=0; j< circles.size(); j++) {
        if (circles[j].id == id) {
            return circles[j];
        }
    }
}
