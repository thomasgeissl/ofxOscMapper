#pragma once

#include <tuple>

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxOscMappable.h"
#include "ofxOscMappableBool.h"
#include "ofxOscMappableFloat.h"
#include "ofxOscMappableInt.h"
#include "ofxOscMappableVoid.h"
#include "ofxOscMappableString.h"


class ofxOscMapper{
	public:
		ofxOscMapper();
		void update();
		void addParameter(ofParameter <bool> & parameter);
		void addParameter(ofParameter <float> & parameter);
		void addParameter(ofParameter <int> & parameter);
		void addParameter(ofParameter <void> & parameter);
		void addParameter(ofParameter <std::string> & parameter);
        void addParameters(ofParameterGroup & parameters);

		void openOscPort(int port);

		bool addMapping(std::string address, int id, bool force = true);
		bool removeMapping(std::string address);

		bool doesMappingExist(std::string address);
		bool doesMappableExist(int id);
		int getMappedId(std::string address);
		ofxOscMappable * getMappable(int id);
		ofParameterGroup & getParameters();
		void onMapEvent(int & idOfMappable);

		bool loadMapping(std::string path);
		bool saveMapping(std::string path, bool force = true);

	private:
		ofxOscReceiver _oscReceiver;
		std::map<int, ofxOscMappable*> _mappables;
		std::map<std::string, int> _mapping;
        std::vector<ofParameter<bool>> _params;

		ofParameterGroup _parameters;
		ofParameter <bool> _activeParameter;
		ofParameter <bool> _activeMappingParameter;

		int _idOfMappable;
        int _idCounter;
};
