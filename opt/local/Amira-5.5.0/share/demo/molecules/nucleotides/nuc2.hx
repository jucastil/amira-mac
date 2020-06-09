# Amira Script
remove -All

# Create viewers
viewer 0 show
viewer 0 setAutoRedraw 0

mainWindow show

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
{nuc_cluster.idx} setIconPosition 20 40
{nuc_cluster.idx} setViewerMask 0
{nuc_cluster.idx} trajectory setIndex 0 0
{nuc_cluster.idx} fire
{nuc_cluster.idx} setViewerMask 16383

set hideNewModules 0
create HxMolecule {Molecule}
{Molecule} setIconPosition 20 70
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
create HxMolView {MoleculeView}
{MoleculeView} setIconPosition 298 70
{MoleculeView} setViewerMask 0
{MoleculeView} {data} connect {Molecule}
{MoleculeView} fire
{MoleculeView} mode setValue 0
{MoleculeView} options setValue 0 0
{MoleculeView} options setValue 1 0
{MoleculeView} options setValue 2 0
{MoleculeView} twistFactor setMinMax 0.5 2
{MoleculeView} twistFactor setValue 1
{MoleculeView} quality setValue 1
{MoleculeView} colorscheme setOptValue 0 0
{MoleculeView} colorscheme setOptValue 1 0
{MoleculeView} atomRadius setMinMax 0 2
{MoleculeView} atomRadius setValue 1
{MoleculeView} bondRadius setMinMax 0 0.5
{MoleculeView} bondRadius setValue 0.05
{MoleculeView} complexity setMinMax 0 1
{MoleculeView} complexity setValue 0.5
{MoleculeView} fire
{MoleculeView} setViewerMask 16383
{MoleculeView} select

set hideNewModules 0

viewer 0 setCameraPosition 20.2268 50.0825 24.2902
viewer 0 setCameraOrientation 0.0360617 0.915564 0.400552 4.09767
viewer 0 setCameraFocalDistance 24.5361
viewer 0 setAutoRedraw 1
viewer 0 redraw
