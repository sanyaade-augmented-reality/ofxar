#include "ofxAR.h"

ofxAR::ofxAR()
{
    //ctor
}

ofxAR::~ofxAR()
{
    //dtor
}

void ofxAR::setup(int w, int h, string cameraFilePath, string markerFilePath){


    static ARLogger      logger;

	bpp = 1;
	useBCH = true;


    width = w;
    height = h;

    numPixels = width*height*bpp;
	cameraBuffer = new unsigned char[numPixels];

    	// ----------------------------------  AR TK+ STUFF - ripped from the single marker demo app

    // create a tracker that does:
    //  - 6x6 sized marker images
    //  - samples at a maximum of 6x6
    //  - works with luminance (gray) images
    //  - can load a maximum of 10 patterns
    //  - can detect a maximum of 10 patterns in one image


	tracker = new ARToolKitPlus::TrackerMultiMarkerImpl<6, 6, 6, 10, 10>(width,height);


	const char* description = tracker->getDescription();
	printf("ARToolKitPlus compile-time information:\n%s\n\n", description);

    // set a logger so we can output error messages
    tracker->setLogger(&logger);
	tracker->setPixelFormat(ARToolKitPlus::PIXEL_FORMAT_LUM);

    if( !tracker->init( cameraFilePath.c_str(), markerFilePath.c_str(), 1.0f, 1000.0f) )            // load std. ARToolKit camera file
	{
		ofLog(OF_LOG_ERROR, "ERROR: init() failed");
		delete cameraBuffer;
		delete tracker;
		return;
	}

    // define size of the marker
    //tracker->setPatternWidth(80); // I'm not sure how to define the size with multimarkers since it doesnt seem to have this option.

	// the marker in the BCH test image has a thin border...
    tracker->setBorderWidth(useBCH ? 0.125f : 0.250f);

    // set a threshold. alternatively we could also activate automatic thresholding
    //tracker->setThreshold(20);
	tracker->activateAutoThreshold(true);
    // let's use lookup-table undistortion for high-speed
    // note: LUT only works with images up to 1024x1024
    tracker->setUndistortionMode(ARToolKitPlus::UNDIST_LUT);

    // RPP is more robust than ARToolKit's standard pose estimator
    tracker->setPoseEstimator(ARToolKitPlus::POSE_ESTIMATOR_RPP);

    // switch to simple ID based markers
    // use the tool in tools/IdPatGen to generate markers
    tracker->setMarkerMode(useBCH ? ARToolKitPlus::MARKER_ID_BCH : ARToolKitPlus::MARKER_ID_SIMPLE);

}

void ofxAR::update(unsigned char * img){
    //find the marker and get back the confidence
    int markerId = tracker->calc(img);

    //ofLog(OF_LOG_VERBOSE, "ofxAR::update - Marker confidence = %i", markerId);

    //rawNumDetected = tracker->getNumDetectedMarkers();
    //ofLog(OF_LOG_VERBOSE, "ofxAR::update - Number of markers: %i", rawNumDetected);

    rawMarkers.clear();
    robustMarkers.clear();

    // Take each found marker and update the rawMarkers and update the robustMarkers

    for(int i=0; i<tracker->getNumDetectedMarkers(); i++) {

        rawMarkers.push_back(tracker->getDetectedMarker(i));

        ofxARmarker tmpRobustMarker;

        tmpRobustMarker.markerData = tracker->getDetectedMarker(i);

        float* cm = getMatrix(i);

        for (int g = 0; g < 16; g++){
            tmpRobustMarker.matrix[g] = cm[g];
        }

        tmpRobustMarker.id = tmpRobustMarker.markerData.id;
        robustMarkers.push_back(tmpRobustMarker);

    }

}

void ofxAR::drawSetupView(int w, int h){
    glViewport(0, 0, w, h );
	glMatrixMode( GL_PROJECTION );
	glLoadMatrixf(tracker->getProjectionMatrix());
}

float* ofxAR::getMatrix(int markerN){

    ARToolKitPlus::ARMarkerInfo marker = tracker->getDetectedMarker(markerN);

    float m34[ 3 ][ 4 ];
    float c[ 2 ] = { 0.0f, 0.0f };
    float w = 40.0f;

    tracker->rppGetTransMat( &marker, c, w, m34 );

    float m[ 16 ]; //this is some crazy matrix transformative stuff. I think initially it came out of one of the arToolkit functions.... but i got it from here: http://chihara.naist.jp/people/STAFF/imura/computer/OpenGL/artp/disp_content
    //float* m;
    for ( int i = 0; i < 3; i++ ) {
        for ( int j = 0; j < 4; j++ ) {
            m[ j * 4 + i ] = m34[ i ][ j ];
        }
    }
    for ( int j = 0; j < 3; j++ ) {
        m[ j * 4 + 3 ] = 0.0f;
    }
    m[ 3 * 4 + 3 ] = 1.0f;

    return m;
}


int ofxAR::getRawDetectedN(){
    return rawNumDetected;
}

