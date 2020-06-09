# Amira Script
remove -all
remove volrenRed.col beeBrain.lda OrthoSlice OrthoSlice2 OrthoSlice3

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

set hideNewModules 1
[ load ${AMIRA_ROOT}/data/colormaps/volrenRed.col ] setLabel volrenRed.col
volrenRed.col setIconPosition 0 0
volrenRed.col fire
{volrenRed.col} setMinMax 0 255
volrenRed.col flags setValue 1
volrenRed.col shift setMinMax -1 1
volrenRed.col shift setButtons 0
volrenRed.col shift setIncrement 0.133333
volrenRed.col shift setValue 0
volrenRed.col shift setSubMinMax -1 1
volrenRed.col scale setMinMax 0 1
volrenRed.col scale setButtons 0
volrenRed.col scale setIncrement 0.1
volrenRed.col scale setValue 1
volrenRed.col scale setSubMinMax 0 1
volrenRed.col fire
volrenRed.col setViewerMask 16383

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/lda/beeBrain.lda ] setLabel beeBrain.lda
beeBrain.lda setIconPosition 19 10
beeBrain.lda fire
beeBrain.lda fire
beeBrain.lda setViewerMask 16383

set hideNewModules 0
create HxOrthoSliceLDM {OrthoSlice}
OrthoSlice setIconPosition 204 91
OrthoSlice data connect beeBrain.lda
OrthoSlice colormap setDefaultColor 1 0.8 0.5
OrthoSlice colormap setDefaultAlpha 0.500000
OrthoSlice colormap connect volrenRed.col
OrthoSlice fire
OrthoSlice sliceOrientation setValue 0
OrthoSlice options setValue 0 0
OrthoSlice options setValue 1 0
OrthoSlice options setValue 2 1
OrthoSlice options setValue 3 0
OrthoSlice interpolation setValue 1
OrthoSlice mappingType setValue 0 1
OrthoSlice range setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
OrthoSlice range setValue 0 0
OrthoSlice range setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
OrthoSlice range setValue 1 255
OrthoSlice sliceNumber setMinMax 0 80
OrthoSlice sliceNumber setButtons 1
OrthoSlice sliceNumber setIncrement 1
OrthoSlice sliceNumber setValue 35
OrthoSlice sliceNumber setSubMinMax 0 80
OrthoSlice transparency setValue 1
OrthoSlice embossing setValue 0 1
OrthoSlice embossingFactor setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
OrthoSlice embossingFactor setValue 0 4
OrthoSlice fire
OrthoSlice setViewerMask 16383
OrthoSlice select

set hideNewModules 0
create HxOrthoSliceLDM {OrthoSlice2}
OrthoSlice2 setIconPosition 205 12
OrthoSlice2 data connect beeBrain.lda
OrthoSlice2 colormap setDefaultColor 1 0.8 0.5
OrthoSlice2 colormap setDefaultAlpha 0.500000
OrthoSlice2 colormap connect volrenRed.col
OrthoSlice2 fire
OrthoSlice2 sliceOrientation setValue 2
OrthoSlice2 options setValue 0 0
OrthoSlice2 options setValue 1 0
OrthoSlice2 options setValue 2 1
OrthoSlice2 options setValue 3 0
OrthoSlice2 interpolation setValue 1
OrthoSlice2 mappingType setValue 0 1
OrthoSlice2 range setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
OrthoSlice2 range setValue 0 0
OrthoSlice2 range setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
OrthoSlice2 range setValue 1 255
OrthoSlice2 sliceNumber setMinMax 0 291
OrthoSlice2 sliceNumber setButtons 1
OrthoSlice2 sliceNumber setIncrement 1
OrthoSlice2 sliceNumber setValue 56
OrthoSlice2 sliceNumber setSubMinMax 0 291
OrthoSlice2 transparency setValue 1
OrthoSlice2 embossing setValue 0 1
OrthoSlice2 embossingFactor setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
OrthoSlice2 embossingFactor setValue 0 4
OrthoSlice2 fire
OrthoSlice2 setViewerMask 16382
OrthoSlice2 select

set hideNewModules 0
create HxOrthoSliceLDM {OrthoSlice3}
OrthoSlice3 setIconPosition 206 47
OrthoSlice3 data connect beeBrain.lda
OrthoSlice3 colormap setDefaultColor 1 0.8 0.5
OrthoSlice3 colormap setDefaultAlpha 0.500000
OrthoSlice3 colormap connect volrenRed.col
OrthoSlice3 fire
OrthoSlice3 sliceOrientation setValue 1
OrthoSlice3 options setValue 0 0
OrthoSlice3 options setValue 1 0
OrthoSlice3 options setValue 2 1
OrthoSlice3 options setValue 3 0
OrthoSlice3 interpolation setValue 1
OrthoSlice3 mappingType setValue 0 1
OrthoSlice3 range setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
OrthoSlice3 range setValue 0 0
OrthoSlice3 range setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
OrthoSlice3 range setValue 1 255
OrthoSlice3 sliceNumber setMinMax 0 193
OrthoSlice3 sliceNumber setButtons 1
OrthoSlice3 sliceNumber setIncrement 1
OrthoSlice3 sliceNumber setValue 51
OrthoSlice3 sliceNumber setSubMinMax 0 193
OrthoSlice3 transparency setValue 1
OrthoSlice3 embossing setValue 0 1
OrthoSlice3 embossingFactor setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
OrthoSlice3 embossingFactor setValue 0 4
OrthoSlice3 fire
OrthoSlice3 setViewerMask 16382
OrthoSlice3 select

set hideNewModules 0


viewer 0 setCameraPosition 1456.06 968.22 -3392.25
viewer 0 setCameraOrientation 1 0 0 3.14159
viewer 0 setCameraFocalDistance 3742.56
viewer 0 setAutoRedraw 1
viewer 0 redraw
