# Amira Script
if { [ exists aneurism.ctdata ] } { aneurism.ctdata hideIcon }
remove -all

# Create viewers
viewer 0 show
viewer 0 setAutoRedraw 0

if { ![info exists FULLSCREEN] || !$FULLSCREEN } {
    mainWindow show
}

if { ![ exists aneurism.ctdata ] } {
set hideNewModules 0
[ load ${AMIRA_ROOT}/data/aneurysm/aneurism.ctdata ] setLabel {aneurism.ctdata}
{aneurism.ctdata} setIconPosition 20 10
{aneurism.ctdata} setViewerMask 0 
{aneurism.ctdata} fire
} else { aneurism.ctdata showIcon }
{aneurism.ctdata} setViewerMask 65535

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/aneurysm/aneurism.surf ] setLabel {aneurism.surf}
{aneurism.surf} setIconPosition 20 66
{aneurism.surf} setViewerMask 0 
{aneurism.surf} fire
{aneurism.surf} setViewerMask 65535

set hideNewModules 0
create HxBoundingBox {BoundingBox}
{BoundingBox} setIconPosition 322 10
{BoundingBox} setViewerMask 0 
{BoundingBox} {data} connect {aneurism.ctdata}
{BoundingBox} text setValue 0 0
{BoundingBox} fire
{BoundingBox} setViewerMask 65535

set hideNewModules 0
create HxOrthoSlice {OrthoSlice}
{OrthoSlice} setIconPosition 336 38
{OrthoSlice} setViewerMask 0 
{OrthoSlice} {data} connect {aneurism.ctdata}
{OrthoSlice} fire
{OrthoSlice} sliceOrientation setValue 0
{OrthoSlice} fire
{OrthoSlice} options setValue 0 1
{OrthoSlice} options setValue 1 0
{OrthoSlice} mappingType setValue 0
{OrthoSlice} linearRange setMinMax 0 -1e+024 1e+024
{OrthoSlice} linearRange setValue 0 -200
{OrthoSlice} linearRange setMinMax 1 -1e+024 1e+024
{OrthoSlice} linearRange setValue 1 200
{OrthoSlice} contrastLimit setMinMax 0 -1e+024 1e+024
{OrthoSlice} contrastLimit setValue 0 7
{OrthoSlice} colormap setDefaultColor 1 0.8 0.5
{OrthoSlice} colormap setDefaultAlpha 1.000000
{OrthoSlice} sliceNumber setMinMax 0 40
{OrthoSlice} sliceNumber setValue 15
{OrthoSlice} transparency setValue 0
{OrthoSlice} fire

{OrthoSlice} fire
{OrthoSlice} setViewerMask 65535

set hideNewModules 0
create HxDisplaySurface {SurfaceView}
{SurfaceView} setIconPosition 325 66
{SurfaceView} setViewerMask 0 
{SurfaceView} {data} connect {aneurism.surf}
{SurfaceView} colormap setDefaultColor 1 0.1 0.1
{SurfaceView} colormap setDefaultAlpha 0.500000
{SurfaceView} drawStyle setValue 1
{SurfaceView} drawStyle setTexture 0
{SurfaceView} drawStyle setNormalBinding 0
{SurfaceView} buffer setIndex -1
{SurfaceView} buffer untouch
{SurfaceView} materials setIndex 0 1
{SurfaceView} materials setIndex 1 0
{SurfaceView} colorMode setValue 0
{SurfaceView} baseTrans setMinMax 0 1
{SurfaceView} baseTrans setValue 0.8
{SurfaceView} fire
{SurfaceView} selectTriangles zab HIJMONMBABANAAAAAMACKAPHCPONKNOBAGCEAAAAKMLJHKPDPBLKME
{SurfaceView} fire
{SurfaceView} setViewerMask 65535

set hideNewModules 0

viewer 0 setCameraPosition -3.97397 12.9368 31.8594
viewer 0 setCameraOrientation -0.0842714 0.538267 0.838551 3.41954
viewer 0 setCameraFocalDistance 14.2409
viewer 0 setAutoRedraw 1
viewer 0 redraw
