project(
    'scop', #name
    ['cpp', 'c'], #language
    meson_version: '>=1.0.0',
    default_options : [ 'b_ndebug=if-release', 'buildtype=debug', 'cpp_std=c++14', 'default_library=static']
)

subdir('include')

subdir('src')
#src target set

subdir('tests')
#test target set

subdir('apps')