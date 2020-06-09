# Amira Script
# test(timeout=420)

if { ![app hasLicense MeshPack] } {
    theMsg error "This script requires a MeshPack license."
    return
}

remove -all

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
create HxGenerateTensorData {AnalyticTensorField}
AnalyticTensorField setIconPosition 21 21
AnalyticTensorField fire
AnalyticTensorField Metric setIndex 0 3
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
{AnalyticTensorField} setRandomValues -0.498749 -0.149709 0.210501 -0.352687 -0.491089 -0.333766 0.0635853 0.395962 0.013535 -0.334101 -0.12212 0.163045 -0.306696 0.32284 -0.196005 0.488525 0.031663 -0.0492111 0.308741 0.246605 -0.485015 -0.0543077 0.0711844 -0.147877 0.0850093 -0.325892 -0.408597 -0.380917 0.101764 -0.442961 -0.020127 0.358943 -0.135548 -0.495331 0.107166 0.107685 -0.149709 0.210501 -0.352687 -0.491089 -0.333766 0.283319 0.395962 0.013535 -0.334101 -0.12212 0.163045 0.302606
{AnalyticTensorField} setBoundingBox -1 1 -1 1 -1 1
AnalyticTensorField fire
AnalyticTensorField setViewerMask 16383

set hideNewModules 0
create HxArithmetic {ArithmeticTensor}
ArithmeticTensor setIconPosition 160 51
ArithmeticTensor inputA connect AnalyticTensorField
ArithmeticTensor fire
ArithmeticTensor resultChannels setIndex 0 0
ArithmeticTensor expr0 setState Aii
ArithmeticTensor expr1 setState Aij
ArithmeticTensor expr2 setState Aik
ArithmeticTensor expr3 setState Ajj
ArithmeticTensor expr4 setState Ajk
ArithmeticTensor expr5 setState Akk
ArithmeticTensor expr6 setState 0
ArithmeticTensor expr7 setState 0
ArithmeticTensor expr8 setState 0
ArithmeticTensor resultType setValue 1
ArithmeticTensor resolution setMinMax 0 1 100000
ArithmeticTensor resolution setValue 0 64
ArithmeticTensor resolution setMinMax 1 1 100000
ArithmeticTensor resolution setValue 1 64
ArithmeticTensor resolution setMinMax 2 1 100000
ArithmeticTensor resolution setValue 2 64
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
ArithmeticTensor fire
ArithmeticTensor setViewerMask 16383

set hideNewModules 0
[ {ArithmeticTensor} create
 ] setLabel {Result2}
Result2 setIconPosition 20 51
Result2 master connect ArithmeticTensor
Result2 fire
Result2 fire
Result2 setViewerMask 16383

set hideNewModules 0
create HxGenerateGradients {CreateGradientImage}
CreateGradientImage setIconPosition 209 101
CreateGradientImage data connect Result2
CreateGradientImage fire
CreateGradientImage Gradient setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
CreateGradientImage Gradient setValue 0 1
CreateGradientImage Gradient setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
CreateGradientImage Gradient setValue 1 0
CreateGradientImage Gradient setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
CreateGradientImage Gradient setValue 2 1
CreateGradientImage BValue setMinMax 0 0 10000
CreateGradientImage BValue setValue 0 1
CreateGradientImage Mode setValue 1
CreateGradientImage ScaleOutput setMinMax 0 0 1000000
CreateGradientImage ScaleOutput setValue 0 400
CreateGradientImage ScaleOutput setMinMax 1 -1000 1000
CreateGradientImage ScaleOutput setValue 1 0
CreateGradientImage Expression setState A>0
CreateGradientImage fire
CreateGradientImage setViewerMask 16383
CreateGradientImage select

set hideNewModules 0

# Generate gradient images for the following gradients
set gradients32 [list {-0.70710 -0.70710 -1.00000} \
    {-0.70710 -0.70710 1.00000} \
    {1.00000 -1.00000 0.00000} \
    {-0.92390 -0.38270 -1.00000} \
    {-0.29510 -0.95550 -1.00000} \
    {0.02780 -0.99960 -1.00000} \
    {0.59570 -0.80320 -1.00000} \
    {0.97570 -0.21910 -1.00000} \
    {-0.92420 -0.38280 -0.99970} \
    {-0.41420 -1.00000 -0.91020} \
    {0.41650 -0.99900 -0.91020} \
    {0.72830 -0.68740 -0.99850} \
    {1.00000 -0.41420 -0.91020} \
    {-1.00000 -0.66820 -0.74400} \
    {-0.66820 -1.00000 -0.74400} \
    {0.78560 -0.91070 -0.74400} \
    {1.00000 -0.66820 -0.74400} \
    {-1.00000 -1.00000 -0.00030} \
    {-1.00000 -0.66820 0.74400} \
    {1.00000 -0.66820 0.74400} \
    {0.66820 -1.00000 0.74400} \
    {1.00000 -0.66820 0.74400} \
    {-0.90000 -0.60130 0.91020} \
    {-0.99850 -0.99850 0.07740} \
    {-0.41420 -1.00000 0.91020} \
    {0.41420 -1.00000 0.91020} \
    {1.00000 -1.00000 0.01110} \
    {1.00000 -0.41420 0.91020} \
    {-0.99880 -0.99880 0.06920} \
    {0.04910 -0.99880 1.00000} \
    {0.99990 -0.99990 0.01630} \
    {1.00000 0.00000 1.00000} ];

set TMPENVS [list TMP TEMP TMPDIR]
set TMPDIR ""
foreach envvar $TMPENVS {
   if { $TMPDIR == "" } {
      if { [catch { set TMPDIR $env($envvar) } error] } {
         echo "Checking for a $envvar environment variable ..."
      }
   }
}
if { $TMPDIR == "" } {
   # Could be Unix-based
   set TMPDIR [exec mktemp -d /tmp/TensorOutOfCore.XXXXXXXXXX]
}
if { [file exists $TMPDIR] == 0 || [file isdirectory $TMPDIR] == 0 } {
   set TMPDIR ""
}
if { $TMPDIR == "" } {
   echo "Error: Failed to find a suitable temporary directory. Make sure that the environment variable TMP is defined."
   return
}
regsub -all {\\} $TMPDIR "/" TMPDIR
echo "Using \"$TMPDIR\" to store temporary files ..."

# Create a b0 substitute
set mag [create HxMagnitude]
$mag data connect Result2
$mag fire
set b0 [lindex [lindex [$mag downStreamConnections] 0] 0]
set cf [create HxCastField]
$cf data connect $b0
$cf outputType setValue 0 1
$cf scaling setValue 0 800
$cf scaling setValue 1 -11.9
$cf fire
$cf action hit
$cf fire
set b0 [lindex [lindex [$cf downStreamConnections] 0] 0]
$b0 save AmiraMesh ${TMPDIR}/B0.am

# Create the gradient images
set fileList [list B0.am]
foreach u $gradients32 {
    CreateGradientImage Gradient setValue 0 [lindex $u 0]
    CreateGradientImage Gradient setValue 1 [lindex $u 1]
    CreateGradientImage Gradient setValue 2 [lindex $u 2]
    CreateGradientImage Mode setValue 1
    CreateGradientImage BValue setValue 0.05
    CreateGradientImage ScaleOutput setValue 0 800
    CreateGradientImage ScaleOutput setValue 1 -400
    CreateGradientImage fire
    CreateGradientImage action hit
    CreateGradientImage fire
    set grad [lindex [lindex [CreateGradientImage downStreamConnections] 0] 0]
    $grad save AmiraMesh ${TMPDIR}/${grad}.am
    lappend fileList ${grad}.am
    set grad [lindex [lindex [CreateGradientImage downStreamConnections] 0] 0]
    $grad master disconnect
    update
    remove $grad
}
update

# Create a data.tensor file
set fp [open ${TMPDIR}/tensor.data "w"]
if { $fp == "" } {
    echo "Error: Could not open tensor.data in ${TMPDIR}."
    return
}

puts $fp "# AmiraMesh3D BINARY 2.0"
puts $fp ""
puts $fp "# Define a dummy lattice to make this AmiraMesh valid"
puts $fp "define Lattice 1 1 1"
puts $fp "Lattice \{ byte Data \} @1"
puts $fp "@1"
puts $fp "a"
puts $fp ""
puts $fp "Parameters \{"
puts $fp "   BoundingBox -1 1 -1 1 -1 1,"
puts $fp "   CoordType \"uniform\","
puts $fp "   Data {"
puts $fp "       directory \"${TMPDIR}/\","
puts $fp "       gradients \"MyGradients\","
puts $fp "       # File0 is always the b=0"
puts $fp "       # measurement (no gradient)"
set i 0
foreach u $fileList {
    puts $fp "       [format "file%d" $i] \{"
    puts $fp "          name \"$u\","
    if { $i > 0 } {
        puts $fp "          gradient \"[expr $i - 1]\","
    }
    puts $fp "       \}"
    set i [expr $i + 1]
}
puts $fp "   \}"
puts $fp "   MyGradients"
foreach u $gradients32 {
    puts $fp "  [lindex $u 0] [lindex $u 1] [lindex $u 2]"
}
puts $fp "   \}"
close $fp
load ${TMPDIR}/tensor.data

set OOC [create HxComputeTensorOutOfCore]
$OOC data connect tensor.data
$OOC action hit
$OOC fire
set tensor [lindex [lindex [$OOC downStreamConnections] 0] 0]
set bingham [lindex [lindex [$OOC downStreamConnections] 2] 0]

set ac [create HxArbitraryCut]
$ac data connect $tensor
set td [create HxTensorDisplay]
$td data connect $tensor
$td module connect $ac
$td fire
$td ScaleByValue setValue 3 0
$td Resolution setValue 0 40
$td Resolution setValue 1 40
$td Scale setValue 40
$td DisplayComplexity setValue 0.8
$td fire
$td action hit
$td fire

update
set vol [create HxVoltex]
$vol fire
update
$vol data connect $bingham
$vol select
$vol fire
update
sleep 1
$vol colormap setMinMax 5 80
$vol alphaScale setValue 0.8
$vol fire
$vol doIt hit
$vol fire

set ann [create HxAnnotation]
$ann text setValue "Bingham test for uniformity (volume rendering)"
$ann fire

create HxDynamicFileSeriesCtrl {TimeSeriesControl}
TimeSeriesControl setIconPosition 232 273
TimeSeriesControl fire
set cmd "TimeSeriesControl init -loadCmd \{load \"\\\$FILENAME\"\} "
foreach u $fileList {
   set cmd "$cmd \\\n \"${TMPDIR}/${u}\""
}
eval $cmd
TimeSeriesControl cachedSteps setMinMax 0 0 [llength $fileList]
TimeSeriesControl cachedSteps setValue 0 [llength $fileList]
TimeSeriesControl time setMinMax 0 [llength $fileList]
TimeSeriesControl time setValue 0
TimeSeriesControl time setDiscrete 1
TimeSeriesControl time setIncrement 1
TimeSeriesControl time animationMode -loop
TimeSeriesControl fire

[ TimeSeriesControl getResult 0 ] setLabel {Result2_Grad0.7283_-0.6874_-0.2.am}
Result2_Grad0.7283_-0.6874_-0.2.am setIconPosition 120 308
Result2_Grad0.7283_-0.6874_-0.2.am master connect TimeSeriesControl
Result2_Grad0.7283_-0.6874_-0.2.am fire

create HxOrthoSlice {OrthoSlice}
OrthoSlice setIconPosition 258 340
OrthoSlice data connect Result2_Grad0.7283_-0.6874_-0.2.am
OrthoSlice fire
OrthoSlice setViewerMask 16382


viewer setCameraOrientation 0.967548 0.0218982 -0.251736 2.92852
viewer setCameraPosition -1.65593 -0.680566 -2.92333
viewer setCameraFocalDistance 3.42246
viewer setCameraNearDistance 0.584277
viewer setCameraFarDistance 6.27627
viewer setCameraType perspective
viewer setCameraHeightAngle 44.9023
viewer 0 setAutoRedraw 1
viewer 0 redraw
