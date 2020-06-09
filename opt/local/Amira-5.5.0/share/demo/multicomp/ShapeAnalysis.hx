# Amira Script
remove -all
remove physics.icol grey.am cellbodies.am cellbodies.labeledRegions.am labelcolors.am cellbodies.labeledRegions.SpreadSheet cellbodies.labeledRegions.BoundingBoxes cellbodies.labeledRegions.Cluster OrthoSlice ShapeAnalysis Colorwash SpreadSheetToCluster EmptyPlane TensorDisplay BoundingBox LineSetView

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
[ load ${AMIRA_ROOT}/data/colormaps/physics.icol ] setLabel physics.icol
physics.icol setIconPosition 0 0
physics.icol setNoRemoveAll 1
physics.icol fire
{physics.icol} setMinMax 0 1 
physics.icol flags setValue 1
physics.icol shift setMinMax -1 1
physics.icol shift setButtons 0
physics.icol shift setIncrement 0.133333
physics.icol shift setValue 0
physics.icol shift setSubMinMax -1 1
physics.icol scale setMinMax 0 1
physics.icol scale setButtons 0
physics.icol scale setIncrement 0.1
physics.icol scale setValue 1
physics.icol scale setSubMinMax 0 1
physics.icol fire
physics.icol setViewerMask 16383

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
[ load ${AMIRA_ROOT}/data/tutorials/multicomp/cellbodies.labeledRegions.am ] setLabel cellbodies.labeledRegions.am
cellbodies.labeledRegions.am setIconPosition 20 40
cellbodies.labeledRegions.am fire
cellbodies.labeledRegions.am primary setIndex 0 0
cellbodies.labeledRegions.am fire
cellbodies.labeledRegions.am setViewerMask 16383

set hideNewModules 1
[ load ${AMIRA_ROOT}/data/colormaps/labelcolors.am ] setLabel labelcolors.am
labelcolors.am setIconPosition 20 70
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
OrthoSlice setViewerMask 16382
OrthoSlice setShadowStyle 0
OrthoSlice setPickable 1

set hideNewModules 0
create HxShapeAnalysis {ShapeAnalysis}
ShapeAnalysis setIconPosition 160 70
ShapeAnalysis data connect cellbodies.labeledRegions.am
ShapeAnalysis fire
ShapeAnalysis fire
ShapeAnalysis setViewerMask 16383
ShapeAnalysis setPickable 1

set hideNewModules 0
[ {ShapeAnalysis} action hit ; {ShapeAnalysis} fire ; {ShapeAnalysis} getResult 
 ] setLabel {cellbodies.labeledRegions.SpreadSheet}
cellbodies.labeledRegions.SpreadSheet setIconPosition 20 100
cellbodies.labeledRegions.SpreadSheet master connect ShapeAnalysis 0
cellbodies.labeledRegions.SpreadSheet fire
cellbodies.labeledRegions.SpreadSheet fire
cellbodies.labeledRegions.SpreadSheet setViewerMask 16383

set hideNewModules 0
create HxColorwash {Colorwash}
Colorwash setIconPosition 373 30
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
Colorwash weightFactor setValue 0.490446
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
create HxSpreadSheetToCluster {SpreadSheetToCluster}
SpreadSheetToCluster setIconPosition 160 130
SpreadSheetToCluster data connect cellbodies.labeledRegions.SpreadSheet
SpreadSheetToCluster fire
SpreadSheetToCluster output setValue 0 1
SpreadSheetToCluster output setToggleVisible 0 1
SpreadSheetToCluster output setValue 1 1
SpreadSheetToCluster output setToggleVisible 1 1
SpreadSheetToCluster tensor setValue 1
SpreadSheetToCluster table setIndex 0 0
SpreadSheetToCluster value setIndex 0 8
SpreadSheetToCluster coordinates setIndex 0 2
SpreadSheetToCluster coordinates setIndex 1 3
SpreadSheetToCluster coordinates setIndex 2 4
SpreadSheetToCluster firstDirection setIndex 0 11
SpreadSheetToCluster firstDirection setIndex 1 12
SpreadSheetToCluster firstDirection setIndex 2 13
SpreadSheetToCluster secondDirection setIndex 0 14
SpreadSheetToCluster secondDirection setIndex 1 15
SpreadSheetToCluster secondDirection setIndex 2 16
SpreadSheetToCluster thirdDirection setIndex 0 17
SpreadSheetToCluster thirdDirection setIndex 1 18
SpreadSheetToCluster thirdDirection setIndex 2 19
SpreadSheetToCluster ExtentMin setIndex 0 20
SpreadSheetToCluster ExtentMin setIndex 1 21
SpreadSheetToCluster ExtentMin setIndex 2 22
SpreadSheetToCluster ExtentMax setIndex 0 23
SpreadSheetToCluster ExtentMax setIndex 1 24
SpreadSheetToCluster ExtentMax setIndex 2 25
SpreadSheetToCluster action snap 0 1
SpreadSheetToCluster fire
SpreadSheetToCluster setViewerMask 16383
SpreadSheetToCluster setPickable 1

set hideNewModules 0
[ {SpreadSheetToCluster} action hit; {SpreadSheetToCluster} fire; {SpreadSheetToCluster} getResult ] setLabel {cellbodies.labeledRegions.BoundingBoxes}
cellbodies.labeledRegions.BoundingBoxes setIconPosition 20 190
cellbodies.labeledRegions.BoundingBoxes master connect SpreadSheetToCluster 0
cellbodies.labeledRegions.BoundingBoxes fire
cellbodies.labeledRegions.BoundingBoxes setViewerMask 16383

set hideNewModules 0
[ {SpreadSheetToCluster} action hit; {SpreadSheetToCluster} fire; {SpreadSheetToCluster} getResult cluster ] setLabel {cellbodies.labeledRegions.Cluster}
cellbodies.labeledRegions.Cluster setIconPosition 20 160
cellbodies.labeledRegions.Cluster master connect SpreadSheetToCluster 1
cellbodies.labeledRegions.Cluster fire
cellbodies.labeledRegions.Cluster setViewerMask 16383

set hideNewModules 0
create HxArbitraryCut {EmptyPlane}
EmptyPlane setIconPosition 354 160
EmptyPlane data connect cellbodies.labeledRegions.Cluster
EmptyPlane fire
EmptyPlane origin  setBoundingBox -1e+008 1e+008 -1e+008 1e+008 -1e+008 1e+008
EmptyPlane origin  setImmediate 0
EmptyPlane origin  setOrtho 0
EmptyPlane origin  showDragger 0
EmptyPlane origin  showPoints 0
EmptyPlane origin  setPointScale 1
EmptyPlane origin  showOptionButton 1
EmptyPlane origin  setNumPoints 1 1 1
EmptyPlane origin  setValue 0 206.92 183.235 31.8097
EmptyPlane normal  setBoundingBox -1e+008 1e+008 -1e+008 1e+008 -1e+008 1e+008
EmptyPlane normal  setImmediate 0
EmptyPlane normal  setOrtho 0
EmptyPlane normal  showDragger 0
EmptyPlane normal  showPoints 0
EmptyPlane normal  setPointScale 1
EmptyPlane normal  showOptionButton 1
EmptyPlane normal  setNumPoints 1 1 1
EmptyPlane normal  setValue 0 0 0 1
EmptyPlane frameSettings setState item 0 1 item 2 1 color 3 1 0.5 0 
EmptyPlane options setValue 0 0
EmptyPlane options setToggleVisible 0 1
EmptyPlane options setValue 1 0
EmptyPlane options setToggleVisible 1 1
EmptyPlane options setValue 2 1
EmptyPlane options setToggleVisible 2 1
EmptyPlane options setValue 3 0
EmptyPlane options setToggleVisible 3 1
EmptyPlane translate setMinMax 0 100
EmptyPlane translate setButtons 1
EmptyPlane translate setIncrement 1
EmptyPlane translate setValue 50
EmptyPlane translate setSubMinMax 0 100
EmptyPlane orientation untouch
EmptyPlane setMinPlanePoint -1e+015 -1e+015 -1e+015
EmptyPlane setMaxPlanePoint 1e+015 1e+015 1e+015
EmptyPlane setTranslateRange 101.000000
EmptyPlane fire
EmptyPlane setViewerMask 16382
EmptyPlane setPickable 1

set hideNewModules 0
create HxTensorDisplay {TensorDisplay}
TensorDisplay setIconPosition 354 180
TensorDisplay data connect cellbodies.labeledRegions.Cluster
TensorDisplay module connect EmptyPlane
TensorDisplay Colormap setDefaultColor 1 0.8 0.5
TensorDisplay Colormap setDefaultAlpha 0.500000
TensorDisplay Colormap setLocalRange 0
TensorDisplay Colormap connect physics.icol
TensorDisplay fire
TensorDisplay DisplayMode setValue 0
TensorDisplay Display setValue 2
TensorDisplay Options setValue 0 1
TensorDisplay Options setToggleVisible 0 1
TensorDisplay MappingsAndColorings setIndex 0 -1
TensorDisplay MappingsAndColorings setIndex 1 0
TensorDisplay ScaleByValue setValue 0 1
TensorDisplay ScaleByValue setToggleVisible 0 1
TensorDisplay ScaleByValue setValue 1 1
TensorDisplay ScaleByValue setToggleVisible 1 1
TensorDisplay ScaleByValue setValue 2 1
TensorDisplay ScaleByValue setToggleVisible 2 1
TensorDisplay ScaleByValue setValue 3 0
TensorDisplay ScaleByValue setToggleVisible 3 1
TensorDisplay DisplayComplexity setMinMax 0 1
TensorDisplay DisplayComplexity setButtons 0
TensorDisplay DisplayComplexity setIncrement 0.1
TensorDisplay DisplayComplexity setValue 0.707006
TensorDisplay DisplayComplexity setSubMinMax 0 1
TensorDisplay Resolution setMinMax 0 1 1000
TensorDisplay Resolution setValue 0 60
TensorDisplay Resolution setMinMax 1 1 1000
TensorDisplay Resolution setValue 1 60
TensorDisplay MaskExpr setState A>0
TensorDisplay Offset setMinMax -5 5
TensorDisplay Offset setButtons 0
TensorDisplay Offset setIncrement 0.666667
TensorDisplay Offset setValue 0
TensorDisplay Offset setSubMinMax -5 5
TensorDisplay Scale setMinMax 0 5000
TensorDisplay Scale setButtons 0
TensorDisplay Scale setIncrement 333.333
TensorDisplay Scale setValue 1
TensorDisplay Scale setSubMinMax 0 5000
TensorDisplay action snap 0 1
{TensorDisplay} fire
{TensorDisplay} setVolumeModeSkip 2
{TensorDisplay} setSigmoidSteepness 1
{TensorDisplay} setPointSize 1
TensorDisplay fire
TensorDisplay setViewerMask 16383
TensorDisplay setPickable 1

set hideNewModules 0
create HxBoundingBox {BoundingBox}
BoundingBox setIconPosition 360 60
BoundingBox data connect cellbodies.am
BoundingBox fire
BoundingBox options setState item 0 0 color 1 1 0.5 0 item 3 0 
BoundingBox lineWidth setMinMax 1 10
BoundingBox lineWidth setButtons 0
BoundingBox lineWidth setIncrement 1
BoundingBox lineWidth setValue 1
BoundingBox lineWidth setSubMinMax 1 10
BoundingBox font setState name: {Helvetica} size: 12 bold: 0 italic: 0 color: 0.8 0.8 0.8
BoundingBox fire
BoundingBox setViewerMask 16383
BoundingBox setShadowStyle 0
BoundingBox setPickable 1

set hideNewModules 0
create HxDisplayLineSet {LineSetView}
LineSetView setIconPosition 362 210
{LineSetView} setLineWidth 1
{LineSetView} setLineColor 1 1 1
{LineSetView} setSphereColor 1 1 1
{LineSetView} setStripeColorMapping 0
LineSetView data connect cellbodies.labeledRegions.BoundingBoxes
LineSetView colormap setDefaultColor 1 0.8 0.5
LineSetView colormap setDefaultAlpha 0.500000
LineSetView colormap setLocalRange 0
LineSetView alphamap setDefaultColor 1 0.8 0.5
LineSetView alphamap setDefaultAlpha 0.500000
LineSetView alphamap setLocalRange 0
LineSetView fire
LineSetView shape setIndex 0 6
LineSetView circleComplexity setMinMax 3 30
LineSetView circleComplexity setButtons 1
LineSetView circleComplexity setIncrement 1
LineSetView circleComplexity setValue 12
LineSetView circleComplexity setSubMinMax 3 30
LineSetView scaleMode setIndex 0 0
LineSetView scaleFactor setMinMax 0 2.5
LineSetView scaleFactor setButtons 0
LineSetView scaleFactor setIncrement 0.166667
LineSetView scaleFactor setValue 0.5
LineSetView scaleFactor setSubMinMax 0 2.5
LineSetView rotateMode setIndex 0 0
LineSetView rotateMode setIndex 1 2
LineSetView rotateMode setIndex 2 0
LineSetView rotateFactor setMinMax 0 360
LineSetView rotateFactor setButtons 0
LineSetView rotateFactor setIncrement 24
LineSetView rotateFactor setValue 0
LineSetView rotateFactor setSubMinMax 0 360
LineSetView twistMode setIndex 0 0
LineSetView twistMode setIndex 1 1
LineSetView twistFactor setMinMax -0.100000001490116 0.100000001490116
LineSetView twistFactor setButtons 0
LineSetView twistFactor setIncrement 0.0133333
LineSetView twistFactor setValue 0.05
LineSetView twistFactor setSubMinMax -0.100000001490116 0.100000001490116
LineSetView colorMode setIndex 0 0
LineSetView colorMode setIndex 1 0
LineSetView colorMode setIndex 2 0
LineSetView spheres setIndex 0 0
LineSetView sphereScale setMinMax 0 2.5
LineSetView sphereScale setButtons 0
LineSetView sphereScale setIncrement 0.166667
LineSetView sphereScale setValue 0.1
LineSetView sphereScale setSubMinMax 0 2.5
LineSetView sphereColor setIndex 0 0
LineSetView sphereColor setIndex 1 0
LineSetView sphereComplexity setMinMax 0.0560000017285347 1
LineSetView sphereComplexity setButtons 0
LineSetView sphereComplexity setIncrement 0.0629333
LineSetView sphereComplexity setValue 0.2
LineSetView sphereComplexity setSubMinMax 0.0560000017285347 1
LineSetView fire
LineSetView setViewerMask 16383
LineSetView setPickable 1

set hideNewModules 0


viewer 0 setCameraOrientation 0.941134 -0.287612 0.177614 4.16264
viewer 0 setCameraPosition 365.871 436.579 -104.925
viewer 0 setCameraFocalDistance 333.765
viewer 0 setCameraNearDistance 138.607
viewer 0 setCameraFarDistance 516.925
viewer 0 setCameraType perspective
viewer 0 setCameraHeightAngle 44.9023
viewer 0 setAutoRedraw 1
viewer 0 redraw

