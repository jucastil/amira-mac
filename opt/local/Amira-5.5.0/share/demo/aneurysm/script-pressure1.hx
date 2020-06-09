# Amira Script
remove -all
remove physics-trans.icol tetragrid.am dynamic-pressure.am GridVolume

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
[ load ${AMIRA_ROOT}/data/aneurysm/physics-trans.icol ] setLabel physics-trans.icol
physics-trans.icol setIconPosition 19 10
physics-trans.icol fire
{physics-trans.icol} setMinMax 0 20
physics-trans.icol flags setValue 0
physics-trans.icol shift setMinMax -1 1
physics-trans.icol shift setButtons 0
physics-trans.icol shift setIncrement 0.133333
physics-trans.icol shift setValue 0
physics-trans.icol shift setSubMinMax -1 1
physics-trans.icol scale setMinMax 0 1
physics-trans.icol scale setButtons 0
physics-trans.icol scale setIncrement 0.1
physics-trans.icol scale setValue 1
physics-trans.icol scale setSubMinMax 0 1
physics-trans.icol fire
physics-trans.icol setViewerMask 65535

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/aneurysm/tetragrid.am ] setLabel tetragrid.am
tetragrid.am setIconPosition 20 38
tetragrid.am fire
tetragrid.am fire
tetragrid.am setViewerMask 65535

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/aneurysm/dynamic-pressure.am ] setLabel dynamic-pressure.am
dynamic-pressure.am setIconPosition 18 69
dynamic-pressure.am grid connect tetragrid.am
dynamic-pressure.am fire
dynamic-pressure.am fire
dynamic-pressure.am setViewerMask 65535

set hideNewModules 0
create HxGridVolume {GridVolume}
GridVolume setIconPosition 331 39
{GridVolume} data connect {tetragrid.am}
{GridVolume} fire
GridVolume data connect tetragrid.am
GridVolume colorField connect dynamic-pressure.am
GridVolume colormap setDefaultColor 1 0.1 0.1
GridVolume colormap setDefaultAlpha 0.500000
GridVolume colormap connect physics-trans.icol
GridVolume fire
GridVolume drawStyle setValue 1
GridVolume fire
GridVolume drawStyle setSpecularLighting 1
GridVolume drawStyle setTexture 1
GridVolume drawStyle setAlphaMode 1
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
GridVolume setShadowStyle 0

set hideNewModules 0


viewer 0 setCameraOrientation 0.947874 -0.308912 0.0781604 2.2756
viewer 0 setCameraPosition -1.05276 -1.10691 24.3433
viewer 0 setCameraFocalDistance 3.64302
viewer 0 setCameraNearDistance 2.02144
viewer 0 setCameraFarDistance 5.05132
viewer 0 setCameraType perspective
viewer 0 setCameraHeightAngle 44.9023
viewer 0 setAutoRedraw 1
viewer 0 redraw
