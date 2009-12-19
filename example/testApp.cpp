#include "testApp.h"




//--------------------------------------------------------------
void testApp::setup(){

    ofSetFrameRate(30);

    ofSetLogLevel(OF_LOG_VERBOSE);

    width = 640;
    height = 480;

    grabber.setVerbose(true);
	grabber.initGrabber(width, height);
	convert.allocate(width, height);
	gray.allocate(width, height);



	bDraw = false;


	ofBackground(127,127,127);

	idNumb.loadFont("frabk.ttf", 24);

    //sampleVideo.loadMovie("movies/Matrixclip.mov");
    //sampleVideo.setUseTexture(true);
    //sampleVideo.play();

    sampleImage.loadImage("faces.jpg");
    sampleImage2.loadImage("icecream.jpg");


    ar.setup(width, height, "data/unibrain-4.3mm.dat", "data/markerboard_480-499.cfg");

}

//--------------------------------------------------------------
void testApp::update(){


	grabber.grabFrame();
	if(grabber.isFrameNew())
	{

		//convert our camera frame to grayscale
		convert.setFromPixels(grabber.getPixels(), width, height);
		gray = convert;

        ar.update(gray.getPixels());

	}

	//sampleVideo.idleMovie();


    //if(sampleVideo.getIsMovieDone()){
    //    sampleVideo.play();
    //}


}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(0xffffff);
	glDisable(GL_DEPTH_TEST);
	grabber.draw(0, 0, ofGetWidth(), ofGetHeight());

    ar.drawSetupView(ofGetWidth(), ofGetHeight());

    glMatrixMode( GL_MODELVIEW );
    glEnable(GL_DEPTH_TEST);

	for(int i=0; i<ar.robustMarkers.size(); i++)
	{

        ar.robustMarkers[i].translateToMarker();

		glPushMatrix();
		glRotatef(-90, 0, 0, 1);
		ofSetColor(255 , 255, 255 );
		//grabber.draw(-30,-20,60,40);
		//sampleVideo.draw(-31,-20,60,40);
		//if (marker.id == 486) sampleImage2.draw(-31,-20,60,40);
		//else sampleImage.draw(-80,-50,160,100);

		sampleImage.draw(-80,-50,160,100);

		/*glPopMatrix();


		glPushMatrix();
		glRotatef(90, 1, 0, 0);
		glRotatef(-90, 0, 1, 0);
		ofSetColor(255 , 255, 255 );
		//idNumb.drawString(ofToString(marker.id), -idNumb.stringWidth(ofToString(marker.id))/2,0);
		glTranslatef(0, 50, -50);

        //if (marker.id == 486) sampleImage2.draw(-31,-20,60,40);
		//else sampleImage.draw(-80,-50,160,100);

		glPopMatrix();*/

	}

}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
		if(key == 'g') grabber.videoSettings();

 		if(key == 's') {

            static char fileNameStr[255];
            sprintf(fileNameStr, "output_%0.4i.png", ofGetFrameNum());
            static ofImage imgScreen;
            imgScreen.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
            printf("Saving file: %s\n", fileNameStr);
            imgScreen.saveImage(fileNameStr);

 		}



}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}
