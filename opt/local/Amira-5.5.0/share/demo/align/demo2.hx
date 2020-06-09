# Amira Script
remove -all
remove leaf.info AlignSlices

# Create viewers
viewer 0 show
mainWindow show

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/align/leaf.info ] setLabel leaf.info
leaf.info setIconPosition 20 10
leaf.info fire
leaf.info setViewerMask 16383

set hideNewModules 0
create HxAlignSlices {AlignSlices}
AlignSlices setIconPosition 160 10
AlignSlices data connect leaf.info
AlignSlices fire
{AlignSlices} linearRange setValue 0 0
{AlignSlices} linearRange setValue 1 255
{AlignSlices} action setIndex -1
{AlignSlices} action untouch
AlignSlices fire
AlignSlices setViewerMask 16383
AlignSlices select
AlignSlices edit

sleep 2

AlignSlices setSliceNumber 1
AlignSlices translate -40.689999 -73.173599
AlignSlices rotate 97.722397
sleep 2

AlignSlices setSliceNumber 2
AlignSlices translate 84.711998 85.452301
AlignSlices rotate 55.791611
sleep 2

AlignSlices setSliceNumber 3
AlignSlices translate 65.444000 -44.973999
AlignSlices rotate -17.832001
sleep 2

AlignSlices setSliceNumber 4
AlignSlices translate -194.723114 -0.16989
AlignSlices rotate 70.537994
AlignSlices mirror
sleep 2

AlignSlices setSliceNumber 5
AlignSlices translate 0.849701 -41.628399
AlignSlices rotate 4.53399
sleep 2

AlignSlices setSliceNumber 6
AlignSlices translate 194.279404 -8.92379
AlignSlices rotate -157.568802
sleep 2

AlignSlices setSliceNumber 7
AlignSlices translate -38.839401 -12.506706
AlignSlices rotate 95.527802
sleep 2

AlignSlices setSliceNumber 8
AlignSlices translate 52.000397 37.821404
AlignSlices rotate -148.204636
sleep 2

AlignSlices setSliceNumber 9
AlignSlices translate 10.459999 -54.860298 
AlignSlices rotate -22.761757
sleep 2

