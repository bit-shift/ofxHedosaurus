#include "SkinSource.h"

#include <midi.h>
#include <algorithms.h>

//-----------------------------------------------------------------------------

SkinSource::SkinSource(midi::in& midi_in)
	: midi_in_(midi_in)
{
	name = "Skin";
	allocate(width_, height_);
}

//-----------------------------------------------------------------------------

void SkinSource::setup()
{
	ofImage image;
    image_.load("assets/skin_tex_01_unsharpen.jpg");
	image2_.load("assets/skin_tex_03.jpg");

	overlay_px_.allocate(image_.getWidth(), image_.getHeight(), 
					     OF_IMAGE_COLOR_ALPHA);
	
	// RED
	midi_in_.add_trigger(midi::trigger_t{ 100, [this](const size_t value){ 
		image::set_channel(overlay_px_, 0, value * 2);
		ofLogNotice("SkinSource", "image::set_channel");
	}});

	// GREEN
	midi_in_.add_trigger(midi::trigger_t{ 106, [this](const size_t value){ 
		image::set_channel(overlay_px_, 1, value * 2);
	}});

	// BLUE
	midi_in_.add_trigger(midi::trigger_t{ 103, [this](const size_t value){ 
		image::set_channel(overlay_px_, 2, value * 2);
	}});

	// ALPHA
	midi_in_.add_trigger(midi::trigger_t{ 117, [this](const size_t value){ 
		image::set_channel(overlay_px_, 3, value * 2);
	}});

	//Set up vertices
	for (int y=0; y<H; y++) 
	{
		for (int x=0; x<W; x++) 
		{ 
			// adding texure coordinates allows us to bind textures to it later 
			// --> this could be made into a function so that 
			// textures can be swapped / updated
			mesh_.addVertex(ofPoint((x - W/2) * meshSize_, 
									(y - H/2) * meshSize_, 0 )); 
			mesh_.addTexCoord(ofPoint(x * (width_ / W), y * (height_ / H)));
			mesh_.addColor(ofColor(255, 255, 255));
		}
	}

	//Set up triangles' indices
	for (int y=0; y<H-1; y++) 
	{
		for (int x=0; x<W-1; x++) 
		{
			int i1 = x + W * y;
			int i2 = x+1 + W * y;
			int i3 = x + W * (y+1);
			int i4 = x+1 + W * (y+1);
			mesh_.addTriangle( i1, i2, i3 );
			mesh_.addTriangle( i2, i4, i3 );
		}
	}
}

//-----------------------------------------------------------------------------

void SkinSource::update()
{
	//convert fbo to ofImage format
	fbo->readToPixels(fbo_px_);
	image_.setFromPixels(fbo_px_);

	//Change vertices
	for (int y=0; y<H; y++) 
	{
		for (int x=0; x<W; x++) 
		{

			//Vertex index
			int i = x + W * y;
			ofPoint p = mesh_.getVertex( i );

			float scaleX = width_ / W;
			float scaleY = height_ / H;

			// get brightness
			int index = ((x * scaleX) + width_ * (y * scaleY)) * 4; // FBO has four components (including Alpha)
			int brightness = fbo_px_[index] / 4; // 4 is an arbitrary scalar to reduce the amount of distortion

			//Change z-coordinate of vertex
			p.z = brightness; // ofNoise(x * 0.05, y * 0.05, ofGetElapsedTimef() * 0.5) * 100;
			mesh_.setVertex( i, p );

			//Change color of vertex
			mesh_.setColor(i , ofColor(255, 255, 255));
		}
	}
}

//-----------------------------------------------------------------------------

void SkinSource::draw()
{
	ofBackground(0); // this matters
	ofEnableBlendMode(OF_BLENDMODE_ADD);

	overlay_.setFromPixels(overlay_px_);

	// image_.draw(0, 0);
	// overlay_.draw(0, 0);

	ofPushMatrix(); //Store the coordinate system

	image_.bind();

	//Move the coordinate center to screen's center
	// ofTranslate(width_ / 2, height_ / 2, 0);
	// mesh_.drawWireframe();
	mesh_.draw();

	image_.unbind();
	ofPopMatrix(); //Restore the coordinate system
}
