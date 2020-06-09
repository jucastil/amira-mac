# Amira Script
remove -all

# Create viewers
viewer 0 show
viewer 0 setAutoRedraw 0

mainWindow show

set hideNewModules 0
create HxAnnaScalarField3 {Scalarfield}
{Scalarfield} setIconPosition 20 10
{Scalarfield} setViewerMask 0 
{Scalarfield} expr setValue "(1+sin(x)*sin(x))*(1+sin(y)*sin(y))*(1+sin(z)*sin(z))/(x*x+y*y+z*z+1)"
{Scalarfield} setBoundingBox -3 3 -3 3 -3 3
{Scalarfield} update
{Scalarfield} fire
{Scalarfield} setViewerMask 32767

set hideNewModules 0
create HxBoundingBox {BoundingBox}
{BoundingBox} setIconPosition 301 10
{BoundingBox} setViewerMask 0 
{BoundingBox} data connect {Scalarfield}
{BoundingBox} text setValue 0 0
{BoundingBox} fire
{BoundingBox} setViewerMask 32767

set hideNewModules 0
create HxArbitraryCut {EmptyPlane}
{EmptyPlane} data connect {Scalarfield}
{EmptyPlane} setIconPosition 310 40
{EmptyPlane} setViewerMask 0 
{EmptyPlane} orientation setIndex 0
{EmptyPlane} orientation untouch
{EmptyPlane} options setValue 0 0
{EmptyPlane} options setValue 1 0
{EmptyPlane} options setValue 2 0
{EmptyPlane} translate setMinMax 0 100
{EmptyPlane} translate setIncrement 1
{EmptyPlane} translate setValue 50
{EmptyPlane} setPlane 0 0 0 1 0 0 0 1 0
{EmptyPlane} fire
{EmptyPlane} setViewerMask 32767
{EmptyPlane} select

set hideNewModules 0
create HxIsolines {Isolines}
{Isolines} setIconPosition 310 60
{Isolines} setViewerMask 0 
{Isolines} data connect {Scalarfield}
{Isolines} module connect {EmptyPlane}
{Isolines} update
{Isolines} colormap setDefaultColor 1 0 0
{Isolines} colormap setDefaultAlpha 1.000000
{Isolines} spacing setValue 1
{Isolines} update
{Isolines} parameters setMinMax 0 16 4096
{Isolines} parameters setValue 0 128
{Isolines} parameters setMinMax 1 0 10
{Isolines} parameters setValue 1 2
{Isolines} options setValue 0 0
{Isolines} options setValue 1 0
{Isolines} fire
{Isolines} setViewerMask 32767
{Isolines} select

{Isolines} explicit setValue "0.2 0.6 1.0"
{Isolines} fire

set hideNewModules 0

viewer 0 setCameraOrientation 0.943412 0.188651 0.272737 1.14653
viewer 0 setCameraPosition 3.84351 -11.141 5.40365
viewer 0 setCameraFocalDistance 13.0208
viewer 0 setAutoRedraw 1
viewer 0 redraw
