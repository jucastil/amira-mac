# Amira Script

# test(timeout=130)

if { ![app hasLicense MolecularPack] } { 
	theMsg error "This script requires a MolecularPack license." 
	return 
} 

remove -All

# Create viewers
viewer 0 show
viewer 0 setAutoRedraw 0

set hideNewModules 1
[ load ${AMIRA_ROOT}/data/colormaps/temperature.icol ] setLabel temperature.icol
{temperature.icol} setIconPosition 0 0
{temperature.icol} setViewerMask 0
{temperature.icol} setMinMax 38 44
{temperature.icol} flags setValue 0
{temperature.icol} shift setMinMax -1 1
{temperature.icol} shift setValue 0
{temperature.icol} scale setMinMax 0 1
{temperature.icol} scale setValue 1
{temperature.icol} fire
{temperature.icol} setViewerMask 16383

set hideNewModules 1
[ load ${AMIRA_ROOT}/data/colormaps/physics.icol ] setLabel physics.icol
{physics.icol} setIconPosition 0 0
{physics.icol} setViewerMask 0
{physics.icol} setMinMax 0 1
{physics.icol} flags setValue 0
{physics.icol} shift setMinMax -1 1
{physics.icol} shift setValue 0
{physics.icol} scale setMinMax 0 1
{physics.icol} scale setValue 1
{physics.icol} fire
{physics.icol} setViewerMask 16383

set hideNewModules 1
[ load ${AMIRA_ROOT}/data/colormaps/volrenRed.col ] setLabel volrenRed.col
{volrenRed.col} setIconPosition 0 0
{volrenRed.col} setViewerMask 0
{volrenRed.col} setMinMax 10 180
{volrenRed.col} flags setValue 0
{volrenRed.col} shift setMinMax -1 1
{volrenRed.col} shift setValue 0
{volrenRed.col} scale setMinMax 0 1
{volrenRed.col} scale setValue 1
{volrenRed.col} fire
{volrenRed.col} setViewerMask 16383

set hideNewModules 1
[ load ${AMIRA_ROOT}/data/colormaps/glow.col ] setLabel glow.col
{glow.col} setIconPosition 0 0
{glow.col} setViewerMask 0
{glow.col} setMinMax 0 255
{glow.col} flags setValue 0
{glow.col} shift setMinMax -1 1
{glow.col} shift setValue 0
{glow.col} scale setMinMax 0 1
{glow.col} scale setValue 1
{glow.col} fire
{glow.col} setViewerMask 16383

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/molecules/nucleotides/gg_0.top ] setLabel gg_0.top
{gg_0.top} setIconPosition 20 10
{gg_0.top} setViewerMask 0
{gg_0.top} trajectory setIndex 0 0
{gg_0.top} fire
{gg_0.top} setViewerMask 16383

set hideNewModules 0
[ lindex [load ${AMIRA_ROOT}/data/molecules/nucleotides/nuc_cluster.idx] end ] setLabel nuc_cluster.idx
{nuc_cluster.idx} setIconPosition 20 70
{nuc_cluster.idx} setViewerMask 0
{nuc_cluster.idx} trajectory setIndex 0 0
{nuc_cluster.idx} fire
{nuc_cluster.idx} setViewerMask 16383

set hideNewModules 0
create HxMolecule {Molecule}
{Molecule} setIconPosition 20 160
{Molecule} setViewerMask 0
{Molecule} {data} connect {nuc_cluster.idx}
{Molecule} fire
{Molecule} time setMinMax 1 121
{Molecule} time setIncrement 1
{Molecule} time setSubMinMax 1 121
{Molecule} time setDiscrete 1
{Molecule} time setValue 1
{Molecule} fire
{Molecule} setViewerMask 16383

set hideNewModules 0
create HxConfDensity {ConfigurationDensity}
{ConfigurationDensity} setIconPosition 160 70
{ConfigurationDensity} setViewerMask 0
{ConfigurationDensity} {data} connect {nuc_cluster.idx}
{ConfigurationDensity} {alignMaster} connect {Molecule}
{ConfigurationDensity} voxelSize setMinMax 0.09 0.4
{ConfigurationDensity} voxelSize setValue 0.15
{ConfigurationDensity} timeSteps setMinMax 0 1 121
{ConfigurationDensity} timeSteps setValue 0 1
{ConfigurationDensity} timeSteps setMinMax 1 1 121
{ConfigurationDensity} timeSteps setValue 1 121
{ConfigurationDensity} transformation setIndex 2
{ConfigurationDensity} selection setIndex 0
{ConfigurationDensity} selection hit
{ConfigurationDensity} shape setValue 0 0
{ConfigurationDensity} shape setValue 1 1
{ConfigurationDensity} radiusOption setValue 0
{ConfigurationDensity} atomRadius setMinMax 0 1.2
{ConfigurationDensity} atomRadius setValue 0.2
{ConfigurationDensity} bondRadius setMinMax 0 0.5
{ConfigurationDensity} bondRadius setValue 0.1
{ConfigurationDensity} field setIndex 0 1
{ConfigurationDensity} colorscheme setOptValue 0 0
{ConfigurationDensity} colorscheme setOptValue 1 0
{ConfigurationDensity} fire
{ConfigurationDensity} setViewerMask 16383

set hideNewModules 0
[ {ConfigurationDensity} create ] setLabel {nuc.color}
{nuc.color} setIconPosition 20 130
{nuc.color} setViewerMask 0
{nuc.color} {master} connect {ConfigurationDensity}
{nuc.color} fire
{nuc.color} setViewerMask 16383

set hideNewModules 0
create HxVoltex {Voltex}
{Voltex} setIconPosition 343 130
{Voltex} setViewerMask 0
{Voltex} {data} connect {nuc.color}
{Voltex} colormap setDefaultColor 1 0.8 0.5
{Voltex} colormap setDefaultAlpha 0.500000
{Voltex} {colormap} connect {volrenRed.col}
{Voltex} mode setValue 1
{Voltex} range setMinMax 0 -1e+24 1e+24
{Voltex} range setValue 0 0
{Voltex} range setMinMax 1 -1e+24 1e+24
{Voltex} range setValue 1 255
{Voltex} lookup setValue 0
{Voltex} alphaScale setMinMax 0 1
{Voltex} alphaScale setValue 1
{Voltex} slices setMinMax 0 256
{Voltex} slices setValue 256
{Voltex} texture2D3D setValue 0
{Voltex} downsample setMinMax 0 -1e+24 1e+24
{Voltex} downsample setValue 0 1
{Voltex} downsample setMinMax 1 -1e+24 1e+24
{Voltex} downsample setValue 1 1
{Voltex} downsample setMinMax 2 -1e+24 1e+24
{Voltex} downsample setValue 2 1
{Voltex} doIt setIndex -1
{Voltex} doIt hit
{Voltex} fire
{Voltex} setViewerMask 16383

set hideNewModules 0
create HxMolecule {Molecule2}
{Molecule2} setIconPosition 20 100
{Molecule2} setViewerMask 0
{Molecule2} {data} connect {nuc_cluster.idx}
{Molecule2} {alignMaster} connect {Molecule}
{Molecule2} transformation setIndex 2
{Molecule2} selection setIndex 0
{Molecule2} selection hit
{Molecule2} time setMinMax 1 121
{Molecule2} time setIncrement 1
{Molecule2} time setSubMinMax 1 121
{Molecule2} time setDiscrete 1
{Molecule2} time setValue 1
{Molecule2} fire
{Molecule2} setViewerMask 16383

set hideNewModules 0
create HxMolView {MoleculeView}
{MoleculeView} setIconPosition 298 100
{MoleculeView} setViewerMask 0
{MoleculeView} {data} connect {Molecule2}
{MoleculeView} fire
{MoleculeView} mode setValue 2
{MoleculeView} options setValue 0 0
{MoleculeView} options setValue 1 0
{MoleculeView} options setValue 2 0
{MoleculeView} twistFactor setMinMax 0.5 2
{MoleculeView} twistFactor setValue 1
{MoleculeView} quality setValue 1
{MoleculeView} colorscheme setOptValue 0 0
{MoleculeView} colorscheme setOptValue 1 0
{MoleculeView} atomRadius setMinMax 0 2
{MoleculeView} atomRadius setValue 0.1
{MoleculeView} bondRadius setMinMax 0 0.5
{MoleculeView} bondRadius setValue 0.05
{MoleculeView} complexity setMinMax 0 1
{MoleculeView} complexity setValue 0.2
{MoleculeView} fire
{MoleculeView} setViewerMask 16383
{MoleculeView} select

set hideNewModules 0

viewer 0 setCameraPosition 52.5321 23.6687 53.2442
viewer 0 setCameraOrientation 0.343193 0.712976 -0.611461 0.950078
viewer 0 setCameraFocalDistance 27.7473
viewer 0 setAutoRedraw 1
viewer 0 redraw
