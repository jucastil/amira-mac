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
load $AMIRA_ROOT/data/medical/reg005.tetragrid.am
{reg005.tetragrid.am} setIconPosition 20 10
{reg005.tetragrid.am} setViewerMask 0
{reg005.tetragrid.am} fire
{reg005.tetragrid.am} setViewerMask 16383

set hideNewModules 0
load $AMIRA_ROOT/data/medical/reg005.thermvals.am
{reg005.thermvals.am} setIconPosition 20 40
{reg005.thermvals.am} setViewerMask 0
{reg005.thermvals.am} {grid} connect {reg005.tetragrid.am}
{reg005.thermvals.am} fire
{reg005.thermvals.am} setViewerMask 16383

set hideNewModules 0
create HxGridVolume {GridVolume}
{GridVolume} setIconPosition 264 9
{GridVolume} setViewerMask 0
{GridVolume} data connect {reg005.tetragrid.am}
{GridVolume} fire
{GridVolume} {data} connect {reg005.tetragrid.am}
{GridVolume} {colorField} connect {reg005.thermvals.am}
{GridVolume} colormap setDefaultColor 1 0.1 0.1
{GridVolume} colormap setDefaultAlpha 0.500000
{GridVolume} {colormap} connect {temperature.icol}
{GridVolume} drawStyle setValue 1
{GridVolume} drawStyle setTexture 1
{GridVolume} drawStyle setNormalBinding 0
{GridVolume} buffer setIndex -1
{GridVolume} buffer untouch
{GridVolume} materials setIndex 0 9
{GridVolume} colorMode setValue 0
{GridVolume} fire
{GridVolume} buffer setIndex 3
{GridVolume} selectTetra zab HIJMONNHMBAJIAEAAMAEMAFIIJKFNIHPBHFHICAFAIDBBNJMHAIIJOMOMALOPDEKMCEGIMMJDMCKHNFLGFHABEPABCCNOCNCNOMDNHMEOCJHNNCFHDHHFHAAAAIAKJFEJFFJJPOOFCAAAAAAPMMPAJFMFENNCE
{GridVolume} update
{GridVolume} fire
{GridVolume} setViewerMask 16383
{GridVolume} select

set hideNewModules 0

viewer 0 setCameraPosition 60.514 78.1052 73.45
viewer 0 setCameraOrientation -0.135013 -0.486724 -0.863059 3.65912
viewer 0 setCameraFocalDistance 75.7422
viewer 0 setAutoRedraw 1
viewer 0 redraw
