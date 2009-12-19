#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxAR.h"


#define _USE_LIVE_VIDEO		// uncomment this to use a live camera
								// otherwise, we'll use a movie file


class testApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
        void keyReleased(int key);

		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);


        ofxAR   ar;

		ofVideoGrabber grabber;
		ofxCvColorImage convert;
		ofxCvGrayscaleImage gray;
		ofVideoPlayer sampleVideo;
		ofImage       sampleImage, sampleImage2;

        int width, height;

		bool bDraw;

		ofTrueTypeFont idNumb;
};

#endif
