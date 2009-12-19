#include "ofxARmarker.h"

ofxARmarker::ofxARmarker()
{
    //ctor
}

ofxARmarker::~ofxARmarker()
{
    //dtor
}

void ofxARmarker::translateToMarker(){


    glLoadMatrixf( matrix );

}
