# Amira Script
remove -All

# Create viewers
viewer 0 show
viewer 0 setAutoRedraw 0

mainWindow show

set hideNewModules 1
[ load ${AMIRA_ROOT}/data/colormaps/physics.icol ] setLabel {physics.icol}
{physics.icol} setIconPosition 0 0
{physics.icol} setViewerMask 0 
{physics.icol} setMinMax 0 1
{physics.icol} flags setValue 0
{physics.icol} update
{physics.icol} fire
{physics.icol} setViewerMask 32767

set hideNewModules 0
create HxAnnaVectorField3 {Vectorfield}
{Vectorfield} setIconPosition 21 10
{Vectorfield} setViewerMask 0 
{Vectorfield} x setValue "-y"
{Vectorfield} y setValue "x+0.4*y"
{Vectorfield} z setValue "-z*z"
{Vectorfield} setBoundingBox -1 1 -1 1 -1 1
{Vectorfield} update
{Vectorfield} fire
{Vectorfield} setViewerMask 32767

set hideNewModules 0
create HxBoundingBox {BoundingBox}
{BoundingBox} setIconPosition 301 10
{BoundingBox} setViewerMask 0 
{BoundingBox} {data} connect {Vectorfield}
{BoundingBox} text setValue 0 0
{BoundingBox} update
{BoundingBox} fire
{BoundingBox} setViewerMask 32767

set hideNewModules 0
create HxFastLIC {PlanarLIC}
{PlanarLIC} setIconPosition 301 40
{PlanarLIC} setViewerMask 0 
{PlanarLIC} {data} connect {Vectorfield}
{PlanarLIC} {colormap} connect {physics.icol}
{PlanarLIC} fire
{PlanarLIC} orientation setIndex -1
{PlanarLIC} orientation untouch
{PlanarLIC} options setValue 0 0
{PlanarLIC} options setValue 1 0
{PlanarLIC} translate setMinMax 0 100
{PlanarLIC} translate setValue 50
{PlanarLIC} colorMode setValue 1
{PlanarLIC} lic setValue 0 40
{PlanarLIC} lic setValue 1 180
{PlanarLIC} phase setMinMax 0 360
{PlanarLIC} phase setValue 0
{PlanarLIC} doIt setIndex -1
{PlanarLIC} doIt untouch
{PlanarLIC} orientation untouch
{PlanarLIC} setPlane 0 0 0 1 0 0 0 1 0
{PlanarLIC} fire
{PlanarLIC} doIt hit
{PlanarLIC} fire
{PlanarLIC} setViewerMask 32767
{PlanarLIC} select

set hideNewModules 0

viewer 0 setCameraPosition 0 0 -4.34026
viewer 0 setCameraOrientation 1 0 0 3.14159
viewer 0 setCameraFocalDistance 4.34026
viewer 0 setAutoRedraw 1
viewer 0 redraw
