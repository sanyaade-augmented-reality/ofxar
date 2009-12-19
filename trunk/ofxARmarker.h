#ifndef OFXARMARKER_H
#define OFXARMARKER_H

#include "ARToolKitPlus/TrackerMultiMarkerImpl.h"

#include "ofMain.h"

class markerHistory {
    float matrix [16];
};

class ofxARmarker
{
    public:
        ofxARmarker();
        virtual ~ofxARmarker();

        void translateToMarker();
        int  id;

        float matrix [16];

        vector <markerHistory> history;

        ARToolKitPlus::ARMarkerInfo markerData;

    protected:
    private:
};




#endif // OFXARMARKER_H
