# Amira Script
remove -all
remove glow.col MultiChannelField channel1.info channel2.info ProjectionView

# Create viewers
viewer setVertical 0

viewer 0 setBackgroundMode 1
viewer 0 setBackgroundColor 0.06 0.13 0.24
viewer 0 setBackgroundColor2 0.72 0.72 0.78
viewer 0 setTransparencyType 6
viewer 0 setAutoRedraw 0
viewer 0 show
mainWindow show

set hideNewModules 1
[ load ${AMIRA_ROOT}/data/colormaps/glow.col ] setLabel glow.col
glow.col setIconPosition 0 0
glow.col setNoRemoveAll 1
glow.col fire
{glow.col} setMinMax 0 255
glow.col flags setValue 1
glow.col shift setMinMax -1 1
glow.col shift setButtons 0
glow.col shift setIncrement 0.133333
glow.col shift setValue 0
glow.col shift setSubMinMax -1 1
glow.col scale setMinMax 0 1
glow.col scale setButtons 0
glow.col scale setIncrement 0.1
glow.col scale setValue 1
glow.col scale setSubMinMax 0 1
glow.col fire
glow.col setViewerMask 16383

set hideNewModules 0
create HxMultiChannelField3 {MultiChannelField}
MultiChannelField setIconPosition 22 25

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/multichannel/channel1.info ] setLabel channel1.info
channel1.info setIconPosition 22 45
channel1.info master connect MultiChannelField
channel1.info fire
channel1.info setViewerMask 16383

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/multichannel/channel2.info ] setLabel channel2.info
channel2.info setIconPosition 22 64
channel2.info master connect MultiChannelField
channel2.info fire
channel2.info setViewerMask 16383
MultiChannelField channel1 setMinMax 0 255
MultiChannelField channel1 setColor 0 0 1
MultiChannelField colormap1 setDefaultColor 0 0 1
MultiChannelField colormap1 setDefaultAlpha 1.000000
MultiChannelField channel2 setMinMax 0 255
MultiChannelField channel2 setColor 0 1 0
MultiChannelField colormap2 setDefaultColor 0 1 0
MultiChannelField colormap2 setDefaultAlpha 1.000000
MultiChannelField channel3 setMinMax 0 255
MultiChannelField channel3 setColor 1 0 0
MultiChannelField colormap3 setDefaultColor 1 0 0
MultiChannelField colormap3 setDefaultAlpha 1.000000
MultiChannelField setModified 0
MultiChannelField fire
MultiChannelField setViewerMask 16383

set hideNewModules 0
create HxProjectionView {ProjectionView}
ProjectionView setIconPosition 271 25
ProjectionView data connect MultiChannelField
ProjectionView colormap setDefaultColor 1 0.8 0.5
ProjectionView colormap setDefaultAlpha 0.500000
ProjectionView colormap connect glow.col
ProjectionView fire
ProjectionView options setValue 0 1
ProjectionView options setToggleVisible 0 1
ProjectionView options setValue 1 0
ProjectionView options setToggleVisible 1 1
ProjectionView options setValue 2 0
ProjectionView options setToggleVisible 2 1
ProjectionView options setValue 3 0
ProjectionView options setToggleVisible 3 1
ProjectionView slices setValue 0 1
ProjectionView slices setToggleVisible 0 1
ProjectionView slices setValue 1 1
ProjectionView slices setToggleVisible 1 1
ProjectionView slices setValue 2 1
ProjectionView slices setToggleVisible 2 1
ProjectionView slices setValue 3 0
ProjectionView slices setToggleVisible 3 1
ProjectionView mapping setIndex 0 0
ProjectionView mapping setIndex 1 0
ProjectionView channels setValue 0 1
ProjectionView channels setToggleVisible 0 1
ProjectionView channels setValue 1 1
ProjectionView channels setToggleVisible 1 1
ProjectionView range setMinMax 0 -3.40282346638529e+038 3.40282346638529e+038
ProjectionView range setValue 0 0
ProjectionView range setMinMax 1 -3.40282346638529e+038 3.40282346638529e+038
ProjectionView range setValue 1 255
ProjectionView contrastLimit setMinMax 0 -2147483648 2147483648
ProjectionView contrastLimit setValue 0 7
ProjectionView minimum setMinMax 0 0 511
ProjectionView minimum setValue 0 0
ProjectionView minimum setMinMax 1 0 511
ProjectionView minimum setValue 1 0
ProjectionView minimum setMinMax 2 0 46
ProjectionView minimum setValue 2 0
ProjectionView maximum setMinMax 0 0 511
ProjectionView maximum setValue 0 511
ProjectionView maximum setMinMax 1 0 511
ProjectionView maximum setValue 1 511
ProjectionView maximum setMinMax 2 0 46
ProjectionView maximum setValue 2 46
ProjectionView update snap 0 1
ProjectionView fire
ProjectionView setViewerMask 16383
ProjectionView select
ProjectionView setPickable 1

set hideNewModules 0


viewer 0 setCameraOrientation 0.176146 0.510805 0.841458 2.56419
viewer 0 setCameraPosition 656.961 760.481 384.317
viewer 0 setCameraFocalDistance 762.475
viewer 0 setCameraNearDistance 458.412
viewer 0 setCameraFarDistance 1068.94
viewer 0 setCameraType perspective
viewer 0 setCameraHeightAngle 44.9023
viewer 0 setAutoRedraw 1
viewer 0 redraw

