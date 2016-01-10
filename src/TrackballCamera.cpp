#include "TrackballCamera.hpp"
#include "tools.hpp"
#include <iostream>

using namespace glm;

TrackballCamera::TrackballCamera() {

    m_currentPosition.distance = 5.0;
    m_currentPosition.angleX = 0.0;
    m_currentPosition.angleY = 0.0;

    m_nbFramesPerSegment = 3000;
    m_currentFrame = 0;
    m_currentSegment = 0;

    m_angle = 70.0;

}

TrackballCamera::TrackballCamera( unsigned nbFramesPerSegment, float angle ) {

    m_currentPosition.distance = 5.0;
    m_currentPosition.angleX = 0.0;
    m_currentPosition.angleY = 0.0;

    m_nbFramesPerSegment = nbFramesPerSegment;
    m_currentFrame = 0;
    m_currentSegment = 0;

    m_angle = angle;

}

void TrackballCamera::updateFrameCounter() {

    m_currentFrame++;
    if ( m_currentFrame >= m_nbFramesPerSegment ) {

        m_currentFrame = 0;
        m_currentSegment++;

        if ( m_currentSegment >= m_controlPoints.size() - 1 ) // If we have reached the total number of segments
            m_currentSegment = 0;

    }

}

void TrackballCamera::computePosition() {

    m_currentPosition.distance = map( m_currentFrame,
                                      0, m_nbFramesPerSegment,
                                      m_controlPoints[m_currentSegment].distance, m_controlPoints[m_currentSegment + 1].distance
                                      );

    m_currentPosition.angleX = map( m_currentFrame,
                                    0, m_nbFramesPerSegment,
                                    m_controlPoints[m_currentSegment].angleX, m_controlPoints[m_currentSegment + 1].angleX
                                    );

    m_currentPosition.angleY = map( m_currentFrame,
                                    0, m_nbFramesPerSegment,
                                    m_controlPoints[m_currentSegment].angleY, m_controlPoints[m_currentSegment + 1].angleY
                                    );

}

void TrackballCamera::addControlPoint( TrackballPosition controlPoint ) {

    m_controlPoints.push_back( controlPoint );

}

void TrackballCamera::moveOnPath() {

    // If at least 2 control points are defined
    if ( m_controlPoints.size() >= 2 ) {

        computePosition();
        updateFrameCounter();

    } else if ( m_controlPoints.size() == 1 ) {

        m_currentPosition = m_controlPoints[0];

    }

}

mat4 TrackballCamera::getViewMatrix() {

    mat4 matrixId = mat4( 1.0 );

    float radAngleX = radians( m_currentPosition.angleX );
    float radAngleY = radians( m_currentPosition.angleY );

    mat4 matrixMoveFront = translate( matrixId, vec3( 0.0f, 0.0f, -m_currentPosition.distance ) );
    mat4 matrixRotateLeft = rotate( matrixId, radAngleX, vec3( 1, 0, 0 ) );
    mat4 matrixRotateUp = rotate( matrixId, radAngleY, vec3( 0, 1, 0 ) );

    return matrixMoveFront * matrixRotateLeft * matrixRotateUp;
}
