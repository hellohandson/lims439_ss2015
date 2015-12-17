#include "ofMain.h"
#include "ofApp.h"

#include "ofAppGlutWindow.h"

#include "ofGLProgrammableRenderer.h"
//========================================================================
int main( ){
    ofGLWindowSettings settings;
    settings.setGLVersion(3,2);
    settings.width = 1280;
    settings.height = 720;
    ofCreateWindow(settings);

	//ofSetupOpenGL(1280,720,OF_WINDOW);			// <-------- setup the GL context
    
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
