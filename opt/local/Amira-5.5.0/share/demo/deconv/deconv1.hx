# Amira Script
remove -all
remove glow.col polytrichum.am polytrichum-psf.am ProjectionView Deconvolution

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
[ load ${AMIRA_ROOT}/data/colormaps/glow.col ] setLabel glow.col
glow.col setIconPosition 0 0
glow.col setNoRemoveAll 1
glow.col fire
{glow.col} setMinMax 0 255
glow.col flags setValue 1
glow.col shift setMinMax -1 1
glow.col shift setButtons 0
glow.col shift setIncrement 0.133333
glow.col shift setValue 0
glow.col shift setSubMinMax -1 1
glow.col scale setMinMax 0 1
glow.col scale setButtons 0
glow.col scale setIncrement 0.1
glow.col scale setValue 1
glow.col scale setSubMinMax 0 1
glow.col fire
glow.col setViewerMask 16383

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/deconv/polytrichum.am ] setLabel polytrichum.am
polytrichum.am setIconPosition 20 10
polytrichum.am sharedColormap setDefaultColor 0.8 0.8 0.8
polytrichum.am sharedColormap setDefaultAlpha 0.500000
polytrichum.am fire
polytrichum.am fire
polytrichum.am setViewerMask 16383

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/deconv/polytrichum-psf.am ] setLabel polytrichum-psf.am
polytrichum-psf.am setIconPosition 20 40
polytrichum-psf.am sharedColormap setDefaultColor 0.8 0.8 0.8
polytrichum-psf.am sharedColormap setDefaultAlpha 0.500000
polytrichum-psf.am fire
polytrichum-psf.am fire
polytrichum-psf.am setViewerMask 16383

set hideNewModules 0
create HxProjectionView {ProjectionView}
ProjectionView setIconPosition 206 10
ProjectionView data connect polytrichum.am
ProjectionView colormap setDefaultColor 1 0.8 0.5
ProjectionView colormap setDefaultAlpha 0.500000
ProjectionView colormap connect glow.col
ProjectionView fire
ProjectionView options setValue 0 0
ProjectionView options setValue 1 0
ProjectionView options setValue 2 0
ProjectionView options setValue 3 0
ProjectionView slices setValue 0 1
ProjectionView slices setValue 1 1
ProjectionView slices setValue 2 1
ProjectionView slices setValue 3 0
ProjectionView mapping setIndex 0 0
ProjectionView mapping setIndex 1 2
ProjectionView range setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
ProjectionView range setValue 0 0
ProjectionView range setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
ProjectionView range setValue 1 255
ProjectionView contrastLimit setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
ProjectionView contrastLimit setValue 0 7
ProjectionView minimum setMinMax 0 0 127
ProjectionView minimum setValue 0 0
ProjectionView minimum setMinMax 1 0 127
ProjectionView minimum setValue 1 0
ProjectionView minimum setMinMax 2 0 63
ProjectionView minimum setValue 2 0
ProjectionView maximum setMinMax 0 0 127
ProjectionView maximum setValue 0 127
ProjectionView maximum setMinMax 1 0 127
ProjectionView maximum setValue 1 127
ProjectionView maximum setMinMax 2 0 63
ProjectionView maximum setValue 2 63
ProjectionView update snap 0 1
ProjectionView fire
ProjectionView setViewerMask 16383
ProjectionView setShadowStyle 0

set hideNewModules 0
create HxDeconvolution {Deconvolution}
Deconvolution setIconPosition 211 40
Deconvolution data connect polytrichum.am
Deconvolution kernel connect polytrichum-psf.am
Deconvolution fire
Deconvolution borderWidth setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
Deconvolution borderWidth setValue 0 0
Deconvolution borderWidth setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
Deconvolution borderWidth setValue 1 0
Deconvolution borderWidth setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
Deconvolution borderWidth setValue 2 0
Deconvolution iterations setMinMax 0 100
Deconvolution iterations setButtons 1
Deconvolution iterations setIncrement 1
Deconvolution iterations setValue 15
Deconvolution iterations setSubMinMax 0 100
Deconvolution initialEstimate setValue 0
Deconvolution overrelaxation setValue 1
Deconvolution regularization setValue 0
Deconvolution penaltyWeight setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
Deconvolution penaltyWeight setValue 0 9.99999974737875e-005
Deconvolution method setValue 0
Deconvolution parameters setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
Deconvolution parameters setValue 0 1.4
Deconvolution parameters setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
Deconvolution parameters setValue 1 0.58
Deconvolution parameters setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
Deconvolution parameters setValue 2 1.51600003242493
Deconvolution mode setValue 0
Deconvolution fire
Deconvolution setViewerMask 16383
Deconvolution select
Deconvolution fire

set hideNewModules 0

proc onKeyF2 {} {
   ProjectionView data connect polytrichum.deconv
   ProjectionView fire
}


viewer 0 setCameraOrientation 0.121443 0.501181 0.856778 2.57404
viewer 0 setCameraPosition 15.6204 21.7676 16.6871
viewer 0 setCameraFocalDistance 23.1981
viewer 0 setCameraNearDistance 14.8601
viewer 0 setCameraFarDistance 31.5529
viewer 0 setCameraType perspective
viewer 0 setCameraHeightAngle 44.9023
viewer 0 setAutoRedraw 1
viewer 0 redraw

echo "Press 'Apply' to start deconvolution"
echo "Press F2 to see the result"
