#pragma once

#include <vector>
#include <cstddef>
#include <GL/glew.h>
#include <glimac/glm.hpp>
#include <glimac/common.hpp>
#include "Texture.hpp"

class Object3D {

  private:
    //Material m_material;
    //Texture m_texture;
    GLuint m_vbo;
    GLuint m_vao;

    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
    std::vector<glimac::ShapeVertex> m_vertices;

  public:
    Object3D();
    virtual void buildVertices() = 0;
    void initVertices();

    void setPosition( glm::vec3 position );
    void setRotation( glm::vec3 rotation );
    void setScale( glm::vec3 scale );
    //void setMaterial( Material material );
    //void setTexture( Texture texture );

    glm::vec3 getPosition();
    glm::vec3 getRotation();
    glm::vec3 getScale();

    void translate();

    virtual void transition() = 0;
    virtual void animation() = 0;

    void draw();

};
