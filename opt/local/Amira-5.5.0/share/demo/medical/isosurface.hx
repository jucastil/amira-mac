# Amira Script
remove -All

# Create viewers
viewer 0 show
viewer 0 setBackgroundMode 1
viewer 0 setAutoRedraw 0

mainWindow show

set hideNewModules 1
[ load $AMIRA_ROOT/data/colormaps/temperature.icol ] setLabel temperature.icol
{temperature.icol} setIconPosition 0 0
{temperature.icol} setViewerMask 0
{temperature.icol} setMinMax 38 44
{temperature.icol} fire
{temperature.icol} setViewerMask 16383

set hideNewModules 1
[ load $AMIRA_ROOT/data/colormaps/physics.icol ] setLabel physics.icol
{physics.icol} setIconPosition 0 0
{physics.icol} setViewerMask 0
{physics.icol} setMinMax 0 1
{physics.icol} fire
{physics.icol} setViewerMask 16383

set hideNewModules 0
[ load $AMIRA_ROOT/data/medical/reg005.ctdata.am ] setLabel reg005.ctdata
{reg005.ctdata} setIconPosition 20 10
{reg005.ctdata} setViewerMask 0
{reg005.ctdata} update
{reg005.ctdata} fire
{reg005.ctdata} setViewerMask 16383

set hideNewModules 0
create HxResample {Resample}
{Resample} setIconPosition 160 10
{Resample} setViewerMask 0
{Resample} data connect reg005.ctdata
{Resample} fire
{Resample} filter setValue 1
{Resample} resolution setMinMaxAll 1 10000 1 10000 1 10000
{Resample} resolution setValues 100 100 60
{Resample} average setMinMaxAll 1 8 1 8 1 8
{Resample} average setValues 2 2 1
{Resample} action setIndex 0
{Resample} action untouch
{Resample} fire
{Resample} setViewerMask 16383

set hideNewModules 0
[ {Resample} create ] setLabel reg005.Resampled
{reg005.Resampled} setIconPosition 20 40
{reg005.Resampled} setViewerMask 0
reg005.Resampled master connect Resample
{reg005.Resampled} update
{reg005.Resampled} fire
{reg005.Resampled} setViewerMask 16383

set hideNewModules 0
create HxIsosurface {Isosurface}
{Isosurface} setIconPosition 318 40
{Isosurface} setViewerMask 0
Isosurface data connect reg005.Resampled
{Isosurface} colormap setDefaultColor 1 0.8 0.4
{Isosurface} colormap setDefaultAlpha 1.000000
{Isosurface} threshold setMinMax -1139 1660
{Isosurface} threshold setValue -200
{Isosurface} options setValue 0 1
{Isosurface} options setValue 1 0
{Isosurface} resolution setValues 2 2 2
{Isosurface} doIt hit
{Isosurface} fire
{Isosurface} setViewerMask 16383
{Isosurface} select

set hideNewModules 0
[ load $AMIRA_ROOT/data/medical/reg005.labels.am ] setLabel reg005.labels
{reg005.labels} setIconPosition 20 70
{reg005.labels} setViewerMask 0
{reg005.labels} primary setValue 0
{reg005.labels} update
{reg005.labels} fire
{reg005.labels} setViewerMask 16383

set hideNewModules 0

viewer setCameraOrientation -0.931737 0.102328 -0.348419 3.65041
viewer setCameraPosition 86.216 -32.2592 -41.343
viewer setCameraFocalDistance 109.791
viewer 0 setAutoRedraw 1
viewer 0 redraw
