#ifndef circleInfo_hpp
#define circleInfo_hpp

#include "ofMain.h"
#include "Cubic.h"

class circleInfo {
public:
    circleInfo () {}; // empty function used to instantiate object.
    void update ();
    void setEndPoint (ofPoint _endPoint); // sets the current location if it is spliting from previous circle Or currently just tracks a blob
    void setParentPoint (ofPoint _endPoint); // sets the parent circle's location to split from;
    ofPoint getPoint ();
    
    float timeStart; //time the circle is created, used for animation progress
    float timeStartRemove; //time the circle is flaged to be removed, used for animation progress
    
    float opacity = 255; // point opacity
    float radius;
    int rings = 0;
    int id = -1; // blob id, used to match new blobs
    bool amIntro = true;
    bool amFollowing = false;
    bool amRemove = false; // used to check to remove from list
    bool amFlagToRemove = false; //used to check if item should fade out;
    bool amFirst = false;
    ofPoint parentPoint; //parent circle's location to split from
    float animationStep;
    bool collided = false;
    vector<int> collidedID;
    vector<float> collidedDist; //list of distance to collidedID
    
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
