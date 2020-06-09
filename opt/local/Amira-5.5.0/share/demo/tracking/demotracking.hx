# Amira Script
if { ![app hasLicense VRPack MeshPack] } { 
	theMsg error "This script requires a VRPack MeshPack license." 
	return 
} 
remove -all
remove physics.icol grid Kepsilon Kturbulent Pressure Velocity Viscosity GridVolume FieldCut

# Create viewers
viewer 0 show
viewer 0 setBackgroundMode 1
viewer 0 setTransparencyType 6
viewer 0 setAutoRedraw 0

set hideNewModules 1
[ load ${AMIRA_ROOT}/data/colormaps/physics.icol ] setLabel physics.icol
physics.icol setIconPosition 20 219
physics.icol fire
{physics.icol} setMinMax -2000 10
{physics.icol} flags setValue 0
{physics.icol} shift setMinMax -1 1
{physics.icol} shift setValue 0
{physics.icol} scale setMinMax 0 1
{physics.icol} scale setValue 1
physics.icol fire
physics.icol setViewerMask 16383

set hideNewModules 0
if { ![info exists TMPIO23] } { set TMPIO23 [load ${AMIRA_ROOT}/data/tutorials/turbine.am] }
[ lindex $TMPIO23 0 ] setLabel grid
grid setIconPosition 18 8
grid fire
grid fire
grid setViewerMask 16383

set hideNewModules 0
if { ![info exists TMPIO23] } { set TMPIO23 [load ${AMIRA_ROOT}/data/tutorials/turbine.am] }
[ lindex $TMPIO23 1 ] setLabel Kepsilon
Kepsilon setIconPosition 20 40
Kepsilon grid connect grid
Kepsilon fire
Kepsilon fire
Kepsilon setViewerMask 16383

set hideNewModules 0
if { ![info exists TMPIO23] } { set TMPIO23 [load ${AMIRA_ROOT}/data/tutorials/turbine.am] }
[ lindex $TMPIO23 2 ] setLabel Kturbulent
Kturbulent setIconPosition 20 70
Kturbulent grid connect grid
Kturbulent fire
Kturbulent fire
Kturbulent setViewerMask 16383

set hideNewModules 0
if { ![info exists TMPIO23] } { set TMPIO23 [load ${AMIRA_ROOT}/data/tutorials/turbine.am] }
[ lindex $TMPIO23 3 ] setLabel Pressure
Pressure setIconPosition 20 100
Pressure grid connect grid
Pressure fire
Pressure fire
Pressure setViewerMask 16383

set hideNewModules 0
if { ![info exists TMPIO23] } { set TMPIO23 [load ${AMIRA_ROOT}/data/tutorials/turbine.am] }
[ lindex $TMPIO23 4 ] setLabel Velocity
Velocity setIconPosition 20 130
Velocity grid connect grid
Velocity fire
Velocity fire
Velocity setViewerMask 16383

set hideNewModules 0
if { ![info exists TMPIO23] } { set TMPIO23 [load ${AMIRA_ROOT}/data/tutorials/turbine.am] }
[ lindex $TMPIO23 5 ] setLabel Viscosity
Viscosity setIconPosition 20 160
Viscosity grid connect grid
Viscosity fire
Viscosity fire
Viscosity setViewerMask 16383

set hideNewModules 0
create HxGridVolume {GridVolume}
GridVolume setIconPosition 199 45
{GridVolume} data connect {grid}
{GridVolume} fire
GridVolume data connect grid
GridVolume colorField connect Pressure
{GridVolume} colormap setDefaultColor 1 0.1 0.1
{GridVolume} colormap setDefaultAlpha 0.500000
GridVolume colormap connect physics.icol
GridVolume fire
{GridVolume} drawStyle setValue 0
{GridVolume} drawStyle setTexture 0
{GridVolume} drawStyle setNormalBinding 0
{GridVolume} materials setIndex 0 0
{GridVolume} colorMode setValue 0
{GridVolume} fire
{GridVolume} selectTetra zab HIJMPLPPHPBEIMICFBDAAKEGMBCIBIAFADAJBIJIPPPPAHAAFHOHIGNP
GridVolume fire
GridVolume setViewerMask 16383

set hideNewModules 0
create HxFieldCut {FieldCut}
FieldCut setIconPosition 205 100
FieldCut data connect Pressure
{FieldCut} colormap setDefaultColor 1 0.8 0.5
{FieldCut} colormap setDefaultAlpha 0.500000
FieldCut colormap connect physics.icol
FieldCut fire
{FieldCut} orientation setIndex -1
{FieldCut} orientation untouch
{FieldCut} options setValue 0 0
{FieldCut} options setValue 1 0
{FieldCut} options setValue 2 0
{FieldCut} translate setMinMax 0 100
{FieldCut} translate setValue 49
{FieldCut} texture setValue 0
{FieldCut} selection setIndex -1
{FieldCut} selection untouch
{FieldCut} selection setOptValue 0 0
{FieldCut} orientation untouch
{FieldCut} setPlane 0 1.05546 0.45199 1 0 0 0 1 0
FieldCut fire
FieldCut setViewerMask 0


create HxDisplayISL {DisplayISL}
{DisplayISL} setIconPosition 203 138
{DisplayISL} setViewerMask 0
{DisplayISL} {data} connect {Velocity}
{DisplayISL} fire
{DisplayISL} setLineWidth 1.000000
{DisplayISL} setLineSmooth 1
{DisplayISL} setBalance 0
{DisplayISL} box setValue 1
{DisplayISL} setBoxType 1
{DisplayISL} setBoxTranslation -0.0322806 0.642238 0.221058
{DisplayISL} setBoxScale 0.270811 0.257261 0.0675248
{DisplayISL} colormap setDefaultColor 1 1 1
{DisplayISL} colormap setDefaultAlpha 1.000000
{DisplayISL} numLines setMinMax 0 500
{DisplayISL} numLines setValue 140
{DisplayISL} length setMinMax 1 250
{DisplayISL} length setValue 110
{DisplayISL} opacity setMinMax 0 1
{DisplayISL} opacity setValue 0.568807
{DisplayISL} fadeFactor setMinMax 0.9 1
{DisplayISL} fadeFactor setValue 1
{DisplayISL} alphaRange setValue 0 0
{DisplayISL} alphaRange setValue 1 100
{DisplayISL} options setValue 0 1
{DisplayISL} options setValue 1 1
{DisplayISL} options setValue 2 0
{DisplayISL} distribute setIndex 0
{DisplayISL} distribute untouch
{DisplayISL} distribute setOptValue 0
{DisplayISL} fire
{DisplayISL} distribute snap 0 1
{DisplayISL} update
{DisplayISL} fire
{DisplayISL} setViewerMask 0

set hideNewModules 0

load $SCRIPTDIR/Scenario.scro
Scenario.scro select
Scenario.scro Action setPin 1
Scenario.scro deselect

viewer 0 setCameraPosition 3.55266 1.0053 3.07733
viewer 0 setCameraOrientation 0.384404 0.522992 0.760731 1.50672
viewer 0 setCameraFocalDistance 4.46526
viewer 0 setAutoRedraw 1
viewer 0 redraw

if { ![exists Tracking] && ![exists VRSettings] } {
    create HxTracking
    VRSettings config setOptValueString vrtest.cfg
    VRSettings options setValue 0 1
    VRSettings fire
    VRSettings options setValue 2 1
    VRSettings action setValue 0 0
    VRSettings fire
}
VRSettings select

menu reset
menu insertItem -id 0 -bg "0.7 0 0" -text "Geometry" -proc "Geometry"
menu insertItem -id 1 -bg "0 0.7 0" -text "Pressure" -proc "Pressure"
menu insertItem -id 2 -bg "0 0 0.7" -text "Velocity" -proc "Velocity"

