# Amira Script
if { ![app hasLicense MeshPack] } { 
	theMsg error "This script requires a MeshPack license." 
	return 
}

remove -all

# Create viewers
viewer setVertical 0

viewer 0 setBackgroundMode 0
viewer 0 setBackgroundColor 0 0 0
viewer 0 setBackgroundColor2 0.72 0.72 0.78
viewer 0 setTransparencyType 5
viewer 0 setAutoRedraw 0
viewer 0 show
mainWindow show

dso open hxcluster
set Object [create HxCluster]
$Object setNumDataColumns 6 
$Object setDataColumnName 0 "Tii" 
$Object setDataColumnName 1 "Tij" 
$Object setDataColumnName 2 "Tik" 
$Object setDataColumnName 3 "Tjj" 
$Object setDataColumnName 4 "Tjk" 
$Object setDataColumnName 5 "Tkk" 

set count 0
for { set u -3.1415 } { $u < 3.1415 } { set u [expr $u+0.1] } {
   for { set v -3.1415 } { $v < 3.1415 } { set v [expr $v+0.6] } {
       set x [expr (10-$v*sin($u/2))*sin($u)]
       set y [expr (10-$v*sin($u/2))*cos($u)]
       set z [expr $v*cos($u/2.0)]
       $Object addPoint $x $y $z
       # create a tensor field
       $Object setDataValue 0 $count $u
       $Object setDataValue 1 $count 0
       $Object setDataValue 2 $count 0
       $Object setDataValue 3 $count $v
       $Object setDataValue 4 $count 0
       $Object setDataValue 5 $count 1
       incr count
   }
}
$Object computeBounds # compute the BoundingBox of the cluster


set hideNewModules 1
[ load ${AMIRA_ROOT}/data/colormaps/physics.icol ] setLabel physics.icol
physics.icol setIconPosition 20 40
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
create HxArbitraryCut {EmptyPlane}
EmptyPlane setIconPosition 407 10
EmptyPlane data connect Cluster
EmptyPlane fire
EmptyPlane options setValue 0 1
EmptyPlane options setValue 1 0
EmptyPlane options setValue 2 1
EmptyPlane options setValue 3 0
EmptyPlane translate setMinMax 0 100
EmptyPlane translate setButtons 1
EmptyPlane translate setIncrement 1
EmptyPlane translate setValue 50
EmptyPlane translate setSubMinMax 0 100
EmptyPlane orientation untouch
EmptyPlane setPlane 0.104024 -1.48661 -0.141469 1 0 0 0 1 0
EmptyPlane fire
EmptyPlane setViewerMask 16382
EmptyPlane select
EmptyPlane setShadowStyle 0

set hideNewModules 0
create HxTensorDisplay {TensorDisplay}
TensorDisplay setIconPosition 407 30
TensorDisplay data connect Cluster
TensorDisplay module connect EmptyPlane
TensorDisplay Colormap setDefaultColor 1 0.8 0.5
TensorDisplay Colormap setDefaultAlpha 0.500000
TensorDisplay Colormap connect physics.icol
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
TensorDisplay DisplayComplexity setValue 0.2
TensorDisplay DisplayComplexity setSubMinMax 0 1
TensorDisplay Resolution setMinMax 0 1 1000
TensorDisplay Resolution setValue 0 30
TensorDisplay Resolution setMinMax 1 1 1000
TensorDisplay Resolution setValue 1 30
TensorDisplay MaskExpr setState A>0
TensorDisplay Offset setMinMax -5 5
TensorDisplay Offset setButtons 0
TensorDisplay Offset setIncrement 0.666667
TensorDisplay Offset setValue 0
TensorDisplay Offset setSubMinMax -5 5
TensorDisplay Scale setMinMax 0 200
TensorDisplay Scale setButtons 0
TensorDisplay Scale setIncrement 13.3333
TensorDisplay Scale setValue 0.3
TensorDisplay Scale setSubMinMax 0 200
{TensorDisplay} fire
{TensorDisplay} setVolumeModeSkip 2
{TensorDisplay} setVolumeMode 0
{TensorDisplay} setSigmoidSteepness 1
{TensorDisplay} setPointSize 1
TensorDisplay fire
TensorDisplay setViewerMask 16383
TensorDisplay select
TensorDisplay setShadowStyle 0
TensorDisplay action hit
TensorDisplay fire

set hideNewModules 0

viewer setCameraOrientation -0.766769 -0.273342 -0.580818 5.04401
viewer setCameraPosition 14.6661 -18.4534 12.1421
viewer setCameraFocalDistance 25.4716
viewer setCameraNearDistance 9.2826
viewer setCameraFarDistance 41.4926
viewer setCameraType perspective
viewer setCameraHeightAngle 44.9023

viewer 0 setAutoRedraw 1
viewer 0 redraw
