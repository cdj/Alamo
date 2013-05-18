#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxSoundStream.h"
//#include "Sample.h"

class testApp : public ofBaseApp{
	
public:
    
    void setup();
    void update(){};
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    
    void audioReceived 	(float * input, int bufferSize, int nChannels);
    void audioInputListener (ofxAudioEventArgs &args);
	
    ofxSoundStream c1;
    ofxSoundStream c2;
	ofxSoundStream c3;
    ofxSoundStream c4;
//    float audio[4][256];
    //float right[4][256];
//    
    float * left;
    float * right;
    float * left2;
    float * right2;
    
    ofSoundPlayer player;
    
    void save();
    //Sample sampleBuf;
//    
//    float * left3;
//    float * right3;
//    
//    float * left4;
//    float * right4;
	
};

#endif	

