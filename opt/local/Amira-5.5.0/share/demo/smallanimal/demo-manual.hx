# Amira Script
remove -all
remove physics.icol glow.col grey.am volrenGlow.am mouseCTdata.am tumorCTdata.am vascularNetwork-SG.am CameraRotate Volren Volren2 ProjectionView SpatialGraphView

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
CameraRotate time setValue 360
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
create HxVolren {Volren}
Volren setIconPosition 295 10
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
create HxVolren {Volren2}
Volren2 setIconPosition 289 70
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
Volren2 alphaScale0 setValue 0.558824
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
Volren2 setViewerMask 16382
Volren2 setPickable 1

set hideNewModules 0
create HxProjectionView {ProjectionView}
ProjectionView setIconPosition 254 40
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
SpatialGraphView setIconPosition 241 100
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
SpatialGraphView setViewerMask 255
SpatialGraphView setPickable 1

set hideNewModules 0

proc onKeyF2 { } {
   Volren2 setViewerMask 16383
   Volren color0 setMinMax 650 1880
   Volren fire
}


proc onKeyF3 { } {
   ProjectionView setViewerMask 16382
   Volren setViewerMask 16382
   viewer 0 viewAll
}

proc onKeyF4 { } {
   CameraRotate action setValue 0 1
   CameraRotate time play -backward
}


viewer 0 setCameraOrientation 0.136947 -0.609791 -0.780641 2.81732
viewer 0 setCameraPosition -23.6674 46.3143 12.2586
viewer 0 setCameraFocalDistance 59.4296
viewer 0 setCameraNearDistance 39.6845
viewer 0 setCameraFarDistance 78.4448
viewer 0 setCameraType perspective
viewer 0 setCameraHeightAngle 44.9023
viewer 0 setAutoRedraw 1
viewer 0 redraw

