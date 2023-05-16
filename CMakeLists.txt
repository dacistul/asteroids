cmake_minimum_required(VERSION 3.0)

project(stefan-gl)

add_executable(stefan-gl main.cpp shader.cpp collisions.cpp asteroid.cpp projectile.cpp ship.cpp physics_object.cpp rendered_object.cpp)
find_package(OpenGL REQUIRED)
configure_file(fragment.glsl fragment.glsl)

configure_file(vertex.glsl vertex.glsl)
target_include_directories(stefan-gl PUBLIC "C:\\UPB - FILS\\First Semester\\Advanced Computer Graphics\\Proiect\\dependente")
target_link_libraries(stefan-gl "C:\\UPB - FILS\\First Semester\\Advanced Computer Graphics\\Proiect\\dependente\\glew\\glew32.lib" "C:\\UPB - FILS\\First Semester\\Advanced Computer Graphics\\Proiect\\dependente\\glfw\\glfw3dll.lib" OpenGL::GL)
install(TARGETS stefan-gl RUNTIME DESTINATION bin)
set_property(TARGET stefan-gl PROPERTY CXX_STANDARD 17)
