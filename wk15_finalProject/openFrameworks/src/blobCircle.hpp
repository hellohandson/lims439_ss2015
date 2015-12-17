//
//  blobCircle.hpp
//  pSpace
//
//  Created by x on 26/9/15.
//
//

#include "ofMain.h"
#include "Cubic.h"

#ifndef blobCircle_hpp
#define blobCircle_hpp

class blobCircle {
    
public:
    blobCircle(){
        
    };
    ofPoint point;
    float opacity;
    int id;
    void setup (ofPoint _point, int _id, int _initTime);
    void draw();
    int initTime;
private:
    bool shown = false;
    float time, beginning, change, duration;
};

#endif /* blobCircle_hpp */
