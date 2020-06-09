# Amira Script
# test(timeout=60)

if { ![app hasLicense MeshPack] } { 
	theMsg error "This script requires a MeshPack license." 
	return 
}

remove -all
#remove physics.icol volrenRed.col AnalyticTensorField Result Result._evec1 Result._evec2 Result._evec3 Result._evals Result.mag CameraPath Result.to-byte ArithmeticTensor ExtractEigenvalues Magnitude Isosurface CastField Light Light2 EmptyPlane TensorDisplay

# Create viewers
viewer setVertical 0

viewer 0 setBackgroundMode 0
viewer 0 setBackgroundColor 0 0 0
viewer 0 setBackgroundColor2 0.72 0.72 0.78
viewer 0 setTransparencyType 5
viewer 0 setAutoRedraw 0
viewer 0 setCameraType 1
viewer 0 show
mainWindow show

set hideNewModules 1
[ load ${AMIRA_ROOT}/data/colormaps/physics.icol ] setLabel physics.icol
physics.icol setIconPosition 0 0
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
[ load ${AMIRA_ROOT}/data/colormaps/volrenRed.col ] setLabel volrenRed.col
volrenRed.col setIconPosition 0 0
volrenRed.col fire
{volrenRed.col} setMinMax -0.864452 0.1
volrenRed.col flags setValue 1
volrenRed.col shift setMinMax -1 1
volrenRed.col shift setButtons 0
volrenRed.col shift setIncrement 0.133333
volrenRed.col shift setValue 0
volrenRed.col shift setSubMinMax -1 1
volrenRed.col scale setMinMax 0 1
volrenRed.col scale setButtons 0
volrenRed.col scale setIncrement 0.1
volrenRed.col scale setValue 1
volrenRed.col scale setSubMinMax 0 1
volrenRed.col fire
volrenRed.col setViewerMask 16383

set hideNewModules 0
create HxGenerateTensorData {AnalyticTensorField}
AnalyticTensorField setIconPosition 20 10
AnalyticTensorField fire
AnalyticTensorField Metric setValue 0 0
AnalyticTensorField fire
AnalyticTensorField Scale setMinMax 9.99999997475243e-007 6.28318548202515
AnalyticTensorField Scale setButtons 0
AnalyticTensorField Scale setIncrement 0.418879
AnalyticTensorField Scale setValue 1
AnalyticTensorField Scale setSubMinMax 9.99999997475243e-007 6.28318548202515
AnalyticTensorField Mass setMinMax 0 1
AnalyticTensorField Mass setButtons 0
AnalyticTensorField Mass setIncrement 0.1
AnalyticTensorField Mass setValue 0.1
AnalyticTensorField Mass setSubMinMax 0 1
AnalyticTensorField AngularMoment setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
AnalyticTensorField AngularMoment setValue 0 0.600000023841858
{AnalyticTensorField} setRandomValues -0.272271 -0.10213 -0.374935 0.0600757 -0.232597 0.288232 0.312799 -0.380215 0.34933 0.124042 -0.208029 -0.0772881 -0.128956 -0.175069 0.393948 -0.0763421 0.181661 0.318384 -0.133106 0.399014 -0.0544298 -0.48352 0.061449 0.239463 -0.465026 -0.298517 -0.277886 0.364132 0.458831 -0.364223 0.0612964 0.440184 0.134754 -0.360378 0.107227 0.0165258 -0.10213 -0.374935 0.0600757 -0.232597 0.288232 -0.479919 -0.380215 0.34933 0.124042 -0.208029 -0.0772881 -0.493011 
{AnalyticTensorField} setBoundingBox -1 1 -1 1 -1 1
AnalyticTensorField fire
AnalyticTensorField setViewerMask 16383

set hideNewModules 0
create HxArithmetic {ArithmeticTensor}
ArithmeticTensor setIconPosition 243 10
ArithmeticTensor inputA connect AnalyticTensorField
ArithmeticTensor fire
ArithmeticTensor resultChannels setValue 0 0
ArithmeticTensor expr0 setState Aii
ArithmeticTensor expr1 setState Aij
ArithmeticTensor expr2 setState Aik
ArithmeticTensor expr3 setState Ajj
ArithmeticTensor expr4 setState Ajk
ArithmeticTensor expr5 setState Akk
ArithmeticTensor resultType setValue 1
ArithmeticTensor resolution setMinMax 0 1 1024
ArithmeticTensor resolution setValue 0 96
ArithmeticTensor resolution setMinMax 1 1 1024
ArithmeticTensor resolution setValue 1 96
ArithmeticTensor resolution setMinMax 2 1 1024
ArithmeticTensor resolution setValue 2 96
ArithmeticTensor minBox setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
ArithmeticTensor minBox setValue 0 -1
ArithmeticTensor minBox setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
ArithmeticTensor minBox setValue 1 -1
ArithmeticTensor minBox setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
ArithmeticTensor minBox setValue 2 -1
ArithmeticTensor maxBox setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
ArithmeticTensor maxBox setValue 0 1
ArithmeticTensor maxBox setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
ArithmeticTensor maxBox setValue 1 1
ArithmeticTensor maxBox setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
ArithmeticTensor maxBox setValue 2 1
ArithmeticTensor doIt snap 0 1
ArithmeticTensor fire
ArithmeticTensor setViewerMask 16383

set hideNewModules 0
[ {ArithmeticTensor} create
 ] setLabel {Result}
Result setIconPosition 20 40
Result master connect ArithmeticTensor
Result fire
Result fire
Result setViewerMask 16383

set hideNewModules 0
create HxExtractEigenvalues {ExtractEigenvalues}
ExtractEigenvalues setIconPosition 160 40
ExtractEigenvalues data connect Result
{ExtractEigenvalues} fire
ExtractEigenvalues data connect Result
ExtractEigenvalues fire
ExtractEigenvalues Options setValue 0 1
ExtractEigenvalues Output setValue 0 1
ExtractEigenvalues Output setValue 1 1
ExtractEigenvalues Output setValue 2 1
ExtractEigenvalues Output setValue 3 1
ExtractEigenvalues MaskExpr setState A>0
ExtractEigenvalues fire
ExtractEigenvalues setViewerMask 16383
ExtractEigenvalues action touch
ExtractEigenvalues action hit
ExtractEigenvalues fire

sleep 5

set hideNewModules 0
[ExtractEigenvalues getResult 0] setLabel Result._evec1
Result._evec1 setIconPosition 20 70
Result._evec1 master connect ExtractEigenvalues 0
Result._evec1 fire
Result._evec1 fire
Result._evec1 setViewerMask 16383

set hideNewModules 0
[ExtractEigenvalues getResult 1] setLabel Result._evec2
Result._evec2 setIconPosition 20 100
Result._evec2 master connect ExtractEigenvalues 1
Result._evec2 fire
Result._evec2 fire
Result._evec2 setViewerMask 16383

set hideNewModules 0
[ExtractEigenvalues getResult 2] setLabel Result._evec3
Result._evec3 setIconPosition 20 130
Result._evec3 master connect ExtractEigenvalues 2
Result._evec3 fire
Result._evec3 fire
Result._evec3 setViewerMask 16383

set hideNewModules 0
create HxMagnitude {Magnitude}
Magnitude setIconPosition 160 160
Magnitude data connect Result._evals
Magnitude fire
Magnitude mode setValue 0
Magnitude doIt snap 0 1
Magnitude fire
Magnitude setViewerMask 16383

set hideNewModules 0
[ Magnitude doIt hit; Magnitude compute; Magnitude getResult
 ] setLabel {Result.mag}
Result.mag setIconPosition 20 190
Result.mag master connect Magnitude
Result.mag fire
Result.mag fire
Result.mag setViewerMask 16383

set hideNewModules 0
create HxIsosurface {Isosurface}
Isosurface setIconPosition 403 190
Isosurface data connect Result.mag
Isosurface colorField connect Result._evec1
Isosurface colormap setDefaultColor 1 0.8 0.4
Isosurface colormap setDefaultAlpha 0.500000
Isosurface colormap connect volrenRed.col
Isosurface fire
Isosurface drawStyle setValue 4
Isosurface drawStyle setSpecularLighting 1
Isosurface drawStyle setTexture 0
Isosurface drawStyle setAlphaMode 3
Isosurface drawStyle setNormalBinding 1
Isosurface drawStyle setCullingMode 0
Isosurface threshold setMinMax 0.00994768925011158 360.583221435547
Isosurface threshold setButtons 0
Isosurface threshold setIncrement 24.0382
Isosurface threshold setValue 0.2
Isosurface threshold setSubMinMax 0.00994768925011158 360.583221435547
Isosurface options setValue 0 0
Isosurface options setValue 1 0
Isosurface resolution setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
Isosurface resolution setValue 0 2
Isosurface resolution setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
Isosurface resolution setValue 1 2
Isosurface resolution setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
Isosurface resolution setValue 2 2
Isosurface doIt snap 0 1
{Isosurface} doIt hit
Isosurface fire
Isosurface setViewerMask 16383

set hideNewModules 0
create HxCastField {CastField}
CastField setIconPosition 160 190
CastField data connect Result.mag
CastField colormap setDefaultColor 1 0.8 0.5
CastField colormap setDefaultAlpha 0.500000
CastField fire
CastField outputType setValue 0 0
CastField scaling setState item 1 0 item 0 1 
CastField voxelGridOptions setValue 0 1
CastField colorFieldOptions setValue 0 0
CastField scaling setValue 0.5
CastField fire
CastField setViewerMask 16383

set hideNewModules 0
[ {CastField} create
 ] setLabel {Result.to-byte}
Result.to-byte setIconPosition 20 220
Result.to-byte master connect CastField
Result.to-byte fire
Result.to-byte fire
Result.to-byte setViewerMask 16383

set hideNewModules 0
create HxLight {Light}
Light setIconPosition 429 10
Light setType 0
Light setColor 1 1 1
Light setSlave 0
Light edit 0
Light setDirection -0.150691 -0.985007 -0.0839802
Light setLocation 0.302373 1.46082 0.0253298
Light setIntensity 1
Light fire
Light setViewerMask 16383

set hideNewModules 0
create HxLight {Light2}
Light2 setIconPosition 423 90
Light2 setType 2
Light2 setColor 1 1 1
Light2 setSlave 0
Light2 edit 0
Light2 setDirection 0.027347 0.96149 -0.273476
Light2 setLocation -0.0662238 -1.76667 0.406994
Light2 setIntensity 1
Light2 setCutOffAngle 0.785398
Light2 setDropOffRate 0
Light2 fire
Light2 setViewerMask 16383

set hideNewModules 0
create HxArbitraryCut {EmptyPlane}
EmptyPlane setIconPosition 396 40
EmptyPlane data connect Result
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
EmptyPlane setPlane 0 0 0 0 1 0 0 0 1
EmptyPlane fire
EmptyPlane setViewerMask 16382

set hideNewModules 0
create HxTensorDisplay {TensorDisplay}
TensorDisplay setIconPosition 396 60
TensorDisplay data connect Result
TensorDisplay module connect EmptyPlane
TensorDisplay Colormap setDefaultColor 1 0.8 0.5
TensorDisplay Colormap setDefaultAlpha 0.500000
TensorDisplay Colormap connect physics.icol
TensorDisplay Mask connect Result.to-byte
TensorDisplay fire
TensorDisplay Display setValue 2
TensorDisplay Options setValue 0 1
TensorDisplay MappingsAndColorings setValue 0 -1
TensorDisplay MappingsAndColorings setValue 1 0
TensorDisplay ScaleByValue setValue 0 1
TensorDisplay ScaleByValue setValue 1 1
TensorDisplay ScaleByValue setValue 2 1
TensorDisplay ScaleByValue setValue 3 1
TensorDisplay DisplayComplexity setMinMax 0 1
TensorDisplay DisplayComplexity setButtons 0
TensorDisplay DisplayComplexity setIncrement 0.1
TensorDisplay DisplayComplexity setValue 0.4
TensorDisplay DisplayComplexity setSubMinMax 0 1
TensorDisplay Resolution setMinMax 0 1 1000
TensorDisplay Resolution setValue 0 15
TensorDisplay Resolution setMinMax 1 1 1000
TensorDisplay Resolution setValue 1 15
TensorDisplay MaskExpr setState A<1
TensorDisplay Scale setMinMax 0 200
TensorDisplay Scale setButtons 0
TensorDisplay Scale setIncrement 13.3333
TensorDisplay Scale setValue 0.04
TensorDisplay Scale setSubMinMax 0 200
{TensorDisplay} fire
{TensorDisplay} setVolumeModeSkip 5
{TensorDisplay} setVolumeMode 1
{TensorDisplay} setSigmoidSteepness 1
{TensorDisplay} setPointSize 1
TensorDisplay fire
TensorDisplay setViewerMask 16383
TensorDisplay action touch
TensorDisplay action hit
TensorDisplay fire

set hideNewModules 0


viewer 0 setCameraPosition 2.43112 -0.00434016 0.00116813
viewer 0 setCameraOrientation 0.57735 0.57735 0.57735 2.0944
viewer 0 setCameraFocalDistance 2.42516
viewer 0 setAutoRedraw 1
viewer 0 redraw
