# Amira Script
# test(timeout=150)

if { ![app hasLicense MolecularPack] } { 
	theMsg error "This script requires a MolecularPack license." 
	return 
} 

remove -all
remove volrenRed.col irc.0001.dat Voltex Molecule MoleculeView ConfigurationDensity irc.color.dat2

# Create viewers
viewer 0 show
viewer 0 setBackgroundMode 1
viewer 0 decoration 1
viewer 0 setTransparencyType 6
viewer 0 setAutoRedraw 0

mainWindow show

set hideNewModules 1
[ load ${AMIRA_ROOT}/data/colormaps/volrenRed.col ] setLabel volrenRed.col
volrenRed.col setIconPosition 0 0
volrenRed.col fire
{volrenRed.col} setMinMax 10 180
{volrenRed.col} flags setValue 0
{volrenRed.col} shift setMinMax -1 1
{volrenRed.col} shift setValue 0
{volrenRed.col} scale setMinMax 0 1
{volrenRed.col} scale setValue 1
volrenRed.col fire
volrenRed.col setViewerMask 16383

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/molecules/irc/irc.????.dat ] setLabel irc.dat
{irc.dat} setIconPosition 20 10
{irc.dat} setViewerMask 0
{irc.dat} trajectory setIndex 0 0
{irc.dat} fire
{irc.dat} setViewerMask 16383

set hideNewModules 0
create HxMolecule {Molecule}
Molecule setIconPosition 20 40
Molecule data connect irc.dat
{Molecule} fire
Molecule time setMinMax 1 1200
Molecule time setSubMinMax 1 1200
Molecule time setValue 1200
Molecule time setDiscrete 1
Molecule time setIncrement 1
{Molecule} selectionBrowser setIndex -1
{Molecule} selectionBrowser untouch
Molecule fire
Molecule setViewerMask 16383

set hideNewModules 0
create HxMolView {MoleculeView}
MoleculeView setIconPosition 298 40
MoleculeView data connect Molecule
{MoleculeView} continuousColormap setDefaultColor 0 0 1
{MoleculeView} continuousColormap setDefaultAlpha 1.000000
{MoleculeView} discreteColormap setDefaultColor 0 0 1
{MoleculeView} discreteColormap setDefaultAlpha 1.000000
{MoleculeView} fire
{MoleculeView} selectAtoms zab HIJMPLPPBPACAACDOEAHPJ
{MoleculeView} mode setValue 2
{MoleculeView} quality setValue 1
{MoleculeView} options setValue 0 0
{MoleculeView} options setValue 1 0
{MoleculeView} options setValue 2 0
{MoleculeView} atomRadius setMinMax 0 2
{MoleculeView} atomRadius setValue 0.08
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
{MoleculeView} highlighting setIndex -1
{MoleculeView} highlighting untouch
{MoleculeView} buffer setIndex -1
{MoleculeView} buffer untouch
MoleculeView fire
MoleculeView setViewerMask 16383

set hideNewModules 0
create HxConfDensity {ConfigurationDensity}
ConfigurationDensity setIconPosition 160 10
ConfigurationDensity data connect irc.dat
{ConfigurationDensity} continuousColormap setDefaultColor 0 0 1
{ConfigurationDensity} continuousColormap setDefaultAlpha 1.000000
{ConfigurationDensity} discreteColormap setDefaultColor 0 0 1
{ConfigurationDensity} discreteColormap setDefaultAlpha 1.000000
{ConfigurationDensity} fire
{ConfigurationDensity} voxelSize setMinMax 0.05 0.5
{ConfigurationDensity} voxelSize setValue 0.0667
{ConfigurationDensity} timeSteps setMinMax 0 1 1200
{ConfigurationDensity} timeSteps setValue 0 1
{ConfigurationDensity} timeSteps setMinMax 1 1 1200
{ConfigurationDensity} timeSteps setValue 1 1200
{ConfigurationDensity} transformation setValue 0
{ConfigurationDensity} selection setIndex -1
{ConfigurationDensity} selection untouch
{ConfigurationDensity} shape setValue 0 0
{ConfigurationDensity} shape setValue 1 1
{ConfigurationDensity} radiusOption setValue 0
{ConfigurationDensity} atomRadius setMinMax 0 1.2
{ConfigurationDensity} atomRadius setValue 0.2
{ConfigurationDensity} bondRadius setMinMax 0 0.5
{ConfigurationDensity} bondRadius setValue 0.1
{ConfigurationDensity} field setIndex 0 1
{ConfigurationDensity} colorscheme setIndex -1
{ConfigurationDensity} colorscheme untouch
{ConfigurationDensity} colorscheme setOptValue 0 0
{ConfigurationDensity} colorscheme setOptValue 1 0
{ConfigurationDensity} buttons setIndex -1
{ConfigurationDensity} buttons untouch
ConfigurationDensity fire
ConfigurationDensity setViewerMask 16383

set hideNewModules 0
[ {ConfigurationDensity} create
 ] setLabel {irc.color.dat}
irc.color.dat setIconPosition 20 73
irc.color.dat master connect ConfigurationDensity
irc.color.dat fire
irc.color.dat fire
irc.color.dat setViewerMask 16383

set hideNewModules 0
create HxVoltex {Voltex}
Voltex setIconPosition 297 73
Voltex data connect irc.color.dat
{Voltex} colormap setDefaultColor 1 0.8 0.5
{Voltex} colormap setDefaultAlpha 0.500000
Voltex colormap connect volrenRed.col
Voltex fire
{Voltex} options setValue 0 0
{Voltex} options setValue 1 1
{Voltex} range setMinMax 0 -1e+24 1e+24
{Voltex} range setValue 0 -200
{Voltex} range setMinMax 1 -1e+24 1e+24
{Voltex} range setValue 1 200
{Voltex} lookup setValue 2
{Voltex} gamma setMinMax 1 8
{Voltex} gamma setValue 3
{Voltex} alphaScale setMinMax 0 1
{Voltex} alphaScale setValue 1
{Voltex} texture2D3D setValue 0
{Voltex} slices setMinMax 0 256
{Voltex} slices setValue 256
{Voltex} downsample setMinMax 0 -1e+24 1e+24
{Voltex} downsample setValue 0 1
{Voltex} downsample setMinMax 1 -1e+24 1e+24
{Voltex} downsample setValue 1 1
{Voltex} downsample setMinMax 2 -1e+24 1e+24
{Voltex} downsample setValue 2 1
{Voltex} doIt hit
Voltex fire
Voltex setViewerMask 0

set hideNewModules 0

viewer 0 setCameraPosition -7.49836 -0.0491942 -9.5384
viewer 0 setCameraOrientation 0.967265 -0.0649898 -0.245307 2.89554
viewer 0 setCameraFocalDistance 13.6592
viewer 0 setAutoRedraw 1
viewer 0 redraw

proc restart { } {
    Molecule select
    Voltex setViewerMask 0
    for { set i 1 } { $i<1201 } { incr i 1 } {
        {Molecule} time setValue $i
        {Molecule} fire
        viewer 0 redraw
    }
    Voltex setViewerMask 16383
}        

echo "type <restart> to start the animation"

restart
