#pragma once

#include "ofMain.h"
#include "Cloth.hpp"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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

    int desiredFrameRate;
    
    Cloth cloth;
    
    ofTexture curtainTex;
    ofTexture flagTex;
    
    
    
    void setupGui();
    string guiName;
    
    ofxPanel gui;
    ofxLabel clothSettingsLabel;
    ofxIntSlider constraintAccuracySlider;
    ofxFloatSlider stiffnessSlider;
    ofxFloatSlider mouseStrengthSlider;
    ofxFloatSlider mouseRadSlider;
    ofxFloatSlider mouseTearRadSlider;
    ofxFloatSlider tearDistanceSlider;
    ofxFloatSlider dampingSlider;
    
    ofxToggle allowTearingToggle;
    
    ofxLabel pinPointsLabel;
    ofxButton curtain;
    ofxButton flag;
    ofxButton free;
    
    ofxLabel waterLabel;
    ofxToggle useWaterEffect;
    ofxIntSlider waterLevel;
    ofxFloatSlider waterDamping;
    
    ofxLabel forcesLabel;
    ofxToggle useGravity;
    ofxFloatSlider gravitySlider;
    ofxToggle useWind;
    ofxFloatSlider windStrengthSlider;
    ofxFloatSlider windVariationSlider;
    ofxFloatSlider windVariationSpeed;
    ofxFloatSlider windScaleSlider;
    
    ofxLabel textureLabel;
    ofxToggle drawTexturedToggle;
    ofxToggle showStressColorsToggle;
    ofxButton curtainTexButton;
    ofxButton flagTexButton;
    
    string fileName;
    

    
};
