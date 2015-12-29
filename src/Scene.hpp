#pragma once

#include <vector>
#include <GL/glew.h>
#include <glimac/glm.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>

#include "Object3D.hpp"
#include "Light.hpp"
#include "Material.hpp"
#include "Texture.hpp"
#include "TrackballCamera.hpp"
#include "FreeFlyCamera.hpp"


class Scene {

  private:
    std::string m_name;
    Program m_program;

    GLint m_uMVPMatrix;
    GLint m_uMVMatrix;
    GLint m_uNormalMatrix;

    glm::mat4 m_ProjMatrix;
    glm::mat4 m_MVMatrix;
    glm::mat4 m_NormalMatrix;

    std::vector<Object3D*> m_objects3D;
    std::vector<Light*> m_lights;
    std::vector<Material> m_materials;
    std::vector<Texture> m_textures;

    Material m_defaultMaterial;
    Texture m_defaultTexture;

    Camera * m_camera;

  public:
    Scene( string name, FilePath vsPath, FilePath fsPath, float viewportWidth, float viewportHeight );
    ~Scene();

    void setViewportDimensions( float viewportWidth, float viewportHeight );
    void setAmbientColor( glm::vec3 color );
    void setCamera( Camera *camera );

    void addObject3D( Object3D *object );
    void addObject3D( Object3D *object, int idMaterial );
    void addObject3D( Object3D *object, int idMaterial, int idTexture );
    void addLight( Light *light );

    void addMaterial( vec3 diffuseColor, vec3 specularColor, int shininess );
    void addTexture( string fileTexture );

    void removeAllObjects3D();
    void removeAllLights();

    void triggerFadeIn();
    void triggerFadeOut();
    void triggerMorphing( float parameter );

    bool update();
    void animate();
    void draw();
    void clear();

};
