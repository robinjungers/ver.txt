#include "SceneManager.hpp"

#include "Sphere.hpp"
#include "Terrain.hpp"
#include "Tesseract.hpp"
#include "Light.hpp"
#include "Material.hpp"
#include "Texture.hpp"
#include "TrackballCamera.hpp"
#include "FreeFlyCamera.hpp"
#include "Column.hpp"
#include "SkyBox.hpp"
#include "tools.hpp"

using namespace std;
using namespace glm;

SceneManager::SceneManager() {

  m_currentScene = 0;
  m_incomingScene = 0;
  m_state = SCENE_FADEIN;
  m_clearColor = vec4( 1.0, 1.0, 1.0, 1.0 );

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

    // Ajout tesseract
    else if ( lineHead == "TESSERACT:" )
      loadTesseractFromFileLine( scene, lineStream );

    // Ajout column
    else if ( lineHead == "COLUMN:" )
      loadColumnFromFileLine( scene, lineStream );

    // Ajout SkyBox
    else if ( lineHead == "SKYBOX:" )
      loadSkyBoxFromFileLine( scene, lineStream );

  }

  m_scenes.push_back( scene );

}

void SceneManager::loadTrackballCameraFromFileLine( Scene * scene, istringstream &lineStream ) {

  unsigned cameraTime;
  float cameraAngle;
  lineStream >> cameraTime >> cameraAngle;
  TrackballCamera * camera = new TrackballCamera( cameraTime, cameraAngle );

  float x, y, z;
  while ( lineStream >> x >> y >> z )
    camera->addControlPoint( (TrackballPosition) { x, y, z } );

  scene->setCamera( camera );

}

void SceneManager::loadFreeFlyCameraFromFileLine( Scene * scene, istringstream &lineStream ) {

  unsigned cameraTime;
  float cameraAngle;
  lineStream >> cameraTime >> cameraAngle;
  FreeFlyCamera * camera = new FreeFlyCamera( cameraTime, cameraAngle );

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
  vec3 position, rotation, scale;
  lineStream >> materialId >> textureId >> position.x >> position.y >> position.z >> rotation.x >> rotation.y >> rotation.z >> scale.x >> scale.y >> scale.z;

  Sphere * sphere = new Sphere();

  sphere->setPosition( position );
  sphere->setRotation( rotation );
  sphere->setScale( scale );

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
  vec3 position, rotation, scale;
  lineStream >> materialId >> textureId >> position.x >> position.y >> position.z >> rotation.x >> rotation.y >> rotation.z >> scale.x >> scale.y >> scale.z;

  Terrain * terrain = new Terrain();

  terrain->setPosition( position );
  terrain->setRotation( rotation );
  terrain->setScale( scale );

  if ( materialId >= 0 ) {
    if ( textureId >= 0 )
      scene->addObject3D( terrain, materialId, textureId );
    else
      scene->addObject3D( terrain, materialId );
  } else {
    scene->addObject3D( terrain );
  }

}

void SceneManager::loadTesseractFromFileLine( Scene * scene, istringstream &lineStream ) {

  int materialId, textureId;
  vec3 position, rotation, scale;
  lineStream >> materialId >> textureId >> position.x >> position.y >> position.z >> rotation.x >> rotation.y >> rotation.z >> scale.x >> scale.y >> scale.z;

  Tesseract * tesseract = new Tesseract();

  tesseract->setPosition( position );
  tesseract->setRotation( rotation );
  tesseract->setScale( scale );

  if ( materialId >= 0 ) {
    if ( textureId >= 0 )
      scene->addObject3D( tesseract, materialId, textureId );
    else
      scene->addObject3D( tesseract, materialId );
  } else
    scene->addObject3D( tesseract );

}

void SceneManager::loadColumnFromFileLine( Scene * scene, std::istringstream &lineStream ){

  int materialId, textureId;
  vec3 position, rotation, scale;
  lineStream >> materialId >> textureId >> position.x >> position.y >> position.z >> rotation.x >> rotation.y >> rotation.z >> scale.x >> scale.y >> scale.z;

  Column * column = new Column();

  column->setPosition( position );
  column->setRotation( rotation );
  column->setScale( scale );

  if ( materialId >= 0 ) {
    if ( textureId >= 0 )
      scene->addObject3D( column, materialId, textureId );
    else
      scene->addObject3D( column, materialId );
  } else {
    scene->addObject3D( column );
  }

}

void SceneManager::loadSkyBoxFromFileLine( Scene * scene, std::istringstream &lineStream ){

  int materialId, textureId;
  vec3 position, rotation, scale;
  lineStream >> materialId >> textureId >> position.x >> position.y >> position.z >> rotation.x >> rotation.y >> rotation.z >> scale.x >> scale.y >> scale.z;

  SkyBox * skyBox = new SkyBox();

  skyBox->setPosition( position );
  skyBox->setRotation( rotation );
  skyBox->setScale( scale );

  if ( materialId >= 0 ) {
    if ( textureId >= 0 )
      scene->addObject3D( skyBox, materialId, textureId );
    else
      scene->addObject3D( skyBox, materialId );
  } else {
    scene->addObject3D( skyBox );
  }

}

void SceneManager::updateViewportDimensions( float viewportWidth, float viewportHeight ) {

  for ( unsigned i = 0; i < m_scenes.size(); ++i )
    m_scenes[i]->setViewportDimensions( viewportWidth, viewportHeight );

}

void SceneManager::switchToScene( unsigned index ) {

  m_incomingScene = index;

}

bool SceneManager::isAvailable() {
  return (m_state == SCENE_ANIMATION) ? true: false;
}


void SceneManager::fadeIn() {
  m_state = SCENE_FADEIN;
  m_scenes[ m_currentScene ]->triggerFadeIn();
}
void SceneManager::fadeOut() {
  m_state = SCENE_FADEOUT;
  m_scenes[ m_currentScene ]->triggerFadeOut();
}
void SceneManager::morphing( float parameter ) {
  m_state = SCENE_MORPHING;
  m_scenes[ m_currentScene ]->triggerMorphing( parameter );
}



void SceneManager::draw() {

  if ( m_state == SCENE_ANIMATION ) {
    m_scenes[ m_currentScene ]->animate();
  } else {

    bool isUpdating = m_scenes[ m_currentScene ]->update();

    if ( !isUpdating ) {
      if ( m_state == SCENE_FADEOUT) {
        m_currentScene = m_incomingScene;
        m_state = SCENE_FADEIN;
        m_scenes[ m_currentScene ]->triggerFadeIn();
      } else {
        m_state = SCENE_ANIMATION;
      }
    }
  }

  m_scenes[ m_currentScene ]->use();
  m_scenes[ m_currentScene ]->draw();

}

void SceneManager::clear() {

  glClearColor( m_clearColor.x, m_clearColor.y, m_clearColor.z, 1.0 );
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

}
