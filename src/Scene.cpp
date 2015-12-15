#include "Scene.hpp"

using namespace std;
using namespace glimac;
using namespace glm;

Scene::Scene() {

}

// Setter
void Scene::setShaders( Program &program ) {
  m_program = program;
}
void Scene::setCamera( Camera &camera ) {
  m_camera = camera;
}
void Scene::setAmbientColor( vec3 color ) {
  glClearColor( color.x, color.y, color.z, 1.0 );
}

// Adder
void Scene::addObject3D( Object3D &object ) {
  m_objects3D.push_back( object );
}
void Scene::addLight( Light &light ) {
  m_lights.push_back( light );
}

// Remover
void Scene::removeAllObjects3D() {
  m_objects3D.clear();
}
void Scene::removeAllLights() {
  m_lights.clear();
}

// Transformers
void Scene::translate( glm::vec3 translation ) {

}
void Scene::rotate( glm::vec3 rotation ) {

}
void Scene::scale( glm::vec3 scale ) {

}

// Displayer
void Scene::draw() {
  for ( unsigned i = 0; i < m_Objects3D.size(); i++ )
    m_Objects3D[i].draw();
}
void Scene::clear() {
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}
void Scene::showUp() {
  // Transitions graphiques
  m_isLocked = true;
}
void Scene::shutDown() {
  m_isLocked = false;
  // Transitions graphiques
}
