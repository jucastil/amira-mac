# Amira Script
remove -all
remove lobus.am CameraRotate Isosurface

# Create viewers
viewer setVertical 0

viewer 0 setBackgroundMode 1
viewer 0 setTransparencyType 6
viewer 0 setAutoRedraw 0
viewer 0 show
mainWindow show

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/tutorials/lobus.am ] setLabel lobus.am
lobus.am setIconPosition 20 10
lobus.am fire
lobus.am fire
lobus.am setViewerMask 16383

set hideNewModules 0
create HxCircularCameraPath {CameraRotate}
CameraRotate setIconPosition 20 38
CameraRotate time setMinMax 0 360
CameraRotate time setSubMinMax 0 360
CameraRotate time setValue 0
CameraRotate time setDiscrete 0
CameraRotate time setIncrement 5
CameraRotate fire
CameraRotate action setOptValue 0 0
CameraRotate setPosition 102.891 106.811 -289.584
CameraRotate setAimPoint 102.891 106.81 70.849
CameraRotate setUpDirection 1.50996e-007 -1 -2.53518e-006
CameraRotate setAxis 0 -1 0
CameraRotate fire
CameraRotate setViewerMask 16383
CameraRotate select

set hideNewModules 0
create HxIsosurface {Isosurface}
Isosurface setIconPosition 215 10
Isosurface data connect lobus.am
Isosurface colormap setDefaultColor 1 0.8 0.4
Isosurface colormap setDefaultAlpha 0.500000
Isosurface fire
Isosurface drawStyle setValue 1
Isosurface drawStyle setTexture 0
Isosurface drawStyle setNormalBinding 1
Isosurface setCullingMode noCulling
Isosurface threshold setMinMax 22 254
Isosurface threshold setButtons 0
Isosurface threshold setIncrement 15.4667
Isosurface threshold setValue 70
Isosurface threshold setSubMinMax 22 254
Isosurface options setValue 0 1
Isosurface options setValue 1 0
Isosurface resolution setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
Isosurface resolution setValue 0 2
Isosurface resolution setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
Isosurface resolution setValue 1 2
Isosurface resolution setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
Isosurface resolution setValue 2 2
{Isosurface} doIt hit
Isosurface fire
Isosurface setViewerMask 16383

set hideNewModules 0


viewer 0 setCameraPosition 102.891 106.811 -289.584
viewer 0 setCameraOrientation -1 -7.54979e-008 0 3.14159
viewer 0 setCameraFocalDistance 360.433
viewer 0 setAutoRedraw 1
viewer 0 redraw
