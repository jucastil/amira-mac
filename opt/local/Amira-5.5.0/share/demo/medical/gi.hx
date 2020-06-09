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
[ load $AMIRA_ROOT/data/medical/reg005.labels.am ] setLabel reg005.labels
{reg005.labels} setIconPosition 20 40
{reg005.labels} setViewerMask 0
{reg005.labels} primary setValue 0
{reg005.labels} update
{reg005.labels} fire
{reg005.labels} setViewerMask 16383

set hideNewModules 0

create HxGiEditor GI
GI attach {reg005.labels}
{reg005.labels} select

viewer 0 setCameraPosition 79.2296 -46.383 77.572
viewer 0 setCameraOrientation -0.824351 -0.287416 -0.487686 5.04756
viewer 0 setCameraFocalDistance 99.1469
viewer 0 setAutoRedraw 1
viewer 0 redraw
