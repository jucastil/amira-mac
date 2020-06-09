# Amira Script
if { ![app hasLicense MolecularPack] } { 
	theMsg error "This script requires a MolecularPack license." 
	return 
} 

remove -all
remove physics.icol 2RNT_receptor.pdb 2RNT_ligand.pdb 2RNT_receptor_2RNT_ligand-interface.surf 2RNT_receptor_2RNT_ligand-distance.field MoleculeView SecStructureView MoleculeView2 CompMolInterface MolSurfaceView

# Create viewers
viewer setVertical 0

viewer 0 setBackgroundMode 1
viewer 0 setTransparencyType 6
viewer 0 setAutoRedraw 0
viewer 0 show
mainWindow show

set hideNewModules 1
[ load ${AMIRA_ROOT}/data/colormaps/physics.icol ] setLabel physics.icol
physics.icol setIconPosition 0 0
physics.icol fire
{physics.icol} setMinMax -0.4 1
physics.icol flags setValue 1
physics.icol shift setMinMax -1 1
physics.icol shift setButtons 0
physics.icol shift setIncrement 0.133333
physics.icol shift setValue 0
physics.icol shift setSubMinMax -1 1
physics.icol scale setMinMax 0 1
physics.icol scale setButtons 0
physics.icol scale setIncrement 0.1
physics.icol scale setValue 1
physics.icol scale setSubMinMax 0 1
physics.icol fire
physics.icol setViewerMask 16383

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/molecules/pdb/2RNT_receptor.pdb ] setLabel 2RNT_receptor.pdb
2RNT_receptor.pdb setIconPosition 20 10
{2RNT_receptor.pdb} fire
2RNT_receptor.pdb time setMinMax 0 1
2RNT_receptor.pdb time setSubMinMax 0 1
2RNT_receptor.pdb time setValue 0
2RNT_receptor.pdb time setDiscrete 1
2RNT_receptor.pdb time setIncrement 1
2RNT_receptor.pdb transformation setValue 0 0
2RNT_receptor.pdb selection setOptValue 0 0
{2RNT_receptor.pdb} fire
2RNT_receptor.pdb fire
2RNT_receptor.pdb setViewerMask 16383

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/molecules/pdb/2RNT_ligand.pdb ] setLabel 2RNT_ligand.pdb
2RNT_ligand.pdb setIconPosition 20 72
{2RNT_ligand.pdb} fire
2RNT_ligand.pdb time setMinMax 0 1
2RNT_ligand.pdb time setSubMinMax 0 1
2RNT_ligand.pdb time setValue 0
2RNT_ligand.pdb time setDiscrete 1
2RNT_ligand.pdb time setIncrement 1
2RNT_ligand.pdb transformation setValue 0 0
2RNT_ligand.pdb selection setOptValue 0 0
{2RNT_ligand.pdb} fire
2RNT_ligand.pdb fire
2RNT_ligand.pdb setViewerMask 16383

set hideNewModules 0
create HxMolView {MoleculeView}
MoleculeView setIconPosition 286 10
MoleculeView data connect 2RNT_receptor.pdb
MoleculeView continuousColormap setDefaultColor 0 0 1
MoleculeView continuousColormap setDefaultAlpha 1.000000
MoleculeView continuousColormap setLocalRange 1
MoleculeView continuousColormap setLocalMinMax 0.000000 1.000000
MoleculeView discreteColormap setDefaultColor 0 0 1
MoleculeView discreteColormap setDefaultAlpha 1.000000
MoleculeView discreteColormap setLocalRange 1
MoleculeView discreteColormap setLocalMinMax 6.000000 20.000000
{MoleculeView} fire
{MoleculeView} selectAtoms zab HIJMPLPPJPLOAAAAKBCAGPJB
MoleculeView mode setValue 1
MoleculeView quality setValue 0
MoleculeView options setValue 0 0
MoleculeView options setValue 1 0
MoleculeView options setValue 2 0
MoleculeView options2 setValue 0 0
MoleculeView atomRadius setMinMax 0 2
MoleculeView atomRadius setButtons 0
MoleculeView atomRadius setIncrement 0.133333
MoleculeView atomRadius setValue 0.1
MoleculeView atomRadius setSubMinMax 0 2
MoleculeView bondRadius setMinMax 0 0.5
MoleculeView bondRadius setButtons 0
MoleculeView bondRadius setIncrement 0.0333333
MoleculeView bondRadius setValue 0.05
MoleculeView bondRadius setSubMinMax 0 0.5
MoleculeView lineWidth setMinMax 1 3
MoleculeView lineWidth setButtons 1
MoleculeView lineWidth setIncrement 1
MoleculeView lineWidth setValue 2
MoleculeView lineWidth setSubMinMax 1 3
MoleculeView complexity setMinMax 0 1
MoleculeView complexity setButtons 0
MoleculeView complexity setIncrement 0.1
MoleculeView complexity setValue 0.2
MoleculeView complexity setSubMinMax 0 1
MoleculeView twistFactor setMinMax 0.5 2
MoleculeView twistFactor setButtons 0
MoleculeView twistFactor setIncrement 0.1
MoleculeView twistFactor setValue 1
MoleculeView twistFactor setSubMinMax 0.5 2
MoleculeView colorscheme setOptValue 0 0
MoleculeView colorscheme setOptValue 1 0
{MoleculeView} fire
MoleculeView continuousColormap setLocalMinMax 0.000000 1.000000
MoleculeView discreteColormap setLocalMinMax 6.000000 20.000000
{MoleculeView} setScheme Color atoms atomic_number
MoleculeView fire
MoleculeView setViewerMask 16383

set hideNewModules 0
create HxSecStructure {SecStructureView}
SecStructureView setIconPosition 266 39
SecStructureView data connect 2RNT_receptor.pdb
SecStructureView discreteColormapBB setDefaultColor 0.78 0.78 0.78
SecStructureView discreteColormapBB setDefaultAlpha 1.000000
SecStructureView discreteColormapBB setLocalRange 1
SecStructureView discreteColormapBB setLocalMinMax 0.000000 1.000000
SecStructureView continuousColormapBB setDefaultColor 0.78 0.78 0.78
SecStructureView continuousColormapBB setDefaultAlpha 1.000000
SecStructureView continuousColormapBB setLocalRange 1
SecStructureView continuousColormapBB setLocalMinMax 1.000000 21.000000
SecStructureView discreteColormapH setDefaultColor 0.3 0.3 0.9
SecStructureView discreteColormapH setDefaultAlpha 1.000000
SecStructureView discreteColormapH setLocalRange 1
SecStructureView discreteColormapH setLocalMinMax 0.000000 1.000000
SecStructureView continuousColormapH setDefaultColor 0.3 0.3 0.9
SecStructureView continuousColormapH setDefaultAlpha 1.000000
SecStructureView continuousColormapH setLocalRange 1
SecStructureView continuousColormapH setLocalMinMax 1.000000 21.000000
SecStructureView discreteColormapS setDefaultColor 0.9 0.2 0.2
SecStructureView discreteColormapS setDefaultAlpha 1.000000
SecStructureView discreteColormapS setLocalRange 1
SecStructureView discreteColormapS setLocalMinMax 0.000000 1.000000
SecStructureView continuousColormapS setDefaultColor 0.9 0.2 0.2
SecStructureView continuousColormapS setDefaultAlpha 1.000000
SecStructureView continuousColormapS setLocalRange 1
SecStructureView continuousColormapS setLocalMinMax 1.000000 21.000000
SecStructureView discreteColormapT setDefaultColor 0.4 0.4 0.4
SecStructureView discreteColormapT setDefaultAlpha 1.000000
SecStructureView discreteColormapT setLocalRange 1
SecStructureView discreteColormapT setLocalMinMax 0.000000 1.000000
SecStructureView continuousColormapT setDefaultColor 0.4 0.4 0.4
SecStructureView continuousColormapT setDefaultAlpha 1.000000
SecStructureView continuousColormapT setLocalRange 1
SecStructureView continuousColormapT setLocalMinMax 1.000000 21.000000
{SecStructureView} fire
{SecStructureView} selectAtoms zab HIJMPLPPJPLOAAAAKBCAGPJB
SecStructureView generalShape setValue 2
SecStructureView generalThreadsWidth setMinMax 0.5 5
SecStructureView generalThreadsWidth setButtons 0
SecStructureView generalThreadsWidth setIncrement 0.3
SecStructureView generalThreadsWidth setValue 2
SecStructureView generalThreadsWidth setSubMinMax 0.5 5
SecStructureView generalRibbonWidth setMinMax 0.5 5
SecStructureView generalRibbonWidth setButtons 0
SecStructureView generalRibbonWidth setIncrement 0.3
SecStructureView generalRibbonWidth setValue 2
SecStructureView generalRibbonWidth setSubMinMax 0.5 5
SecStructureView options setValue 0
SecStructureView backboneTubeRadius setMinMax 0.100000001490116 0.5
SecStructureView backboneTubeRadius setButtons 0
SecStructureView backboneTubeRadius setIncrement 0.0266667
SecStructureView backboneTubeRadius setValue 0.2
SecStructureView backboneTubeRadius setSubMinMax 0.100000001490116 0.5
SecStructureView colorschemeBB setOptValue 0 0
SecStructureView colorschemeBB setOptValue 1 0
SecStructureView helixShape setValue 1
SecStructureView helixTubeRadius setMinMax 0.100000001490116 2
SecStructureView helixTubeRadius setButtons 0
SecStructureView helixTubeRadius setIncrement 0.126667
SecStructureView helixTubeRadius setValue 0.5
SecStructureView helixTubeRadius setSubMinMax 0.100000001490116 2
SecStructureView helixCylinderRadius setMinMax 1 4
SecStructureView helixCylinderRadius setButtons 0
SecStructureView helixCylinderRadius setIncrement 0.2
SecStructureView helixCylinderRadius setValue 2.1
SecStructureView helixCylinderRadius setSubMinMax 1 4
SecStructureView helixRibbonWidth setMinMax 0.5 7
SecStructureView helixRibbonWidth setButtons 0
SecStructureView helixRibbonWidth setIncrement 0.433333
SecStructureView helixRibbonWidth setValue 3
SecStructureView helixRibbonWidth setSubMinMax 0.5 7
SecStructureView colorschemeH setOptValue 0 0
SecStructureView colorschemeH setOptValue 1 0
SecStructureView sheetShape setValue 1
SecStructureView sheetArrowWidth setMinMax 0.5 5
SecStructureView sheetArrowWidth setButtons 0
SecStructureView sheetArrowWidth setIncrement 0.3
SecStructureView sheetArrowWidth setValue 1.5
SecStructureView sheetArrowWidth setSubMinMax 0.5 5
SecStructureView sheetArrowOptions setValue 0 1
SecStructureView sheetArrowOptions setValue 1 1
SecStructureView sheetArrowOptions setValue 2 1
SecStructureView sheetRadius setMinMax 0.100000001490116 2
SecStructureView sheetRadius setButtons 0
SecStructureView sheetRadius setIncrement 0.126667
SecStructureView sheetRadius setValue 0.3
SecStructureView sheetRadius setSubMinMax 0.100000001490116 2
SecStructureView colorschemeS setOptValue 0 0
SecStructureView colorschemeS setOptValue 1 0
SecStructureView turnTubeRadius setMinMax 0.100000001490116 2
SecStructureView turnTubeRadius setButtons 0
SecStructureView turnTubeRadius setIncrement 0.126667
SecStructureView turnTubeRadius setValue 0.3
SecStructureView turnTubeRadius setSubMinMax 0.100000001490116 2
SecStructureView colorschemeT setOptValue 0 0
SecStructureView colorschemeT setOptValue 1 0
SecStructureView structures setValue 0 1
SecStructureView structures setValue 1 1
SecStructureView structures setValue 2 1
SecStructureView structures setValue 3 1
SecStructureView complexity setMinMax 0 1
SecStructureView complexity setButtons 0
SecStructureView complexity setIncrement 0.1
SecStructureView complexity setValue 0.5
SecStructureView complexity setSubMinMax 0 1
SecStructureView highlightingColor setColor 0 1 0 0
{SecStructureView} fire
SecStructureView discreteColormapBB setLocalMinMax 0.000000 1.000000
SecStructureView continuousColormapBB setLocalMinMax 1.000000 21.000000
{SecStructureView} setScheme BackboneColor residues type
SecStructureView discreteColormapH setLocalMinMax 0.000000 1.000000
SecStructureView continuousColormapH setLocalMinMax 1.000000 21.000000
{SecStructureView} setScheme HelixColor residues type
SecStructureView discreteColormapS setLocalMinMax 0.000000 1.000000
SecStructureView continuousColormapS setLocalMinMax 1.000000 21.000000
{SecStructureView} setScheme SheetColor residues type
SecStructureView discreteColormapT setLocalMinMax 0.000000 1.000000
SecStructureView continuousColormapT setLocalMinMax 1.000000 21.000000
{SecStructureView} setScheme TurnColor residues type
SecStructureView fire
SecStructureView setViewerMask 16383

set hideNewModules 0
create HxMolView {MoleculeView2}
MoleculeView2 setIconPosition 279 72
MoleculeView2 data connect 2RNT_ligand.pdb
MoleculeView2 continuousColormap setDefaultColor 0 0 1
MoleculeView2 continuousColormap setDefaultAlpha 1.000000
MoleculeView2 continuousColormap setLocalRange 1
MoleculeView2 continuousColormap setLocalMinMax 0.000000 1.000000
MoleculeView2 discreteColormap setDefaultColor 0 0 1
MoleculeView2 discreteColormap setDefaultAlpha 1.000000
MoleculeView2 discreteColormap setLocalRange 1
MoleculeView2 discreteColormap setLocalMinMax 6.000000 15.000000
{MoleculeView2} fire
{MoleculeView2} selectAtoms zab HIJMPLPPBPACAACDOEAHPJ
MoleculeView2 mode setValue 2
MoleculeView2 quality setValue 1
MoleculeView2 options setValue 0 0
MoleculeView2 options setValue 1 0
MoleculeView2 options setValue 2 0
MoleculeView2 options2 setValue 0 0
MoleculeView2 atomRadius setMinMax 0 2
MoleculeView2 atomRadius setButtons 0
MoleculeView2 atomRadius setIncrement 0.133333
MoleculeView2 atomRadius setValue 0.3
MoleculeView2 atomRadius setSubMinMax 0 2
MoleculeView2 bondRadius setMinMax 0 0.5
MoleculeView2 bondRadius setButtons 0
MoleculeView2 bondRadius setIncrement 0.0333333
MoleculeView2 bondRadius setValue 0.2
MoleculeView2 bondRadius setSubMinMax 0 0.5
MoleculeView2 lineWidth setMinMax 1 3
MoleculeView2 lineWidth setButtons 1
MoleculeView2 lineWidth setIncrement 1
MoleculeView2 lineWidth setValue 2
MoleculeView2 lineWidth setSubMinMax 1 3
MoleculeView2 complexity setMinMax 0 1
MoleculeView2 complexity setButtons 0
MoleculeView2 complexity setIncrement 0.1
MoleculeView2 complexity setValue 0.4
MoleculeView2 complexity setSubMinMax 0 1
MoleculeView2 twistFactor setMinMax 0.5 2
MoleculeView2 twistFactor setButtons 0
MoleculeView2 twistFactor setIncrement 0.1
MoleculeView2 twistFactor setValue 1
MoleculeView2 twistFactor setSubMinMax 0.5 2
MoleculeView2 colorscheme setOptValue 0 0
MoleculeView2 colorscheme setOptValue 1 0
{MoleculeView2} fire
MoleculeView2 continuousColormap setLocalMinMax 0.000000 1.000000
MoleculeView2 discreteColormap setLocalMinMax 6.000000 15.000000
{MoleculeView2} setScheme Color atoms atomic_number
MoleculeView2 fire
MoleculeView2 setViewerMask 16383

set hideNewModules 0
create HxCompMolInterface {CompMolInterface}
CompMolInterface setIconPosition 160 10
CompMolInterface data connect 2RNT_receptor.pdb
CompMolInterface data2 connect 2RNT_ligand.pdb
CompMolInterface fire
CompMolInterface voxelsize setMinMax 0.100000001490116 4
CompMolInterface voxelsize setButtons 0
CompMolInterface voxelsize setIncrement 0.26
CompMolInterface voxelsize setValue 0.5
CompMolInterface voxelsize setSubMinMax 0.100000001490116 4
CompMolInterface cutoffdistance setMinMax 0 20
CompMolInterface cutoffdistance setButtons 0
CompMolInterface cutoffdistance setIncrement 1.33333
CompMolInterface cutoffdistance setValue 1
CompMolInterface cutoffdistance setSubMinMax 0 20
CompMolInterface distancetype setValue 1
CompMolInterface levels setValue 0 0
CompMolInterface fire
CompMolInterface setViewerMask 16383

set hideNewModules 0
[ {CompMolInterface} create 0 
 ] setLabel {2RNT_receptor_2RNT_ligand-interface.surf}
2RNT_receptor_2RNT_ligand-interface.surf setIconPosition 20 104
2RNT_receptor_2RNT_ligand-interface.surf master connect CompMolInterface 0
2RNT_receptor_2RNT_ligand-interface.surf fire
2RNT_receptor_2RNT_ligand-interface.surf fire
2RNT_receptor_2RNT_ligand-interface.surf setViewerMask 16383

set hideNewModules 0
[ {CompMolInterface} create 1 
 ] setLabel {2RNT_receptor_2RNT_ligand-distance.field}
2RNT_receptor_2RNT_ligand-distance.field setIconPosition 21 168
2RNT_receptor_2RNT_ligand-distance.field master connect CompMolInterface 1
2RNT_receptor_2RNT_ligand-distance.field fire
2RNT_receptor_2RNT_ligand-distance.field fire
2RNT_receptor_2RNT_ligand-distance.field setViewerMask 16383

set hideNewModules 0
create HxMolSurfaceView {MolSurfaceView}
MolSurfaceView setIconPosition 273 137
MolSurfaceView data connect 2RNT_receptor_2RNT_ligand-interface.surf
{MolSurfaceView} fire
MolSurfaceView colorField connect 2RNT_receptor_2RNT_ligand-distance.field
MolSurfaceView colormap setDefaultColor 1 0.1 0.1
MolSurfaceView colormap setDefaultAlpha 0.500000
MolSurfaceView colormap connect physics.icol
MolSurfaceView molecule connect 2RNT_receptor.pdb
MolSurfaceView continuousColormap setDefaultColor 0 0 1
MolSurfaceView continuousColormap setDefaultAlpha 1.000000
MolSurfaceView continuousColormap setLocalRange 1
MolSurfaceView continuousColormap setLocalMinMax 0.000000 1.000000
MolSurfaceView discreteColormap setDefaultColor 0 0 1
MolSurfaceView discreteColormap setDefaultAlpha 1.000000
MolSurfaceView discreteColormap setLocalRange 1
MolSurfaceView discreteColormap setLocalMinMax 6.000000 20.000000
MolSurfaceView molecule2 connect 2RNT_ligand.pdb
MolSurfaceView discreteColormap2 setDefaultColor 0 0 1
MolSurfaceView discreteColormap2 setDefaultAlpha 1.000000
MolSurfaceView discreteColormap2 setLocalRange 1
MolSurfaceView discreteColormap2 setLocalMinMax 0.000000 1.000000
MolSurfaceView continuousColormap2 setDefaultColor 0 0 1
MolSurfaceView continuousColormap2 setDefaultAlpha 1.000000
MolSurfaceView continuousColormap2 setLocalRange 1
MolSurfaceView continuousColormap2 setLocalMinMax 6.000000 15.000000
{MolSurfaceView} fire
{MolSurfaceView} selectAtoms zab HIJMPLPPJPLOAAAAKBCAGPJB 0
{MolSurfaceView} selectAtoms zab HIJMPLPPBPACAACDOEAHPJ 1
MolSurfaceView drawStyle setValue 1
MolSurfaceView drawStyle setTexture 0
MolSurfaceView drawStyle setNormalBinding 1
MolSurfaceView setCullingMode noCulling
MolSurfaceView baseTrans setMinMax 0 1
MolSurfaceView baseTrans setButtons 0
MolSurfaceView baseTrans setIncrement 0.1
MolSurfaceView baseTrans setValue 0.8
MolSurfaceView baseTrans setSubMinMax 0 1
MolSurfaceView colorMode setValue 2
MolSurfaceView defaultColors setColor 0 0.5 0.5 0.5
MolSurfaceView defaultColors setColor 1 0.3 0.3 0.8
MolSurfaceView pickAction setValue 0
MolSurfaceView selectionDistance setMinMax 0.100000001490116 100
MolSurfaceView selectionDistance setButtons 0
MolSurfaceView selectionDistance setIncrement 6.66
MolSurfaceView selectionDistance setValue 10
MolSurfaceView selectionDistance setSubMinMax 0.100000001490116 100
MolSurfaceView colorscheme setOptValue 0 0
MolSurfaceView colorscheme setOptValue 1 0
MolSurfaceView colorscheme2 setOptValue 0 0
MolSurfaceView colorscheme2 setOptValue 1 0
{MolSurfaceView} fire
{MolSurfaceView} selectTriangles zab HIJMPLPPHPBEIMICFBDAAKEGMBGAAHAAHLJFKGKA
{MolSurfaceView} fire
MolSurfaceView continuousColormap setLocalMinMax 0.000000 1.000000
MolSurfaceView discreteColormap setLocalMinMax 6.000000 20.000000
{MolSurfaceView} setScheme Color atoms atomic_number
MolSurfaceView discreteColormap2 setLocalMinMax 0.000000 1.000000
MolSurfaceView continuousColormap2 setLocalMinMax 6.000000 15.000000
{MolSurfaceView} setScheme Color2 atoms atomic_number
MolSurfaceView fire
MolSurfaceView setViewerMask 16383
MolSurfaceView select

set hideNewModules 0


viewer 0 setCameraPosition 55.2443 32.2021 45.3112
viewer 0 setCameraOrientation 0.425778 0.0248961 0.904485 2.75218
viewer 0 setCameraFocalDistance 50.4518
viewer 0 setAutoRedraw 1
viewer 0 redraw
