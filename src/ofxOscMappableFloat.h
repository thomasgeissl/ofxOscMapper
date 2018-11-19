#pragma once
#include "ofxOscMappable.h"

class ofxOscMappableFloat : public ofxOscMappable {
public:
    ofxOscMappableFloat(ofParameter<float> & parameter, int id) : ofxOscMappable(id), _parameter(parameter){
        parameter.addListener(this, &ofxOscMappableFloat::notify);
    }
    void map(ofxOscMessage & msg){
        if(msg.getArgTypeName(0) != "f") return;

        auto newValue = ofMap(msg.getArgAsFloat(0), 0, 1, _parameter.getMin(), _parameter.getMax());
        _parameter = newValue;
    }
    void notify(float & value){
        _mapEvent.notify(_id);
    }
    ofParameter<float> _parameter;
};
