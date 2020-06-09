# Amira Script
remove -all
remove volrenRed.col beeBrain.lda Voltex

# Create viewers
viewer setVertical 0

viewer 0 setBackgroundMode 1
viewer 0 setBackgroundColor 0.06 0.13 0.24
viewer 0 setBackgroundColor2 0.72 0.72 0.78
viewer 0 setTransparencyType 5
viewer 0 setAutoRedraw 0
viewer 0 setCameraType 1
viewer 0 show
mainWindow show

set hideNewModules 1
[ load ${AMIRA_ROOT}/data/colormaps/volrenRed.col ] setLabel volrenRed.col
volrenRed.col setIconPosition 0 0
volrenRed.col fire
{volrenRed.col} setMinMax 0 255
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
volrenRed.col setViewerMask 16383

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/lda/beeBrain.lda ] setLabel beeBrain.lda
beeBrain.lda setIconPosition 19 10
beeBrain.lda fire
beeBrain.lda fire
beeBrain.lda setViewerMask 16383

set hideNewModules 0
create HxVolumeRender {Voltex}
Voltex setIconPosition 366 10
Voltex data connect beeBrain.lda
Voltex colormap setDefaultColor 1 0.8 0.5
Voltex colormap setDefaultAlpha 0.500000
Voltex colormap connect volrenRed.col
Voltex fire
Voltex renderStyle setValue 0
Voltex options setValue 0 0
Voltex options setValue 1 1
Voltex options setValue 2 1
Voltex options setValue 3 1
Voltex composition setValue 0
Voltex interpolation setValue 1
Voltex range setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
Voltex range setValue 0 0
Voltex range setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
Voltex range setValue 1 255
Voltex lookup setValue 2
Voltex gamma setMinMax 1 8
Voltex gamma setButtons 0
Voltex gamma setIncrement 0.466667
Voltex gamma setValue 3
Voltex gamma setSubMinMax 1 8
Voltex alphaScale setMinMax 0 1
Voltex alphaScale setButtons 0
Voltex alphaScale setIncrement 0.1
Voltex alphaScale setValue 1
Voltex alphaScale setSubMinMax 0 1
Voltex texture2D3D setValue 1
Voltex slices setMinMax 1 292
Voltex slices setButtons 1
Voltex slices setIncrement 1
Voltex slices setValue 70
Voltex slices setSubMinMax 1 292
Voltex useRGBA setValue 0 0
Voltex fire
Voltex setViewerMask 16383
Voltex select

set hideNewModules 0


viewer 0 setCameraPosition 1503.53 1180.66 4233.35
viewer 0 setCameraOrientation -0.00645761 -0.0276155 -0.999598 3.1219
viewer 0 setCameraFocalDistance 3839.53
viewer 0 setAutoRedraw 1
viewer 0 redraw
