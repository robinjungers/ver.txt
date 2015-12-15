#pragma once

#include <glimac/glm.hpp>

struct Vertex3D {

  glm::vec3 position;
  glm::vec3 normal;
  glm::vec3 texCoords;

};


class Object3D {

  private:
    Material m_material;
    Texture m_texture;
    GLint m_vbo;
    GLint m_vao;

    glm::vec3 m_position;
    std::vector<Vertex3D> m_vertices;

  public:
    Object3D();
    void initVertices();

    void setPosition( glm::vec3 position );
    void setTexture( Texture &texture );

    void draw();

};
