# Amira Script
remove -All

# Create viewers
viewer 0 show
viewer 0 setAutoRedraw 0

mainWindow show

set COARSEGRID [ load $AMIRA_ROOT/data/medical/reg005.tetragrid.am ]

create HxGridVolume GridVolume
GridVolume data connect $COARSEGRID
GridVolume options setValue 0 0
GridVolume drawStyle setValue 0
GridVolume select
GridVolume fire

viewer setCameraOrientation 0.931475 0.206105 0.299793 1.00282
viewer setCameraPosition 49.5157 -39.276 80.7458
viewer setCameraFocalDistance 84.8686
viewer 0 setAutoRedraw 1
viewer 0 redraw
sleep 3

# Add default selection (all)
GridVolume buffer setIndex 0
GridVolume fire
viewer 0 redraw
sleep 1.5

# Remove FAT
GridVolume options setValue 0 1
GridVolume materials setIndex 0 10
GridVolume fire
viewer 0 redraw
sleep 1.5
GridVolume buffer setIndex 1
GridVolume fire
viewer 0 redraw
sleep 1.5

# Remove MUSCLE
GridVolume materials setIndex 0 9
GridVolume fire
viewer 0 redraw
sleep 1.5
GridVolume buffer setIndex 1
GridVolume fire
viewer 0 redraw
sleep 1.5

# Remove INTESTINE
GridVolume materials setIndex 0 5
GridVolume fire
viewer 0 redraw
sleep 1.5
GridVolume buffer setIndex 1
GridVolume fire
viewer 0 redraw
sleep 1.5

# Remove BLADDER
GridVolume materials setIndex 0 1
GridVolume fire
viewer 0 redraw
sleep 1.5
GridVolume buffer setIndex 1
GridVolume fire
viewer 0 redraw
sleep 1.5

# Remove KIDNEY
GridVolume materials setIndex 0 7
GridVolume fire
viewer 0 redraw
sleep 1.5
GridVolume buffer setIndex 1
GridVolume fire
viewer 0 redraw
sleep 1.5

# Remove LIVER
GridVolume materials setIndex 0 8
GridVolume fire
viewer 0 redraw
sleep 1.5
GridVolume buffer setIndex 1
GridVolume fire
viewer 0 redraw
sleep 1.5

set muscle {
    357 658 902 1204 1502 1833 2149 2479 2815 3148 3461 3810 4186 4573 4965
    5355 5730 6108 6545 6998 7468 7933 8452 8937 9409 9870 10321 10773
    11197 11596 11988 12428 12784 13136 13491 13840 14209 14589 14978 15320
    15697 16109 16515 16914 17234 17548 17860 18186 18480 18767 19048 19325
    19610 19873 20169 20457 20727 21000 21271 21549 21834 22114 22390 22713
    23053 23390 23726 24029 24361 24678 24995 25296 25605 25892 26169
}

set fat {
    196 406 553 764 949 1146 1370 1545 1776 1994 2230 2501 2742 3042 3318
    3635 4050 4385 4753 5055 5403 5753 6034 6347 6643 6930 7242 7532 7864
    8173 8440 8788 9188 9629 10022 10390 10787 11138 11572 11957 12348
    12744 13072 13485 13907 14342 14844 15273 15755 16218 16659 17123 17544
    17986 18460 18941 19496 20003 20516 21012 21492 22064 22656 23296 23904
    24489 25067 25598 26305 26956 27571 28155 28642 29116 29543
}

set nFat 0
set nMuscle 0
viewer 0 setAutoRedraw 0

while { $nMuscle < 7 } {
    set num [ lindex $muscle $nMuscle ]
    incr nMuscle
    GridVolume selectTetra 17548 $num

    viewer 0 redraw
    update
}

while { $nMuscle < 75 } {
    set num [ lindex $muscle $nMuscle ]
    incr nMuscle
    GridVolume selectTetra 17548 $num

    set num [ lindex $fat $nFat ]
    incr nFat
    GridVolume selectTetra 43717 $num

    viewer 0 redraw
    update
}

while { $nFat < 75 } {
    set num [ lindex $fat $nFat ]
    incr nFat
    GridVolume selectTetra 43717 $num

    viewer 0 redraw
    update
}

viewer 0 setAutoRedraw 1

sleep 1.5
GridVolume colorMode setValue 2
GridVolume fire
viewer 0 redraw

echo "Script finished"
