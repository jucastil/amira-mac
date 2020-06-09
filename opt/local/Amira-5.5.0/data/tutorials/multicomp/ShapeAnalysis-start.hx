# Amira Script
remove -all
remove grey.am cellbodies.am cellbodies.labeledRegions.am labelcolors.am OrthoSlice Colorwash

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
[ load ${AMIRA_ROOT}/data/colormaps/grey.am ] setLabel grey.am
grey.am setIconPosition 0 0
grey.am setNoRemoveAll 1
grey.am fire
{grey.am} setMinMax 0 255
grey.am flags setValue 1
grey.am shift setMinMax -1 1
grey.am shift setButtons 0
grey.am shift setIncrement 0.133333
grey.am shift setValue 0
grey.am shift setSubMinMax -1 1
grey.am scale setMinMax 0 1
grey.am scale setButtons 0
grey.am scale setIncrement 0.1
grey.am scale setValue 1
grey.am scale setSubMinMax 0 1
grey.am fire
grey.am setViewerMask 16383

set hideNewModules 0
[ load ${SCRIPTDIR}/cellbodies.am ] setLabel cellbodies.am
cellbodies.am setIconPosition 20 10
cellbodies.am fire
cellbodies.am setViewerMask 16383

set hideNewModules 0
[ load ${SCRIPTDIR}/cellbodies.labeledRegions.am ] setLabel cellbodies.labeledRegions.am
cellbodies.labeledRegions.am setIconPosition 20 40
cellbodies.labeledRegions.am fire
cellbodies.labeledRegions.am primary setIndex 0 0
cellbodies.labeledRegions.am fire
cellbodies.labeledRegions.am setViewerMask 16383

set hideNewModules 1
[ load ${AMIRA_ROOT}/data/colormaps/labelcolors.am ] setLabel labelcolors.am
labelcolors.am setIconPosition 21 70
labelcolors.am fire
{labelcolors.am} setMinMax 1 255
labelcolors.am flags setValue 1
labelcolors.am shift setMinMax -1 1
labelcolors.am shift setButtons 0
labelcolors.am shift setIncrement 0.133333
labelcolors.am shift setValue 0
labelcolors.am shift setSubMinMax -1 1
labelcolors.am scale setMinMax 0 1
labelcolors.am scale setButtons 0
labelcolors.am scale setIncrement 0.1
labelcolors.am scale setValue 1
labelcolors.am scale setSubMinMax 0 1
labelcolors.am fire
labelcolors.am setViewerMask 16383

set hideNewModules 0
create HxOrthoSlice {OrthoSlice}
OrthoSlice setIconPosition 282 10
OrthoSlice data connect cellbodies.am
{OrthoSlice} fire
OrthoSlice sliceOrientation setValue 0
{OrthoSlice} fire
OrthoSlice origin  setBoundingBox -1e+008 1e+008 -1e+008 1e+008 -1e+008 1e+008
OrthoSlice origin  setImmediate 0
OrthoSlice origin  setOrtho 0
OrthoSlice origin  showDragger 0
OrthoSlice origin  showPoints 0
OrthoSlice origin  setPointScale 1
OrthoSlice origin  showOptionButton 1
OrthoSlice origin  setNumPoints 1 1 1
OrthoSlice origin  setValue 0 207.323 183.126 32.9332
OrthoSlice normal  setBoundingBox -1e+008 1e+008 -1e+008 1e+008 -1e+008 1e+008
OrthoSlice normal  setImmediate 0
OrthoSlice normal  setOrtho 0
OrthoSlice normal  showDragger 0
OrthoSlice normal  showPoints 0
OrthoSlice normal  setPointScale 1
OrthoSlice normal  showOptionButton 1
OrthoSlice normal  setNumPoints 1 1 1
OrthoSlice normal  setValue 0 0 0 1
OrthoSlice options setValue 0 1
OrthoSlice options setToggleVisible 0 1
OrthoSlice options setValue 1 0
OrthoSlice options setToggleVisible 1 1
OrthoSlice options setValue 2 0
OrthoSlice options setToggleVisible 2 1
OrthoSlice mapping setIndex 0 1
OrthoSlice contrastLimit setMinMax 0 -2147483648 2147483648
OrthoSlice contrastLimit setValue 0 7
OrthoSlice colormap setDefaultColor 1 0.8 0.5
OrthoSlice colormap setDefaultAlpha 1.000000
OrthoSlice colormap setLocalRange 1
OrthoSlice colormap setLocalMinMax 0.000000 255.000000
OrthoSlice colormap connect grey.am
OrthoSlice sliceNumber setMinMax 0 107
OrthoSlice sliceNumber setButtons 1
OrthoSlice sliceNumber setIncrement 1
OrthoSlice sliceNumber setValue 54
OrthoSlice sliceNumber setSubMinMax 0 107
OrthoSlice transparency setValue 0
OrthoSlice frameSettings setState item 0 1 item 2 1 color 3 1 0.5 0 
OrthoSlice fire

OrthoSlice fire
OrthoSlice setViewerMask 16383
OrthoSlice setShadowStyle 0
OrthoSlice setPickable 1

set hideNewModules 0
create HxColorwash {Colorwash}
Colorwash setIconPosition 282 30
Colorwash data connect cellbodies.labeledRegions.am
Colorwash module connect OrthoSlice
Colorwash colormap setDefaultColor 1 0.8 0.5
Colorwash colormap setDefaultAlpha 0.500000
Colorwash colormap setLocalRange 0
Colorwash colormap connect labelcolors.am
Colorwash fire
Colorwash mode setIndex 0 2
Colorwash weightFactor setMinMax 0 1
Colorwash weightFactor setButtons 0
Colorwash weightFactor setIncrement 0.1
Colorwash weightFactor setValue 0.5
Colorwash weightFactor setSubMinMax 0 1
Colorwash lenseWidth setMinMax 5 80
Colorwash lenseWidth setButtons 1
Colorwash lenseWidth setIncrement 1
Colorwash lenseWidth setValue 30
Colorwash lenseWidth setSubMinMax 5 80
Colorwash overlayRange setMinMax 0 -3.40282346638529e+038 3.40282346638529e+038
Colorwash overlayRange setValue 0 100
Colorwash overlayRange setMinMax 1 -3.40282346638529e+038 3.40282346638529e+038
Colorwash overlayRange setValue 1 1000
Colorwash alpha setMinMax 0 1
Colorwash alpha setButtons 0
Colorwash alpha setIncrement 0.1
Colorwash alpha setValue 0.3
Colorwash alpha setSubMinMax 0 1
Colorwash options setValue 0 0
Colorwash options setToggleVisible 0 1
Colorwash options setValue 1 1
Colorwash options setToggleVisible 1 1
Colorwash fire
Colorwash setViewerMask 16383
Colorwash setPickable 1

set hideNewModules 0


viewer 0 setCameraOrientation 1 0 0 3.14159
viewer 0 setCameraPosition 207.323 183.126 -230.719
viewer 0 setCameraFocalDistance 263.652
viewer 0 setCameraNearDistance 263.388
viewer 0 setCameraFarDistance 263.916
viewer 0 setCameraType perspective
viewer 0 setCameraHeightAngle 44.9023
viewer 0 setAutoRedraw 1
viewer 0 redraw

