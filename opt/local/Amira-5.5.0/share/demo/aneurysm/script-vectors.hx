# Amira Script
remove -All

# Create viewers
viewer 0 show
viewer 0 setAutoRedraw 0

if { ![info exists FULLSCREEN] || !$FULLSCREEN } {
mainWindow show
}

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/aneurysm/tetragrid.am ] setLabel {tetragrid.am}
{tetragrid.am} setIconPosition 20 38
{tetragrid.am} setViewerMask 0 
{tetragrid.am} fire
{tetragrid.am} setViewerMask 65535

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/aneurysm/velocity.am ] setLabel {velocity.am}
{velocity.am} setIconPosition 20 66
{velocity.am} setViewerMask 0 
{velocity.am} {grid} connect {tetragrid.am}
{velocity.am} fire
{velocity.am} setViewerMask 65535

set hideNewModules 0
create HxBoundingBox {BoundingBox}
{BoundingBox} setIconPosition 323 10
{BoundingBox} setViewerMask 0 
{BoundingBox} {data} connect {tetragrid.am}
{BoundingBox} text setValue 0 0
{BoundingBox} fire
{BoundingBox} setViewerMask 65535

set hideNewModules 0
create HxGridBoundary {GridBoundary}
{GridBoundary} setIconPosition 321 38
{GridBoundary} setViewerMask 0 
{GridBoundary} data connect {tetragrid.am}
{GridBoundary} fire
{GridBoundary} {data} connect {tetragrid.am}
{GridBoundary} colormap setDefaultColor 1 0.1 0.1
{GridBoundary} colormap setDefaultAlpha 0.500000
{GridBoundary} drawStyle setValue 1
{GridBoundary} drawStyle setTexture 0
{GridBoundary} drawStyle setNormalBinding 0
{GridBoundary} buffer setIndex -1
{GridBoundary} buffer untouch
{GridBoundary} materials setIndex 0 1
{GridBoundary} materials setIndex 1 0
{GridBoundary} colorMode setValue 0
{GridBoundary} fire
{GridBoundary} buffer setIndex 3
{GridBoundary} selectTriangles zab HIJMPLPPHPBEIMICFBDAAKEGMBCIBIAFKDGABEAMHGGAAPMEAAIFMKKOBA
{GridBoundary} fire
{GridBoundary} setViewerMask 65535

set hideNewModules 0
create HxArbitraryCut {EmptyPlane}
{EmptyPlane} setIconPosition 329 66
{EmptyPlane} setViewerMask 0 
{EmptyPlane} {data} connect {velocity.am}
{EmptyPlane} orientation setIndex -1
{EmptyPlane} orientation untouch
{EmptyPlane} options setValue 0 1
{EmptyPlane} options setValue 1 0
{EmptyPlane} options setValue 2 1
{EmptyPlane} translate setMinMax 0 100
{EmptyPlane} translate setValue 49
{EmptyPlane} orientation untouch
{EmptyPlane} setPlane -0.757691 1.49144 26.708 1 6.62101e-008 2.72033e-008 -2.72033e-008 0.610905 -0.791704
{EmptyPlane} fire
{EmptyPlane} setViewerMask 65535

set hideNewModules 0
create HxVectors {Vectors}
{Vectors} setIconPosition 329 86
{Vectors} setViewerMask 0 
{Vectors} {data} connect {velocity.am}
{Vectors} {module} connect {EmptyPlane}
{Vectors} colormap setDefaultColor 0.13 0.08 0.6
{Vectors} colormap setDefaultAlpha 0.500000
{Vectors} {colormap} connect {temperature.icol}
{Vectors} colormap setMinMax 0 0.500000
{Vectors} resolution setMinMax 0 -1e+024 1e+024
{Vectors} resolution setValue 0 150
{Vectors} resolution setMinMax 1 -1e+024 1e+024
{Vectors} resolution setValue 1 150
{Vectors} scale setMinMax 0 5
{Vectors} scale setValue 1
{Vectors} mode setValue 0 0
{Vectors} mode setValue 1 0
{Vectors} mode setValue 2 1
{Vectors} mode setValue 3 0
{Vectors} colorMode setValue 0
{Vectors} phase setMinMax 0 360
{Vectors} phase setValue 0
{Vectors} fire
{Vectors} setViewerMask 65535

EmptyPlane invertClippingPlane
GridBoundary clipGeom EmptyPlane
BoundingBox clipGeom EmptyPlane
{EmptyPlane} select

set hideNewModules 0

load ${AMIRA_ROOT}/data/aneurysm/keyframecampath.civ

viewer 0 setCameraPosition 1.47288 0.294706 24.0704
viewer 0 setCameraOrientation 0.954844 -0.0619855 0.290568 2.7333
viewer 0 setCameraFocalDistance 3.58044
viewer 0 setAutoRedraw 1
viewer 0 redraw

proc onKeyF2 { } {
   global STEREO;

   Vectors unclipGeom EmptyPlane
   GridBoundary unclipGeom EmptyPlane
   BoundingBox setViewerMask 0
   EmptyPlane setViewerMask 0
   if {[info exists STEREO]} {
    viewer 0 setStereo 0.2
   }
   viewer 0 setCameraPath keyframecampath.civ
   viewer 0 autoAnimateCamera 1
}

