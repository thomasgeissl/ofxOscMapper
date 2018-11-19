#include "ofxOscMapper.h"

ofxOscMapper::ofxOscMapper() : _idCounter(0){
	_parameters.setName("parameters");
	_activeParameter.set("on/off", true);
	_activeMappingParameter.set("mapping mode", false);

	_parameters.add(_activeParameter);
	_parameters.add(_activeMappingParameter);
}
void ofxOscMapper::update(){
	if(!_activeParameter){
		return;
	}
	while(_oscReceiver.hasWaitingMessages()){
		ofxOscMessage m;
		_oscReceiver.getNextMessage(m);
		 if(_activeMappingParameter){
			 if(_idOfMappable != -1){
				 addMapping(m.getAddress(), _idOfMappable);
                 _idOfMappable = -1;
			 }
         }
         if(doesMappingExist(m.getAddress())){
             auto id = getMappedId(m.getAddress());
             if(doesMappableExist(id)){
                 getMappable(id)->map(m);
             }
         }
	}
}
void ofxOscMapper::addParameter(ofParameter <bool> & parameter){
	ofxOscMappableBool * mappable = new ofxOscMappableBool(parameter, ++_idCounter);

	ofAddListener(mappable->getMapEvent(), this, &ofxOscMapper::onMapEvent);
	_mappables[_idCounter] = mappable;
}
void ofxOscMapper::addParameter(ofParameter <float> & parameter){
	ofxOscMappableFloat * mappable = new ofxOscMappableFloat(parameter, ++_idCounter);
//    mappable.addListener(*this);
	ofAddListener(mappable->getMapEvent(), this, &ofxOscMapper::onMapEvent);
	_mappables[_idCounter] = mappable;
}
void ofxOscMapper::addParameter(ofParameter <int> & parameter){
	ofxOscMappableInt * mappable = new ofxOscMappableInt(parameter, ++_idCounter);
//    mappable.addListener(*this);
	ofAddListener(mappable->getMapEvent(), this, &ofxOscMapper::onMapEvent);
	_mappables[_idCounter] = mappable;
}
void ofxOscMapper::addParameter(ofParameter <void> & parameter){
	ofxOscMappableVoid * mappable = new ofxOscMappableVoid(parameter, ++_idCounter);
//    mappable.addListener(*this);
	ofAddListener(mappable->getMapEvent(), this, &ofxOscMapper::onMapEvent);
	_mappables[_idCounter] = mappable;
}
void ofxOscMapper::addParameters(ofParameterGroup & parameters){
    for(auto parameter : parameters){
        auto type = parameter->type();
        if(type == "11ofParameterIvE"){
            auto typedParameter = parameter->cast<void>();
            addParameter(typedParameter);
        }else if(type == "11ofParameterIbE"){
            auto typedParameter = parameter->cast<bool>();
            addParameter(typedParameter);
        }else if(type == "11ofParameterIiE"){
            auto typedParameter = parameter->cast<int>();
            addParameter(typedParameter);
        }else if(type == "11ofParameterIfE"){
            auto typedParameter = parameter->cast<float>();
            addParameter(typedParameter);
        }
    }
}
void ofxOscMapper::openOscPort(int port){
	_oscReceiver.setup(port);
}

bool ofxOscMapper::addMapping(std::string address, int id, bool force){
	if(doesMappingExist(address)){
		ofLogWarning("ofxOscMapper") << "mapping does already exist: " << address;
		if(force){
			_mapping[address] = id;
			return true;
		}else{
			return false;
		}
	}else{
		_mapping[address] = id;
        ofLogNotice("ofxOscMapper") << "added mapping: " << address;
		return true;
	}
}
bool ofxOscMapper::removeMapping(std::string address){
	if(doesMappingExist(address)){
		_mapping.erase(_mapping.find(address));
		return true;
	}else{
		ofLogWarning("ofxOscMapper") << "mapping does not exist. are you sure you are doing right?";
		return false;
	}
}

bool ofxOscMapper::doesMappingExist(std::string address){
	return (_mapping.find(address) != _mapping.end());
}

bool ofxOscMapper::doesMappableExist(int id){
	return (_mappables.find(id) != _mappables.end());
}

int ofxOscMapper::getMappedId(std::string address){
	if(doesMappingExist(address)){
		return _mapping[address];
	}else{
//        TODO: better throw an exception instead of returning -1?
		ofLogError("ofxOscMapper") << "mapping does not exist. returning -1";
		return -1;
	}
}

ofxOscMappable * ofxOscMapper::getMappable(int id){
	if(doesMappableExist(id)){
		return _mappables[id];
	}else{
//        TODO: better throw an exception instead of returning nullptr?
		ofLogError("ofxOscMapper") << "mappable does not exit. returning nullptr";
		return nullptr;
	}
}

ofParameterGroup & ofxOscMapper::getParameters(){
	return _parameters;
}


void ofxOscMapper::onMapEvent(int & idOfMappable){
	if(_activeMappingParameter){
		_idOfMappable = idOfMappable;
	}
}

bool ofxOscMapper::loadMapping(string path){
	ofFile mappingFile;
	ofJson mappingJson;
	// mappingFile.open(ofToDataPath(path));
	// if(mappingFile.exists()){
    //     mappingFile >> mappingJson;
    //     ofLogNotice("ofxOscMapper") << "successfully loaded mappings " << mappingJson.dump(4);
    //     _mapping.clear();

    //     for(auto mapping : mappingJson["mappings"]){
    //         addMapping(mapping["channel"].get<int>(), mapping["pitchOrCC"].get<int>(), mapping["isCC"].get<bool>(), mapping["id"].get<int>());
    //     }
	// }else{
	// 	ofLogError("ofxOscMapper") << ofToDataPath(path) << " does not exist";
	// 	return false;
	// }
}

bool ofxOscMapper::saveMapping(string path, bool force){
	// ofFile mappingFile;
	// mappingFile.open(ofToDataPath(path), ofFile::ReadWrite);
	// if(mappingFile.exists() && !force){
	// 	ofLogError("ofxOscMapper") << ofToDataPath(path) << " already exists.";
	// 	return false;
	// }else{
	// 	mappingFile.create();
	// }
	// ofJson mappingJson;

	// mappingJson["mappings"] = ofJson::array();
	// for(auto mapping : _mapping){
	// 	int channel = std::get<0>(mapping.first);
	// 	int pitchOrCC = std::get<1>(mapping.first);
	// 	bool isCC = std::get<2>(mapping.first);

	// 	int id = mapping.second;
    //     // TODO: add parameter name for better debugging or manually removing entries
    //     mappingJson["mappings"].push_back({{"channel", channel}, {"pitchOrCC", pitchOrCC}, {"isCC", isCC}, {"id", id}});
	// }
	// mappingFile << mappingJson.dump(4);
	// mappingFile.close();
	return true;
}
