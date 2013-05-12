#include "testApp.h"
#include "stdio.h"



//--------------------------------------------------------------
void testApp::setup(){
	
	ofBackground(0,0,0);
    

	left = new float[256];
	right = new float[256];
    
    left2 = new float[256];
	right2 = new float[256];
    
	
	c1.listDevices();
   // c1.setDeviceId(0);
	c1.setDeviceIdByName("Loud Technologies Inc.: Onyx-i (4034)");
	//c1.setDeviceIdByName("Griffin Technology, Inc: iMic USB audio system");
	c1.setup(2, 4, this, 44100, 256, 4);
	
	ofAddListener(c1.audioReceivedEvent, this, &testApp::audioInputListener);
	/*
	c2.setDeviceId(1);
	c2.setup(0, 2, this, 44100, 256, 4);
	ofAddListener(c2.audioReceivedEvent, this, &testApp::audioInputListener);*/
    
    /*
    c3.listDevices();
	//c1.setDeviceIdByName("M-Audio: FireWire 410 Multichannel");
	//c1.setDeviceIdByName("Griffin Technology, Inc: iMic USB audio system");
	c3.setup(0, 2, this, 44100, 256, 4);
	
	ofAddListener(c1.audioReceivedEvent, this, &testApp::audioInputListener);
	
	c4.setDeviceId(0);
	c4.setup(0, 2, this, 44100, 256, 4);
	ofAddListener(c2.audioReceivedEvent, this, &testApp::audioInputListener);
*/
    
}

//--------------------------------------------------------------
void testApp::draw(){
	//ofLogNotice()<<"aaa";

    /*
    ofSetColor(150);
    ofDrawBitmapString("Device 1:" , 100, 80);
	
	// draw the left:
	ofSetColor(150);
    
	ofRect(100,100,256,200);
	ofSetColor(255);
    
	for (int i = 0; i < 256; i++){
		ofLine(100+i,200,100+i,200+left[i]*100.0f);
	}
	
	// draw the right:
	ofSetColor(150);
	ofRect(600,100,256,200);
	ofSetColor(255);
    
	for (int i = 0; i < 256; i++){
		ofLine(600+i,200,600+i,200+right[i]*100.0f);
	}
	
	*/
    
    
    
    /*
     ofSetColor(150);
     ofDrawBitmapString("Device 1:" , 100, 80);
     
     // draw the left:
     ofSetColor(150);
     
     ofRect(100,100,256,200);
     ofSetColor(255);
     
     for (int i = 0; i < 256; i++){
     ofLine(100+i,200,100+i,200+left[i]*100.0f);
     }
     
     // draw the right:
     ofSetColor(150);
     ofRect(600,100,256,200);
     ofSetColor(255);
     
     for (int i = 0; i < 256; i++){
     ofLine(600+i,200,600+i,200+right[i]*100.0f);
     }
     
     */
    
    
	ofSetColor(150);
	ofDrawBitmapString("Device 1, 2" , 100, 380);
	
	// draw the left:
	ofSetColor(150);
    
	ofRect(100,400,256,200);
	ofSetColor(255);
    
    
	for (int i = 0; i < 256; i++){
		ofLine(100+i,500,100+i,500+left[i]*100.0f);
	}
	
	// draw the right:
	ofSetColor(150);
    
	ofRect(600,400,256,200);
	ofSetColor(255);
    
	for (int i = 0; i < 256; i++){
		ofLine(600+i,500,600+i,500+right[i]*100.0f);
	}
    
    //////////////////////////////////////////////

	ofSetColor(150);
	ofDrawBitmapString("Device 3, 4" , 100, 80);
	
    // draw the left:
    ofSetColor(150);
    
    ofRect(100,100,256,200);
    ofSetColor(255);
    
    for (int i = 0; i < 256; i++){
        ofLine(100+i,200,100+i,200+left2[i]*100.0f);
    }
    
    // draw the right:
    ofSetColor(150);
    ofRect(600,100,256,200);
    ofSetColor(255);

	for (int i = 0; i < 256; i++){
		ofLine(600+i,200,600+i,200+right2[i]*100.0f);
	}
    
}


static float adder = 0;
int bufferCounter = 0;
//--------------------------------------------------------------
void testApp::audioReceived(float * input, int bufferSize, int nChannels){
	// samples are "interleaved"
    /*
    ofLogNotice()<<"audio received, channel:" << nChannels<<", bufSize:"<<bufferSize;
    
    for (int i = 0; i < bufferSize; i++){
     left[i] = input[i*2];
     right[i] = input[i*2+1];
     }
     bufferCounter++;
     */
}

//--------------------------------------------------------------
void testApp::audioInputListener(ofxAudioEventArgs &args){
	// samples are "interleaved"
	if(args.deviceID == 0){
        ofLogNotice()<<"i am 0";
        // (args.nChannels)/2
        ofLogNotice()<<"bufferSize"<<args.bufferSize;
    
        for (int i = 0; i < args.bufferSize; i+=2){
            left[i] = args.buffer[i*2];
            right[i] = args.buffer[i*2+1];
            left2[i] = args.buffer[i*2+2];
            right2[i] = args.buffer[i*2+3];
        }
        
	}
    
//    
//    sampleBuf = left;
//    sampleBuf.save();
//
    
    
//	else{
//		for (int i = 0; i < args.bufferSize; i++){
//			left[i] = args.buffer[i*2];
//			right[i] = args.buffer[i*2+1];
//		}
//	}
	//cout << "Audio Input event received from device " << args.deviceID << " - " << args.deviceName << endl;
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
	
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





