# Amira Script
remove -all

# Create viewers
viewer 0 show
viewer 0 setBackgroundMode 0
viewer 0 setBackgroundColor 0
viewer 0 setAutoRedraw 0

mainWindow show

set hideNewModules 1
[ load ${AMIRA_ROOT}/data/colormaps/volrenRed.col ] setLabel volrenRed.col
volrenRed.col setIconPosition 0 0
volrenRed.col fire
{volrenRed.col} setMinMax 0 1
{volrenRed.col} flags setValue 0
{volrenRed.col} shift setMinMax -1 1
{volrenRed.col} shift setValue 0
{volrenRed.col} scale setMinMax 0 1
{volrenRed.col} scale setValue 1
volrenRed.col fire
volrenRed.col setViewerMask 16383

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/align/leaf.info ] setLabel leaf.info
leaf.info setIconPosition 20 10
leaf.info fire
leaf.info setViewerMask 16383
leaf.info parameters newBundle AlignTransform
leaf.info parameters AlignTransform setValue ImageSize 800 600
leaf.info parameters AlignTransform setValue slice0000 0 0 0 -1
leaf.info parameters AlignTransform setValue slice0001 -40.69 73.1736 97.7224 -1
leaf.info parameters AlignTransform setValue slice0002 44.022 -12.2787 153.514 -1
leaf.info parameters AlignTransform setValue slice0003 109.466 32.6953 135.682 -1
leaf.info parameters AlignTransform setValue slice0004 -85.2571 32.8652 206.22 1
leaf.info parameters AlignTransform setValue slice0005 -84.4074 74.4936 210.754 -1
leaf.info parameters AlignTransform setValue slice0006 109.872 83.4174 53.1852 -1
leaf.info parameters AlignTransform setValue slice0007 71.0326 95.9241 148.713 -1
leaf.info parameters AlignTransform setValue slice0008 123.033 58.1027 0.508362 -1
leaf.info parameters AlignTransform setValue slice0009 133.493 112.963 -22.2534 -1

set hideNewModules 0
create HxAlignSlices {AlignSlices}
AlignSlices setIconPosition 160 10
AlignSlices data connect leaf.info
AlignSlices fire
{AlignSlices} linearRange setValue 0 0
{AlignSlices} linearRange setValue 1 255
{AlignSlices} action setIndex -1
{AlignSlices} action untouch
AlignSlices fire
AlignSlices setViewerMask 16383
AlignSlices select
# AlignSlices edit
AlignSlices action hit 1
AlignSlices fire

#leaf.align crop 123 634 37 548 0 9
leaf.align alphaAverage 185 0

set hideNewModules 0
create HxArithmetic {Arithmetic}
Arithmetic setIconPosition 168 75
Arithmetic inputA connect leaf.align
Arithmetic fire
Arithmetic resultChannels setValue 0 0
Arithmetic expr0 setState Ar
Arithmetic expr1 setState Ag
Arithmetic expr2 setState Ab
Arithmetic expr3 setState {Aa*(Ar || Ag || Ab)}
Arithmetic expr4 setState 0
Arithmetic expr5 setState 0
Arithmetic resultType setValue 0
Arithmetic resolution setMinMax 0 1 1024
Arithmetic resolution setValue 0 64
Arithmetic resolution setMinMax 1 1 1024
Arithmetic resolution setValue 1 64
Arithmetic resolution setMinMax 2 1 1024
Arithmetic resolution setValue 2 64
Arithmetic minBox setMinMax 0 -1.00000001384843e+24 1.00000001384843e+24
Arithmetic minBox setValue 0 -1
Arithmetic minBox setMinMax 1 -1.00000001384843e+24 1.00000001384843e+24
Arithmetic minBox setValue 1 -1
Arithmetic minBox setMinMax 2 -1.00000001384843e+24 1.00000001384843e+24
Arithmetic minBox setValue 2 -1
Arithmetic maxBox setMinMax 0 -1.00000001384843e+24 1.00000001384843e+24
Arithmetic maxBox setValue 0 1
Arithmetic maxBox setMinMax 1 -1.00000001384843e+24 1.00000001384843e+24
Arithmetic maxBox setValue 1 1
Arithmetic maxBox setMinMax 2 -1.00000001384843e+24 1.00000001384843e+24
Arithmetic maxBox setValue 2 1
Arithmetic fire
Arithmetic setViewerMask 16383

set hideNewModules 0
[ {Arithmetic} create
 ] setLabel {leaf.align.transbg}
leaf.align.transbg setIconPosition 22 110
leaf.align.transbg master connect Arithmetic
leaf.align.transbg fire
leaf.align.transbg fire
leaf.align.transbg setViewerMask 16383

create HxVoltex {Voltex}
Voltex setIconPosition 207 110
Voltex data connect leaf.align.transbg
{Voltex} colormap setDefaultColor 1 0.8 0.5
{Voltex} colormap setDefaultAlpha 0.500000
Voltex colormap connect volrenRed.col
Voltex fire
{Voltex} mode setValue 1
{Voltex} range setValue 0 0
{Voltex} range setValue 1 255
{Voltex} lookup setValue 2
{Voltex} gamma setMinMax 1 8
{Voltex} gamma setValue 3
{Voltex} alphaScale setMinMax 0 1
{Voltex} alphaScale setValue 1
{Voltex} slices setMinMax 0 256
{Voltex} slices setValue 200
{Voltex} downsample setValue 0 2
{Voltex} downsample setValue 1 2
{Voltex} downsample setValue 2 1
{Voltex} doIt setIndex -1
{Voltex} doIt untouch
Voltex fire
Voltex setViewerMask 16383
Voltex select
Voltex doIt hit
Voltex fire

set hideNewModules 0

viewer 0 setCameraPosition 628.435 464.273 -1114
viewer 0 setCameraOrientation 0.954069 -0.291948 0.0672168 3.32067
viewer 0 setCameraFocalDistance 1207.13
viewer 0 setAutoRedraw 1
viewer 0 redraw

