set(EyeTER_SRC
  Editor.cpp
  main.cpp
  MainWindow.cpp
  ProgramEditorWidget.cpp
)

set(EyeTER_HDR
  ../include/Editor.h
  ../include/EditorMarginArea.h
  ../include/MainWindow.h
  ../include/ProgramEditorWidget.h
)

add_executable( EyeTER ${EyeTER_SRC} ${EyeTER_HDR} )
qt5_use_modules( EyeTER Widgets )
target_link_libraries( EyeTER eyeter ${OpenCV_LIBS} ${OpenGL_LIBS})