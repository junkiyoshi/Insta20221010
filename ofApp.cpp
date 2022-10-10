#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(255);

	int size = 10;
	for (int x = 30; x < 690; x += size) {

		for (int y = 30; y < 690; y += size) {

			int index = this->mesh.getNumVertices();

			this->mesh.addVertex(glm::vec3(x, y, 0));
			this->mesh.addVertex(glm::vec3(x + size, y, 0));
			this->mesh.addVertex(glm::vec3(x + size, y + size, 0));
			this->mesh.addVertex(glm::vec3(x, y + size, 0));

			this->mesh.addIndex(index + 0);
			this->mesh.addIndex(index + 1);
			this->mesh.addIndex(index + 2);

			this->mesh.addIndex(index + 0);
			this->mesh.addIndex(index + 2);
			this->mesh.addIndex(index + 3);

			this->mesh.addColor(ofColor(0));
			this->mesh.addColor(ofColor(0));
			this->mesh.addColor(ofColor(0));
			this->mesh.addColor(ofColor(0));
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
	auto noise_seed = glm::vec4(ofRandom(1000), ofRandom(1000), ofRandom(1000), ofRandom(1000));

	auto noise_step = 0.001;
	auto frame_step = 0.03;

	for (int i = 0; i < this->mesh.getNumVertices(); i++) {

		auto vertex = this->mesh.getVertex(i);
		auto noise_value = glm::vec3(
			ofNoise(noise_seed.r, vertex.x * noise_step, vertex.y * noise_step + ofGetFrameNum() * frame_step),
			ofNoise(noise_seed.g, vertex.x * noise_step, vertex.y * noise_step + ofGetFrameNum() * frame_step),
			ofNoise(noise_seed.b, vertex.x * noise_step, vertex.y * noise_step + ofGetFrameNum() * frame_step));

		auto r = noise_value.r < 0.2 ? 0 : noise_value.r < 0.7 ? ofMap(noise_value.r, 0.2, 0.7, 0, 255) : 255;
		auto g = noise_value.g < 0.2 ? 0 : noise_value.g < 0.7 ? ofMap(noise_value.g, 0.2, 0.7, 0, 255) : 255;
		auto b = noise_value.b < 0.2 ? 0 : noise_value.b < 0.7 ? ofMap(noise_value.b, 0.2, 0.7, 0, 255) : 255;

		this->mesh.setColor(i, ofColor(r, g, b, 255));
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->mesh.draw();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}