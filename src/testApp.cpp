#include "testApp.h"
#include <iostream.h>

//--------------------------------------------------------------
void testApp::setup(){
    
    myPlayer.loadMovie( "GoodHair_shorter/Resources/GoodHair_shorter.mov" );
    videoSound.loadSound( "GoodHair_short.mp3" );
    
    videoSound.play();
    videoSound.setVolume(0.8f);
    
    BlurOne.allocate(ofGetWidth(), ofGetHeight());
    BlurTwo.allocate(ofGetWidth(), ofGetHeight());
    
    shader.load("shaders/pixelate");
    shaderX.load("shaders/blur");
    shaderY.load("shaders/blur2");
    
    point.set(20, 20);
//    myPlayer.setLoopState(OF_LOOP_PALINDROME);
    myPlayer.play();
    myPlayer.setSpeed(1.5f);
    myPlayer.setVolume(0.0f);


}

//--------------------------------------------------------------
void testApp::update(){
    cout<<"mouseX"<<endl;
    cout<<mouseX<<endl;
    cout<<"mouseY"<<endl;
    cout<<mouseY<<endl;
    
    ofSetWindowTitle(ofToString(ofGetFrameRate())+"fps");
    myPlayer.update();
    ofSoundUpdate();
    
    if(upLeftQuad || lowRightQuad){
    BlurOne.begin();
    myPlayer.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    
    ofSetColor(255);
    for(int y = 0; y<ofGetHeight(); y+=10)
        for(int x=0; x<ofGetWidth(); x+=10) {
            ofRect(x, y, 5, 5);
        }
    
    BlurOne.end();
    }

    if(upLeftQuad || lowRightQuad){
    int iterations = 5;
    for (int i=0; i<iterations; i++){
    
        BlurTwo.begin();
        shaderX.begin();
        shaderX.setUniform1f("amount", point.x);
        BlurOne.draw(0, 0);
        shaderX.end();
        BlurTwo.end();
        
        BlurOne.begin();
        shaderY.begin();
        shaderY.setUniform1f("amount", point.y);
        BlurTwo.draw(0, 0);
        shaderY.end();
        BlurOne.end();
        }
    }
    
}
//--------------------------------------------------------------
void testApp::draw(){
    if(upLeftQuad || lowRightQuad){

    BlurOne.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    }
//    Pixel  = myPlayer.getPixelsRef();
//    Texture.allocate(ofGetWindowWidth(), ofGetWindowHeight(), GL_RGB);
//    Texture.loadData(Pixel);
    
    if((upRightQuad || lowLeftQuad)){
    shader.begin();
    shader.setUniform2f("sampleDivisor", point.x, point.y);
    myPlayer.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    shader.end();
    }

    if(upLeftQuad || lowRightQuad){
    BlurTwo.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    }
}
//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
    //this is where I am mapping mouseX/mouseY ==> Pixel x,y
    float dist = ofDist(0, 0, x, y);
    float max = ofDist(0, 0, myPlayer.width, myPlayer.height);
    float rectSize = ofMap(dist, 0, max, 100, 1);
    point.x = rectSize;
    point.y = rectSize;

    int xpos = x;
    float playhead = ofMap(xpos, 0, dist, 0, 1);
    float playBack = myPlayer.getPosition();
//    float skip = playBack + 0.3;
//    float position = ofMap(myPlayer.getTotalNumFrames(), 0.0f, myPlayer.getDuration()* 30.0f, 0.0f, 1.0f);
//
//    if (playhead > playBack) {
//        playhead = playBack;
    if(myPlayer.getPosition() == 1.0){
        playhead = 0;
    }
    myPlayer.setPosition(playhead);

//    } else if (playhead==playBack){
//            myPlayer.setPosition(skip);
//        } else{
//               myPlayer.firstFrame();
//        }

    if((xpos % 5 == 0) && (xpos % 3 != 0)) {
    
    if((mouseX > 0 && mouseX < 510) && (mouseY > 0 && mouseY < 362)){
        
        upLeftQuad = true;
        upRightQuad = false;
        lowLeftQuad = false;
        lowRightQuad = false;
        
    } else if((mouseX > 514 && mouseX < 1024) && (mouseY > 366 && mouseY < 768)){
        upLeftQuad = false;
        upRightQuad = false;
        lowLeftQuad = false;
        lowRightQuad = true;
        
    } else if((mouseX > 0 && mouseX < 510) && (mouseY > 366 && mouseY < 768)){
        
        upLeftQuad = false;
        upRightQuad = false;
        lowLeftQuad = true;
        lowRightQuad = false;
        
    }else if((mouseX > 514 && mouseX < 1024) && (mouseY > 0 && mouseY < 362)){
        
        upLeftQuad = false;
        upRightQuad = true;
        lowLeftQuad = false;
        lowRightQuad = false;
        
        }
    }
    if((xpos % 3 == 0) || (xpos % 5 != 0)){

    if((mouseX > 0 && mouseX < 510) && (mouseY > 0 && mouseY < 362)){
    
    upLeftQuad = false;
    upRightQuad = true;
    lowLeftQuad = false;
    lowRightQuad = false;
    
    } else if((mouseX > 514 && mouseX < 1024) && (mouseY > 366 && mouseY < 768)){
    upLeftQuad = false;
    upRightQuad = false;
    lowLeftQuad = true;
    lowRightQuad = false;
    
    } else if((mouseX > 0 && mouseX < 510) && (mouseY > 366 && mouseY < 768)){
    
    upLeftQuad = false;
    upRightQuad = false;
    lowLeftQuad = false;
    lowRightQuad = true;
    
    }else if((mouseX > 514 && mouseX < 1024) && (mouseY > 0 && mouseY < 362)){
    
    upLeftQuad = true;
    upRightQuad = true;
    lowLeftQuad = false;
    lowRightQuad = false;
    
        }
    }
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

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
