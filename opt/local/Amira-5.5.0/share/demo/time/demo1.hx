# Amira Script
remove -all
remove glow.col DisplayTime TimeSeriesControl OrthoSlice pvcca1.0013.jpeg

# Create viewers
viewer 0 show
viewer 0 setBackgroundMode 1
viewer 0 setTransparencyType 6
viewer 0 setAutoRedraw 0

mainWindow show

set hideNewModules 1
[ load ${AMIRA_ROOT}/data/colormaps/glow.col ] setLabel glow.col
glow.col setIconPosition 0 0
glow.col fire
{glow.col} setMinMax 0 255
{glow.col} flags setValue 0
{glow.col} shift setMinMax -1 1
{glow.col} shift setValue 0
{glow.col} scale setMinMax 0 1
{glow.col} scale setValue 1
glow.col fire
glow.col setViewerMask 16383

set hideNewModules 0
create HxDynamicFileSeriesCtrl {TimeSeriesControl}
TimeSeriesControl setIconPosition 23 47
{TimeSeriesControl} cachedSteps setMinMax 0 0 48
{TimeSeriesControl} cachedSteps setValue 0 48
TimeSeriesControl time setMinMax 0 47
TimeSeriesControl time setSubMinMax 0 47
TimeSeriesControl time setValue 12
TimeSeriesControl time setDiscrete 1
TimeSeriesControl time setIncrement 1
TimeSeriesControl init -loadCmd {load -jpg +box 0 511 0 511 0 1 +mode 2 "$FILENAME"} \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0001.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0002.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0003.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0004.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0005.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0006.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0007.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0008.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0009.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0010.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0011.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0012.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0013.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0014.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0015.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0016.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0017.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0018.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0019.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0020.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0021.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0022.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0023.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0024.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0025.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0026.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0027.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0028.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0029.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0030.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0031.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0032.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0033.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0034.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0035.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0036.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0037.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0038.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0039.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0040.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0041.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0042.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0043.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0044.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0045.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0046.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0047.jpeg" \
"${AMIRA_ROOT}/data/multichannel/channel1/pvcca1.0048.jpeg"
TimeSeriesControl fire
TimeSeriesControl setViewerMask 16383
TimeSeriesControl select

set hideNewModules 0
[ TimeSeriesControl getResult 0
 ] setLabel {pvcca1.0013.jpeg}
pvcca1.0013.jpeg setIconPosition 25 82
pvcca1.0013.jpeg master connect TimeSeriesControl
pvcca1.0013.jpeg fire
pvcca1.0013.jpeg fire
pvcca1.0013.jpeg setViewerMask 16383

set hideNewModules 0
create HxDisplayValue {DisplayTime}
DisplayTime setIconPosition 250 47
DisplayTime Time connect TimeSeriesControl
DisplayTime fire
{DisplayTime} options setValue 0
{DisplayTime} options2 setValue 0 0
{DisplayTime} options2 setValue 1 0
{DisplayTime} options2 setValue 2 0
{DisplayTime} options2 setValue 3 1
{DisplayTime} options2 setValue 4 0
{DisplayTime} value setMinMax 0 -1e+24 1e+24
{DisplayTime} value setValue 0 0
{DisplayTime} position setMinMax 0 -2000 2000
{DisplayTime} position setValue 0 30
{DisplayTime} position setMinMax 1 -2000 2000
{DisplayTime} position setValue 1 -20
{DisplayTime} size setMinMax 0 0 600
{DisplayTime} size setValue 0 180
{DisplayTime} size setMinMax 1 0 1
{DisplayTime} size setValue 1 0.1
{DisplayTime} color setColor 0 1 1 1
{DisplayTime} color setColor 1 0.866 0.624 0.096
{DisplayTime} color setColor 2 0.023 0.229 0.57
{DisplayTime} color setColor 3 1 1 1
{DisplayTime} labels setValue "<unset>"
{DisplayTime} format setValue "Image %g"
{DisplayTime} setFontSize 28
{DisplayTime} setMinMaxFormat %g
{DisplayTime} useAnimationMinMax 0
DisplayTime fire
DisplayTime setViewerMask 16383

set hideNewModules 0
create HxOrthoSlice {OrthoSlice}
OrthoSlice setIconPosition 267 82
OrthoSlice data connect pvcca1.0013.jpeg
{OrthoSlice} fire
{OrthoSlice} sliceOrientation setValue 0
{OrthoSlice} fire
{OrthoSlice} options setValue 0 1
{OrthoSlice} options setValue 1 0
{OrthoSlice} options setValue 2 0
{OrthoSlice} mappingType setValue 0
{OrthoSlice} linearRange setMinMax 0 -1e+24 1e+24
{OrthoSlice} linearRange setValue 0 0
{OrthoSlice} linearRange setMinMax 1 -1e+24 1e+24
{OrthoSlice} linearRange setValue 1 230
{OrthoSlice} contrastLimit setMinMax 0 -1e+24 1e+24
{OrthoSlice} contrastLimit setValue 0 7
{OrthoSlice} colormap setDefaultColor 1 0.8 0.5
{OrthoSlice} colormap setDefaultAlpha 1.000000
OrthoSlice colormap connect glow.col
{OrthoSlice} sliceNumber setMinMax 0 0
{OrthoSlice} sliceNumber setValue 0
{OrthoSlice} transparency setValue 0
OrthoSlice setFrameWidth 0
OrthoSlice setFrameColor 1 0.5 0
OrthoSlice frame 1
OrthoSlice fire

OrthoSlice fire
OrthoSlice setViewerMask 16383

set hideNewModules 0

viewer 0 setCameraPosition 255.5 255.5 -845.916
viewer 0 setCameraOrientation 1 0 0 3.14159
viewer 0 setCameraFocalDistance 845.916
viewer 0 setAutoRedraw 1
viewer 0 redraw
