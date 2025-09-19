project('tll-example', 'cpp'
	, version: '0.0.0'
	, license: 'MIT'
	, default_options: ['cpp_std=c++2a', 'werror=true', 'optimization=2']
)

include = [include_directories('src')]

fmt = dependency('fmt')
tll = dependency('tll')
gtkmm = dependency('gtkmm-3.0', required: false, disabler: true)

shared_library('tll-example'
	, ['src/module.cc', 'src/logic.cc']
	, include_directories : include
	, dependencies : [fmt, tll]
)

executable('gtk-example', ['src/gtk.cc'], dependencies : [gtkmm, fmt, tll])

subdir('scheme') # scheme_headers defined here

executable('binder', ['src/binder.cc'] + scheme_headers, dependencies : [fmt, tll])

test('pytest', import('python').find_installation('python3', disabler: true)
	, args: ['-m', 'pytest', '-v', 'tests']
	, env: 'BUILD_DIR=@0@'.format(meson.current_build_dir())
	, workdir: meson.current_source_dir()
)
