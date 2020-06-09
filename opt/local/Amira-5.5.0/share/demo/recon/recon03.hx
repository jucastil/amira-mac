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
{lobus.labels.am} setIconPosition 20 40
{lobus.labels.am} setViewerMask 0
{lobus.labels.am} {ImageData} connect {lobus.am}
{lobus.labels.am} primary setValue 0
{lobus.labels.am} update
{lobus.labels.am} fire
{lobus.labels.am} setViewerMask 16383

set hideNewModules 0
create HxResample {Resample}
{Resample} setIconPosition 160 40
{Resample} setViewerMask 0
{Resample} {data} connect {lobus.labels.am}
{Resample} fire
{Resample} filter setValue 1
{Resample} resolution setMinMax 0 1 10000
{Resample} resolution setValue 0 128
{Resample} resolution setMinMax 1 1 10000
{Resample} resolution setValue 1 128
{Resample} resolution setMinMax 2 1 10000
{Resample} resolution setValue 2 87
{Resample} average setMinMax 0 1 8
{Resample} average setValue 0 2
{Resample} average setMinMax 1 1 8
{Resample} average setValue 1 2
{Resample} average setMinMax 2 1 8
{Resample} average setValue 2 1
{Resample} action setIndex -1
{Resample} action untouch
{Resample} update
{Resample} fire
{Resample} setViewerMask 16383

set hideNewModules 0
[ {Resample} create
 ] setLabel {lobus.Resampled}
{lobus.Resampled} setIconPosition 20 70
{lobus.Resampled} setViewerMask 0
{lobus.Resampled} {master} connect {Resample}
{lobus.Resampled} primary setValue 0
{lobus.Resampled} update
{lobus.Resampled} fire
{lobus.Resampled} setViewerMask 16383

set hideNewModules 0
create HxGMC {GMC}
{GMC} setIconPosition 160 70
{GMC} setViewerMask 0
{GMC} {data} connect {lobus.Resampled}
{GMC} options setValue 0 1
{GMC} options setValue 1 1
{GMC} minEdgeLength setMinMax 0 0 0.5
{GMC} minEdgeLength setValue 0 0
{GMC} action setIndex -1
{GMC} action untouch
{GMC} update
{GMC} fire
{GMC} setViewerMask 16383

set hideNewModules 0
[ {GMC} create {lobus.gmc-surf}
 ] setLabel {lobus.gmc-surf}
{lobus.gmc-surf} setIconPosition 20 100
{lobus.gmc-surf} setViewerMask 0
{lobus.gmc-surf} {master} connect {GMC}
{lobus.gmc-surf} update
{lobus.gmc-surf} fire
{lobus.gmc-surf} setViewerMask 16383

set hideNewModules 0
create HxDisplaySurface {SurfaceView}
{SurfaceView} setIconPosition 295 100
{SurfaceView} setViewerMask 0
{SurfaceView} {data} connect {lobus.gmc-surf}
{SurfaceView} colormap setDefaultColor 1 0.1 0.1
{SurfaceView} colormap setDefaultAlpha 0.500000
{SurfaceView} drawStyle setValue 0
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
{SurfaceView} update
{SurfaceView} fire
{SurfaceView} setViewerMask 16383
{SurfaceView} select

set hideNewModules 0

viewer 0 setCameraPosition 98.4314 101.568 -280.586
viewer 0 setCameraOrientation 1 0 0 3.14159
viewer 0 setCameraFocalDistance 355.025
viewer 0 setAutoRedraw 1
viewer 0 redraw
