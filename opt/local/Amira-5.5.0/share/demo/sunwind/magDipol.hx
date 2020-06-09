# Amira Script
if { ![app hasLicense MeshPack] } { 
	theMsg error "This script requires a MeshPack license." 
	return 
} 

remove -all

set SUNWINDATADIR ${AMIRA_ROOT}/data/misc

# Create viewers
viewer 0 show
viewer 0 decoration 1
viewer 0 setBackgroundMode 1
viewer 0 setAutoRedraw 0

mainWindow show

set hideNewModules 0
create HxAnnaScalarField3 {ScalarField}
{ScalarField} setIconPosition 20 70
{ScalarField} setViewerMask 0
{ScalarField} expr setValue "exp(-(x*x+4*y*y+z*z/2))"
{ScalarField} setBoundingBox -1 1 -1 1 -1 1
{ScalarField} update
{ScalarField} fire
{ScalarField} setViewerMask 16383

set hideNewModules 0
[ load ${SUNWINDATADIR}/earth.iv ] setLabel earth.iv
{earth.iv} setIconPosition 20 10
{earth.iv} setViewerMask 0
{earth.iv} update
{earth.iv} fire
{earth.iv} setViewerMask 16383

set hideNewModules 0
create HxIvDisplay {IvDisplay}
{IvDisplay} setIconPosition 323 10
{IvDisplay} setViewerMask 0
{IvDisplay} {data} connect {earth.iv}
{IvDisplay} drawStyle setValue 0
{IvDisplay} update
{IvDisplay} fire
{IvDisplay} setViewerMask 16383

set hideNewModules 0
create HxMagDipol {MagDipol}
{MagDipol} setIconPosition 20 40
{MagDipol} setViewerMask 0
{MagDipol} phi setMinMax -180 180
{MagDipol} phi setValue 135
{MagDipol} b setMinMax 0 25
{MagDipol} b setValue 10
{MagDipol} update
{MagDipol} fire
{MagDipol} setViewerMask 16383
{MagDipol} select

set hideNewModules 0
create HxDisplayISL {DisplayISL}
{DisplayISL} setIconPosition 315 40
{DisplayISL} setViewerMask 0
{DisplayISL} {data} connect {MagDipol}
{DisplayISL} fire
{DisplayISL} setLineWidth 1.000000
{DisplayISL} setLineSmooth 1
{DisplayISL} setBalance 0
{DisplayISL} box setValue 2
{DisplayISL} setBoxType 1
{DisplayISL} setBoxTranslation 0 -0.0764129 0
{DisplayISL} setBoxScale 1 0.600569 1
{DisplayISL} {alphaField} connect {ScalarField}
{DisplayISL} colormap setDefaultColor 1 1 1
{DisplayISL} colormap setDefaultAlpha 1.000000
{DisplayISL} numLines setMinMax 0 500
{DisplayISL} numLines setValue 250
{DisplayISL} length setMinMax 1 250
{DisplayISL} length setValue 60
{DisplayISL} opacity setMinMax 0 1
{DisplayISL} opacity setValue 1
{DisplayISL} fadeFactor setMinMax 0.9 1
{DisplayISL} fadeFactor setValue 0.997248
{DisplayISL} alphaRange setMinMax 0 -1e+20 1e+20
{DisplayISL} alphaRange setValue 0 0
{DisplayISL} alphaRange setMinMax 1 -1e+20 1e+20
{DisplayISL} alphaRange setValue 1 1
{DisplayISL} options setValue 0 0
{DisplayISL} options setValue 1 1
{DisplayISL} options setValue 2 0
{DisplayISL} distribute setIndex 0
{DisplayISL} distribute untouch
{DisplayISL} distribute setOptValue 0
{DisplayISL} seed setValue 1
{DisplayISL} fire
{DisplayISL} distribute setIndex 0
{DisplayISL} update
{DisplayISL} fire
{DisplayISL} setViewerMask 16383
{DisplayISL} select

set hideNewModules 0

viewer 0 setCameraPosition -0.0245302 -4.16103 -0.135002
viewer 0 setCameraOrientation 0.581176 0.583233 -0.567515 2.12024
viewer 0 setCameraFocalDistance 4.1129
viewer 0 setAutoRedraw 1
viewer 0 redraw
