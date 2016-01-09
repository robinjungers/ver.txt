#pragma once

#include <vector>
#include <iostream>

#include <fstream>
#include <sstream>
#include <string>

#ifdef __APPLE__
	#include <glimac/SDLAppleWindowManager.hpp>
#else
	#include <glimac/SDLWindowManager.hpp>
#endif
#include <glimac/FilePath.hpp>
#include "Scene.hpp"
#include "InputManager.hpp"

enum State {

  SCENE_TRANSITION,
  SCENE_ANIMATION

};

class SceneManager {

  private:
    State m_state;

    unsigned m_currentScene;
    std::vector<Scene*> m_scenes;

    void loadTrackballCameraFromFileLine( Scene * scene, std::istringstream &lineStream );
    void loadFreeFlyCameraFromFileLine( Scene * scene, std::istringstream &lineStream );
    void loadLightFromFileLine( Scene * scene, std::istringstream &lineStream );
    void loadMaterialFromFileLine( Scene * scene, std::istringstream &lineStream );
    void loadTextureFromFileLine( Scene * scene, std::istringstream &lineStream );
    void loadSphereFromFileLine( Scene * scene, std::istringstream &lineStream );
    void loadTerrainFromFileLine( Scene * scene, std::istringstream &lineStream );
    void loadTesseractFromFileLine( Scene * scene, istringstream &lineStream );
    void loadColumnFromFileLine( Scene * scene, std::istringstream &lineStream );

  public:
    SceneManager();
    ~SceneManager();
    void loadSceneFromFile( FilePath srcPath, std::string filePath, InputManager &inputManager, float viewportWidth, float viewportHeight );

    void updateViewportDimensions( float viewportWidth, float viewportHeight );
    void setCurrentScene( unsigned index );

	void fadeIn();
	void fadeOut();
	void morphing( float parameter );

    void draw();
    void clear();

};
