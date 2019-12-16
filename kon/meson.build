kon_sources = [
    'src/konstyleplugin.cpp',
    'src/konstyle.cpp',
    'src/konutil.cpp',
    
    'src/widgets/konbutton.cpp',
]

kon_moc_headers = [
    'include/konstyle.h',
    'include/konstyleplugin.h',
]

kon_cpp_args = [
    '-DQT_PLUGIN',
]

kon_include = include_directories('include')

kon_moc_files = qt5.preprocess(moc_headers: kon_moc_headers,
                               include_directories: kon_include,
                               dependencies: kon_deps)

kon_lib = shared_library('kon',
                         kon_sources,
                         kon_moc_files,
                         cpp_args: kon_cpp_args,
                         include_directories: kon_include,
                         dependencies: kon_deps,
                         install: true,
                         install_dir: join_paths(get_option('libdir'), 'qt5', 'plugins', 'styles'))