# Copyright: (C) 2009 RobotCub Consortium
# Author: Paul Fitzpatrick
# CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT

IF (COMPILE_DEVICE_LIBRARY)
  yarp_prepare_device(nvidia TYPE NVIDIAGPU INCLUDE "NVIDIADeviceDriver.h")
  yarp_install(FILES nvidia.ini
               COMPONENT runtime
               DESTINATION ${YARP_PLUGIN_MANIFESTS_INSTALL_DIR})
ENDIF (COMPILE_DEVICE_LIBRARY)

IF (NOT SKIP_nvidia)

 FIND_PACKAGE(YARP REQUIRED)

 FIND_LIBRARY(lib_CgGL CgGL)
 FIND_LIBRARY(lib_pthread pthread)
 FIND_LIBRARY(lib_GL GL)
 FIND_LIBRARY(lib_glut glut)

 SET (OK FALSE)

 IF(lib_CgGL AND lib_pthread AND lib_GL AND lib_glut)
  SET (OK TRUE)
 ENDIF(lib_CgGL AND lib_pthread AND lib_GL AND lib_glut)

 IF (NOT WINDOWS)
  FIND_LIBRARY(lib_GLEW GLEW)
  IF (NOT lib_GLEW)
    SET (OK FALSE)
  ENDIF (NOT lib_GLEW)
 ENDIF (NOT WINDOWS)


 IF (OK)

  ADD_DEFINITIONS(-DGL_GLEXT_PROTOTYPES -DGLX_GLXEXT_PROTOTYPES)

  LINK_LIBRARIES(pthread GL glut CgGL)
  IF (NOT WINDOWS)
    LINK_LIBRARIES(GLEW)
  ENDIF (NOT WINDOWS)	

  YARP_ADD_PLUGIN(yarp_nvidia NVIDIADeviceDriver.cpp NVIDIADeviceDriver.h FBO_Filter.h)
  yarp_install(TARGETS yarp_nvidia
               EXPORT YARP
               COMPONENT runtime
               LIBRARY DESTINATION ${YARP_DYNAMIC_PLUGINS_INSTALL_DIR}
               ARCHIVE DESTINATION ${YARP_STATIC_PLUGINS_INSTALL_DIR})

 ELSE (OK)

  MESSAGE(FATAL_ERROR "could not find all libraries needed by nvidia driver")

 ENDIF (OK)

ENDIF (NOT SKIP_nvidia)
