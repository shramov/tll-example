schemegen = find_program('tll-schemegen', dirs: [tll.get_variable(pkgconfig: 'prefix') / 'python'])

scheme_src = ['binder.yaml']
scheme_headers = []
foreach f : scheme_src
  scheme_headers += [custom_target(
      f,
      output : '@BASENAME@.h',
      input : f,
      command : [schemegen, '--format=cpp-binder', '@INPUT@', '-o', '@OUTPUT@'],
  )]
endforeach
