# Amira Script
remove -All

# Create viewers
viewer 0 show
viewer 0 setAutoRedraw 0

mainWindow show

set hideNewModules 1
[ load ${AMIRA_ROOT}/data/colormaps/temperature.icol ] setLabel {temperature.icol}
{temperature.icol} setIconPosition 0 0
{temperature.icol} setViewerMask 0
{temperature.icol} setMinMax 38 44
{temperature.icol} fire
{temperature.icol} setViewerMask 16383

set hideNewModules 1
[ load ${AMIRA_ROOT}/data/colormaps/physics.icol ] setLabel {physics.icol}
{physics.icol} setIconPosition 0 0
{physics.icol} setViewerMask 0
{physics.icol} setMinMax 0 1
{physics.icol} fire
{physics.icol} setViewerMask 16383

set hideNewModules 0
load $AMIRA_ROOT/data/medical/reg005.tetragrid.am
{reg005.tetragrid.am} setIconPosition 20 10
{reg005.tetragrid.am} setViewerMask 0
{reg005.tetragrid.am} update
{reg005.tetragrid.am} fire
{reg005.tetragrid.am} setViewerMask 16383

set hideNewModules 0
load $AMIRA_ROOT/data/medical/reg005.thermvals.am
{reg005.thermvals.am} setIconPosition 20 40
{reg005.thermvals.am} setViewerMask 0
{reg005.thermvals.am} {grid} connect {reg005.tetragrid.am}
{reg005.thermvals.am} update
{reg005.thermvals.am} fire
{reg005.thermvals.am} setViewerMask 16383

set hideNewModules 0
create HxGridVolume {GridVolume}
{GridVolume} setIconPosition 264 10
{GridVolume} setViewerMask 0
{GridVolume} data connect {reg005.tetragrid.am}
{GridVolume} fire
{GridVolume} {data} connect {reg005.tetragrid.am}
{GridVolume} colormap setDefaultColor 1 0.1 0.1
{GridVolume} colormap setDefaultAlpha 0.500000
{GridVolume} drawStyle setValue 2
{GridVolume} drawStyle setTexture 0
{GridVolume} drawStyle setNormalBinding 0
{GridVolume} buffer setIndex -1
{GridVolume} buffer untouch
{GridVolume} materials setIndex 0 2
{GridVolume} colorMode setValue 0
{GridVolume} fire
{GridVolume} buffer setIndex 3
{GridVolume} selectTetra zab HIJMONNDMBAJIADABAEENBENANFGJDFDNKBGKLLBBAGBJDAOBEECNEMDHLPAMPHDJKIIDJJJNHOIFOBLENEOABDPHBEGDMPKDNKMHENEMMFCLGPNOLDPAAAAAAAAAAAAAALMKFADLAKPLAEL
{GridVolume} update
{GridVolume} fire
{GridVolume} setViewerMask 16383

set hideNewModules 0
create HxIsoTetra {Isosurface}
{Isosurface} setIconPosition 271 40
{Isosurface} setViewerMask 0
{Isosurface} {data} connect {reg005.thermvals.am}
{Isosurface} colormap setDefaultColor 1 0.8 0.4
{Isosurface} colormap setDefaultAlpha 0.500000
{Isosurface} {colormap} connect {temperature.icol}
{Isosurface} drawStyle setValue 1
{Isosurface} drawStyle setTexture 0
{Isosurface} drawStyle setNormalBinding 1
{Isosurface} buffer setIndex -1
{Isosurface} buffer untouch
{Isosurface} threshold setMinMax 27.746 43.9744
{Isosurface} threshold setValue 42.5
{Isosurface} fire
{Isosurface} setViewerMask 16383

create HxSplats {Splats}
{Splats} setIconPosition 293 70
{Splats} setViewerMask 0
{Splats} data connect {reg005.thermvals.am}
{Splats} fire
{Splats} alphaScale setMinMax 1 20
{Splats} alphaScale setValue 8
{Splats} gamma setMinMax 0.5 4
{Splats} gamma setValue 1.75
{Splats} range setValue 0 40.5
{Splats} range setValue 1 44
{Splats} interpolation setValue 1
{Splats} fire
{Splats} setViewerMask 16383
{Splats} select

viewer 0 setCameraPosition 41.7826 -27.3795 58.3263
viewer 0 setCameraOrientation 0.952322 0.189421 0.23917 1.10617
viewer 0 setCameraFocalDistance 59.1706
viewer 0 setAutoRedraw 1
viewer 0 redraw
