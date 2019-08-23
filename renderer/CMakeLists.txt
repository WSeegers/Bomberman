
add_library(Renderer STATIC
	src/Renderer.cpp
	src/Camera.cpp
	src/Model.cpp
	src/Shader.cpp
	src/Mesh.cpp
)

if (APPLE)
	target_link_libraries(Renderer "-framework OpenGL")
endif()