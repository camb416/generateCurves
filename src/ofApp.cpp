#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    gui.setup("my panel");
    gui.add(numCols.setup("cols",3,1,12));
    gui.add(numRows.setup("rows",3,1,12));
    
    
    
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushMatrix();
    ofTranslate(200,200);

    bool f = true;
    int startNum = 0;
    int stopAtNum = numCols;
    int incNum = 1;
    
    int counter = 0;
    ofSetColor(255);
    for(int i=0;i<numRows;i++){
        
        if(f){
            startNum = 0;
            stopAtNum = numCols;
            incNum = 1;
            for(int j=0;j<numCols;j++){
                ofDrawBitmapString(ofToString(counter),j*30, i*30);
                pts.push_back(new ofVec3f(j*30,i*30));

                if(i>0){
                    ofxCurve * c;
                    c = new ofxCurve(*pts[pts.size()-2], *pts[pts.size()-2], *pts[pts.size()-1]+ofVec3f(ofRandom(5.0f),ofRandom(5.0f),ofRandom(5.0f)), *pts[pts.size()-1]);
                    curves.push_back(c);
                }
                
                counter++;
            }
        } else {

            for(int j=numCols-1;j>-1;j--){
                ofDrawBitmapString(ofToString(counter),j*30, i*30);
                    pts.push_back(new ofVec3f(j*30,i*30));
                counter++;
            }
        }
      

        
        f = !f;
        
        
        
       
    }
    ofTranslate(15,15);
    ofSetColor(255,0,0);
    if(f){
        for(int j=0;j<numCols;j++){
            
            if(f){
                startNum = 0;
                stopAtNum = numCols;
                incNum = 1;
                for(int i=0;i<numRows;i++){
                    ofDrawBitmapString(ofToString(counter),j*30, i*30);
                    pts.push_back(new ofVec3f(j*30,i*30));
                    
                    counter++;
                }
            } else {
                
                for(int i=numRows-1;i>-1;i--){
                    ofDrawBitmapString(ofToString(counter),j*30, i*30);
                    pts.push_back(new ofVec3f(j*30,i*30));
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
                    ofDrawBitmapString(ofToString(counter),j*30, i*30);
                    pts.push_back(new ofVec3f(j*30,i*30));
                    
                    counter++;
                }
            } else {
                
                for(int i=numRows-1;i>-1;i--){
                    ofDrawBitmapString(ofToString(counter),j*30, i*30);
                    pts.push_back(new ofVec3f(j*30,i*30));
                    counter++;
                }
            }
            
            
            
            f = !f;
            
            
            
            
        }
    }

    
    
    
    
    //ofBeginShape();
    ofNoFill();
    for(int i=0;i<pts.size()-1;i++){
        if(i%numCols==0){
            ofSetColor(255,255,0);
        } else {
            ofSetColor(0,255,0);
        }
        ofDrawLine(*pts.at(i), *pts.at(i+1));
        //ofVertex(pts.at(i)->x,pts.at(i)->y);
    }
    
    for(int i=0;i<curves.size();i++){
        curves.at(i)->update();
        curves.at(i)->draw();
    }
    
    curves.clear();
    //ofEndShape(false);
    pts.clear();
    ofPopMatrix();
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
