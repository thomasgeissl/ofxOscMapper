#pragma once
#include "ofxOscMappable.h"

class ofxOscMappableBool : public ofxOscMappable {
public:
    ofxOscMappableBool(ofParameter <bool> & parameter, int id) : ofxOscMappable(id), _parameter(parameter){
        _parameter.addListener(this, &ofxOscMappableBool::notify);
    }
    void map(ofxOscMessage & msg){

        auto newValue = _parameter;
        if(msg.getArgTypeName(0) == "F" || msg.getArgTypeName(0) == "T"){
            newValue = msg.getArgAsBool(0);
        } else if(msg.getArgTypeName(0) == "f"){
            newValue = msg.getArgAsFloat(0) > 0;
        } else if(msg.getArgTypeName(0) == "i"){
            newValue = msg.getArgAsInt(0) > 0;
        } else {
            ofLogWarning("ofxOscMapper") << "cannot map osc message of type "<<msg.getArgTypeName(0);
        }
 
        _parameter = newValue;
    }
    void notify(bool & value){
        _mapEvent.notify(_id);
    }
    ofParameter<bool> _parameter;
};
