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
create HxIsosurface {Isosurface}
{Isosurface} setIconPosition 245 39
{Isosurface} setViewerMask 0
{Isosurface} {data} connect {lobus.am}
{Isosurface} colormap setDefaultColor 1 0.8 0.4
{Isosurface} colormap setDefaultAlpha 0.157000
{Isosurface} drawStyle setValue 1
{Isosurface} drawStyle setTexture 0
{Isosurface} drawStyle setNormalBinding 1
{Isosurface} buffer setIndex -1
{Isosurface} buffer untouch
{Isosurface} threshold setMinMax 22 254
{Isosurface} threshold setValue 77
{Isosurface} options setValue 0 1
{Isosurface} options setValue 1 1
{Isosurface} resolution setMinMax 0 -1e+24 1e+24
{Isosurface} resolution setValue 0 2
{Isosurface} resolution setMinMax 1 -1e+24 1e+24
{Isosurface} resolution setValue 1 2
{Isosurface} resolution setMinMax 2 -1e+24 1e+24
{Isosurface} resolution setValue 2 2
{Isosurface} doIt setIndex -1
{Isosurface} doIt untouch
{Isosurface} doIt hit
{Isosurface} update
{Isosurface} fire
{Isosurface} setViewerMask 16383

set hideNewModules 0
create HxObliqueSlice {ObliqueSlice}
{ObliqueSlice} setIconPosition 246 69
{ObliqueSlice} setViewerMask 0
{ObliqueSlice} {data} connect {lobus.am}
{ObliqueSlice} fire
{ObliqueSlice} {data} connect {lobus.am}
{ObliqueSlice} colormap setDefaultColor 1 0.8 0.5
{ObliqueSlice} colormap setDefaultAlpha 0.500000
{ObliqueSlice} {colormap} connect {physics.icol}
{ObliqueSlice} orientation setIndex -1
{ObliqueSlice} orientation untouch
{ObliqueSlice} options setValue 0 0
{ObliqueSlice} options setValue 1 0
{ObliqueSlice} options setValue 2 0
{ObliqueSlice} translate setMinMax 0 86
{ObliqueSlice} translate setValue 56
{ObliqueSlice} mappingType setValue 0
{ObliqueSlice} linearRange setMinMax 0 -1e+24 1e+24
{ObliqueSlice} linearRange setValue 0 0
{ObliqueSlice} linearRange setMinMax 1 -1e+24 1e+24
{ObliqueSlice} linearRange setValue 1 255
{ObliqueSlice} contrastLimit setMinMax 0 0 99
{ObliqueSlice} contrastLimit setValue 0 7
{ObliqueSlice} sampling setValue 0 1
{ObliqueSlice} sampling setValue 1 1
{ObliqueSlice} sampling setValue 2 0
{ObliqueSlice} overlayType setValue 0
{ObliqueSlice} transparency setValue 0
{ObliqueSlice} orientation untouch
{ObliqueSlice} setPlane 118.602 76.9956 29.895 0.854297 0.394158 0.338845 0.0557491 -0.717616 0.694204
{ObliqueSlice} update
{ObliqueSlice} fire
{ObliqueSlice} setViewerMask 16383
{ObliqueSlice} select

set hideNewModules 0
create HxBoundingBox {BoundingBox}
{BoundingBox} setIconPosition 245 10
{BoundingBox} setViewerMask 0
{BoundingBox} {data} connect {lobus.am}
{BoundingBox} text setValue 0 0
{BoundingBox} update
{BoundingBox} fire
{BoundingBox} setViewerMask 16383

set hideNewModules 0
create HxIsolines {Isolines}
{Isolines} setIconPosition 246 89
{Isolines} setViewerMask 0
{Isolines} {data} connect {lobus.am}
{Isolines} {module} connect {ObliqueSlice}
{Isolines} fire
{Isolines} colormap setDefaultColor 1 0 0
{Isolines} colormap setDefaultAlpha 0.500000
{Isolines} spacing setValue 0
{Isolines} uniform setValue 0 50
{Isolines} uniform setValue 1 150
{Isolines} uniform setMinMax 2 1 200
{Isolines} uniform setValue 2 2
{Isolines} explicit setValue "80 196"
{Isolines} parameters setMinMax 0 16 4096
{Isolines} parameters setValue 0 128
{Isolines} parameters setMinMax 1 0 10
{Isolines} parameters setValue 1 2
{Isolines} options setValue 0 0
{Isolines} options setValue 1 0
{Isolines} update
{Isolines} fire
{Isolines} setViewerMask 16383

Isosurface clipGeom ObliqueSlice

set hideNewModules 0

viewer 0 setCameraPosition 365.75 298.257 -130.492
viewer 0 setCameraOrientation 0.881318 -0.404604 0.244078 4.01077
viewer 0 setCameraFocalDistance 398.937
viewer 0 setAutoRedraw 1
viewer 0 redraw
