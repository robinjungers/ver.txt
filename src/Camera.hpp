#pragma once

#include <glimac/glm.hpp>

class Camera {

  protected:
    unsigned m_nbFramesPerSegment;
    unsigned m_currentFrame;
    unsigned m_currentSegment;

  public:
    virtual ~Camera() {};

    virtual void moveOnPath() = 0;
    virtual glm::mat4 getViewMatrix() = 0;

};
