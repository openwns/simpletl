import os
import CNBuildSupport
from CNBuildSupport import CNBSEnvironment
import wnsbase.RCS as RCS

commonEnv = CNBSEnvironment(PROJNAME       = 'simpletl',
                            PROJMODULES    = ['simpletl'],
                            AUTODEPS       = [],
                            DEFAULTVERSION = True,
                            LIBRARY        = True,
                            SHORTCUTS      = True,
			    REVISIONCONTROL = RCS.Bazaar('../', 'SimpleTL', 'main', '1.0'),
                            )

Return('commonEnv')

