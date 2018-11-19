#pragma once
#include "ofxOscMappable.h"

class ofxOscMappableString : public ofxOscMappable {
public:
    ofxOscMappableString(ofParameter <std::string> & parameter, int id) : ofxOscMappable(id), _parameter(parameter){
        _parameter.addListener(this, &ofxOscMappableString::notify);
    }
    void map(ofxOscMessage & msg){
        if(msg.getArgTypeName(0) == "s"){
            auto newValue = msg.getArgAsString(0);
            _parameter = newValue;
        } 
    }
    void notify(std::string & value){
        _mapEvent.notify(_id);
    }
    ofParameter<std::string> _parameter;
};
