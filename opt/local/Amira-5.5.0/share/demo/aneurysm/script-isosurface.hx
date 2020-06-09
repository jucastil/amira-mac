# Amira Script
remove -all
remove glow.col aneurism.ctdata BoundingBox OrthoSlice Isosurface

# Create viewers
viewer setVertical 0

viewer 0 setBackgroundMode 1
viewer 0 setBackgroundColor 0.06 0.13 0.24
viewer 0 setBackgroundColor2 0.72 0.72 0.78
viewer 0 setTransparencyType 5
viewer 0 setAutoRedraw 0
viewer 0 show
mainWindow show

set hideNewModules 1
[ load ${AMIRA_ROOT}/data/colormaps/glow.col ] setLabel glow.col
glow.col setIconPosition 0 0
glow.col setNoRemoveAll 1
glow.col fire
{glow.col} setMinMax 0 255
glow.col flags setValue 0
glow.col shift setMinMax -1 1
glow.col shift setButtons 0
glow.col shift setIncrement 0.133333
glow.col shift setValue 0
glow.col shift setSubMinMax -1 1
glow.col scale setMinMax 0 1
glow.col scale setButtons 0
glow.col scale setIncrement 0.1
glow.col scale setValue 1
glow.col scale setSubMinMax 0 1
glow.col fire
glow.col setViewerMask 65535

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/aneurysm/aneurism.ctdata ] setLabel aneurism.ctdata
aneurism.ctdata setIconPosition 20 10
aneurism.ctdata fire
aneurism.ctdata fire
aneurism.ctdata setViewerMask 65535

set hideNewModules 0
create HxBoundingBox {BoundingBox}
BoundingBox setIconPosition 322 10
{BoundingBox} setLineWidth 0
{BoundingBox} setColor 1 0.5 0
BoundingBox data connect aneurism.ctdata
BoundingBox fire
BoundingBox text setValue 0 0
BoundingBox fire
BoundingBox setViewerMask 65535
BoundingBox setShadowStyle 0

set hideNewModules 0
create HxOrthoSlice {OrthoSlice}
OrthoSlice setIconPosition 336 38
OrthoSlice data connect aneurism.ctdata
{OrthoSlice} fire
OrthoSlice sliceOrientation setValue 0
{OrthoSlice} fire
OrthoSlice options setValue 0 1
OrthoSlice options setValue 1 0
OrthoSlice options setValue 2 0
OrthoSlice mappingType setIndex 0 0
OrthoSlice linearRange setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
OrthoSlice linearRange setValue 0 -200
OrthoSlice linearRange setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
OrthoSlice linearRange setValue 1 200
OrthoSlice contrastLimit setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
OrthoSlice contrastLimit setValue 0 7
OrthoSlice colormap setDefaultColor 1 0.8 0.5
OrthoSlice colormap setDefaultAlpha 1.000000
OrthoSlice colormap connect glow.col
OrthoSlice sliceNumber setMinMax 0 40
OrthoSlice sliceNumber setButtons 1
OrthoSlice sliceNumber setIncrement 1
OrthoSlice sliceNumber setValue 0
OrthoSlice sliceNumber setSubMinMax 0 40
OrthoSlice transparency setValue 0
OrthoSlice setFrameWidth 0
OrthoSlice setFrameColor 1 0.5 0
OrthoSlice frame 1
OrthoSlice fire

OrthoSlice fire
OrthoSlice setViewerMask 65535
OrthoSlice setShadowStyle 0

set hideNewModules 0
create HxIsosurface {Isosurface}
Isosurface setIconPosition 336 66
Isosurface data connect aneurism.ctdata
Isosurface colormap setDefaultColor 1 0.8 0.4
Isosurface colormap setDefaultAlpha 0.500000
Isosurface fire
Isosurface drawStyle setValue 1
Isosurface fire
Isosurface drawStyle setSpecularLighting 1
Isosurface drawStyle setTexture 0
Isosurface drawStyle setAlphaMode 1
Isosurface drawStyle setNormalBinding 1
Isosurface drawStyle setCullingMode 0
Isosurface drawStyle setSortingMode 1
Isosurface textureWrap setIndex 0 1
Isosurface threshold setMinMax -1000 2117
Isosurface threshold setButtons 0
Isosurface threshold setIncrement 207.8
Isosurface threshold setValue -200
Isosurface threshold setSubMinMax -1000 2117
Isosurface options setValue 0 1
Isosurface options setValue 1 1
Isosurface resolution setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
Isosurface resolution setValue 0 4
Isosurface resolution setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
Isosurface resolution setValue 1 4
Isosurface resolution setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
Isosurface resolution setValue 2 1
Isosurface numberOfCores setMinMax 1 10
Isosurface numberOfCores setButtons 1
Isosurface numberOfCores setIncrement 1
Isosurface numberOfCores setValue 2
Isosurface numberOfCores setSubMinMax 1 10
{Isosurface} doIt hit
Isosurface fire
Isosurface setViewerMask 65535
Isosurface setShadowStyle 0

set hideNewModules 0


viewer 0 setCameraOrientation -0.802983 0.278561 0.526898 5.00681
viewer 0 setCameraPosition -19.8335 -22.3713 41.2096
viewer 0 setCameraFocalDistance 35.0652
viewer 0 setCameraNearDistance 19.8237
viewer 0 setCameraFarDistance 46.4519
viewer 0 setCameraType perspective
viewer 0 setCameraHeightAngle 44.9023
viewer 0 setAutoRedraw 1
viewer 0 redraw
