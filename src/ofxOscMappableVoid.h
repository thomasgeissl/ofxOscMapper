#pragma once
#include "ofxOscMappable.h"

class ofxOscMappableVoid : public ofxOscMappable {
public:
    ofxOscMappableVoid(ofParameter <void> & parameter, int id) : ofxOscMappable(id), _parameter(parameter){
        parameter.addListener(this, &ofxOscMappableVoid::notify);
    }
    void map(ofxOscMessage & msg){
        _parameter.trigger();
    }
    void notify(){
        _mapEvent.notify(_id);
    }
    ofParameter <void> _parameter;
};
