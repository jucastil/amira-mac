# Amira Script

# test(timeout=130)

if { ![app hasLicense MolecularPack] } { 
	theMsg error "This script requires a MolecularPack license." 
	return 
} 

remove -All

# Create viewers
viewer 0 show
##viewer 0 setSize 824 825
viewer 0 setAutoRedraw 0

mainWindow show

set hideNewModules 1
[ load ${AMIRA_ROOT}/data/colormaps/temperature.icol ] setLabel {temperature.icol}
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
[ load ${AMIRA_ROOT}/data/colormaps/physics.icol ] setLabel {physics.icol}
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
[ load ${AMIRA_ROOT}/data/colormaps/volrenRed.col ] setLabel {volrenRed.col}
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
[ load ${AMIRA_ROOT}/data/colormaps/glow.col ] setLabel {glow.col}
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
[ load ${AMIRA_ROOT}/data/molecules/alkane/alkane.zmf ] setLabel {alkane.zmf}
{alkane.zmf} setIconPosition 17 7
{alkane.zmf} setViewerMask 0
{alkane.zmf} fire
{alkane.zmf} setViewerMask 16383

set hideNewModules 0
create HxMolTrajectory {MolTrajectory}
{MolTrajectory} setIconPosition 163 7
{MolTrajectory} setViewerMask 0
{MolTrajectory} {bundle} connect {alkane.zmf}
{MolTrajectory} fire
{MolTrajectory} trajectory setIndex 0 0
{MolTrajectory} fire
{MolTrajectory} setViewerMask 16383
{MolTrajectory} select

set hideNewModules 0
[lindex [ load -subtrajectory ${AMIRA_ROOT}/data/molecules/alkane/but_cluster_3_1.idx ] end] setLabel {but_cluster_3_1.idx}
{but_cluster_3_1.idx} setIconPosition 17 57
{but_cluster_3_1.idx} setViewerMask 0
{but_cluster_3_1.idx} trajectory setIndex 0 0
{but_cluster_3_1.idx} fire
{but_cluster_3_1.idx} setViewerMask 16383

set hideNewModules 0
[lindex [ load -subtrajectory ${AMIRA_ROOT}/data/molecules/alkane/but_cluster_3_2.idx ] end] setLabel {but_cluster_3_2.idx}
{but_cluster_3_2.idx} setIconPosition 17 156
{but_cluster_3_2.idx} setViewerMask 0
{but_cluster_3_2.idx} trajectory setIndex 0 0
{but_cluster_3_2.idx} fire
{but_cluster_3_2.idx} setViewerMask 16383

set hideNewModules 0
[lindex [ load -subtrajectory ${AMIRA_ROOT}/data/molecules/alkane/but_cluster_3_3.idx ] end] setLabel {but_cluster_3_3.idx}
{but_cluster_3_3.idx} setIconPosition 18 254
{but_cluster_3_3.idx} setViewerMask 0
{but_cluster_3_3.idx} trajectory setIndex 0 0
{but_cluster_3_3.idx} fire
{but_cluster_3_3.idx} setViewerMask 16383

set hideNewModules 0
create HxMolecule {Molecule2}
{Molecule2} setIconPosition 20 329
{Molecule2} setViewerMask 0
{Molecule2} {data} connect {but_cluster_3_1.idx}
{Molecule2} fire
{Molecule2} time setMinMax  1 332
{Molecule2} time setIncrement  1
{Molecule2} time setSubMinMax  1 332
{Molecule2} time setDiscrete  1
{Molecule2} time setValue  1
{Molecule2} fire
{Molecule2} setViewerMask 16383

set hideNewModules 0
create HxMeanMolecule {MeanMolecule}
{MeanMolecule} setIconPosition 164 57
{MeanMolecule} setViewerMask 0
{MeanMolecule} {data} connect {but_cluster_3_1.idx}
{MeanMolecule} {alignMaster} connect {Molecule2}
{MeanMolecule} timeSteps setMinMax 0 1 798
{MeanMolecule} timeSteps setValue 0 1
{MeanMolecule} timeSteps setMinMax 1 1 798
{MeanMolecule} timeSteps setValue 1 798
{MeanMolecule} selection setIndex 0
{MeanMolecule} selection hit
{MeanMolecule} doIt hit
{MeanMolecule} fire
{MeanMolecule} setViewerMask 16383

set hideNewModules 0
{but_cluster_3_1.mean} setIconPosition 163 57
{but_cluster_3_1.mean} setViewerMask 0
{but_cluster_3_1.mean} time setMinMax  0 0
{but_cluster_3_1.mean} time setIncrement  1
{but_cluster_3_1.mean} time setSubMinMax  0 0
{but_cluster_3_1.mean} time setDiscrete  1
{but_cluster_3_1.mean} time setValue  0
{but_cluster_3_1.mean} fire
{but_cluster_3_1.mean} setViewerMask 16383

set hideNewModules 0
create HxMolView {MolView}
{MolView} setIconPosition 317 57
{MolView} setViewerMask 0
{MolView} {data} connect {but_cluster_3_1.mean}
{MolView} fire
{MolView} mode setValue 2
{MolView} options setValue 0 0
{MolView} options setValue 1 0
{MolView} options setValue 2 0
{MolView} twistFactor setMinMax 0.5 2
{MolView} twistFactor setValue 1
{MolView} quality setValue 1
{MolView} colorscheme setOptValue 0 0
{MolView} colorscheme setOptValue 1 0
{MolView} atomRadius setMinMax 0 2
{MolView} atomRadius setValue 0.1
{MolView} bondRadius setMinMax 0 0.5
{MolView} bondRadius setValue 0.05
{MolView} complexity setMinMax 0 1
{MolView} complexity setValue 0.2
{MolView} fire
{MolView} setViewerMask 16382

set hideNewModules 0
create HxMolecule {Molecule3}
{Molecule3} setIconPosition 20 329
{Molecule3} setViewerMask 0
{Molecule3} {data} connect {but_cluster_3_2.idx}
{Molecule3} fire
{Molecule3} time setMinMax  1 332
{Molecule3} time setIncrement  1
{Molecule3} time setSubMinMax  1 332
{Molecule3} time setDiscrete  1
{Molecule3} time setValue  270
{Molecule3} fire
{Molecule3} setViewerMask 16383

set hideNewModules 0
create HxMeanMolecule {MeanMolecule2}
{MeanMolecule2} setIconPosition 163 156
{MeanMolecule2} setViewerMask 0
{MeanMolecule2} {data} connect {but_cluster_3_2.idx}
{MeanMolecule2} {alignMaster} connect {Molecule3}
{MeanMolecule2} timeSteps setMinMax 0 1 546
{MeanMolecule2} timeSteps setValue 0 1
{MeanMolecule2} timeSteps setMinMax 1 1 546
{MeanMolecule2} timeSteps setValue 1 546
{MeanMolecule2} selection setIndex 0
{MeanMolecule2} selection hit
{MeanMolecule2} doIt hit
{MeanMolecule2} fire
{MeanMolecule2} setViewerMask 16383

set hideNewModules 0
{but_cluster_3_2.mean} setIconPosition 162 156
{but_cluster_3_2.mean} setViewerMask 0
{but_cluster_3_2.mean} {alignMaster} connect {but_cluster_3_1.mean}
{but_cluster_3_2.mean} transformation setIndex 2
{but_cluster_3_2.mean} slaveSelection 0 5 6 
{but_cluster_3_2.mean} masterSelection 0 5 6 
{but_cluster_3_2.mean} time setMinMax  0 0
{but_cluster_3_2.mean} time setIncrement  1
{but_cluster_3_2.mean} time setSubMinMax  0 0
{but_cluster_3_2.mean} time setDiscrete  1
{but_cluster_3_2.mean} time setValue  0
{but_cluster_3_2.mean} fire
{but_cluster_3_2.mean} setViewerMask 16383

set hideNewModules 0
create HxMolView {MolView2}
{MolView2} setIconPosition 309 156
{MolView2} setViewerMask 0
{MolView2} {data} connect {but_cluster_3_2.mean}
{MolView2} fire
{MolView2} mode setValue 2
{MolView2} options setValue 0 0
{MolView2} options setValue 1 0
{MolView2} options setValue 2 0
{MolView2} twistFactor setMinMax 0.5 2
{MolView2} twistFactor setValue 1
{MolView2} quality setValue 1
{MolView2} colorscheme setOptValue 0 0
{MolView2} colorscheme setOptValue 1 0
{MolView2} atomRadius setMinMax 0 2
{MolView2} atomRadius setValue 0.1
{MolView2} bondRadius setMinMax 0 0.5
{MolView2} bondRadius setValue 0.05
{MolView2} complexity setMinMax 0 1
{MolView2} complexity setValue 0.2
{MolView2} fire
{MolView2} setViewerMask 16382

set hideNewModules 0
create HxMolecule {Molecule4}
{Molecule4} setIconPosition 20 329
{Molecule4} setViewerMask 0
{Molecule4} {data} connect {but_cluster_3_3.idx}
{Molecule4} fire
{Molecule4} time setMinMax  1 332
{Molecule4} time setIncrement  1
{Molecule4} time setSubMinMax  1 332
{Molecule4} time setDiscrete  1
{Molecule4} time setValue  325
{Molecule4} fire
{Molecule4} setViewerMask 16383

set hideNewModules 0
create HxMeanMolecule {MeanMolecule3}
{MeanMolecule3} setIconPosition 163 254
{MeanMolecule3} setViewerMask 0
{MeanMolecule3} {data} connect {but_cluster_3_3.idx}
{MeanMolecule3} {alignMaster} connect {Molecule4}
{MeanMolecule3} timeSteps setMinMax 0 1 656
{MeanMolecule3} timeSteps setValue 0 1
{MeanMolecule3} timeSteps setMinMax 1 1 656
{MeanMolecule3} timeSteps setValue 1 656
{MeanMolecule3} selection setIndex 0
{MeanMolecule3} selection hit
{MeanMolecule3} doIt hit
{MeanMolecule3} fire
{MeanMolecule3} setViewerMask 16383

set hideNewModules 0
{but_cluster_3_3.mean} setIconPosition 163 254
{but_cluster_3_3.mean} setViewerMask 0
{but_cluster_3_3.mean} {alignMaster} connect {but_cluster_3_1.mean}
{but_cluster_3_3.mean} transformation setIndex 2
{but_cluster_3_3.mean} slaveSelection 0 5 6 
{but_cluster_3_3.mean} masterSelection 0 5 6 
{but_cluster_3_3.mean} time setMinMax  0 0
{but_cluster_3_3.mean} time setIncrement  1
{but_cluster_3_3.mean} time setSubMinMax  0 0
{but_cluster_3_3.mean} time setDiscrete  1
{but_cluster_3_3.mean} time setValue  0
{but_cluster_3_3.mean} fire
{but_cluster_3_3.mean} setViewerMask 16383

set hideNewModules 0
create HxMolView {MolView3}
{MolView3} setIconPosition 310 254
{MolView3} setViewerMask 0
{MolView3} {data} connect {but_cluster_3_3.mean}
{MolView3} fire
{MolView3} mode setValue 2
{MolView3} options setValue 0 0
{MolView3} options setValue 1 0
{MolView3} options setValue 2 0
{MolView3} twistFactor setMinMax 0.5 2
{MolView3} twistFactor setValue 1
{MolView3} quality setValue 1
{MolView3} colorscheme setOptValue 0 0
{MolView3} colorscheme setOptValue 1 0
{MolView3} atomRadius setMinMax 0 2
{MolView3} atomRadius setValue 0.1
{MolView3} bondRadius setMinMax 0 0.5
{MolView3} bondRadius setValue 0.05
{MolView3} complexity setMinMax 0 1
{MolView3} complexity setValue 0.2
{MolView3} fire
{MolView3} setViewerMask 16382

set hideNewModules 0
create HxConfDensity {ConfigurationDensity}
{ConfigurationDensity} setIconPosition 17 82
{ConfigurationDensity} setViewerMask 0
{ConfigurationDensity} {data} connect {but_cluster_3_1.idx}
{ConfigurationDensity} {alignMaster} connect {but_cluster_3_1.mean}
{ConfigurationDensity} voxelSize setMinMax 0 0.4
{ConfigurationDensity} voxelSize setValue 0.1
{ConfigurationDensity} timeSteps setMinMax 0 1 798
{ConfigurationDensity} timeSteps setValue 0 1
{ConfigurationDensity} timeSteps setMinMax 1 1 798
{ConfigurationDensity} timeSteps setValue 1 798
{ConfigurationDensity} selection setIndex -1
{ConfigurationDensity} selection untouch
{ConfigurationDensity} shape setValue 0 0
{ConfigurationDensity} shape setValue 1 1
{ConfigurationDensity} radiusOption setValue 0
{ConfigurationDensity} atomRadius setMinMax 0 1.2
{ConfigurationDensity} atomRadius setValue 0.2
{ConfigurationDensity} bondRadius setMinMax 0 0.5
{ConfigurationDensity} bondRadius setValue 0.1
{ConfigurationDensity} field setIndex 0 0
{ConfigurationDensity} colorscheme setOptValue 0 1
{ConfigurationDensity} colorscheme setOptValue 1 0
{ConfigurationDensity} fire
{ConfigurationDensity} setViewerMask 16383

set hideNewModules 0
create HxConfDensity {ConfigurationDensity2}
{ConfigurationDensity2} setIconPosition 18 181
{ConfigurationDensity2} setViewerMask 0
{ConfigurationDensity2} {data} connect {but_cluster_3_2.idx}
{ConfigurationDensity2} {alignMaster} connect {but_cluster_3_2.mean}
{ConfigurationDensity2} voxelSize setMinMax 0 0.4
{ConfigurationDensity2} voxelSize setValue 0.1
{ConfigurationDensity2} timeSteps setMinMax 0 1 546
{ConfigurationDensity2} timeSteps setValue 0 1
{ConfigurationDensity2} timeSteps setMinMax 1 1 546
{ConfigurationDensity2} timeSteps setValue 1 546
{ConfigurationDensity2} selection setIndex -1
{ConfigurationDensity2} selection untouch
{ConfigurationDensity2} shape setValue 0 0
{ConfigurationDensity2} shape setValue 1 1
{ConfigurationDensity2} radiusOption setValue 0
{ConfigurationDensity2} atomRadius setMinMax 0 1.2
{ConfigurationDensity2} atomRadius setValue 0.2
{ConfigurationDensity2} bondRadius setMinMax 0 0.5
{ConfigurationDensity2} bondRadius setValue 0.1
{ConfigurationDensity2} field setIndex 0 0
{ConfigurationDensity2} colorscheme setOptValue 0 1
{ConfigurationDensity2} colorscheme setOptValue 1 0
{ConfigurationDensity2} fire
{ConfigurationDensity2} setViewerMask 16383

set hideNewModules 0
create HxConfDensity {ConfigurationDensity3}
{ConfigurationDensity3} setIconPosition 18 279
{ConfigurationDensity3} setViewerMask 0
{ConfigurationDensity3} {data} connect {but_cluster_3_3.idx}
{ConfigurationDensity3} {alignMaster} connect {but_cluster_3_3.mean}
{ConfigurationDensity3} voxelSize setMinMax 0 0.4
{ConfigurationDensity3} voxelSize setValue 0.1
{ConfigurationDensity3} timeSteps setMinMax 0 1 656
{ConfigurationDensity3} timeSteps setValue 0 1
{ConfigurationDensity3} timeSteps setMinMax 1 1 656
{ConfigurationDensity3} timeSteps setValue 1 656
{ConfigurationDensity3} selection setIndex -1
{ConfigurationDensity3} selection untouch
{ConfigurationDensity3} shape setValue 0 0
{ConfigurationDensity3} shape setValue 1 1
{ConfigurationDensity3} radiusOption setValue 0
{ConfigurationDensity3} atomRadius setMinMax 0 1.2
{ConfigurationDensity3} atomRadius setValue 0.2
{ConfigurationDensity3} bondRadius setMinMax 0 0.5
{ConfigurationDensity3} bondRadius setValue 0.1
{ConfigurationDensity3} field setIndex 0 0
{ConfigurationDensity3} colorscheme setOptValue 0 1
{ConfigurationDensity3} colorscheme setOptValue 1 0
{ConfigurationDensity3} fire
{ConfigurationDensity3} setViewerMask 16383

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/molecules/alkane/but_cluster_3_1.1.scalar ] setLabel {but_cluster_3_1.1.scalar}
{but_cluster_3_1.1.scalar} setIconPosition 163 82
{but_cluster_3_1.1.scalar} setViewerMask 0
{but_cluster_3_1.1.scalar} {master} connect {ConfigurationDensity}
{but_cluster_3_1.1.scalar} fire
{but_cluster_3_1.1.scalar} setViewerMask 16383

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/molecules/alkane/but_cluster_3_2.1.scalar ] setLabel {but_cluster_3_2.1.scalar}
{but_cluster_3_2.1.scalar} setIconPosition 162 181
{but_cluster_3_2.1.scalar} setViewerMask 0
{but_cluster_3_2.1.scalar} {master} connect {ConfigurationDensity2}
{but_cluster_3_2.1.scalar} fire
{but_cluster_3_2.1.scalar} setViewerMask 16383

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/molecules/alkane/but_cluster_3_3.1.scalar ] setLabel {but_cluster_3_3.1.scalar}
{but_cluster_3_3.1.scalar} setIconPosition 162 279
{but_cluster_3_3.1.scalar} setViewerMask 0
{but_cluster_3_3.1.scalar} {master} connect {ConfigurationDensity3}
{but_cluster_3_3.1.scalar} fire
{but_cluster_3_3.1.scalar} setViewerMask 16383

set hideNewModules 0
create HxIsosurface {Isosurface}
{Isosurface} setIconPosition 317 83
{Isosurface} setViewerMask 0
{Isosurface} {data} connect {but_cluster_3_1.1.scalar}
{Isosurface} colormap setDefaultColor 0.227451 0.227451 0.968627
{Isosurface} colormap setDefaultAlpha 1.000000
{Isosurface} drawStyle setValue 1
{Isosurface} drawStyle setTexture 0
{Isosurface} drawStyle setNormalBinding 1
{Isosurface} buffer setIndex -1
{Isosurface} buffer untouch
{Isosurface} threshold setMinMax 0 649
{Isosurface} threshold setValue 65
{Isosurface} options setValue 0 1
{Isosurface} options setValue 1 0
{Isosurface} resolution setMinMax 0 -1e+24 1e+24
{Isosurface} resolution setValue 0 2
{Isosurface} resolution setMinMax 1 -1e+24 1e+24
{Isosurface} resolution setValue 1 2
{Isosurface} resolution setMinMax 2 -1e+24 1e+24
{Isosurface} resolution setValue 2 2
{Isosurface} doIt setIndex -1
{Isosurface} doIt untouch
{Isosurface} doIt hit
{Isosurface} fire
{Isosurface} setViewerMask 16382

set hideNewModules 0
create HxIsosurface {Isosurface2}
{Isosurface2} setIconPosition 311 181
{Isosurface2} setViewerMask 0
{Isosurface2} {data} connect {but_cluster_3_2.1.scalar}
{Isosurface2} colormap setDefaultColor 1 0.917647 0.223529
{Isosurface2} colormap setDefaultAlpha 1.000000
{Isosurface2} drawStyle setValue 1
{Isosurface2} drawStyle setTexture 0
{Isosurface2} drawStyle setNormalBinding 1
{Isosurface2} buffer setIndex -1
{Isosurface2} buffer untouch
{Isosurface2} threshold setMinMax 0 484
{Isosurface2} threshold setValue 50
{Isosurface2} options setValue 0 1
{Isosurface2} options setValue 1 0
{Isosurface2} resolution setMinMax 0 -1e+24 1e+24
{Isosurface2} resolution setValue 0 2
{Isosurface2} resolution setMinMax 1 -1e+24 1e+24
{Isosurface2} resolution setValue 1 2
{Isosurface2} resolution setMinMax 2 -1e+24 1e+24
{Isosurface2} resolution setValue 2 2
{Isosurface2} doIt setIndex -1
{Isosurface2} doIt untouch
{Isosurface2} doIt hit
{Isosurface2} fire
{Isosurface2} setViewerMask 16382

set hideNewModules 0
create HxIsosurface {Isosurface3}
{Isosurface3} setIconPosition 310 279
{Isosurface3} setViewerMask 0
{Isosurface3} {data} connect {but_cluster_3_3.1.scalar}
{Isosurface3} colormap setDefaultColor 0 0.811765 0.368627
{Isosurface3} colormap setDefaultAlpha 1.000000
{Isosurface3} drawStyle setValue 1
{Isosurface3} drawStyle setTexture 0
{Isosurface3} drawStyle setNormalBinding 1
{Isosurface3} buffer setIndex -1
{Isosurface3} buffer untouch
{Isosurface3} threshold setMinMax 0 568
{Isosurface3} threshold setValue 56
{Isosurface3} options setValue 0 1
{Isosurface3} options setValue 1 0
{Isosurface3} resolution setMinMax 0 -1e+24 1e+24
{Isosurface3} resolution setValue 0 2
{Isosurface3} resolution setMinMax 1 -1e+24 1e+24
{Isosurface3} resolution setValue 1 2
{Isosurface3} resolution setMinMax 2 -1e+24 1e+24
{Isosurface3} resolution setValue 2 2
{Isosurface3} doIt setIndex -1
{Isosurface3} doIt untouch
{Isosurface3} doIt hit
{Isosurface3} fire
{Isosurface3} setViewerMask 16382

set hideNewModules 0
create HxMolecule {Molecule}
{Molecule} setIconPosition 20 329
{Molecule} setViewerMask 0
{Molecule} {data} connect {MolTrajectory}
{Molecule} {alignMaster} connect {but_cluster_3_1.mean}
{Molecule} transformation setIndex 2
{Molecule} slaveSelection 0 5 6 
{Molecule} masterSelection 0 5 6 
{Molecule} time setMinMax  1 332
{Molecule} time setIncrement  1
{Molecule} time setSubMinMax  1 332
{Molecule} time setDiscrete  1
{Molecule} time setValue  1
{Molecule} fire
{Molecule} setViewerMask 16383

set hideNewModules 0
create HxMolView {MolView4}
{MolView4} setIconPosition 310 329
{MolView4} setViewerMask 0
{MolView4} {data} connect {Molecule}
{MolView4} fire
{MolView4} mode setValue 2
{MolView4} options setValue 0 0
{MolView4} options setValue 1 0
{MolView4} options setValue 2 0
{MolView4} twistFactor setMinMax 0.5 2
{MolView4} twistFactor setValue 1
{MolView4} quality setValue 1
{MolView4} colorscheme setOptValue 0 0
{MolView4} colorscheme setOptValue 1 0
{MolView4} atomRadius setMinMax 0 2
{MolView4} atomRadius setValue 0.1
{MolView4} bondRadius setMinMax 0 0.5
{MolView4} bondRadius setValue 0.05
{MolView4} complexity setMinMax 0 1
{MolView4} complexity setValue 0.2
{MolView4} fire
{MolView4} setViewerMask 16383

set hideNewModules 0

viewer 0 setCameraPosition -11.9699 -4.42813 6.87907
viewer 0 setCameraOrientation -0.878968 -0.0562356 0.473553 2.55863
viewer 0 setCameraFocalDistance 6.8101
viewer 0 setAutoRedraw 1
viewer 0 redraw

proc restart { } {
    {Isosurface} setViewerMask 0
    {Isosurface2} setViewerMask 0
    {Isosurface3} setViewerMask 0

    {MolTrajectory} select 0
    {Molecule} select
    for { set i 1 } { $i<333 } { incr i 1 } {
        {Molecule} time setValue  $i	 
        {Molecule} fire
        viewer 0 redraw
    }
    {Molecule} time setValue  1
    viewer 0 redraw
    
    {Isosurface} setViewerMask 16383
    viewer 0 redraw
    sleep 1
    {Isosurface2} setViewerMask 16383
    viewer 0 redraw
    sleep 1
    {Isosurface3} setViewerMask 16383
    viewer 0 redraw
}

echo "type <restart> to start the animation"

restart
