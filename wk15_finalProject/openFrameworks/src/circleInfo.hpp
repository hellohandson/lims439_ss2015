//
//  circleInfo.hpp
//  pSpace
//
//  Created by x on 27/9/15.
//
//

#ifndef circleInfo_hpp
#define circleInfo_hpp

#include "ofMain.h"
#include "Cubic.h"

class circleInfo {
public:
    circleInfo(){};
    void update ();
    void setEndPoint (ofPoint _endPoint); //set the current location if it is spliting from previous circle Or currently just tracks a blob
    void setParentPoint (ofPoint _endPoint); //parent circle's location to split from
    ofPoint getPoint ();
    float timeStart;
    float timeStartRemove;
    float opacity = 255;
    float radius;
    int rings = 0;
    int id = -1;
    bool amIntro = true;
    bool amFollowing = false;
    bool amRemove = false;
    bool amFlagToRemove = false;
    bool amFirst = false;
    ofPoint parentPoint;
    float animationStep;
    bool collided = false;
    vector<int> collidedID;
    vector<float> collidedDist;    
    float sWidth = 100;
    float sHeight = 100;
    float inputWidth = 100;
    float inputHeight = 100;
    float getOpacity ();
    
private:
    float animationDuration = 4000;
    ofPoint point; // current point's location
    ofPoint goPoint; // final end point to go to
};

#endif /* circleInfo_hpp */
