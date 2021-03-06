#pragma once

#include <vector>
#include <glimac/glm.hpp>
#include <glimac/common.hpp>
#include "Texture.hpp"
#include "Material.hpp"

class Object3D {

  protected:
    Material * m_material;
    Texture * m_texture;
    GLuint m_vbo;
    GLuint m_vao;
    bool m_castsLight;

    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
    bool m_isRescalable;

    float m_morphingParameter;
    float m_fadingParameter;
    float m_currentMorphingParameter;
    float m_currentFadingParameter;

    std::vector<glimac::ShapeVertex> m_vertices;

    virtual void buildVertices() = 0;
    void initVertices();
    void reInitVertices();

  public:
    Object3D();
    virtual ~Object3D() {};

    void setPosition( glm::vec3 position );
    void setRotation( glm::vec3 rotation );
    void setScale( glm::vec3 scale );

    void setMaterial( Material * material );
    void setTexture( Texture * texture );

    void pushMorphingParameter( float morphingParameter );
    void pushFadingParameter( float fadingParameter );

    glm::vec3 getPosition();
    glm::vec3 getRotation();
    glm::vec3 getScale();
    float getFading();

    bool transition();
    virtual void animation() = 0;

    virtual void draw() = 0;

};

class Solid : public Object3D {

  public:
    void draw();

};
