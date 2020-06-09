# Amira Script
remove -all
viewer 0 show
viewer 0 setBackgroundMode 1
mainWindow show

if { [ exists StreamSurface ] == 1 } {
    StreamSurface setViewerMask 0
}

if { [ exists slic.iv ] == 0 } {
    load ${AMIRA_ROOT}/data/misc/slic.iv
}
slic.iv showIcon

if { [ exists IvDisplay ] == 0 } {
    create HxIvDisplay IvDisplay
}

IvDisplay data connect slic.iv
IvDisplay fire

viewer setCameraOrientation -0.62127 -0.00227295 0.783593 2.06564
viewer setCameraPosition -1.77442 1.51604 0.976471
viewer setCameraFocalDistance 2.79836
viewer 0 redraw
echo "Script finished"
