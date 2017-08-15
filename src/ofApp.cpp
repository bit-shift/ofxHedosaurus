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
		"assets/spaceship_tex_00.png",
		"assets/spaceship_tex_01.png",
		"assets/spaceship_tex_02.png",
		"assets/spaceship_tex_03.png",
		"assets/spaceship_tex_04.png",
		"assets/spaceship_tex_05.png",
		// "assets/spaceship_tex_06.png",
		// "assets/spaceship_tex_07.png",
		// "assets/spaceship_tex_08.png",
		// "assets/spaceship_tex_09.png",
		// "assets/spaceship_tex_10.png",
		"assets/spaceship_tex_11.png",
		"assets/spaceship_tex_12.png",
		"assets/spaceship_tex_13.png",
		"assets/spaceship_tex_14.png",
		"assets/spaceship_tex_15.png",
		"assets/spaceship_tex_16.png",
		"assets/spaceship_tex_17.png",
		"assets/spaceship_tex_18.png",
		"assets/spaceship_tex_19.png",
		"assets/spaceship_tex_20.png",
		"assets/spaceship_tex_21.png",
		"assets/spaceship_tex_22.png",
		"assets/spaceship_tex_23.png",
		"assets/spaceship_tex_24.png",
		"assets/spaceship_tex_25.png",
	};

	std::vector<std::string> videos = {
		// "sources/videos/VJzoo_CVIp005diagstrips.avi"
	};

	// Add our CustomSource to list of fbo sources of the piMapper
	// FBO sources should be added before piMapper.setup() so the
	// piMapper is able to load the source if it is assigned to
	// a surface in XML settings.
	for (auto source_idx : boost::irange(0, 3))
	{
		const string name = "Source_" + to_string(source_idx);
		const auto source = make_shared<TextureSource>(name, images, videos);

		sources_.push_back(source);

		sequencer_.add_source(source);
		piMapper.registerFboSource(source.get());
	}

	piMapper.setup();

	ofSetFullscreen(Settings::instance()->getFullscreen());
	ofSetEscapeQuitsApp(false);

	register_midi_trigger(images.size() + videos.size() + 1);
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

void ofApp::register_midi_trigger(const size_t node_count)
{
	const size_t midi_root_channel = 1;
	const size_t midi_root_note = 12;

	for (auto source_idx: boost::irange(0, 3))
	{
		for (auto node_idx: boost::irange(0, int(node_count)))
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
