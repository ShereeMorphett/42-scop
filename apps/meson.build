
glfw_dep = dependency('glfw3', required: true)
gl_dep = dependency('gl', required: true)

executable('scop', 'main.cpp', 'Mesh.cpp', 'render.cpp',
    dependencies: [glfw_dep, gl_dep],
    install: true)