# Install script for directory: C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/out/install/x64-Debug")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/out/build/x64-Debug/src/libwebpdecoder.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/out/build/x64-Debug/src/libwebp.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/out/build/x64-Debug/src/demux/libwebpdemux.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/out/build/x64-Debug/dwebp.exe")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/out/build/x64-Debug/cwebp.exe")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/out/build/x64-Debug/src/mux/libwebpmux.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/out/build/x64-Debug/img2webp.exe")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/out/build/x64-Debug/webpinfo.exe")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/out/build/x64-Debug/webpmux.exe")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/out/build/x64-Debug/get_disto.exe")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/out/build/x64-Debug/webp_quality.exe")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/out/build/x64-Debug/webpdecoder.lib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/webp" TYPE FILE FILES
    "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/src/webp/decode.h"
    "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/src/webp/types.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/out/build/x64-Debug/webp.lib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/webp" TYPE FILE FILES
    "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/src/webp/decode.h"
    "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/src/webp/encode.h"
    "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/src/webp/types.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/out/build/x64-Debug/webpdemux.lib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/webp" TYPE FILE FILES
    "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/src/webp/decode.h"
    "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/src/webp/demux.h"
    "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/src/webp/mux_types.h"
    "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/src/webp/types.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/out/build/x64-Debug/webpmux.lib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/webp" TYPE FILE FILES
    "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/src/webp/mux.h"
    "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/src/webp/mux_types.h"
    "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/src/webp/types.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/WebP/cmake/WebPTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/WebP/cmake/WebPTargets.cmake"
         "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/out/build/x64-Debug/CMakeFiles/Export/share/WebP/cmake/WebPTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/WebP/cmake/WebPTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/WebP/cmake/WebPTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/WebP/cmake" TYPE FILE FILES "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/out/build/x64-Debug/CMakeFiles/Export/share/WebP/cmake/WebPTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/WebP/cmake" TYPE FILE FILES "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/out/build/x64-Debug/CMakeFiles/Export/share/WebP/cmake/WebPTargets-debug.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/WebP/cmake" TYPE FILE FILES
    "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/out/build/x64-Debug/WebPConfigVersion.cmake"
    "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/out/build/x64-Debug/WebPConfig.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdocx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man1" TYPE FILE FILES "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/man/cwebp.1")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdocx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man1" TYPE FILE FILES "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/man/dwebp.1")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdocx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man1" TYPE FILE FILES "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/man/img2webp.1")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdocx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man1" TYPE FILE FILES "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/man/vwebp.1")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdocx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man1" TYPE FILE FILES "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/man/webpmux.1")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdocx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man1" TYPE FILE FILES "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/man/webpinfo.1")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/home/dev/ProgramPraktyki/android/app/jni/SDL_image/external/libwebp-1.0.2/out/build/x64-Debug/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
