#include "Scene.hpp"
#include "InputManager.hpp"

#include <iostream>

using namespace std;
using namespace glimac;
using namespace glm;


Scene::Scene( string name, FilePath vsPath, FilePath fsPath )
: m_defaultMaterial( vec3( 1.0, 1.0, 1.0 ), vec3( 1.0, 1.0, 1.0 ), 30 ),
m_defaultTexture( "default.png" ) {

  m_name = name;

  m_program = loadProgram( vsPath, fsPath );
  m_program.use();

  m_uMVPMatrix = glGetUniformLocation( m_program.getGLId(), "uMVPMatrix" );
  m_uMVMatrix = glGetUniformLocation( m_program.getGLId(), "uMVMatrix" );
  m_uNormalMatrix = glGetUniformLocation( m_program.getGLId(), "uNormalMatrix" );

  Light::getUniformLocations( m_program );
  Material::getUniformLocations( m_program );
  Texture::getUniformLocations( m_program );
  InputManager::getUniformLocations( m_program );

  m_ProjMatrix = perspective( radians(70.f), 800.f/600.f, 0.1f, 1000.f );

  cout << endl << "Creating scene called : '" << m_name << "'" << endl;

}

Scene::~Scene() {

  cout << endl << "Deleting scene called : '" << m_name << "'" << endl;

  delete m_camera;

  for ( unsigned i = 0; i < m_objects3D.size(); ++i )
    delete m_objects3D[i];
  for ( unsigned i = 0; i < m_lights.size(); ++i )
    delete m_lights[i];

}



// Setter
void Scene::setAmbientColor( vec3 color ) {

  glClearColor( color.x, color.y, color.z, 1.0 );

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

  if ( m_lights.size() == 10 )
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
void Scene::draw() {

  m_camera->moveOnPath();

  m_MVMatrix = m_camera->getViewMatrix();
  m_NormalMatrix = transpose( inverse( m_MVMatrix ) );

  glUniformMatrix4fv( m_uMVPMatrix, 1, GL_FALSE, value_ptr( m_ProjMatrix * m_MVMatrix ) );
  glUniformMatrix4fv( m_uMVMatrix, 1, GL_FALSE, value_ptr( m_MVMatrix ) );
  glUniformMatrix4fv( m_uNormalMatrix, 1, GL_FALSE, value_ptr( m_NormalMatrix ) );


  int nbLights = m_lights.size();

  Light::sendUniformNumber( nbLights );

  for ( unsigned i = 0; ( i < nbLights ) && ( i < MAX_LIGHTS ); ++i )
    m_lights[i]->sendUniformValues( m_MVMatrix, i );


  for ( unsigned i = 0; i < m_objects3D.size(); ++i )
    m_objects3D[i]->draw();

}

void Scene::clear() {

  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

}


void Scene::showUp() {
  // Transitions graphiques
}
void Scene::shutDown() {
  // Transitions graphiques
}
