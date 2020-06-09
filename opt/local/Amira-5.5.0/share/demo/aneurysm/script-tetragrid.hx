# Amira Script
remove -All

# Create viewers
viewer 0 show
viewer 0 setAutoRedraw 0

if { ![info exists FULLSCREEN] || !$FULLSCREEN } {
mainWindow show
}

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/aneurysm/tetragrid.am ] setLabel {tetragrid.am}
{tetragrid.am} setIconPosition 20 38
{tetragrid.am} setViewerMask 0 
{tetragrid.am} fire
{tetragrid.am} setViewerMask 65535
{tetragrid.am} select

set hideNewModules 0
create HxGridVolume {GridVolume}
{GridVolume} setIconPosition 331 38
{GridVolume} setViewerMask 0 
{GridVolume} data connect {tetragrid.am}
{GridVolume} fire
{GridVolume} {data} connect {tetragrid.am}
{GridVolume} colormap setDefaultColor 1 0.1 0.1
{GridVolume} colormap setDefaultAlpha 0.500000
{GridVolume} drawStyle setValue 0
{GridVolume} drawStyle setTexture 0
{GridVolume} drawStyle setNormalBinding 0
{GridVolume} buffer setIndex -1
{GridVolume} buffer untouch
{GridVolume} materials setIndex 0 0
{GridVolume} colorMode setValue 0
{GridVolume} fire
#{GridVolume} buffer setIndex 3
{GridVolume} selectTetra zab HIJMONMBDBABAAAAAIMACAONBPHKMGPAABAKAAAAAAAAAAAAAAAAAAAAAAAAPIDCFLAHNFGNLBBN
{GridVolume} fire
{GridVolume} setViewerMask 65535

set hideNewModules 0

viewer 0 setCameraPosition -1.26722 4.081 29.4533
viewer 0 setCameraOrientation -0.058043 0.397577 0.915731 3.42295
viewer 0 setCameraFocalDistance 3.77904
viewer 0 setAutoRedraw 1
viewer 0 redraw

sleep 1

proc onKeyF2 { } {
    GridVolume fire
    GridVolume unselectTetra 0 110000
    viewer 0 redraw

    set n 1000
    while { $n<115000 } {
        GridVolume selectTetra 0 $n
        incr n 3000
        viewer 0 redraw
    }
}

#onKeyF2
echo "Press F2 to animate the scene."
