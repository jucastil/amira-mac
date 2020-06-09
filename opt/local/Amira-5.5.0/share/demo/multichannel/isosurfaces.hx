# Amira Script
remove -all
remove MultiChannelField channel1.info channel2.info Resample MultiChannelField2 channel1.Resampled channel2.Resampled Isosurface Isosurface2 BoundingBox

# Create viewers
viewer 0 show
viewer 0 setBackgroundMode 1
viewer 0 setTransparencyType 6
viewer 0 setAutoRedraw 0

mainWindow show

set hideNewModules 0
create HxMultiChannelField3 {MultiChannelField}
MultiChannelField setIconPosition 22 25
MultiChannelField setExpectedNumChannels 2
MultiChannelField fire
MultiChannelField setViewerMask 16383

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/multichannel/channel1.info ] setLabel channel1.info
channel1.info setIconPosition 22 43
channel1.info master connect MultiChannelField
channel1.info fire
channel1.info fire
channel1.info setViewerMask 16383

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/multichannel/channel2.info ] setLabel channel2.info
channel2.info setIconPosition 22 61
channel2.info master connect MultiChannelField
channel2.info fire
channel2.info fire
channel2.info setViewerMask 16383

set hideNewModules 0
create HxResample {Resample}
Resample setIconPosition 160 25
Resample data connect MultiChannelField
{Resample} fire
{Resample} filter setValue 1
{Resample} resolution setMinMax 0 1 10000
{Resample} resolution setValue 0 128
{Resample} resolution setMinMax 1 1 10000
{Resample} resolution setValue 1 128
{Resample} resolution setMinMax 2 1 10000
{Resample} resolution setValue 2 47
{Resample} average setMinMax 0 1 8
{Resample} average setValue 0 2
{Resample} average setMinMax 1 1 8
{Resample} average setValue 1 2
{Resample} average setMinMax 2 1 8
{Resample} average setValue 2 1
{Resample} action setIndex -1
{Resample} action untouch
Resample fire
{Resample} action hit
Resample fire
Resample setViewerMask 16383

set hideNewModules 0
create HxIsosurface {Isosurface}
Isosurface setIconPosition 325 107
Isosurface data connect channel1.Resampled
{Isosurface} colormap setDefaultColor 0.880282 0.0495934 0.0495934
{Isosurface} colormap setDefaultAlpha 1.000000
Isosurface fire
{Isosurface} drawStyle setValue 1
{Isosurface} drawStyle setTexture 0
{Isosurface} drawStyle setNormalBinding 1
{Isosurface} buffer setIndex -1
{Isosurface} buffer untouch
{Isosurface} threshold setMinMax 0 255
{Isosurface} threshold setValue 60
{Isosurface} options setValue 0 1
{Isosurface} options setValue 1 0
{Isosurface} resolution setMinMax 0 -1e+024 1e+024
{Isosurface} resolution setValue 0 2
{Isosurface} resolution setMinMax 1 -1e+024 1e+024
{Isosurface} resolution setValue 1 2
{Isosurface} resolution setMinMax 2 -1e+024 1e+024
{Isosurface} resolution setValue 2 2
{Isosurface} doIt setIndex -1
{Isosurface} doIt untouch
{Isosurface} doIt hit
Isosurface fire
Isosurface setViewerMask 16383
Isosurface select

set hideNewModules 0
create HxIsosurface {Isosurface2}
Isosurface2 setIconPosition 319 135
Isosurface2 data connect channel2.Resampled
{Isosurface2} colormap setDefaultColor 0.0782123 0.873239 0.0307479
{Isosurface2} colormap setDefaultAlpha 0.274648
Isosurface2 fire
{Isosurface2} drawStyle setValue 4
{Isosurface2} drawStyle setTexture 0
{Isosurface2} drawStyle setNormalBinding 1
{Isosurface2} buffer setIndex -1
{Isosurface2} buffer untouch
{Isosurface2} threshold setMinMax 1 255
{Isosurface2} threshold setValue 55
{Isosurface2} options setValue 0 1
{Isosurface2} options setValue 1 0
{Isosurface2} resolution setMinMax 0 -1e+024 1e+024
{Isosurface2} resolution setValue 0 2
{Isosurface2} resolution setMinMax 1 -1e+024 1e+024
{Isosurface2} resolution setValue 1 2
{Isosurface2} resolution setMinMax 2 -1e+024 1e+024
{Isosurface2} resolution setValue 2 2
{Isosurface2} doIt setIndex -1
{Isosurface2} doIt untouch
{Isosurface2} doIt hit
Isosurface2 fire
Isosurface2 setViewerMask 16383
Isosurface2 select

set hideNewModules 0
create HxBoundingBox {BoundingBox}
BoundingBox setIconPosition 311 25
{BoundingBox} setLineWidth 0
{BoundingBox} setColor 1 0.5 0
BoundingBox data connect MultiChannelField
BoundingBox fire
{BoundingBox} text setValue 0 0
BoundingBox fire
BoundingBox setViewerMask 16383

set hideNewModules 0


viewer 0 setCameraPosition 521.514 15.9386 -373.5
viewer 0 setCameraOrientation 0.415004 -0.863831 0.285601 3.44017
viewer 0 setCameraFocalDistance 574.64
viewer 0 setAutoRedraw 1
viewer 0 redraw
