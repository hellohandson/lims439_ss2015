//
//  cCollisionManager.cpp
//  pSpace
//
//  Created by x on 1/10/15.
//
//

#include "cCollisionManager.hpp"

void cCollisionManager::setup (int _noOfRings){
    rings = _noOfRings;
    
};
void cCollisionManager::update (vector<circleInfo>& circles){
    //clear circles collision info before check
    clearCircleCollisionInfo(circles);
    for (int i=0; i< circles.size(); i++) {
        circleInfo & circle = circles[i];
        if (!circle.amFlagToRemove || !circle.amRemove) {
            // check collisions only on circles still active
            checkCollisions(circle, circles, i+1);

        }
    }
};
void cCollisionManager::clearCircleCollisionInfo (vector<circleInfo>& circles) {
    for (int i=0; i< circles.size(); i++) {
        circles[i].collided = false;
        circles[i].collidedID.clear();
        circles[i].collidedDist.clear();
    }
}

void cCollisionManager::updateRadius (float _radius){
    radius = _radius;
    checkRadius = radius;
};
void cCollisionManager::checkCollisions (circleInfo& target, vector<circleInfo>& list, int startID) {
    for (int i=startID; i< list.size(); i++) {
        circleInfo & circle = list[i];
        if (target.id != circle.id) {
            //make sure not checking agaisnt itself
            if (!circle.amFlagToRemove || !circle.amRemove) {
                // check collisions only on circles still active
                ofPoint targetPos = target.getPoint();
                ofPoint circlePos = circle.getPoint();
                float distance = ofDist(targetPos.x, targetPos.y, circlePos.x, circlePos.y);
                if (checkRadius > distance/2) {
                    target.collided = true;
                    target.collidedID.push_back(circle.id);
                    target.collidedDist.push_back(distance);
                    circle.collided = true;
                    circle.collidedID.push_back(target.id);
                    circle.collidedDist.push_back(distance);
                }
            }
        }
        
    }
}