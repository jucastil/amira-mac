# Amira Script

# test(timeout=130)

if { ![app hasLicense MolecularPack] } { 
	theMsg error "This script requires a MolecularPack license." 
	return 
} 

remove -all
remove rna.mol MolTrajectory Molecule BondAngleView MolecularSurface Molecule.surf SurfaceView

# Create viewers
viewer 0 show
viewer 0 setBackgroundMode 1
viewer 0 decoration 1
viewer 0 setTransparencyType 6
viewer 0 setAutoRedraw 0

mainWindow show

set hideNewModules 0
[ load $AMIRA_ROOT/data/molecules/rna/rna.mol ] setLabel rna.mol
rna.mol setIconPosition 20 10
rna.mol fire
rna.mol fire
rna.mol setViewerMask 16383

set hideNewModules 0
create HxMolTrajectory {MolTrajectory}
MolTrajectory setIconPosition 20 39
MolTrajectory bundle connect rna.mol
{MolTrajectory} fire
{MolTrajectory} trajectory setIndex 0 3
MolTrajectory fire
MolTrajectory setViewerMask 16383

set hideNewModules 0
create HxMolecule {Molecule}
Molecule setIconPosition 20 70
Molecule data connect MolTrajectory
{Molecule} fire
Molecule time setMinMax 1 1
Molecule time setSubMinMax 1 1
Molecule time setValue 1
Molecule time setDiscrete 1
Molecule time setIncrement 1
{Molecule} selectionBrowser setIndex -1
{Molecule} selectionBrowser untouch
Molecule fire
Molecule setViewerMask 16383

set hideNewModules 0
create HxBondAngle {BondAngleView}
BondAngleView setIconPosition 288 70
BondAngleView data connect Molecule
{BondAngleView} colormap setDefaultColor 1 0.1 0.1
{BondAngleView} colormap setDefaultAlpha 0.500000
{BondAngleView} continuousColormap setDefaultColor 0 0 1
{BondAngleView} continuousColormap setDefaultAlpha 1.000000
{BondAngleView} discreteColormap setDefaultColor 0 0 1
{BondAngleView} discreteColormap setDefaultAlpha 1.000000
{BondAngleView} fire
{BondAngleView} selectAtoms zab HIJMPLPPJPPGAAAAKHMHGDJN
{BondAngleView} drawStyle setValue 0
{BondAngleView} drawStyle setTexture 0
{BondAngleView} drawStyle setNormalBinding 0
{BondAngleView} buffer setIndex -1
{BondAngleView} buffer untouch
{BondAngleView} transparency setMinMax 0 1
{BondAngleView} transparency setValue 0.5
{BondAngleView} colorMode setValue 0
{BondAngleView} colorscheme setIndex -1
{BondAngleView} colorscheme untouch
{BondAngleView} colorscheme setOptValue 0 0
{BondAngleView} colorscheme setOptValue 1 0
{BondAngleView} highlighting setIndex -1
{BondAngleView} highlighting untouch
{BondAngleView} buffer setIndex -1
{BondAngleView} buffer untouch
BondAngleView fire
BondAngleView setViewerMask 16383

set hideNewModules 0
create HxCompMolSurface {CompMolSurface}
CompMolSurface setIconPosition 160 70
CompMolSurface Molecule connect Molecule
{CompMolSurface} fire
{CompMolSurface} selectAtoms zab HIJMPLPPJPPGAAAAKHMHGDJN 0
{CompMolSurface} buffer setIndex -1
{CompMolSurface} buffer untouch
{CompMolSurface} buffer setIndex -1
{CompMolSurface} buffer untouch
{CompMolSurface} surfaceType setValue 2
{CompMolSurface} quality setValue 0
{CompMolSurface} probeRadius setMinMax 0.5 3
{CompMolSurface} probeRadius setValue 1.4
{CompMolSurface} edgeLength setMinMax 0.239999994635582 3.40000009536743
{CompMolSurface} edgeLength setValue 0.537285
{CompMolSurface} nopPerA2 setMinMax 0.100000001490116 20
{CompMolSurface} nopPerA2 setValue 4
{CompMolSurface} options setValue 0 0
{CompMolSurface} options setValue 1 0
{CompMolSurface} options setValue 2 0
{CompMolSurface} doIt setIndex -1
{CompMolSurface} doIt untouch
CompMolSurface fire
CompMolSurface setViewerMask 16383
CompMolSurface select

set hideNewModules 0
[ {CompMolSurface} create
 ] setLabel {Molecule.surf}
Molecule.surf setIconPosition 20 98
Molecule.surf master connect CompMolSurface
Molecule.surf fire
Molecule.surf fire
Molecule.surf setViewerMask 16383

set hideNewModules 0
create HxMolSurfaceView {MolSurfaceView}
MolSurfaceView setIconPosition 297 98
MolSurfaceView data connect Molecule.surf
{MolSurfaceView} fire
{MolSurfaceView} colormap setDefaultColor 1 0.1 0.1
{MolSurfaceView} colormap setDefaultAlpha 0.500000
MolSurfaceView molecule connect Molecule
{MolSurfaceView} continuousColormap setDefaultColor 0 0 1
{MolSurfaceView} continuousColormap setDefaultAlpha 1.000000
{MolSurfaceView} discreteColormap setDefaultColor 0 0 1
{MolSurfaceView} discreteColormap setDefaultAlpha 1.000000
{MolSurfaceView} fire
{MolSurfaceView} selectAtoms zab HIJMPLPPJPPGAAAAKHMHGDJN 0
{MolSurfaceView} drawStyle setValue 4
{MolSurfaceView} drawStyle setTexture 0
{MolSurfaceView} drawStyle setNormalBinding 1
{MolSurfaceView} baseTrans setMinMax 0 1
{MolSurfaceView} baseTrans setValue 0.8
{MolSurfaceView} colorMode setValue 1
{MolSurfaceView} defaultColors setColor 0 0.5 0.5 0.5
{MolSurfaceView} defaultColors setColor 1 0.3 0.3 0.8
{MolSurfaceView} buffer setIndex -1
{MolSurfaceView} buffer untouch
{MolSurfaceView} highlighting setIndex -1
{MolSurfaceView} highlighting untouch
{MolSurfaceView} buffer setIndex -1
{MolSurfaceView} buffer untouch
{MolSurfaceView} colorscheme setIndex -1
{MolSurfaceView} colorscheme untouch
{MolSurfaceView} colorscheme setOptValue 0 0
{MolSurfaceView} colorscheme setOptValue 1 0
{MolSurfaceView} fire
MolSurfaceView hideBox 1
{MolSurfaceView} selectTriangles zab HIJMONMBDBABAAAAAAMCKAPOKJGHAMBPKAAAAAAAOAGPKDPMJCDD
MolSurfaceView fire
MolSurfaceView setViewerMask 16383

set hideNewModules 0


viewer 0 setCameraPosition -0.436612 -0.830319 -25.8004
viewer 0 setCameraOrientation 0.999979 0.00181241 -0.00628985 3.12358
viewer 0 setCameraFocalDistance 44.3666
viewer 0 setAutoRedraw 1
viewer 0 redraw
