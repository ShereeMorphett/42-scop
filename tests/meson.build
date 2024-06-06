

test_dependencies = [ ft_dep]
test_dependencies += subproject('catch2').get_variable('catch2_with_main_dep')

test_args = []


test_link_args = []

test_overrides = [ 'warning_level=3']

test_source_files = []
test_source_files += files('math.cpp') # is a magic thing that checks if files in array exist, returns an array

test_exe = executable(
    meson.project_name() + '_tests',
    test_source_files,
    cpp_args: test_args,
    link_args: test_link_args,
    dependencies: test_dependencies,
    override_options: test_overrides,
)


test(meson.project_name() + '_tests', test_exe)