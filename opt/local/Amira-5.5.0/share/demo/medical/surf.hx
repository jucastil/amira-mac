# Amira Script
remove -All

# Create viewers
viewer 0 show
viewer 0 setAutoRedraw 0

mainWindow show

set hideNewModules 1
[ load ${AMIRA_ROOT}/data/colormaps/temperature.icol ] setLabel {temperature.icol}
{temperature.icol} setIconPosition 0 0
{temperature.icol} setViewerMask 0
{temperature.icol} setMinMax 38 44
{temperature.icol} fire
{temperature.icol} setViewerMask 16383

set hideNewModules 1
[ load ${AMIRA_ROOT}/data/colormaps/physics.icol ] setLabel {physics.icol}
{physics.icol} setIconPosition 0 0
{physics.icol} setViewerMask 0
{physics.icol} setMinMax 0 1
{physics.icol} fire
{physics.icol} setViewerMask 16383

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/medical/reg005.surf ] setLabel {reg005.surf}
{reg005.surf} setIconPosition 20 10
{reg005.surf} setViewerMask 0
{reg005.surf} update
{reg005.surf} fire
{reg005.surf} setViewerMask 16383

set hideNewModules 0
create HxDisplaySurface {SurfaceView}
{SurfaceView} setIconPosition 307 10
{SurfaceView} setViewerMask 0
{SurfaceView} {data} connect {reg005.surf}
{SurfaceView} colormap setDefaultColor 1 0.1 0.1
{SurfaceView} colormap setDefaultAlpha 0.500000
{SurfaceView} drawStyle setValue 0
{SurfaceView} drawStyle setTexture 0
{SurfaceView} drawStyle setNormalBinding 0
{SurfaceView} buffer setIndex -1
{SurfaceView} buffer untouch
{SurfaceView} materials setIndex 0 4
{SurfaceView} materials setIndex 1 0
{SurfaceView} colorMode setValue 2
{SurfaceView} baseTrans setMinMax 0 1
{SurfaceView} baseTrans setValue 0.8
{SurfaceView} fire
{SurfaceView} selectTriangles zab HIJMGDGABIAFKDGABEIMICFBDABMMBPPPPHPIAJIDMLABPIIIBEGDACBJLPHABECMJCAILDJDGIAOMHJOAEIKODNEDBNNEENKLPPAHAMKGAGEKOCOJADCFJKAHAJPINPMAMAMAKIEDAFHDBODADADAPPAHKHLNFBDAIMABDAIKHPAACJHOBMLCHEHFALLBAAAACDJNEKBF
{SurfaceView} update
{SurfaceView} fire
{SurfaceView} setViewerMask 16383
{SurfaceView} select

set hideNewModules 0

viewer 0 setCameraPosition 35.5324 -21.1342 57.8418
viewer 0 setCameraOrientation 0.975384 0.129511 0.178475 1.06459
viewer 0 setCameraFocalDistance 55.7045
viewer 0 setAutoRedraw 1
viewer 0 redraw
