# Amira Script
remove -all
remove volrenRed.col volrenGreen.col 3DHEAD.lda OrthoSlice ObliqueSlice Voltex BoundingBox

# Create viewers
viewer setVertical 0

viewer 0 setBackgroundMode 1
viewer 0 setBackgroundColor 0 0.1 0.3
viewer 0 setBackgroundColor2 0.7 0.7 0.8
viewer 0 setTransparencyType 5
viewer 0 setAutoRedraw 0
viewer 0 show
mainWindow show

set hideNewModules 1
[ load ${AMIRA_ROOT}/data/colormaps/volrenRed.col ] setLabel volrenRed.col
volrenRed.col setIconPosition 0 0
volrenRed.col fire
{volrenRed.col} setMinMax 10 180
volrenRed.col flags setValue 1
volrenRed.col shift setMinMax -1 1
volrenRed.col shift setButtons 0
volrenRed.col shift setIncrement 0.133333
volrenRed.col shift setValue 0
volrenRed.col shift setSubMinMax -1 1
volrenRed.col scale setMinMax 0 1
volrenRed.col scale setButtons 0
volrenRed.col scale setIncrement 0.1
volrenRed.col scale setValue 1
volrenRed.col scale setSubMinMax 0 1
volrenRed.col fire
volrenRed.col setViewerMask 32767

set hideNewModules 1
[ load ${AMIRA_ROOT}/data/colormaps/volrenGreen.col ] setLabel volrenGreen.col
volrenGreen.col setIconPosition 0 0
volrenGreen.col fire
{volrenGreen.col} setMinMax 13 200
volrenGreen.col flags setValue 1
volrenGreen.col shift setMinMax -1 1
volrenGreen.col shift setButtons 0
volrenGreen.col shift setIncrement 0.133333
volrenGreen.col shift setValue 0
volrenGreen.col shift setSubMinMax -1 1
volrenGreen.col scale setMinMax 0 1
volrenGreen.col scale setButtons 0
volrenGreen.col scale setIncrement 0.1
volrenGreen.col scale setValue 1
volrenGreen.col scale setSubMinMax 0 1
volrenGreen.col fire
volrenGreen.col setViewerMask 32767

set hideNewModules 0
[ load ${SCRIPTDIR}/3DHEAD.lda ] setLabel 3DHEAD.lda
3DHEAD.lda setIconPosition 46 115
3DHEAD.lda fire
3DHEAD.lda fire
3DHEAD.lda setViewerMask 32767
3DHEAD.lda select

set hideNewModules 0
create HxOrthoSliceLDM {OrthoSlice}
OrthoSlice setIconPosition 211 46
OrthoSlice data connect 3DHEAD.lda
OrthoSlice colormap setDefaultColor 1 0.8 0.5
OrthoSlice colormap setDefaultAlpha 0.500000
OrthoSlice colormap connect volrenGreen.col
OrthoSlice fire
OrthoSlice sliceOrientation setValue 0
OrthoSlice options setValue 0 0
OrthoSlice options setValue 1 0
OrthoSlice options setValue 2 1
OrthoSlice options setValue 3 0
OrthoSlice interpolation setValue 1
OrthoSlice mappingType setValue 0 1
OrthoSlice range setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
OrthoSlice range setValue 0 0
OrthoSlice range setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
OrthoSlice range setValue 1 255
OrthoSlice sliceNumber setMinMax 0 183
OrthoSlice sliceNumber setButtons 1
OrthoSlice sliceNumber setIncrement 12
OrthoSlice sliceNumber setValue 66.3824
OrthoSlice sliceNumber setSubMinMax 0 183
OrthoSlice transparency setValue 1
OrthoSlice fire
OrthoSlice setViewerMask 32767

set hideNewModules 0
create HxObliqueSliceLDM {ObliqueSlice}
ObliqueSlice setIconPosition 210 89
ObliqueSlice data connect 3DHEAD.lda
ObliqueSlice colormap setDefaultColor 1 0.8 0.5
ObliqueSlice colormap setDefaultAlpha 0.500000
ObliqueSlice colormap connect volrenGreen.col
ObliqueSlice fire
ObliqueSlice options setValue 0 0
ObliqueSlice options setValue 1 0
ObliqueSlice options setValue 2 0
ObliqueSlice options setValue 3 0
ObliqueSlice translate setMinMax 0 430
ObliqueSlice translate setButtons 1
ObliqueSlice translate setIncrement 28
ObliqueSlice translate setValue 261
ObliqueSlice translate setSubMinMax 0 430
ObliqueSlice sliceOptions setValue 0 0
ObliqueSlice sliceOptions setValue 1 1
ObliqueSlice sliceOptions setValue 2 0
ObliqueSlice interpolation setValue 1
ObliqueSlice mappingType setValue 0 1
ObliqueSlice range setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
ObliqueSlice range setValue 0 0
ObliqueSlice range setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
ObliqueSlice range setValue 1 255
ObliqueSlice transparency setValue 1
ObliqueSlice orientation untouch
ObliqueSlice setPlane 103.419 376.028 26.282 0.821376 -0.551363 0.146081 0.196787 0.0335442 -0.979872
ObliqueSlice fire
ObliqueSlice setViewerMask 32767

set hideNewModules 0
create HxVolumeRender {Voltex}
Voltex setIconPosition 210 131
Voltex data connect 3DHEAD.lda
Voltex colormap setDefaultColor 1 0.8 0.5
Voltex colormap setDefaultAlpha 0.500000
Voltex colormap connect volrenRed.col
Voltex fire
Voltex renderStyle setValue 0
Voltex options setValue 0 0
Voltex options setValue 1 1
Voltex options setValue 2 1
Voltex composition setValue 0
Voltex interpolation setValue 1
Voltex range setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
Voltex range setValue 0 0
Voltex range setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
Voltex range setValue 1 255
Voltex lookup setValue 2
Voltex alphaScale setMinMax 0 1
Voltex alphaScale setButtons 0
Voltex alphaScale setIncrement 0.1
Voltex alphaScale setValue 0.0921986
Voltex alphaScale setSubMinMax 0 1
Voltex texture2D3D setValue 1
Voltex slices setMinMax 1 431
Voltex slices setButtons 1
Voltex slices setIncrement 28
Voltex slices setValue 431
Voltex slices setSubMinMax 1 431
Voltex useRGBA setValue 0 0
Voltex fire
Voltex setViewerMask 32767

set hideNewModules 0
create HxBoundingBox {BoundingBox}
BoundingBox setIconPosition 209 172
{BoundingBox} setLineWidth 0
{BoundingBox} setColor 1 0.5 0
BoundingBox data connect 3DHEAD.lda
BoundingBox fire
BoundingBox text setValue 0 0
BoundingBox fire
BoundingBox setViewerMask 32767

set hideNewModules 0


viewer 0 setCameraPosition -188.395 174.519 405.812
viewer 0 setCameraOrientation 0.425153 0.0133047 -0.905024 2.96547
viewer 0 setCameraFocalDistance 498.938
viewer 0 setAutoRedraw 1
viewer 0 redraw
