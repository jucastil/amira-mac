# Amira Script
remove -All
viewer 0 show
mainWindow show
viewer 0 setAutoRedraw 0

load ${AMIRA_ROOT}/data/colormaps/temperature.icol
load ${AMIRA_ROOT}/data/colormaps/efield.icol
load ${AMIRA_ROOT}/data/colormaps/sar.icol
load ${AMIRA_ROOT}/data/colormaps/physics.icol
load ${AMIRA_ROOT}/data/misc/r_cluster.iv

create HxIsosurface Isosurface
create HxIvDisplay IvDisplay
temperature.icol hideIcon
efield.icol hideIcon
sar.icol hideIcon
physics.icol hideIcon
temperature.icol setIconPosition 0 0
temperature.icol setViewerMask 16383
efield.icol setIconPosition 0 0
efield.icol setViewerMask 16383
sar.icol setIconPosition 0 0
sar.icol setViewerMask 16383
physics.icol setIconPosition 0 0
physics.icol setViewerMask 16383
r_cluster.iv setIconPosition 20 10
r_cluster.iv setViewerMask 16383
Isosurface setIconPosition 318 40
Isosurface setViewerMask 16383

IvDisplay setIconPosition 323 10
IvDisplay setViewerMask 16383
IvDisplay data connect r_cluster.iv
IvDisplay drawStyle setValue 0 
IvDisplay fire

viewer 0 setCameraPosition 18.9072 17.142 18.3199
viewer 0 setCameraOrientation 0.336644 0.30839 0.8897 3.13243
viewer 0 setCameraFocalDistance 31.4157

load ${AMIRA_ROOT}/data/misc/r_000000.am
r_000000.am setIconPosition 20 40
r_000000.am setViewerMask 16383
load ${AMIRA_ROOT}/data/misc/r_000002.am
load ${AMIRA_ROOT}/data/misc/r_000004.am

Isosurface select
Isosurface data connect r_000004.am
Isosurface threshold setMinMax 0 256
Isosurface threshold setValue 76.8
Isosurface colormap setDefaultColor 0.3 0.3 1
Isosurface colormap setDefaultAlpha 0.070000
Isosurface options setValue 0 0
Isosurface options setValue 1 0
Isosurface drawStyle setValue 4
Isosurface fire
Isosurface doIt hit
Isosurface fire
Isosurface doIt snap 1
Isosurface fire

viewer 0 setAutoRedraw 1
viewer 0 redraw

load ${AMIRA_ROOT}/data/misc/r_000006.am
load ${AMIRA_ROOT}/data/misc/r_000007.am
load ${AMIRA_ROOT}/data/misc/r_000008.am

proc loop { } {
    Isosurface data connect r_000002.am
    Isosurface fire
    viewer 0 redraw
    update
    Isosurface data connect r_000004.am
    Isosurface fire
    viewer 0 redraw
    update
    Isosurface data connect r_000006.am
    Isosurface fire
    viewer 0 redraw
    update
    Isosurface data connect r_000007.am
    Isosurface fire
    update
    viewer 0 redraw
    Isosurface data connect r_000008.am
    Isosurface fire
    viewer 0 redraw
    update
}

echo "Type 'loop' for time animation !"
