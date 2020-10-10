
from building import *

cwd     = GetCurrentDir()

# init src and inc vars
src = []
inc = [cwd]

inc = inc + [cwd + "/lwgps/lwgps/src/include"]
inc = inc + [cwd + "/lwgps/lwgps/src/include/lwgps"]
src += Glob("lwgps/lwgps/src/lwgps/*.c")
src += Glob("*.c")

if GetDepend('LWGPS_USING_SAMPLES'):
    src    += Glob('lwgps/examples/*.c')

group = DefineGroup('lwgps', src, depend = ['PKG_USING_LWGPS'], CPPPATH = inc)

Return('group')
