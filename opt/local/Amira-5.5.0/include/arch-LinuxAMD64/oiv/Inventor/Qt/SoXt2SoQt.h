/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef __SOXT2SOQT_H__
#define __SOXT2SOQT_H__

#if defined(_WIN32) || defined(__APPLE__)
#  ifndef XAnyEvent
#    define XAnyEvent QEvent
#  endif
#endif

#ifndef SoXt
#define SoXt    SoQt
#define SoXtAmbientColorMultiSlider     SoQtAmbientColorMultiSlider
#define SoXtAmbientColorSliderModule    SoQtAmbientColorSliderModule
#define SoXtBitmapButton        SoQtBitmapButton
#define SoXtCenterMultiSlider   SoQtCenterMultiSlider
#define SoXtCenterSliderModule  SoQtCenterSliderModule
#define SoXtClipboard   SoQtClipboard
#define SoXtClipboardPasteCB    SoQtClipboardPasteCB
#define SoXtColEd       SoQtColEd
#define SoXtColPatch    SoQtColPatch
#define SoXtColSldr     SoQtColSldr
#define SoXtColWhl      SoQtColWhl
#define SoXtCollisionViewer SoQtCollisionViewer
#define SoXtCollisionViewerCB SoQtCollisionViewerCB
#define SoXtComp        SoQtComp
#define SoXtComponent   SoQtComponent
#define SoXtComponentCB SoQtComponentCB
#define SoXtComponentVisibilityCB       SoQtComponentVisibilityCB
#define SoXtComponents  SoQtComponents
#define SoXtConstrVwr   SoQtConstrVwr
#define SoXtConstrainedViewer   SoQtConstrainedViewer
#define SoXtDevice      SoQtDevice
#define SoXtDiffuseColorMultiSlider     SoQtDiffuseColorMultiSlider
#define SoXtDiffuseColorSliderModule    SoQtDiffuseColorSliderModule
#define SoXtDirLtEd     SoQtDirLtEd
#define SoXtDirectionalLightEditor      SoQtDirectionalLightEditor
#define SoXtDirectionalLightEditorCB    SoQtDirectionalLightEditorCB
#define SoXtEmissiveColorMultiSlider    SoQtEmissiveColorMultiSlider
#define SoXtEmissiveColorSliderModule   SoQtEmissiveColorSliderModule
#define SoXtEventHandler        SoQtEventHandler
#define SoXtExamVwr     SoQtExamVwr
#define SoXtExamVwrCreate       SoQtExamVwrCreate
#define SoXtExamVwrCreateStd    SoQtExamVwrCreateStd
#define SoXtExaminerViewer      SoQtExaminerViewer
#define SoXtFileSelectionDialog SoQtFileSelectionDialog
#define SoXtFloatText   SoQtFloatText
#define SoXtFlyViewer   SoQtFlyViewer
#define SoXtFlyVwr      SoQtFlyVwr
#define SoXtFlyVwrCreate        SoQtFlyVwrCreate
#define SoXtFlyVwrCreateStd     SoQtFlyVwrCreateStd
#define SoXtFovMultiSlider      SoQtFovMultiSlider
#define SoXtFullViewer  SoQtFullViewer
#define SoXtFullVwr     SoQtFullVwr
#define SoXtGDI SoQtGDI
#define SoXtGDIThumbWheel       SoQtGDIThumbWheel
#define SoXtGDIThumbWheelCB     SoQtGDIThumbWheelCB
#define SoXtGDIThumbWheelCBData SoQtGDIThumbWheelCBData
#define SoXtGDIWidget   SoQtGDIWidget
#define SoXtGL  SoQtGL
#define SoXtGLWidget    SoQtGLWidget
#define SoXtInputFocus  SoQtInputFocus
#define SoXtKeyboard    SoQtKeyboard
#define SoXtLight       SoQtLight
#define SoXtLightColorMultiSlider       SoQtLightColorMultiSlider
#define SoXtLightColorSliderModule      SoQtLightColorSliderModule
#define SoXtLightIntensityMultiSlider   SoQtLightIntensityMultiSlider
#define SoXtLightIntensitySliderModule  SoQtLightIntensitySliderModule
#define SoXtLightSliderSet      SoQtLightSliderSet
#define SoXtLtSldrs     SoQtLtSldrs
#define SoXtMMSliderMax SoQtMMSliderMax
#define SoXtMMSliderMin SoQtMMSliderMin
#define SoXtMaterial    SoQtMaterial
#define SoXtMaterialEditor      SoQtMaterialEditor
#define SoXtMaterialEditorCB    SoQtMaterialEditorCB
#define SoXtMaterialList        SoQtMaterialList
#define SoXtMaterialListCB      SoQtMaterialListCB
#define SoXtMaterialSliderSet   SoQtMaterialSliderSet
#define SoXtMessageHook SoQtMessageHook
#define SoXtMinMaxSlider        SoQtMinMaxSlider
#define SoXtMouse       SoQtMouse
#define SoXtMPRenderArea        SoQtRenderArea
#define SoXtMPRenderAreaEventCB SoQtRenderAreaEventCB
#define SoXtMpViewerCB SoQtViewerCB
#define SoXtMPViewer    SoQtViewer
#define SoXtMPExaminerViewer SoQtExaminerViewer
#define SoXtMPFullViewer SoQtFullViewer
#define SoXtMPGLWidget SoQtGLWidget
#define SoXtMPRenderArea SoQtRenderArea
#define SoXtMPViewerCameraTypeChangeCB  SoQtViewerCameraTypeChangeCB
#define SoXtMPViewerFPSCB SoQtViewerFPSCB
#define SoXtMPViewerDecimationPercentageCB SoQtViewerDecimationPercentageCB
#define SoXtMtlEd       SoQtMtlEd
#define SoXtMtlList     SoQtMtlList
#define SoXtMtlSldrs    SoQtMtlSldrs
#define SoXtMultiSlider SoQtMultiSlider
#define SoXtPlaneViewer SoQtPlaneViewer
#define SoXtPlnVwr      SoQtPlnVwr
#define SoXtPlnVwrCreate        SoQtPlnVwrCreate
#define SoXtPlnVwrCreateStd     SoQtPlnVwrCreateStd
#define SoXtPrintDialog SoQtPrintDialog
#define SoXtPrintDialogCB       SoQtPrintDialogCB
#define SoXtPrintDlog   SoQtPrintDlog
#define SoXtPushButton  SoQtPushButton
#define SoXtRA  SoQtRA
#define SoXtRACreate    SoQtRACreate
#define SoXtRACreateStd SoQtRACreateStd
#define SoXtRenderArea  SoQtRenderArea
#define SoXtRenderAreaEventCB   SoQtRenderAreaEventCB
#define SoXtResource    SoQtResource
#define SoXtRotateMultiSlider   SoQtRotateMultiSlider
#define SoXtRotateSliderModule  SoQtRotateSliderModule
#define SoXtScaleMultiSlider    SoQtScaleMultiSlider
#define SoXtScaleOrientationMultiSlider SoQtScaleOrientationMultiSlider
#define SoXtScaleOrientationSliderModule        SoQtScaleOrientationSliderModule
#define SoXtScaleSliderModule   SoQtScaleSliderModule
#define SoXtShininessMultiSlider        SoQtShininessMultiSlider
#define SoXtShininessSliderModule       SoQtShininessSliderModule
#define SoXtSldr        SoQtSldr
#define SoXtSldrs       SoQtSldrs
#define SoXtSldrsBase   SoQtSldrsBase
#define SoXtSlider      SoQtSlider
#define SoXtSliderControlPanel  SoQtSliderControlPanel
#define SoXtSliderModule        SoQtSliderModule
#define SoXtSliderSet   SoQtSliderSet
#define SoXtSliderSetBase       SoQtSliderSetBase
#define SoXtSliderTool  SoQtSliderTool
#define SoXtSpaceball      SoQtSpaceball
#define SoXtSpecularColorMultiSlider    SoQtSpecularColorMultiSlider
#define SoXtSpecularColorSliderModule   SoQtSpecularColorSliderModule
#define SoXtThumbWheel  SoQtThumbWheel
#define SoXtThumbWheelCB        SoQtThumbWheelCB
#define SoXtThumbWheelCBData    SoQtThumbWheelCBData
#define SoXtTransMultiSlider    SoQtTransMultiSlider
#define SoXtTransSliderModule   SoQtTransSliderModule
#define SoXtTransform   SoQtTransform
#define SoXtTransformSliderSet  SoQtTransformSliderSet
#define SoXtTransparencyMultiSlider     SoQtTransparencyMultiSlider
#define SoXtTransparencySliderModule    SoQtTransparencySliderModule
#define SoXtViewer      SoQtViewer
#define SoXtViewerCB    SoQtViewerCB
#define SoXtViewerCameraTypeChangeCB    SoQtViewerCameraTypeChangeCB
#define SoXtViewerFPSCB SoQtViewerFPSCB
#define SoXtViewerDecimationPercentageCB SoQtViewerDecimationPercentageCB
#define SoXtVwr SoQtVwr
#define SoXtWalkViewer  SoQtWalkViewer
#define SoXtWalkVwr     SoQtWalkVwr
#define SoXtWalkVwrCreate       SoQtWalkVwrCreate
#define SoXtWalkVwrCreateStd    SoQtWalkVwrCreateStd
#define SoXtXfSldrs     SoQtXfSldrs
#define SoXtColorEditor SoQtColorEditor
#define SoXtColorEditorCB       SoQtColorEditorCB
#define SoXtColorPatch  SoQtColorPatch
#define SoXtColorSlider SoQtColorSlider
#define SoXtColorWheel  SoQtColorWheel
#define SoXtColorWheelCB        SoQtColorWheelCB
#define SoXtSlider      SoQtSlider
#define SoXtSliderCB    SoQtSliderCB
#endif

#endif //__SOXT2SOQT_H__
