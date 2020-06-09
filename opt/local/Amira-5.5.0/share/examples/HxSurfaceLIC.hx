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
{BoundingBox} {data} connect {Scalarfield}
{BoundingBox} text setValue 0 0
{BoundingBox} update
{BoundingBox} fire
{BoundingBox} setViewerMask 32767

set hideNewModules 0
create HxArithmetic {Arithmetic}
{Arithmetic} setIconPosition 160 10
{Arithmetic} setViewerMask 0 
{Arithmetic} {inputA} connect {Scalarfield}
{Arithmetic} expr setValue "A"
{Arithmetic} resultType setValue 1
{Arithmetic} resolution setMinMaxAll 1 512 1 512 1 512
{Arithmetic} resolution setValues 32 32 32
{Arithmetic} minBox setValue 0 -1
{Arithmetic} minBox setValue 1 -1
{Arithmetic} minBox setValue 2 -1
{Arithmetic} maxBox setValue 0 1
{Arithmetic} maxBox setValue 1 1
{Arithmetic} maxBox setValue 2 1
{Arithmetic} update
{Arithmetic} fire
{Arithmetic} setViewerMask 32767

set hideNewModules 0
[ {Arithmetic} create ] setLabel Result
{Result} setIconPosition 21 40
{Result} setViewerMask 0 
{Result} {master} connect {Arithmetic}
{Result} update
{Result} fire
{Result} setViewerMask 32767

set hideNewModules 0
create HxIsosurface {Isosurface}
{Isosurface} setIconPosition 318 40
{Isosurface} setViewerMask 0
{Isosurface} {data} connect {Result}
{Isosurface} fire
{Isosurface} colormap setDefaultColor 1 0.8 0.4
{Isosurface} colormap setDefaultAlpha 0.500000
{Isosurface} drawStyle setValue 0
{Isosurface} drawStyle setTexture 0
{Isosurface} drawStyle setNormalBinding 1
{Isosurface} buffer setIndex -1
{Isosurface} buffer untouch
{Isosurface} threshold setMinMax 0.0378908 1.24942
{Isosurface} threshold setValue 0.615187
{Isosurface} options setValue 0 1
{Isosurface} options setValue 1 0
{Isosurface} resolution setMinMaxAll 0 100 0 100 0 100
{Isosurface} resolution setValues 2 2 2
{Isosurface} doIt hit
{Isosurface} fire

set surface [ {Isosurface} createSurface ]

create HxAnnaVectorField3 {Vectorfield}
{Vectorfield} setIconPosition 20 100
{Vectorfield} setViewerMask 0 
{Vectorfield} x setValue "-y"
{Vectorfield} y setValue "x"
{Vectorfield} z setValue "0"
{Vectorfield} update
{Vectorfield} fire
{Vectorfield} setViewerMask 32767

create HxSurfaceLIC {SurfaceLIC}
{SurfaceLIC} setIconPosition 313 70
{SurfaceLIC} setViewerMask 0 
{SurfaceLIC} surface connect $surface
{SurfaceLIC} vectorField connect {Vectorfield}
{SurfaceLIC} fire
{SurfaceLIC} colormap setDefaultColor 0.5 0.5 0.5
{SurfaceLIC} colormap setDefaultAlpha 1.000000
{SurfaceLIC} colorMode setValue 0
{SurfaceLIC} interpol setValue 1
{SurfaceLIC} contrast setValue 0 200
{SurfaceLIC} contrast setValue 1 220
{SurfaceLIC} options setMinMaxAll 0 500 1 2048
{SurfaceLIC} options setValues 25 200
{SurfaceLIC} update
{SurfaceLIC} fire
{SurfaceLIC} setViewerMask 32767
{SurfaceLIC} select
{SurfaceLIC} doIt hit
{SurfaceLIC} fire

set hideNewModules 0

viewer 0 setCameraPosition 9.56586 -6.13125 7.38878
viewer 0 setCameraOrientation 0.638456 0.365542 0.677313 1.34704
viewer 0 setCameraFocalDistance 13.9553
viewer 0 setAutoRedraw 1
viewer 0 redraw
