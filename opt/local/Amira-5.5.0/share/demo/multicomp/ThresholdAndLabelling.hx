# Amira Script
remove -all
remove grey.am cellbodies.am cellbodies.labels.am labelcolors.am cellbodies.labels.DistField.am Result Result.Regions LocalThreshold OrthoSlice DistanceMap Arithmetic WatershedSegmentation Colorwash

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
[ load ${AMIRA_ROOT}/data/tutorials/multicomp/cellbodies.am ] setLabel cellbodies.am
cellbodies.am setIconPosition 20 10
cellbodies.am fire
cellbodies.am setViewerMask 16383

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/tutorials/multicomp/cellbodies.labels.am ] setLabel cellbodies.labels.am
cellbodies.labels.am setIconPosition 20 30
cellbodies.labels.am ImageData connect cellbodies.am
cellbodies.labels.am fire
cellbodies.labels.am primary setIndex 0 0
cellbodies.labels.am fire
cellbodies.labels.am setViewerMask 16383

set hideNewModules 1
[ load ${AMIRA_ROOT}/data/colormaps/labelcolors.am ] setLabel labelcolors.am
labelcolors.am setIconPosition 129 15
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
create HxLocalThreshold {LocalThreshold}
LocalThreshold setIconPosition 160 60
LocalThreshold data connect cellbodies.am
LocalThreshold fire
LocalThreshold Algorithm setIndex 0 3
LocalThreshold Export setValue 0 0
LocalThreshold Export setToggleVisible 0 1
LocalThreshold Export setValue 1 0
LocalThreshold Export setToggleVisible 1 1
LocalThreshold ObjectSize setMinMax 0 1 256
LocalThreshold ObjectSize setValue 0 51
LocalThreshold ObjectSize setMinMax 1 1 256
LocalThreshold ObjectSize setValue 1 51
LocalThreshold ObjectSize setMinMax 2 1 108
LocalThreshold ObjectSize setValue 2 21
LocalThreshold Lambda setMinMax -1 1
LocalThreshold Lambda setButtons 0
LocalThreshold Lambda setIncrement 0.133333
LocalThreshold Lambda setValue -0.2
LocalThreshold Lambda setSubMinMax -1 1
LocalThreshold Normalization setMinMax 0 0 255
LocalThreshold Normalization setValue 0 127.5
LocalThreshold SeedThreshold setMinMax 0 255
LocalThreshold SeedThreshold setButtons 0
LocalThreshold SeedThreshold setIncrement 17
LocalThreshold SeedThreshold setValue 112
LocalThreshold SeedThreshold setSubMinMax 0 255
LocalThreshold LowThreshold setMinMax 0 255
LocalThreshold LowThreshold setButtons 0
LocalThreshold LowThreshold setIncrement 17
LocalThreshold LowThreshold setValue 70
LocalThreshold LowThreshold setSubMinMax 0 255
LocalThreshold fire
LocalThreshold setViewerMask 16383
LocalThreshold setPickable 1

set hideNewModules 0
create HxOrthoSlice {OrthoSlice}
OrthoSlice setIconPosition 373 10
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
OrthoSlice origin  setValue 0 207.323 183.126 35.3727
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
OrthoSlice sliceNumber setValue 58
OrthoSlice sliceNumber setSubMinMax 0 107
OrthoSlice transparency setValue 0
OrthoSlice frameSettings setState item 0 1 item 2 1 color 3 1 0.5 0 
OrthoSlice fire

OrthoSlice fire
OrthoSlice setViewerMask 16383
OrthoSlice select
OrthoSlice sliceNumber setPin 1
OrthoSlice deselect
OrthoSlice setShadowStyle 0
OrthoSlice setPickable 1

set hideNewModules 0
create HxComputeDistanceMap {DistanceMap}
DistanceMap setIconPosition 160 90
DistanceMap data connect cellbodies.labels.am
DistanceMap fire
DistanceMap type setValue 1
DistanceMap chamferMetric setValue 2
DistanceMap region setIndex 0 0
DistanceMap seed  setBoundingBox 113.835 300.811 89.6384 276.614 -1.3294e-005 65.2566
DistanceMap seed  setImmediate 0
DistanceMap seed  setOrtho 0
DistanceMap seed  showDragger 0
DistanceMap seed  showPoints 0
DistanceMap seed  setPointScale 1
DistanceMap seed  showOptionButton 1
DistanceMap seed  setNumPoints 1 -1 -1
DistanceMap seed  setValue 0 113.835 89.6384 0
DistanceMap fire
DistanceMap setViewerMask 16383
DistanceMap setPickable 1

set hideNewModules 0
[ {DistanceMap} create 0 ] setLabel {cellbodies.labels.DistField.am}
cellbodies.labels.DistField.am setIconPosition 20 120
cellbodies.labels.DistField.am master connect DistanceMap 0
cellbodies.labels.DistField.am fire
cellbodies.labels.DistField.am setViewerMask 16383

set hideNewModules 0
create HxArithmetic {Arithmetic}
Arithmetic setIconPosition 160 150
Arithmetic inputA connect cellbodies.labels.DistField.am
Arithmetic fire
Arithmetic resultChannels setIndex 0 0
Arithmetic expr0 setState -a+6.809
Arithmetic expr1 setState 0
Arithmetic expr2 setState 0
Arithmetic expr3 setState 0
Arithmetic expr4 setState 0
Arithmetic expr5 setState 0
Arithmetic expr6 setState 0
Arithmetic expr7 setState 0
Arithmetic expr8 setState 0
Arithmetic resultType setValue 0
Arithmetic resultLocation setValue 0
Arithmetic resolution setMinMax 0 1 100000
Arithmetic resolution setValue 0 64
Arithmetic resolution setMinMax 1 1 100000
Arithmetic resolution setValue 1 64
Arithmetic resolution setMinMax 2 1 100000
Arithmetic resolution setValue 2 64
Arithmetic minBox setMinMax 0 -3.40282346638529e+038 3.40282346638529e+038
Arithmetic minBox setValue 0 -1
Arithmetic minBox setMinMax 1 -3.40282346638529e+038 3.40282346638529e+038
Arithmetic minBox setValue 1 -1
Arithmetic minBox setMinMax 2 -3.40282346638529e+038 3.40282346638529e+038
Arithmetic minBox setValue 2 -1
Arithmetic maxBox setMinMax 0 -3.40282346638529e+038 3.40282346638529e+038
Arithmetic maxBox setValue 0 1
Arithmetic maxBox setMinMax 1 -3.40282346638529e+038 3.40282346638529e+038
Arithmetic maxBox setValue 1 1
Arithmetic maxBox setMinMax 2 -3.40282346638529e+038 3.40282346638529e+038
Arithmetic maxBox setValue 2 1
Arithmetic options setValue 0 0
Arithmetic options setToggleVisible 0 1
Arithmetic fire
Arithmetic setViewerMask 16383
Arithmetic setPickable 1

set hideNewModules 0
[ {Arithmetic} create
 ] setLabel {Result}
Result setIconPosition 20 150
Result master connect Arithmetic
Result fire
Result setViewerMask 16383

set hideNewModules 0
create HxWatershedSegmentation {WatershedSegmentation}
WatershedSegmentation setIconPosition 160 180
WatershedSegmentation data connect Result
WatershedSegmentation fire
WatershedSegmentation inputThreshold setMinMax -6.72492969897576e-005 6.80900001525879
WatershedSegmentation inputThreshold setButtons 0
WatershedSegmentation inputThreshold setIncrement 0.453938
WatershedSegmentation inputThreshold setValue 0.5
WatershedSegmentation inputThreshold setSubMinMax -6.72492969897576e-005 6.80900001525879
WatershedSegmentation minimalDepth setMinMax 0 6.30900001525879
WatershedSegmentation minimalDepth setButtons 0
WatershedSegmentation minimalDepth setIncrement 0.4206
WatershedSegmentation minimalDepth setValue 1.8
WatershedSegmentation minimalDepth setSubMinMax 0 6.30900001525879
WatershedSegmentation outputType setIndex 0 0
WatershedSegmentation fire
WatershedSegmentation setViewerMask 16383
WatershedSegmentation setPickable 1

set hideNewModules 0
[ {WatershedSegmentation} action hit ; {WatershedSegmentation} fire ; {WatershedSegmentation} getResult 
 ] setLabel {Result.Regions}
Result.Regions setIconPosition 20 210
Result.Regions master connect WatershedSegmentation
Result.Regions fire
Result.Regions primary setIndex 0 0
Result.Regions fire
Result.Regions setViewerMask 16383

set hideNewModules 0
create HxColorwash {Colorwash}
Colorwash setIconPosition 373 30
Colorwash data connect Result.Regions
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
Colorwash select
Colorwash weightFactor setPin 1
Colorwash deselect
Colorwash setPickable 1

set hideNewModules 0


viewer 0 setCameraOrientation 1 0 0 3.14159
viewer 0 setCameraPosition 207.323 183.126 -230.718
viewer 0 setCameraFocalDistance 263.652
viewer 0 setCameraNearDistance 265.824
viewer 0 setCameraFarDistance 266.357
viewer 0 setCameraType perspective
viewer 0 setCameraHeightAngle 44.9023
viewer 0 setAutoRedraw 1
viewer 0 redraw

