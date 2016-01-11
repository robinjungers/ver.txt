include_directories(include)
file(GLOB_RECURSE SRC_FILES *.cpp *.hpp)

if(APPLE)

	list(REMOVE_ITEM SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/SDLWindowManager.cpp)	
	
else()

	list(REMOVE_ITEM SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/SDLAppleWindowManager.cpp)

endif()

add_library(glimac ${SRC_FILES})
