
glfw_dep = dependency('glfw3', required: true)
gl_dep = dependency('gl', required: true)
glew_dep = dependency('glew', required: true)

executable('scop', 'main.cpp', 'Mesh.cpp', 'render.cpp', 'tools.cpp', 'Material.cpp',
    dependencies: [glfw_dep, gl_dep, glew_dep],
    install: true)