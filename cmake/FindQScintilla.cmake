# 2014-10-09 wose: found at http://pastebin.com/fkBwbEXk

# Module file for QScintilla - compiled with Qt5. These variables are available:
# QSCINTILLA2_FOUND = Status of QScintilla
# QSCINTILLA2_INCLUDE_DIR = QScintilla include dir
# QSCINTILLA2_LIBRARY = QScintilla library

# Check
if(${Qt5Widgets_FOUND})
	
	# Set as not found
	set(QSCINTILLA2_FOUND false)
	
	# Iterate over the include list of the Qt5Widgets module
	set(CONTINUE true)
	foreach(TEMPPATH in ${Qt5Widgets_INCLUDE_DIRS})
		if(CONTINUE)
			
			# Check for a Qsci directory
			set(QSCIPATH ${TEMPPATH}/Qsci)
			find_path(QSCINTILLA2_INCLUDE_DIR qsciglobal.h ${QSCIPATH})
			
			# Found - break loop
			if(QSCINTILLA2_INCLUDE_DIR)
				set(CONTINUE false)
			endif()
			
		endif()
	endforeach()
	
	# Check
	if(QSCINTILLA2_INCLUDE_DIR)
		
		# Get Qt5Widgets library and cut off the library name
		get_target_property(QT5_WIDGETSLIBRARY Qt5::Widgets LOCATION)
		get_filename_component(QT5_WIDGETSLIBRARYPATH ${QT5_WIDGETSLIBRARY} PATH)

		# Add library
		set(QSCINTILLA_NAMES qt5scintilla2)
		find_library(QSCINTILLA2_LIBRARY NAMES ${QSCINTILLA_NAMES} PATHS QT5_WIDGETSLIBRARYPATH /usr/lib/)
		
		# Check
		if(QSCINTILLA2_LIBRARY)
			
			# Enable library
			set(QSCINTILLA2_FOUND true)
			mark_as_advanced(QSCINTILLA2_INCLUDE_DIR QSCINTILLA2_LIBRARY)
		else()
			message(FATAL_ERROR "QScintilla2 library not found")
		endif()
		
	else()
		message(FATAL_ERROR "Cannot find QScintilla2 header")
	endif()
	
else()
	message(FATAL_ERROR "Qt5Widgets module not found")
endif()