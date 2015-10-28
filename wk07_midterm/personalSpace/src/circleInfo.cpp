#include "circleInfo.hpp"

void circleInfo::update () {
    float currentTime = ofGetElapsedTimeMillis ();
    if (amIntro) {
        float timeDiff = currentTime - timeStart;
        
        animationStep = Cubic::easeOut(timeDiff, 0, 1, animationDuration);
        if (timeDiff > animationDuration) {
            animationStep = 1;
            amIntro = false;
            amFollowing = true;
        }
        if (amFirst) {
            opacity = 255 * animationStep;
        } else {
            
            
            point.x += (goPoint.x - point.x) * animationStep;
            point.y += (goPoint.y - point.y) * animationStep;
        }
        
        if (animationStep >=1) {
            amIntro = false;
            amFollowing = true;
        }
    } else {
        point = goPoint;
        //check if item is flag to remove;
        if (!amRemove) {
            if (amFlagToRemove ){
                float timeDiff = currentTime - timeStartRemove;
                if (timeDiff > animationDuration) {
                    opacity = 0;
                    amRemove = true;
                } else {
                    animationStep = Cubic::easeOut(timeDiff, 0, 1, animationDuration);
                    opacity = 255 - (255* animationStep);
                }
                //ofLog(OF_LOG_NOTICE, "[circle] amFlagToRemove: %i, start:%f, current:%f, diff:%f, %f" , id, timeStartRemove, currentTime, timeDiff, opacity );
            }
        }
        
    }
    
};
void circleInfo::setEndPoint (ofPoint _endPoint) {
//    ofLog(OF_LOG_NOTICE, "[circleInfo] setEndPoint id: %i, %f:%f " , id, point.x, point.y);

    if (amFirst ) {
        point = _endPoint;
        goPoint = _endPoint;
        
    } else {
        goPoint = _endPoint;
        //point.x = (goPoint.x - point.x)/2;
        //point.x = (goPoint.x - point.x)/2;
    }
    
};
void circleInfo::setParentPoint (ofPoint _parentPoint) {
    point = _parentPoint;
    parentPoint = _parentPoint;
}
ofPoint circleInfo::getPoint () {
    ofPoint tpoint;
    tpoint.x = point.x *(sWidth /  inputWidth ) * 0.9 + ((1-0.9) /2) * sWidth;
    tpoint.y = point.y *( sHeight / inputHeight) * 0.9 + ((1-0.9) /2) * sHeight ;
    return tpoint;
}
float circleInfo::getOpacity () {
    return opacity / 255;
}