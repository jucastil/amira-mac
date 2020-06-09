# Amira Script
remove -All

# Create viewers
viewer 0 show
viewer 0 setBackgroundMode 1
viewer 0 decoration 1
viewer 0 setTransparencyType 6
viewer 0 setAutoRedraw 0

mainWindow show

set hideNewModules 1
[ load ${AMIRA_ROOT}/data/colormaps/physics.icol ] setLabel physics.icol
{physics.icol} setIconPosition 0 0
{physics.icol} setViewerMask 0
{physics.icol} setMinMax 0 100
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
{volrenRed.col} setMinMax 50 160
{volrenRed.col} flags setValue 0
{volrenRed.col} shift setMinMax -1 1
{volrenRed.col} shift setValue 0
{volrenRed.col} scale setMinMax 0 1
{volrenRed.col} scale setValue 1
{volrenRed.col} fire
{volrenRed.col} setViewerMask 16383

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/tutorials/lobus.am ] setLabel lobus.am
{lobus.am} setIconPosition 9 10
{lobus.am} setViewerMask 0
{lobus.am} fire
{lobus.am} setViewerMask 16383

set hideNewModules 0
create HxVoltex {Voltex}
{Voltex} setIconPosition 246 10
{Voltex} setViewerMask 0
{Voltex} {data} connect {lobus.am}
{Voltex} colormap setDefaultColor 1 0.8 0.5
{Voltex} colormap setDefaultAlpha 0.500000
{Voltex} {colormap} connect {volrenRed.col}
{Voltex} mode setValue 1
{Voltex} range setMinMax 0 -1e+24 1e+24
{Voltex} range setValue 0 -200
{Voltex} range setMinMax 1 -1e+24 1e+24
{Voltex} range setValue 1 200
{Voltex} lookup setValue 2
{Voltex} alphaScale setMinMax 0 1
{Voltex} alphaScale setValue 1
{Voltex} slices setMinMax 0 256
{Voltex} slices setValue 256
{Voltex} downsample setMinMax 0 -1e+24 1e+24
{Voltex} downsample setValue 0 1
{Voltex} downsample setMinMax 1 -1e+24 1e+24
{Voltex} downsample setValue 1 1
{Voltex} downsample setMinMax 2 -1e+24 1e+24
{Voltex} downsample setValue 2 1
{Voltex} fire
{Voltex} setViewerMask 16383
{Voltex} select
{Voltex} doIt hit
{Voltex} fire

set hideNewModules 0

viewer 0 setCameraPosition 322.716 106.553 -479.578
viewer 0 setCameraOrientation 0.984808 -7.5904e-09 0.173648 3.14159
viewer 0 setCameraFocalDistance 591.198
viewer 0 setAutoRedraw 1
viewer 0 redraw
