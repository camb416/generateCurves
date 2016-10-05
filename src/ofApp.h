#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxCurve.h"

#include "ofxMidi.h"


class ofApp : public ofBaseApp, public ofxMidiListener{

	public:
		void setup();
		void update();
		void draw();
    
    void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    ofxPanel gui;
    ofxIntSlider numCols;
    ofxIntSlider numRows;
    ofxFloatSlider scale;
    ofxFloatSlider depth;
    ofxFloatSlider tipScale;
    ofxFloatSlider edgeScale;
    ofxFloatSlider rotX;
    ofxFloatSlider rotY;
    ofxFloatSlider rotZ;
    ofxFloatSlider tranX;
    ofxFloatSlider tranY;
    ofxFloatSlider tranZ;
    ofxToggle bDrawControls;
    ofxToggle bDrawBigDots;
    
    ofxButton regenBtn;
    
    
    vector<ofVec3f*> pts;
    vector<ofxCurve*> curves;
    
    void generateCurve();
    
    
    // midi stuff
    void newMidiMessage(ofxMidiMessage& eventArgs);
    
    stringstream text;
    
    ofxMidiIn midiIn;
    ofxMidiMessage midiMessage;
    
    
    
};
