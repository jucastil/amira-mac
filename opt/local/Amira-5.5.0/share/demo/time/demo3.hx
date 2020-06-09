# Amira Script
remove -all
remove Time r_000002.am r_000004.am r_000006.am r_000008.am r_000010.am Arithmetic Result Isosurface DisplayTime r_cluster.iv IvDisplay Interpol.scro

# Create viewers
viewer 0 show
viewer 0 setBackgroundMode 1
viewer 0 setAutoRedraw 0

mainWindow show

set hideNewModules 0
create HxScriptObject {Interpol.scro}
{Interpol.scro} script setValue ${AMIRA_ROOT}/share/demo/time/Interpol.scro
Interpol.scro setIconPosition 128 10
Interpol.scro fire
Interpol.scro setViewerMask 16383
Interpol.scro select

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/misc/r_000002.am ] setLabel r_000002.am
r_000002.am setIconPosition 19 42
r_000002.am fire
r_000002.am setViewerMask 16383

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/misc/r_000004.am ] setLabel r_000004.am
r_000004.am setIconPosition 19 73
r_000004.am fire
r_000004.am setViewerMask 16383

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/misc/r_000006.am ] setLabel r_000006.am
r_000006.am setIconPosition 19 103
r_000006.am fire
r_000006.am setViewerMask 16383

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/misc/r_000007.am ] setLabel r_000008.am
r_000008.am setIconPosition 19 133
r_000008.am fire
r_000008.am setViewerMask 16383

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/misc/r_000008.am ] setLabel r_000010.am
r_000010.am setIconPosition 19 163
r_000010.am fire
r_000010.am setViewerMask 16383

set hideNewModules 0
create HxArithmetic {Arithmetic}
Arithmetic setIconPosition 160 42
Arithmetic inputA connect r_000002.am
Arithmetic inputB connect r_000004.am
Arithmetic fire
{Arithmetic} expr setValue "A+0*(B-A)"
{Arithmetic} resultType setValue 0
{Arithmetic} minBox setValue 0 -1
{Arithmetic} minBox setValue 1 -1
{Arithmetic} minBox setValue 2 -1
{Arithmetic} maxBox setValue 0 1
{Arithmetic} maxBox setValue 1 1
{Arithmetic} maxBox setValue 2 1
{Arithmetic} doIt setIndex -1
{Arithmetic} doIt untouch
Arithmetic fire
Arithmetic setViewerMask 16383

set hideNewModules 0
[ {Arithmetic} create
 ] setLabel {Result}
Result setIconPosition 247 42
Result master connect Arithmetic
Result fire
Result setViewerMask 16383

set hideNewModules 0
create HxIsosurface {Isosurface}
Isosurface setIconPosition 235 79
Isosurface data connect Result
{Isosurface} colormap setDefaultColor 0.3 0.3 1
{Isosurface} colormap setDefaultAlpha 0.07
Isosurface fire
{Isosurface} drawStyle setValue 4
{Isosurface} buffer setIndex -1
{Isosurface} buffer untouch
{Isosurface} threshold setMinMax 0 255
{Isosurface} threshold setValue 76
{Isosurface} options setValue 0 0
{Isosurface} options setValue 1 0
{Isosurface} doIt setIndex -1
{Isosurface} doIt untouch
Isosurface fire
Isosurface setViewerMask 16383

set hideNewModules 0
create HxDisplayValue {DisplayTime}
DisplayTime setIconPosition 245 10
DisplayTime Time connect Interpol.scro
DisplayTime fire
{DisplayTime} options setValue 2
{DisplayTime} options2 setValue 0 1
{DisplayTime} options2 setValue 1 1
{DisplayTime} options2 setValue 2 1
{DisplayTime} options2 setValue 3 1
{DisplayTime} options2 setValue 4 0
{DisplayTime} value setValue 0 0
{DisplayTime} position setValue 0 30
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
[ load ${AMIRA_ROOT}/data/misc/r_cluster.iv ] setLabel r_cluster.iv
r_cluster.iv setIconPosition 20 220
r_cluster.iv fire
r_cluster.iv fire
r_cluster.iv setViewerMask 16383

{Isosurface} doIt snap 1
{Isosurface} fire

set hideNewModules 0
create HxIvDisplay {IvDisplay}
IvDisplay setIconPosition 275 220
IvDisplay data connect r_cluster.iv
IvDisplay fire
{IvDisplay} drawStyle setValue 0
IvDisplay fire
IvDisplay setViewerMask 16383

set hideNewModules 0

viewer 0 setCameraPosition -16.1311 -2.85971 -40.6586
viewer 0 setCameraOrientation 0.981919 0.0207368 -0.188165 3.08306
viewer 0 setCameraFocalDistance 43.835
viewer 0 setAutoRedraw 1
viewer 0 redraw

