#pragma once

#include <glimac/glm.hpp>
#include <vector>
#include "Camera.hpp"

struct TrackballPosition {

	float distance;
    float angleX;
    float angleY;

};

class TrackballCamera : public Camera {

private:
    TrackballPosition m_currentPosition;
	std::vector<TrackballPosition> m_controlPoints;

	void updateFrameCounter();
	void computePosition();

public:
	TrackballCamera();
	TrackballCamera( unsigned nbFramesPerSegment, float angle );
	~TrackballCamera() {};

	void addControlPoint( TrackballPosition controlPoint );

	void moveOnPath();
	glm::mat4 getViewMatrix();

};
