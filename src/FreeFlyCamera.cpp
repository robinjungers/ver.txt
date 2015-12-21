#include "FreeFlyCamera.hpp"
#include "tools.hpp"

using namespace glm;

FreeFlyCamera::FreeFlyCamera() {

	m_currentPosition.position = vec3( 0.0f );
	m_currentPosition.phi = 90;
	m_currentPosition.theta = 0.0;

	m_nbFramesPerSegment = 3000;
	m_currentFrame = 0;
	m_currentSegment = 0;

}

FreeFlyCamera::FreeFlyCamera( unsigned nbFramesPerSegment ) {

	m_currentPosition.position = vec3( 0.0f );;
	m_currentPosition.phi = 90;
	m_currentPosition.theta = 0.0;

	m_nbFramesPerSegment = nbFramesPerSegment;
	m_currentFrame = 0;
	m_currentSegment = 0;

}

void FreeFlyCamera::computeDirectionVectors() {

	float radPhi = radians( m_currentPosition.phi );
	float radTheta = radians( m_currentPosition.theta );

	m_frontVector = vec3( cos( radTheta ) * sin( radPhi ), sin( radTheta ), cos( radTheta ) * cos( radPhi ) );
	vec3 m_leftVector = vec3( sin( radPhi + ( PI / 2.0 ) ), 0, cos( radPhi + ( PI / 2.0 ) ) );
	m_upVector = cross( m_frontVector, m_leftVector );

}

void FreeFlyCamera::updateFrameCounter() {

	m_currentFrame++;
	if ( m_currentFrame >= m_nbFramesPerSegment ) {

		m_currentFrame = 0;
		m_currentSegment++;

		if ( m_currentSegment >= m_controlPoints.size() - 1 ) // If we have reached the total number of segments
			m_currentSegment = 0;

	}

}

void FreeFlyCamera::computePosition() {

	m_currentPosition.position.x = map(	m_currentFrame,
										0, m_nbFramesPerSegment,
										m_controlPoints[m_currentSegment].position.x, m_controlPoints[m_currentSegment + 1].position.x
										);

	m_currentPosition.position.y = map(	m_currentFrame,
										0, m_nbFramesPerSegment,
										m_controlPoints[m_currentSegment].position.y, m_controlPoints[m_currentSegment + 1].position.y
										);

	m_currentPosition.position.z = map(	m_currentFrame,
										0, m_nbFramesPerSegment,
										m_controlPoints[m_currentSegment].position.z, m_controlPoints[m_currentSegment + 1].position.z
										);

	m_currentPosition.phi = map( m_currentFrame,
								 0, m_nbFramesPerSegment,
								 m_controlPoints[m_currentSegment].phi, m_controlPoints[m_currentSegment + 1].phi
								 );

	m_currentPosition.theta = map( m_currentFrame,
								   0, m_nbFramesPerSegment,
								   m_controlPoints[m_currentSegment].theta, m_controlPoints[m_currentSegment + 1].theta
								   );

}

void FreeFlyCamera::addControlPoint( FreeFlyPosition controlPoint ) {

	m_controlPoints.push_back( controlPoint );

}

void FreeFlyCamera::moveOnPath() {

	// If at least 2 control points are defined
	if (m_controlPoints.size() >= 2) {

		computePosition();
		updateFrameCounter();

	} else if ( m_controlPoints.size() == 1 ) {

        m_currentPosition = m_controlPoints[0];

    }

}

mat4 FreeFlyCamera::getViewMatrix() {

	computeDirectionVectors();

	mat4 MV = lookAt( m_currentPosition.position, m_currentPosition.position + m_frontVector, m_upVector );

	return MV;
}
