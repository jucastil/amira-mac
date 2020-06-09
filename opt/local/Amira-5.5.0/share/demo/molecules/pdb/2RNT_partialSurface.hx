# Amira Script
if { ![app hasLicense MolecularPack] } { 
	theMsg error "This script requires a MolecularPack license." 
	return 
} 

remove -all
remove 2RNT.pdb CompMolSurface MoleculeView 2RNT-surf MolSurfaceView

# Create viewers
viewer setVertical 0

viewer 0 show
#viewer 0 setSize 2103 825
viewer 0 setBackgroundMode 1
viewer 0 decoration 1
viewer 0 setTransparencyType 6
viewer 0 setAutoRedraw 0

mainWindow show

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/molecules/pdb/2RNT.pdb ] setLabel 2RNT.pdb
2RNT.pdb setIconPosition 20 10
{2RNT.pdb} fire
2RNT.pdb time setMinMax 0 1
2RNT.pdb time setSubMinMax 0 1
2RNT.pdb time setValue 0
2RNT.pdb time setDiscrete 1
2RNT.pdb time setIncrement 1
{2RNT.pdb} transformation setIndex 0 0
{2RNT.pdb} selection setIndex -1
{2RNT.pdb} selection untouch
{2RNT.pdb} selection setOptValue 0 0
{2RNT.pdb} selectionBrowser setIndex -1
{2RNT.pdb} selectionBrowser untouch
{2RNT.pdb} transform setIndex -1
{2RNT.pdb} transform untouch
#{2RNT.pdb} createSelectionBrowser 
#{2RNT.pdb} showSelectionBrowser 
#{2RNT.pdb} selectionBrowserSetMasterLevel residues
2RNT.pdb setTransform 1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1
2RNT.pdb fire
2RNT.pdb setViewerMask 16383

set hideNewModules 0
create HxCompMolSurface {CompMolSurface}
CompMolSurface setIconPosition 160 10
CompMolSurface Molecule connect 2RNT.pdb
{CompMolSurface} fire
{CompMolSurface} selectAtoms zab HIJMPLPPHPGAAAAAEBMAHHIJ 0
{CompMolSurface} buffer setIndex -1
{CompMolSurface} buffer untouch
{CompMolSurface} buffer setIndex -1
{CompMolSurface} buffer untouch
{CompMolSurface} surfaceType setValue 2
{CompMolSurface} quality setValue 0
{CompMolSurface} probeRadius setMinMax 0.5 3
{CompMolSurface} probeRadius setValue 1.4
{CompMolSurface} edgeLength setMinMax 0.239999994635582 3.40000009536743
{CompMolSurface} edgeLength setValue 0.759836
{CompMolSurface} nopPerA2 setMinMax 0.100000001490116 20
{CompMolSurface} nopPerA2 setValue 2
{CompMolSurface} options setValue 0 1
{CompMolSurface} options setValue 1 1
{CompMolSurface} options setValue 2 0
{CompMolSurface} doIt setIndex -1
{CompMolSurface} doIt untouch
CompMolSurface fire
CompMolSurface setViewerMask 16383

set hideNewModules 0
create HxMolView {MoleculeView}
MoleculeView setIconPosition 286 10
MoleculeView data connect 2RNT.pdb
{MoleculeView} continuousColormap setDefaultColor 0 0 1
{MoleculeView} continuousColormap setDefaultAlpha 1.000000
{MoleculeView} continuousColormap setLocalRange 1
{MoleculeView} continuousColormap setLocalMinMax 0.000000 255.000000
{MoleculeView} discreteColormap setDefaultColor 0 0 1
{MoleculeView} discreteColormap setDefaultAlpha 1.000000
{MoleculeView} discreteColormap setLocalRange 1
{MoleculeView} discreteColormap setLocalMinMax 6.000000 20.000000
{MoleculeView} fire
{MoleculeView} selectAtoms zab HIJMPLPPHPGAAAAAEBMAHHIJ
{MoleculeView} mode setValue 1
{MoleculeView} quality setValue 0
{MoleculeView} options setValue 0 0
{MoleculeView} options setValue 1 0
{MoleculeView} options setValue 2 0
{MoleculeView} atomRadius setMinMax 0 2
{MoleculeView} atomRadius setValue 0.1
{MoleculeView} bondRadius setMinMax 0 0.5
{MoleculeView} bondRadius setValue 0.05
{MoleculeView} lineWidth setMinMax 1 3
{MoleculeView} lineWidth setValue 2
{MoleculeView} complexity setMinMax 0 1
{MoleculeView} complexity setValue 0.2
{MoleculeView} twistFactor setMinMax 0.5 2
{MoleculeView} twistFactor setValue 1
{MoleculeView} colorscheme setIndex -1
{MoleculeView} colorscheme untouch
{MoleculeView} colorscheme setOptValue 0 0
{MoleculeView} colorscheme setOptValue 1 0
{MoleculeView} defineColor setIndex -1
{MoleculeView} defineColor untouch
{MoleculeView} highlighting setIndex -1
{MoleculeView} highlighting untouch
{MoleculeView} buffer setIndex -1
{MoleculeView} buffer untouch
{MoleculeView} fire
{MoleculeView} continuousColormap setLocalMinMax 0.000000 255.000000
{MoleculeView} discreteColormap setLocalMinMax 6.000000 20.000000
{MoleculeView} setScheme Color atoms atomic_number
MoleculeView fire
MoleculeView setViewerMask 16383

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/molecules/pdb/2RNT_partialSurface-files/2RNT-surf ] setLabel 2RNT-surf
2RNT-surf setIconPosition 20 40
2RNT-surf master connect CompMolSurface
2RNT-surf fire
2RNT-surf fire
2RNT-surf setViewerMask 16383

set hideNewModules 0
create HxMolSurfaceView {MolSurfaceView}
MolSurfaceView setIconPosition 274 40
MolSurfaceView data connect 2RNT-surf
{MolSurfaceView} fire
{MolSurfaceView} colormap setDefaultColor 1 0.1 0.1
{MolSurfaceView} colormap setDefaultAlpha 0.500000
MolSurfaceView molecule connect 2RNT.pdb
{MolSurfaceView} continuousColormap setDefaultColor 0 0 1
{MolSurfaceView} continuousColormap setDefaultAlpha 1.000000
{MolSurfaceView} continuousColormap setLocalRange 1
{MolSurfaceView} continuousColormap setLocalMinMax 0.000000 255.000000
{MolSurfaceView} discreteColormap setDefaultColor 0 0 1
{MolSurfaceView} discreteColormap setDefaultAlpha 1.000000
{MolSurfaceView} discreteColormap setLocalRange 1
{MolSurfaceView} discreteColormap setLocalMinMax 6.000000 20.000000
{MolSurfaceView} fire
{MolSurfaceView} selectAtoms zab HIJMPLPPHPGAAAAAEBMAHHIJ 0
{MolSurfaceView} drawStyle setValue 1
{MolSurfaceView} drawStyle setTexture 0
{MolSurfaceView} drawStyle setNormalBinding 1
{MolSurfaceView} baseTrans setMinMax 0 1
{MolSurfaceView} baseTrans setValue 0.8
{MolSurfaceView} colorMode setValue 1
{MolSurfaceView} defaultColors setColor 0 0.5 0.5 0.5
{MolSurfaceView} defaultColors setColor 1 0.3 0.3 0.8
{MolSurfaceView} pickAction setValue 0
{MolSurfaceView} selectionDistance setMinMax 0.100000001490116 100
{MolSurfaceView} selectionDistance setValue 10
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
{MolSurfaceView} defineColor setIndex -1
{MolSurfaceView} defineColor untouch
{MolSurfaceView} fire
MolSurfaceView hideBox 1
{MolSurfaceView} selectTriangles zab HIJMPLPPHPBEAMEHAAAAHDDKNGDI
{MolSurfaceView} fire
{MolSurfaceView} continuousColormap setLocalMinMax 0.000000 255.000000
{MolSurfaceView} discreteColormap setLocalMinMax 6.000000 20.000000
{MolSurfaceView} setScheme Color atoms atomic_number
MolSurfaceView fire
MolSurfaceView setViewerMask 16383
MolSurfaceView select

set hideNewModules 0


viewer 0 setCameraPosition 22.2946 33.8987 57.2756
viewer 0 setCameraOrientation 0.00920047 -0.109904 0.9939 4.40504
viewer 0 setCameraFocalDistance 44.0377
viewer 0 setAutoRedraw 1
viewer 0 redraw
