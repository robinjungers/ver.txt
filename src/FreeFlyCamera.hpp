#pragma once

#include <glimac/glm.hpp>
#include <vector>
#include "Camera.hpp"

struct FreeFlyPosition {

	glm::vec3 position;
	float phi;
	float theta;

};

class FreeFlyCamera : public Camera {

private:
	FreeFlyPosition m_currentPosition;
	std::vector<FreeFlyPosition> m_controlPoints;

	glm::vec3 m_frontVector;
	glm::vec3 m_upVector;

	void computeDirectionVectors();
	void updateFrameCounter();
	void computePosition();

public:
	FreeFlyCamera();
	FreeFlyCamera( unsigned nbFramesPerSegment );

	void addControlPoint( FreeFlyPosition controlPoint );

	void moveOnPath();
	glm::mat4 getViewMatrix();

};
