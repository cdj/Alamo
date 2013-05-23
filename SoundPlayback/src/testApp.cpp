#include "testApp.h"



//--------------------------------------------------------------
void testApp::setup(){

	ofBackground(255,255,255);
    ofSetFrameRate(30);
    
	sampleRate 			= 44100;
	phase 				= 0;
	phaseAdder 			= 0.0f;
	phaseAdderTarget 	= 0.0f;
	volume				= 0.4f;
	bRingModulation 	= false;
	lAudio = new float[256];
	rAudio = new float[256];
	cAudio = new float[256];
    
	sample.load("test2.wav"); // supports mono or stereo .wav files
	sample.setLooping(true);
    
	sample.generateWaveForm(&waveForm);
    
    bScrubMode = false;
    bReverse = false;
    
    targetFrequency = 1000.0f;
	phaseAdderTarget = (targetFrequency / (float) sampleRate) * TWO_PI;
    
    
	ofSoundStreamSetup(3,0,this, sampleRate,384, 6);
    
    
	bSendSerialMessage = false;
	accelSerial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = accelSerial.getDeviceList();
    
	// this should be set to whatever com port your serial device is connected to.
	// (ie, COM4 on a pc, /dev/tty.... on linux, /dev/tty... on a mac)
	// arduino users check in arduino app....
	int baud = 9600;
	//accelSerial.setup(0, baud); //open the first device
	//serial.setup("COM4", baud); // windows example
	//serial.setup("/dev/tty.usbserial-A4001JEC", baud); // mac osx example
	//serial.setup("/dev/ttyUSB0", baud); //linux example
	
    for (int i=0; i<deviceList.size(); i++) {
        if(ofIsStringInString(deviceList[i].getDeviceName(), "usbserial")) {
            accelSerial.setup(i, baud);
            break;
        }
    }
           
           
    for (int i=0; i<deviceList.size(); i++) {
        if(ofIsStringInString(deviceList[i].getDeviceName(), "tty.usbmodem")) { // this should be an arduino...
            ledSerial.setup(i, baud);
            break;
        }
    }
    
    
	nTimesRead = 0;
	nBytesRead = 0;
	readTime = 0;
	memset(bytesReadString, 0, 4);

}

//--------------------------------------------------------------
void testApp::exit(){
    ofSoundStreamStop();
    ofSoundStreamClose();
    delete lAudio;
    delete rAudio;
    delete cAudio;
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    static int last_x = 0;
    static int curr_x = 0;
    
    last_x = curr_x;
    curr_x = mouseX;
    deltax = (1.0f + fabs(curr_x - last_x))/1.0f;
    
    if(bScrubMode) {
        float next_pos = widthPct;
        float curr_pos = sample.getPosition();
        
        deltapos = (next_pos - curr_pos);
        
        speed = deltapos*((float)sample.getLength()/(float)sample.getSampleRate())*10.0f;
        sample.setSpeed(speed);
    }
    
	if (bSendSerialMessage){
		
		// (1) write the letter "a" to serial:
		
		// (2) read
		// now we try to read 3 bytes
		// since we might not get them all the time 3 - but sometimes 0, 6, or something else,
		// we will try to read three bytes, as much as we can
		// otherwise, we may have a "lag" if we don't read fast enough
		// or just read three every time. now, we will be sure to
		// read as much as we can in groups of three...
		
        bool isSpinning = false;
        
		nTimesRead = 0;
		nBytesRead = 0;
		int nRead  = 0;  // a temp variable to keep count per read
		
		unsigned char bytesReturned[3];
		
		memset(bytesReadString, 0, 4);
		memset(bytesReturned, 0, 3);
		
		while( (nRead = accelSerial.readBytes( bytesReturned, 3)) > 0){
			nTimesRead++;
			nBytesRead = nRead;
		};
		
		memcpy(bytesReadString, bytesReturned, 3);
		
		bSendSerialMessage = false;
		readTime = ofGetElapsedTimef();
        
        
        
        // determine if spinning
        
        
        // play or stop sounds
        if (isSpinning) {
            if (!sample.getIsPlaying()) {
                sample.play();
            }
            
        } else {
            if (sample.getIsPlaying()) { // needs condition for 8 second buffer
                sample.stop();
            }
        }
        
        
        // send spin status to arduino
        ledSerial.writeByte(isSpinning ? '0' : '1');
	}

}

//--------------------------------------------------------------
void testApp::draw(){
 /*
	// draw waveform
	sample.drawWaveForm(5, 500, ofGetWidth()-10, 100, &waveForm);
    
	// draw the left:
	ofSetColor(0x333333);
	ofRect(100,100,256,200);
	ofSetColor(0xFFFFFF);
	for (int i = 0; i < 256; i++){
		ofLine(100+i,200,100+i,200+lAudio[i]*200.0f);
	}
    
	// draw the right:
	ofSetColor(0x333333);
	ofRect(600,100,256,200);
	ofSetColor(0xFFFFFF);
	for (int i = 0; i < 256; i++){
		ofLine(600+i,200,600+i,200+rAudio[i]*200.0f);
	}
 */
  
	ofSetColor(0,0,0);
	char reportString[255];
	sprintf(reportString, "volume: (%f) modify with -/+ keys\npan: (%f)\nspeed: (%f)\nplayback: %s\nposition: %f\npaused: %s", volume, pan, speed, bRingModulation ? "ring modulation" : "normal",sample.getPosition(),sample.getIsPaused()?"yes":"no");
	if (bRingModulation) sprintf(reportString, "%s (%fhz)", reportString, targetFrequency);    
    
	ofDrawBitmapString(reportString,80,380);
    
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    static bool toggle = false;
    
	if (key == '-'){
		volume -= 0.05;
		volume = MAX(volume, 0);
	} else if (key == '+'){
		volume += 0.05;
		volume = MIN(volume, 1);
	}
    
	if(key == ' ')
	{
	    toggle = !toggle;
	    sample.setPaused(toggle);
	}
    
	if(key == 'r')
	{
	    bReverse = !bReverse;
	    if(bReverse) {
	        speed = -1.0f;
            sample.setSpeed(speed);
	    }
        else
        {
            speed = 1.0f;
            sample.setSpeed(speed);
        }
	}
    
	if(key == 's')
	{
	    if(bScrubMode) {speed = 1.0f;sample.setSpeed(speed);}
	    bScrubMode = !bScrubMode;
	}
    
	if(key == 'h')
	{
	    sample.stop();
	}
	if(key == 'p')
	{
	    sample.play();
	}
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    /*
	int width = ofGetWidth();
	widthPct = (float)x / (float)width;
	pan = widthPct;
    
	float height = (float)ofGetHeight();
	float heightPct = 1 - ((height-y) / height);
    
	if(!bScrubMode) {
        speed = 2*(-1.0f + 2*heightPct);
        sample.setSpeed(speed);
	}
    */
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	/*int width = ofGetWidth();
	pan = (float)x / (float)width;
    
	float height = (float)ofGetHeight();
	float heightPct = ((height-y) / height);
	targetFrequency = 2000.0f * heightPct;
	phaseAdderTarget = (targetFrequency / (float) sampleRate) * TWO_PI;*/
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	/*bRingModulation = true;*/
}


//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	/*bRingModulation = false;*/
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

//--------------------------------------------------------------
void testApp::audioRequested 	(float * output, int bufferSize, int nChannels){
    
	float leftScale = 1 - pan;
	float rightScale = pan;
	float centerScale = 1;
    
	// sin (n) seems to have trouble when n is very large, so we
	// keep phase in the range of 0-TWO_PI like this:
	while (phase > TWO_PI){
		phase -= TWO_PI;
	}
    
    phaseAdder = 0.95f * phaseAdder + 0.05f * phaseAdderTarget;
    
    for (int i = 0; i < bufferSize; i++){
        if ( bRingModulation == true)
        {
            phase += phaseAdder;
            float mod = sin(phase);
            
            // mono
            if(sample.getChannels() == 1) {
                float smp = sample.update();
                lAudio[i] = output[i*nChannels    ] = mod * smp * volume * leftScale;
                rAudio[i] = output[i*nChannels + 1] = mod * smp * volume * rightScale;
                cAudio[i] = output[i*nChannels + 2] = mod * smp * volume * centerScale;
            }
            // stereo
            else if (sample.getChannels() == 2) {
                lAudio[i] = output[i*nChannels    ] = mod * sample.update() * volume * leftScale;
                rAudio[i] = output[i*nChannels + 1] = mod * sample.update() * volume * rightScale;
                cAudio[i] = output[i*nChannels + 2] = mod * sample.update() * volume * centerScale;
            }
            else if (sample.getChannels() == 3) {
                lAudio[i] = output[i*nChannels    ] = mod * sample.update() * volume * leftScale;
                rAudio[i] = output[i*nChannels + 1] = mod * sample.update() * volume * rightScale;
                cAudio[i] = output[i*nChannels + 2] = mod * sample.update() * volume * centerScale;
            }
        }
        else //normal playback
        {
            // mono
            if(sample.getChannels() == 1) {
                float smp = sample.update();
                lAudio[i] = output[i*nChannels    ] = smp * volume * leftScale;
                rAudio[i] = output[i*nChannels + 1] = smp * volume * rightScale;
                cAudio[i] = output[i*nChannels + 2] = smp * volume * centerScale;
            }
            // stereo
            else if (sample.getChannels() == 2) {
                lAudio[i] = output[i*nChannels    ] = sample.update() * volume * leftScale;
                rAudio[i] = output[i*nChannels + 1] = sample.update() * volume * rightScale;
                cAudio[i] = output[i*nChannels + 2] = sample.update() * volume * centerScale;
            }
            else if (sample.getChannels() == 2) {
                lAudio[i] = output[i*nChannels    ] = sample.update() * volume * leftScale;
                rAudio[i] = output[i*nChannels + 1] = sample.update() * volume * rightScale;
                cAudio[i] = output[i*nChannels + 2] = sample.update() * volume * centerScale;
            }
            else
            {
                lAudio[i]  = output[i*nChannels    ] = 0.0;
                rAudio[i]  = output[i*nChannels + 1] = 0.0;
                rAudio[i]  = output[i*nChannels + 2] = 0.0;
            }
        }
        
        
    }
}

