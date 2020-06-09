# Amira Script
remove -all
remove Scalarfield Scalarfield2 Scalarfield3 Result Result2 Result3 BoundingBox BoundingBox2 BoundingBox3 Arithmetic Arithmetic2 Arithmetic3 Isosurface Isosurface2 Isosurface3 TransformAnimation GlobalAxis BoundingBox4 BoundingBox5 BoundingBox6 TransformAnimation2 TransformAnimation3

# Create viewers
viewer setVertical 0

viewer 0 setBackgroundMode 1
viewer 0 setBackgroundColor 0.06 0.13 0.24
viewer 0 setBackgroundColor2 0.72 0.72 0.78
viewer 0 setTransparencyType 5
viewer 0 setAutoRedraw 0
viewer 0 show
mainWindow show

set hideNewModules 0
create HxAnnaScalarField3 {Scalarfield}
Scalarfield setIconPosition 20 10
Scalarfield fire
Scalarfield expr setState {x*x + y*y + z*z}
{Scalarfield} setBoundingBox -1 0 0 1 -1 1
Scalarfield fire
Scalarfield setViewerMask 16383

set hideNewModules 0
create HxAnnaScalarField3 {Scalarfield2}
Scalarfield2 setIconPosition 20 40
Scalarfield2 fire
Scalarfield2 expr setState {x*x + y*y + z*z}
{Scalarfield2} setBoundingBox 0 1 0 1 -1 1
Scalarfield2 fire
Scalarfield2 setViewerMask 16383

set hideNewModules 0
create HxAnnaScalarField3 {Scalarfield3}
Scalarfield3 setIconPosition 20 70
Scalarfield3 fire
Scalarfield3 expr setState {x*x + y*y + z*z}
{Scalarfield3} setBoundingBox -1 1 -1 0 -1 1
Scalarfield3 fire
Scalarfield3 setViewerMask 16383

set hideNewModules 0
create HxBoundingBox {BoundingBox}
BoundingBox setIconPosition 369 10
{BoundingBox} setLineWidth 2
{BoundingBox} setColor 1 0.5 0
BoundingBox data connect Scalarfield
BoundingBox fire
BoundingBox text setValue 0 0
BoundingBox fire
BoundingBox setViewerMask 16382

set hideNewModules 0
create HxBoundingBox {BoundingBox2}
BoundingBox2 setIconPosition 363 40
{BoundingBox2} setLineWidth 2
{BoundingBox2} setColor 1 0.5 0
BoundingBox2 data connect Scalarfield2
BoundingBox2 fire
BoundingBox2 text setValue 0 0
BoundingBox2 fire
BoundingBox2 setViewerMask 16382

set hideNewModules 0
create HxBoundingBox {BoundingBox3}
BoundingBox3 setIconPosition 363 70
{BoundingBox3} setLineWidth 2
{BoundingBox3} setColor 1 0.5 0
BoundingBox3 data connect Scalarfield3
BoundingBox3 fire
BoundingBox3 text setValue 0 0
BoundingBox3 fire
BoundingBox3 setViewerMask 16382

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
Arithmetic doIt snap 0 1
Arithmetic fire
Arithmetic setViewerMask 16383

set hideNewModules 0
[ {Arithmetic} create
 ] setLabel {Result}
Result setIconPosition 20 100
Result master connect Arithmetic
Result fire
Result setTransform 1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1
Result fire
Result setViewerMask 16383

set hideNewModules 0
create HxArithmetic {Arithmetic2}
Arithmetic2 setIconPosition 160 40
Arithmetic2 inputA connect Scalarfield2
Arithmetic2 fire
Arithmetic2 resultChannels setValue 0 0
Arithmetic2 expr0 setState A
Arithmetic2 expr1 setState 0
Arithmetic2 expr2 setState 0
Arithmetic2 expr3 setState 0
Arithmetic2 expr4 setState 0
Arithmetic2 expr5 setState 0
Arithmetic2 resultType setValue 1
Arithmetic2 resolution setMinMax 0 1 1024
Arithmetic2 resolution setValue 0 64
Arithmetic2 resolution setMinMax 1 1 1024
Arithmetic2 resolution setValue 1 64
Arithmetic2 resolution setMinMax 2 1 1024
Arithmetic2 resolution setValue 2 64
Arithmetic2 minBox setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
Arithmetic2 minBox setValue 0 -1
Arithmetic2 minBox setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
Arithmetic2 minBox setValue 1 -1
Arithmetic2 minBox setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
Arithmetic2 minBox setValue 2 -1
Arithmetic2 maxBox setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
Arithmetic2 maxBox setValue 0 1
Arithmetic2 maxBox setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
Arithmetic2 maxBox setValue 1 1
Arithmetic2 maxBox setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
Arithmetic2 maxBox setValue 2 1
Arithmetic2 doIt snap 0 1
Arithmetic2 fire
Arithmetic2 setViewerMask 16383

set hideNewModules 0
[ {Arithmetic2} create
 ] setLabel {Result2}
Result2 setIconPosition 20 130
Result2 master connect Arithmetic2
Result2 fire
Result2 setTransform 1 1.74846e-007 0 0 -1.74846e-007 1 0 0 0 0 1 0 0 -1.74846e-007 0 1
Result2 fire
Result2 setViewerMask 16383

set hideNewModules 0
create HxArithmetic {Arithmetic3}
Arithmetic3 setIconPosition 160 70
Arithmetic3 inputA connect Scalarfield3
Arithmetic3 fire
Arithmetic3 resultChannels setValue 0 0
Arithmetic3 expr0 setState A
Arithmetic3 expr1 setState 0
Arithmetic3 expr2 setState 0
Arithmetic3 expr3 setState 0
Arithmetic3 expr4 setState 0
Arithmetic3 expr5 setState 0
Arithmetic3 resultType setValue 1
Arithmetic3 resolution setMinMax 0 1 1024
Arithmetic3 resolution setValue 0 64
Arithmetic3 resolution setMinMax 1 1 1024
Arithmetic3 resolution setValue 1 64
Arithmetic3 resolution setMinMax 2 1 1024
Arithmetic3 resolution setValue 2 64
Arithmetic3 minBox setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
Arithmetic3 minBox setValue 0 -1
Arithmetic3 minBox setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
Arithmetic3 minBox setValue 1 -1
Arithmetic3 minBox setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
Arithmetic3 minBox setValue 2 -1
Arithmetic3 maxBox setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
Arithmetic3 maxBox setValue 0 1
Arithmetic3 maxBox setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
Arithmetic3 maxBox setValue 1 1
Arithmetic3 maxBox setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
Arithmetic3 maxBox setValue 2 1
Arithmetic3 doIt snap 0 1
Arithmetic3 fire
Arithmetic3 setViewerMask 16383

set hideNewModules 0
[ {Arithmetic3} create
 ] setLabel {Result3}
Result3 setIconPosition 20 160
Result3 master connect Arithmetic3
Result3 fire
Result3 setTransform 1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1
Result3 fire
Result3 setViewerMask 16383

set hideNewModules 0
create HxIsosurface {Isosurface}
Isosurface setIconPosition 383 100
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
Isosurface threshold setMinMax 0.000251952675171196 3
Isosurface threshold setButtons 0
Isosurface threshold setIncrement 0.199983
Isosurface threshold setValue 0.5
Isosurface threshold setSubMinMax 0.000251952675171196 3
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
create HxIsosurface {Isosurface2}
Isosurface2 setIconPosition 377 130
Isosurface2 data connect Result2
Isosurface2 colormap setDefaultColor 1 0.8 0.4
Isosurface2 colormap setDefaultAlpha 0.500000
Isosurface2 fire
Isosurface2 drawStyle setValue 1
Isosurface2 drawStyle setSpecularLighting 1
Isosurface2 drawStyle setTexture 0
Isosurface2 drawStyle setAlphaMode 1
Isosurface2 drawStyle setNormalBinding 1
Isosurface2 drawStyle setCullingMode 0
Isosurface2 drawStyle setSortingMode 1
Isosurface2 textureWrap setValue 0 1
Isosurface2 threshold setMinMax 0.000251952675171196 3
Isosurface2 threshold setButtons 0
Isosurface2 threshold setIncrement 0.199983
Isosurface2 threshold setValue 0.5
Isosurface2 threshold setSubMinMax 0.000251952675171196 3
Isosurface2 options setValue 0 1
Isosurface2 options setValue 1 0
Isosurface2 resolution setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
Isosurface2 resolution setValue 0 2
Isosurface2 resolution setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
Isosurface2 resolution setValue 1 2
Isosurface2 resolution setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
Isosurface2 resolution setValue 2 2
{Isosurface2} doIt hit
Isosurface2 fire
Isosurface2 setViewerMask 16383

set hideNewModules 0
create HxIsosurface {Isosurface3}
Isosurface3 setIconPosition 377 160
Isosurface3 data connect Result3
Isosurface3 colormap setDefaultColor 1 0.8 0.4
Isosurface3 colormap setDefaultAlpha 0.500000
Isosurface3 fire
Isosurface3 drawStyle setValue 1
Isosurface3 drawStyle setSpecularLighting 1
Isosurface3 drawStyle setTexture 0
Isosurface3 drawStyle setAlphaMode 1
Isosurface3 drawStyle setNormalBinding 1
Isosurface3 drawStyle setCullingMode 0
Isosurface3 drawStyle setSortingMode 1
Isosurface3 textureWrap setValue 0 1
Isosurface3 threshold setMinMax 0.000503905350342393 3
Isosurface3 threshold setButtons 0
Isosurface3 threshold setIncrement 0.199966
Isosurface3 threshold setValue 0.5
Isosurface3 threshold setSubMinMax 0.000503905350342393 3
Isosurface3 options setValue 0 1
Isosurface3 options setValue 1 0
Isosurface3 resolution setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
Isosurface3 resolution setValue 0 2
Isosurface3 resolution setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
Isosurface3 resolution setValue 1 2
Isosurface3 resolution setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
Isosurface3 resolution setValue 2 2
{Isosurface3} doIt hit
Isosurface3 fire
Isosurface3 setViewerMask 16383

set hideNewModules 0
create HxObjectTransformAnimation {TransformAnimation}
TransformAnimation setIconPosition 160 100
TransformAnimation setIgnoreKeyListChange 1
TransformAnimation setNumInputs 2
TransformAnimation appendTransform 1 2 "Translation ID 2"
TransformAnimation appendTransform 0 1 "Rotation ID 1"
TransformAnimation appendTransform 1 4 "Translation ID 4"
TransformAnimation setEditMode 1
TransformAnimation setAnimationDump 2 10 0 1 0 0 0 0 1 0 -1 0 0 0.6 1 0 0 0 0 1 45 -1 0 0
TransformAnimation spatialData1 connect Result
TransformAnimation time setMinMax 0 1
TransformAnimation time setSubMinMax 0 1
TransformAnimation time setValue 0
TransformAnimation time setDiscrete 0
TransformAnimation time setIncrement 0.01
TransformAnimation time animationMode -swing
TransformAnimation fire
TransformAnimation mode setState 
TransformAnimation animationKeys setValue 0 0
TransformAnimation animationActions setState item 1 0 
TransformAnimation edit2 setState item 2 0 
TransformAnimation translateX2 setMinMax -10 10
TransformAnimation translateX2 setButtons 0
TransformAnimation translateX2 setIncrement 1.33333
TransformAnimation translateX2 setValue 1
TransformAnimation translateX2 setSubMinMax -10 10
TransformAnimation translateY2 setMinMax -10 10
TransformAnimation translateY2 setButtons 0
TransformAnimation translateY2 setIncrement 1.33333
TransformAnimation translateY2 setValue 0
TransformAnimation translateY2 setSubMinMax -10 10
TransformAnimation translateZ2 setMinMax -10 10
TransformAnimation translateZ2 setButtons 0
TransformAnimation translateZ2 setIncrement 1.33333
TransformAnimation translateZ2 setValue 0
TransformAnimation translateZ2 setSubMinMax -10 10
TransformAnimation edit1 setState item 2 0 
TransformAnimation degree1 setMinMax 0 360
TransformAnimation degree1 setButtons 0
TransformAnimation degree1 setIncrement 24
TransformAnimation degree1 setValue 0
TransformAnimation degree1 setSubMinMax 0 360
TransformAnimation axis1 setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
TransformAnimation axis1 setValue 0 0
TransformAnimation axis1 setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
TransformAnimation axis1 setValue 1 0
TransformAnimation axis1 setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
TransformAnimation axis1 setValue 2 1
TransformAnimation edit4 setState item 2 0 
TransformAnimation translateX4 setMinMax -10 10
TransformAnimation translateX4 setButtons 0
TransformAnimation translateX4 setIncrement 1.33333
TransformAnimation translateX4 setValue -1
TransformAnimation translateX4 setSubMinMax -10 10
TransformAnimation translateY4 setMinMax -10 10
TransformAnimation translateY4 setButtons 0
TransformAnimation translateY4 setIncrement 1.33333
TransformAnimation translateY4 setValue 0
TransformAnimation translateY4 setSubMinMax -10 10
TransformAnimation translateZ4 setMinMax -10 10
TransformAnimation translateZ4 setButtons 0
TransformAnimation translateZ4 setIncrement 1.33333
TransformAnimation translateZ4 setValue 0
TransformAnimation translateZ4 setSubMinMax -10 10
TransformAnimation addNewTransform setState item 0 1 item 3 0 
TransformAnimation fire
TransformAnimation setIgnoreKeyListChange 0
TransformAnimation fire
TransformAnimation setViewerMask 16383
TransformAnimation select
TransformAnimation time setPin 1
TransformAnimation deselect

set hideNewModules 0
create HxAxis {GlobalAxis}
GlobalAxis setIconPosition 383 190
GlobalAxis fire
GlobalAxis axis setValue 0 1
GlobalAxis axis setValue 1 1
GlobalAxis axis setValue 2 1
GlobalAxis options setValue 0 1
GlobalAxis options setValue 1 0
GlobalAxis options setValue 2 0
GlobalAxis thickness setMinMax 1 15
GlobalAxis thickness setButtons 0
GlobalAxis thickness setIncrement 0.933333
GlobalAxis thickness setValue 5
GlobalAxis thickness setSubMinMax 1 15
GlobalAxis color setColor 0 1 0 0
GlobalAxis color setColor 1 0 1 0
GlobalAxis color setColor 2 0 0 1
GlobalAxis color setColor 3 0.8 0.8 0.8
GlobalAxis color setColor 4 1 0.8 0.5
GlobalAxis fire
GlobalAxis setBoundingBox 0 2.07846 0 2.07846 0 2.07846
{GlobalAxis} setFontSize 10 
{GlobalAxis} setFontName {Helvetica} 
{GlobalAxis} setAxisText 0 {x} 
{GlobalAxis} setAxisText 1 {y} 
{GlobalAxis} setAxisText 2 {z} 
{GlobalAxis} setDelta 0.1 
{GlobalAxis} setLocalMode 0 
{GlobalAxis} setFlip 0 0 
{GlobalAxis} setFlip 1 0 
{GlobalAxis} setFlip 2 0 
GlobalAxis fire
GlobalAxis setViewerMask 16382

set hideNewModules 0
create HxBoundingBox {BoundingBox4}
BoundingBox4 setIconPosition 18 197
{BoundingBox4} setLineWidth 2
{BoundingBox4} setColor 1 0.5 0
BoundingBox4 data connect Result
BoundingBox4 fire
BoundingBox4 text setValue 0 0
BoundingBox4 fire
BoundingBox4 setViewerMask 16382

set hideNewModules 0
create HxBoundingBox {BoundingBox5}
BoundingBox5 setIconPosition 20 225
{BoundingBox5} setLineWidth 2
{BoundingBox5} setColor 1 0.5 0
BoundingBox5 data connect Result2
BoundingBox5 fire
BoundingBox5 text setValue 0 0
BoundingBox5 fire
BoundingBox5 setViewerMask 16382

set hideNewModules 0
create HxBoundingBox {BoundingBox6}
BoundingBox6 setIconPosition 25 252
{BoundingBox6} setLineWidth 2
{BoundingBox6} setColor 1 0.5 0
BoundingBox6 data connect Result3
BoundingBox6 fire
BoundingBox6 text setValue 0 0
BoundingBox6 fire
BoundingBox6 setViewerMask 16382

set hideNewModules 0
create HxObjectTransformAnimation {TransformAnimation2}
TransformAnimation2 setIconPosition 160 130
TransformAnimation2 setIgnoreKeyListChange 1
TransformAnimation2 setNumInputs 2
TransformAnimation2 appendTransform 1 2 "Translation ID 2"
TransformAnimation2 appendTransform 0 1 "Rotation ID 1"
TransformAnimation2 appendTransform 1 4 "Translation ID 4"
TransformAnimation2 setEditMode 1
TransformAnimation2 setAnimationDump 2 10 0.1 -1 0 0 0 0 1 360 1 0 0 0.7 -1 0 0 0 0 1 315 1 0 0
TransformAnimation2 spatialData1 connect Result2
TransformAnimation2 time connect TransformAnimation
TransformAnimation2 time setMinMax 0 1
TransformAnimation2 time setSubMinMax 0 1
TransformAnimation2 time setValue 0
TransformAnimation2 time setDiscrete 0
TransformAnimation2 time setIncrement 0.01
TransformAnimation2 time animationMode -swing
TransformAnimation2 fire
TransformAnimation2 mode setState 
TransformAnimation2 animationKeys setValue 0 0
TransformAnimation2 animationActions setState item 1 0 
TransformAnimation2 edit2 setState item 2 0 
TransformAnimation2 translateX2 setMinMax -10 10
TransformAnimation2 translateX2 setButtons 0
TransformAnimation2 translateX2 setIncrement 1.33333
TransformAnimation2 translateX2 setValue -1
TransformAnimation2 translateX2 setSubMinMax -10 10
TransformAnimation2 translateY2 setMinMax -10 10
TransformAnimation2 translateY2 setButtons 0
TransformAnimation2 translateY2 setIncrement 1.33333
TransformAnimation2 translateY2 setValue 0
TransformAnimation2 translateY2 setSubMinMax -10 10
TransformAnimation2 translateZ2 setMinMax -10 10
TransformAnimation2 translateZ2 setButtons 0
TransformAnimation2 translateZ2 setIncrement 1.33333
TransformAnimation2 translateZ2 setValue 0
TransformAnimation2 translateZ2 setSubMinMax -10 10
TransformAnimation2 edit1 setState item 2 0 
TransformAnimation2 degree1 setMinMax 0 360
TransformAnimation2 degree1 setButtons 0
TransformAnimation2 degree1 setIncrement 24
TransformAnimation2 degree1 setValue 360
TransformAnimation2 degree1 setSubMinMax 0 360
TransformAnimation2 axis1 setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
TransformAnimation2 axis1 setValue 0 0
TransformAnimation2 axis1 setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
TransformAnimation2 axis1 setValue 1 0
TransformAnimation2 axis1 setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
TransformAnimation2 axis1 setValue 2 1
TransformAnimation2 edit4 setState item 2 0 
TransformAnimation2 translateX4 setMinMax -10 10
TransformAnimation2 translateX4 setButtons 0
TransformAnimation2 translateX4 setIncrement 1.33333
TransformAnimation2 translateX4 setValue 1
TransformAnimation2 translateX4 setSubMinMax -10 10
TransformAnimation2 translateY4 setMinMax -10 10
TransformAnimation2 translateY4 setButtons 0
TransformAnimation2 translateY4 setIncrement 1.33333
TransformAnimation2 translateY4 setValue 0
TransformAnimation2 translateY4 setSubMinMax -10 10
TransformAnimation2 translateZ4 setMinMax -10 10
TransformAnimation2 translateZ4 setButtons 0
TransformAnimation2 translateZ4 setIncrement 1.33333
TransformAnimation2 translateZ4 setValue 0
TransformAnimation2 translateZ4 setSubMinMax -10 10
TransformAnimation2 addNewTransform setState item 0 1 item 3 0 
TransformAnimation2 fire
TransformAnimation2 setIgnoreKeyListChange 0
TransformAnimation2 fire
TransformAnimation2 setViewerMask 16383

set hideNewModules 0
create HxObjectTransformAnimation {TransformAnimation3}
TransformAnimation3 setIconPosition 160 160
TransformAnimation3 setIgnoreKeyListChange 1
TransformAnimation3 setNumInputs 2
TransformAnimation3 appendTransform 2 1 "Uniform Scale ID 1"
TransformAnimation3 appendTransform 1 2 "Translation ID 2"
TransformAnimation3 setEditMode 1
TransformAnimation3 setAnimationDump 2 4 0.71 1 0 0 0 1 1.5 0 0.8 0
TransformAnimation3 spatialData1 connect Result3
TransformAnimation3 time connect TransformAnimation
TransformAnimation3 time setMinMax 0 1
TransformAnimation3 time setSubMinMax 0 1
TransformAnimation3 time setValue 0
TransformAnimation3 time setDiscrete 0
TransformAnimation3 time setIncrement 0.01
TransformAnimation3 time animationMode -swing
TransformAnimation3 fire
TransformAnimation3 mode setState 
TransformAnimation3 animationKeys setValue 0 0
TransformAnimation3 animationActions setState item 1 0 
TransformAnimation3 edit1 setState item 2 0 
TransformAnimation3 scale1 setMinMax 0.00100000004749745 10
TransformAnimation3 scale1 setButtons 0
TransformAnimation3 scale1 setIncrement 0.6666
TransformAnimation3 scale1 setValue 1
TransformAnimation3 scale1 setSubMinMax 0.00100000004749745 10
TransformAnimation3 edit2 setState item 2 0 
TransformAnimation3 translateX2 setMinMax -10 10
TransformAnimation3 translateX2 setButtons 0
TransformAnimation3 translateX2 setIncrement 1.33333
TransformAnimation3 translateX2 setValue 0
TransformAnimation3 translateX2 setSubMinMax -10 10
TransformAnimation3 translateY2 setMinMax -10 10
TransformAnimation3 translateY2 setButtons 0
TransformAnimation3 translateY2 setIncrement 1.33333
TransformAnimation3 translateY2 setValue 0
TransformAnimation3 translateY2 setSubMinMax -10 10
TransformAnimation3 translateZ2 setMinMax -10 10
TransformAnimation3 translateZ2 setButtons 0
TransformAnimation3 translateZ2 setIncrement 1.33333
TransformAnimation3 translateZ2 setValue 0
TransformAnimation3 translateZ2 setSubMinMax -10 10
TransformAnimation3 addNewTransform setState item 0 1 item 3 0 
TransformAnimation3 fire
TransformAnimation3 setIgnoreKeyListChange 0
TransformAnimation3 fire
TransformAnimation3 setViewerMask 16383

set hideNewModules 0


viewer 0 setCameraOrientation 0.000677535 -0.957818 -0.287374 3.1692
viewer 0 setCameraPosition 0.0906377 2.49452 -3.02556
viewer 0 setCameraFocalDistance 3.83071
viewer 0 setCameraNearDistance 2.89981
viewer 0 setCameraFarDistance 4.90243
viewer 0 setCameraType perspective
viewer 0 setCameraHeightAngle 44.9023
viewer 0 setAutoRedraw 1
viewer 0 redraw
