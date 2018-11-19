#pragma once
#include "ofParameter.h"
#include "ofxOsc.h"

class ofxOscMapper;
class ofxOscMappable {
public:
    ofxOscMappable(int id);
    void addListener(ofxOscMapper & listener);
    virtual void map(ofxOscMessage & msg){}
    ofEvent<int> & getMapEvent();
    
protected:
    ofEvent<int> _mapEvent;
    int _id;
    
private:
};

