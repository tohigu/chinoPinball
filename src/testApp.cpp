#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	// setup OF
    //ofSetFrameRate(60);
	//ofSetVerticalSync(true);
	ofBackground( 10, 10, 10);
#ifdef USE_SYPHON
    mainOutputSyphonServer.setName("Screen Output");
#endif

	chinopinball.setup();
	
}

//--------------------------------------------------------------
void testApp::update() {
    
    chinopinball.update();
    
}

//--------------------------------------------------------------
void testApp::draw() {
    
    chinopinball.draw();
#ifdef USE_SYPHON
    mainOutputSyphonServer.publishScreen();
#endif
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
    chinopinball.keyPressed(key);
	

	if(key == OF_KEY_F1){
		ofSetLogLevel(OF_LOG_SILENT); //Play ChinoP clean of COUTS!
	}
	else if(key == OF_KEY_F2){
		ofSetLogLevel(OF_LOG_VERBOSE); //Set active all Verbose commets (OF verboses included)
	}
	else if(key == OF_KEY_F3){
		ofLog(OF_LOG_VERBOSE, "CollisionVerbose");
		ofSetLogLevel("CollisionVerbose", OF_LOG_VERBOSE); //check COUTS from Collisions
	}
	else if(key == OF_KEY_F4){
		ofLog(OF_LOG_VERBOSE, "EditorVerbose");
		ofSetLogLevel("EditorVerbose", OF_LOG_VERBOSE); //check COUTS from Editor mode.
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {
    chinopinball.keyReleased(key);
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo) {

}