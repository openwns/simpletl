libname = 'simpletl'
srcFiles = [
    'src/SimpleTL.cpp',
    'src/Routing.cpp',
    'src/Medium.cpp',
    'src/PDU.cpp',
    'src/PCI.cpp',
    'src/events/ConInd.cpp',
    'src/events/DataInd.cpp',
    'src/events/DisconInd.cpp',
    'src/node/component/Component.cpp',
    'src/service/Connection.cpp',
    'src/service/TCP.cpp',
    'src/service/UDP.cpp'
    ]
hppFiles = [
    'src/Medium.hpp',
    'src/PCI.hpp',
    'src/PDU.hpp',
    'src/Routing.hpp',
    'src/SimpleTL.hpp',
    'src/events/ConInd.hpp',
    'src/events/DataInd.hpp',
    'src/events/DisconInd.hpp',
    'src/node/component/Component.hpp',
    'src/service/Connection.hpp',
    'src/service/TCP.hpp',
    'src/service/UDP.hpp'
]
pyconfigs = [
'simpleTL/Channel.py',
'simpleTL/Component.py',
'simpleTL/SimpleTL.py',
'simpleTL/__init__.py'
]
dependencies = []
Return('libname srcFiles hppFiles pyconfigs dependencies')
