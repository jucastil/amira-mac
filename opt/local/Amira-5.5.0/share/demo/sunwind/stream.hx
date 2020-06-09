# Amira Script
if { ![app hasLicense MeshPack] } { 
	theMsg error "This script requires a MeshPack license." 
	return 
} 

remove -All

set DATADIR $AMIRA_ROOT/data/

load ${DATADIR}/colormaps/temperature.icol
temperature.icol hideIcon
temperature.icol setMinMax 0 40

load ${DATADIR}/colormaps/efield.icol
efield.icol hideIcon

load ${DATADIR}/colormaps/sar.icol
sar.icol hideIcon

load ${DATADIR}/colormaps/physics.icol
physics.icol hideIcon

create HxMagDipol MagDipol
MagDipol fire
MagDipol phi setMinMax -180.000000 180.000000
MagDipol phi setValue -120.5
MagDipol b setMinMax 0.000000 25.000000
MagDipol b setValue 10.000000
MagDipol fire

create HxStreamSurf StreamSurface

MagDipol setIconPosition 20 10
MagDipol setViewerMask 16383

StreamSurface setIconPosition 160 10
StreamSurface setViewerMask 16383
StreamSurface data connect MagDipol
StreamSurface fire
StreamSurface colormap setDefaultColor 0.500000 0.500000 0.500000
StreamSurface colormap setDefaultAlpha 1.000000
StreamSurface colormap connect temperature.icol
StreamSurface fire
StreamSurface origin setValue 0 0.103565
StreamSurface origin setValue 1 0.001838
StreamSurface origin setValue 2 0.666231
StreamSurface origin setImmediate 0
StreamSurface origin showDragger 0
StreamSurface fire
StreamSurface resolution setMinMax -0.750000 0.750000
StreamSurface resolution setValue 0.4
StreamSurface fire
StreamSurface length setValue 0 5
StreamSurface length setValue 1 50
StreamSurface length setValue 2 15
StreamSurface fire
StreamSurface doLineSet 0

MagDipol select
StreamSurface select
viewer 0 show

viewer 0 setCameraOrientation 0.564043 -0.0120251 -0.825658 4.30901
viewer 0 setCameraPosition -1.57623 1.56144 1.32901
viewer 0 setCameraFocalDistance 2.88392
