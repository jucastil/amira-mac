/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T.MEHAMLI (Feb 2008)
**=======================================================================*/


#ifndef SOXT2SOWX_H
#define SOXT2SOWX_H

//////////////////////////////////////////////////////////////////////////////
//
//  Header: SoXt2SoWx
//
//////////////////////////////////////////////////////////////////////////////

#if defined(_WIN32) || defined(__APPLE__)
#  ifndef XAnyEvent
#    define XAnyEvent wxEvent
#  endif
#endif

#ifndef SoXt
#define SoXt																SoWx
#define SoXtAmbientColorMultiSlider					#error "No wxWidgets port"
#define SoXtAmbientColorSliderModule				#error "No wxWidgets port"
#define SoXtBitmapButton										SoWxBitmapToggleButton
#define SoXtCenterMultiSlider								#error "No wxWidgets port"
#define SoXtCenterSliderModule							#error "No wxWidgets port"
#define SoXtClipboard												#error "No wxWidgets port"
#define SoXtClipboardPasteCB								#error "No wxWidgets port"
#define SoXtColEd														#error "No wxWidgets port"
#define SoXtColPatch												#error "No wxWidgets port"
#define SoXtColSldr													#error "No wxWidgets port"
#define SoXtColWhl													#error "No wxWidgets port"
#define SoXtCollisionViewer									#error "No wxWidgets port"
#define SoXtCollisionViewerCB								#error "No wxWidgets port"
#define SoXtComp														SoWxComp
#define SoXtComponent												SoWxComponent
#define SoXtComponentCB											SoWxComponentCB
#define SoXtComponentVisibilityCB						SoWxComponentVisibilityCB
#define SoXtComponents											SoWxComponents
#define SoXtConstrVwr												SoWxConstrVwr
#define SoXtConstrainedViewer								SoWxConstrainedViewer
#define SoXtDevice													SoWxDevice
#define SoXtDiffuseColorMultiSlider					#error "No wxWidgets port"
#define SoXtDiffuseColorSliderModule				#error "No wxWidgets port"
#define SoXtDirLtEd													#error "No wxWidgets port"
#define SoXtDirectionalLightEditor					#error "No wxWidgets port"
#define SoXtDirectionalLightEditorCB				#error "No wxWidgets port"
#define SoXtEmissiveColorMultiSlider				#error "No wxWidgets port"
#define SoXtEmissiveColorSliderModule				#error "No wxWidgets port"
#define SoXtEventHandler										#error "No wxWidgets port"
#define SoXtExamVwr													SoWxExamVwr
#define SoXtExamVwrCreate										SoWxExamVwrCreate
#define SoXtExamVwrCreateStd								SoWxExamVwrCreateStd
#define SoXtExaminerViewer									SoWxExaminerViewer
#define SoXtFileSelectionDialog							#error "No wxWidgets port"
#define SoXtFloatText												#error "No wxWidgets port"
#define SoXtFlyViewer												SoWxFlyViewer
#define SoXtFlyVwr													SoWxFlyVwr
#define SoXtFlyVwrCreate										SoWxFlyVwrCreate
#define SoXtFlyVwrCreateStd									SoWxFlyVwrCreateStd
#define SoXtFovMultiSlider									#error "No wxWidgets port"
#define SoXtFullViewer											SoWxFullViewer
#define SoXtFullVwr													SoWxFullVwr
#define SoXtGDI															#error "No wxWidgets port"
#define SoXtGDIThumbWheel										#error "No wxWidgets port"
#define SoXtGDIThumbWheelCB									#error "No wxWidgets port"
#define SoXtGDIThumbWheelCBData							#error "No wxWidgets port"
#define SoXtGDIWidget												#error "No wxWidgets port"
#define SoXtGL															SoWxGL
#define SoXtGLWidget												SoWxGLWidget
#define SoXtInputFocus											#error "No wxWidgets port"
#define SoXtKeyboard												SoWxKeyboard
#define SoXtLight														#error "No wxWidgets port"
#define SoXtLightColorMultiSlider						#error "No wxWidgets port"
#define SoXtLightColorSliderModule					#error "No wxWidgets port"
#define SoXtLightIntensityMultiSlider				#error "No wxWidgets port"
#define SoXtLightIntensitySliderModule			#error "No wxWidgets port"
#define SoXtLightSliderSet									#error "No wxWidgets port"
#define SoXtLtSldrs													#error "No wxWidgets port"
#define SoXtMMSliderMax											#error "No wxWidgets port"
#define SoXtMMSliderMin											#error "No wxWidgets port"
#define SoXtMaterial												#error "No wxWidgets port"
#define SoXtMaterialEditor									#error "No wxWidgets port"
#define SoXtMaterialEditorCB								#error "No wxWidgets port"
#define SoXtMaterialList										#error "No wxWidgets port"
#define SoXtMaterialListCB									#error "No wxWidgets port"
#define SoXtMaterialSliderSet								#error "No wxWidgets port"
#define SoXtMessageHook											#error "No wxWidgets port"
#define SoXtMinMaxSlider										#error "No wxWidgets port"
#define SoXtMouse														SoWxMouse
#define SoXtMPRenderArea										SoWxRenderArea
#define SoXtMPRenderAreaEventCB							SoWxRenderAreaEventCB
#define SoXtMpViewerCB											SoWxViewerCB
#define SoXtMPViewer												SoWxViewer
#define SoXtMPExaminerViewer								SoWxExaminerViewer
#define SoXtMPFullViewer										SoWxFullViewer
#define SoXtMPGLWidget											SoWxGLWidget
#define SoXtMPRenderArea										SoWxRenderArea
#define SoXtMPViewerCameraTypeChangeCB			#error "No wxWidgets port"
#define SoXtMPViewerFPSCB										SoWxViewerFPSCB
#define SoXtMPViewerDecimationPercentageCB	SoWxViewerDecimationPercentageCB
#define SoXtMtlEd														#error "No wxWidgets port"
#define SoXtMtlList													#error "No wxWidgets port"
#define SoXtMtlSldrs												#error "No wxWidgets port"
#define SoXtMultiSlider											#error "No wxWidgets port"
#define SoXtPlaneViewer											SoWxPlaneViewer
#define SoXtPlnVwr													SoWxPlnVwr
#define SoXtPlnVwrCreate										SoWxPlnVwrCreate
#define SoXtPlnVwrCreateStd									SoWxPlnVwrCreateStd
#define SoXtPrintDialog											#error "No wxWidgets port"
#define SoXtPrintDialogCB										#error "No wxWidgets port"
#define SoXtPrintDlog												#error "No wxWidgets port"
#define SoXtPushButton											#error "No wxWidgets port"
#define SoXtRA															SoWxRA
#define SoXtRACreate												SoWxRACreate
#define SoXtRACreateStd											SoWxRACreateStd
#define SoXtRenderArea											SoWxRenderArea
#define SoXtRenderAreaEventCB								SoWxRenderAreaEventCB
#define SoXtResource												#error "No wxWidgets port"
#define SoXtRotateMultiSlider								#error "No wxWidgets port"
#define SoXtRotateSliderModule							#error "No wxWidgets port"
#define SoXtScaleMultiSlider								#error "No wxWidgets port"
#define SoXtScaleOrientationMultiSlider			#error "No wxWidgets port"
#define SoXtScaleOrientationSliderModule    #error "No wxWidgets port"
#define SoXtScaleSliderModule								#error "No wxWidgets port"
#define SoXtShininessMultiSlider						#error "No wxWidgets port"
#define SoXtShininessSliderModule						#error "No wxWidgets port"
#define SoXtSldr														#error "No wxWidgets port"
#define SoXtSldrs														#error "No wxWidgets port"
#define SoXtSldrsBase												#error "No wxWidgets port"
#define SoXtSlider													#error "No wxWidgets port"
#define SoXtSliderControlPanel							#error "No wxWidgets port"
#define SoXtSliderModule										#error "No wxWidgets port"
#define SoXtSliderSet												#error "No wxWidgets port"
#define SoXtSliderSetBase										#error "No wxWidgets port"
#define SoXtSliderTool											#error "No wxWidgets port"
#define SoXtSpaceball												#error "No wxWidgets port"
#define SoXtSpecularColorMultiSlider				#error "No wxWidgets port"
#define SoXtSpecularColorSliderModule				#error "No wxWidgets port"
#define SoXtThumbWheel											SoWxThumbWheel
#define SoXtThumbWheelCB										SoWxThumbWheelCB
#define SoXtThumbWheelCBData								SoWxThumbWheelCBData
#define SoXtTransMultiSlider								#error "No wxWidgets port"
#define SoXtTransSliderModule								#error "No wxWidgets port"
#define SoXtTransform												#error "No wxWidgets port"
#define SoXtTransformSliderSet							#error "No wxWidgets port"
#define SoXtTransparencyMultiSlider					#error "No wxWidgets port"
#define SoXtTransparencySliderModule				#error "No wxWidgets port"
#define SoXtViewer													SoWxViewer
#define SoXtViewerCB												SoWxViewerCB
#define SoXtViewerCameraTypeChangeCB				SoWxViewerCameraTypeChangeCB
#define SoXtViewerFPSCB											SoWxViewerFPSCB
#define SoXtViewerDecimationPercentageCB		SoWxViewerDecimationPercentageCB
#define SoXtVwr															SoWxVwr
#define SoXtWalkViewer											SoWxWalkViewer
#define SoXtWalkVwr													SoWxWalkVwr
#define SoXtWalkVwrCreate										SoWxWalkVwrCreate
#define SoXtWalkVwrCreateStd								SoWxWalkVwrCreateStd
#define SoXtXfSldrs													#error "No wxWidgets port"
#define SoXtColorEditor											#error "No wxWidgets port"
#define SoXtColorEditorCB										#error "No wxWidgets port"
#define SoXtColorPatch											#error "No wxWidgets port"
#define SoXtColorSlider											#error "No wxWidgets port"
#define SoXtColorWheel											#error "No wxWidgets port"
#define SoXtColorWheelCB										#error "No wxWidgets port"
#define SoXtSlider													#error "No wxWidgets port"
#define SoXtSliderCB												#error "No wxWidgets port"
#endif

#endif //SOXT2SOWX_H
