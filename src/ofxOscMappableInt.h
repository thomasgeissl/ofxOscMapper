#pragma once
#include "ofxOscMappable.h"

class ofxOscMappableInt : public ofxOscMappable {
public:
    ofxOscMappableInt(ofParameter<int> & parameter, int id) : ofxOscMappable(id), _parameter(parameter){
        parameter.addListener(this, &ofxOscMappableInt::notify);
    }
    void map(ofxOscMessage & msg){
        if(msg.getArgTypeName(0) == "f" ){
            auto newValue = ofMap(msg.getArgAsFloat(0), 0, 1, _parameter.getMin(), _parameter.getMax());
            _parameter = newValue;
        // } else if(!msg.getArgTypeName() == "i" ){
        //     _parameter = msg.getArgAsInt(0);
        }
    }
    void notify(int & value){
        _mapEvent.notify(_id);
    }
    ofParameter<int> _parameter;
};
