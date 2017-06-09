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
	skin_source_.reset(new SkinSource());
	sequencer_.add_source(skin_source_);

	piMapper.registerFboSource(skin_source_.get());
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
	// ALPHA
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

	// y-morphing
	// mapping_.add_trigger(midi::trigger{1, 51, 0,
	// [this](FboSource& source, const size_t value){ 
	// 	node3_->parameters().get<int>("y").set(value * 2);
	// }});

	// mapping_.add_trigger(midi::trigger{1, 55, 0,
	// [this](FboSource& source, const size_t value){
	// 	node7_->parameters().get<int>("y").set(value * 2);
	// }});

	// BPM
	mapping_.add_trigger(midi::trigger{1, 14, 0,
	[this](Source& source, const size_t value){ 
		sequencer_.parameters().get<size_t>("bpm").set(value * 2);
	}});

	// TRANSPORT
	mapping_.add_trigger(midi::trigger{1, 0, 91,
	[this](Source& source, const size_t value){ 
		sequencer_.parameters().get<size_t>("running").set(true);
	}});
	mapping_.add_trigger(midi::trigger{1, 0, 92,
	[this](Source& source, const size_t value){ 
		sequencer_.parameters().get<size_t>("running").set(false);
	}});

	// 	// ALPHA
	// midi_in_.add_trigger(midi::trigger{1, 7, 0,
	// [this](FboSource& source, const size_t value) {
	// 	source.set_param("alpha", value);
	// }});

	// midi_in_.add_trigger(midi::trigger{2, 7, 0,
	// [this](FboSource& source, const size_t value) {
	// 	source.set_param("alpha", value);
	// }});

	// midi_in_.add_trigger(midi::trigger{3, 7, 0,
	// [this](FboSource& source, const size_t value) {
	// 	node2_->parameters().get<size_t>("alpha").set(value * 2);
	// }});

	// midi_in_.add_trigger(midi::trigger{4, 7, 0,
	// [this](FboSource& source, const size_t value){
	// 	node3_->parameters().get<size_t>("alpha").set(value * 2);
	// }});

	// midi_in_.add_trigger(midi::trigger{5, 7, 0,
	// [this](FboSource& source, const size_t value){ 
	// 	node4_->parameters().get<size_t>("alpha").set(value * 2);
	// }});

	// midi_in_.add_trigger(midi::trigger{6, 7, 0,
	// [this](cFboSource& source, onst size_t value){ 
	// 	node5_->parameters().get<size_t>("alpha").set(value * 2);
	// }});

	// midi_in_.add_trigger(midi::trigger{7, 7, 0,
	// [this](FboSource& source, const size_t value){ 
	// 	node6_->parameters().get<size_t>("alpha").set(value * 2);
	// }});

	// midi_in_.add_trigger(midi::trigger{8, 7, 0,FboSource& source, 
	// [this](FboSource& source, const size_t value){ 
	// 	node7_->parameters().get<size_t>("alpha").set(value * 2);
	// }});
}
