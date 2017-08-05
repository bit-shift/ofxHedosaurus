#include "ofApp.h"

using Source = ofx::piMapper::FboSource;

void ofApp::setup(){
	ofBackground(0);

	// Enable or disable audio for video sources globally
	// Set this to false to save resources on the Raspberry Pi
	ofx::piMapper::VideoSource::enableAudio = true;
	ofx::piMapper::VideoSource::useHDMIForAudio = false;

	std::vector<std::string> filenames = {
		"assets/spaceship_tex_00.png",
		"assets/spaceship_tex_01.png",
		"assets/spaceship_tex_02.png",
		"assets/spaceship_tex_03.png",
		"assets/spaceship_tex_04.png",
		"assets/spaceship_tex_05.png",
		"assets/spaceship_tex_06.png",
		"assets/spaceship_tex_07.png"
	};

	// Add our CustomSource to list of fbo sources of the piMapper
	// FBO sources should be added before piMapper.setup() so the
	// piMapper is able to load the source if it is assigned to
	// a surface in XML settings.
	source0_.reset(new SkinSource("Source_0", filenames));
	source1_.reset(new SkinSource("Source_1", filenames));
	source2_.reset(new SkinSource("Source_2", filenames));
	source3_.reset(new SkinSource("Source_3", filenames));
	source4_.reset(new SkinSource("Source_4", filenames));
	source5_.reset(new SkinSource("Source_5", filenames));
	source6_.reset(new SkinSource("Source_6", filenames));
	source7_.reset(new SkinSource("Source_7", filenames));

	sequencer_.add_source(source0_);
	sequencer_.add_source(source1_);
	sequencer_.add_source(source2_);
	sequencer_.add_source(source3_);
	sequencer_.add_source(source4_);
	sequencer_.add_source(source5_);
	sequencer_.add_source(source6_);
	sequencer_.add_source(source7_);

	piMapper.registerFboSource(source0_.get());
	piMapper.registerFboSource(source1_.get());
	piMapper.registerFboSource(source2_.get());
	piMapper.registerFboSource(source3_.get());
	piMapper.registerFboSource(source4_.get());
	piMapper.registerFboSource(source5_.get());
	piMapper.registerFboSource(source6_.get());
	piMapper.registerFboSource(source7_.get());
	piMapper.setup();

	mapping_.select_source(source0_);

	// The info layer is hidden by default, press <i> to toggle
	// piMapper.showInfo();

	ofSetFullscreen(Settings::instance()->getFullscreen());
	ofSetEscapeQuitsApp(false);

	register_midi_trigger();
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
	// ALPHA: SOURCE 0
	//
	mapping_.add_trigger(midi::trigger{1, 0, 12,
	[this](Source& source, const size_t value) {
		source0_->set_param(0, "alpha", value);
	}});

	mapping_.add_trigger(midi::trigger{1, 0, 13,
	[this](Source& source, const size_t value) {
		source0_->set_param(1, "alpha", value);
	}});

	mapping_.add_trigger(midi::trigger{1, 0, 14,
	[this](Source& source, const size_t value) {
		source0_->set_param(2, "alpha", value);
	}});

	mapping_.add_trigger(midi::trigger{1, 0, 15,
	[this](Source& source, const size_t value){
		source0_->set_param(3, "alpha", value);
	}});

	mapping_.add_trigger(midi::trigger{1, 0, 16,
	[this](Source& source, const size_t value){
		source0_->set_param(4, "alpha", value);
	}});

	mapping_.add_trigger(midi::trigger{1, 0, 17,
	[this](Source& source, const size_t value){
		source0_->set_param(5, "alpha", value);
	}});

	mapping_.add_trigger(midi::trigger{1, 0, 18,
	[this](Source& source, const size_t value){
		source0_->set_param(6, "alpha", value);
	}});

	mapping_.add_trigger(midi::trigger{1, 0, 19,
	[this](Source& source, const size_t value){
		source0_->set_param(7, "alpha", value);
	}});

	//
	// ALPHA: SOURCE 1
	//
	mapping_.add_trigger(midi::trigger{2, 0, 12,
	[this](Source& source, const size_t value) {
		source1_->set_param(0, "alpha", value);
	}});

	mapping_.add_trigger(midi::trigger{2, 0, 13,
	[this](Source& source, const size_t value) {
		source1_->set_param(1, "alpha", value);
	}});

	mapping_.add_trigger(midi::trigger{2, 0, 14,
	[this](Source& source, const size_t value) {
		source1_->set_param(2, "alpha", value);
	}});

	mapping_.add_trigger(midi::trigger{2, 0, 15,
	[this](Source& source, const size_t value){
		source1_->set_param(3, "alpha", value);
	}});

	mapping_.add_trigger(midi::trigger{2, 0, 16,
	[this](Source& source, const size_t value){
		source1_->set_param(4, "alpha", value);
	}});

	mapping_.add_trigger(midi::trigger{2, 0, 17,
	[this](Source& source, const size_t value){
		source1_->set_param(5, "alpha", value);
	}});

	mapping_.add_trigger(midi::trigger{2, 0, 18,
	[this](Source& source, const size_t value){
		source1_->set_param(6, "alpha", value);
	}});

	mapping_.add_trigger(midi::trigger{2, 0, 19,
	[this](Source& source, const size_t value){
		source1_->set_param(7, "alpha", value);
	}});

	//
	// ALPHA: SOURCE 2
	//
	mapping_.add_trigger(midi::trigger{3, 0, 12,
	[this](Source& source, const size_t value) {
		source2_->set_param(0, "alpha", value);
	}});

	mapping_.add_trigger(midi::trigger{3, 0, 13,
	[this](Source& source, const size_t value) {
		source2_->set_param(1, "alpha", value);
	}});

	mapping_.add_trigger(midi::trigger{3, 0, 14,
	[this](Source& source, const size_t value) {
		source2_->set_param(2, "alpha", value);
	}});

	mapping_.add_trigger(midi::trigger{3, 0, 15,
	[this](Source& source, const size_t value){
		source2_->set_param(3, "alpha", value);
	}});

	mapping_.add_trigger(midi::trigger{3, 0, 16,
	[this](Source& source, const size_t value){
		source2_->set_param(4, "alpha", value);
	}});

	mapping_.add_trigger(midi::trigger{3, 0, 17,
	[this](Source& source, const size_t value){
		source2_->set_param(5, "alpha", value);
	}});

	mapping_.add_trigger(midi::trigger{3, 0, 18,
	[this](Source& source, const size_t value){
		source2_->set_param(6, "alpha", value);
	}});

	mapping_.add_trigger(midi::trigger{3, 0, 19,
	[this](Source& source, const size_t value){
		source2_->set_param(7, "alpha", value);
	}});

	//
	// ALPHA: SOURCE 3
	//
	mapping_.add_trigger(midi::trigger{4, 0, 12,
	[this](Source& source, const size_t value) {
		source3_->set_param(0, "alpha", value);
	}});

	mapping_.add_trigger(midi::trigger{4, 0, 13,
	[this](Source& source, const size_t value) {
		source3_->set_param(1, "alpha", value);
	}});

	mapping_.add_trigger(midi::trigger{4, 0, 14,
	[this](Source& source, const size_t value) {
		source3_->set_param(2, "alpha", value);
	}});

	mapping_.add_trigger(midi::trigger{4, 0, 15,
	[this](Source& source, const size_t value){
		source3_->set_param(3, "alpha", value);
	}});

	mapping_.add_trigger(midi::trigger{4, 0, 16,
	[this](Source& source, const size_t value){
		source3_->set_param(4, "alpha", value);
	}});

	mapping_.add_trigger(midi::trigger{4, 0, 17,
	[this](Source& source, const size_t value){
		source3_->set_param(5, "alpha", value);
	}});

	mapping_.add_trigger(midi::trigger{4, 0, 18,
	[this](Source& source, const size_t value){
		source3_->set_param(6, "alpha", value);
	}});

	mapping_.add_trigger(midi::trigger{4, 0, 19,
	[this](Source& source, const size_t value){
		source3_->set_param(7, "alpha", value);
	}});
	

	//
	// SOURCE SELECTION
	//
	mapping_.add_trigger(midi::trigger{1, 0, 52,
	[this](Source& source, const size_t value){
		mapping_.select_source(source0_);
	}});

	mapping_.add_trigger(midi::trigger{2, 0, 52,
	[this](Source& source, const size_t value){
		mapping_.select_source(source1_);
	}});

	mapping_.add_trigger(midi::trigger{3, 0, 52,
	[this](Source& source, const size_t value){
		mapping_.select_source(source2_);
	}});

	mapping_.add_trigger(midi::trigger{4, 0, 52,
	[this](Source& source, const size_t value){
		mapping_.select_source(source3_);
	}});

	mapping_.add_trigger(midi::trigger{5, 0, 52,
	[this](Source& source, const size_t value){
		mapping_.select_source(source4_);
	}});

	mapping_.add_trigger(midi::trigger{6, 0, 52,
	[this](Source& source, const size_t value){
		mapping_.select_source(source5_);
	}});

	mapping_.add_trigger(midi::trigger{7, 0, 52,
	[this](Source& source, const size_t value){
		mapping_.select_source(source6_);
	}});

	mapping_.add_trigger(midi::trigger{8, 0, 52,
	[this](Source& source, const size_t value){
		mapping_.select_source(source7_);
	}});

	//
	// ALPHA
	//
	mapping_.add_trigger(midi::trigger{1, 7, 0,
	[this](Source& source, const size_t value) {
		source0_->parameters().get<size_t>("alpha").set(value * 2);
	}});

	mapping_.add_trigger(midi::trigger{2, 7, 0,
	[this](Source& source, const size_t value) {
		source1_->parameters().get<size_t>("alpha").set(value * 2);
	}});

	mapping_.add_trigger(midi::trigger{3, 7, 0,
	[this](Source& source, const size_t value) {
		source2_->parameters().get<size_t>("alpha").set(value * 2);
	}});

	mapping_.add_trigger(midi::trigger{4, 7, 0,
	[this](Source& source, const size_t value){
		source3_->parameters().get<size_t>("alpha").set(value * 2);
	}});

	mapping_.add_trigger(midi::trigger{5, 7, 0,
	[this](Source& source, const size_t value){
		source4_->parameters().get<size_t>("alpha").set(value * 2);
	}});

	mapping_.add_trigger(midi::trigger{6, 7, 0,
	[this](Source& source, const size_t value){
		source5_->parameters().get<size_t>("alpha").set(value * 2);
	}});

	mapping_.add_trigger(midi::trigger{7, 7, 0,
	[this](Source& source, const size_t value){
		source6_->parameters().get<size_t>("alpha").set(value * 2);
	}});

	mapping_.add_trigger(midi::trigger{7, 7, 0,
	[this](Source& source, const size_t value){
		source7_->parameters().get<size_t>("alpha").set(value * 2);
	}});

	// midi_in_.add_trigger(midi::trigger{8, 7, 0,FboSource& source,
	// [this](FboSource& source, const size_t value){
	// 	node7_->parameters().get<size_t>("alpha").set(value * 2);
	// }});
}
