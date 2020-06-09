# Amira Script
if { ![app hasLicense MolecularPack] } { 
	theMsg error "This script requires a MolecularPack license." 
	return 
} 

remove -all
remove 2JEL.pdb SecStructureView

# Create viewers
viewer setVertical 0

viewer 0 show
#viewer 0 setSize 906 825
viewer 0 setBackgroundMode 1
viewer 0 decoration 1
viewer 0 setTransparencyType 6
viewer 0 setAutoRedraw 0

mainWindow show

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/molecules/pdb/2JEL.pdb ] setLabel 2JEL.pdb
2JEL.pdb setIconPosition 18 24
{2JEL.pdb} fire
2JEL.pdb time setMinMax 0 1
2JEL.pdb time setSubMinMax 0 1
2JEL.pdb time setValue 0
2JEL.pdb time setDiscrete 1
2JEL.pdb time setIncrement 1
{2JEL.pdb} transformation setIndex 0 0
{2JEL.pdb} selection setIndex -1
{2JEL.pdb} selection untouch
{2JEL.pdb} selection setOptValue 0 0
{2JEL.pdb} selectionBrowser setIndex -1
{2JEL.pdb} selectionBrowser untouch
{2JEL.pdb} transform setIndex -1
{2JEL.pdb} transform untouch
2JEL.pdb setTransform 1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1
2JEL.pdb fire
2JEL.pdb setViewerMask 16383

set hideNewModules 0
create HxSecStructure {SecStructureView}
SecStructureView setIconPosition 252 24
SecStructureView data connect 2JEL.pdb
{SecStructureView} discreteColormapBB setDefaultColor 0.78 0.78 0.78
{SecStructureView} discreteColormapBB setDefaultAlpha 1.000000
{SecStructureView} discreteColormapBB setLocalRange 1
{SecStructureView} discreteColormapBB setLocalMinMax 0.000000 255.000000
{SecStructureView} continuousColormapBB setDefaultColor 0.78 0.78 0.78
{SecStructureView} continuousColormapBB setDefaultAlpha 1.000000
{SecStructureView} continuousColormapBB setLocalRange 1
{SecStructureView} continuousColormapBB setLocalMinMax 1.000000 589.000000
{SecStructureView} discreteColormapH setDefaultColor 0.3 0.3 0.9
{SecStructureView} discreteColormapH setDefaultAlpha 1.000000
{SecStructureView} discreteColormapH setLocalRange 1
{SecStructureView} discreteColormapH setLocalMinMax 0.000000 255.000000
{SecStructureView} continuousColormapH setDefaultColor 0.3 0.3 0.9
{SecStructureView} continuousColormapH setDefaultAlpha 1.000000
{SecStructureView} continuousColormapH setLocalRange 1
{SecStructureView} continuousColormapH setLocalMinMax 1.000000 589.000000
{SecStructureView} discreteColormapS setDefaultColor 0.9 0.2 0.2
{SecStructureView} discreteColormapS setDefaultAlpha 1.000000
{SecStructureView} discreteColormapS setLocalRange 1
{SecStructureView} discreteColormapS setLocalMinMax 0.000000 255.000000
{SecStructureView} continuousColormapS setDefaultColor 0.862745 0.0901961 0.0901961
{SecStructureView} continuousColormapS setDefaultAlpha 1.000000
{SecStructureView} continuousColormapS setLocalRange 1
{SecStructureView} continuousColormapS setLocalMinMax 1.000000 589.000000
{SecStructureView} discreteColormapT setDefaultColor 0.4 0.4 0.4
{SecStructureView} discreteColormapT setDefaultAlpha 1.000000
{SecStructureView} discreteColormapT setLocalRange 1
{SecStructureView} discreteColormapT setLocalMinMax 0.000000 255.000000
{SecStructureView} continuousColormapT setDefaultColor 0.4 0.4 0.4
{SecStructureView} continuousColormapT setDefaultAlpha 1.000000
{SecStructureView} continuousColormapT setLocalRange 1
{SecStructureView} continuousColormapT setLocalMinMax 1.000000 589.000000
{SecStructureView} fire
{SecStructureView} selectAtoms zab HIJMPLPPHPBEIMEEAAAAEJNNPGBI
{SecStructureView} generalShape setValue 0
{SecStructureView} generalThreadsWidth setMinMax 0.5 4
{SecStructureView} generalThreadsWidth setValue 2
{SecStructureView} generalRibbonWidth setMinMax 0.5 4
{SecStructureView} generalRibbonWidth setValue 2
{SecStructureView} options setValue 2
{SecStructureView} backboneTubeRadius setMinMax 0.100000001490116 0.5
{SecStructureView} backboneTubeRadius setValue 0.2
{SecStructureView} colorschemeBB setIndex -1
{SecStructureView} colorschemeBB untouch
{SecStructureView} colorschemeBB setOptValue 0 0
{SecStructureView} colorschemeBB setOptValue 1 2
{SecStructureView} defineColorBB setIndex -1
{SecStructureView} defineColorBB untouch
{SecStructureView} helixShape setValue 1
{SecStructureView} helixTubeRadius setMinMax 0.100000001490116 2
{SecStructureView} helixTubeRadius setValue 0.5
{SecStructureView} helixCylinderRadius setMinMax 1 4
{SecStructureView} helixCylinderRadius setValue 2.1
{SecStructureView} helixRibbonWidth setMinMax 0.5 5
{SecStructureView} helixRibbonWidth setValue 3
{SecStructureView} colorschemeH setIndex -1
{SecStructureView} colorschemeH untouch
{SecStructureView} colorschemeH setOptValue 0 0
{SecStructureView} colorschemeH setOptValue 1 2
{SecStructureView} defineColorH setIndex -1
{SecStructureView} defineColorH untouch
{SecStructureView} sheetShape setValue 1
{SecStructureView} sheetArrowWidth setMinMax 0.5 5
{SecStructureView} sheetArrowWidth setValue 1.5
{SecStructureView} sheetArrowOptions setValue 0 1
{SecStructureView} sheetArrowOptions setValue 1 1
{SecStructureView} sheetArrowOptions setValue 2 1
{SecStructureView} sheetRadius setMinMax 0.100000001490116 2
{SecStructureView} sheetRadius setValue 0.3
{SecStructureView} colorschemeS setIndex -1
{SecStructureView} colorschemeS untouch
{SecStructureView} colorschemeS setOptValue 0 0
{SecStructureView} colorschemeS setOptValue 1 2
{SecStructureView} defineColorS setIndex -1
{SecStructureView} defineColorS untouch
{SecStructureView} turnTubeRadius setMinMax 0.100000001490116 2
{SecStructureView} turnTubeRadius setValue 0.3
{SecStructureView} colorschemeT setIndex -1
{SecStructureView} colorschemeT untouch
{SecStructureView} colorschemeT setOptValue 0 0
{SecStructureView} colorschemeT setOptValue 1 2
{SecStructureView} defineColorT setIndex -1
{SecStructureView} defineColorT untouch
{SecStructureView} structures setValue 0 1
{SecStructureView} structures setValue 1 1
{SecStructureView} structures setValue 2 1
{SecStructureView} structures setValue 3 1
{SecStructureView} complexity setMinMax 0 1
{SecStructureView} complexity setValue 0.5
{SecStructureView} buffer setIndex -1
{SecStructureView} buffer untouch
{SecStructureView} fire
{SecStructureView} discreteColormapBB setLocalMinMax 0.000000 255.000000
{SecStructureView} continuousColormapBB setLocalMinMax 1.000000 589.000000
{SecStructureView} setScheme BackboneColor residues index
{SecStructureView} discreteColormapH setLocalMinMax 0.000000 255.000000
{SecStructureView} continuousColormapH setLocalMinMax 1.000000 589.000000
{SecStructureView} setScheme HelixColor residues index
{SecStructureView} discreteColormapS setLocalMinMax 0.000000 255.000000
{SecStructureView} continuousColormapS setLocalMinMax 1.000000 589.000000
{SecStructureView} setScheme SheetColor residues index
{SecStructureView} discreteColormapT setLocalMinMax 0.000000 255.000000
{SecStructureView} continuousColormapT setLocalMinMax 1.000000 589.000000
{SecStructureView} setScheme TurnColor residues index
SecStructureView fire
SecStructureView setViewerMask 16383
SecStructureView select

set hideNewModules 0


viewer 0 setCameraPosition -21.6332 15.8907 76.0604
viewer 0 setCameraOrientation 0.427842 0.164576 -0.888744 4.63103
viewer 0 setCameraFocalDistance 113.5
viewer 0 setAutoRedraw 1
viewer 0 redraw
