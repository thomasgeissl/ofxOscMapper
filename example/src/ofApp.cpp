#include "ofApp.h"

void ofApp::setup(){
	ofSetFrameRate(120);
	_parameters.setName("parameters");
	_mappableParameters.setName("mappable parameters");
	_mappableBoolParameter.set("bool parameter", false);
	_mappableFloatParameter.set("float parameter", 0, 0, 1);
	_mappableIntParameter.set("int parameter", 0, 0, 100);
	_mappableVoidParameter.setName("void parameter");

	_mappableParameters.add(_mappableBoolParameter);
	_mappableParameters.add(_mappableFloatParameter);
	_mappableParameters.add(_mappableIntParameter);
	_mappableParameters.add(_mappableVoidParameter);

	_oscMapper.getParameters().setName("Mapper parameters");
	_parameters.add(_oscMapper.getParameters());
	_parameters.add(_mappableParameters);

	_gui.setup(_parameters);

	_oscMapper.addParameter(_mappableBoolParameter);
	_oscMapper.addParameter(_mappableFloatParameter);
	_oscMapper.addParameter(_mappableIntParameter);
	_oscMapper.addParameter(_mappableVoidParameter);

	_oscMapper.openOscPort(8000);
}

//--------------------------------------------------------------
void ofApp::exit(){
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
	_gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	switch(key){
	 case 'l':
		 _oscMapper.loadMapping("mapping.json");
		 break;

	 case 's':
		 _oscMapper.saveMapping("mapping.json");
		 break;
	}

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
