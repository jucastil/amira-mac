# Amira Script
if { ![app hasLicense VRPack] } { 
	theMsg error "This script requires a VRPack license." 
	return 
} 

remove -all

if { [exists Tracking] } {
    Tracking setLabel VRSettings
}

if { ![exists VRSettings] } {
    create HxTracking
    VRSettings select
    VRSettings fire
}

proc Menu0 { id } {
    global AMIRA_ROOT
    switch $id \
        0 { load $AMIRA_ROOT/share/demo/medical/ctstack.hx } \
        1 { load $AMIRA_ROOT/share/demo/medical/isosurface.hx } \
        2 { load $AMIRA_ROOT/share/demo/medical/surf.hx } \
        3 { load $AMIRA_ROOT/share/demo/medical/tetra.hx } \
        4 { load $AMIRA_ROOT/share/demo/medical/gridcut.hx } \
        5 { load $AMIRA_ROOT/share/demo/medical/pseudocolor.hx } \
        6 { load $AMIRA_ROOT/share/demo/medical/splats.hx }
}

proc Menu1 { id } {
    global AMIRA_ROOT
    switch $id \
        0 { load $AMIRA_ROOT/share/demo/aneurysm/script-isosurface.hx } \
        1 { load $AMIRA_ROOT/share/demo/aneurysm/script-surface.hx } \
        2 { load $AMIRA_ROOT/share/demo/aneurysm/script-tetragrid.hx } \
        3 { load $AMIRA_ROOT/share/demo/aneurysm/script-vectors.hx } \
        4 { load $AMIRA_ROOT/share/demo/aneurysm/script-isl.hx } \
        5 { load $AMIRA_ROOT/share/demo/aneurysm/script-lic.hx } \
        6 { load $AMIRA_ROOT/share/demo/aneurysm/script-pressure1.hx }
}

proc Menu2 { id } {
    global AMIRA_ROOT
    switch $id \
        0 { load $AMIRA_ROOT/share/demo/recon/recon01.hx } \
        1 { load $AMIRA_ROOT/share/demo/recon/recon05.hx } \
        2 { load $AMIRA_ROOT/share/demo/recon/recon04.hx }
}

proc Menu3 { id } {
    global AMIRA_ROOT
    switch $id \
        0 { load $AMIRA_ROOT/share/demo/multichannel/projectionview.hx } \
        1 { load $AMIRA_ROOT/share/demo/multichannel/slicing.hx } \
        2 { load $AMIRA_ROOT/share/demo/multichannel/isosurfaces.hx } \
        3 { load $AMIRA_ROOT/share/demo/multichannel/voltex.hx }
}

menu reset

menu insertMenu -id 0 -text "Medical"
menu insertMenu -id 1 -text "CFD Aneurysm"
menu insertMenu -id 2 -text "Reconstruction"
menu insertMenu -id 3 -text "Multi-Channel"

menu 0 insertItem -id 0 -text "CT Slices" -proc "Menu0"
menu 0 insertItem -id 1 -text "Isosurface" -proc "Menu0"
menu 0 insertItem -id 2 -text "Surface model" -proc "Menu0"
menu 0 insertItem -id 4 -text "Oblique slice" -proc "Menu0"
menu 0 insertItem -id 5 -text "Pseudo-color" -proc "Menu0"

menu 1 insertItem -id 0 -text "CT-Data" -proc "Menu1"
menu 1 insertItem -id 1 -text "Surface" -proc "Menu1"
menu 1 insertItem -id 2 -text "Tetragrid" -proc "Menu1"
menu 1 insertItem -id 3 -text "Vectors" -proc "Menu1"
menu 1 insertItem -id 4 -text "ISL" -proc "Menu1"
menu 1 insertItem -id 5 -text "LIC" -proc "Menu1"
menu 1 insertItem -id 6 -text "Pressure" -proc "Menu1"


menu 2 insertItem -id 0 -text "Slice & Isosurface" -proc "Menu2"
menu 2 insertItem -id 1 -text "Volume Rendering" -proc "Menu2"
menu 2 insertItem -id 2 -text "Simplified Surface" -proc "Menu2"

menu 3 insertItem -id 0 -text "Projection view" -proc "Menu3"
menu 3 insertItem -id 1 -text "Slicing" -proc "Menu3"
menu 3 insertItem -id 2 -text "Isosurface" -proc "Menu3"
menu 3 insertItem -id 3 -text "Volume Rendering" -proc "Menu3"

# Make sure that a 3d config is active
if { [VRSettings isPlanarConfig] } {
    VRSettings loadConfig vrtest.cfg
}

# Show 3d menu and tracker emulator
VRSettings options setValue 2 1
VRSettings action setValue 0 0
VRSettings fire

viewer 0 show
theMain ignoreShow 1
 
Menu0 0

VRSettings select
