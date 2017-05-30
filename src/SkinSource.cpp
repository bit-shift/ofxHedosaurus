#include "SkinSource.h"

//--------------------------------------------------------------

SkinSource::SkinSource(){
	name = "Skin";
	allocate(500, 500);
}

//--------------------------------------------------------------

void SkinSource::setup(){
    
#ifdef TARGET_OPENGLES
	_shader.load("shaders/mesh_bulb/shadersES2/shader");
#else
	if(ofIsGLProgrammableRenderer()){
		_shader.load("shaders/mesh_bulb/shadersGL3/shader");
	}else{
		_shader.load("shaders/mesh_bulb/shadersGL2/shader");
	}
#endif

    int planeWidth = ofGetWidth();
    int planeHeight = ofGetHeight();
    int planeGridSize = 20;
    int planeColums = planeWidth / planeGridSize;
    int planeRows = planeHeight / planeGridSize;
    
    _plane.set(planeWidth, planeHeight, planeColums, planeRows, OF_PRIMITIVE_TRIANGLES);
}

//--------------------------------------------------------------

void SkinSource::draw(){
	
	_shader.begin();
    
    // center screen.
    float cx = ofGetWidth() / 2.0;
    float cy = ofGetHeight() / 2.0;
    
    // the plane is being position in the middle of the screen,
    // so we have to apply the same offset to the mouse coordinates before passing into the shader.
    float mx = ofGetAppPtr()->mouseX - cx;
    float my = ofGetAppPtr()->mouseY - cy;
    
    // we can pass in a single value into the shader by using the setUniform1 function.
    // if you want to pass in a float value, use setUniform1f.
    // if you want to pass in a integer value, use setUniform1i.
    _shader.setUniform1f("mouseRange", 150);
    
    // we can pass in two values into the shader at the same time by using the setUniform2 function.
    // inside the shader these two values are set inside a vec2 object.
    _shader.setUniform2f("mousePos", mx, my);
    
    // color changes from magenta to blue when moving the mouse from left to right.
    float percentX = ofGetAppPtr()->mouseX / (float)ofGetWidth();
    percentX = ofClamp(percentX, 0, 1);
    ofFloatColor colorLeft = ofColor::magenta;
    ofFloatColor colorRight = ofColor::blue;
    ofFloatColor colorMix = colorLeft.getLerped(colorRight, percentX);
    
    // create a float array with the color values.
    float mouseColor[4] = {colorMix.r, colorMix.g, colorMix.b, colorMix.a};
    
    // we can pass in four values into the shader at the same time as a float array.
    // we do this by passing a pointer reference to the first element in the array.
    // inside the shader these four values are set inside a vec4 object.
    _shader.setUniform4fv("mouseColor", mouseColor);

	// _shader.setUniformTexture("tex0", fbo->getTexture(), 0);
    
    // ofTranslate(cx, cy);

    _plane.drawWireframe();
    
    _shader.end();
}