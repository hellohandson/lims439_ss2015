//
//  cCollisionManager.hpp
//  pSpace
//
//  Created by x on 1/10/15.
//
//

#ifndef cCollisionManager_hpp
#define cCollisionManager_hpp

#include "ofMain.h"
#include "circleInfo.hpp"

class cCollisionManager {
public:
    void setup (int _noOfRings);
    void update (vector<circleInfo>& circles);
    
    void updateRadius (float _radius);
    
private:
    int rings;
    float radius;
    float checkRadius;
    
    void checkCollisions (circleInfo& target, vector<circleInfo>& list, int startID = 1);
    
    void clearCircleCollisionInfo (vector<circleInfo>& circles);
};

#endif /* cCollisionManager_hpp */
