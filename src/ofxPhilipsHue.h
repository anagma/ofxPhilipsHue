//
//  ofxPhilipsHue.h
//  ofxHttpForm example
//
//  Created by Oriol Ferrer Mesià on 28/12/13.
//
//

#ifndef __ofxPhilipsHue__
#define __ofxPhilipsHue__

#include "ofMain.h"

//TODO clean up this mess of unnecessary includes!
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/StreamCopier.h"
#include "Poco/Path.h"
#include "Poco/URI.h"
#include "Poco/Exception.h"
#include "Poco/Mutex.h"
#include "Poco/Net/FilePartSource.h"

#include "ofxJsonxx.h"

using namespace Poco::Net;
using namespace Poco;
using Poco::Exception;
using Poco::Net::HTTPClientSession;


typedef struct {
	int id;
	string name;
	bool on;
	int brightness;
	int hue;
	int saturation;
} ofxPhilipsHueLight;

typedef struct{
	int id;
	string name;
	
	bool on;
	int brightness;
	int hue;
	int saturation;

	vector<int> lightsId;
} ofxPhilipsHueGroup;

class ofxPhilipsHue{

public:

	ofxPhilipsHue();

	//you will need the bridge IP address
	//and the API username (follow this http://developers.meethue.com/gettingstarted.html)
	void setup(string bridgeIP, string userName);

	//all values mapped to [0..1] range
	void setLightState(	int lightID,
					   bool state,
					   float brightness = -1.0,
					   float saturation = -1.0,
					   float hue = -1.0,
					   int transitionDuration = 0/*ms*/
	);

	void setLightState(	int lightID,
					   bool state,
					   ofColor color,
					   int transitionDuration = 0/*ms*/
	);

	void blinkLightOnce(int lightID);
	
	void setGroupState(int groupId,
					   bool state,
					   float brightness = -1.0,
					   float saturation = -1.0,
					   float hue = -1.0,
					   int transitionDuration = 0/*ms*/
	);
	
	vector<ofxPhilipsHueLight> getLights();
	vector<ofxPhilipsHueGroup> getGroups();

private:

	bool sendCommand(int lightID, string json);
	string bridge;
	string apiUser;
	
	
	string sendGetCommand(	string uri, string json="");
	string sendPutCommand(	string uri, string json="");
	string sendPostCommand(	string uri, string json="");
	string sendDeleteCommand(	string uri, string json="");
	
	string sendRequest(string requestType, string uri, string json="");
};


#endif /* defined(__ofxPhilipsHue__) */
