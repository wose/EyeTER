set(EyeTER_SRC
  ChartWidget.cpp
  Editor.cpp
  GraphicWindow.cpp
  Highlighter.cpp
  HistogramWindow.cpp
  main.cpp
  MainWindow.cpp
  OpenGLWidget.cpp
  OperatorModel.cpp
  ProgramEditorWidget.cpp
)

set(EyeTER_HDR
  ../include/ChartWidget.h
  ../include/Editor.h
  ../include/EditorMarginArea.h
  ../include/GraphicWindow.h
  ../include/Highlighter.h
  ../include/HistogramWindow.h
  ../include/MainWindow.h
  ../include/OpenGLWidget.h
  ../include/OperatorModel.h
  ../include/ProgramEditorWidget.h
)

add_executable( EyeTER ${EyeTER_SRC} ${EyeTER_HDR} )
qt5_use_modules( EyeTER Widgets OpenGL)
target_link_libraries( EyeTER eyeter ${OpenCV_LIBS} ${OpenGL_LIBS})