#include "ofApp.h"

#include <boost/range/irange.hpp>

using Source = ofx::piMapper::FboSource;

void ofApp::setup(){
	ofBackground(0);

	// Enable or disable audio for video sources globally
	// Set this to false to save resources on the Raspberry Pi
	ofx::piMapper::VideoSource::enableAudio = true;
	ofx::piMapper::VideoSource::useHDMIForAudio = false;

	std::vector<std::string> images = {
		"assets/spaceship_tex_08.png",
		"assets/spaceship_tex_09.png",
		"assets/spaceship_tex_10.png",
		"assets/spaceship_tex_11.png",
		"assets/spaceship_tex_04.png",
		"assets/spaceship_tex_05.png",
		"assets/spaceship_tex_06.png",
		"assets/spaceship_tex_07.png"
	};

	std::vector<std::string> videos = {
		"assets/spaceship_tex_08.png",
		"assets/spaceship_tex_09.png",
		"assets/spaceship_tex_10.png",
		"assets/spaceship_tex_11.png",
		"assets/spaceship_tex_04.png",
		"assets/spaceship_tex_05.png",
		"assets/spaceship_tex_06.png",
		"assets/spaceship_tex_07.png"
	};

	// Add our CustomSource to list of fbo sources of the piMapper
	// FBO sources should be added before piMapper.setup() so the
	// piMapper is able to load the source if it is assigned to
	// a surface in XML settings.
	for (auto source_idx : boost::irange(0, 7))
	{
		const string name = "Source_" + to_string(source_idx);
		const auto source = make_shared<TextureSource>(name, images);

		sources_.push_back(source);

		sequencer_.add_source(source);
		piMapper.registerFboSource(source.get());
	}

	piMapper.setup();

	ofSetFullscreen(Settings::instance()->getFullscreen());
	ofSetEscapeQuitsApp(false);

	register_midi_trigger();
}

void ofApp::update(){
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
	const size_t midi_root_channel = 1;
	const size_t midi_root_note = 12;

	for (auto source_idx: boost::irange(0, 7))
	{
		for (auto node_idx: boost::irange(0, 7))
		{
			const auto note = midi_root_note + node_idx;
			const auto channel = midi_root_channel + source_idx;

			mapping_.add_trigger(midi::trigger{channel, 0, note,
			[this, node_idx, source_idx] (const size_t value) {
				if (auto source = sources_.at(source_idx))
					source->set_param(node_idx, "alpha", value);
			}});
		}
	}
}
