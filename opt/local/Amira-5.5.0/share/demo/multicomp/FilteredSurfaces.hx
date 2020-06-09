# Amira Script
remove -all
remove grey.am cellbodies.am cellbodies.labeledRegions.am labelcolors.am cellbodies.labeledRegions.SpreadSheet cellbodies.labeledRegions.Spreadsheet.Filtered cellbodies.labeledRegions.Labels.Filtered cellbodies.labeledRegions.Labels.surf OrthoSlice ShapeAnalysis SpreadsheetFilter FilterBySpreadsheet Colorwash BoundingBox SurfaceGen SurfaceView

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
{grey.am} setMinMax 58 160
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
cellbodies.labeledRegions.SpreadSheet setIconPosition 20 130
cellbodies.labeledRegions.SpreadSheet master connect ShapeAnalysis 0
cellbodies.labeledRegions.SpreadSheet fire
cellbodies.labeledRegions.SpreadSheet fire
cellbodies.labeledRegions.SpreadSheet setViewerMask 16383

set hideNewModules 0
create HxSpreadsheetFilter {SpreadsheetFilter}
SpreadsheetFilter setIconPosition 160 160
SpreadsheetFilter data connect cellbodies.labeledRegions.SpreadSheet
SpreadsheetFilter fire
SpreadsheetFilter table setIndex 0 0
SpreadsheetFilter fire
SpreadsheetFilter table setIndex 0 0
SpreadsheetFilter expression setState {}
SpreadsheetFilter action snap 0 1
SpreadsheetFilter column0 setState item 0 1 item 2 1 
SpreadsheetFilter filter0 setMinMax -0 5000
SpreadsheetFilter filter0 setValues 300 5000
SpreadsheetFilter filter0 setButtons 1
SpreadsheetFilter filter0 setIncrement 333.333
SpreadsheetFilter filter0 setSubMinMax 0 0
SpreadsheetFilter column1 setState item 0 5 item 2 1 
SpreadsheetFilter filter1 setMinMax 0 1
SpreadsheetFilter filter1 setValues 0.5 1
SpreadsheetFilter filter1 setButtons 1
SpreadsheetFilter filter1 setIncrement 0.01
SpreadsheetFilter filter1 setSubMinMax 0 0
SpreadsheetFilter column2 setState item 0 6 item 2 0 
SpreadsheetFilter filter2 setMinMax -0 2
SpreadsheetFilter filter2 setValues 0 2
SpreadsheetFilter filter2 setButtons 1
SpreadsheetFilter filter2 setIncrement 0.133333
SpreadsheetFilter filter2 setSubMinMax 0 0
SpreadsheetFilter column3 setState item 0 7 item 2 0 
SpreadsheetFilter filter3 setMinMax -0 2
SpreadsheetFilter filter3 setValues 0 2
SpreadsheetFilter filter3 setButtons 1
SpreadsheetFilter filter3 setIncrement 0.133333
SpreadsheetFilter filter3 setSubMinMax 0 0
SpreadsheetFilter fire
SpreadsheetFilter filter0 setValues 300 5000
SpreadsheetFilter filter1 setValues 0.5 1
SpreadsheetFilter filter2 setValues 0 2
SpreadsheetFilter filter3 setValues 0 2
SpreadsheetFilter fire
SpreadsheetFilter fire
SpreadsheetFilter setViewerMask 16383
SpreadsheetFilter select
SpreadsheetFilter filter0 setPin 1
SpreadsheetFilter filter1 setPin 1
SpreadsheetFilter deselect
SpreadsheetFilter setPickable 1

set hideNewModules 0
[ {SpreadsheetFilter} action hit; {SpreadsheetFilter} fire; {SpreadsheetFilter} getResult ] setLabel {cellbodies.labeledRegions.Spreadsheet.Filtered}
cellbodies.labeledRegions.Spreadsheet.Filtered setIconPosition 20 190
cellbodies.labeledRegions.Spreadsheet.Filtered master connect SpreadsheetFilter
cellbodies.labeledRegions.Spreadsheet.Filtered fire
cellbodies.labeledRegions.Spreadsheet.Filtered fire
cellbodies.labeledRegions.Spreadsheet.Filtered setViewerMask 16383

set hideNewModules 0
create HxFilterBySpreadsheet {FilterBySpreadsheet}
FilterBySpreadsheet setIconPosition 160 100
FilterBySpreadsheet data connect cellbodies.labeledRegions.am
FilterBySpreadsheet InputSpreadSheet connect cellbodies.labeledRegions.Spreadsheet.Filtered
FilterBySpreadsheet fire
FilterBySpreadsheet table setIndex 0 0
FilterBySpreadsheet LabelColumn setIndex 0 0
FilterBySpreadsheet action snap 0 1
FilterBySpreadsheet fire
FilterBySpreadsheet setViewerMask 16383
FilterBySpreadsheet setPickable 1

set hideNewModules 0
[ {FilterBySpreadsheet} action hit; {FilterBySpreadsheet} fire; {FilterBySpreadsheet} getResult ] setLabel {cellbodies.labeledRegions.Labels.Filtered}
cellbodies.labeledRegions.Labels.Filtered setIconPosition 20 220
cellbodies.labeledRegions.Labels.Filtered master connect FilterBySpreadsheet
cellbodies.labeledRegions.Labels.Filtered fire
cellbodies.labeledRegions.Labels.Filtered primary setIndex 0 0
cellbodies.labeledRegions.Labels.Filtered fire
cellbodies.labeledRegions.Labels.Filtered setViewerMask 16383

set hideNewModules 0
create HxColorwash {Colorwash}
Colorwash setIconPosition 373 30
Colorwash data connect cellbodies.labeledRegions.Labels.Filtered
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
create HxGMC {SurfaceGen}
SurfaceGen setIconPosition 160 250
SurfaceGen data connect cellbodies.labeledRegions.Labels.Filtered
SurfaceGen fire
SurfaceGen smoothing setIndex 0 3
SurfaceGen options setValue 0 1
SurfaceGen options setToggleVisible 0 1
SurfaceGen options setValue 1 0
SurfaceGen options setToggleVisible 1 1
SurfaceGen border setValue 0 1
SurfaceGen border setToggleVisible 0 1
SurfaceGen border setValue 1 0
SurfaceGen border setToggleVisible 1 1
SurfaceGen minEdgeLength setMinMax 0 0 0.800000011920929
SurfaceGen minEdgeLength setValue 0 0
SurfaceGen materialList setIndex 0 0
SurfaceGen smoothMaterial setIndex 0 0
SurfaceGen action snap 0 1
SurfaceGen fire
SurfaceGen setViewerMask 16383
SurfaceGen setPickable 1

set hideNewModules 0
[ {SurfaceGen} create {cellbodies.labeledRegions.Labels.surf}
 ] setLabel {cellbodies.labeledRegions.Labels.surf}
cellbodies.labeledRegions.Labels.surf setIconPosition 20 280
cellbodies.labeledRegions.Labels.surf master connect SurfaceGen
cellbodies.labeledRegions.Labels.surf fire
cellbodies.labeledRegions.Labels.surf LevelOfDetail setMinMax -1 -1
cellbodies.labeledRegions.Labels.surf LevelOfDetail setButtons 1
cellbodies.labeledRegions.Labels.surf LevelOfDetail setIncrement 1
cellbodies.labeledRegions.Labels.surf LevelOfDetail setValue -1
cellbodies.labeledRegions.Labels.surf LevelOfDetail setSubMinMax -1 -1
cellbodies.labeledRegions.Labels.surf setTransform 1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1
cellbodies.labeledRegions.Labels.surf fire
cellbodies.labeledRegions.Labels.surf setViewerMask 16383

set hideNewModules 0
create HxDisplaySurface {SurfaceView}
SurfaceView setIconPosition 360 280
SurfaceView data connect cellbodies.labeledRegions.Labels.surf
SurfaceView colormap setDefaultColor 1 0.1 0.1
SurfaceView colormap setDefaultAlpha 0.500000
SurfaceView colormap setLocalRange 0
SurfaceView fire
SurfaceView drawStyle setValue 1
SurfaceView fire
SurfaceView drawStyle setSpecularLighting 1
SurfaceView drawStyle setTexture 1
SurfaceView drawStyle setAlphaMode 1
SurfaceView drawStyle setNormalBinding 0
SurfaceView drawStyle setSortingMode 1
SurfaceView drawStyle setLineWidth 0.000000
SurfaceView drawStyle setOutlineColor 0 0 0.2
SurfaceView textureWrap setIndex 0 1
SurfaceView cullingMode setValue 0
SurfaceView selectionMode setIndex 0 0
SurfaceView Patch setMinMax 0 164
SurfaceView Patch setButtons 1
SurfaceView Patch setIncrement 1
SurfaceView Patch setValue 0
SurfaceView Patch setSubMinMax 0 39
SurfaceView BoundaryId setIndex 0 -1
SurfaceView materials setIndex 0 1
SurfaceView materials setIndex 1 0
SurfaceView colorMode setIndex 0 0
SurfaceView baseTrans setMinMax 0 1
SurfaceView baseTrans setButtons 0
SurfaceView baseTrans setIncrement 0.1
SurfaceView baseTrans setValue 0.8
SurfaceView baseTrans setSubMinMax 0 1
SurfaceView VRMode setIndex 0 0
SurfaceView fire
SurfaceView hideBox 1
{SurfaceView} selectTriangles zab HIJMONMBDBABAAAAAAMCKAPOKJGHAJEPKAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAOAGPOBAIEBDG
SurfaceView fire
SurfaceView setViewerMask 16383
SurfaceView setShadowStyle 0
SurfaceView setPickable 1

set hideNewModules 0


viewer 0 setCameraOrientation 0.941134 -0.287612 0.177614 4.16264
viewer 0 setCameraPosition 365.871 436.579 -104.925
viewer 0 setCameraFocalDistance 333.765
viewer 0 setCameraNearDistance 197.93
viewer 0 setCameraFarDistance 458.663
viewer 0 setCameraType perspective
viewer 0 setCameraHeightAngle 44.9023
viewer 0 setAutoRedraw 1
viewer 0 redraw

