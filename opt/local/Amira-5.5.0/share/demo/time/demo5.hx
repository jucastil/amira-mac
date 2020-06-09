# Amira Script
remove -all
remove physics.icol Scalarfield Result Duplicate Duplicate2 Arithmetic Isosurface ObliqueSlice EmptyPlane Isolines TransformAnimation TransformAnimation2 TransformAnimation3

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

set hideNewModules 0
create HxAnnaScalarField3 {Scalarfield}
Scalarfield setIconPosition 20 10
Scalarfield fire
Scalarfield expr setState {0.5*x*x + y*y + z*z}
Scalarfield fire
Scalarfield setViewerMask 16383

set hideNewModules 0
create HxArithmetic {Arithmetic}
Arithmetic setIconPosition 160 10
Arithmetic inputA connect Scalarfield
Arithmetic fire
Arithmetic resultChannels setValue 0 0
Arithmetic expr0 setState A
Arithmetic expr1 setState 0
Arithmetic expr2 setState 0
Arithmetic expr3 setState 0
Arithmetic expr4 setState 0
Arithmetic expr5 setState 0
Arithmetic resultType setValue 1
Arithmetic resolution setMinMax 0 1 1024
Arithmetic resolution setValue 0 64
Arithmetic resolution setMinMax 1 1 1024
Arithmetic resolution setValue 1 64
Arithmetic resolution setMinMax 2 1 1024
Arithmetic resolution setValue 2 64
Arithmetic minBox setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
Arithmetic minBox setValue 0 -1
Arithmetic minBox setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
Arithmetic minBox setValue 1 -1
Arithmetic minBox setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
Arithmetic minBox setValue 2 -1
Arithmetic maxBox setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
Arithmetic maxBox setValue 0 1
Arithmetic maxBox setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
Arithmetic maxBox setValue 1 1
Arithmetic maxBox setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
Arithmetic maxBox setValue 2 1
Arithmetic fire
Arithmetic setViewerMask 16383

set hideNewModules 0
[ {Arithmetic} create
 ] setLabel {Result}
Result setIconPosition 20 40
Result master connect Arithmetic
Result fire
Result setTransform 1 0 0 0 0 1 0 0 0 0 1 0 0 0 -10 1
Result fire
Result setViewerMask 16383

set hideNewModules 0
create HxAnnaScalarField3 {Duplicate}
Duplicate setIconPosition 20 70
Duplicate inputA connect Result
Duplicate fire
Duplicate expr setState a
Duplicate setTransform 1 0 0 0 0 1 0 0 0 0 1 0 0 0 -10 1
Duplicate fire
Duplicate setViewerMask 16383

set hideNewModules 0
create HxAnnaScalarField3 {Duplicate2}
Duplicate2 setIconPosition 20 100
Duplicate2 inputA connect Result
Duplicate2 fire
Duplicate2 expr setState a
Duplicate2 setTransform 1 0 0 0 0 1 0 0 0 0 1 0 0 0 -10 1
Duplicate2 fire
Duplicate2 setViewerMask 16383

set hideNewModules 0
create HxIsosurface {Isosurface}
Isosurface setIconPosition 382 40
Isosurface data connect Result
Isosurface colormap setDefaultColor 1 0.8 0.4
Isosurface colormap setDefaultAlpha 0.500000
Isosurface fire
Isosurface drawStyle setValue 1
Isosurface drawStyle setSpecularLighting 1
Isosurface drawStyle setTexture 0
Isosurface drawStyle setAlphaMode 1
Isosurface drawStyle setNormalBinding 1
Isosurface drawStyle setCullingMode 0
Isosurface drawStyle setSortingMode 1
Isosurface textureWrap setValue 0 1
Isosurface threshold setMinMax 0.00062988162972033 2.5
Isosurface threshold setButtons 0
Isosurface threshold setIncrement 0.166625
Isosurface threshold setValue 0.5
Isosurface threshold setSubMinMax 0.00062988162972033 2.5
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
create HxObliqueSlice {ObliqueSlice}
ObliqueSlice setIconPosition 373 70
ObliqueSlice data connect Duplicate
{ObliqueSlice} fire
ObliqueSlice data connect Duplicate
ObliqueSlice colormap setDefaultColor 1 0.8 0.5
ObliqueSlice colormap setDefaultAlpha 0.500000
ObliqueSlice colormap connect physics.icol
ObliqueSlice fire
ObliqueSlice options setValue 0 0
ObliqueSlice options setValue 1 0
ObliqueSlice options setValue 2 1
ObliqueSlice options setValue 3 0
ObliqueSlice options setValue 4 0
ObliqueSlice mappingType setValue 0 2
ObliqueSlice linearRange setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
ObliqueSlice linearRange setValue 0 -200
ObliqueSlice linearRange setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
ObliqueSlice linearRange setValue 1 200
ObliqueSlice contrastLimit setMinMax 0 0 99
ObliqueSlice contrastLimit setValue 0 7
ObliqueSlice translate setMinMax 0 100
ObliqueSlice translate setButtons 1
ObliqueSlice translate setIncrement 1
ObliqueSlice translate setValue 50
ObliqueSlice translate setSubMinMax 0 100
ObliqueSlice sampling setState item 0 1 item 1 0 item 2 0 
ObliqueSlice overlayType setValue 0 0
ObliqueSlice transparency setValue 0
ObliqueSlice orientation untouch
ObliqueSlice setPlane 0 0 0 1 0 0 0 1 0
ObliqueSlice fire
ObliqueSlice setViewerMask 16383

set hideNewModules 0
create HxArbitraryCut {EmptyPlane}
EmptyPlane setIconPosition 376 100
EmptyPlane data connect Duplicate2
EmptyPlane fire
EmptyPlane options setValue 0 0
EmptyPlane options setValue 1 0
EmptyPlane options setValue 2 1
EmptyPlane options setValue 3 0
EmptyPlane translate setMinMax 0 100
EmptyPlane translate setButtons 1
EmptyPlane translate setIncrement 1
EmptyPlane translate setValue 50
EmptyPlane translate setSubMinMax 0 100
EmptyPlane orientation untouch
EmptyPlane setPlane 0 0 0 1 0 0 0 1 0
EmptyPlane fire
EmptyPlane setViewerMask 16383

set hideNewModules 0
create HxIsolines {Isolines}
Isolines setIconPosition 376 120
Isolines data connect Duplicate2
Isolines module connect EmptyPlane
Isolines colormap setDefaultColor 1 0 0
Isolines colormap setDefaultAlpha 0.500000
Isolines fire
Isolines spacing setValue 0
Isolines uniform setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
Isolines uniform setValue 0 0.100000001490116
Isolines uniform setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
Isolines uniform setValue 1 1
Isolines uniform setMinMax 2 1 200
Isolines uniform setValue 2 3
Isolines explicit setState {0.52551 1.52538}
Isolines parameters setMinMax 0 16 4096
Isolines parameters setValue 0 128
Isolines parameters setMinMax 1 0 10
Isolines parameters setValue 1 2
Isolines options setValue 0 0
Isolines options setValue 1 0
Isolines fire
Isolines setViewerMask 16383

set hideNewModules 0
create HxObjectTransformAnimation {TransformAnimation}
TransformAnimation setIconPosition 160 40
TransformAnimation setIgnoreKeyListChange 1
TransformAnimation setNumInputs 2
TransformAnimation appendTransform 2 1 "Object Size"
TransformAnimation appendTransform 0 2 "Local Object Rotation"
TransformAnimation appendTransform 1 3 "Local Object Translation"
TransformAnimation appendTransform 1 4 "Depth (z-Slider) and up/down (y-Slider) on Screen"
TransformAnimation appendTransform 0 5 "Position on Screen"
TransformAnimation setEditMode 1
TransformAnimation setAnimationDump 0
TransformAnimation spatialData1 connect Result
TransformAnimation time setMinMax 0 1
TransformAnimation time setSubMinMax 0 1
TransformAnimation time setValue 0
TransformAnimation time setDiscrete 0
TransformAnimation time setIncrement 0.01
TransformAnimation time animationMode -once
TransformAnimation fire
TransformAnimation mode setState 
TransformAnimation animationKeys setValue 0 0
TransformAnimation animationActions setState item 1 0 
TransformAnimation edit1 setState item 2 0 
TransformAnimation scale1 setMinMax 0.00100000004749745 10
TransformAnimation scale1 setButtons 0
TransformAnimation scale1 setIncrement 0.6666
TransformAnimation scale1 setValue 1
TransformAnimation scale1 setSubMinMax 0.00100000004749745 10
TransformAnimation edit2 setState item 2 0 
TransformAnimation degree2 setMinMax -360 360
TransformAnimation degree2 setButtons 0
TransformAnimation degree2 setIncrement 24
TransformAnimation degree2 setValue 0
TransformAnimation degree2 setSubMinMax -360 360
TransformAnimation axis2 setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
TransformAnimation axis2 setValue 0 0
TransformAnimation axis2 setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
TransformAnimation axis2 setValue 1 1
TransformAnimation axis2 setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
TransformAnimation axis2 setValue 2 0
TransformAnimation edit3 setState item 2 0 
TransformAnimation translateX3 setMinMax -10 10
TransformAnimation translateX3 setButtons 0
TransformAnimation translateX3 setIncrement 1.33333
TransformAnimation translateX3 setValue 0
TransformAnimation translateX3 setSubMinMax -10 10
TransformAnimation translateY3 setMinMax -10 10
TransformAnimation translateY3 setButtons 0
TransformAnimation translateY3 setIncrement 1.33333
TransformAnimation translateY3 setValue 0
TransformAnimation translateY3 setSubMinMax -10 10
TransformAnimation translateZ3 setMinMax -10 10
TransformAnimation translateZ3 setButtons 0
TransformAnimation translateZ3 setIncrement 1.33333
TransformAnimation translateZ3 setValue 0
TransformAnimation translateZ3 setSubMinMax -10 10
TransformAnimation edit4 setState item 2 0 
TransformAnimation translateX4 setMinMax -10 10
TransformAnimation translateX4 setButtons 0
TransformAnimation translateX4 setIncrement 1.33333
TransformAnimation translateX4 setValue 0
TransformAnimation translateX4 setSubMinMax -10 10
TransformAnimation translateY4 setMinMax -10 10
TransformAnimation translateY4 setButtons 0
TransformAnimation translateY4 setIncrement 1.33333
TransformAnimation translateY4 setValue 0
TransformAnimation translateY4 setSubMinMax -10 10
TransformAnimation translateZ4 setMinMax -10 10
TransformAnimation translateZ4 setButtons 0
TransformAnimation translateZ4 setIncrement 1.33333
TransformAnimation translateZ4 setValue -10
TransformAnimation translateZ4 setSubMinMax -10 10
TransformAnimation edit5 setState item 2 0 
TransformAnimation degree5 setMinMax -180 180
TransformAnimation degree5 setButtons 0
TransformAnimation degree5 setIncrement 24
TransformAnimation degree5 setValue 0
TransformAnimation degree5 setSubMinMax -180 180
TransformAnimation axis5 setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
TransformAnimation axis5 setValue 0 0
TransformAnimation axis5 setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
TransformAnimation axis5 setValue 1 1
TransformAnimation axis5 setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
TransformAnimation axis5 setValue 2 0
TransformAnimation addNewTransform setState item 0 0 item 3 0 
TransformAnimation fire
TransformAnimation setIgnoreKeyListChange 0
TransformAnimation fire
TransformAnimation setViewerMask 16383

set hideNewModules 0
create HxObjectTransformAnimation {TransformAnimation2}
TransformAnimation2 setIconPosition 160 70
TransformAnimation2 setIgnoreKeyListChange 1
TransformAnimation2 setNumInputs 2
TransformAnimation2 appendTransform 2 1 "Object Size"
TransformAnimation2 appendTransform 0 2 "Local Object Rotation"
TransformAnimation2 appendTransform 1 3 "Local Object Translation"
TransformAnimation2 appendTransform 1 4 "Depth (z-Slider) and up/down (y-Slider) on Screen"
TransformAnimation2 appendTransform 0 5 "Position on Screen"
TransformAnimation2 setEditMode 1
TransformAnimation2 setAnimationDump 2 15 0 1 0 1 0 0 0 0 0 0 0 -10 0 1 0 0 1 1 0 1 0 0 0 0 0 0 0 -10 0 1 0 -25
TransformAnimation2 spatialData1 connect Duplicate
TransformAnimation2 time setMinMax 0 1
TransformAnimation2 time setSubMinMax 0 1
TransformAnimation2 time setValue 0
TransformAnimation2 time setDiscrete 0
TransformAnimation2 time setIncrement 0.01
TransformAnimation2 time animationMode -once
TransformAnimation2 fire
TransformAnimation2 mode setState 
TransformAnimation2 animationKeys setValue 0 1
TransformAnimation2 animationActions setState item 1 0 
TransformAnimation2 edit1 setState item 2 0 
TransformAnimation2 scale1 setMinMax 0.00100000004749745 10
TransformAnimation2 scale1 setButtons 0
TransformAnimation2 scale1 setIncrement 0.6666
TransformAnimation2 scale1 setValue 1
TransformAnimation2 scale1 setSubMinMax 0.00100000004749745 10
TransformAnimation2 edit2 setState item 2 0 
TransformAnimation2 degree2 setMinMax -360 360
TransformAnimation2 degree2 setButtons 0
TransformAnimation2 degree2 setIncrement 24
TransformAnimation2 degree2 setValue 0
TransformAnimation2 degree2 setSubMinMax -360 360
TransformAnimation2 axis2 setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
TransformAnimation2 axis2 setValue 0 0
TransformAnimation2 axis2 setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
TransformAnimation2 axis2 setValue 1 1
TransformAnimation2 axis2 setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
TransformAnimation2 axis2 setValue 2 0
TransformAnimation2 edit3 setState item 2 0 
TransformAnimation2 translateX3 setMinMax -10 10
TransformAnimation2 translateX3 setButtons 0
TransformAnimation2 translateX3 setIncrement 1.33333
TransformAnimation2 translateX3 setValue 0
TransformAnimation2 translateX3 setSubMinMax -10 10
TransformAnimation2 translateY3 setMinMax -10 10
TransformAnimation2 translateY3 setButtons 0
TransformAnimation2 translateY3 setIncrement 1.33333
TransformAnimation2 translateY3 setValue 0
TransformAnimation2 translateY3 setSubMinMax -10 10
TransformAnimation2 translateZ3 setMinMax -10 10
TransformAnimation2 translateZ3 setButtons 0
TransformAnimation2 translateZ3 setIncrement 1.33333
TransformAnimation2 translateZ3 setValue 0
TransformAnimation2 translateZ3 setSubMinMax -10 10
TransformAnimation2 edit4 setState item 2 0 
TransformAnimation2 translateX4 setMinMax -10 10
TransformAnimation2 translateX4 setButtons 0
TransformAnimation2 translateX4 setIncrement 1.33333
TransformAnimation2 translateX4 setValue 0
TransformAnimation2 translateX4 setSubMinMax -10 10
TransformAnimation2 translateY4 setMinMax -10 10
TransformAnimation2 translateY4 setButtons 0
TransformAnimation2 translateY4 setIncrement 1.33333
TransformAnimation2 translateY4 setValue 0
TransformAnimation2 translateY4 setSubMinMax -10 10
TransformAnimation2 translateZ4 setMinMax -10 10
TransformAnimation2 translateZ4 setButtons 0
TransformAnimation2 translateZ4 setIncrement 1.33333
TransformAnimation2 translateZ4 setValue -10
TransformAnimation2 translateZ4 setSubMinMax -10 10
TransformAnimation2 edit5 setState item 2 0 
TransformAnimation2 degree5 setMinMax -180 180
TransformAnimation2 degree5 setButtons 0
TransformAnimation2 degree5 setIncrement 24
TransformAnimation2 degree5 setValue 0
TransformAnimation2 degree5 setSubMinMax -180 180
TransformAnimation2 axis5 setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
TransformAnimation2 axis5 setValue 0 0
TransformAnimation2 axis5 setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
TransformAnimation2 axis5 setValue 1 1
TransformAnimation2 axis5 setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
TransformAnimation2 axis5 setValue 2 0
TransformAnimation2 addNewTransform setState item 0 0 item 3 0 
TransformAnimation2 fire
TransformAnimation2 setIgnoreKeyListChange 0
TransformAnimation2 fire
TransformAnimation2 setViewerMask 16383
TransformAnimation2 select
TransformAnimation2 time setPin 1
TransformAnimation2 deselect

set hideNewModules 0
create HxObjectTransformAnimation {TransformAnimation3}
TransformAnimation3 setIconPosition 160 100
TransformAnimation3 setIgnoreKeyListChange 1
TransformAnimation3 setNumInputs 2
TransformAnimation3 appendTransform 2 1 "Object Size"
TransformAnimation3 appendTransform 0 2 "Local Object Rotation"
TransformAnimation3 appendTransform 1 3 "Local Object Translation"
TransformAnimation3 appendTransform 1 4 "Depth (z-Slider) and up/down (y-Slider) on Screen"
TransformAnimation3 appendTransform 0 5 "Position on Screen"
TransformAnimation3 setEditMode 1
TransformAnimation3 setAnimationDump 2 15 0 1 0 1 0 0 0 0 0 0 0 -10 0 1 0 0 1 1 0 1 0 0 0 0 0 0 0 -10 0 1 0 25
TransformAnimation3 spatialData1 connect Duplicate2
TransformAnimation3 time connect TransformAnimation2
TransformAnimation3 time setMinMax 0 1
TransformAnimation3 time setSubMinMax 0 1
TransformAnimation3 time setValue 0
TransformAnimation3 time setDiscrete 0
TransformAnimation3 time setIncrement 0.01
TransformAnimation3 time animationMode -once
TransformAnimation3 fire
TransformAnimation3 mode setState 
TransformAnimation3 animationKeys setValue 0 1
TransformAnimation3 animationActions setState item 1 0 
TransformAnimation3 edit1 setState item 2 0 
TransformAnimation3 scale1 setMinMax 0.00100000004749745 10
TransformAnimation3 scale1 setButtons 0
TransformAnimation3 scale1 setIncrement 0.6666
TransformAnimation3 scale1 setValue 1
TransformAnimation3 scale1 setSubMinMax 0.00100000004749745 10
TransformAnimation3 edit2 setState item 2 0 
TransformAnimation3 degree2 setMinMax -360 360
TransformAnimation3 degree2 setButtons 0
TransformAnimation3 degree2 setIncrement 24
TransformAnimation3 degree2 setValue 0
TransformAnimation3 degree2 setSubMinMax -360 360
TransformAnimation3 axis2 setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
TransformAnimation3 axis2 setValue 0 0
TransformAnimation3 axis2 setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
TransformAnimation3 axis2 setValue 1 1
TransformAnimation3 axis2 setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
TransformAnimation3 axis2 setValue 2 0
TransformAnimation3 edit3 setState item 2 0 
TransformAnimation3 translateX3 setMinMax -10 10
TransformAnimation3 translateX3 setButtons 0
TransformAnimation3 translateX3 setIncrement 1.33333
TransformAnimation3 translateX3 setValue 0
TransformAnimation3 translateX3 setSubMinMax -10 10
TransformAnimation3 translateY3 setMinMax -10 10
TransformAnimation3 translateY3 setButtons 0
TransformAnimation3 translateY3 setIncrement 1.33333
TransformAnimation3 translateY3 setValue 0
TransformAnimation3 translateY3 setSubMinMax -10 10
TransformAnimation3 translateZ3 setMinMax -10 10
TransformAnimation3 translateZ3 setButtons 0
TransformAnimation3 translateZ3 setIncrement 1.33333
TransformAnimation3 translateZ3 setValue 0
TransformAnimation3 translateZ3 setSubMinMax -10 10
TransformAnimation3 edit4 setState item 2 0 
TransformAnimation3 translateX4 setMinMax -10 10
TransformAnimation3 translateX4 setButtons 0
TransformAnimation3 translateX4 setIncrement 1.33333
TransformAnimation3 translateX4 setValue 0
TransformAnimation3 translateX4 setSubMinMax -10 10
TransformAnimation3 translateY4 setMinMax -10 10
TransformAnimation3 translateY4 setButtons 0
TransformAnimation3 translateY4 setIncrement 1.33333
TransformAnimation3 translateY4 setValue 0
TransformAnimation3 translateY4 setSubMinMax -10 10
TransformAnimation3 translateZ4 setMinMax -10 10
TransformAnimation3 translateZ4 setButtons 0
TransformAnimation3 translateZ4 setIncrement 1.33333
TransformAnimation3 translateZ4 setValue -10
TransformAnimation3 translateZ4 setSubMinMax -10 10
TransformAnimation3 edit5 setState item 2 0 
TransformAnimation3 degree5 setMinMax -180 180
TransformAnimation3 degree5 setButtons 0
TransformAnimation3 degree5 setIncrement 24
TransformAnimation3 degree5 setValue 0
TransformAnimation3 degree5 setSubMinMax -180 180
TransformAnimation3 axis5 setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
TransformAnimation3 axis5 setValue 0 0
TransformAnimation3 axis5 setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
TransformAnimation3 axis5 setValue 1 1
TransformAnimation3 axis5 setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
TransformAnimation3 axis5 setValue 2 0
TransformAnimation3 addNewTransform setState item 0 0 item 3 0 
TransformAnimation3 fire
TransformAnimation3 setIgnoreKeyListChange 0
TransformAnimation3 fire
TransformAnimation3 setViewerMask 16383

set hideNewModules 0


viewer 0 setCameraOrientation 0.0353622 0.139612 -0.989575 3.13471
viewer 0 setCameraPosition -0.890837 -3.56766 2.69188
viewer 0 setCameraFocalDistance 12.9004
viewer 0 setCameraNearDistance 12.1784
viewer 0 setCameraFarDistance 14.2507
viewer 0 setCameraType perspective
viewer 0 setCameraHeightAngle 44.9023
viewer 0 setAutoRedraw 1
viewer 0 redraw
