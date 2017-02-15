# TODO: Help
# TODO: pretty build
# TODO: doxy?
BaseEnv = Environment(CCFLAGS='-W -Wall -Wextra -Werror -Wno-unused-parameter -g -O3 -std=c++0x',
                      OBJPREFIX='.obj/' )

Export('BaseEnv')

SConscript(['climaze/SConscript',
            'libmaze/SConscript',
            'test/SConscript'])

Help("""
Usage: 'scons [options] [args] targets...'

Targets:
  test_runner  builds the unit test runner

Options:
  -c           cleans the specified target
               
Args:          
  test         runs the full unit test suite
    
""")

