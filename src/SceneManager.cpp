#include "SceneManager.hpp"

#include <glimac/glm.hpp>

#include "Sphere.hpp"
#include "Terrain.hpp"
#include "Light.hpp"
#include "Material.hpp"
#include "Texture.hpp"
#include "TrackballCamera.hpp"
#include "FreeFlyCamera.hpp"
#include "Column.hpp"

using namespace std;
using namespace glm;

SceneManager::SceneManager() {

  m_currentScene = 0;
  m_state = SCENE_TRANSITION;

}

SceneManager::~SceneManager() {

  for ( unsigned i = 0; i < m_scenes.size(); ++i )
    delete m_scenes[i];

}


void SceneManager::loadSceneFromFile( FilePath srcPath, string filePath, InputManager &inputManager, float viewportWidth, float viewportHeight ) {

  Scene * scene;

  ifstream fileStream( "assets/config/" + filePath );

  string line;
  while ( std::getline(fileStream, line) ) {
    istringstream lineStream(line);
    string lineHead;

    // Verification du premier terme de la ligne
    if ( !(lineStream >> lineHead) ) break;

    // Déclaration de Scène
    if ( lineHead == "SCENE:" ) {

      string sceneName, vsPath, fsPath;
      lineStream >> sceneName >> vsPath >> fsPath;
      scene = new Scene( sceneName, srcPath.dirPath() + vsPath, srcPath.dirPath() + fsPath, viewportWidth, viewportHeight );
      inputManager.addEntry( sceneName );

    }

    // Ajout Trackball caméra
    else if ( lineHead == "TRACKBALLCAMERA:" )
      loadTrackballCameraFromFileLine( scene, lineStream );

    // Ajout FreeFly caméra
    else if ( lineHead == "FREEFLYCAMERA:" )
      loadFreeFlyCameraFromFileLine( scene, lineStream );

    // Ajout lumière
    else if ( lineHead == "LIGHT:" )
      loadLightFromFileLine( scene, lineStream );

    // Ajout matériaux
    else if ( lineHead == "MATERIAL:" )
      loadMaterialFromFileLine( scene, lineStream );

    // Ajout texture
    else if ( lineHead == "TEXTURE:" )
      loadTextureFromFileLine( scene, lineStream );

    // Ajout Sphère
    else if ( lineHead == "SPHERE:" )
      loadSphereFromFileLine( scene, lineStream );

    // Ajout terrain
    else if ( lineHead == "TERRAIN:" )
      loadTerrainFromFileLine( scene, lineStream );

    // Ajout column
    else if ( lineHead == "COLUMN:" )
      loadColumnFromFileLine( scene, lineStream );


  }

  m_scenes.push_back( scene );

}

void SceneManager::loadTrackballCameraFromFileLine( Scene * scene, istringstream &lineStream ) {

  unsigned cameraTime;
  lineStream >> cameraTime;
  TrackballCamera * camera = new TrackballCamera( cameraTime );

  float x, y, z;
  while ( lineStream >> x >> y >> z )
    camera->addControlPoint( (TrackballPosition) { x, y, z } );

  scene->setCamera( camera );

}

void SceneManager::loadFreeFlyCameraFromFileLine( Scene * scene, istringstream &lineStream ) {

  unsigned cameraTime;
  lineStream >> cameraTime;
  FreeFlyCamera * camera = new FreeFlyCamera( cameraTime );

  float x, y, z, phi, theta;
  while ( lineStream >> x >> y >> z >> phi >> theta)
    camera->addControlPoint( (FreeFlyPosition) { vec3(x, y, z), phi, theta } );

  scene->setCamera( camera );

}

void SceneManager::loadLightFromFileLine( Scene * scene, istringstream &lineStream ) {

  float x, y, z, w, r, g, b;
  lineStream >> x >> y >> z >> w >> r >> g >> b;
  Light * light = new Light( vec4(x, y, z, w), vec3(r, g, b) );
  scene->addLight( light );

}

void SceneManager::loadMaterialFromFileLine( Scene * scene, istringstream &lineStream ) {

  float r1, g1, b1, r2, g2, b2, shininess;
  lineStream >> r1 >> g1 >> b1 >> r2 >> g2 >> b2 >> shininess;
  scene->addMaterial( vec3(r1, g1, b1), vec3(r2, g2, b2), shininess );

}

void SceneManager::loadTextureFromFileLine( Scene * scene, istringstream &lineStream ) {

  string textureFile;
  lineStream >> textureFile;
  scene->addTexture( textureFile );

}

void SceneManager::loadSphereFromFileLine( Scene * scene, istringstream &lineStream ) {

  int materialId, textureId;
  lineStream >> materialId >> textureId;

  Sphere * sphere = new Sphere();
  if ( materialId >= 0 ) {
    if ( textureId >= 0 )
      scene->addObject3D( sphere, materialId, textureId );
    else
      scene->addObject3D( sphere, materialId );
  } else {
    scene->addObject3D( sphere );
  }

}

void SceneManager::loadTerrainFromFileLine( Scene * scene, istringstream &lineStream ) {

  int materialId, textureId;
  lineStream >> materialId >> textureId;

  Terrain * terrain = new Terrain();
  if ( materialId >= 0 ) {
    if ( textureId >= 0 )
      scene->addObject3D( terrain, materialId, textureId );
    else
      scene->addObject3D( terrain, materialId );
  } else {
    scene->addObject3D( terrain );
  }

}

void SceneManager::loadColumnFromFileLine( Scene * scene, std::istringstream &lineStream ){
  
  int materialId, textureId;
  lineStream >> materialId >> textureId;

  Column * column = new Column();
  if ( materialId >= 0 ) {
    if ( textureId >= 0 )
      scene->addObject3D( column, materialId, textureId );
    else
      scene->addObject3D( column, materialId );
  } else {
    scene->addObject3D( column );
  }

}

void SceneManager::updateViewportDimensions( float viewportWidth, float viewportHeight ) {

  glViewport(0, 0, viewportWidth, viewportHeight);

  for ( unsigned i = 0; i < m_scenes.size(); ++i )
    m_scenes[i]->setViewportDimensions( viewportWidth, viewportHeight );

}

void SceneManager::setCurrentScene( unsigned index ) {

  m_currentScene = index;

}


void SceneManager::fadeIn() {
  m_state = SCENE_TRANSITION;
  m_scenes[ m_currentScene ]->triggerFadeIn();
}
void SceneManager::fadeOut() {
  m_state = SCENE_TRANSITION;
  m_scenes[ m_currentScene ]->triggerFadeOut();
}
void SceneManager::morphing( float parameter ) {
  m_state = SCENE_TRANSITION;
  m_scenes[ m_currentScene ]->triggerMorphing( parameter );
}



void SceneManager::draw() {

  m_scenes[ m_currentScene ]->setAmbientColor( vec3( 1.0, 1.0, 1.0 ) );

  if ( m_state == SCENE_TRANSITION ) {
    bool isUpdating = m_scenes[ m_currentScene ]->update();
    if ( !isUpdating )
      m_state = SCENE_ANIMATION;
  } else {
    m_scenes[ m_currentScene ]->animate();
  }

  m_scenes[ m_currentScene ]->draw();

}

void SceneManager::clear() {

  m_scenes[ m_currentScene ]->clear();

}
