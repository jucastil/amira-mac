# Amira Script
remove -all
remove DisplayTime r_cluster.iv IvDisplay TimeSeriesControl r_000007.am Isosurface

# Create viewers
viewer 0 show
viewer 0 setBackgroundMode 1
viewer 0 setTransparencyType 6
viewer 0 setAutoRedraw 0

mainWindow show

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/misc/r_cluster.iv ] setLabel r_cluster.iv
r_cluster.iv setIconPosition 24 169
r_cluster.iv fire
r_cluster.iv fire
r_cluster.iv setViewerMask 16383

set hideNewModules 0
create HxIvDisplay {IvDisplay}
IvDisplay setIconPosition 259 169
IvDisplay data connect r_cluster.iv
IvDisplay fire
{IvDisplay} drawStyle setValue 0
IvDisplay fire
IvDisplay setViewerMask 16383

set hideNewModules 0
create HxDynamicFileSeriesCtrl {TimeSeriesControl}
TimeSeriesControl setIconPosition 21 44
{TimeSeriesControl} cachedSteps setMinMax 0 0 6
{TimeSeriesControl} cachedSteps setValue 0 6
TimeSeriesControl time setMinMax 0 5
TimeSeriesControl time setSubMinMax 0 5
TimeSeriesControl time setValue 4
TimeSeriesControl time setDiscrete 1
TimeSeriesControl time setIncrement 1
TimeSeriesControl init -loadCmd {load "$FILENAME"} \
"${AMIRA_ROOT}/data/misc/r_000000.am" \
"${AMIRA_ROOT}/data/misc/r_000002.am" \
"${AMIRA_ROOT}/data/misc/r_000004.am" \
"${AMIRA_ROOT}/data/misc/r_000006.am" \
"${AMIRA_ROOT}/data/misc/r_000007.am" \
"${AMIRA_ROOT}/data/misc/r_000008.am"
TimeSeriesControl fire
TimeSeriesControl setViewerMask 16383
TimeSeriesControl select

set hideNewModules 0
[ TimeSeriesControl getResult 0
 ] setLabel {r_000007.am}
r_000007.am setIconPosition 23 81
r_000007.am master connect TimeSeriesControl
r_000007.am fire
r_000007.am fire
r_000007.am setViewerMask 16383

set hideNewModules 0
create HxIsosurface {Isosurface}
Isosurface setIconPosition 248 81
Isosurface data connect r_000007.am
{Isosurface} colormap setDefaultColor 0.3 0.3 1
{Isosurface} colormap setDefaultAlpha 0.070000
Isosurface fire
{Isosurface} drawStyle setValue 4
{Isosurface} drawStyle setTexture 0
{Isosurface} drawStyle setNormalBinding 1
{Isosurface} buffer setIndex -1
{Isosurface} buffer untouch
{Isosurface} threshold setMinMax 0 255
{Isosurface} threshold setValue 75
{Isosurface} options setValue 0 0
{Isosurface} options setValue 1 0
{Isosurface} resolution setMinMax 0 -1e+24 1e+24
{Isosurface} resolution setValue 0 2
{Isosurface} resolution setMinMax 1 -1e+24 1e+24
{Isosurface} resolution setValue 1 2
{Isosurface} resolution setMinMax 2 -1e+24 1e+24
{Isosurface} resolution setValue 2 2
{Isosurface} doIt setIndex -1
{Isosurface} doIt untouch
{Isosurface} doIt snap 1
Isosurface fire
Isosurface setViewerMask 16383

set hideNewModules 0
create HxDisplayValue {DisplayTime}
DisplayTime setIconPosition 233 44
DisplayTime Time connect TimeSeriesControl
DisplayTime fire
{DisplayTime} options setValue 2
{DisplayTime} options2 setValue 0 1
{DisplayTime} options2 setValue 1 1
{DisplayTime} options2 setValue 2 1
{DisplayTime} options2 setValue 3 1
{DisplayTime} options2 setValue 4 0
{DisplayTime} value setMinMax 0 -1e+24 1e+24
{DisplayTime} value setValue 0 0
{DisplayTime} position setMinMax 0 -2000 2000
{DisplayTime} position setValue 0 30
{DisplayTime} position setMinMax 1 -2000 2000
{DisplayTime} position setValue 1 30
{DisplayTime} size setMinMax 0 0 600
{DisplayTime} size setValue 0 180
{DisplayTime} size setMinMax 1 0 1
{DisplayTime} size setValue 1 0.1
{DisplayTime} color setColor 0 1 1 1
{DisplayTime} color setColor 1 0.866 0.624 0.096
{DisplayTime} color setColor 2 0.023 0.229 0.57
{DisplayTime} color setColor 3 1 1 1
{DisplayTime} labels setValue "<unset>"
{DisplayTime} format setValue "%g"
{DisplayTime} setFontSize 14
{DisplayTime} setMinMaxFormat %g
{DisplayTime} useAnimationMinMax 0
DisplayTime fire
DisplayTime setViewerMask 16383

set hideNewModules 0

viewer 0 setCameraPosition 20.4903 1.38672 29.0443
viewer 0 setCameraOrientation -0.304342 0.00511106 -0.952549 2.98049
viewer 0 setCameraFocalDistance 35.5716
viewer 0 setAutoRedraw 1
viewer 0 redraw
