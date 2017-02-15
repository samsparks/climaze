# TODO: Help
# TODO: pretty build
# TODO: doxy?
BaseEnv = Environment(CCFLAGS='-W -Wall -Wextra -Werror -Wno-unused-parameter -g -O3 -std=c++0x',
                      OBJPREFIX='.obj/' )

Export('BaseEnv')

SConscript(['climaze/SConscript',
            'libmaze/SConscript',
            'test/SConscript'])
