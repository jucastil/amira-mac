# Amira Script
remove -all
remove temperature.icol tetragrid.am velocity.am BoundingBox GridBoundary PlanarLIC

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
[ load ${AMIRA_ROOT}/data/colormaps/temperature.icol ] setLabel temperature.icol
temperature.icol setIconPosition 0 0
temperature.icol setNoRemoveAll 1
temperature.icol fire
{temperature.icol} setMinMax 0 0.5
temperature.icol flags setValue 0
temperature.icol shift setMinMax -1 1
temperature.icol shift setButtons 0
temperature.icol shift setIncrement 0.133333
temperature.icol shift setValue 0
temperature.icol shift setSubMinMax -1 1
temperature.icol scale setMinMax 0 1
temperature.icol scale setButtons 0
temperature.icol scale setIncrement 0.1
temperature.icol scale setValue 1
temperature.icol scale setSubMinMax 0 1
temperature.icol fire
temperature.icol setViewerMask 65535

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
create HxBoundingBox {BoundingBox}
BoundingBox setIconPosition 323 10
{BoundingBox} setLineWidth 0
{BoundingBox} setColor 1 0.5 0
BoundingBox data connect tetragrid.am
BoundingBox fire
BoundingBox text setValue 0 0
BoundingBox fire
BoundingBox setViewerMask 65535
BoundingBox setShadowStyle 0

set hideNewModules 0
create HxGridBoundary {GridBoundary}
GridBoundary setIconPosition 321 38
{GridBoundary} data connect {tetragrid.am}
{GridBoundary} fire
GridBoundary data connect tetragrid.am
GridBoundary colormap setDefaultColor 1 0.1 0.1
GridBoundary colormap setDefaultAlpha 0.500000
GridBoundary fire
GridBoundary drawStyle setValue 1
GridBoundary fire
GridBoundary drawStyle setSpecularLighting 1
GridBoundary drawStyle setTexture 0
GridBoundary drawStyle setAlphaMode 1
GridBoundary drawStyle setNormalBinding 0
GridBoundary drawStyle setCullingMode 0
GridBoundary drawStyle setSortingMode 1
GridBoundary textureWrap setIndex 0 1
GridBoundary materials setIndex 0 1
GridBoundary materials setIndex 1 0
GridBoundary colorMode setValue 0
{GridBoundary} fire
{GridBoundary} buffer setIndex 3
{GridBoundary} selectTriangles zab HIJMPLPPHPBEIMICFBDAAKEGMBCIBIAFKDGABEAMHGGAAPMEAAIFMKKOBA
{GridBoundary} setSelectAllNew 0
GridBoundary fire
GridBoundary setViewerMask 65535
GridBoundary setShadowStyle 0

set hideNewModules 0
create HxFastLIC {PlanarLIC}
PlanarLIC setIconPosition 339 66
PlanarLIC data connect velocity.am
PlanarLIC colormap setDefaultColor 1 0 0
PlanarLIC colormap setDefaultAlpha 0.500000
PlanarLIC colormap connect temperature.icol
PlanarLIC colormap2 setDefaultColor 1 0 0
PlanarLIC colormap2 setDefaultAlpha 0.500000
PlanarLIC fire
PlanarLIC options setValue 0 0
PlanarLIC options setValue 1 0
PlanarLIC options setValue 2 0
PlanarLIC translate setMinMax 0 100
PlanarLIC translate setButtons 1
PlanarLIC translate setIncrement 1
PlanarLIC translate setValue 49.4786
PlanarLIC translate setSubMinMax 0 100
PlanarLIC colorMode setIndex 0 1
PlanarLIC lic setMinMax 0 0 2000
PlanarLIC lic setValue 0 40
PlanarLIC lic setMinMax 1 20 1024
PlanarLIC lic setValue 1 320
PlanarLIC lic setMinMax 2 0 2147483648
PlanarLIC lic setValue 2 0
PlanarLIC phase setMinMax 0 360
PlanarLIC phase setButtons 0
PlanarLIC phase setIncrement 24
PlanarLIC phase setValue 0
PlanarLIC phase setSubMinMax 0 360
PlanarLIC action snap 0 1
PlanarLIC orientation untouch
PlanarLIC setMinPlanePoint -1e+015 -1e+015 -1e+015
PlanarLIC setMaxPlanePoint 1e+015 1e+015 1e+015
PlanarLIC setPlane -0.757691 1.49144 26.708 1 6.62101e-008 2.72033e-008 -2.72033e-008 0.610905 -0.791704
PlanarLIC setTranslateRange 101.000000
PlanarLIC lic setValue 2 1
PlanarLIC fire
PlanarLIC setViewerMask 65535
PlanarLIC select
PlanarLIC setShadowStyle 0

set hideNewModules 0

BoundingBox clipGeom PlanarLIC
GridBoundary clipGeom PlanarLIC
PlanarLIC invertClippingPlane

viewer 0 setCameraOrientation 0.954844 -0.0619855 0.290568 2.7333
viewer 0 setCameraPosition 1.47288 0.294706 24.0704
viewer 0 setCameraFocalDistance 3.58044
viewer 0 setCameraNearDistance 1.6673
viewer 0 setCameraFarDistance 5.5999
viewer 0 setCameraType perspective
viewer 0 setCameraHeightAngle 44.9023
viewer 0 setAutoRedraw 1
viewer 0 redraw
