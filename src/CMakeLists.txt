set(SRC
EyeTERApp.cpp
MainFrame.cpp
GraphicFrame.cpp
GLPane.cpp)

add_executable( EyeTER ${SRC})
target_link_libraries( EyeTER ${OpenCV_LIBS} ${wxWidgets_LIBRARIES} ${OpenGL_LIBS})
