#include "ofApp.h"

using Source = ofx::piMapper::FboSource;

void ofApp::setup(){
	ofBackground(0);

	// Enable or disable audio for video sources globally
	// Set this to false to save resources on the Raspberry Pi
	ofx::piMapper::VideoSource::enableAudio = true;
	ofx::piMapper::VideoSource::useHDMIForAudio = false;

	// Add our CustomSource to list of fbo sources of the piMapper
	// FBO sources should be added before piMapper.setup() so the
	// piMapper is able to load the source if it is assigned to
	// a surface in XML settings.
	head_source_.reset(new SkinSource("Head"));
	neck_source_.reset(new SkinSource("Neck"));
	body_source_.reset(new SkinSource("Body"));
	fin_source_.reset(new SkinSource("Fins"));
	leg_front_source_.reset(new SkinSource("Leg Front"));
	leg_back_source_.reset(new SkinSource("Leg Back"));
	tail_source_.reset(new SkinSource("Tail"));

	sequencer_.add_source(head_source_);
	sequencer_.add_source(neck_source_);
	sequencer_.add_source(body_source_);
	sequencer_.add_source(fin_source_);
	sequencer_.add_source(leg_front_source_);
	sequencer_.add_source(leg_back_source_);
	sequencer_.add_source(tail_source_);

	piMapper.registerFboSource(head_source_.get());
	piMapper.registerFboSource(neck_source_.get());
	piMapper.registerFboSource(body_source_.get());
	piMapper.registerFboSource(fin_source_.get());
	piMapper.registerFboSource(leg_front_source_.get());
	piMapper.registerFboSource(leg_back_source_.get());
	piMapper.registerFboSource(tail_source_.get());
	piMapper.setup();

	// The info layer is hidden by default, press <i> to toggle
	// piMapper.showInfo();
	
	ofSetFullscreen(Settings::instance()->getFullscreen());
	ofSetEscapeQuitsApp(false);
}

void ofApp::update(){
	sequencer_.update();
	piMapper.update();
}

void ofApp::draw(){
	piMapper.draw();
}

void ofApp::exit(){
	piMapper.draw();
}

void ofApp::keyPressed(int key){
	if (key == 'f')
		ofToggleFullscreen();
	else
		piMapper.keyPressed(key);
}

void ofApp::keyReleased(int key){
	piMapper.keyReleased(key);
}

void ofApp::mousePressed(int x, int y, int button){
	piMapper.mousePressed(x, y, button);
}

void ofApp::mouseReleased(int x, int y, int button){
	piMapper.mouseReleased(x, y, button);
}

void ofApp::mouseDragged(int x, int y, int button){
	piMapper.mouseDragged(x, y, button);
}

void ofApp::register_midi_trigger()
{
	//
	// BPM
	//
	mapping_.add_trigger(midi::trigger{1, 14, 0,
	[this](Source& source, const size_t value){ 
		sequencer_.parameters().get<size_t>("bpm").set(value * 2);
	}});

	//
	// TRANSPORT
	//
	mapping_.add_trigger(midi::trigger{1, 0, 91,
	[this](Source& source, const size_t value){ 
		sequencer_.parameters().get<size_t>("running").set(true);
	}});
	mapping_.add_trigger(midi::trigger{1, 0, 92,
	[this](Source& source, const size_t value){ 
		sequencer_.parameters().get<size_t>("running").set(false);
	}});

	//
	// ALPHA
	//
	mapping_.add_trigger(midi::trigger{1, 48, 0,
	[](Source& source, const size_t value) {
		source.set_param(0, "alpha", value);
	}});

	mapping_.add_trigger(midi::trigger{1, 49, 0,
	[](Source& source, const size_t value) {
		source.set_param(1, "alpha", value);
	}});

	mapping_.add_trigger(midi::trigger{1, 7, 0,
	[](Source& source, const size_t value) {
		source.set_param(2, "alpha", value);
	}});

	mapping_.add_trigger(midi::trigger{1, 7, 0,
	[](Source& source, const size_t value){
		source.set_param(3, "alpha", value);
	}});

	mapping_.add_trigger(midi::trigger{1, 7, 0,
	[](Source& source, const size_t value){ 
		source.set_param(4, "alpha", value);
	}});

	mapping_.add_trigger(midi::trigger{1, 7, 0,
	[](Source& source, const size_t value){ 
		source.set_param(5, "alpha", value);
	}});

	mapping_.add_trigger(midi::trigger{1, 7, 0,
	[](Source& source, const size_t value){ 
		source.set_param(6, "alpha", value);
	}});

	mapping_.add_trigger(midi::trigger{1, 7, 0,
	[](Source& source, const size_t value){ 
		source.set_param(7, "alpha", value);
	}});

	//
	// SOURCE SELECTION
	//
	mapping_.add_trigger(midi::trigger{1, 0, 0,
	[this](Source& source, const size_t value){ 
		// head
	}});

	mapping_.add_trigger(midi::trigger{1, 0, 0,
	[this](Source& source, const size_t value){ 
		// neck
	}});

	mapping_.add_trigger(midi::trigger{1, 0, 0,
	[this](Source& source, const size_t value){ 
		// body
	}});

	mapping_.add_trigger(midi::trigger{1, 0, 0,
	[this](Source& source, const size_t value){ 
		// fins
	}});

	mapping_.add_trigger(midi::trigger{1, 0, 0,
	[this](Source& source, const size_t value){ 
		// feet
	}});

	mapping_.add_trigger(midi::trigger{1, 0, 0,
	[this](Source& source, const size_t value){ 
		// tail
	}});

	//
	// ALPHA
	//
	mapping_.add_trigger(midi::trigger{1, 7, 0,
	[this](Source& source, const size_t value) {
		head_source_->parameters().get<size_t>("alpha").set(value * 2);
	}});

	mapping_.add_trigger(midi::trigger{2, 7, 0,
	[this](Source& source, const size_t value) {
		neck_source_->parameters().get<size_t>("alpha").set(value * 2);
	}});

	mapping_.add_trigger(midi::trigger{3, 7, 0,
	[this](Source& source, const size_t value) {
		body_source_->parameters().get<size_t>("alpha").set(value * 2);
	}});

	mapping_.add_trigger(midi::trigger{4, 7, 0,
	[this](Source& source, const size_t value){
		fin_source_->parameters().get<size_t>("alpha").set(value * 2);
	}});

	mapping_.add_trigger(midi::trigger{5, 7, 0,
	[this](Source& source, const size_t value){ 
		leg_front_source_->parameters().get<size_t>("alpha").set(value * 2);
	}});

	mapping_.add_trigger(midi::trigger{6, 7, 0,
	[this](Source& source, const size_t value){ 
		leg_back_source_->parameters().get<size_t>("alpha").set(value * 2);
	}});

	mapping_.add_trigger(midi::trigger{7, 7, 0,
	[this](Source& source, const size_t value){ 
		tail_source_->parameters().get<size_t>("alpha").set(value * 2);
	}});

	// midi_in_.add_trigger(midi::trigger{8, 7, 0,FboSource& source, 
	// [this](FboSource& source, const size_t value){ 
	// 	node7_->parameters().get<size_t>("alpha").set(value * 2);
	// }});
}
