#include "ofApp.h"

#include <boost/range/irange.hpp>

using Source = ofx::piMapper::FboSource;

void ofApp::setup(){
	ofBackground(0);

	// Enable or disable audio for video sources globally
	// Set this to false to save resources on the Raspberry Pi
	ofx::piMapper::VideoSource::enableAudio = true;
	ofx::piMapper::VideoSource::useHDMIForAudio = false;

	// paula:
	// karakola@riseup.net

	std::vector<std::string> images = {
		"assets/spaceship_tex_00.png",
		"assets/spaceship_tex_01.png",
		"assets/spaceship_tex_02.png",
		"assets/spaceship_tex_03.png",
		"assets/spaceship_tex_04.png",
		"assets/spaceship_tex_05.png",
		"assets/spaceship_tex_06.png",
		"assets/spaceship_tex_07.png",
		"assets/spaceship_tex_08.png",
		"assets/spaceship_tex_09.png",

		"assets/spaceship_tex_10.png",
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
		"assets/spaceship_tex_26.png",
		"assets/spaceship_tex_27.png",
		"assets/spaceship_tex_28.png",
		"assets/spaceship_tex_29.png",

		"assets/spaceship_tex_30.png",
		"assets/spaceship_tex_31.png",
		"assets/spaceship_tex_32.png",
		"assets/spaceship_tex_33.png",
		"assets/spaceship_tex_34.png",
		"assets/spaceship_tex_35.png",
		"assets/spaceship_tex_36.png",
		"assets/spaceship_tex_37.png",
		"assets/spaceship_tex_38.png",
		"assets/spaceship_tex_39.png",

		"assets/spaceship_tex_40.png",
		"assets/spaceship_tex_41.png",
		"assets/spaceship_tex_42.png",
		"assets/spaceship_tex_43.png",
		"assets/spaceship_tex_44.png",
		"assets/spaceship_tex_45.png",
		"assets/spaceship_tex_46.png",
		"assets/spaceship_tex_47.png",
		"assets/spaceship_tex_48.png",
		"assets/spaceship_tex_49.png",

		"assets/spaceship_tex_50.png",
		"assets/spaceship_tex_51.png",
		"assets/spaceship_tex_52.png",
		"assets/spaceship_tex_53.png",
		"assets/spaceship_tex_54.png",
		"assets/spaceship_tex_55.png",
		"assets/spaceship_tex_56.png",
		"assets/spaceship_tex_57.png",
		"assets/spaceship_tex_58.png",
		"assets/spaceship_tex_59.png",

		"assets/spaceship_tex_60.png",
		"assets/spaceship_tex_61.png",
		"assets/spaceship_tex_62.png",
		"assets/spaceship_tex_63.png",
		"assets/spaceship_tex_64.png",
		"assets/spaceship_tex_65.png",
		"assets/spaceship_tex_66.png",
		"assets/spaceship_tex_67.png",
		"assets/spaceship_tex_68.png",
		"assets/spaceship_tex_69.png",

		"assets/spaceship_tex_70.png",
		"assets/spaceship_tex_71.png",
		"assets/spaceship_tex_72.png",
		"assets/spaceship_tex_73.png",
		"assets/spaceship_tex_74.png",
		"assets/spaceship_tex_75.png",
		"assets/spaceship_tex_76.png",
		"assets/spaceship_tex_77.png",
		"assets/spaceship_tex_78.png",
		"assets/spaceship_tex_79.png",

		"assets/spaceship_tex_80.png",
		"assets/spaceship_tex_81.png",
		"assets/spaceship_tex_82.png",
		"assets/spaceship_tex_83.png",
		"assets/spaceship_tex_84.png",
		"assets/spaceship_tex_85.png",
		"assets/spaceship_tex_86.png",
		"assets/spaceship_tex_87.png",
		"assets/spaceship_tex_88.png",
		"assets/spaceship_tex_89.png",

		"assets/spaceship_tex_90.png",
		"assets/spaceship_tex_91.png",
		"assets/spaceship_tex_92.png",
		"assets/spaceship_tex_93.png",
		"assets/spaceship_tex_94.png",
		"assets/spaceship_tex_95.png",
		"assets/spaceship_tex_96.png",
		"assets/spaceship_tex_97.png",
		"assets/spaceship_tex_98.png",
		"assets/spaceship_tex_99.png",

		"assets/spaceship_tex_100.png",
		"assets/spaceship_tex_101.png",
		"assets/spaceship_tex_102.png",
		"assets/spaceship_tex_103.png",
		"assets/spaceship_tex_104.png",
		"assets/spaceship_tex_105.png",
		"assets/spaceship_tex_106.png",
		"assets/spaceship_tex_107.png",
		"assets/spaceship_tex_108.png",
		"assets/spaceship_tex_109.png",
		"assets/spaceship_tex_110.png",
	};

	std::vector<std::string> videos = {
		// "sources/videos/VJzoo_CVIp005diagstrips.avi"
	};

	// Add our CustomSource to list of fbo sources of the piMapper
	// FBO sources should be added before piMapper.setup() so the
	// piMapper is able to load the source if it is assigned to
	// a surface in XML settings.
	for (auto source_idx : boost::irange(0, 6))
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
	const size_t midi_root_note = 1;

	for (auto source_idx: boost::irange(0, 6))
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
