# Amira Script
remove -All

# Create viewers
viewer 0 show
viewer 0 setAutoRedraw 0

mainWindow show

set hideNewModules 1
[ load ${AMIRA_ROOT}/data/colormaps/physics.icol ] setLabel {physics.icol}
{physics.icol} setIconPosition 0 0
{physics.icol} setViewerMask 0
{physics.icol} setMinMax 0 100
{physics.icol} flags setValue 0
{physics.icol} shift setMinMax -1 1
{physics.icol} shift setValue 0
{physics.icol} scale setMinMax 0 1
{physics.icol} scale setValue 1
{physics.icol} update
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
{volrenRed.col} update
{volrenRed.col} fire
{volrenRed.col} setViewerMask 16383

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/tutorials/lobus.am ] setLabel {lobus.am}
{lobus.am} setIconPosition 9 10
{lobus.am} setViewerMask 0
{lobus.am} update
{lobus.am} fire
{lobus.am} setViewerMask 16383

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/tutorials/lobus.labels.am ] setLabel {lobus.labels.am}
{lobus.labels.am} setIconPosition 25 51
{lobus.labels.am} setViewerMask 0
{lobus.labels.am} {ImageData} connect {lobus.am}
{lobus.labels.am} primary setValue 0
{lobus.labels.am} update
{lobus.labels.am} fire
{lobus.labels.am} setViewerMask 16383
{lobus.labels.am} select

set hideNewModules 0
create HxOrthoSlice {OrthoSlice}
{OrthoSlice} setIconPosition 293 51
{OrthoSlice} setViewerMask 0
{OrthoSlice} {data} connect {lobus.labels.am}
{OrthoSlice} fire
{OrthoSlice} sliceOrientation setValue 0
{OrthoSlice} fire
{OrthoSlice} options setValue 0 1
{OrthoSlice} options setValue 1 0
{OrthoSlice} mappingType setValue 0
{OrthoSlice} linearRange setMinMax 0 -1e+24 1e+24
{OrthoSlice} linearRange setValue 0 0
{OrthoSlice} linearRange setMinMax 1 -1e+24 1e+24
{OrthoSlice} linearRange setValue 1 3
{OrthoSlice} contrastLimit setMinMax 0 -1e+24 1e+24
{OrthoSlice} contrastLimit setValue 0 7
{OrthoSlice} colormap setDefaultColor 1 0.8 0.5
{OrthoSlice} colormap setDefaultAlpha 1.000000
{OrthoSlice} sliceNumber setMinMax 0 86
{OrthoSlice} sliceNumber setValue 43
{OrthoSlice} transparency setValue 0
{OrthoSlice} fire

{OrthoSlice} update
{OrthoSlice} fire
{OrthoSlice} setViewerMask 16383

set hideNewModules 0

viewer 0 setCameraPosition 100 99.9992 -284.492
viewer 0 setCameraOrientation 1 0 0 3.14159
viewer 0 setCameraFocalDistance 352.992
viewer 0 setAutoRedraw 1
viewer 0 redraw
