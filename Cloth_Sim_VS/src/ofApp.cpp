#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetVerticalSync(false);
    
    desiredFrameRate = 60;
    ofSetFrameRate(desiredFrameRate);
    
    float curtainWidth = 800;
    float curtainHeight = 500;
    int restDist = 7;
    
    int numX = curtainWidth/restDist;
    int numY = curtainHeight/restDist;

    float guiWidth = 230;
    
    

    
    ofVec2f pos(guiWidth + (ofGetWidth() - guiWidth)/2 - curtainWidth/2 , 30);
    
    guiName = "settings";
    gui.setup(guiName, guiName + ".xml");
    gui.add(clothSettingsLabel.setup("   CLOTH SETTINGS", ""));
    gui.add(constraintAccuracySlider.setup("Solving Iterations", 3, 1, 10));
    gui.add(stiffnessSlider.setup("Link Stiffness", 1.0, 0.0, 1.2));
    gui.add(mouseRadSlider.setup("Mouse Rad", 40, 0, 200));
    gui.add(mouseStrengthSlider.setup("Mouse Strength", 1.0, 0.0, 10.0));
    gui.add(mouseTearRadSlider.setup("Mouse Tear Rad", 10.0, 0.0, 50.0));
    gui.add(tearDistanceSlider.setup("Link Tear Dist", 80.0, 1.0, 200.0));
    gui.add(dampingSlider.setup("Damping", 0.99, 0.85, 1.0));
    
    gui.add(allowTearingToggle.setup("Allow Tearing", true));
    
    //pin points
    gui.add(pinPointsLabel.setup("   PIN MODES", ""));
    gui.add(curtain.setup("Curtain Mode", false));
    gui.add(flag.setup("Flag Mode", false));
    gui.add(free.setup("Free Mode", false));
    
    //water settings
    gui.add(waterLabel.setup("   WATER", ""));
    gui.add(useWaterEffect.setup("Simulate Water", false));
    gui.add(waterLevel.setup("Water Level", ofGetHeight() * 0.9, 0, ofGetHeight()));
    gui.add(waterDamping.setup("Water Damping", 0.8, 0.0001, 1.0));

    //forces
    gui.add(forcesLabel.setup("   FORCES", ""));
    gui.add(useGravity.setup("Use Gravity", false));
    gui.add(gravitySlider.setup("Gravity Strength", 980, 0, 2000));
    gui.add(useWind.setup("Use Wind", false));
    gui.add(windStrengthSlider.setup("Wind Strength", 1000, 0, 2000));
    gui.add(windVariationSlider.setup("Wind Variation", 500, 0, 3000));
    gui.add(windVariationSpeed.setup("Wind Var. Speed", 1.0, 0.01, 3.0f));
    gui.add(windScaleSlider.setup("Wind Scale", 1.0, 0.001, 0.15f));

    gui.add(textureLabel.setup("   TEXTURES", ""));
    gui.add(drawTexturedToggle.setup("Draw Textured", false));
    gui.add(showStressColorsToggle.setup("Show Stresses", false));
    gui.add(curtainTexButton.setup("Curtain Tex", false));
    gui.add(flagTexButton.setup("Jolly Roger Tex", false));
    
    
    //formatting
    gui.setHeaderBackgroundColor(255);
    
    
    
    //color applies to gui title only
    gui.setDefaultTextColor(ofColor(255));
    
    //color of the labels
    clothSettingsLabel.setDefaultTextColor(ofColor(0));
    clothSettingsLabel.setBackgroundColor(255);

    waterLabel.setDefaultTextColor(ofColor(0));
    waterLabel.setBackgroundColor(255);

    pinPointsLabel.setDefaultTextColor(ofColor(0));
    pinPointsLabel.setBackgroundColor(255);

    forcesLabel.setDefaultTextColor(ofColor(0));
    forcesLabel.setBackgroundColor(255);

    textureLabel.setDefaultTextColor(ofColor(0));
    textureLabel.setBackgroundColor(255);
    
    gui.setPosition(10, 50);
    
    gui.loadFromFile(guiName + ".xml");
    
    cloth.setup(pos, numX, numY, restDist, desiredFrameRate);
    
    
    ofImage img;
    img.load("curtain.jpg");
    
    curtainTex = img.getTexture();
    
    
    img.load("flag.jpg");
    
    flagTex = img.getTexture();
    
    
    cloth.tex = curtainTex;
    
}

//--------------------------------------------------------------
void ofApp::update(){

    if( curtain ){
        cloth.clear();
        cloth.createCloth(Cloth::CURTAIN);
    }
    
    if( flag ){
        cloth.clear();
        cloth.createCloth(Cloth::FLAG);
        
        //pick some good settings for a waving flag
        windStrengthSlider = 350;
        windVariationSlider = 1275;
        windVariationSpeed = 0.35385;
        windScaleSlider = 0.04096;
        
        gravitySlider = 110;
        useGravity = true;
        useWind = true;
    }
    
    if( free ){
        cloth.clear();
        cloth.createCloth(Cloth::FREE);
    }
    
    
    if( curtainTexButton ){
        cloth.tex = curtainTex;
    }
    
    if( flagTexButton ){
        cloth.tex = flagTex;
    }

    
    
    
    cloth.mouseInflueceStrength = mouseStrengthSlider;
    cloth.mouseInfluenceSize = mouseRadSlider;
    cloth.stiffness = stiffnessSlider;
    cloth.damping = dampingSlider;
    cloth.mouseTearSize = mouseTearRadSlider;
    cloth.tearDistance = tearDistanceSlider;
    cloth.allowTearing = allowTearingToggle;
    cloth.gravity = gravitySlider;
    cloth.constraintAccuracy = constraintAccuracySlider;
    cloth.showStressColors = showStressColorsToggle;
    
    cloth.useWaterEffect = useWaterEffect;
    cloth.waterDamping = waterDamping;
    cloth.waterlevel = waterLevel;
    
    cloth.useGravity = useGravity;
    cloth.gravity = gravitySlider;
    
    cloth.useWind = useWind;
    cloth.windStrength = windStrengthSlider;
    cloth.windVariation = windVariationSlider;
    cloth.windVariationSpeed = windVariationSpeed;
    cloth.windScale = windScaleSlider;
    
    
    //use noise to generate wind
    
    
    
    
    
    
    cloth.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    

    
    ofBackgroundGradient(ofColor(100), ofColor(0));
    
    
    
    if( drawTexturedToggle ){
        cloth.drawTexturedMesh();
    } else {
        cloth.draw();
    }

    //draw water
    if( useWaterEffect ){
        
        ofSetColor(0, 128, 255, 100);
        ofDrawRectangle(0, waterLevel, ofGetWidth(), ofGetHeight() - waterLevel);
        
    }

    
    
    
    ofPushStyle();
    ofNoFill();
    ofSetColor(255, 100);
    ofDrawCircle(ofGetMouseX(), ofGetMouseY(), mouseRadSlider);
    ofPopStyle();

    ofPushStyle();
    ofNoFill();
    ofSetColor(255, 0, 0);
    ofDrawCircle(ofGetMouseX(), ofGetMouseY(), mouseTearRadSlider);
    ofPopStyle();

    
    
    ofSetColor(255);
    ofDrawBitmapString("Framerate: " + ofToString(ofGetFrameRate()), 10, 15);
    ofDrawBitmapString("Num Points: " + ofToString(cloth.pointMasses.size()), 10, 30);
    
    gui.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if( key == 's' ){
        gui.saveToFile(guiName + ".xml");
    }
    
    if( key == 'l' ){
        gui.loadFromFile(guiName + ".xml");
    }
    
    if( key == 'r' ){
        cloth.reset();
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
