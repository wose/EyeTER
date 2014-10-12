set(EyeTER_SRC
  main.cpp
  MainWindow.cpp
  ProgramEditorWidget.cpp
)

set(EyeTER_HDR
  ../include/MainWindow.h
  ../include/ProgramEditorWidget.h
)

add_executable( EyeTER ${EyeTER_SRC} ${EyeTER_HDR} )
qt5_use_modules( EyeTER Widgets )
target_link_libraries( EyeTER ${OpenCV_LIBS} ${OpenGL_LIBS} ${QSCINTILLA2_LIBRARY})