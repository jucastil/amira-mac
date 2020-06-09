# Amira Script
remove -all

# Create viewers
viewer 0 show
viewer 0 setAutoRedraw 0

mainWindow show

set hideNewModules 0
create HxAnnaVectorField3 {Brusselator}
{Brusselator} setIconPosition 20 10
{Brusselator} setViewerMask 0 
{Brusselator} x setValue "1 + x*x*y - (z+1)*x"
{Brusselator} y setValue "x*z - x*x*y"
{Brusselator} z setValue "-x*z + 1.45"
{Brusselator} setBoundingBox 0 6 0 6 0 6
{Brusselator} update
{Brusselator} fire
{Brusselator} setViewerMask 32767

set hideNewModules 0
create HxBoundingBox {BoundingBox}
{BoundingBox} setIconPosition 300 10
{BoundingBox} setViewerMask 0 
{BoundingBox} {data} connect {Brusselator}
{BoundingBox} text setValue 0 0
{BoundingBox} update
{BoundingBox} fire
{BoundingBox} setViewerMask 32767

set hideNewModules 0
create HxDisplayISL {DisplayISL}
{DisplayISL} setIconPosition 315 40
{DisplayISL} setViewerMask 0 
{DisplayISL} {data} connect {Brusselator}
{DisplayISL} fire
{DisplayISL} setLineWidth 1.000000
{DisplayISL} setLineSmooth 1
{DisplayISL} box setValue 1
{DisplayISL} setBoxTranslation 2.93432 0.897338 1.1844
{DisplayISL} setBoxScale 0.32607 0.130572 0.157149
{DisplayISL} colormap setDefaultColor 1 1 1
{DisplayISL} colormap setDefaultAlpha 1.000000
{DisplayISL} numLines setMinMax 0 1000
{DisplayISL} numLines setValue 100
{DisplayISL} length setMinMax 1 250
{DisplayISL} length setValue 160
{DisplayISL} opacity setMinMax 0 1
{DisplayISL} opacity setValue 1
{DisplayISL} fadeFactor setMinMax 0.9 1
{DisplayISL} fadeFactor setValue 0.993
{DisplayISL} alphaRange setMinMax 0 -1e+20 1e+20
{DisplayISL} alphaRange setValue 0 0
{DisplayISL} alphaRange setMinMax 1 -1e+20 1e+20
{DisplayISL} alphaRange setValue 1 100
{DisplayISL} options setValue 0 1
{DisplayISL} options setValue 1 1
{DisplayISL} options setValue 2 0
{DisplayISL} distribute setIndex 0
{DisplayISL} distribute untouch
{DisplayISL} distribute setOptValue 0
{DisplayISL} fire
{DisplayISL} distribute setIndex 0
{DisplayISL} update
{DisplayISL} fire
{DisplayISL} setViewerMask 32767
{DisplayISL} select

set hideNewModules 0

viewer 0 setCameraPosition -4.29638 8.53804 -6.32191
viewer 0 setCameraOrientation -0.0741433 -0.965759 -0.24862 2.48088
viewer 0 setCameraFocalDistance 13.0431
viewer 0 setAutoRedraw 1
viewer 0 redraw
