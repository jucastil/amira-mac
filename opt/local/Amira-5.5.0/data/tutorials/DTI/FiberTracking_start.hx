# Amira Script
remove -all
remove gradient_0.3564_-0.8637_-0.3521 gradient_0.8602_-0.3606_-0.3521 gradient_0.3564_-0.3633_0.8579 gradient_0.3564_-0.8672_0.3536 gradient_0.8602_-0.3633_0.3536 gradient_0.3564_0.3633_-0.8579 gradient_0.3564_0.8672_-0.3536 gradient_0.8602_0.3633_-0.3536 gradient_0.0000_0.0000_0.0000 gradient_0.3564_0.3606_0.8556 gradient_0.3564_0.8637_0.3521 gradient_0.0000_0.0000_0._tensor ComputeTensor

# Create viewers
viewer setVertical 0

viewer 0 setBackgroundMode 1
viewer 0 setBackgroundColor 0.06 0.13 0.24
viewer 0 setBackgroundColor2 0.72 0.72 0.78
viewer 0 setTransparencyType 5
viewer 0 setAutoRedraw 0
viewer 0 show
mainWindow show

set hideNewModules 0
[ load ${SCRIPTDIR}/gradients-am/B0.am ] setLabel B0.am
#B0 setIconPosition 20 400
B0.am setTransform 0.998265 0.0575642 0.0121967 0 -0.0575686 0.998341 6.4075e-007 0 -0.0121766 -0.000702754 0.999925 0 -10.0696 3.05086 0.707304 1
B0.am fire
B0.am setViewerMask 16383
set hideNewModules 1

# set hideNewModules 0
[ load ${SCRIPTDIR}/gradients-am/gradient_0.3564_-0.8637_-0.3521.am ] setLabel gradient_0.3564_-0.8637_-0.3521.am
#gradient_0.3564_-0.8637_-0.3521 setIconPosition 20 160
gradient_0.3564_-0.8637_-0.3521.am setTransform 0.998267 0.057564 0.0121968 0 -0.0575683 0.998342 7.45058e-008 0 -0.0121766 -0.000702247 0.999926 0 -10.0697 3.05088 0.707292 1
gradient_0.3564_-0.8637_-0.3521.am fire
gradient_0.3564_-0.8637_-0.3521.am setViewerMask 16383

# set hideNewModules 0
[ load ${SCRIPTDIR}/gradients-am/gradient_0.8602_-0.3606_-0.3521.am ] setLabel gradient_0.8602_-0.3606_-0.3521.am
gradient_0.8602_-0.3606_-0.3521.am setIconPosition 20 190
gradient_0.8602_-0.3606_-0.3521.am setTransform 0.998267 0.057564 0.0121968 0 -0.0575683 0.998342 7.45058e-008 0 -0.0121766 -0.000702247 0.999926 0 -10.0697 3.05088 0.707292 1
gradient_0.8602_-0.3606_-0.3521.am fire
gradient_0.8602_-0.3606_-0.3521.am setViewerMask 16383

# set hideNewModules 0
[ load ${SCRIPTDIR}/gradients-am/gradient_0.3564_-0.3633_0.8579.am ] setLabel gradient_0.3564_-0.3633_0.8579.am
gradient_0.3564_-0.3633_0.8579.am setIconPosition 20 220
gradient_0.3564_-0.3633_0.8579.am setTransform 0.998267 0.057564 0.0121968 0 -0.0575683 0.998342 7.45058e-008 0 -0.0121766 -0.000702247 0.999926 0 -10.0697 3.05088 0.707292 1
gradient_0.3564_-0.3633_0.8579.am fire
gradient_0.3564_-0.3633_0.8579.am setViewerMask 16383

# set hideNewModules 0
[ load ${SCRIPTDIR}/gradients-am/gradient_0.3564_-0.8672_0.3536.am ] setLabel gradient_0.3564_-0.8672_0.3536.am
gradient_0.3564_-0.8672_0.3536.am setIconPosition 20 250
gradient_0.3564_-0.8672_0.3536.am setTransform 0.998267 0.057564 0.0121968 0 -0.0575683 0.998342 7.45058e-008 0 -0.0121766 -0.000702247 0.999926 0 -10.0697 3.05088 0.707292 1
gradient_0.3564_-0.8672_0.3536.am fire
gradient_0.3564_-0.8672_0.3536.am setViewerMask 16383

# set hideNewModules 0
[ load ${SCRIPTDIR}/gradients-am/gradient_0.8602_-0.3633_0.3536.am ] setLabel gradient_0.8602_-0.3633_0.3536.am
gradient_0.8602_-0.3633_0.3536.am setIconPosition 20 280
gradient_0.8602_-0.3633_0.3536.am setTransform 0.998267 0.057564 0.0121968 0 -0.0575683 0.998342 7.45058e-008 0 -0.0121766 -0.000702247 0.999926 0 -10.0697 3.05088 0.707292 1
gradient_0.8602_-0.3633_0.3536.am fire
gradient_0.8602_-0.3633_0.3536.am setViewerMask 16383

# set hideNewModules 0
[ load ${SCRIPTDIR}/gradients-am/gradient_0.3564_0.3633_-0.8579.am ] setLabel gradient_0.3564_0.3633_-0.8579.am
gradient_0.3564_0.3633_-0.8579.am setIconPosition 20 310
gradient_0.3564_0.3633_-0.8579.am setTransform 0.998267 0.057564 0.0121968 0 -0.0575683 0.998342 7.45058e-008 0 -0.0121766 -0.000702247 0.999926 0 -10.0697 3.05088 0.707292 1
gradient_0.3564_0.3633_-0.8579.am fire
gradient_0.3564_0.3633_-0.8579.am setViewerMask 16383

# set hideNewModules 0
[ load ${SCRIPTDIR}/gradients-am/gradient_0.3564_0.8672_-0.3536.am ] setLabel gradient_0.3564_0.8672_-0.3536.am
gradient_0.3564_0.8672_-0.3536.am setIconPosition 20 340
gradient_0.3564_0.8672_-0.3536.am setTransform 0.998267 0.057564 0.0121968 0 -0.0575683 0.998342 7.45058e-008 0 -0.0121766 -0.000702247 0.999926 0 -10.0697 3.05088 0.707292 1
gradient_0.3564_0.8672_-0.3536.am fire
gradient_0.3564_0.8672_-0.3536.am setViewerMask 16383

# set hideNewModules 0
[ load ${SCRIPTDIR}/gradients-am/gradient_0.8602_0.3633_-0.3536.am ] setLabel gradient_0.8602_0.3633_-0.3536.am
gradient_0.8602_0.3633_-0.3536.am setIconPosition 20 370
gradient_0.8602_0.3633_-0.3536.am setTransform 0.998267 0.057564 0.0121968 0 -0.0575683 0.998342 7.45058e-008 0 -0.0121766 -0.000702247 0.999926 0 -10.0697 3.05088 0.707292 1
gradient_0.8602_0.3633_-0.3536.am fire
gradient_0.8602_0.3633_-0.3536.am setViewerMask 16383

# set hideNewModules 0
[ load ${SCRIPTDIR}/gradients-am/gradient_0.3564_0.3606_0.8556.am ] setLabel gradient_0.3564_0.3606_0.8556.am
gradient_0.3564_0.3606_0.8556.am setIconPosition 20 430
gradient_0.3564_0.3606_0.8556.am setTransform 0.998267 0.057564 0.0121968 0 -0.0575683 0.998342 7.45058e-008 0 -0.0121766 -0.000702247 0.999926 0 -10.0697 3.05088 0.707292 1
gradient_0.3564_0.3606_0.8556.am fire
gradient_0.3564_0.3606_0.8556.am setViewerMask 16383

# set hideNewModules 0
[ load ${SCRIPTDIR}/gradients-am/gradient_0.3564_0.8637_0.3521.am ] setLabel gradient_0.3564_0.8637_0.3521.am
gradient_0.3564_0.8637_0.3521.am setIconPosition 20 460
gradient_0.3564_0.8637_0.3521.am setTransform 0.998267 0.057564 0.0121968 0 -0.0575683 0.998342 7.45058e-008 0 -0.0121766 -0.000702247 0.999926 0 -10.0697 3.05088 0.707292 1
gradient_0.3564_0.8637_0.3521.am fire
gradient_0.3564_0.8637_0.3521.am setViewerMask 16383

set hideNewModules 0
create HxComputeTensor {ComputeTensor}
#ComputeTensor setIconPosition 380 306
ComputeTensor data connect  
{ComputeTensor} createMorePorts 4
{ComputeTensor} fire
ComputeTensor data connect B0.am 
ComputeTensor S1 connect gradient_0.3564_-0.8637_-0.3521.am
ComputeTensor S2 connect gradient_0.8602_-0.3606_-0.3521.am
ComputeTensor S3 connect gradient_0.3564_-0.3633_0.8579.am
ComputeTensor S4 connect gradient_0.3564_-0.8672_0.3536.am
ComputeTensor S5 connect gradient_0.8602_-0.3633_0.3536.am
ComputeTensor S6 connect gradient_0.3564_0.3633_-0.8579.am
ComputeTensor S7 connect gradient_0.3564_0.8672_-0.3536.am
ComputeTensor S8 connect gradient_0.8602_0.3633_-0.3536.am
ComputeTensor S9 connect gradient_0.3564_0.3606_0.8556.am
ComputeTensor S10 connect gradient_0.3564_0.8637_0.3521.am
ComputeTensor fire
ComputeTensor diffusionweightingfactor setMinMax 0 -3.40282346638529e+038 3.40282346638529e+038
ComputeTensor diffusionweightingfactor setValue 0 1000
ComputeTensor Options setValue 0 0
ComputeTensor Options setToggleVisible 0 1
ComputeTensor Options setValue 1 0
ComputeTensor Options setToggleVisible 1 1
ComputeTensor Size setMinMax 0 -2147483648 2147483648
ComputeTensor Size setValue 0 3
ComputeTensor Size setMinMax 1 -2147483648 2147483648
ComputeTensor Size setValue 1 3
ComputeTensor Size setMinMax 2 -2147483648 2147483648
ComputeTensor Size setValue 2 3
ComputeTensor Sigma setMinMax 0 -3.40282346638529e+038 3.40282346638529e+038
ComputeTensor Sigma setValue 0 0.600000023841858
ComputeTensor Sigma setMinMax 1 -3.40282346638529e+038 3.40282346638529e+038
ComputeTensor Sigma setValue 1 0.600000023841858
ComputeTensor Sigma setMinMax 2 -3.40282346638529e+038 3.40282346638529e+038
ComputeTensor Sigma setValue 2 0.600000023841858
ComputeTensor G1 setMinMax 0 -3.40282346638529e+038 3.40282346638529e+038
ComputeTensor G1 setValue 0 0.356370985507965
ComputeTensor G1 setMinMax 1 -3.40282346638529e+038 3.40282346638529e+038
ComputeTensor G1 setValue 1 -0.863713026046753
ComputeTensor G1 setMinMax 2 -3.40282346638529e+038 3.40282346638529e+038
ComputeTensor G1 setValue 2 -0.352135986089706
ComputeTensor G2 setMinMax 0 -3.40282346638529e+038 3.40282346638529e+038
ComputeTensor G2 setValue 0 0.860233008861542
ComputeTensor G2 setMinMax 1 -3.40282346638529e+038 3.40282346638529e+038
ComputeTensor G2 setValue 1 -0.360554993152618
ComputeTensor G2 setMinMax 2 -3.40282346638529e+038 3.40282346638529e+038
ComputeTensor G2 setValue 2 -0.352135986089706
ComputeTensor G3 setMinMax 0 -3.40282346638529e+038 3.40282346638529e+038
ComputeTensor G3 setValue 0 0.356370985507965
ComputeTensor G3 setMinMax 1 -3.40282346638529e+038 3.40282346638529e+038
ComputeTensor G3 setValue 1 -0.363317996263504
ComputeTensor G3 setMinMax 2 -3.40282346638529e+038 3.40282346638529e+038
ComputeTensor G3 setValue 2 0.857904016971588
ComputeTensor G4 setMinMax 0 -3.40282346638529e+038 3.40282346638529e+038
ComputeTensor G4 setValue 0 0.356370985507965
ComputeTensor G4 setMinMax 1 -3.40282346638529e+038 3.40282346638529e+038
ComputeTensor G4 setValue 1 -0.867178976535797
ComputeTensor G4 setMinMax 2 -3.40282346638529e+038 3.40282346638529e+038
ComputeTensor G4 setValue 2 0.353552997112274
ComputeTensor G5 setMinMax 0 -3.40282346638529e+038 3.40282346638529e+038
ComputeTensor G5 setValue 0 0.860233008861542
ComputeTensor G5 setMinMax 1 -3.40282346638529e+038 3.40282346638529e+038
ComputeTensor G5 setValue 1 -0.363317996263504
ComputeTensor G5 setMinMax 2 -3.40282346638529e+038 3.40282346638529e+038
ComputeTensor G5 setValue 2 0.353552997112274
ComputeTensor G6 setMinMax 0 -3.40282346638529e+038 3.40282346638529e+038
ComputeTensor G6 setValue 0 0.356370985507965
ComputeTensor G6 setMinMax 1 -3.40282346638529e+038 3.40282346638529e+038
ComputeTensor G6 setValue 1 0.363317996263504
ComputeTensor G6 setMinMax 2 -3.40282346638529e+038 3.40282346638529e+038
ComputeTensor G6 setValue 2 -0.857904016971588
ComputeTensor G7 setMinMax 0 -3.40282346638529e+038 3.40282346638529e+038
ComputeTensor G7 setValue 0 0.356370985507965
ComputeTensor G7 setMinMax 1 -3.40282346638529e+038 3.40282346638529e+038
ComputeTensor G7 setValue 1 0.867178976535797
ComputeTensor G7 setMinMax 2 -3.40282346638529e+038 3.40282346638529e+038
ComputeTensor G7 setValue 2 -0.353552997112274
ComputeTensor G8 setMinMax 0 -3.40282346638529e+038 3.40282346638529e+038
ComputeTensor G8 setValue 0 0.860233008861542
ComputeTensor G8 setMinMax 1 -3.40282346638529e+038 3.40282346638529e+038
ComputeTensor G8 setValue 1 0.363317996263504
ComputeTensor G8 setMinMax 2 -3.40282346638529e+038 3.40282346638529e+038
ComputeTensor G8 setValue 2 -0.353552997112274
ComputeTensor G9 setMinMax 0 -3.40282346638529e+038 3.40282346638529e+038
ComputeTensor G9 setValue 0 0.356370985507965
ComputeTensor G9 setMinMax 1 -3.40282346638529e+038 3.40282346638529e+038
ComputeTensor G9 setValue 1 0.360554993152618
ComputeTensor G9 setMinMax 2 -3.40282346638529e+038 3.40282346638529e+038
ComputeTensor G9 setValue 2 0.855570018291473
ComputeTensor G10 setMinMax 0 -3.40282346638529e+038 3.40282346638529e+038
ComputeTensor G10 setValue 0 0.356370985507965
ComputeTensor G10 setMinMax 1 -3.40282346638529e+038 3.40282346638529e+038
ComputeTensor G10 setValue 1 0.863713026046753
ComputeTensor G10 setMinMax 2 -3.40282346638529e+038 3.40282346638529e+038
ComputeTensor G10 setValue 2 0.352135986089706
ComputeTensor G11 setMinMax 0 -3.40282346638529e+038 3.40282346638529e+038
ComputeTensor G11 setValue 0 1
ComputeTensor G11 setMinMax 1 -3.40282346638529e+038 3.40282346638529e+038
ComputeTensor G11 setValue 1 0
ComputeTensor G11 setMinMax 2 -3.40282346638529e+038 3.40282346638529e+038
ComputeTensor G11 setValue 2 0
ComputeTensor fire
ComputeTensor setViewerMask 16383
ComputeTensor setPickable 1

set hideNewModules 0
[ {ComputeTensor} create
 ] setLabel {B0._tensor}
# B0._tensor setIconPosition 21 490
B0._tensor master connect ComputeTensor
B0._tensor setTransform 0.998265 0.0575642 0.0121967 0 -0.0575686 0.998341 5.66244e-007 0 -0.0121766 -0.000702679 0.999925 0 -10.0696 3.05086 0.707304 1
B0._tensor fire
B0._tensor setViewerMask 16383

set hideNewModules 0
remove gradient_0.3564_-0.8637_-0.3521.am gradient_0.8602_-0.3606_-0.3521.am \
gradient_0.3564_-0.3633_0.8579.am gradient_0.3564_-0.8672_0.3536.am \
gradient_0.8602_-0.3633_0.3536.am gradient_0.3564_0.3633_-0.8579.am \
gradient_0.3564_0.8672_-0.3536.am gradient_0.8602_0.3633_-0.3536.am \
  gradient_0.3564_0.3606_0.8556.am \
gradient_0.3564_0.8637_0.3521.am

viewer 0 setCameraOrientation -0.34458 -0.930966 -0.120694 5.61018
viewer 0 setCameraPosition 128.286 -54.7837 152.406
viewer 0 setCameraFocalDistance 196.607
viewer 0 setCameraNearDistance 115.044
viewer 0 setCameraFarDistance 248.11
viewer 0 setCameraType perspective
viewer 0 setCameraHeightAngle 44.9023
viewer 0 setAutoRedraw 1
viewer 0 redraw

