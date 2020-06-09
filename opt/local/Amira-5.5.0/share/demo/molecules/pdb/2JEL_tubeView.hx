# Amira Script
if { ![app hasLicense MolecularPack] } { 
	theMsg error "This script requires a MolecularPack license." 
	return 
} 

remove -all
remove temperature.icol 2JEL.pdb TubeView

# Create viewers
viewer setVertical 0

viewer 0 setBackgroundMode 1
viewer 0 setBackgroundColor 0.06 0.13 0.24
viewer 0 setBackgroundColor2 0.72 0.72 0.78
viewer 0 setTransparencyType 5
viewer 0 setAutoRedraw 0
viewer 0 show
mainWindow show

set hideNewModules 1
[ load ${AMIRA_ROOT}/data/colormaps/temperature.icol ] setLabel temperature.icol
temperature.icol setIconPosition 0 0
temperature.icol setNoRemoveAll 1
temperature.icol fire
{temperature.icol} setMinMax 38 44
temperature.icol flags setValue 1
temperature.icol shift setMinMax -1 1
temperature.icol shift setButtons 0
temperature.icol shift setIncrement 0.133333
temperature.icol shift setValue 0
temperature.icol shift setSubMinMax -1 1
temperature.icol scale setMinMax 0 1
temperature.icol scale setButtons 0
temperature.icol scale setIncrement 0.1
temperature.icol scale setValue 1
temperature.icol scale setSubMinMax 0 1
temperature.icol fire
temperature.icol setViewerMask 16383

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/molecules/pdb/2JEL.pdb ] setLabel 2JEL.pdb
2JEL.pdb setIconPosition 32 52
{2JEL.pdb} fire
2JEL.pdb time setMinMax 0 1
2JEL.pdb time setSubMinMax 0 1
2JEL.pdb time setValue 0
2JEL.pdb time setDiscrete 1
2JEL.pdb time setIncrement 1
2JEL.pdb time animationMode -once
2JEL.pdb transformation setIndex 0 0
2JEL.pdb selection setOptValue 0 0
{2JEL.pdb} fire
2JEL.pdb fire
2JEL.pdb setViewerMask 16383

set hideNewModules 0
create HxTubeView {TubeView}
TubeView setIconPosition 396 52
TubeView data connect 2JEL.pdb
TubeView discreteColormapColoring setDefaultColor 0.78 0.78 0.78
TubeView discreteColormapColoring setDefaultAlpha 1.000000
TubeView discreteColormapColoring setLocalRange 1
TubeView discreteColormapColoring setLocalMinMax 0.000000 1.000000
TubeView continuousColormapColoring setDefaultColor 0.78 0.78 0.78
TubeView continuousColormapColoring setDefaultAlpha 1.000000
TubeView continuousColormapColoring setLocalRange 1
TubeView continuousColormapColoring setLocalMinMax 1.000000 3.000000
TubeView continuousColormapColoring connect temperature.icol
{TubeView} fire
TubeView selectAtoms zab HIJMPLPPHPBEIMEEAAAAEJNNPGBI
TubeView part setState backbone
TubeView distanceCutoff setMinMax 0.100000001490116 100
TubeView distanceCutoff setButtons 0
TubeView distanceCutoff setIncrement 6.66
TubeView distanceCutoff setValue 20
TubeView distanceCutoff setSubMinMax 0.100000001490116 100
TubeView radius setMinMax 0.100000001490116 1
TubeView radius setButtons 0
TubeView radius setIncrement 0.06
TubeView radius setValue 0.2
TubeView radius setSubMinMax 0.100000001490116 1
TubeView complexity setMinMax 0 1
TubeView complexity setButtons 0
TubeView complexity setIncrement 0.1
TubeView complexity setValue 0.3
TubeView complexity setSubMinMax 0 1
TubeView interpolationMethod setIndex 0 1
TubeView capShape setValue 3
TubeView colorschemeColoring setOptValue 0 2
TubeView colorschemeColoring setOptValue 1 1
TubeView coloringMode setValue 1
TubeView highlightingColor setColor 0 0.949 0.847 0.09
{TubeView} fire
TubeView discreteColormapColoring setLocalMinMax 0.000000 1.000000
TubeView continuousColormapColoring setLocalMinMax 1.000000 3.000000
TubeView fire
TubeView setViewerMask 16383
TubeView select
TubeView setPickable 1

set hideNewModules 0


viewer 0 setCameraOrientation 0.427842 0.164576 -0.888744 4.63103
viewer 0 setCameraPosition -21.6332 15.8907 76.0604
viewer 0 setCameraFocalDistance 113.5
viewer 0 setCameraNearDistance 58.0155
viewer 0 setCameraFarDistance 169.919
viewer 0 setCameraType perspective
viewer 0 setCameraHeightAngle 44.9023
viewer 0 setAutoRedraw 1
viewer 0 redraw

