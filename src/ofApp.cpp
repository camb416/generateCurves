#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    gui.setup("my panel");
    gui.add(numCols.setup("cols",3,1,12));
    gui.add(numRows.setup("rows",3,1,12));
    gui.add(scale.setup("scale",100,10,300));
    gui.add(tipScale.setup("tip scale",1.0f,0.1f,3.0f));
    gui.add(edgeScale.setup("edge scale",1.0f,0.1f,3.0f));
    
    
    gui.loadFromFile("settings.xml");
    
    
    generateCurve();
    
    
}

void ofApp::generateCurve(){
    
    pts.clear();
    curves.clear();
    
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
                ofDrawBitmapString(ofToString(counter),j*scale, i*scale);
                pts.push_back(new ofVec3f(j*scale,i*scale));
                
                //                if(i>0){
                //                    ofxCurve * c;
                //                    c = new ofxCurve(*pts[pts.size()-2], *pts[pts.size()-2], *pts[pts.size()-1]+ofVec3f(ofRandom(5.0f),ofRandom(5.0f),ofRandom(5.0f)), *pts[pts.size()-1]);
                //                    curves.push_back(c);
                //                }
                
                counter++;
            }
        } else {
            
            for(int j=numCols-1;j>-1;j--){
                ofDrawBitmapString(ofToString(counter),j*scale, i*scale);
                pts.push_back(new ofVec3f(j*scale,i*scale));
                
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
                    ofDrawBitmapString(ofToString(counter),j*scale, i*scale);
                    pts.push_back(new ofVec3f(j*scale,i*scale));
                    
                    counter++;
                }
            } else {
                
                for(int i=numRows-1;i>-1;i--){
                    ofDrawBitmapString(ofToString(counter),j*scale, i*scale);
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
                    ofDrawBitmapString(ofToString(counter),j*scale, i*scale);
                    pts.push_back(new ofVec3f(j*scale,i*scale));
                    
                    counter++;
                }
            } else {
                
                for(int i=numRows-1;i>-1;i--){
                    ofDrawBitmapString(ofToString(counter),j*scale, i*scale);
                    pts.push_back(new ofVec3f(j*scale,i*scale));
                    counter++;
                }
            }
            
            
            
            f = !f;
            
            
            
            
        }
    }
    
    
    ofxCurve * c;
    c = new ofxCurve(*pts[0], *pts[0]+ofVec3f(0,-scale*tipScale,0), *pts[0]+ofVec3f(-scale*tipScale,0,0), *pts[0]);
   curves.push_back(c);
    
    for(int i=0;i<pts.size();i++){
        ofxCurve * c;
        ofVec3f v = ofVec3f(0,0,0);
        ofVec3f v2 = v;
        if(i>0){
            if((i)%numCols==0){
                
                
                if(pts[i]->x == pts[i-1]->x &&
                   pts[i]->y == pts[i-1]->y){ // this never executes... problem! (because we're evaluating the previous ones, not the current.
                    v = ofVec3f(scale*tipScale,0,0);
                    v2 = ofVec3f(0,scale*tipScale,0);
                    ofLog() << "blargh";
                } else if(pts[i-2]->x > pts[i-1]->x){
                    v = v2 = ofVec3f(-scale*edgeScale,0,0);
                } else if(pts[i-2]->x < pts[i-1]->x){
                    v = v2 = ofVec3f(scale*edgeScale,0,0);
                } else if(pts[i-2]->y > pts[i-1]->y){
                    v = v2 = ofVec3f(0,-scale*edgeScale,0);
                } else if(pts[i-2]->y < pts[i-1]->y){
                    v = v2 = ofVec3f(0,scale*edgeScale,0);
                }
                
                
                ofLog() << i << ", " << v.x << ", "<< v.y<< ", " << v2.x<< ", " << v2.y;
                c = new ofxCurve(*pts[i-1], *pts[i-1]+v, *pts[i]+v2, *pts[i]);
                curves.push_back(c);
                
            } else{
                c = new ofxCurve(*pts[i-1], *pts[i-1], *pts[i], *pts[i]);
                curves.push_back(c);
            }
        }
    }

    
}


//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushMatrix();
    ofTranslate(200,200);

    
    
    //ofBeginShape();
    ofNoFill();
    for(int i=0;i<pts.size()-1;i++){
        if(i%numCols==0){
            ofSetColor(255,255,0);
        } else {
            ofSetColor(0,255,0);
        }
       // ofDrawLine(*pts.at(i), *pts.at(i+1));
        //ofVertex(pts.at(i)->x,pts.at(i)->y);
        ofFill();
        ofSetColor(0);
        ofDrawEllipse(*pts.at(i), 15, 15);
    }
    ofNoFill();
    for(int i=0;i<curves.size();i++){
        ofSetColor(0);
        curves.at(i)->update();
        curves.at(i)->draw(true);
    }
    
    //curves.clear();
    //ofEndShape(false);
    //pts.clear();
    ofPopMatrix();
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    generateCurve();
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
