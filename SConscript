
from building import *

cwd     = GetCurrentDir()

# init src and inc vars
src = []
inc = [cwd]

inc = inc + [cwd + "/lwgps/lwgps/src/include"]
src = src + ["/lwgps/lwgps/src/lwgps/lwgps.c"]

group = DefineGroup('lwgps', src, depend = ['PKG_USING_LWGPS'], CPPPATH = inc)

Return('group')
