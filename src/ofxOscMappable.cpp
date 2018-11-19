#include "ofxOscMappable.h"

ofxOscMappable::ofxOscMappable(int id) : _id(id){}

void ofxOscMappable::addListener(ofxOscMapper & listener){
//    ofAddListener(_mapEvent, &listener, &ofxOscMapper::onMapEvent);
}

ofEvent <int> & ofxOscMappable::getMapEvent(){
	return _mapEvent;
}
