# Amira Script
remove -all
remove leaf.info AlignSlices

viewer 0 show
mainWindow show

set hideNewModules 0
[ load ${AMIRA_ROOT}/data/align/leaf.info ] setLabel leaf.info
leaf.info setIconPosition 20 10
leaf.info fire
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

AlignSlices setLandmark 0 0 229 178
AlignSlices setLandmark 0 1 390 279
AlignSlices setLandmark 1 0 469 172
AlignSlices setLandmark 1 1 339 327
AlignSlices setLandmark 2 0 664 329
AlignSlices setLandmark 2 1 455 306
AlignSlices setLandmark 3 0 664 164
AlignSlices setLandmark 3 1 468 208
AlignSlices setLandmark 4 0 357 416
AlignSlices setLandmark 4 1 461 254
AlignSlices setLandmark 5 0 455 388
AlignSlices setLandmark 5 1 364 213
AlignSlices setLandmark 6 0 259 53
AlignSlices setLandmark 6 1 279 254
AlignSlices setLandmark 7 0 622 195
AlignSlices setLandmark 7 1 420 193
AlignSlices setLandmark 8 0 104 235
AlignSlices setLandmark 8 1 268 342
AlignSlices setLandmark 9 0 112 409
AlignSlices setLandmark 9 1 304 443

AlignSlices redrawInhibit +1
AlignSlices setEditMode 1
AlignSlices setEditableSlice lower
AlignSlices redrawInhibit -1
AlignSlices setSliceNumber 0

sleep 2

AlignSlices setSliceNumber 1

sleep 2

AlignSlices setSliceNumber 2

sleep 2

AlignSlices setSliceNumber 3

sleep 2

AlignSlices redrawInhibit +1
AlignSlices setSliceNumber 4
AlignSlices redrawInhibit -1
AlignSlices mirror

sleep 2

AlignSlices setSliceNumber 5

sleep 2

AlignSlices setSliceNumber 6

sleep 2

AlignSlices setSliceNumber 7

sleep 2

AlignSlices setSliceNumber 8

sleep 2

AlignSlices setEditableSlice upper

sleep 2

AlignSlices redrawInhibit +1
AlignSlices setSliceNumber 1
AlignSlices setAlignMode 2
AlignSlices redrawInhibit -1
AlignSlices alignAll

