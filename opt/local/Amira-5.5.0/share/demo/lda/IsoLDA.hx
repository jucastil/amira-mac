# Amira Script
remove -all
remove beeBrain.lda Isosurface

# Create viewers
viewer setVertical 0

viewer 0 setBackgroundMode 1
viewer 0 setBackgroundColor 0.06 0.13 0.24
viewer 0 setBackgroundColor2 0.72 0.72 0.78
viewer 0 setTransparencyType 5
viewer 0 setAutoRedraw 0
viewer 0 setCameraType 1
viewer 0 show
mainWindow show

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/lda/beeBrain.lda ] setLabel beeBrain.lda
beeBrain.lda setIconPosition 19 45
beeBrain.lda fire
beeBrain.lda fire
beeBrain.lda setViewerMask 16383

set hideNewModules 0
create HxIsosurfaceRender {Isosurface}
Isosurface setIconPosition 304 56
Isosurface data connect beeBrain.lda
Isosurface colormap setDefaultColor 1 0.8 0.5
Isosurface colormap setDefaultAlpha 1.000000
Isosurface fire
Isosurface slices setMinMax 1 81
Isosurface slices setButtons 1
Isosurface slices setIncrement 1
Isosurface slices setValue 81
Isosurface slices setSubMinMax 1 81
Isosurface threshold setMinMax 0 255
Isosurface threshold setButtons 0
Isosurface threshold setIncrement 17
Isosurface threshold setValue 127.5
Isosurface threshold setSubMinMax 0 255
Isosurface fire
Isosurface setViewerMask 16383
Isosurface select

set hideNewModules 0


viewer 0 setCameraPosition 1456.06 968.22 -3934.69
viewer 0 setCameraOrientation 1 0 0 3.14159
viewer 0 setCameraFocalDistance 4334.69
viewer 0 setAutoRedraw 1
viewer 0 redraw
