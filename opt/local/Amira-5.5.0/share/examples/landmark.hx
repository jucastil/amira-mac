# Amira Script
remove -All

# Create viewers
viewer 0 show
viewer 0 decoration 1
#viewer 0 setSize 824 825
#viewer 0 setPosition 8 32
viewer 0 setBackgroundMode 1
viewer 0 setAutoRedraw 0

mainWindow show


set hideNewModules 0
[ load $AMIRA_ROOT/data/tutorials/lobus.am ] setLabel lobus.am

set hideNewModules 0
create HxIsosurface {Isosurface}
{Isosurface} setViewerMask 0 
{Isosurface} {data} connect {lobus.am}
{Isosurface} colormap setDefaultColor 0.1 0.25 0.849711
{Isosurface} colormap setDefaultAlpha 0.254335
{Isosurface} drawStyle setValue 1
{Isosurface} drawStyle setTexture 0
{Isosurface} drawStyle setNormalBinding 1
{Isosurface} buffer setIndex -1
{Isosurface} buffer untouch
{Isosurface} threshold setMinMax 21 247
{Isosurface} threshold setValue 75
{Isosurface} options setValue 0 1
{Isosurface} options setValue 1 1
{Isosurface} resolution setMinMaxAll 0 100 0 100 0 100
{Isosurface} resolution setValues 4 4 2
{Isosurface} doIt hit
{Isosurface} fire
{Isosurface} setViewerMask 32767

set hideNewModules 0
[ load $AMIRA_ROOT/data/tutorials/lobus2.am ] setLabel lobus2.am

set hideNewModules 0
create HxIsosurface {Isosurface2}
{Isosurface2} setViewerMask 0 
{Isosurface2} {data} connect {lobus2.am}
{Isosurface2} colormap setDefaultColor 1 0.9 0.0548642
{Isosurface2} colormap setDefaultAlpha 0.554913
{Isosurface2} drawStyle setValue 1
{Isosurface2} drawStyle setTexture 0
{Isosurface2} drawStyle setNormalBinding 1
{Isosurface2} buffer setIndex -1
{Isosurface2} buffer untouch
{Isosurface2} threshold setMinMax 21 247
{Isosurface2} threshold setValue 75
{Isosurface2} options setValue 0 1
{Isosurface2} options setValue 1 1
{Isosurface2} resolution setMinMaxAll 0 100 0 100 0 100
{Isosurface2} resolution setValues 4 4 2
{Isosurface2} doIt hit
{Isosurface2} fire
{Isosurface2} setViewerMask 65533

set hideNewModules 0
viewer 0 setCameraOrientation -0.803515 -0.0640563 0.591828 2.45417
viewer 0 setCameraPosition -222.285 258.958 7.22364
viewer 0 setCameraFocalDistance 359.098
viewer 0 setAutoRedraw 1
viewer 0 redraw
