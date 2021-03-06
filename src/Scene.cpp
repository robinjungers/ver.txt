#include "Scene.hpp"
#include "InputManager.hpp"
#include "Tesseract.hpp"

#include <iostream>

using namespace std;
using namespace glimac;
using namespace glm;


Scene::Scene( string name, FilePath vsPath, FilePath fsPath )
: m_defaultMaterial( vec3( 1.0, 1.0, 1.0 ), vec3( 1.0, 1.0, 1.0 ), 30 ),
m_defaultTexture( "default.png" ) {

  m_name = name;

  m_program = loadProgram( vsPath, fsPath );

  m_uMVPMatrix = glGetUniformLocation( m_program.getGLId(), "uMVPMatrix" );
  m_uMVMatrix = glGetUniformLocation( m_program.getGLId(), "uMVMatrix" );
  m_uNormalMatrix = glGetUniformLocation( m_program.getGLId(), "uNormalMatrix" );
  m_uViewportDimensions = glGetUniformLocation( m_program.getGLId(), "uViewportDimensions" );

  m_ambientColor.r = 0;
  m_ambientColor.g = 0;
  m_ambientColor.b = 0;

  cout << "Creating scene called : '" << m_name << "'\n";

}

Scene::~Scene() {

  cout << "Deleting scene called : '" << m_name << "'\n";

  delete m_camera;

  for ( unsigned i = 0; i < m_objects3D.size(); ++i )
    delete m_objects3D[i];
  for ( unsigned i = 0; i < m_lights.size(); ++i )
    delete m_lights[i];

}



// Setter
void Scene::setViewportDimensions( float viewportWidth, float viewportHeight ) {

  m_ProjMatrix = perspective( radians( (float) m_camera->getAngle() ), viewportWidth / viewportHeight, 0.1f, 1000.f );
  glUniform2f( m_uViewportDimensions, viewportWidth, viewportHeight );

}

void Scene::setAmbientColor( vec3 color ) {

  m_ambientColor = color;

}

void Scene::setCamera( Camera *camera ) {

  m_camera = camera;

}



// Adder
void Scene::addObject3D( Object3D *object ) {

  m_objects3D.push_back( object );
  m_objects3D.back()->setMaterial( &m_defaultMaterial );
  m_objects3D.back()->setTexture( &m_defaultTexture );

}

void Scene::addObject3D( Object3D *object, int idMaterial ) {

  m_objects3D.push_back( object );
  m_objects3D.back()->setMaterial( &( m_materials[idMaterial] ) );
  m_objects3D.back()->setTexture( &m_defaultTexture );

}

void Scene::addObject3D( Object3D *object, int idMaterial, int idTexture ) {

  m_objects3D.push_back( object );
  m_objects3D.back()->setMaterial( &( m_materials[idMaterial] ) );
  m_objects3D.back()->setTexture( &( m_textures[idTexture] ) );

}

void Scene::addLight( Light *light ) {

  if ( m_lights.size() == MAX_LIGHTS )
    m_lights.erase(  m_lights.begin() );

  m_lights.push_back( light );
  m_lights.back()->getUniformLocations( m_program );

}

void Scene::addMaterial( vec3 diffuseColor, vec3 specularColor, int shininess ) {

  m_materials.push_back( Material( diffuseColor, specularColor, shininess ) );

}

void Scene::addTexture( string fileTexture ) {

  m_textures.push_back( Texture( fileTexture ) );

}



// Displayer
void Scene::use() {

  m_program.use();

  Light::getUniformLocations( m_program );
  Material::getUniformLocations( m_program );
  Texture::getUniformLocations( m_program );
  InputManager::getUniformLocations( m_program );
  Tesseract::getUniformLocations( m_program );

}

bool Scene::update() {
  bool isUpdating = true;
  for ( unsigned i = 0; i < m_objects3D.size(); ++i ) {
    if ( !m_objects3D[i]->transition() )
      isUpdating = false;
  }
  return isUpdating;
}

void Scene::animate() {
  for ( unsigned i = 0; i < m_objects3D.size(); ++i )
    m_objects3D[i]->animation();
}

void Scene::draw() {

  m_camera->moveOnPath();

  int nbLights = m_lights.size();
  Light::sendUniformNumber( nbLights );

  for ( unsigned i = 0; i < m_objects3D.size(); ++i ) {

    mat4 MVMatrix = m_camera->getViewMatrix();

    MVMatrix = scale( MVMatrix, m_objects3D[i]->getScale() * m_objects3D[i]->getFading() );
    MVMatrix = rotate( MVMatrix, m_objects3D[i]->getRotation().x, vec3( 1, 0, 0 ) );
    MVMatrix = rotate( MVMatrix, m_objects3D[i]->getRotation().y, vec3( 0, 1, 0 ) );
    MVMatrix = rotate( MVMatrix, m_objects3D[i]->getRotation().z, vec3( 0, 0, 1 ) );
    MVMatrix = translate( MVMatrix, m_objects3D[i]->getPosition() );

    mat4 normalMatrix = transpose( inverse( MVMatrix ) );

    glUniformMatrix4fv( m_uMVPMatrix, 1, GL_FALSE, value_ptr( m_ProjMatrix * MVMatrix ) );
    glUniformMatrix4fv( m_uMVMatrix, 1, GL_FALSE, value_ptr( MVMatrix ) );
    glUniformMatrix4fv( m_uNormalMatrix, 1, GL_FALSE, value_ptr( normalMatrix ) );

    for ( unsigned i = 0; ( i < nbLights ) && ( i < MAX_LIGHTS ); ++i )
      m_lights[i]->sendUniformValues( MVMatrix, i );

    m_objects3D[i]->draw();

  }

}

void Scene::clear() {

  glClearColor( m_ambientColor.r, m_ambientColor.g, m_ambientColor.b, 1.0 );
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

}

void Scene::triggerFadeIn() {
  for ( unsigned i = 0; i < m_objects3D.size(); ++i )
    m_objects3D[i]->pushFadingParameter( 1.0 );
}

void Scene::triggerFadeOut() {
  for ( unsigned i = 0; i < m_objects3D.size(); ++i )
    m_objects3D[i]->pushFadingParameter( 0.0 );
}

void Scene::triggerMorphing( float parameter ) {
  for ( unsigned i = 0; i < m_objects3D.size(); ++i )
    m_objects3D[i]->pushMorphingParameter( parameter );
}
