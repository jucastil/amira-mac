# Amira Script
remove -All

# Create viewers
viewer 0 show
viewer 0 setBackgroundMode 1
viewer 0 setAutoRedraw 0

mainWindow show

set hideNewModules 1
[ load $AMIRA_ROOT/data/colormaps/temperature.icol ] setLabel temperature.icol
{temperature.icol} setIconPosition 0 0
{temperature.icol} setViewerMask 0
{temperature.icol} setMinMax 38 44
{temperature.icol} fire
{temperature.icol} setViewerMask 16383

set hideNewModules 1
[ load $AMIRA_ROOT/data/colormaps/physics.icol ] setLabel physics.icol
{physics.icol} setIconPosition 0 0
{physics.icol} setViewerMask 0
{physics.icol} fire
{physics.icol} setViewerMask 16383

set hideNewModules 0
[ load $AMIRA_ROOT/data/medical/reg005.ctdata.am ] setLabel reg005.ctdata
{reg005.ctdata} setIconPosition 20 10
{reg005.ctdata} setViewerMask 0
{reg005.ctdata} fire
{reg005.ctdata} setViewerMask 16383

set hideNewModules 0
[load $AMIRA_ROOT/data/medical/reg005.labels.am] setLabel reg005.labels

set hideNewModules 0
create HxBoundingBox {BoundingBox}
{BoundingBox} setIconPosition 301 10
{BoundingBox} setViewerMask 0
BoundingBox data connect reg005.ctdata
{BoundingBox} text setValue 0 0
{BoundingBox} fire
{BoundingBox} setViewerMask 16383

set hideNewModules 0
create HxOrthoSlice {OrthoSlice}
{OrthoSlice} setIconPosition 316 40
{OrthoSlice} setViewerMask 0
OrthoSlice data connect reg005.ctdata
{OrthoSlice} fire
{OrthoSlice} sliceOrientation setIndex -1
{OrthoSlice} sliceOrientation untouch
{OrthoSlice} fire
{OrthoSlice} options setValue 0 0
{OrthoSlice} options setValue 1 0
{OrthoSlice} mappingType setValue 0
{OrthoSlice} linearRange setMinMax 0 -3.40282346638529e+38 3.40282346638529e+38
{OrthoSlice} linearRange setValue 0 -200
{OrthoSlice} linearRange setMinMax 1 -3.40282346638529e+38 3.40282346638529e+38
{OrthoSlice} linearRange setValue 1 200
{OrthoSlice} contrastLimit setMinMaxAll 0 100
{OrthoSlice} contrastLimit setValues 7
{OrthoSlice} colormap setDefaultColor 0.5 0.5 0.5
{OrthoSlice} colormap setDefaultAlpha 1.000000
{OrthoSlice} sliceNumber setMinMax 0 59
{OrthoSlice} sliceNumber setValue 0
{OrthoSlice} transparency setValue 0
{OrthoSlice} fire

{OrthoSlice} update
{OrthoSlice} fire
{OrthoSlice} setViewerMask 16383

set hideNewModules 0
create HxOrthoSlice {OrthoSlice2}
{OrthoSlice2} setIconPosition 309 70
{OrthoSlice2} setViewerMask 0
OrthoSlice2 data connect reg005.ctdata
{OrthoSlice2} fire
{OrthoSlice2} sliceOrientation setIndex -1
{OrthoSlice2} sliceOrientation untouch
{OrthoSlice2} fire
{OrthoSlice2} options setValue 0 0
{OrthoSlice2} options setValue 1 0
{OrthoSlice2} mappingType setValue 0
{OrthoSlice2} linearRange setMinMax 0 -3.40282346638529e+38 3.40282346638529e+38
{OrthoSlice2} linearRange setValue 0 -200
{OrthoSlice2} linearRange setMinMax 1 -3.40282346638529e+38 3.40282346638529e+38
{OrthoSlice2} linearRange setValue 1 200
{OrthoSlice2} contrastLimit setMinMaxAll 0 100
{OrthoSlice2} contrastLimit setValues 7
{OrthoSlice2} colormap setDefaultColor 0.5 0.5 0.5
{OrthoSlice2} colormap setDefaultAlpha 1.000000
{OrthoSlice2} sliceNumber setMinMax 0 59
{OrthoSlice2} sliceNumber setValue 16
{OrthoSlice2} transparency setValue 0
{OrthoSlice2} fire

{OrthoSlice2} update
{OrthoSlice2} fire
{OrthoSlice2} setViewerMask 16383

set hideNewModules 0
create HxOrthoSlice {OrthoSlice3}
{OrthoSlice3} setIconPosition 309 100
{OrthoSlice3} setViewerMask 0
OrthoSlice3 data connect reg005.ctdata
{OrthoSlice3} fire
{OrthoSlice3} sliceOrientation setIndex -1
{OrthoSlice3} sliceOrientation untouch
{OrthoSlice3} fire
{OrthoSlice3} options setValue 0 0
{OrthoSlice3} options setValue 1 0
{OrthoSlice3} mappingType setValue 0
{OrthoSlice3} linearRange setMinMax 0 -3.40282346638529e+38 3.40282346638529e+38
{OrthoSlice3} linearRange setValue 0 -200
{OrthoSlice3} linearRange setMinMax 1 -3.40282346638529e+38 3.40282346638529e+38
{OrthoSlice3} linearRange setValue 1 200
{OrthoSlice3} contrastLimit setMinMaxAll 0 100
{OrthoSlice3} contrastLimit setValues 7
{OrthoSlice3} colormap setDefaultColor 0.5 0.5 0.5
{OrthoSlice3} colormap setDefaultAlpha 1.000000
{OrthoSlice3} sliceNumber setMinMax 0 59
{OrthoSlice3} sliceNumber setValue 30
{OrthoSlice3} transparency setValue 0
{OrthoSlice3} fire

{OrthoSlice3} update
{OrthoSlice3} fire
{OrthoSlice3} setViewerMask 16383

set hideNewModules 0
create HxOrthoSlice {OrthoSlice4}
{OrthoSlice4} setIconPosition 309 130
{OrthoSlice4} setViewerMask 0
OrthoSlice4 data connect reg005.ctdata
{OrthoSlice4} fire
{OrthoSlice4} sliceOrientation setIndex -1
{OrthoSlice4} sliceOrientation untouch
{OrthoSlice4} fire
{OrthoSlice4} options setValue 0 0
{OrthoSlice4} options setValue 1 0
{OrthoSlice4} mappingType setValue 0
{OrthoSlice4} linearRange setMinMax 0 -3.40282346638529e+38 3.40282346638529e+38
{OrthoSlice4} linearRange setValue 0 -200
{OrthoSlice4} linearRange setMinMax 1 -3.40282346638529e+38 3.40282346638529e+38
{OrthoSlice4} linearRange setValue 1 200
{OrthoSlice4} contrastLimit setMinMaxAll 0 100
{OrthoSlice4} contrastLimit setValues 7
{OrthoSlice4} colormap setDefaultColor 0.5 0.5 0.5
{OrthoSlice4} colormap setDefaultAlpha 1.000000
{OrthoSlice4} sliceNumber setMinMax 0 59
{OrthoSlice4} sliceNumber setValue 45
{OrthoSlice4} transparency setValue 0
{OrthoSlice4} fire

{OrthoSlice4} update
{OrthoSlice4} fire
{OrthoSlice4} setViewerMask 16383

set hideNewModules 0
create HxOrthoSlice {OrthoSlice5}
{OrthoSlice5} setIconPosition 309 160
{OrthoSlice5} setViewerMask 0
OrthoSlice5 data connect reg005.ctdata
{OrthoSlice5} fire
{OrthoSlice5} sliceOrientation setIndex -1
{OrthoSlice5} sliceOrientation untouch
{OrthoSlice5} fire
{OrthoSlice5} options setValue 0 0
{OrthoSlice5} options setValue 1 0
{OrthoSlice5} mappingType setValue 0
{OrthoSlice5} linearRange setMinMax 0 -3.40282346638529e+38 3.40282346638529e+38
{OrthoSlice5} linearRange setValue 0 -200
{OrthoSlice5} linearRange setMinMax 1 -3.40282346638529e+38 3.40282346638529e+38
{OrthoSlice5} linearRange setValue 1 200
{OrthoSlice5} contrastLimit setMinMaxAll 0 100
{OrthoSlice5} contrastLimit setValues 7
{OrthoSlice5} colormap setDefaultColor 0.5 0.5 0.5
{OrthoSlice5} colormap setDefaultAlpha 1.000000
{OrthoSlice5} sliceNumber setMinMax 0 59
{OrthoSlice5} sliceNumber setValue 59
{OrthoSlice5} transparency setValue 0
{OrthoSlice5} fire

{OrthoSlice5} update
{OrthoSlice5} fire
{OrthoSlice5} setViewerMask 16383

set hideNewModules 0

viewer 0 setCameraPosition 79.2296 -46.383 77.572
viewer 0 setCameraOrientation -0.824351 -0.287416 -0.487686 5.04756
viewer 0 setCameraFocalDistance 99.1469
viewer 0 setAutoRedraw 1
viewer 0 redraw
