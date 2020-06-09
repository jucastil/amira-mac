# Amira Script
remove -all
remove tetragrid.am velocity.am velocity.mag DisplayISL GridVolume Magnitude

# Create viewers
viewer setVertical 0

viewer 0 setBackgroundMode 1
viewer 0 setBackgroundColor 0.06 0.13 0.24
viewer 0 setBackgroundColor2 0.72 0.72 0.78
viewer 0 setTransparencyType 5
viewer 0 setAutoRedraw 0
viewer 0 show
mainWindow show

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/aneurysm/tetragrid.am ] setLabel tetragrid.am
tetragrid.am setIconPosition 20 38
tetragrid.am fire
tetragrid.am fire
tetragrid.am setViewerMask 65535

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/aneurysm/velocity.am ] setLabel velocity.am
velocity.am setIconPosition 20 66
velocity.am grid connect tetragrid.am
velocity.am fire
velocity.am fire
velocity.am setViewerMask 65535

set hideNewModules 0
create HxDisplayISL {DisplayISL}
DisplayISL setIconPosition 333 66
DisplayISL data connect velocity.am
DisplayISL colormap setDefaultColor 1 1 1
DisplayISL colormap setDefaultAlpha 0.500000
DisplayISL fire
DisplayISL numLines setMinMax 0 500
DisplayISL numLines setButtons 0
DisplayISL numLines setIncrement 33.3333
DisplayISL numLines setValue 75
DisplayISL numLines setSubMinMax 0 500
DisplayISL length setMinMax 1 250
DisplayISL length setButtons 0
DisplayISL length setIncrement 16.6
DisplayISL length setValue 250
DisplayISL length setSubMinMax 1 250
DisplayISL opacity setMinMax 0 1
DisplayISL opacity setButtons 0
DisplayISL opacity setIncrement 0.1
DisplayISL opacity setValue 1
DisplayISL opacity setSubMinMax 0 1
DisplayISL fadeFactor setMinMax 0.899999976158142 1
DisplayISL fadeFactor setButtons 0
DisplayISL fadeFactor setIncrement 0.00666667
DisplayISL fadeFactor setValue 0.9
DisplayISL fadeFactor setSubMinMax 0.899999976158142 1
DisplayISL stepSize setMinMax 0 0.00800000037997961
DisplayISL stepSize setButtons 0
DisplayISL stepSize setIncrement 0.000533333
DisplayISL stepSize setValue 0.005
DisplayISL stepSize setSubMinMax 0 0.00800000037997961
DisplayISL seed setValue 1
DisplayISL alphaRange setMinMax 0 -1.00000002004088e+020 1.00000002004088e+020
DisplayISL alphaRange setValue 0 -0.200000002980232
DisplayISL alphaRange setMinMax 1 -1.00000002004088e+020 1.00000002004088e+020
DisplayISL alphaRange setValue 1 0.5
DisplayISL aniTime setMinMax 0 100000
DisplayISL aniTime setButtons 0
DisplayISL aniTime setIncrement 6666.67
DisplayISL aniTime setValue 5000
DisplayISL aniTime setSubMinMax 0 100000
DisplayISL options setValue 0 0
DisplayISL options setValue 1 1
DisplayISL options setValue 2 0
DisplayISL box setValue 2
DisplayISL distResolution setMinMax 0 2 1000
DisplayISL distResolution setValue 0 32
DisplayISL distResolution setMinMax 1 2 1000
DisplayISL distResolution setValue 1 32
DisplayISL distResolution setMinMax 2 2 1000
DisplayISL distResolution setValue 2 32
DisplayISL distribute setOptValue 0 0
{DisplayISL} setLineWidth 1.000000
{DisplayISL} setLineSmooth 1
{DisplayISL} setBalance 0
{DisplayISL} setBoxType 0
{DisplayISL} setBoxTranslation -0.171839 1.89897 26.2252
{DisplayISL} setBoxScale 0.0831661 0.0831662 0.0831661
{DisplayISL} fire
{DisplayISL} doIt hit
DisplayISL fire
DisplayISL setViewerMask 65535
DisplayISL select
DisplayISL setShadowStyle 0

set hideNewModules 0
create HxGridVolume {GridVolume}
GridVolume setIconPosition 331 38
{GridVolume} data connect {tetragrid.am}
{GridVolume} fire
GridVolume data connect tetragrid.am
GridVolume colormap setDefaultColor 1 0.1 0.1
GridVolume colormap setDefaultAlpha 0.500000
GridVolume fire
GridVolume drawStyle setValue 4
GridVolume fire
GridVolume drawStyle setSpecularLighting 1
GridVolume drawStyle setTexture 0
GridVolume drawStyle setAlphaMode 3
GridVolume drawStyle setNormalBinding 0
GridVolume drawStyle setCullingMode 1
GridVolume drawStyle setSortingMode 1
GridVolume textureWrap setIndex 0 1
GridVolume materials setIndex 0 0
GridVolume colorMode setValue 2
GridVolume VRMode setValue 0
{GridVolume} fire
#{GridVolume} buffer setIndex 3
{GridVolume} selectTetra zab HIJMONMBDBABAAAAAIMACAONBPHKMGPAABAKAAAAAAAAAAAAAAAAAAAAAAAAPIDCFLAHNFGNLBBN
{GridVolume} setSelectAllNew 0
GridVolume fire
GridVolume setViewerMask 65535
GridVolume select
GridVolume setShadowStyle 0

set hideNewModules 0
create HxMagnitude {Magnitude}
Magnitude setIconPosition 160 66
Magnitude data connect velocity.am
Magnitude fire
Magnitude mode setValue 0
Magnitude doIt snap 0 1
Magnitude fire
Magnitude setViewerMask 65535

set hideNewModules 0
[ {Magnitude} doIt hit; {Magnitude} fire; {Magnitude} getResult
 ] setLabel {velocity.mag}
velocity.mag setIconPosition 20 94
velocity.mag master connect Magnitude
velocity.mag grid connect tetragrid.am
velocity.mag fire
velocity.mag fire
velocity.mag setViewerMask 65535

set hideNewModules 0


viewer 0 setCameraOrientation 0.963773 -0.217834 0.153914 2.40698
viewer 0 setCameraPosition -0.0523784 -0.60493 24.7987
viewer 0 setCameraFocalDistance 3.01078
viewer 0 setCameraNearDistance 1.3806
viewer 0 setCameraFarDistance 4.43793
viewer 0 setCameraType perspective
viewer 0 setCameraHeightAngle 44.9023
viewer 0 setAutoRedraw 1
viewer 0 redraw
