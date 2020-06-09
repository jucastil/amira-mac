# Amira Script
remove -all
remove physics.icol glow.col grey.am volrenGlow.am mouseCTdata.am tumorCTdata.am vascularNetwork-SG.am CameraRotate CameraPath.civ Volren DemoMaker Volren2 ProjectionView SpatialGraphView OrthoSlice Annotation

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
{physics.icol} setMinMax 0.03 0.353062
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
[ load ${AMIRA_ROOT}/data/colormaps/glow.col ] setLabel glow.col
glow.col setIconPosition 0 0
glow.col setNoRemoveAll 1
glow.col fire
{glow.col} setMinMax 0 255
glow.col flags setValue 1
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
glow.col setViewerMask 16383

set hideNewModules 1
[ load ${AMIRA_ROOT}/data/colormaps/grey.am ] setLabel grey.am
grey.am setIconPosition 0 0
grey.am setNoRemoveAll 1
grey.am fire
{grey.am} setMinMax -200 685
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

set hideNewModules 1
[ load ${AMIRA_ROOT}/data/colormaps/volrenGlow.am ] setLabel volrenGlow.am
volrenGlow.am setIconPosition 0 0
volrenGlow.am setNoRemoveAll 1
volrenGlow.am fire
{volrenGlow.am} setMinMax 250 430
volrenGlow.am flags setValue 1
volrenGlow.am shift setMinMax -1 1
volrenGlow.am shift setButtons 0
volrenGlow.am shift setIncrement 0.133333
volrenGlow.am shift setValue 0
volrenGlow.am shift setSubMinMax -1 1
volrenGlow.am scale setMinMax 0 1
volrenGlow.am scale setButtons 0
volrenGlow.am scale setIncrement 0.1
volrenGlow.am scale setValue 1
volrenGlow.am scale setSubMinMax 0 1
volrenGlow.am fire
volrenGlow.am setViewerMask 16383

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/smallanimal/mouseCTdata.am ] setLabel mouseCTdata.am
mouseCTdata.am setIconPosition 20 10
mouseCTdata.am fire
mouseCTdata.am setViewerMask 16383

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/smallanimal/tumorCTdata.am ] setLabel tumorCTdata.am
tumorCTdata.am setIconPosition 20 40
tumorCTdata.am fire
tumorCTdata.am setViewerMask 16383

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/smallanimal/vascularNetwork-SG.am ] setLabel vascularNetwork-SG.am
vascularNetwork-SG.am setIconPosition 20 70
vascularNetwork-SG.am fire
vascularNetwork-SG.am setViewerMask 16383

set hideNewModules 0
create HxCircularCameraPath {CameraRotate}
CameraRotate setIconPosition 20 100
CameraRotate time setMinMax 0 360
CameraRotate time setSubMinMax 0 360
CameraRotate time setValue 0
CameraRotate time setDiscrete 0
CameraRotate time setIncrement 1
CameraRotate time animationMode -once
CameraRotate fire
CameraRotate action setOptValue 0 0
CameraRotate setPosition -23.6674 46.3143 12.2586
CameraRotate setAimPoint 0.254784 -6.19849 -1.95449
CameraRotate setUpDirection 0.0860594 -0.223575 0.97088
CameraRotate setAxis 0 0 1
CameraRotate fire
CameraRotate setViewerMask 16383

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/smallanimal/CameraPath.civ ] setLabel CameraPath.civ
CameraPath.civ setIconPosition 20 130
CameraPath.civ time setMinMax 0 10
CameraPath.civ time setSubMinMax 0 10
CameraPath.civ time setValue 0
CameraPath.civ time setDiscrete 0
CameraPath.civ time setIncrement 0.5
CameraPath.civ time animationMode -once
CameraPath.civ fire
CameraPath.civ setViewerMask 16383

set hideNewModules 0
create HxVolren {Volren}
Volren setIconPosition 297 10
Volren data connect mouseCTdata.am
Volren color0 setDefaultColor 0.137 0.941 0.089
Volren color0 setDefaultAlpha 0.500000
Volren color0 setLocalRange 0
Volren color0 connect grey.am
Volren fire
Volren tabs setValue 0
Volren options0 setState 
Volren alphaScale0 setMinMax 0 1
Volren alphaScale0 setButtons 0
Volren alphaScale0 setIncrement 0.1
Volren alphaScale0 setValue 1
Volren alphaScale0 setSubMinMax 0 1
Volren commonMode setState item 0 0 item 1 0 
Volren commonOptions setValue 0 0
Volren commonOptions setToggleVisible 0 1
Volren commonDRRGamma setMinMax 0 10
Volren commonDRRGamma setButtons 0
Volren commonDRRGamma setIncrement 0.666667
Volren commonDRRGamma setValue 1
Volren commonDRRGamma setSubMinMax 0 10
Volren shading setValue 2
Volren coefficients setState item 0 0.3 item 1 0.6 item 2 0.7 color 666 1 1 1 
Volren lightAngle setValue 0
Volren shadingLightAngleYaw setMinMax -1 1
Volren shadingLightAngleYaw setButtons 0
Volren shadingLightAngleYaw setIncrement 0.133333
Volren shadingLightAngleYaw setValue 0
Volren shadingLightAngleYaw setSubMinMax -1 1
Volren shadingLightAnglePitch setMinMax -0.5 0.5
Volren shadingLightAnglePitch setButtons 0
Volren shadingLightAnglePitch setIncrement 0.0666667
Volren shadingLightAnglePitch setValue 0
Volren shadingLightAnglePitch setSubMinMax -0.5 0.5
Volren defaultMaterial setState item 0 1 item 1 0 color 2 1 1 1 item 3 0 item 4 0 
Volren fire
Volren setViewerMask 16383
Volren setPickable 1

set hideNewModules 0
create HxScriptObject {DemoMaker}
{DemoMaker} script setValue ${AMIRA_ROOT}/share/script-objects/DemoMaker.scro
DemoMaker setIconPosition 160 10
{DemoMaker} setVar {scroTypeDemoMaker} {1}
{DemoMaker} setVar {isInitialized} {0}
{DemoMaker} setVar {isDemoMakerActive} {1}
{DemoMaker} setVar {funcKeysDefined} {1}
{DemoMaker} setVar {atEndCallback} {}
{DemoMaker} setVar {internalEventList} {dummy {numeric {{OrthoSlice/Slice Number} 168} 0 15 0 299 -1e24 1e24 {OrthoSlice sliceNumber setValue %0%; OrthoSlice fire}} {numeric {CameraRotate/Time 170} 2.5 15 0 360 -1e24 1e24 {CameraRotate time setValue %0%; CameraRotate fire}} {numeric {Volren/Color/max 131} 7.52471 27.5247 685 1880 -1e24 1e24 {Volren color0 setMinMax [Volren color0 getMinValue] %0%; Volren fire}} {numeric {Volren/Color/min 132} 7.52471 27.5247 -200 650 -1e24 1e24 {Volren color0 setMinMax %0% [Volren color0 getMaxValue]; Volren fire}} {numeric {Volren2/AlphaScale 143} 20.2151 32.5 0 1 -1e24 1e24 {Volren2 alphaScale0 setValue %0%; Volren2 fire}} {numeric {Volren2/AlphaScale 144} 32.5 42.5 1 0 -1e24 1e24 {Volren2 alphaScale0 setValue %0%; Volren2 fire}} {toggle {{SpatialGraphView/Viewer mask/Viewer 0} 146} 32.5404 1 {SpatialGraphView setViewerMask [expr ([SpatialGraphView getViewerMask]&254)+%0%*1]}} {break {{Break (continue on keystroke)} 151} 42.5} {toggle {{Annotation/Viewer mask/Viewer 0} 155} 42.5501 1 {Annotation setViewerMask [expr ([Annotation getViewerMask]&254)+%0%*1]}} {numeric {CameraPath.civ/Time 154} 42.6 48.75 0 10 -1e24 1e24 {CameraPath.civ time setValue %0%; CameraPath.civ fire}} {toggle {{Annotation/Viewer mask/Viewer 0} 166} 42.7 0 {Annotation setViewerMask [expr ([Annotation getViewerMask]&254)+%0%*1]}}}
{DemoMaker} setVar {lastStartTime} {2.5}
{DemoMaker} setVar {lastEndTime} {15}
{DemoMaker} setVar {lastTimeStep} {0}
{DemoMaker} setVar {eventIdCount} {171}
{DemoMaker} setVar {myNamespace} {DemoMaker1}
{DemoMaker} setVar {lengthOfNewEvents} {5.13851}
{DemoMaker} setVar {CustomHelp} {HxDemoDirector.html}
DemoMaker fire
DemoMaker time setMinMax 0 48.75
DemoMaker time setSubMinMax 0 48.75
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
DemoMaker moreOpt1 setValue 0 1
DemoMaker moreOpt1 setToggleVisible 0 1
DemoMaker moreOpt1 setValue 1 1
DemoMaker moreOpt1 setToggleVisible 1 1
DemoMaker moreOpt2 setValue 0 1
DemoMaker moreOpt2 setToggleVisible 0 1
DemoMaker moreOpt2 setValue 1 0
DemoMaker moreOpt2 setToggleVisible 1 1
DemoMaker moreOpt2 setValue 2 0
DemoMaker moreOpt2 setToggleVisible 2 1
DemoMaker eventListFile setState {C:/Program Files/Amira 5.4.0/share/script-objects/event_list.txt}
DemoMaker waitImg setState {C:/Program Files/Amira 5.4.0/share/script-objects/img/amira_150_red.png}
DemoMaker moveFrom setMinMax 0 -3.40282346638529e+038 3.40282346638529e+038
DemoMaker moveFrom setValue 0 0
DemoMaker moveFrom setMinMax 1 -3.40282346638529e+038 3.40282346638529e+038
DemoMaker moveFrom setValue 1 0
DemoMaker moveTo setMinMax 0 -3.40282346638529e+038 3.40282346638529e+038
DemoMaker moveTo setValue 0 0
DemoMaker moveTo setMinMax 1 -3.40282346638529e+038 3.40282346638529e+038
DemoMaker moveTo setValue 1 0
DemoMaker guiElements setOptValue 0 18
DemoMaker command setState {echo "%0% %1% %2%"}
DemoMaker startEndValue setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
DemoMaker startEndValue setValue 0 0
DemoMaker startEndValue setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
DemoMaker startEndValue setValue 1 360
DemoMaker startVector setState {0 0 0}
DemoMaker endVector setState {1 1 1}
DemoMaker toggleValue setValue 0
DemoMaker selectValue setIndex 0 -1
DemoMaker selectValue setIndex 1 -1
DemoMaker triggerTime setMinMax 0 -10000000000 10000000000
DemoMaker triggerTime setValue 0 27.5
DemoMaker modifKeys setValue 0 0
DemoMaker modifKeys setToggleVisible 0 1
DemoMaker modifKeys setValue 1 0
DemoMaker modifKeys setToggleVisible 1 1
DemoMaker modifKeys setValue 2 0
DemoMaker modifKeys setToggleVisible 2 1
DemoMaker waitingTime setMinMax 0 -3.40282346638529e+038 3.40282346638529e+038
DemoMaker waitingTime setValue 0 4.96867990493774
DemoMaker gotoTime setMinMax 0 -3.40282346638529e+038 3.40282346638529e+038
DemoMaker gotoTime setValue 0 19.97998046875
DemoMaker startEndTime setMinMax 0 -10000000000 10000000000
DemoMaker startEndTime setValue 0 2.5
DemoMaker startEndTime setMinMax 1 -10000000000 10000000000
DemoMaker startEndTime setValue 1 15
DemoMaker loadFile setState {}
DemoMaker loadOptions setValue 0 1
DemoMaker loadOptions setToggleVisible 0 1
DemoMaker startScro setIndex 0 -1
DemoMaker startTime setMinMax 0 -3.40282346638529e+038 3.40282346638529e+038
DemoMaker startTime setValue 0 0
DemoMaker descriptionFileName setState {description.xml}
DemoMaker fire
DemoMaker setViewerMask 16383
DemoMaker setPickable 1

set hideNewModules 0
create HxVolren {Volren2}
Volren2 setIconPosition 291 100
Volren2 data connect tumorCTdata.am
Volren2 color0 setDefaultColor 0.137 0.941 0.089
Volren2 color0 setDefaultAlpha 0.500000
Volren2 color0 setLocalRange 0
Volren2 color0 connect volrenGlow.am
Volren2 fire
Volren2 tabs setValue 0
Volren2 options0 setState 
Volren2 alphaScale0 setMinMax 0 1
Volren2 alphaScale0 setButtons 0
Volren2 alphaScale0 setIncrement 0.1
Volren2 alphaScale0 setValue 0
Volren2 alphaScale0 setSubMinMax 0 1
Volren2 commonMode setState item 0 0 item 1 0 
Volren2 commonOptions setValue 0 0
Volren2 commonOptions setToggleVisible 0 1
Volren2 commonDRRGamma setMinMax 0 10
Volren2 commonDRRGamma setButtons 0
Volren2 commonDRRGamma setIncrement 0.666667
Volren2 commonDRRGamma setValue 1
Volren2 commonDRRGamma setSubMinMax 0 10
Volren2 shading setValue 2
Volren2 coefficients setState item 0 0.3 item 1 0.6 item 2 0.7 color 666 1 1 1 
Volren2 lightAngle setValue 0
Volren2 shadingLightAngleYaw setMinMax -1 1
Volren2 shadingLightAngleYaw setButtons 0
Volren2 shadingLightAngleYaw setIncrement 0.133333
Volren2 shadingLightAngleYaw setValue 0
Volren2 shadingLightAngleYaw setSubMinMax -1 1
Volren2 shadingLightAnglePitch setMinMax -0.5 0.5
Volren2 shadingLightAnglePitch setButtons 0
Volren2 shadingLightAnglePitch setIncrement 0.0666667
Volren2 shadingLightAnglePitch setValue 0
Volren2 shadingLightAnglePitch setSubMinMax -0.5 0.5
Volren2 defaultMaterial setState item 0 1 item 1 0 color 2 1 1 1 item 3 0 item 4 0 
Volren2 fire
Volren2 setViewerMask 16383
Volren2 setPickable 1

set hideNewModules 0
create HxProjectionView {ProjectionView}
ProjectionView setIconPosition 256 40
ProjectionView data connect mouseCTdata.am
ProjectionView colormap setDefaultColor 1 0.8 0.5
ProjectionView colormap setDefaultAlpha 0.500000
ProjectionView colormap setLocalRange 0
ProjectionView colormap connect glow.col
ProjectionView fire
ProjectionView options setValue 0 0
ProjectionView options setToggleVisible 0 1
ProjectionView options setValue 1 1
ProjectionView options setToggleVisible 1 1
ProjectionView options setValue 2 0
ProjectionView options setToggleVisible 2 1
ProjectionView options setValue 3 0
ProjectionView options setToggleVisible 3 1
ProjectionView slices setValue 0 0
ProjectionView slices setToggleVisible 0 1
ProjectionView slices setValue 1 1
ProjectionView slices setToggleVisible 1 1
ProjectionView slices setValue 2 1
ProjectionView slices setToggleVisible 2 1
ProjectionView slices setValue 3 0
ProjectionView slices setToggleVisible 3 1
ProjectionView mapping setIndex 0 0
ProjectionView mapping setIndex 1 0
ProjectionView range setMinMax 0 -3.40282346638529e+038 3.40282346638529e+038
ProjectionView range setValue 0 -1000
ProjectionView range setMinMax 1 -3.40282346638529e+038 3.40282346638529e+038
ProjectionView range setValue 1 3000
ProjectionView contrastLimit setMinMax 0 -2147483648 2147483648
ProjectionView contrastLimit setValue 0 7
ProjectionView minimum setMinMax 0 0 224
ProjectionView minimum setValue 0 0
ProjectionView minimum setMinMax 1 0 179
ProjectionView minimum setValue 1 0
ProjectionView minimum setMinMax 2 0 299
ProjectionView minimum setValue 2 0
ProjectionView maximum setMinMax 0 0 224
ProjectionView maximum setValue 0 224
ProjectionView maximum setMinMax 1 0 179
ProjectionView maximum setValue 1 179
ProjectionView maximum setMinMax 2 0 299
ProjectionView maximum setValue 2 299
ProjectionView update snap 0 1
ProjectionView fire
ProjectionView setViewerMask 16383
ProjectionView setPickable 1

set hideNewModules 0
create HxSpatialGraphView {SpatialGraphView}
SpatialGraphView setIconPosition 243 130
SpatialGraphView data connect vascularNetwork-SG.am
SpatialGraphView nodeColormap setDefaultColor 1 0.8 0.5
SpatialGraphView nodeColormap setDefaultAlpha 0.500000
SpatialGraphView nodeColormap setLocalRange 0
SpatialGraphView nodeColormap connect physics.icol
SpatialGraphView segmentColormap setDefaultColor 1 0.8 0.5
SpatialGraphView segmentColormap setDefaultAlpha 0.500000
SpatialGraphView segmentColormap setLocalRange 0
SpatialGraphView segmentColormap connect physics.icol
SpatialGraphView fire
SpatialGraphView itemsToShow setValue 0 0
SpatialGraphView itemsToShow setToggleVisible 0 1
SpatialGraphView itemsToShow setValue 1 1
SpatialGraphView itemsToShow setToggleVisible 1 1
SpatialGraphView nodeScale setIndex 0 0
SpatialGraphView nodeScaleFactor setMinMax 0 10
SpatialGraphView nodeScaleFactor setButtons 0
SpatialGraphView nodeScaleFactor setIncrement 0.666667
SpatialGraphView nodeScaleFactor setValue 0.0852
SpatialGraphView nodeScaleFactor setSubMinMax 0 10
SpatialGraphView nodeColoring setIndex 0 0
SpatialGraphView nodeLabelColoringOptions setValue 0
SpatialGraphView nodeColor setColor 0 0.8 0.8 0.8
SpatialGraphView segmentStyle setValue 0 1
SpatialGraphView segmentStyle setToggleVisible 0 1
SpatialGraphView segmentStyle setValue 1 0
SpatialGraphView segmentStyle setToggleVisible 1 1
SpatialGraphView segmentStyle setValue 2 1
SpatialGraphView segmentStyle setToggleVisible 2 1
SpatialGraphView tubeScale setIndex 0 1
SpatialGraphView tubeScaleFactor setMinMax 0 10
SpatialGraphView tubeScaleFactor setButtons 0
SpatialGraphView tubeScaleFactor setIncrement 0.666667
SpatialGraphView tubeScaleFactor setValue 1.5
SpatialGraphView tubeScaleFactor setSubMinMax 0 10
SpatialGraphView segmentWidth setMinMax 0 10
SpatialGraphView segmentWidth setButtons 0
SpatialGraphView segmentWidth setIncrement 0.666667
SpatialGraphView segmentWidth setValue 1
SpatialGraphView segmentWidth setSubMinMax 0 10
SpatialGraphView segmentColoring setIndex 0 1
SpatialGraphView segmentLabelColoringOptions setValue 0
SpatialGraphView segmentColor setColor 0 0.8 0.8 0.8
{SpatialGraphView} setVisibility HIJMPLPPBPDHAAAAJEJFBLOF HIJMPLPPBPDLAAAACKPLBHOJ
SpatialGraphView fire
SpatialGraphView setViewerMask 254
SpatialGraphView setPickable 1

set hideNewModules 0
create HxOrthoSlice {OrthoSlice}
OrthoSlice setIconPosition 277 70
OrthoSlice data connect mouseCTdata.am
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
OrthoSlice origin  setValue 0 -0.0300002 -6.562 -17.97
OrthoSlice normal  setBoundingBox -1e+008 1e+008 -1e+008 1e+008 -1e+008 1e+008
OrthoSlice normal  setImmediate 0
OrthoSlice normal  setOrtho 0
OrthoSlice normal  showDragger 0
OrthoSlice normal  showPoints 0
OrthoSlice normal  setPointScale 1
OrthoSlice normal  showOptionButton 1
OrthoSlice normal  setNumPoints 1 1 1
OrthoSlice normal  setValue 0 0 0 1
OrthoSlice options setValue 0 0
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
OrthoSlice colormap setLocalMinMax -200.000000 200.000000
OrthoSlice colormap connect grey.am
OrthoSlice sliceNumber setMinMax 0 299
OrthoSlice sliceNumber setButtons 1
OrthoSlice sliceNumber setIncrement 1
OrthoSlice sliceNumber setValue 0
OrthoSlice sliceNumber setSubMinMax 0 299
OrthoSlice transparency setValue 0
OrthoSlice frameSettings setState item 0 1 item 2 1 color 3 1 0.5 0 
OrthoSlice fire

OrthoSlice fire
OrthoSlice setViewerMask 16382
OrthoSlice setShadowStyle 0
OrthoSlice setPickable 1

set hideNewModules 0
create HxAnnotation {Annotation}
Annotation setIconPosition 276 160
Annotation fire
Annotation background setState item 0 1 color 1 0.5 0.5 0.5 
Annotation postype setValue 1
Annotation position setMinMax 0 -2000 2000
Annotation position setValue 0 335
Annotation position setMinMax 1 -2000 2000
Annotation position setValue 1 -491
Annotation ndcposition setMinMax 0 -1 1
Annotation ndcposition setValue 0 0.0399999991059303
Annotation ndcposition setMinMax 1 -1 1
Annotation ndcposition setValue 1 -0.0399999991059303
Annotation text setState {Press F4 to continue!}
Annotation font setState name: {Helvetica} size: 20 bold: 1 italic: 0 color: 1 1 1
Annotation fire
Annotation setViewerMask 254
Annotation setPickable 1

set hideNewModules 0

Volren clipGeom OrthoSlice
Volren2 clipGeom OrthoSlice
SpatialGraphView clipGeom OrthoSlice

viewer 0 setCameraOrientation 0.136947 -0.609791 -0.780641 2.81732
viewer 0 setCameraPosition -23.6674 46.3143 12.2586
viewer 0 setCameraFocalDistance 59.4296
viewer 0 setCameraNearDistance 39.9333
viewer 0 setCameraFarDistance 78.4448
viewer 0 setCameraType perspective
viewer 0 setCameraHeightAngle 44.9023
viewer 0 setAutoRedraw 1
viewer 0 redraw

