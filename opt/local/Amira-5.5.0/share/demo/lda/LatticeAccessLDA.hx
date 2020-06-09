# Amira Script
remove -all
remove physics.icol volrenRed.col beeBrain.lda beeBrain.view beeBrain2.view LatticeAccess LatticeAccess2 Isosurface EmptyPlane Isolines SelectRoi Voltex

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
[ load ${AMIRA_ROOT}/data/colormaps/physics.icol ] setLabel physics.icol
physics.icol setIconPosition 0 0
physics.icol fire
{physics.icol} setMinMax 45 255
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
physics.icol setViewerMask 16383

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
beeBrain.lda setIconPosition 6 19
beeBrain.lda fire
beeBrain.lda fire
beeBrain.lda setViewerMask 16383

set hideNewModules 0
create HxLatticeAccess {LatticeAccess}
LatticeAccess setIconPosition 2 65
LatticeAccess data connect beeBrain.lda
LatticeAccess time setMinMax 0 1
LatticeAccess time setSubMinMax 0 1
LatticeAccess time setValue 0
LatticeAccess time setDiscrete 0
LatticeAccess time setIncrement 0.01
LatticeAccess time animationMode -once
LatticeAccess fire
LatticeAccess dataset setValue 0 0
LatticeAccess boxMin setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
LatticeAccess boxMin setValue 0 0
LatticeAccess boxMin setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
LatticeAccess boxMin setValue 1 0
LatticeAccess boxMin setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
LatticeAccess boxMin setValue 2 0
LatticeAccess boxSize setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
LatticeAccess boxSize setValue 0 143
LatticeAccess boxSize setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
LatticeAccess boxSize setValue 1 95
LatticeAccess boxSize setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
LatticeAccess boxSize setValue 2 81
LatticeAccess options setValue 0 1
LatticeAccess options setValue 1 0
LatticeAccess options setValue 2 1
LatticeAccess subsample setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
LatticeAccess subsample setValue 0 4
LatticeAccess subsample setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
LatticeAccess subsample setValue 1 4
LatticeAccess subsample setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
LatticeAccess subsample setValue 2 4
LatticeAccess timeSlider setMinMax 0 0
LatticeAccess timeSlider setButtons 1
LatticeAccess timeSlider setIncrement 1
LatticeAccess timeSlider setValue 0
LatticeAccess timeSlider setSubMinMax 0 0
LatticeAccess action snap 0 1
LatticeAccess fire
LatticeAccess setViewerMask 16383

set hideNewModules 0
[ {LatticeAccess} create ] setLabel {beeBrain.view}
beeBrain.view setIconPosition 1 109
beeBrain.view master connect LatticeAccess
beeBrain.view fire
beeBrain.view fire
beeBrain.view setViewerMask 16383

set hideNewModules 0
create HxLatticeAccess {LatticeAccess2}
LatticeAccess2 setIconPosition 187 62
LatticeAccess2 data connect beeBrain.lda
LatticeAccess2 time setMinMax 0 1
LatticeAccess2 time setSubMinMax 0 1
LatticeAccess2 time setValue 0
LatticeAccess2 time setDiscrete 0
LatticeAccess2 time setIncrement 0.01
LatticeAccess2 time animationMode -once
LatticeAccess2 fire
LatticeAccess2 dataset setValue 0 0
LatticeAccess2 boxMin setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
LatticeAccess2 boxMin setValue 0 0
LatticeAccess2 boxMin setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
LatticeAccess2 boxMin setValue 1 95
LatticeAccess2 boxMin setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
LatticeAccess2 boxMin setValue 2 0
LatticeAccess2 boxSize setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
LatticeAccess2 boxSize setValue 0 286
LatticeAccess2 boxSize setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
LatticeAccess2 boxSize setValue 1 97
LatticeAccess2 boxSize setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
LatticeAccess2 boxSize setValue 2 81
LatticeAccess2 options setValue 0 1
LatticeAccess2 options setValue 1 0
LatticeAccess2 options setValue 2 1
LatticeAccess2 subsample setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
LatticeAccess2 subsample setValue 0 4
LatticeAccess2 subsample setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
LatticeAccess2 subsample setValue 1 4
LatticeAccess2 subsample setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
LatticeAccess2 subsample setValue 2 4
LatticeAccess2 timeSlider setMinMax 0 0
LatticeAccess2 timeSlider setButtons 1
LatticeAccess2 timeSlider setIncrement 1
LatticeAccess2 timeSlider setValue 0
LatticeAccess2 timeSlider setSubMinMax 0 0
LatticeAccess2 action snap 0 1
LatticeAccess2 fire
LatticeAccess2 setViewerMask 16383

set hideNewModules 0
[ {LatticeAccess2} create ] setLabel {beeBrain2.view}
beeBrain2.view setIconPosition 189 111
beeBrain2.view master connect LatticeAccess2
beeBrain2.view fire
beeBrain2.view fire
beeBrain2.view setViewerMask 16383

set hideNewModules 0
create HxIsosurface {Isosurface}
Isosurface setIconPosition 203 168
Isosurface data connect beeBrain2.view
Isosurface colormap setDefaultColor 1 0.8 0.4
Isosurface colormap setDefaultAlpha 0.500000
Isosurface fire
Isosurface drawStyle setValue 1
Isosurface drawStyle setSpecularLighting 1
Isosurface drawStyle setTexture 0
Isosurface drawStyle setAlphaMode 1
Isosurface drawStyle setNormalBinding 1
Isosurface drawStyle setCullingMode 0
Isosurface threshold setMinMax 0 255
Isosurface threshold setButtons 0
Isosurface threshold setIncrement 17
Isosurface threshold setValue 141.064
Isosurface threshold setSubMinMax 0 255
Isosurface options setValue 0 1
Isosurface options setValue 1 0
Isosurface resolution setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
Isosurface resolution setValue 0 2
Isosurface resolution setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
Isosurface resolution setValue 1 2
Isosurface resolution setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
Isosurface resolution setValue 2 2
Isosurface doIt snap 0 1
{Isosurface} doIt hit
Isosurface fire
Isosurface setViewerMask 16383

set hideNewModules 0
create HxArbitraryCut {EmptyPlane}
EmptyPlane setIconPosition 16 176
EmptyPlane data connect beeBrain.view
EmptyPlane fire
EmptyPlane options setValue 0 0
EmptyPlane options setValue 1 0
EmptyPlane options setValue 2 1
EmptyPlane options setValue 3 0
EmptyPlane translate setMinMax 0 100
EmptyPlane translate setButtons 1
EmptyPlane translate setIncrement 1
EmptyPlane translate setValue 50
EmptyPlane translate setSubMinMax 0 100
EmptyPlane orientation untouch
EmptyPlane setPlane 711.056 473.219 400 1 0 0 0 1 0
EmptyPlane setFrame 0
EmptyPlane fire
EmptyPlane setViewerMask 16383

set hideNewModules 0
create HxIsolines {Isolines}
Isolines setIconPosition 16 196
Isolines data connect beeBrain.view
Isolines module connect EmptyPlane
Isolines colormap setDefaultColor 1 0 0
Isolines colormap setDefaultAlpha 0.500000
Isolines colormap connect physics.icol
Isolines fire
Isolines spacing setValue 0
Isolines uniform setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
Isolines uniform setValue 0 0
Isolines uniform setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
Isolines uniform setValue 1 255
Isolines uniform setMinMax 2 1 200
Isolines uniform setValue 2 5
Isolines explicit setState {63.75 191.25}
Isolines parameters setMinMax 0 16 4096
Isolines parameters setValue 0 128
Isolines parameters setMinMax 1 0 10
Isolines parameters setValue 1 1
Isolines options setValue 0 0
Isolines options setValue 1 0
Isolines fire
Isolines setViewerMask 16383

set hideNewModules 0
create HxSelectROILDM {SelectRoi}
SelectRoi setIconPosition 312 39
SelectRoi data connect beeBrain.lda
SelectRoi fire
SelectRoi controlling setValue 0
SelectRoi minimum setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
SelectRoi minimum setValue 0 0
SelectRoi minimum setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
SelectRoi minimum setValue 1 0
SelectRoi minimum setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
SelectRoi minimum setValue 2 0
SelectRoi maximum setMinMax 0 -1.00000001384843e+024 1.00000001384843e+024
SelectRoi maximum setValue 0 144
SelectRoi maximum setMinMax 1 -1.00000001384843e+024 1.00000001384843e+024
SelectRoi maximum setValue 1 93
SelectRoi maximum setMinMax 2 -1.00000001384843e+024 1.00000001384843e+024
SelectRoi maximum setValue 2 80
SelectRoi options setValue 0 0
SelectRoi cropping setValue 0 1
SelectRoi fire
SelectRoi setViewerMask 16383
SelectRoi select

set hideNewModules 0
create HxVolumeRender {Voltex}
Voltex setIconPosition 182 6
Voltex data connect beeBrain.lda
Voltex ROI connect SelectRoi
Voltex colormap setDefaultColor 1 0.8 0.5
Voltex colormap setDefaultAlpha 0.500000
Voltex colormap connect volrenRed.col
Voltex fire
Voltex renderStyle setValue 0
Voltex options setValue 0 0
Voltex options setValue 1 1
Voltex options setValue 2 1
Voltex options setValue 3 0
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
Voltex alphaScale setValue 0.340426
Voltex alphaScale setSubMinMax 0 1
Voltex texture2D3D setValue 1
Voltex slices setMinMax 1 292
Voltex slices setButtons 1
Voltex slices setIncrement 1
Voltex slices setValue 100
Voltex slices setSubMinMax 1 292
Voltex useRGBA setValue 0 0
Voltex fire
Voltex setViewerMask 16383

set hideNewModules 0


viewer 0 setCameraPosition 1549.23 965.244 4748.37
viewer 0 setCameraOrientation -0.0111638 4.37086e-008 -0.999938 3.14159
viewer 0 setCameraFocalDistance 4349.46
viewer 0 setAutoRedraw 1
viewer 0 redraw
