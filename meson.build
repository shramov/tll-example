project('tll-example', 'cpp'
	, version: '0.0.0'
	, license: 'MIT'
	, default_options: ['cpp_std=c++2a', 'werror=true', 'optimization=2']
)

include = [include_directories('src')]

fmt = dependency('fmt')
tll = dependency('tll')

shared_library('tll-example'
	, ['src/module.cc']
	, include_directories : include
	, dependencies : [fmt, tll]
)

test('pytest', import('python').find_installation('python3', disabler: true)
	, args: ['-m', 'pytest', '-v', 'tests']
	, env: 'BUILD_DIR=@0@'.format(meson.current_build_dir())
	, workdir: meson.current_source_dir()
)
