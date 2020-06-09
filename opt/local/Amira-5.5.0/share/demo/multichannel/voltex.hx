# Amira Script
remove -all
remove volrenRed.col MultiChannelField channel1.info channel2.info Voltex

# Create viewers
viewer 0 show
viewer 0 setBackgroundMode 1
viewer 0 setTransparencyType 6
viewer 0 setAutoRedraw 0

mainWindow show

set hideNewModules 1
[ load ${AMIRA_ROOT}/data/colormaps/volrenRed.col ] setLabel volrenRed.col
volrenRed.col setIconPosition 0 0
volrenRed.col fire
{volrenRed.col} setMinMax 10 180
{volrenRed.col} flags setValue 0
{volrenRed.col} shift setMinMax -1 1
{volrenRed.col} shift setValue 0
{volrenRed.col} scale setMinMax 0 1
{volrenRed.col} scale setValue 1
volrenRed.col fire
volrenRed.col setViewerMask 16383

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
create HxVoltex {Voltex}
Voltex setIconPosition 345 25
Voltex data connect MultiChannelField
{Voltex} colormap setDefaultColor 1 0.8 0.5
{Voltex} colormap setDefaultAlpha 0.500000
Voltex colormap connect volrenRed.col
Voltex fire
{Voltex} gamma setMinMax 1 8
{Voltex} gamma setValue 2.39007
{Voltex} slices setValue 256
{Voltex} alphaScale setMinMax 0 1
{Voltex} alphaScale setValue 1
{Voltex} downsample setValue 0 4
{Voltex} downsample setValue 1 4
{Voltex} downsample setValue 2 1
Voltex channels setValue 0 1
Voltex channels setValue 1 1
{Voltex} doIt setIndex -1
{Voltex} doIt untouch
Voltex fire
{Voltex} doIt hit
Voltex fire
Voltex setViewerMask 16383
Voltex select

set hideNewModules 0

viewer 0 setCameraPosition 217.175 217.175 -659.074
viewer 0 setCameraOrientation -0.707107 -0.707107 0 3.14159
viewer 0 setCameraFocalDistance 732.674
viewer 0 setAutoRedraw 1
viewer 0 redraw
