#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(1.5);
	ofNoFill();
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(250, 1);
	this->triangles = ico_sphere.getMesh().getUniqueFaces();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	
	int log = 10;
	float noise_seed_x = ofRandom(1000);
	float noise_seed_y = ofRandom(1000);
	for (auto& triangle : this->triangles) {

		for (int j = 0; j < 3; j++) {

			ofBeginShape();
			for (int i = 0; i < log; i++) {

				glm::vec3 location(triangle.getVertex(j).x, triangle.getVertex(j).y, triangle.getVertex(j).z);
				auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed_x, (ofGetFrameNum() + i) * 0.008), 0, 1, -PI, PI), glm::vec3(1, 0, 0));
				auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed_y, (ofGetFrameNum() + i) * 0.008), 0, 1, -PI, PI), glm::vec3(0, 1, 0));

				location = glm::vec4(location, 0) * rotation_x * rotation_y;
				ofVertex(location);

				if (i == log - 1) {

					ofFill();
					ofDrawSphere(location, 5);
					ofNoFill();
				}
			}

			ofEndShape();
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}