cmake_minimum_required(VERSION 3.7.0)

project(GTK_LED_Control)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

# This one is important
SET(CMAKE_SYSTEM_NAME Linux)

set (CMAKE_C_FLAGS "-D_GNU_SOURCE -Wall -std=c99")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_BUILD_TYPE Debug)

if(DEFINED ARCH)
  if(${ARCH} STREQUAL "RASPBERRY")
    message("-- Created ${ARCH} compilation.")  
    # set (LIBS hardware interface)
    set (LIBS hardware)
    set (FOLDER "raspberry")  
  elseif(${ARCH} STREQUAL "PC")
    message("-- Created ${ARCH} compilation.") 
    # set (LIBS interface)
    set (FOLDER "pc")
  endif()
else()
  message(WARNING "")
  message("-- You must specify the ARCH variable")
  message("-- cmake -DARCH=PC  ..")
  message("-- or")
  message("-- cmake -DARCH=RASPBERRY  ..")
  message("")
  message(FATAL_ERROR "")
endif()


find_package(PkgConfig)
if (PKG_CONFIG_FOUND)
  pkg_check_modules(GTK "gtk+-3.0")
  if (GTK_FOUND)
    # add_library(view "")    
    add_executable(gtk_led "")    
    target_sources(gtk_led 
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/src/gtk_led.c
    ${CMAKE_CURRENT_LIST_DIR}/src/platform/${FOLDER}/led_process.c
    )
    target_include_directories(gtk_led PUBLIC  ${CMAKE_CURRENT_LIST_DIR}/include)
    target_link_libraries(gtk_led PUBLIC ${GTK_LIBRARIES} ${LIBS} -export-dynamic)
    add_definitions(${GTK_CFLAGS} ${GTK_CFLAGS_OTHER})
  endif()
endif()

install(TARGETS gtk_led DESTINATION bin)

file(COPY glade DESTINATION bin)

