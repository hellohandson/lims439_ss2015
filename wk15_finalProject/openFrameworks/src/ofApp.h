#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "myBlobManager.hpp"
#include "blobCircle.hpp"
#include "circleManager.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        ofVideoGrabber vidGrabber;
        bool usePS3 = false;
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
        float   width;
        float   height;
        float   displayArea;
        float   pi = 3.1416;
        float inputWidth = 100;
        float inputHeight = 100;
        float threshold;
        ofVideoPlayer movie;
        
        bool bLearnBackground;
        ofxCvColorImage colorImg;
        ofxCvGrayscaleImage grayImage, grayBg, grayDiff;
        bool showLabels = true;
    
        ofxCv::ContourFinder contourFinder;
        ofxCv::TrackingColorMode trackingColorMode;
    
private:
    void initVideo();
    void drawVideo (bool _show);
    void drawCircles ();
    void updateCircleRadius();
    void setupTracker ();
    void drawDebug();
    float circleRadius = 100;
    vector<blobCircle> blobCircles;
    myBlobManager blobManager;
    circleManager circleManager;
};
