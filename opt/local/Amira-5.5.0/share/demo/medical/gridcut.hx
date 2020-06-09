# Amira Script
remove -All

# Create viewers
viewer 0 show
viewer 0 setAutoRedraw 0

mainWindow show

set hideNewModules 0
[ load $AMIRA_ROOT/data/medical/reg005.tetragrid.am ] setLabel {reg005.tetragrid.am}
{reg005.tetragrid.am} setIconPosition 20 10
{reg005.tetragrid.am} setViewerMask 0
{reg005.tetragrid.am} update
{reg005.tetragrid.am} fire
{reg005.tetragrid.am} setViewerMask 16383

set hideNewModules 0
create HxGridVolume {GridVolume}
{GridVolume} setIconPosition 313 10
{GridVolume} setViewerMask 0
{GridVolume} data connect {reg005.tetragrid.am}
{GridVolume} fire
{GridVolume} {data} connect {reg005.tetragrid.am}
{GridVolume} colormap setDefaultColor 1 0.1 0.1
{GridVolume} colormap setDefaultAlpha 0.500000
{GridVolume} drawStyle setValue 1
{GridVolume} drawStyle setTexture 0
{GridVolume} drawStyle setNormalBinding 0
{GridVolume} materials setIndex 0 0
{GridVolume} colorMode setValue 0
{GridVolume} fire
{GridVolume} selectTetra zab HIJMONMDDBANAAAAAMADCAAJPDKPLGKLIMBOJAJAAAAAAAAAAAAAAAAAAAMLKOBPCEAAMFDG
{GridVolume} fire
{GridVolume} setViewerMask 16383

set hideNewModules 0
create HxGridCut {GridCut}
{GridCut} setIconPosition 313 43
{GridCut} setViewerMask 0
{GridCut} {data} connect {reg005.tetragrid.am}
{GridCut} colormap setDefaultColor 1 0.8 0.5
{GridCut} colormap setDefaultAlpha 0.500000
{GridCut} orientation setIndex -1
{GridCut} orientation untouch
{GridCut} options setValue 0 0
{GridCut} options setValue 1 0
{GridCut} options setValue 2 0
{GridCut} translate setMinMax 0 100
{GridCut} translate setValue 71
{GridCut} texture setValue 0
{GridCut} selection setIndex -1
{GridCut} selection untouch
{GridCut} selection setOptValue 0
{GridCut} orientation untouch
{GridCut} setPlane 24.2612 13.2075 39.4146 1 0 8.9407e-08 -2.98023e-08 0.555362 0.831609
{GridCut} fire
{GridCut} setViewerMask 16383
{GridCut} select

set hideNewModules 0
create HxOverlayGrid {Intersection}
{Intersection} setIconPosition 313 63
{Intersection} setViewerMask 0
{Intersection} {data} connect {reg005.tetragrid.am}
{Intersection} {module} connect {GridCut}
{Intersection} mode setValue 0 0
{Intersection} lineWidth setValue 0
{Intersection} selection setIndex -1
{Intersection} selection untouch
{Intersection} selection setOptValue 0
{Intersection} fire
{Intersection} setMatList 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
{Intersection} fire
{Intersection} setColor 0
{Intersection} setViewerMask 16383

set hideNewModules 0
GridVolume clipGeom GridCut

viewer 0 setCameraPosition 80.127 -11.2987 93.9149
viewer 0 setCameraOrientation 0.365235 -0.185151 0.912317 2.90025
viewer 0 setCameraFocalDistance 91.0714
viewer 0 setAutoRedraw 1
viewer 0 redraw
