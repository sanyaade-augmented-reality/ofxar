#ifndef OFXAR_H
#define OFXAR_H

#include "ARToolKitPlus/TrackerMultiMarkerImpl.h"

#include "ofxARmarker.h"

#include "ofMain.h"


class ARLogger : public ARToolKitPlus::Logger
{
    void artLog(const char* nStr)
    {
        string message1 = "ofxAR::LOGGER - ";
        string message2 = nStr;
        string message = message1 + message2;
        ofLog(OF_LOG_VERBOSE, message);
    }
};

class ofxAR
{
    public:
        ofxAR();
        virtual ~ofxAR();

        void setup(int w, int h, string cameraFilePath, string markerFilePath);
        void update(unsigned char * img);
        void drawSetupView(int w, int h);
        int  getRawDetectedN();
        float* getMatrix(int markerN);

        vector <ARToolKitPlus::ARMarkerInfo> rawMarkers;
        vector <ofxARmarker>                 robustMarkers;

        int             rawNumDetected;

		int             width, height, bpp;
		size_t          numPixels;
		size_t          numBytesRead;
		unsigned char   *cameraBuffer;
		bool            useBCH;


        ARToolKitPlus::TrackerMultiMarker *tracker;

    protected:
    private:
};

#endif // OFXAR_H
