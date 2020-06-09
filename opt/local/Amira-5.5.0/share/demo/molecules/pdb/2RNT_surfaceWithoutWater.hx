# Amira Script
if { ![app hasLicense MolecularPack] } { 
	theMsg error "This script requires a MolecularPack license." 
	return 
} 

remove -all
remove physics.icol 2RNT.pdb CompMolSurface 2RNT-surf MolSurfaceView MoleculeLabel

# Create viewers
viewer setVertical 0

viewer 0 show
#viewer 0 setSize 2103 825
viewer 0 setBackgroundMode 1
viewer 0 decoration 1
viewer 0 setTransparencyType 6
viewer 0 setAutoRedraw 0

mainWindow show

set hideNewModules 1
[ load ${AMIRA_ROOT}/data/colormaps/physics.icol ] setLabel physics.icol
physics.icol setIconPosition 0 0
physics.icol fire
{physics.icol} setMinMax 0 1
{physics.icol} flags setValue 0
{physics.icol} shift setMinMax -1 1
{physics.icol} shift setValue 0
{physics.icol} scale setMinMax 0 1
{physics.icol} scale setValue 1
physics.icol fire
physics.icol setViewerMask 16383

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
{CompMolSurface} selectAtoms zab HIJMPLPPJPPGIABBIIBJJAAAJAPLABAALAEIGKII 0
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
{CompMolSurface} options setValue 0 0
{CompMolSurface} options setValue 1 0
{CompMolSurface} options setValue 2 0
{CompMolSurface} doIt setIndex -1
{CompMolSurface} doIt untouch
CompMolSurface fire
CompMolSurface setViewerMask 16383

set hideNewModules 0
[ {CompMolSurface} create
 ] setLabel {2RNT-surf}
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
{MolSurfaceView} discreteColormap setLocalMinMax 1.000000 22.000000
MolSurfaceView discreteColormap connect physics.icol
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
{MolSurfaceView} colorscheme setOptValue 0 1
{MolSurfaceView} colorscheme setOptValue 1 0
{MolSurfaceView} defineColor setIndex -1
{MolSurfaceView} defineColor untouch
{MolSurfaceView} fire
MolSurfaceView hideBox 1
{MolSurfaceView} selectTriangles zab HIJMONMBDBABAAAAAAMCKAPOKJGHAJEPKAAAAAIAJHABMKNGFFEG
{MolSurfaceView} fire
{MolSurfaceView} continuousColormap setLocalMinMax 0.000000 255.000000
{MolSurfaceView} discreteColormap setLocalMinMax 1.000000 22.000000
{MolSurfaceView} setScheme Color residues type
MolSurfaceView fire
MolSurfaceView setViewerMask 16383

set hideNewModules 0
create HxMolLabel {MoleculeLabel}
MoleculeLabel setIconPosition 283 10
MoleculeLabel data connect 2RNT.pdb
MoleculeLabel fire
{MoleculeLabel} levels setIndex 0 2
{MoleculeLabel} attributes setIndex 0 0
{MoleculeLabel} attributes setIndex 1 1
{MoleculeLabel} levelOption setValue 0 1
{MoleculeLabel} buttons setIndex -1
{MoleculeLabel} buttons untouch
{MoleculeLabel} fontSize setMinMax 5 30
{MoleculeLabel} fontSize setValue 14
{MoleculeLabel} color setColor 0 0 0 0
{MoleculeLabel} options setValue 0 1
{MoleculeLabel} options setValue 1 1
{MoleculeLabel} setLabelSetInfo 0 1 0.95 0.85 0.1 0 7 14
{MoleculeLabel} setLabelSetInfo 1 1 0.95 0.85 0.1 0 2 14
{MoleculeLabel} setLabelSetInfo 2 1 0 0 0 0 1 14
{MoleculeLabel} setLabelString residues/NIL8 "SER  NIL8"
{MoleculeLabel} setLabelString residues/NIL9 "ASN  NIL9"
{MoleculeLabel} setLabelString residues/NIL12 "SER  NIL12"
{MoleculeLabel} setLabelString residues/NIL13 "SER  NIL13"
{MoleculeLabel} setLabelString residues/NIL14 "SER  NIL14"
{MoleculeLabel} setLabelString residues/NIL17 "SER  NIL17"
{MoleculeLabel} setLabelString residues/NIL35 "SER  NIL35"
{MoleculeLabel} setLabelString residues/NIL36 "ASN  NIL36"
{MoleculeLabel} setLabelString residues/NIL37 "SER  NIL37"
{MoleculeLabel} setLabelString residues/NIL43 "ASN  NIL43"
{MoleculeLabel} setLabelString residues/NIL44 "ASN  NIL44"
{MoleculeLabel} setLabelString residues/NIL51 "SER  NIL51"
{MoleculeLabel} setLabelString residues/NIL53 "SER  NIL53"
{MoleculeLabel} setLabelString residues/NIL54 "SER  NIL54"
{MoleculeLabel} setLabelString residues/NIL63 "SER  NIL63"
{MoleculeLabel} setLabelString residues/NIL64 "SER  NIL64"
{MoleculeLabel} setLabelString residues/NIL69 "SER  NIL69"
{MoleculeLabel} setLabelString residues/NIL72 "SER  NIL72"
{MoleculeLabel} setLabelString residues/NIL81 "ASN  NIL81"
{MoleculeLabel} setLabelString residues/NIL83 "ASN  NIL83"
{MoleculeLabel} setLabelString residues/NIL84 "ASN  NIL84"
{MoleculeLabel} setLabelString residues/NIL96 "SER  NIL96"
{MoleculeLabel} setLabelString residues/NIL98 "ASN  NIL98"
{MoleculeLabel} setLabelString residues/NIL99 "ASN  NIL99"
{MoleculeLabel} setLabelSetInfo 3 1 0.95 0.85 0.1 0 2 14
{MoleculeLabel} setLabelSetInfo 4 1 0.95 0.85 0.1 0 2 14
{MoleculeLabel} setLabelSetInfo 5 1 0.95 0.85 0.1 0 3 14
MoleculeLabel fire
MoleculeLabel setViewerMask 16383
MoleculeLabel select

set hideNewModules 0


viewer 0 setCameraPosition 48.7633 82.0231 14.3415
viewer 0 setCameraOrientation 0.874702 -0.0841755 0.477296 4.41789
viewer 0 setCameraFocalDistance 53.393
viewer 0 setAutoRedraw 1
viewer 0 redraw
