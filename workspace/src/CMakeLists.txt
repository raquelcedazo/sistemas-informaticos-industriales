INCLUDE_DIRECTORIES("${PROJECT_INCLUDE_DIR}")

SET(COMMON_SRCS 
	Esfera.cpp
	Plano.cpp
	Raqueta.cpp
	Vector2D.cpp
	)
				
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ..)

# 1. Ejecutable del SERVIDOR (con pthread)
ADD_EXECUTABLE(servidor servidor.cpp MundoServidor.cpp ${COMMON_SRCS})
TARGET_LINK_LIBRARIES(servidor glut GL GLU pthread)

# 2. Ejecutable del CLIENTE
ADD_EXECUTABLE(cliente cliente.cpp MundoCliente.cpp ${COMMON_SRCS})
TARGET_LINK_LIBRARIES(cliente glut GL GLU)

# 3. Ejecutable del logger (FIFO)
add_executable(logger logger.cpp)

# 4. Ejecutable del bot autónomo (mmap)
add_executable(bot bot.cpp ${COMMON_SRCS})
TARGET_LINK_LIBRARIES(bot glut GL GLU)
