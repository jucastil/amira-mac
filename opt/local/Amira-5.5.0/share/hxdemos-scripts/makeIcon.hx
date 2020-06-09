# Amira Script

# makeIcon: creates an icon for the current view
#
# 1) in case no arguments are given the snapshot
#    is made according to the current viewer size
# 2) in case width or height is given as parameter
#    the image is scaled using a Lanczos filter
# 3) in case width and height is given the viewer
#    will be resized (decoration trouble here)
# ------------------------------------------------
proc makeIcon { fileName {width 0} {height 0} } {

   # create png images
   set fileName "$fileName.png"

   set decorationWidth 62
   set decorationHeight 24

   set previousSize [ viewer getSize ]
   set oldWidth [ lindex $previousSize 0 ] 
   set oldHeight [ lindex $previousSize 1 ] 
   # echo "viewer size is $oldWidth x $oldHeight"
   set viewerResized 0

   # we don't want any decoration here
   viewer decoration 0

   # resize viewer in case width and height are given
   if { ($width > 0) && ($height > 0) &&
        (($width != $oldWidth) && ($height != $oldHeight)) } {
       # echo "setting viewer to $width x $height"
       viewer setSize $width $height
       set viewerResized 1
   }

   # snapshot of the current view
   # echo "doing snapshot for $fileName"
   viewer snapshot $fileName

   if { $viewerResized } {
       set oldWidth [ expr $oldWidth + $decorationWidth ]
       set oldHeight [ expr $oldHeight + $decorationHeight ]
       # echo "resetting viewer to $oldWidth x $oldHeight"
       viewer setSize $oldWidth $oldHeight
   }

   viewer decoration 1

   if { $viewerResized || ($width == $height) } return;

   # scale the image in case only one dimension was given
   if { $height > 0 } {
       set width [ expr int($oldWidth * double($height) / double($oldHeight)) ]
   } else {
       set height [ expr int($oldHeight * double($width) / double($oldWidth)) ]
   }

   # load snapshot image into the object pool
   set image [ load -png +box 0 $width 0 $height 0 1 +mode 10 $fileName ]

   # resample image to the given width or height using a Lanczos filter
   # echo "scaling image to $width x $height pixels"
   set resample [ create HxResample ]
   $resample data connect $image
   $resample filter setValue 4
   $resample fire
   $resample resolution setValue 0 $width
   $resample resolution setValue 1 $height
   $resample resolution setValue 2 1
   $resample resolution touch
   $resample action hit
   $resample fire
   set icon [ $resample getResult ]

   # save icon in png format
   $icon save PNG $fileName

   # for some strange reason, saving $icon results in renaming the
   # object, so we need to get the name of $icon again
   set icon [ $resample getResult ]

   remove $image;
   remove $resample
   remove $icon
}
