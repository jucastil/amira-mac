# Amira Script
remove -all
remove temperature.icol reg005.ctdata.am reg005.tetragrid.am reg005.thermvals.am OrthoSlice Colorwash

# Create viewers
viewer 0 show
viewer 0 setBackgroundMode 1
viewer 0 setTransparencyType 6
viewer 0 setAutoRedraw 0

mainWindow show

set hideNewModules 1
[ load ${AMIRA_ROOT}/data/colormaps/temperature.icol ] setLabel temperature.icol
temperature.icol setIconPosition 0 0
temperature.icol fire
{temperature.icol} setMinMax 40 43
{temperature.icol} flags setValue 0
{temperature.icol} shift setMinMax -1 1
{temperature.icol} shift setValue 0
{temperature.icol} scale setMinMax 0 1
{temperature.icol} scale setValue 1
temperature.icol fire
temperature.icol setViewerMask 32767

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/medical/reg005.ctdata.am ] setLabel reg005.ctdata.am
reg005.ctdata.am setIconPosition 20 10
reg005.ctdata.am fire
reg005.ctdata.am fire
reg005.ctdata.am setViewerMask 32767

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/medical/reg005.tetragrid.am ] setLabel reg005.tetragrid.am
reg005.tetragrid.am setIconPosition 20 40
reg005.tetragrid.am fire
reg005.tetragrid.am fire
reg005.tetragrid.am setViewerMask 32767

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/medical/reg005.thermvals.am ] setLabel reg005.thermvals.am
reg005.thermvals.am setIconPosition 20 70
reg005.thermvals.am grid connect reg005.tetragrid.am
reg005.thermvals.am fire
reg005.thermvals.am fire
reg005.thermvals.am setViewerMask 32767

set hideNewModules 0
create HxOrthoSlice {OrthoSlice}
OrthoSlice setIconPosition 278 10
OrthoSlice data connect reg005.ctdata.am
{OrthoSlice} fire
{OrthoSlice} sliceOrientation setValue 0
{OrthoSlice} fire
{OrthoSlice} options setValue 0 1
{OrthoSlice} options setValue 1 0
{OrthoSlice} options setValue 2 0
{OrthoSlice} mappingType setValue 0
{OrthoSlice} linearRange setMinMax 0 -1e+24 1e+24
{OrthoSlice} linearRange setValue 0 -200
{OrthoSlice} linearRange setMinMax 1 -1e+24 1e+24
{OrthoSlice} linearRange setValue 1 200
{OrthoSlice} contrastLimit setMinMax 0 -1e+24 1e+24
{OrthoSlice} contrastLimit setValue 0 7
{OrthoSlice} colormap setDefaultColor 1 0.8 0.5
{OrthoSlice} colormap setDefaultAlpha 1.000000
{OrthoSlice} sliceNumber setMinMax 0 58
{OrthoSlice} sliceNumber setValue 22
{OrthoSlice} transparency setValue 0
OrthoSlice setFrameWidth 0
OrthoSlice setFrameColor 1 0.5 0
OrthoSlice frame 1
OrthoSlice fire

OrthoSlice fire
OrthoSlice setViewerMask 32767

set hideNewModules 0
create HxColorwash {Colorwash}
Colorwash setIconPosition 278 30
Colorwash data connect reg005.thermvals.am
Colorwash module connect OrthoSlice
{Colorwash} colormap setDefaultColor 1 0.8 0.5
{Colorwash} colormap setDefaultAlpha 0.500000
Colorwash colormap connect temperature.icol
Colorwash fire
{Colorwash} mode setValue 0
{Colorwash} weightFactor setValue 0.5
{Colorwash} lenseWidth setValue 30
{Colorwash} overlayRange setValue 0 100
{Colorwash} overlayRange setValue 1 1000
Colorwash fire
Colorwash setViewerMask 32767
Colorwash select

set hideNewModules 0

viewer 0 setCameraPosition 24.3114 21.4016 -41.901
viewer 0 setCameraOrientation 1 0 0 3.14159
viewer 0 setCameraFocalDistance 64.901
viewer 0 setAutoRedraw 1
viewer 0 redraw
