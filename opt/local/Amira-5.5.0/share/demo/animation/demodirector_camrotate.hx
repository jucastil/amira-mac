# Amira Script
remove -all
remove temperature.icol reg005.ctdata.am reg005.surf CameraRotate BoundingBox OrthoSlice DemoMaker SurfaceView

# Create viewers
viewer setVertical 0

viewer 0 setBackgroundMode 1
viewer 0 setBackgroundColor 0.06 0.13 0.24
viewer 0 setBackgroundColor2 0.72 0.72 0.78
viewer 0 setTransparencyType 6
viewer 0 setAutoRedraw 0
viewer 0 show
mainWindow show

set hideNewModules 1
[ load ${AMIRA_ROOT}/data/colormaps/temperature.icol ] setLabel temperature.icol
temperature.icol setIconPosition 0 0
temperature.icol setNoRemoveAll 1
temperature.icol fire
{temperature.icol} setMinMax 38 44
temperature.icol flags setValue 1
temperature.icol shift setMinMax -1 1
temperature.icol shift setButtons 0
temperature.icol shift setIncrement 0.133333
temperature.icol shift setValue 0
temperature.icol shift setSubMinMax -1 1
temperature.icol scale setMinMax 0 1
temperature.icol scale setButtons 0
temperature.icol scale setIncrement 0.1
temperature.icol scale setValue 1
temperature.icol scale setSubMinMax 0 1
temperature.icol fire
temperature.icol setViewerMask 16383

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/medical/reg005.ctdata.am ] setLabel reg005.ctdata.am
reg005.ctdata.am setIconPosition 20 10
reg005.ctdata.am fire
reg005.ctdata.am setViewerMask 16383

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/medical/reg005.surf ] setLabel reg005.surf
reg005.surf setIconPosition 20 77
reg005.surf fire
reg005.surf LevelOfDetail setMinMax -1 -1
reg005.surf LevelOfDetail setButtons 1
reg005.surf LevelOfDetail setIncrement 1
reg005.surf LevelOfDetail setValue -1
reg005.surf LevelOfDetail setSubMinMax -1 -1
reg005.surf fire
reg005.surf setViewerMask 16383

set hideNewModules 0
create HxCircularCameraPath {CameraRotate}
CameraRotate setIconPosition 20 107
CameraRotate time setMinMax 0 360
CameraRotate time setSubMinMax 0 360
CameraRotate time setValue 0
CameraRotate time setDiscrete 0
CameraRotate time setIncrement 1
CameraRotate time animationMode -once
CameraRotate fire
CameraRotate action setOptValue 0 0
CameraRotate setPosition 44.1818 -61.0237 70.2967
CameraRotate setAimPoint 24.3114 21.4018 30.0003
CameraRotate setUpDirection -0.153342 0.403931 0.901846
CameraRotate setAxis 0 0 1
CameraRotate fire
CameraRotate setViewerMask 16383

set hideNewModules 0
create HxBoundingBox {BoundingBox}
BoundingBox setIconPosition 337 10
BoundingBox data connect reg005.ctdata.am
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
create HxOrthoSlice {OrthoSlice}
OrthoSlice setIconPosition 350 40
OrthoSlice data connect reg005.ctdata.am
{OrthoSlice} fire
OrthoSlice sliceOrientation setValue 0
{OrthoSlice} fire
OrthoSlice origin  setBoundingBox -1e+008 1e+008 -1e+008 1e+008 -1e+008 1e+008
OrthoSlice origin  setImmediate 0
OrthoSlice origin  setOrtho 0
OrthoSlice origin  showDragger 0
OrthoSlice origin  showPoints 0
OrthoSlice origin  setPointScale 1
OrthoSlice origin  setNumPoints 1 1 1
OrthoSlice origin  setValue 0 24.3114 21.4016 1
OrthoSlice normal  setBoundingBox -1e+008 1e+008 -1e+008 1e+008 -1e+008 1e+008
OrthoSlice normal  setImmediate 0
OrthoSlice normal  setOrtho 0
OrthoSlice normal  showDragger 0
OrthoSlice normal  showPoints 0
OrthoSlice normal  setPointScale 1
OrthoSlice normal  setNumPoints 1 1 1
OrthoSlice normal  setValue 0 0 0 1
OrthoSlice options setValue 0 1
OrthoSlice options setToggleVisible 0 1
OrthoSlice options setValue 1 0
OrthoSlice options setToggleVisible 1 1
OrthoSlice options setValue 2 0
OrthoSlice options setToggleVisible 2 1
OrthoSlice mappingType setIndex 0 0
OrthoSlice linearRange setMinMax 0 -3.40282346638529e+038 3.40282346638529e+038
OrthoSlice linearRange setValue 0 -200
OrthoSlice linearRange setMinMax 1 -3.40282346638529e+038 3.40282346638529e+038
OrthoSlice linearRange setValue 1 200
OrthoSlice contrastLimit setMinMax 0 -2147483648 2147483648
OrthoSlice contrastLimit setValue 0 7
OrthoSlice colormap setDefaultColor 1 0.8 0.5
OrthoSlice colormap setDefaultAlpha 1.000000
OrthoSlice colormap connect temperature.icol
OrthoSlice sliceNumber setMinMax 0 58
OrthoSlice sliceNumber setButtons 1
OrthoSlice sliceNumber setIncrement 1
OrthoSlice sliceNumber setValue 0
OrthoSlice sliceNumber setSubMinMax 0 58
OrthoSlice transparency setValue 0
OrthoSlice frameSettings setState item 0 1 item 2 1 color 3 1 0.5 0 
OrthoSlice fire

OrthoSlice fire
OrthoSlice setViewerMask 16383
OrthoSlice setShadowStyle 0
OrthoSlice setPickable 1

set hideNewModules 0
create HxScriptObject {DemoMaker}
{DemoMaker} script setValue ${AMIRA_ROOT}/share/script-objects/DemoMaker.scro
DemoMaker setIconPosition 109 47
{DemoMaker} setVar {scroTypeDemoMaker} {1}
{DemoMaker} setVar {isInitialized} {0}
{DemoMaker} setVar {isDemoMakerActive} {1}
{DemoMaker} setVar {funcKeysDefined} {1}
{DemoMaker} setVar {atEndCallback} {}
{DemoMaker} setVar {internalEventList} {dummy {numeric {{OrthoSlice/Slice Number} 102} 0 15 0 30 -1e24 1e24 {OrthoSlice sliceNumber setValue %0%; OrthoSlice fire}} {numeric {CameraRotate/Time 108} 15 30 0 360 -1e24 1e24 {CameraRotate time setValue %0%; CameraRotate fire}} {toggle {{SurfaceView/Viewer mask/Viewer 0} 105} 15 1 {SurfaceView setViewerMask [expr ([SurfaceView getViewerMask]&254)+%0%*1]}}}
{DemoMaker} setVar {lastStartTime} {15}
{DemoMaker} setVar {lastEndTime} {30}
{DemoMaker} setVar {lastTimeStep} {0}
{DemoMaker} setVar {eventIdCount} {109}
{DemoMaker} setVar {eventTemplateIdCount} {160}
{DemoMaker} setVar {lengthOfNewEvents} {10.6637}
{DemoMaker} setVar {CustomHelp} {HxDemoDirector.html}
DemoMaker fire
DemoMaker time setMinMax 0 100
DemoMaker time setSubMinMax 0 100
DemoMaker time setValue 0
DemoMaker time setDiscrete 0
DemoMaker time setIncrement 0.1
DemoMaker time animationMode -once
DemoMaker eventList setOptValue 0 2
DemoMaker eventSearch setState {}
DemoMaker functions setValue 0 1
DemoMaker functions setToggleVisible 0 1
DemoMaker functions setValue 1 0
DemoMaker functions setToggleVisible 1 1
DemoMaker options setValue 0 0
DemoMaker options setToggleVisible 0 1
DemoMaker options setValue 1 0
DemoMaker options setToggleVisible 1 1
DemoMaker options setValue 2 1
DemoMaker options setToggleVisible 2 1
DemoMaker moreOpt1 setValue 0 0
DemoMaker moreOpt1 setToggleVisible 0 1
DemoMaker moreOpt1 setValue 1 1
DemoMaker moreOpt1 setToggleVisible 1 1
DemoMaker moreOpt2 setValue 0 1
DemoMaker moreOpt2 setToggleVisible 0 1
DemoMaker moreOpt2 setValue 1 0
DemoMaker moreOpt2 setToggleVisible 1 1
DemoMaker moreOpt2 setValue 2 0
DemoMaker moreOpt2 setToggleVisible 2 1
DemoMaker eventListFile setState {C:/Program Files/Amira 5.3.0/share/script-objects/event_list.txt}
DemoMaker waitImg setState {C:/Program Files/Amira 5.3.0/share/script-objects/img/amira_150_red.png}
DemoMaker moveFrom setMinMax 0 -3.40282346638529e+038 3.40282346638529e+038
DemoMaker moveFrom setValue 0 0
DemoMaker moveFrom setMinMax 1 -3.40282346638529e+038 3.40282346638529e+038
DemoMaker moveFrom setValue 1 0
DemoMaker moveTo setMinMax 0 -3.40282346638529e+038 3.40282346638529e+038
DemoMaker moveTo setValue 0 0
DemoMaker moveTo setMinMax 1 -3.40282346638529e+038 3.40282346638529e+038
DemoMaker moveTo setValue 1 0
DemoMaker guiElements setOptValue 0 11
DemoMaker command setState {echo "%0% %1% %2%"}
DemoMaker startEndValue setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
DemoMaker startEndValue setValue 0 0
DemoMaker startEndValue setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
DemoMaker startEndValue setValue 1 360
DemoMaker startVector setState {0 0 0}
DemoMaker endVector setState {1 1 1}
DemoMaker toggleValue setValue 1
DemoMaker selectValue setIndex 0 -1
DemoMaker selectValue setIndex 1 -1
DemoMaker triggerTime setMinMax 0 -10000000000 10000000000
DemoMaker triggerTime setValue 0 0
DemoMaker modifKeys setValue 0 0
DemoMaker modifKeys setToggleVisible 0 1
DemoMaker modifKeys setValue 1 0
DemoMaker modifKeys setToggleVisible 1 1
DemoMaker modifKeys setValue 2 0
DemoMaker modifKeys setToggleVisible 2 1
DemoMaker waitingTime setMinMax 0 -3.40282346638529e+038 3.40282346638529e+038
DemoMaker waitingTime setValue 0 10.6637001037598
DemoMaker gotoTime setMinMax 0 -3.40282346638529e+038 3.40282346638529e+038
DemoMaker gotoTime setValue 0 10.6637001037598
DemoMaker startEndTime setMinMax 0 -10000000000 10000000000
DemoMaker startEndTime setValue 0 15
DemoMaker startEndTime setMinMax 1 -10000000000 10000000000
DemoMaker startEndTime setValue 1 30
DemoMaker loadFile setState {}
DemoMaker loadOptions setValue 0 1
DemoMaker loadOptions setToggleVisible 0 1
DemoMaker startScro setIndex 0 -1
DemoMaker startTime setMinMax 0 -3.40282346638529e+038 3.40282346638529e+038
DemoMaker startTime setValue 0 0
DemoMaker descriptionFileName setState {description.xml}
DemoMaker fire
DemoMaker setViewerMask 16383
DemoMaker select
DemoMaker setPickable 1

set hideNewModules 0
create HxDisplaySurface {SurfaceView}
SurfaceView setIconPosition 330 77
SurfaceView data connect reg005.surf
SurfaceView colormap setDefaultColor 1 0.1 0.1
SurfaceView colormap setDefaultAlpha 0.500000
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
SurfaceView Patch setMinMax 0 49
SurfaceView Patch setButtons 1
SurfaceView Patch setIncrement 1
SurfaceView Patch setValue 0
SurfaceView Patch setSubMinMax 0 49
SurfaceView BoundaryId setIndex 0 -1
SurfaceView materials setIndex 0 4
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
{SurfaceView} selectTriangles zab HIJMGDGABIAFKDGABEIMICFBDABMMBPPPPHPIAHIBEAMAFEAFJEMNHDHFAKCPLBPDIKNIANMCAEPLGDLPOADFNMAEILBDPIAOGDMGAGAGAKGICDJKDIAHOIAIDAMDNMACIPOABKEPIHBMIFCOCBMJCNMEAEKNOADAAEHKOMGNB
SurfaceView fire
SurfaceView setViewerMask 254
SurfaceView setShadowStyle 0
SurfaceView setPickable 1

set hideNewModules 0


viewer 0 setCameraOrientation 0.970638 0.0886327 0.22362 1.16014
viewer 0 setCameraPosition 44.1818 -61.0237 70.2967
viewer 0 setCameraFocalDistance 93.8754
viewer 0 setCameraNearDistance 63.7457
viewer 0 setCameraFarDistance 124.065
viewer 0 setCameraType perspective
viewer 0 setCameraHeightAngle 44.9023
viewer 0 setAutoRedraw 1
viewer 0 redraw

