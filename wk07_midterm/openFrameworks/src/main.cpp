#include "ofMain.h"
#include "ofApp.h"

#include "ofAppGlutWindow.h"

#include "ofGLProgrammableRenderer.h"
//========================================================================
int main( ){
    ofAppGlutWindow window;
    //    window.setGlutDisplayString("rgba double samples>=4");
    ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);
    window.setGlutDisplayString("rgba double samples>=4 depth");
	ofSetupOpenGL(1280,720,OF_WINDOW);			
    
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
	ofRunApp(new ofApp());

}
