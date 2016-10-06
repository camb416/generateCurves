#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    // print input ports to console
    midiIn.listPorts(); // via instance
    //ofxMidiIn::listPorts(); // via static as well
    
    // open port by number (you may need to change this)
    midiIn.openPort(0);
    //midiIn.openPort("IAC Pure Data In");	// by name
    //midiIn.openVirtualPort("ofxMidiIn Input"); // open a virtual port
    
    // don't ignore sysex, timing, & active sense messages,
    // these are ignored by default
    midiIn.ignoreTypes(false, false, false);
    
    // add ofApp as a listener
    midiIn.addListener(this);
    
    // print received messages to the console
    midiIn.setVerbose(true);

    
    
    gui.setup("my panel");
    gui.add(numCols.setup("cols",11,11,127));
    gui.add(numRows.setup("rows",11,11,127));
    gui.add(scale.setup("scale",100,1,300));
    gui.add(tipScale.setup("tip scale",1.0f,0.1f,3.0f));
    gui.add(edgeScale.setup("edge scale",1.0f,0.1f,3.0f));
    gui.add(depth.setup("depth",0.0f,10.0f,100.0f));
    gui.add(rotX.setup("x rot", 0.0f,0.0f,360));
    gui.add(rotY.setup("y rot", 0.0f,0.0f,360));
    gui.add(rotZ.setup("z rot", 0.0f,0.0f,360));
    gui.add(tranX.setup("x tran", 150.0f,0.0f,1000.0f));
    gui.add(tranY.setup("y tran", 0.0f,-500.0f,500.0f));
    gui.add(tranZ.setup("z tran", 0.0f,-1000.0f,1000.0f));
    gui.add(regenBtn.setup("regen curve"));
    gui.add(bDrawControls.setup("draw control pts",true));
    gui.add(bDrawBigDots.setup("draw intersections", true));
    regenBtn.addListener(this, &ofApp::generateCurve);
    
    
    
    
    gui.loadFromFile("settings.xml");
    
    
    bPauseDraw = true;
    
    generateCurve();
    
    
}

void ofApp::generateCurve(){
    bPauseDraw = true;
    pts.clear();
    curves.clear();
    
    bool f = true;
    int startNum = 0;
    int stopAtNum = numCols;
    int incNum = 1;
    
    int counter = 0;
    for(int i=0;i<numRows;i++){
        
        if(f){
            startNum = 0;
            stopAtNum = numCols;
            incNum = 1;
            for(int j=0;j<numCols;j++){
                pts.push_back(new ofVec3f(j*scale,i*scale));
                
                counter++;
            }
        } else {
            
            for(int j=numCols-1;j>-1;j--){

                pts.push_back(new ofVec3f(j*scale,i*scale));
                
                counter++;
            }
        }
        
        
        
        f = !f;
        
        
        
        
    }

    if(f){
        for(int j=0;j<numCols;j++){
            
            if(f){
                startNum = 0;
                stopAtNum = numCols;
                incNum = 1;
                for(int i=0;i<numRows;i++){

                    pts.push_back(new ofVec3f(j*scale,i*scale));
                    
                    counter++;
                }
            } else {
                
                for(int i=numRows-1;i>-1;i--){

                    pts.push_back(new ofVec3f(j*scale,i*scale));
                    counter++;
                }
            }
            
            
            
            f = !f;
            
            
            
            
        }
        
    } else {
        for(int j=numCols-1;j>-1;j--){
            
            if(f){
                startNum = 0;
                stopAtNum = numCols;
                incNum = 1;
                for(int i=0;i<numRows;i++){

                    pts.push_back(new ofVec3f(j*scale,i*scale));
                    
                    counter++;
                }
            } else {
                
                for(int i=numRows-1;i>-1;i--){

                    pts.push_back(new ofVec3f(j*scale,i*scale));
                    counter++;
                }
            }
            
            
            
            f = !f;
            
            
            
            
        }
    }
    
    
    ofxCurve * c;
    float d = depth;
    ofVec3f dv = ofVec3f(0,0,d);
    c = new ofxCurve(*pts[0] + dv, *pts[0]+ofVec3f(0,-scale*tipScale,d), *pts[0]+ofVec3f(-scale*tipScale,0,-d), *pts[0] - dv);
   curves.push_back(c);
    d = -d;
    dv = -dv;
    for(int i=0;i<pts.size();i++){
        ofxCurve * c;
        ofVec3f v = ofVec3f(0,0,0);
        ofVec3f v2 = v;
        if(i>0){
            if((i)%numCols==0){
                
                
                if(pts[i]->x == pts[i-1]->x &&
                   pts[i]->y == pts[i-1]->y){
                    v = ofVec3f(scale*tipScale,0,d);
                    v2 = ofVec3f(0,scale*tipScale,-d);
                    
                } else if(pts[i-2]->x > pts[i-1]->x){
                    v  = ofVec3f(-scale*edgeScale,0,d);
                    v2 = ofVec3f(-scale*edgeScale,0,-d);
                } else if(pts[i-2]->x < pts[i-1]->x){
                    v  = ofVec3f(scale*edgeScale,0,d);
                    v2 = ofVec3f(scale*edgeScale,0,-d);
                } else if(pts[i-2]->y > pts[i-1]->y){
                    v  = ofVec3f(0,-scale*edgeScale,d);
                    v2 = ofVec3f(0,-scale*edgeScale,-d);
                } else if(pts[i-2]->y < pts[i-1]->y){
                    v  = ofVec3f(0,scale*edgeScale,d);
                    v2 = ofVec3f(0,scale*edgeScale,-d);
                }
                
                c = new ofxCurve(*pts[i-1]+dv, *pts[i-1]+v, *pts[i]+v2, *pts[i]-dv);
                curves.push_back(c);
                 d = -d;
                 dv = -dv;
                
            } else{
                c = new ofxCurve(*pts[i-1]+dv, (*pts[i-1]+*pts[i])/2.0f+dv, (*pts[i-1]+*pts[i])/2.0f-dv, *pts[i]-dv);
                curves.push_back(c);
                 d = -d;
                dv = -dv;
            }
        }
    }
    bPauseDraw = false;
    
}


//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    if(!bPauseDraw){
        
        ofBackground(0);
        ofSetColor(255);
        ofPushMatrix();
        ofTranslate(tranX,tranY,tranZ);

        ofRotateX(rotX);
        ofRotateY(rotY);
        ofRotateZ(rotZ);
        
        ofNoFill();
        for(int i=0;i<pts.size()-1;i++){
            ofFill();
            if(bDrawBigDots) ofDrawEllipse(*pts.at(i), 15, 15);
        }
        ofNoFill();
        for(int i=0;i<curves.size();i++){
            curves.at(i)->update();
            curves.at(i)->draw(bDrawControls);
        }
        
        ofPopMatrix();
    }
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    generateCurve();
}

void ofApp::newMidiMessage(ofxMidiMessage& msg) {
    
    // make a copy of the latest message
    midiMessage = msg;
    ofLog() << midiMessage.control;
    
    switch(midiMessage.control){
        case 81:
            numCols = ofMap(midiMessage.value,0,127,numCols.getMin(),numCols.getMax());
            break;
        case 82:
            numRows = ofMap(midiMessage.value,0,127,numRows.getMin(),numRows.getMax());
            break;
        case 83:
            scale = ofMap(midiMessage.value,0,127,scale.getMin(),scale.getMax());
            break;
        case 84:
            tipScale = ofMap(midiMessage.value,0,127,tipScale.getMin(),tipScale.getMax());
            break;
        case 85:
            edgeScale = ofMap(midiMessage.value,0,127,edgeScale.getMin(),edgeScale.getMax());
            break;
        case 86:
            depth = ofMap(midiMessage.value,0,127,depth.getMin(),depth.getMax());
            break;
        case 87:
            rotX = ofMap(midiMessage.value,0,127,rotX.getMin(),rotX.getMax());
            break;
        case 88:
            rotY = ofMap(midiMessage.value,0,127,rotY.getMin(),rotY.getMax());
            break;
        case 89:
            rotZ = ofMap(midiMessage.value,0,127,rotZ.getMin(),rotZ.getMax());
            break;
        case 90:
            tranX = ofMap(midiMessage.value,0,127,tranX.getMin(),tranX.getMax());
            break;
        case 91:
            tranY = ofMap(midiMessage.value,0,127,tranY.getMin(),tranY.getMax());
            break;
        case 92:
            tranZ = ofMap(midiMessage.value,0,127,tranZ.getMin(),tranZ.getMax());
            break;
        case 65:
            generateCurve();
            break;
        case 66:
            bDrawControls = !bDrawControls;
            break;
        case 67:
            bDrawBigDots = !bDrawBigDots;
            break;
    }
    
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
void ofApp::exit() {
    
    // clean up
    midiIn.closePort();
    midiIn.removeListener(this);
}
