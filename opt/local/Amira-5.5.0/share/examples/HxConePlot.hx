# Amira Script
remove -all
remove physics.icol wing.am wing.mag Result wing.iv ConePlot BoundingBox Magnitude Arithmetic SelectRoi IvDisplay

# Create viewers
viewer setVertical 0

viewer 0 setBackgroundMode 1
viewer 0 setBackgroundColor 0.06 0.13 0.24
viewer 0 setBackgroundColor2 0.72 0.72 0.78
viewer 0 setTransparencyType 5
viewer 0 setAutoRedraw 0
viewer 0 show
mainWindow show

set hideNewModules 1
[ load ${AMIRA_ROOT}/data/colormaps/physics.icol ] setLabel physics.icol
physics.icol setIconPosition 0 0
physics.icol fire
{physics.icol} setMinMax 0 13
physics.icol flags setValue 1
physics.icol shift setMinMax -1 1
physics.icol shift setButtons 0
physics.icol shift setIncrement 0.133333
physics.icol shift setValue 0
physics.icol shift setSubMinMax -1 1
physics.icol scale setMinMax 0 1
physics.icol scale setButtons 0
physics.icol scale setIncrement 0.1
physics.icol scale setValue 1
physics.icol scale setSubMinMax 0 1
physics.icol fire
physics.icol setViewerMask 32767

set hideNewModules 0
[ load "${AMIRA_ROOT}/data/tutorials/wing.am" ] setLabel wing.am
wing.am setIconPosition 20 11
wing.am fire
wing.am fire
wing.am setViewerMask 32767

set hideNewModules 0
[ load "${AMIRA_ROOT}/data/tutorials/wing.iv" ] setLabel wing.iv
wing.iv setIconPosition 20 110
wing.iv fire
wing.iv fire
wing.iv setViewerMask 32767

set hideNewModules 0
create HxBoundingBox {BoundingBox}
BoundingBox setIconPosition 324 11
{BoundingBox} setLineWidth 0
{BoundingBox} setColor 1 0.5 0
BoundingBox data connect wing.am
BoundingBox fire
BoundingBox text setValue 0 0
BoundingBox fire
BoundingBox setViewerMask 32767

set hideNewModules 0
create HxMagnitude {Magnitude}
Magnitude setIconPosition 160 11
Magnitude data connect wing.am
Magnitude fire
Magnitude mode setValue 0
Magnitude doIt snap 0 1
Magnitude fire
Magnitude setViewerMask 32767

set hideNewModules 0
[ Magnitude doIt hit; Magnitude compute; Magnitude getResult
 ] setLabel {wing.mag}
wing.mag setIconPosition 20 41
wing.mag master connect Magnitude
wing.mag fire
wing.mag fire
wing.mag setViewerMask 32767

set hideNewModules 0
create HxArithmetic {Arithmetic}
Arithmetic setIconPosition 209 79
Arithmetic inputA connect wing.mag
Arithmetic fire
Arithmetic resultChannels setValue 0 0
Arithmetic expr0 setState A<3
Arithmetic expr1 setState 0
Arithmetic expr2 setState 0
Arithmetic expr3 setState 0
Arithmetic expr4 setState 0
Arithmetic expr5 setState 0
Arithmetic resultType setValue 0
Arithmetic resolution setMinMax 0 1 1024
Arithmetic resolution setValue 0 64
Arithmetic resolution setMinMax 1 1 1024
Arithmetic resolution setValue 1 64
Arithmetic resolution setMinMax 2 1 1024
Arithmetic resolution setValue 2 64
Arithmetic minBox setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
Arithmetic minBox setValue 0 -1
Arithmetic minBox setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
Arithmetic minBox setValue 1 -1
Arithmetic minBox setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
Arithmetic minBox setValue 2 -1
Arithmetic maxBox setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
Arithmetic maxBox setValue 0 1
Arithmetic maxBox setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
Arithmetic maxBox setValue 1 1
Arithmetic maxBox setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
Arithmetic maxBox setValue 2 1
Arithmetic fire
Arithmetic setViewerMask 32767

set hideNewModules 0
[ {Arithmetic} create
 ] setLabel {Result}
Result setIconPosition 18 79
Result master connect Arithmetic
Result fire
Result fire
Result setViewerMask 32767

set hideNewModules 0
create HxSelectRoi {SelectRoi}
SelectRoi setIconPosition 48 150
SelectRoi data connect wing.am
SelectRoi fire
SelectRoi minimum setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
SelectRoi minimum setValue 0 -0.137195706367493
SelectRoi minimum setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
SelectRoi minimum setValue 1 -0.242669984698296
SelectRoi minimum setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
SelectRoi minimum setValue 2 0.0295275151729584
SelectRoi maximum setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
SelectRoi maximum setValue 0 1.0336582660675
SelectRoi maximum setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
SelectRoi maximum setValue 1 0.29021829366684
SelectRoi maximum setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
SelectRoi maximum setValue 2 0.697412729263306
SelectRoi options setValue 0 1
SelectRoi fire
SelectRoi setViewerMask 65534

set hideNewModules 0
create HxParticlePlot {ConePlot}
ConePlot setIconPosition 274 150
ConePlot data connect wing.am
ConePlot ROI connect SelectRoi
ConePlot distribution connect Result
ConePlot Colormap setDefaultColor 0.8 0.8 0.8
ConePlot Colormap setDefaultAlpha 0.500000
ConePlot Colormap connect physics.icol
ConePlot Animate setMinMax 0 149
ConePlot Animate setSubMinMax 0 149
ConePlot Animate setValue 59
ConePlot Animate setDiscrete 1
ConePlot Animate setIncrement 1
ConePlot fire
ConePlot distribute setOptValue 0 1
ConePlot Resolution setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
ConePlot Resolution setValue 0 30
ConePlot Resolution setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
ConePlot Resolution setValue 1 30
ConePlot Resolution setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
ConePlot Resolution setValue 2 30
ConePlot Options setMinMax 0 1 500
ConePlot Options setValue 0 100
ConePlot Options setMinMax 1 1 150
ConePlot Options setValue 1 1
ConePlot Options setMinMax 2 1 500
ConePlot Options setValue 2 150
ConePlot Options2 setMinMax 0 0 0.100000001490116
ConePlot Options2 setValue 0 0.00499999988824129
ConePlot Options2 setMinMax 1 9.99999974737875e-006 100
ConePlot Options2 setValue 1 0.0299999993294477
ConePlot Options2 setMinMax 2 9.99999974737875e-005 100
ConePlot Options2 setValue 2 0.00999999977648258
ConePlot threshold setState x>0
ConePlot setStepsToBlend 10
ConePlot fire
ConePlot setViewerMask 32767
ConePlot select
ConePlot DoIt touch
ConePlot DoIt hit
ConePlot fire

ConePlot Animate play -loop


set hideNewModules 0
create HxIvDisplay {IvDisplay}
IvDisplay setIconPosition 344 110
IvDisplay data connect wing.iv
IvDisplay fire
IvDisplay drawStyle setValue 0 0
IvDisplay fire
IvDisplay setViewerMask 32767

set hideNewModules 0


viewer 0 setCameraPosition 0.797073 -0.135818 0.929792
viewer 0 setCameraOrientation -0.199597 0.110762 -0.973598 3.16109
viewer 0 setCameraFocalDistance 0.638285
viewer 0 setAutoRedraw 1
viewer 0 redraw
