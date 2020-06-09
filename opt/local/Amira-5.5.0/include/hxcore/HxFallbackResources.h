/*
Copyright 1999-2013 Visualization Sciences Group, SAS
Copyright 1995-2013, ZIB Berlin
ALL RIGHTS RESERVED.

amira(R) is a registered trademark of ZIB.

amira(R) is being jointly developed by Zuse Institute Berlin and
Visualization Sciences Group, SAS.
Avizo® is a registered trademark of Visualization Sciences Group, SAS
HardCopy, MeshViz, VolumeViz, TerrainViz are marks of Visualization
Sciences Group, SAS 
Visualization Sciences Group, SAS is a source licensee of OpenGL®, Open Inventor® 
from Silicon Graphics, Inc. OpenGL® and Open Inventor® are 
registered trademark of Silicon Graphics, Inc. All other products and 
company names are trademarks or registered trademarks of 
their respective companies. 

FEI Visualization Sciences Group accepts no liability to any 
party for loss or damage caused by errors or omissions or by 
statements of any kind in this publication, whether such errors 
result from accident, negligence or any other cause. FEI Visualization
Sciences Group assumes  no liability for incidental or consequential
damages arising from the use of information in this publication.
FEI Visualization Sciences Group provides no 
warranties regarding the information contained in this 
publication, whether expressed, implied, or statutory, including 
implied warranties of merchantability or fitness for a 
particular purpose. 

FEI Visualization Sciences Group also does not assume any liability
for links from this publication to publications from other companies,
organizations or individuals. FEI Visualization Sciences Group does not
imply endorsement of any specific  company, organization or individual
through offering links to this content.
All information provided within this publication 
is subject to change at any time and is provided for 
informational purposes only by FEI Visualization Sciences Group.
Copyright 1994-2012 by Visualization Sciences Group, SAS Merignac, France.

*/

/// @addtogroup hxcore hxcore
/// @{
#if defined(__sgi) && !defined(TGS_OIV)
String fallbackResources[] = {
    "*useSchemes: all",
    "*sgiMode: true",
    NULL
};
#elif !defined(_WIN32)
String fallbackResources[] = {

    "*useSchemes: all",
    "*sgiMode: true",
#ifdef __linux
    "*background: #c1c1c1",
#endif
    "*HxMain*IvExamPrefTitle.labelString: Examiner Viewer Preference Sheet",
    "*IvFormPreference3.IvAutoClippingPlanes.labelString: Auto clipping planes ",
    "*IvFormPreference4.IvStereoViewing.labelString: Stereo Viewing",
    "*IvFormPreference4*IvCameraRotation.labelString: camera rotation:",

    "*IvFunctions2.IvHelp.labelString: Help",
    "*IvFunctions2.IvHome.labelString: Home",
    "*IvFunctions2.IvSetHome.labelString: Set Home",
    "*IvFunctions2.IvViewAll.labelString: View All",
    "*IvFunctions2.IvSeek.labelString: Seek",
    "*IvFunctions2.IvCopyView.labelString: Copy View",
    "*IvFunctions2.IvPasteView.labelString: Paste View",
    "*IvZoomForm.IvCameraZoom.labelString: Camera zoom",
    "*IvZoomForm.IvZoomSliderRangesFrom.labelString: Zoom slider ranges from:",
    "*IvZoomForm.IvTo.labelString: to:",
    "*IvZoomForm.IvZoomSlider.labelString: Zoom slider",
    "*IvZoomForm.IvZoomField.labelString: Zoom field",
    "*IvZoomForm.IvZoomFrom.labelString: Zoom from",
    "*IvZoomForm.IvZoomTo.labelString: Zoom to",

    "*HxMain*panel.form.*.BottomTrimForm.IvExamRotx.fontList: -adobe-helvetica-medium-r-normal-*-12-*",
    "*HxMain*panel.form.*.BottomTrimForm.IvExamRotx.labelString: Rotx",
    "*IvExamRotx.labelString: Rotx",
    "*HxMain*panel.form.*.BottomTrimForm.IvExamRoty.fontList: -adobe-helvetica-medium-r-normal-*-12-*",
    "*HxMain*panel.form.*.BottomTrimForm.IvExamRoty.labelString: Roty",
    "*IvExamRoty.labelString: Roty",
    "*HxMain*panel.form.*.BottomTrimForm.MotionZ.fontList: -adobe-helvetica-medium-r-normal-*-12-*",
    "*HxMain*panel.form.*.BottomTrimForm.MotionZ.labelString: Dolly",
    "*HxMain*IvExamPrefTitle.labelString: Examiner Viewer Preference Sheet",
    "*IvFormPreference3.IvAutoClippingPlanes.labelString: Auto clipping planes ",
    "*IvFormPreference4.IvStereoViewing.labelString: Stereo Viewing",
    "*IvFormPreference4*IvCameraRotation.labelString: camera rotation:",
    "*IvZoomForm.IvZoomTo.labelString: Zoom to",

    "*IvFormExaminer1.IvEnableSpinAnimation.labelString: Enable spin animation",
    "*IvFormExaminer1.IvShowPointOfRotationAxes.labelString: Show point of rotation axes",
    "*IvFormExaminer1.IvAxesSize.labelString: axes size",
    "*IvFormExaminer1.IvPixels.labelString: pixels",
    "*IvFormPreference1.IvSeconds.labelString: seconds",
    "*IvFormPreference1.IvSeekAnimationTime.labelString: Seek animation time",
    "*IvFormPreference1.IvSeekTo.labelString: Seek to:",
    "*IvFormPreference1.IvPoint.labelString: point",
    "*IvFormPreference1.IvObject.labelString: object",
    "*IvFormPreference2.IvSeekDistance.labelString: Seek distance:",
    "*IvFormPreference2.IvPercentage.labelString: percentage",
    "*IvFormPreference2.IvAbsolute.labelString: absolute",

    "*IvExamPopupTitle.labelString: Examiner Viewer",
    "*IvMenu.IvFunctions1.labelString: Functions",
    "*IvMenu.IvDrawStyle1.labelString: Draw Style",
    "*IvMenu.IvViewing.labelString: Viewing",
    "*IvMenu.IvDecoration.labelString: Decoration",
    "*IvMenu.IvHeadlight.labelString: Headlight",
    "*IvMenu.IvPreferences.labelString: Preferences ...",
    "*IvFunctions2.IvHome.labelString: Home",
    "*IvFunctions2.IvSetHome.labelString: Set Home",

    "*HxMain*IvDrawStyle1.labelString: Draw Style",
    "*HxMain*IvDrawStyle2.IvAsIs.labelString: as is",
    "*HxMain*IvDrawStyle2.IvHiddenLine.labelString: hidden line",
    "*HxMain*IvDrawStyle2.IvNoTexture.labelString: no texture",
    "*HxMain*IvDrawStyle2.IvLowResolution.labelString: low resolution",
    "*HxMain*IvDrawStyle2.IvWireFrame.labelString: wireframe",
    "*HxMain*IvDrawStyle2.IvPoints.labelString: points",
    "*HxMain*IvDrawStyle2.IvBoundingBoxNoDepth.labelString: bounding box ( no depth )",
    "*HxMain*IvDrawStyle2.IvMoveSameAsStill.labelString: move same as still",
    "*HxMain*IvDrawStyle2.IvMoveNoTexture.labelString:  move no texture.",
    "*HxMain*IvDrawStyle2.IvMoveLowRes.labelString: move low res",
    "*HxMain*IvDrawStyle2.IvMoveWireFrame.labelString: move wireframe",
    "*HxMain*IvDrawStyle2.IvMoveLowResWireFrameNoDepth.labelString: move low res wire frame ( no depth )",
    "*HxMain*IvDrawStyle2.IvMovePoints.labelString: move points",
    "*HxMain*IvDrawStyle2.IvMoveLowResPointsNoDepth.labelString: move low res points ( no depth )",
    "*HxMain*IvDrawStyle2.IvMoveBoundingBoxNoDepth.labelString: move bounding box ( no depth )",
    "*HxMain*IvDrawStyle2.IvSingleBuffer.labelString: single buffer",
    "*HxMain*IvDrawStyle2.IvDoubleBuffer.labelString: Double buffer",
    "*HxMain*IvDrawStyle2.IvInteractiveBuffer.labelString: interactive buffer",

    "*IvExamDolly.labelString: Dolly",
    "*IvExamZoom.labelString: Zoom",
    "*IvNearPlane.labelString: near plane:",
    "*IvFarPlane.labelString: far  plane:",

    "*HxMain*IvDLMenuBar*IvEdit.fontList: -adobe-helvetica-bold-o-normal-*-14-100-*-*-*-*-*-*",
    "*HxMain*IvDLMenuBar*IvEdit.labelString: Edit",
    "*HxMain*IvCEMenuBar*IvEdit.fontList: -adobe-helvetica-bold-o-normal-*-14-100-*-*-*-*-*-*",
    "*HxMain*IvCEMenuBar*IvEdit.labelString: Edit",

    "*HxMain*IvDLMenuBar*IvColorEditor.labelString: Color Editor",
    "*HxMain*IvDLMenuBar*IvCopy.labelString: Copy",
    "*HxMain*IvDLMenuBar*IvPaste.labelString: Paste",
    "*HxMain*IvDLMenuBar*IvHelp.labelString: Help",

    "*HxMain*IvDirectLightInten.labelString: Inten",
    "*HxMain*IvDirectLightColorEditor.labelString: Directional light color",

    "*HxMain*IvColorEditorCont.labelString: Inten",
    "*HxMain*IvColorEditor.labelString: Inten",

    "*HxMain*IvColorEditorR.labelString: R",
    "*HxMain*IvColorEditorG.labelString: G",
    "*HxMain*IvColorEditorB.labelString: B",
    "*HxMain*IvColorEditorH.labelString: H",
    "*HxMain*IvColorEditorS.labelString: S",
    "*HxMain*IvColorEditorV.labelString: V",
    "!*HxMain*IvColorEditorRight.labelString:",
    "!*HxMain*IvColorEditorSwitch.labelString:",
    "*HxMain*IvColorEditorCont.labelString: Continous",
    "*HxMain*IvColorEditorManu.labelString: Manual",
    "*HxMain*IvColorEditorWysi.labelString: WYSIWYG",
    "*HxMain*IvColorEditorCopy.labelString: Copy",
    "*HxMain*IvColorEditorPaste.labelString: Paste",
    "*HxMain*IvColorEditorHelp.labelString: Help",
    "*HxMain*IvColorEditorNone.labelString: None",
    "*HxMain*IvColorEditorValue.labelString: Value",
    "*HxMain*IvColorEditorRGB.labelString: RGB",
    "*HxMain*IvColorEditorHSV.labelString: HSV",
    "*HxMain*IvColorEditorRGBV.labelString: RGB V",
    "*HxMain*IvColorEditorRGBHSV.labelString: RGB HSV",

    "*IvMenu*fontList: -adobe-helvetica-bold-*-normal-*-14-100-*-*-*-*-*-*",
    "*IvDrawStyle2*fontList: -adobe-helvetica-bold-*-normal-*-14-100-*-*-*-*-*-*",
    "*IvFunctions2*fontList: -adobe-helvetica-bold-*-normal-*-14-100-*-*-*-*-*-*",
    "*IvFormExaminer1*fontList: -adobe-helvetica-medium-r-normal-*-14-*",
    "*IvFormPreference1*fontList: -adobe-helvetica-medium-r-normal-*-14-*",
    "*IvFormPreference2*fontList: -adobe-helvetica-medium-r-normal-*-14-*",
    "*IvFormPreference3*fontList: -adobe-helvetica-medium-r-normal-*-14-*",
    "*IvFormPreference4*fontList: -adobe-helvetica-medium-r-normal-*-14-*",
    "*IvZoomForm*fontList: -adobe-helvetica-medium-r-normal-*-14-*",
    "*IvSeek*fontList: -adobe-helvetica-medium-r-normal-*-14-*",

    "*IvStereoPreference.title: Stereo Preferences",
    "*IvStereoPreference.IvStereoPrefMainForm.IvStereoPrefTopForm.IvStereoPrefRowCol.IvStereoPrefUseStereo.labelString: Use stereo",
    "*IvPulldownMenuRatioWin.IvRawStereo.labelString: Raw Stereo (OpenGL)",
    "*IvPulldownMenuRatioWin.IvHorizontalInterlacedF.labelString: Horizontal Interlaced (Fast)",
    "*IvPulldownMenuRatioWin.IvVerticalInterlacedF.labelString: Vertical Interlaced (Fast)",
    "*IvPulldownMenuRatioWin.IvHorizontalInterlacedB.labelString: Horizontal Interlaced (Best)",
    "*IvPulldownMenuRatioWin.IvVerticalInterlacedB.labelString: Vertical Interlaced (Best)",
    "*IvPulldownMenuRatioWin.IvHorizontalHalfFilledScreen.labelString: Horizontal Half Filled Screen",
    "*IvPulldownMenuRatioWin.IvHorizontalHalfScreen.labelString: Horizontal Half Screen",
    "*IvPulldownMenuRatioWin.IvVerticalHalfFilledScreen.labelString: Vertical Half Filled Screen",
    "*IvPulldownMenuRatioWin.IvVerticalHalfScreen.labelString: Vertical Half Screen",
    "*IvPulldownMenuRatioWin.IvRedCyanStereo.labelString: Red/Cyan Stereo",
    "*IvPulldownMenuRatioWin.IvBlueYellowStereo.labelString: Blue/Yellow Stereo",
    "*IvPulldownMenuRatioWin.IvGreenMagentaStereo.labelString: Green/Magenta Stereo",

    "*IvAdjustFrame*IvAdjustRowCol.IvAdjustStereoToggle.labelString: Reverse left and right views",

    "*IvScaleParallax.titleString: Zero parallax balance",
    "*IvScaleCamOffset.titleString: Cameras offset",


    NULL
};
#endif

/// @}
