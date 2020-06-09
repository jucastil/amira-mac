# Amira Script
remove -all
remove MultiChannelField channel1.info channel2.info BoundingBox OrthoSlice ObliqueSlice

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
create HxOrthoSlice {OrthoSlice}
OrthoSlice setIconPosition 325 53
OrthoSlice data connect MultiChannelField
{OrthoSlice} fire
{OrthoSlice} sliceOrientation setValue 0
{OrthoSlice} fire
{OrthoSlice} options setValue 0 1
{OrthoSlice} options setValue 1 0
{OrthoSlice} options setValue 2 1
{OrthoSlice} mappingType setValue 0
{OrthoSlice} linearRange setMinMax 0 -1e+024 1e+024
{OrthoSlice} linearRange setValue 0 -200
{OrthoSlice} linearRange setMinMax 1 -1e+024 1e+024
{OrthoSlice} linearRange setValue 1 200
{OrthoSlice} contrastLimit setMinMax 0 -1e+024 1e+024
{OrthoSlice} contrastLimit setValue 0 7
{OrthoSlice} colormap setDefaultColor 1 0.8 0.5
{OrthoSlice} colormap setDefaultAlpha 1.000000
{OrthoSlice} sliceNumber setMinMax 0 46
{OrthoSlice} sliceNumber setValue 32
{OrthoSlice} transparency setValue 0
{OrthoSlice} channels setValue 0 1
{OrthoSlice} channels setValue 1 1
OrthoSlice setFrameWidth 0
OrthoSlice setFrameColor 1 0.5 0
OrthoSlice frame 1
OrthoSlice fire

OrthoSlice fire
OrthoSlice setViewerMask 16383

set hideNewModules 0
create HxObliqueSlice {ObliqueSlice}
ObliqueSlice setIconPosition 315 80
ObliqueSlice data connect MultiChannelField
{ObliqueSlice} fire
ObliqueSlice data connect MultiChannelField
{ObliqueSlice} colormap setDefaultColor 1 0.8 0.5
{ObliqueSlice} colormap setDefaultAlpha 0.500000
ObliqueSlice fire
{ObliqueSlice} orientation setIndex -1
{ObliqueSlice} orientation untouch
{ObliqueSlice} options setValue 0 0
{ObliqueSlice} options setValue 1 0
{ObliqueSlice} options setValue 2 0
{ObliqueSlice} translate setMinMax 0 511
{ObliqueSlice} translate setValue 276
{ObliqueSlice} mappingType setValue 0
{ObliqueSlice} linearRange setMinMax 0 -1e+024 1e+024
{ObliqueSlice} linearRange setValue 0 -200
{ObliqueSlice} linearRange setMinMax 1 -1e+024 1e+024
{ObliqueSlice} linearRange setValue 1 200
{ObliqueSlice} contrastLimit setMinMax 0 0 99
{ObliqueSlice} contrastLimit setValue 0 7
{ObliqueSlice} sampling setValue 0 1
{ObliqueSlice} sampling setValue 1 0
{ObliqueSlice} sampling setValue 2 0
{ObliqueSlice} overlayType setValue 0
{ObliqueSlice} transparency setValue 0
ObliqueSlice channels setValue 0 1
ObliqueSlice channels setValue 1 1
{ObliqueSlice} orientation untouch
{ObliqueSlice} setPlane 174.093 210.699 73.0749 -0.731769 -0.681487 0.00941522 0.0068357 0.00647503 0.999956
ObliqueSlice fire
ObliqueSlice setViewerMask 16383
ObliqueSlice select

set hideNewModules 0

viewer 0 setCameraPosition 608.482 89.7802 -266.57
viewer 0 setCameraOrientation 0.4855 -0.811164 0.326041 3.61596
viewer 0 setCameraFocalDistance 548.575
viewer 0 setAutoRedraw 1
viewer 0 redraw
