CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT (TENIS)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)

SET(COMMON_SRCS
    src/Mundo.cpp
    src/Esfera.cpp
    src/Plano.cpp
    src/Raqueta.cpp
    src/Vector2D.cpp
)

# Ejecutable principal del juego
ADD_EXECUTABLE(tenis src/tenis.cpp ${COMMON_SRCS})
TARGET_LINK_LIBRARIES(tenis glut GL GLU)

# Ejecutable para el bot (Práctica 3)
ADD_EXECUTABLE(bot src/bot.cpp ${COMMON_SRCS})

# En Linux, las funciones de memoria compartida POSIX (shm_open/mmap) pueden requerir la librería rt
if(UNIX AND NOT APPLE)
    TARGET_LINK_LIBRARIES(bot -lrt)
endif()
