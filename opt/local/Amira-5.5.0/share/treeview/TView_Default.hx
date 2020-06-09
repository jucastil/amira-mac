# Amira Script

set hideNewModules 1
create HxDirectory {Settings}
Settings setIconPosition 388 100
Settings setTreeViewDirectory
Settings setSubDirectoriesAllowed 0
Settings fire
Settings setViewerMask 32767

set hideNewModules 1
create HxDirectoryData {Data}
Data setIconPosition 442 10
Data setTreeViewDirectory
Data fire
Data setViewerMask 32767

set hideNewModules 1
create HxDirectory {Display}
Display setIconPosition 431 40
Display setTreeViewDirectory
Display setSubDirectoriesAllowed 0
Display fire
Display setViewerMask 32767

set hideNewModules 1
create HxDirectory {Compute}
Compute setIconPosition 423 70
Compute setTreeViewDirectory
Compute setSubDirectoriesAllowed 0
Compute fire
Compute setViewerMask 32767

set hideNewModules 1
create HxDirectory {Animation-Demo-Scripts}
Animation-Demo-Scripts setIconPosition 388 100
Animation-Demo-Scripts setTreeViewDirectory
Animation-Demo-Scripts setSubDirectoriesAllowed 0
Animation-Demo-Scripts fire
Animation-Demo-Scripts setViewerMask 32767

set hideNewModules 1
create HxDirectoryColormaps {Colormaps}
Colormaps setIconPosition 416 130
Colormaps setTreeViewDirectory
Colormaps fire
Colormaps setViewerMask 32767
Colormaps select
