#pragma once

#include <vector>
#include <GL/glew.h>
#include <glimac/glm.hpp>
#include <glimac/Program.hpp>

class Scene {

  private:
    bool m_isLocked;

    Program m_program;
    Camera m_camera;

    std::vector<Object3D> m_objects3D;
    std::vector<Light> m_lights;

  public:
    Scene();

    void setShaders( Program &program );
    void setCamera( Camera &camera );
    void setAmbientColor( glm::vec3 color );

    void addObject3D( Object3D &object );
    void addLight( Light &light );

    void removeAllObjects3D();
    void removeAllLights();

    void translate( glm::vec3 translation );
    void rotate( glm::vec3 rotation );
    void scale( glm::vec3 scale );

    void draw();
    void clear();
    void showUp();
    void shutDown();

};
