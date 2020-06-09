/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef __SOXT2SOWIN_H__
#define __SOXT2SOWIN_H__

#ifdef _WIN32

#ifndef SoXt
#define SoXt    SoWin
#define SoXtAmbientColorMultiSlider     SoWinAmbientColorMultiSlider
#define SoXtAmbientColorSliderModule    SoWinAmbientColorSliderModule
#define SoXtBitmapButton        SoWinBitmapButton
#define SoXtCenterMultiSlider   SoWinCenterMultiSlider
#define SoXtCenterSliderModule  SoWinCenterSliderModule
#define SoXtClipboard   SoWinClipboard
#define SoXtClipboardPasteCB    SoWinClipboardPasteCB
#define SoXtColEd       SoWinColEd
#define SoXtColPatch    SoWinColPatch
#define SoXtColSldr     SoWinColSldr
#define SoXtColWhl      SoWinColWhl
#define SoXtCollisionViewer SoWinCollisionViewer
#define SoXtCollisionViewerCB SoWinCollisionViewerCB
#define SoXtComp        SoWinComp
#define SoXtComponent   SoWinComponent
#define SoXtComponentCB SoWinComponentCB
#define SoXtComponentVisibilityCB       SoWinComponentVisibilityCB
#define SoXtComponents  SoWinComponents
#define SoXtConstrVwr   SoWinConstrVwr
#define SoXtConstrainedViewer   SoWinConstrainedViewer
#define SoXtDevice      SoWinDevice
#define SoXtDiffuseColorMultiSlider     SoWinDiffuseColorMultiSlider
#define SoXtDiffuseColorSliderModule    SoWinDiffuseColorSliderModule
#define SoXtDirLtEd     SoWinDirLtEd
#define SoXtDirectionalLightEditor      SoWinDirectionalLightEditor
#define SoXtDirectionalLightEditorCB    SoWinDirectionalLightEditorCB
#define SoXtEmissiveColorMultiSlider    SoWinEmissiveColorMultiSlider
#define SoXtEmissiveColorSliderModule   SoWinEmissiveColorSliderModule
#define SoXtEventHandler        SoWinEventHandler
#define SoXtExamVwr     SoWinExamVwr
#define SoXtExamVwrCreate       SoWinExamVwrCreate
#define SoXtExamVwrCreateStd    SoWinExamVwrCreateStd
#define SoXtExaminerViewer      SoWinExaminerViewer
#define SoXtFileSelectionDialog SoWinFileSelectionDialog
#define SoXtFloatText   SoWinFloatText
#define SoXtFlyViewer   SoWinFlyViewer
#define SoXtFlyVwr      SoWinFlyVwr
#define SoXtFlyVwrCreate        SoWinFlyVwrCreate
#define SoXtFlyVwrCreateStd     SoWinFlyVwrCreateStd
#define SoXtFovMultiSlider      SoWinFovMultiSlider
#define SoXtFullViewer  SoWinFullViewer
#define SoXtFullVwr     SoWinFullVwr
#define SoXtGDI SoWinGDI
#define SoXtGDIThumbWheel       SoWinGDIThumbWheel
#define SoXtGDIThumbWheelCB     SoWinGDIThumbWheelCB
#define SoXtGDIThumbWheelCBData SoWinGDIThumbWheelCBData
#define SoXtGDIWidget   SoWinGDIWidget
#define SoXtGL  SoWinGL
#define SoXtGLWidget    SoWinGLWidget
#define SoXtInputFocus  SoWinInputFocus
#define SoXtKeyboard    SoWinKeyboard
#define SoXtLight       SoWinLight
#define SoXtLightColorMultiSlider       SoWinLightColorMultiSlider
#define SoXtLightColorSliderModule      SoWinLightColorSliderModule
#define SoXtLightIntensityMultiSlider   SoWinLightIntensityMultiSlider
#define SoXtLightIntensitySliderModule  SoWinLightIntensitySliderModule
#define SoXtLightSliderSet      SoWinLightSliderSet
#define SoXtLtSldrs     SoWinLtSldrs
#define SoXtMMSliderMax SoWinMMSliderMax
#define SoXtMMSliderMin SoWinMMSliderMin
#define SoXtMaterial    SoWinMaterial
#define SoXtMaterialEditor      SoWinMaterialEditor
#define SoXtMaterialEditorCB    SoWinMaterialEditorCB
#define SoXtMaterialList        SoWinMaterialList
#define SoXtMaterialListCB      SoWinMaterialListCB
#define SoXtMaterialSliderSet   SoWinMaterialSliderSet
#define SoXtMessageHook SoWinMessageHook
#define SoXtMinMaxSlider        SoWinMinMaxSlider
#define SoXtMouse       SoWinMouse
#define SoXtMPRenderArea        SoWinMPRenderArea
#define SoXtMPRenderAreaEventCB SoWinMPRenderAreaEventCB
#define SoXtMpViewerCB SoWinMPViewerCB
#define SoXtMPViewer    SoWinMPViewer
#define SoXtMPExaminerViewer SoWinMPExaminerViewer
#define SoXtMPFullViewer SoWinMPFullViewer
#define SoXtMPGLWidget SoWinMPGLWidget
#define SoXtMPRenderArea SoWinMPRenderArea
#define SoXtMPViewerCameraTypeChangeCB  SoWinMPViewerCameraTypeChangeCB
#define SoXtMPViewerFPSCB SoWinMPViewerFPSCB
#define SoXtMPViewerDecimationPercentageCB SoWinMPViewerDecimationPercentageCB
#define SoXtMtlEd       SoWinMtlEd
#define SoXtMtlList     SoWinMtlList
#define SoXtMtlSldrs    SoWinMtlSldrs
#define SoXtMultiSlider SoWinMultiSlider
#define SoXtPlaneViewer SoWinPlaneViewer
#define SoXtPlnVwr      SoWinPlnVwr
#define SoXtPlnVwrCreate        SoWinPlnVwrCreate
#define SoXtPlnVwrCreateStd     SoWinPlnVwrCreateStd
#define SoXtPrintDialog SoWinPrintDialog
#define SoXtPrintDialogCB       SoWinPrintDialogCB
#define SoXtPrintDlog   SoWinPrintDlog
#define SoXtPushButton  SoWinPushButton
#define SoXtRA  SoWinRA
#define SoXtRACreate    SoWinRACreate
#define SoXtRACreateStd SoWinRACreateStd
#define SoXtRenderArea  SoWinRenderArea
#define SoXtRenderAreaEventCB   SoWinRenderAreaEventCB
#define SoXtResource    SoWinResource
#define SoXtRotateMultiSlider   SoWinRotateMultiSlider
#define SoXtRotateSliderModule  SoWinRotateSliderModule
#define SoXtScaleMultiSlider    SoWinScaleMultiSlider
#define SoXtScaleOrientationMultiSlider SoWinScaleOrientationMultiSlider
#define SoXtScaleOrientationSliderModule        SoWinScaleOrientationSliderModule
#define SoXtScaleSliderModule   SoWinScaleSliderModule
#define SoXtShininessMultiSlider        SoWinShininessMultiSlider
#define SoXtShininessSliderModule       SoWinShininessSliderModule
#define SoXtSldr        SoWinSldr
#define SoXtSldrs       SoWinSldrs
#define SoXtSldrsBase   SoWinSldrsBase
#define SoXtSlider      SoWinSlider
#define SoXtSliderControlPanel  SoWinSliderControlPanel
#define SoXtSliderModule        SoWinSliderModule
#define SoXtSliderSet   SoWinSliderSet
#define SoXtSliderSetBase       SoWinSliderSetBase
#define SoXtSliderTool  SoWinSliderTool
#define SoXtSpaceball      SoWinSpaceball
#define SoXtSpecularColorMultiSlider    SoWinSpecularColorMultiSlider
#define SoXtSpecularColorSliderModule   SoWinSpecularColorSliderModule
#define SoXtThumbWheel  SoWinThumbWheel
#define SoXtThumbWheelCB        SoWinThumbWheelCB
#define SoXtThumbWheelCBData    SoWinThumbWheelCBData
#define SoXtTransMultiSlider    SoWinTransMultiSlider
#define SoXtTransSliderModule   SoWinTransSliderModule
#define SoXtTransform   SoWinTransform
#define SoXtTransformSliderSet  SoWinTransformSliderSet
#define SoXtTransparencyMultiSlider     SoWinTransparencyMultiSlider
#define SoXtTransparencySliderModule    SoWinTransparencySliderModule
#define SoXtViewer      SoWinViewer
#define SoXtViewerCB    SoWinViewerCB
#define SoXtViewerCameraTypeChangeCB    SoWinViewerCameraTypeChangeCB
#define SoXtViewerFPSCB SoWinViewerFPSCB
#define SoXtViewerDecimationPercentageCB SoWinViewerDecimationPercentageCB
#define SoXtVwr SoWinVwr
#define SoXtWalkViewer  SoWinWalkViewer
#define SoXtWalkVwr     SoWinWalkVwr
#define SoXtWalkVwrCreate       SoWinWalkVwrCreate
#define SoXtWalkVwrCreateStd    SoWinWalkVwrCreateStd
#define SoXtXfSldrs     SoWinXfSldrs
#define SoXtColorEditor SoWinColorEditor
#define SoXtColorEditorCB       SoWinColorEditorCB
#define SoXtColorPatch  SoWinColorPatch
#define SoXtColorSlider SoWinColorSlider
#define SoXtColorWheel  SoWinColorWheel
#define SoXtColorWheelCB        SoWinColorWheelCB
#define SoXtSlider      SoWinSlider
#define SoXtSliderCB    SoWinSliderCB
#endif

#endif // _WIN32

#endif
