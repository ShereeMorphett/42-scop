
gl_dep = dependency('gl', required: true)
sfml_dep = dependency('sfml', required: true)


subdir('glad')

executable('scop', 'main.cpp', 'Mesh.cpp', 'render.cpp', 'tools.cpp', 'Material.cpp', glad_src,
    dependencies: [gl_dep, sfml_dep],
    install: true)