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

/// @addtogroup hxmoledit hxmoledit
/// @{
#ifndef QXMOLEDITORBASE_H
#define QXMOLEDITORBASE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_MolEditorBase
{
public:
    QWidget *widget;
    QVBoxLayout *vboxLayout;
    QTabWidget *MainTab;
    QWidget *TransformTab;
    QGridLayout *gridLayout;
    QFrame *Frame6;
    QGroupBox *bondLenghtGroupBox;
    QLabel *TextLabel4_4_2_2_3_2_2_2;
    QLineEdit *bondLengthLineView;
    QLineEdit *bondLengthLineEdit;
    QToolButton *absoluteBondLengthButton;
    QToolButton *relativeBondLengthButton;
    QToolButton *showStretchDraggerButton;
    QGroupBox *torsionGroupBox;
    QLabel *TextLabel4_4_2_2_2;
    QLineEdit *bondTorsionLineEdit;
    QLineEdit *bondTorsionLineView;
    QToolButton *absoluteBondTorsionButton;
    QToolButton *relativeBondTorsionButton;
    QToolButton *showRotationDraggerButton;
    QButtonGroup *positionButtonGroup;
    QWidget *Layout11_2;
    QHBoxLayout *hboxLayout;
    QLineEdit *moveXLineView;
    QLineEdit *moveYLineView;
    QLineEdit *moveZLineView;
    QWidget *Layout10_2;
    QHBoxLayout *hboxLayout1;
    QLineEdit *moveXLineEdit;
    QLineEdit *moveYLineEdit;
    QLineEdit *moveZLineEdit;
    QWidget *Layout37;
    QHBoxLayout *hboxLayout2;
    QLabel *TextLabel2_4;
    QLabel *TextLabel2_2_2;
    QLabel *TextLabel2_3_2;
    QToolButton *showMoveDraggerButton;
    QToolButton *relativeMoveButton;
    QToolButton *absoluteMoveButton;
    QGroupBox *bondAngleGroupBox;
    QLabel *TextLabel4_4_2_2_3_2_3;
    QLineEdit *bondAngleLineView;
    QLineEdit *bondAngleLineEdit;
    QToolButton *absoluteBondAngleButton;
    QToolButton *relativeBondAngleButton;
    QToolButton *showBendDraggerButton;
    QToolButton *symmetricBondAngleButton;
    QSpacerItem *spacerItem;
    QWidget *ToolsTab;
    QGridLayout *gridLayout1;
    QGroupBox *ChangeTopGroupBox;
    QGridLayout *gridLayout2;
    QSpacerItem *spacerItem1;
    QSpacerItem *spacerItem2;
    QHBoxLayout *hboxLayout3;
    QVBoxLayout *vboxLayout1;
    QToolButton *CopySelectedButton;
    QLabel *TextLabel1_2;
    QSpacerItem *spacerItem3;
    QVBoxLayout *vboxLayout2;
    QToolButton *SplitSelectedButton;
    QLabel *TextLabel2;
    QSpacerItem *spacerItem4;
    QVBoxLayout *vboxLayout3;
    QToolButton *DeleteSelectedButton;
    QLabel *TextLabel3;
    QSpacerItem *spacerItem5;
    QVBoxLayout *vboxLayout4;
    QToolButton *AddOtherButton;
    QLabel *TextLabel4;
    QGroupBox *ConectionGroupBox;
    QGridLayout *gridLayout3;
    QHBoxLayout *hboxLayout4;
    QLabel *TextLabel1;
    QSlider *MaximalAtomDistSlider;
    QLineEdit *MaximalAtomDistEdit;
    QButtonGroup *ConnectModeButtonGroup;
    QGridLayout *gridLayout4;
    QToolButton *StandardConnectButton;
    QToolButton *BondLengthConnectButton;
    QToolButton *ExternalConnectButton;
    QToolButton *AllSelectedConnectButton;
    QToolButton *DistanceConnectButton;
    QLabel *ModeTextLabel;
    QButtonGroup *ConnectActionButtonGroup;
    QGridLayout *gridLayout5;
    QVBoxLayout *vboxLayout5;
    QToolButton *ConnectActionButton;
    QLabel *TextLabel2_2;
    QVBoxLayout *vboxLayout6;
    QToolButton *DisconnectActionButton;
    QLabel *TextLabel3_2;
    QSpacerItem *spacerItem6;
    QSpacerItem *spacerItem7;
    QSpacerItem *spacerItem8;
    QWidget *BuildingTab;
    QGridLayout *gridLayout6;
    QFrame *buildingFrame;
    QVBoxLayout *vboxLayout7;
    QVBoxLayout *vboxLayout8;
    QHBoxLayout *hboxLayout5;
    QGroupBox *atomsGroupBox;
    QGridLayout *gridLayout7;
    QToolButton *atomCButton;
    QToolButton *atomHButton;
    QToolButton *atomOButton;
    QToolButton *atomPlusButton;
    QToolButton *atomMinusButton;
    QToolButton *atomNButton;
    QToolButton *atomSButton;
    QToolButton *atomPButton;
    QToolButton *atomValencyPlusButton;
    QToolButton *atomValencyMinusButton;
    QToolButton *atomFButton;
    QToolButton *atomClButton;
    QToolButton *atomElementSelectorButton;
    QToolButton *atomDeleteButton;
    QGroupBox *bondsGroupBox;
    QGridLayout *gridLayout8;
    QToolButton *bondSingleButton;
    QToolButton *bondDoubleButton;
    QToolButton *bondTripleButton;
    QToolButton *bondAromaticButton;
    QToolButton *bondDeleteButton;
    QGroupBox *carbonChainGroupBox;
    QGridLayout *gridLayout9;
    QLineEdit *carbonChainLengthLineEdit;
    QToolButton *carbonChainAddRingButton;
    QButtonGroup *carbonChainHybridizationButtonGroup;
    QGridLayout *gridLayout10;
    QToolButton *carbonChainSp2Button;
    QToolButton *carbonChainSp3Button;
    QToolButton *carbonChainAddTransButton;
    QToolButton *carbonChainAddCisButton;
    QHBoxLayout *hboxLayout6;
    QGroupBox *groupBox10;
    QHBoxLayout *hboxLayout7;
    QToolButton *relaxButton;
    QToolButton *relaxAllButton;
    QToolButton *minimizeAllButton;
    QToolButton *geometryChiralityButton;
    QGroupBox *smilesStringGroupBox;
    QHBoxLayout *hboxLayout8;
    QLineEdit *smilesStringLineEdit;
    QToolButton *smilesStringAddButton;
    QSpacerItem *spacerItem9;
    QSpacerItem *spacerItem10;
    QSpacerItem *spacerItem11;
    QHBoxLayout *hboxLayout9;
    QPushButton *okButton;
    QPushButton *undoButton;
    QPushButton *applyButton;
    QPushButton *resetButton;
    QPushButton *cancelButton;

    void setupUi(QMainWindow *MolEditorBase)
    {
    if (MolEditorBase->objectName().isEmpty())
        MolEditorBase->setObjectName(QString::fromUtf8("MolEditorBase"));
    MolEditorBase->resize(584, 355);
    QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(MolEditorBase->sizePolicy().hasHeightForWidth());
    MolEditorBase->setSizePolicy(sizePolicy);
    MolEditorBase->setWindowIcon(QIcon(QString::fromUtf8(":/icons/share/png/HxMoleculeEditor.png")));
    widget = new QWidget(MolEditorBase);
    widget->setObjectName(QString::fromUtf8("widget"));
    widget->setGeometry(QRect(0, 0, 584, 355));
    vboxLayout = new QVBoxLayout(widget);
    vboxLayout->setSpacing(4);
    vboxLayout->setMargin(11);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    vboxLayout->setContentsMargins(8, 8, 8, 8);
    MainTab = new QTabWidget(widget);
    MainTab->setObjectName(QString::fromUtf8("MainTab"));
    MainTab->setEnabled(true);
    MainTab->setTabShape(QTabWidget::Rounded);
    TransformTab = new QWidget();
    TransformTab->setObjectName(QString::fromUtf8("TransformTab"));
    gridLayout = new QGridLayout(TransformTab);
    gridLayout->setSpacing(6);
    gridLayout->setMargin(11);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    Frame6 = new QFrame(TransformTab);
    Frame6->setObjectName(QString::fromUtf8("Frame6"));
    QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(Frame6->sizePolicy().hasHeightForWidth());
    Frame6->setSizePolicy(sizePolicy1);
    Frame6->setMinimumSize(QSize(341, 221));
    Frame6->setFrameShape(QFrame::NoFrame);
    Frame6->setFrameShadow(QFrame::Plain);
    Frame6->setLineWidth(0);
    bondLenghtGroupBox = new QGroupBox(Frame6);
    bondLenghtGroupBox->setObjectName(QString::fromUtf8("bondLenghtGroupBox"));
    bondLenghtGroupBox->setGeometry(QRect(193, 108, 141, 108));
    sizePolicy1.setHeightForWidth(bondLenghtGroupBox->sizePolicy().hasHeightForWidth());
    bondLenghtGroupBox->setSizePolicy(sizePolicy1);
    TextLabel4_4_2_2_3_2_2_2 = new QLabel(bondLenghtGroupBox);
    TextLabel4_4_2_2_3_2_2_2->setObjectName(QString::fromUtf8("TextLabel4_4_2_2_3_2_2_2"));
    TextLabel4_4_2_2_3_2_2_2->setGeometry(QRect(27, 20, 65, 17));
    TextLabel4_4_2_2_3_2_2_2->setAlignment(Qt::AlignCenter);
    TextLabel4_4_2_2_3_2_2_2->setWordWrap(false);
    bondLengthLineView = new QLineEdit(bondLenghtGroupBox);
    bondLengthLineView->setObjectName(QString::fromUtf8("bondLengthLineView"));
    bondLengthLineView->setEnabled(false);
    bondLengthLineView->setGeometry(QRect(27, 37, 60, 25));
    bondLengthLineView->setMaximumSize(QSize(60, 32767));
    bondLengthLineEdit = new QLineEdit(bondLenghtGroupBox);
    bondLengthLineEdit->setObjectName(QString::fromUtf8("bondLengthLineEdit"));
    bondLengthLineEdit->setGeometry(QRect(27, 69, 60, 25));
    bondLengthLineEdit->setMaximumSize(QSize(60, 32767));
    absoluteBondLengthButton = new QToolButton(bondLenghtGroupBox);
    absoluteBondLengthButton->setObjectName(QString::fromUtf8("absoluteBondLengthButton"));
    absoluteBondLengthButton->setGeometry(QRect(104, 12, 30, 30));
    sizePolicy1.setHeightForWidth(absoluteBondLengthButton->sizePolicy().hasHeightForWidth());
    absoluteBondLengthButton->setSizePolicy(sizePolicy1);
    absoluteBondLengthButton->setMaximumSize(QSize(30, 30));
    absoluteBondLengthButton->setIcon(QIcon(QString::fromUtf8(":/icons/buttons/a.bmp")));
    absoluteBondLengthButton->setIconSize(QSize(32, 32));
    relativeBondLengthButton = new QToolButton(bondLenghtGroupBox);
    relativeBondLengthButton->setObjectName(QString::fromUtf8("relativeBondLengthButton"));
    relativeBondLengthButton->setGeometry(QRect(104, 42, 30, 30));
    sizePolicy1.setHeightForWidth(relativeBondLengthButton->sizePolicy().hasHeightForWidth());
    relativeBondLengthButton->setSizePolicy(sizePolicy1);
    relativeBondLengthButton->setMaximumSize(QSize(30, 30));
    relativeBondLengthButton->setIcon(QIcon(QString::fromUtf8(":/icons/buttons/a2.bmp")));
    relativeBondLengthButton->setIconSize(QSize(32, 32));
    relativeBondLengthButton->setAutoRepeat(true);
    showStretchDraggerButton = new QToolButton(bondLenghtGroupBox);
    showStretchDraggerButton->setObjectName(QString::fromUtf8("showStretchDraggerButton"));
    showStretchDraggerButton->setGeometry(QRect(104, 72, 30, 30));
    sizePolicy1.setHeightForWidth(showStretchDraggerButton->sizePolicy().hasHeightForWidth());
    showStretchDraggerButton->setSizePolicy(sizePolicy1);
    showStretchDraggerButton->setMaximumSize(QSize(30, 30));
    showStretchDraggerButton->setIcon(QIcon(QString::fromUtf8(":/icons/buttons/a3.bmp")));
    showStretchDraggerButton->setIconSize(QSize(32, 32));
    torsionGroupBox = new QGroupBox(Frame6);
    torsionGroupBox->setObjectName(QString::fromUtf8("torsionGroupBox"));
    torsionGroupBox->setGeometry(QRect(194, 0, 141, 108));
    sizePolicy1.setHeightForWidth(torsionGroupBox->sizePolicy().hasHeightForWidth());
    torsionGroupBox->setSizePolicy(sizePolicy1);
    TextLabel4_4_2_2_2 = new QLabel(torsionGroupBox);
    TextLabel4_4_2_2_2->setObjectName(QString::fromUtf8("TextLabel4_4_2_2_2"));
    TextLabel4_4_2_2_2->setGeometry(QRect(29, 20, 62, 15));
    sizePolicy1.setHeightForWidth(TextLabel4_4_2_2_2->sizePolicy().hasHeightForWidth());
    TextLabel4_4_2_2_2->setSizePolicy(sizePolicy1);
    TextLabel4_4_2_2_2->setAlignment(Qt::AlignCenter);
    TextLabel4_4_2_2_2->setWordWrap(false);
    bondTorsionLineEdit = new QLineEdit(torsionGroupBox);
    bondTorsionLineEdit->setObjectName(QString::fromUtf8("bondTorsionLineEdit"));
    bondTorsionLineEdit->setGeometry(QRect(27, 70, 60, 25));
    QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(bondTorsionLineEdit->sizePolicy().hasHeightForWidth());
    bondTorsionLineEdit->setSizePolicy(sizePolicy2);
    bondTorsionLineEdit->setMaximumSize(QSize(60, 32767));
    bondTorsionLineView = new QLineEdit(torsionGroupBox);
    bondTorsionLineView->setObjectName(QString::fromUtf8("bondTorsionLineView"));
    bondTorsionLineView->setEnabled(false);
    bondTorsionLineView->setGeometry(QRect(27, 39, 60, 25));
    bondTorsionLineView->setMaximumSize(QSize(60, 32767));
    absoluteBondTorsionButton = new QToolButton(torsionGroupBox);
    absoluteBondTorsionButton->setObjectName(QString::fromUtf8("absoluteBondTorsionButton"));
    absoluteBondTorsionButton->setGeometry(QRect(104, 12, 30, 30));
    sizePolicy1.setHeightForWidth(absoluteBondTorsionButton->sizePolicy().hasHeightForWidth());
    absoluteBondTorsionButton->setSizePolicy(sizePolicy1);
    absoluteBondTorsionButton->setMaximumSize(QSize(30, 30));
    absoluteBondTorsionButton->setIcon(QIcon(QString::fromUtf8(":/icons/buttons/a.bmp")));
    absoluteBondTorsionButton->setIconSize(QSize(32, 32));
    relativeBondTorsionButton = new QToolButton(torsionGroupBox);
    relativeBondTorsionButton->setObjectName(QString::fromUtf8("relativeBondTorsionButton"));
    relativeBondTorsionButton->setGeometry(QRect(104, 42, 30, 30));
    sizePolicy1.setHeightForWidth(relativeBondTorsionButton->sizePolicy().hasHeightForWidth());
    relativeBondTorsionButton->setSizePolicy(sizePolicy1);
    relativeBondTorsionButton->setMaximumSize(QSize(30, 30));
    relativeBondTorsionButton->setIcon(QIcon(QString::fromUtf8(":/icons/buttons/a2.bmp")));
    relativeBondTorsionButton->setIconSize(QSize(32, 32));
    relativeBondTorsionButton->setAutoRepeat(true);
    showRotationDraggerButton = new QToolButton(torsionGroupBox);
    showRotationDraggerButton->setObjectName(QString::fromUtf8("showRotationDraggerButton"));
    showRotationDraggerButton->setGeometry(QRect(104, 72, 30, 30));
    sizePolicy1.setHeightForWidth(showRotationDraggerButton->sizePolicy().hasHeightForWidth());
    showRotationDraggerButton->setSizePolicy(sizePolicy1);
    showRotationDraggerButton->setMaximumSize(QSize(30, 30));
    showRotationDraggerButton->setIcon(QIcon(QString::fromUtf8(":/icons/buttons/a3.bmp")));
    showRotationDraggerButton->setIconSize(QSize(32, 32));
    positionButtonGroup = new QButtonGroup(Frame6);
    positionButtonGroup->setObjectName(QString::fromUtf8("positionButtonGroup"));
    positionButtonGroup->setGeometry(QRect(7, 0, 182, 108));
    sizePolicy1.setHeightForWidth(positionButtonGroup->sizePolicy().hasHeightForWidth());
    positionButtonGroup->setSizePolicy(sizePolicy1);
    positionButtonGroup->setFlat(false);
    positionButtonGroup->setLineWidth(1);
    positionButtonGroup->setExclusive(false);
    Layout11_2 = new QWidget(positionButtonGroup);
    Layout11_2->setObjectName(QString::fromUtf8("Layout11_2"));
    Layout11_2->setGeometry(QRect(13, 37, 121, 28));
    hboxLayout = new QHBoxLayout(Layout11_2);
    hboxLayout->setSpacing(0);
    hboxLayout->setMargin(11);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    hboxLayout->setContentsMargins(0, 0, 0, 0);
    moveXLineView = new QLineEdit(Layout11_2);
    moveXLineView->setObjectName(QString::fromUtf8("moveXLineView"));
    moveXLineView->setEnabled(false);
    moveXLineView->setMaximumSize(QSize(60, 32767));

    hboxLayout->addWidget(moveXLineView);

    moveYLineView = new QLineEdit(Layout11_2);
    moveYLineView->setObjectName(QString::fromUtf8("moveYLineView"));
    moveYLineView->setEnabled(false);
    moveYLineView->setMaximumSize(QSize(60, 32767));

    hboxLayout->addWidget(moveYLineView);

    moveZLineView = new QLineEdit(Layout11_2);
    moveZLineView->setObjectName(QString::fromUtf8("moveZLineView"));
    moveZLineView->setEnabled(false);
    moveZLineView->setMaximumSize(QSize(60, 32767));

    hboxLayout->addWidget(moveZLineView);

    Layout10_2 = new QWidget(positionButtonGroup);
    Layout10_2->setObjectName(QString::fromUtf8("Layout10_2"));
    Layout10_2->setGeometry(QRect(13, 69, 121, 28));
    hboxLayout1 = new QHBoxLayout(Layout10_2);
    hboxLayout1->setSpacing(0);
    hboxLayout1->setMargin(11);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    hboxLayout1->setContentsMargins(0, 0, 0, 0);
    moveXLineEdit = new QLineEdit(Layout10_2);
    moveXLineEdit->setObjectName(QString::fromUtf8("moveXLineEdit"));
    moveXLineEdit->setEnabled(true);
    moveXLineEdit->setMaximumSize(QSize(60, 32767));

    hboxLayout1->addWidget(moveXLineEdit);

    moveYLineEdit = new QLineEdit(Layout10_2);
    moveYLineEdit->setObjectName(QString::fromUtf8("moveYLineEdit"));
    moveYLineEdit->setMaximumSize(QSize(60, 32767));

    hboxLayout1->addWidget(moveYLineEdit);

    moveZLineEdit = new QLineEdit(Layout10_2);
    moveZLineEdit->setObjectName(QString::fromUtf8("moveZLineEdit"));
    moveZLineEdit->setMaximumSize(QSize(60, 32767));

    hboxLayout1->addWidget(moveZLineEdit);

    Layout37 = new QWidget(positionButtonGroup);
    Layout37->setObjectName(QString::fromUtf8("Layout37"));
    Layout37->setGeometry(QRect(13, 19, 121, 15));
    hboxLayout2 = new QHBoxLayout(Layout37);
    hboxLayout2->setSpacing(0);
    hboxLayout2->setMargin(11);
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    hboxLayout2->setContentsMargins(0, 0, 0, 0);
    TextLabel2_4 = new QLabel(Layout37);
    TextLabel2_4->setObjectName(QString::fromUtf8("TextLabel2_4"));
    TextLabel2_4->setAlignment(Qt::AlignCenter);
    TextLabel2_4->setWordWrap(false);

    hboxLayout2->addWidget(TextLabel2_4);

    TextLabel2_2_2 = new QLabel(Layout37);
    TextLabel2_2_2->setObjectName(QString::fromUtf8("TextLabel2_2_2"));
    sizePolicy.setHeightForWidth(TextLabel2_2_2->sizePolicy().hasHeightForWidth());
    TextLabel2_2_2->setSizePolicy(sizePolicy);
    TextLabel2_2_2->setAlignment(Qt::AlignCenter);
    TextLabel2_2_2->setWordWrap(false);

    hboxLayout2->addWidget(TextLabel2_2_2);

    TextLabel2_3_2 = new QLabel(Layout37);
    TextLabel2_3_2->setObjectName(QString::fromUtf8("TextLabel2_3_2"));
    TextLabel2_3_2->setAlignment(Qt::AlignCenter);
    TextLabel2_3_2->setWordWrap(false);

    hboxLayout2->addWidget(TextLabel2_3_2);

    showMoveDraggerButton = new QToolButton(positionButtonGroup);
    showMoveDraggerButton->setObjectName(QString::fromUtf8("showMoveDraggerButton"));
    showMoveDraggerButton->setGeometry(QRect(145, 72, 30, 30));
    sizePolicy1.setHeightForWidth(showMoveDraggerButton->sizePolicy().hasHeightForWidth());
    showMoveDraggerButton->setSizePolicy(sizePolicy1);
    showMoveDraggerButton->setMaximumSize(QSize(30, 30));
    showMoveDraggerButton->setIcon(QIcon(QString::fromUtf8(":/icons/buttons/a3.bmp")));
    showMoveDraggerButton->setIconSize(QSize(32, 32));
    relativeMoveButton = new QToolButton(positionButtonGroup);
    relativeMoveButton->setObjectName(QString::fromUtf8("relativeMoveButton"));
    relativeMoveButton->setGeometry(QRect(145, 42, 30, 30));
    sizePolicy1.setHeightForWidth(relativeMoveButton->sizePolicy().hasHeightForWidth());
    relativeMoveButton->setSizePolicy(sizePolicy1);
    relativeMoveButton->setMaximumSize(QSize(30, 30));
    relativeMoveButton->setIcon(QIcon(QString::fromUtf8(":/icons/buttons/a2.bmp")));
    relativeMoveButton->setIconSize(QSize(32, 32));
    relativeMoveButton->setAutoRepeat(true);
    absoluteMoveButton = new QToolButton(positionButtonGroup);
    absoluteMoveButton->setObjectName(QString::fromUtf8("absoluteMoveButton"));
    absoluteMoveButton->setGeometry(QRect(145, 12, 30, 30));
    sizePolicy1.setHeightForWidth(absoluteMoveButton->sizePolicy().hasHeightForWidth());
    absoluteMoveButton->setSizePolicy(sizePolicy1);
    absoluteMoveButton->setMaximumSize(QSize(30, 30));
    absoluteMoveButton->setIcon(QIcon(QString::fromUtf8(":/icons/buttons/a.bmp")));
    absoluteMoveButton->setIconSize(QSize(32, 32));
    absoluteMoveButton->setCheckable(false);
    bondAngleGroupBox = new QGroupBox(Frame6);
    bondAngleGroupBox->setObjectName(QString::fromUtf8("bondAngleGroupBox"));
    bondAngleGroupBox->setGeometry(QRect(7, 108, 182, 108));
    sizePolicy1.setHeightForWidth(bondAngleGroupBox->sizePolicy().hasHeightForWidth());
    bondAngleGroupBox->setSizePolicy(sizePolicy1);
    bondAngleGroupBox->setAlignment(Qt::AlignLeading);
    TextLabel4_4_2_2_3_2_3 = new QLabel(bondAngleGroupBox);
    TextLabel4_4_2_2_3_2_3->setObjectName(QString::fromUtf8("TextLabel4_4_2_2_3_2_3"));
    TextLabel4_4_2_2_3_2_3->setGeometry(QRect(61, 18, 62, 16));
    TextLabel4_4_2_2_3_2_3->setAlignment(Qt::AlignCenter);
    TextLabel4_4_2_2_3_2_3->setWordWrap(false);
    bondAngleLineView = new QLineEdit(bondAngleGroupBox);
    bondAngleLineView->setObjectName(QString::fromUtf8("bondAngleLineView"));
    bondAngleLineView->setEnabled(false);
    bondAngleLineView->setGeometry(QRect(60, 36, 60, 25));
    bondAngleLineView->setMaximumSize(QSize(60, 32767));
    bondAngleLineEdit = new QLineEdit(bondAngleGroupBox);
    bondAngleLineEdit->setObjectName(QString::fromUtf8("bondAngleLineEdit"));
    bondAngleLineEdit->setGeometry(QRect(60, 68, 60, 25));
    bondAngleLineEdit->setMaximumSize(QSize(60, 32767));
    absoluteBondAngleButton = new QToolButton(bondAngleGroupBox);
    absoluteBondAngleButton->setObjectName(QString::fromUtf8("absoluteBondAngleButton"));
    absoluteBondAngleButton->setGeometry(QRect(145, 12, 30, 30));
    sizePolicy1.setHeightForWidth(absoluteBondAngleButton->sizePolicy().hasHeightForWidth());
    absoluteBondAngleButton->setSizePolicy(sizePolicy1);
    absoluteBondAngleButton->setMaximumSize(QSize(30, 30));
    absoluteBondAngleButton->setIcon(QIcon(QString::fromUtf8(":/icons/buttons/a.bmp")));
    absoluteBondAngleButton->setIconSize(QSize(32, 32));
    absoluteBondAngleButton->setCheckable(false);
    relativeBondAngleButton = new QToolButton(bondAngleGroupBox);
    relativeBondAngleButton->setObjectName(QString::fromUtf8("relativeBondAngleButton"));
    relativeBondAngleButton->setGeometry(QRect(145, 42, 30, 30));
    sizePolicy1.setHeightForWidth(relativeBondAngleButton->sizePolicy().hasHeightForWidth());
    relativeBondAngleButton->setSizePolicy(sizePolicy1);
    relativeBondAngleButton->setMaximumSize(QSize(30, 30));
    relativeBondAngleButton->setIcon(QIcon(QString::fromUtf8(":/icons/buttons/a2.bmp")));
    relativeBondAngleButton->setIconSize(QSize(32, 32));
    relativeBondAngleButton->setCheckable(false);
    relativeBondAngleButton->setAutoRepeat(true);
    showBendDraggerButton = new QToolButton(bondAngleGroupBox);
    showBendDraggerButton->setObjectName(QString::fromUtf8("showBendDraggerButton"));
    showBendDraggerButton->setGeometry(QRect(145, 72, 30, 30));
    sizePolicy1.setHeightForWidth(showBendDraggerButton->sizePolicy().hasHeightForWidth());
    showBendDraggerButton->setSizePolicy(sizePolicy1);
    showBendDraggerButton->setMaximumSize(QSize(30, 30));
    showBendDraggerButton->setIcon(QIcon(QString::fromUtf8(":/icons/buttons/a3.bmp")));
    showBendDraggerButton->setIconSize(QSize(32, 32));
    showBendDraggerButton->setCheckable(false);
    symmetricBondAngleButton = new QToolButton(bondAngleGroupBox);
    symmetricBondAngleButton->setObjectName(QString::fromUtf8("symmetricBondAngleButton"));
    symmetricBondAngleButton->setGeometry(QRect(14, 72, 30, 30));
    sizePolicy1.setHeightForWidth(symmetricBondAngleButton->sizePolicy().hasHeightForWidth());
    symmetricBondAngleButton->setSizePolicy(sizePolicy1);
    symmetricBondAngleButton->setMaximumSize(QSize(30, 30));
    symmetricBondAngleButton->setIcon(QIcon(QString::fromUtf8(":/icons/buttons/a4.bmp")));
    symmetricBondAngleButton->setIconSize(QSize(32, 32));
    symmetricBondAngleButton->setCheckable(true);

    gridLayout->addWidget(Frame6, 0, 0, 1, 1);

    spacerItem = new QSpacerItem(16, 105, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout->addItem(spacerItem, 1, 0, 1, 1);

    MainTab->addTab(TransformTab, QString());
    ToolsTab = new QWidget();
    ToolsTab->setObjectName(QString::fromUtf8("ToolsTab"));
    gridLayout1 = new QGridLayout(ToolsTab);
    gridLayout1->setSpacing(6);
    gridLayout1->setMargin(11);
    gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
    ChangeTopGroupBox = new QGroupBox(ToolsTab);
    ChangeTopGroupBox->setObjectName(QString::fromUtf8("ChangeTopGroupBox"));
    sizePolicy.setHeightForWidth(ChangeTopGroupBox->sizePolicy().hasHeightForWidth());
    ChangeTopGroupBox->setSizePolicy(sizePolicy);
    gridLayout2 = new QGridLayout(ChangeTopGroupBox);
    gridLayout2->setSpacing(6);
    gridLayout2->setMargin(11);
    gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
    gridLayout2->setHorizontalSpacing(5);
    gridLayout2->setVerticalSpacing(5);
    gridLayout2->setContentsMargins(6, 6, 6, 6);
    spacerItem1 = new QSpacerItem(34, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout2->addItem(spacerItem1, 0, 0, 1, 1);

    spacerItem2 = new QSpacerItem(35, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout2->addItem(spacerItem2, 0, 2, 1, 1);

    hboxLayout3 = new QHBoxLayout();
    hboxLayout3->setSpacing(1);
    hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
    hboxLayout3->setContentsMargins(0, 0, 0, 0);
    vboxLayout1 = new QVBoxLayout();
    vboxLayout1->setSpacing(2);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    vboxLayout1->setContentsMargins(0, 0, 0, 0);
    CopySelectedButton = new QToolButton(ChangeTopGroupBox);
    CopySelectedButton->setObjectName(QString::fromUtf8("CopySelectedButton"));
    sizePolicy1.setHeightForWidth(CopySelectedButton->sizePolicy().hasHeightForWidth());
    CopySelectedButton->setSizePolicy(sizePolicy1);
    CopySelectedButton->setMaximumSize(QSize(33, 33));
    CopySelectedButton->setIcon(QIcon(QString::fromUtf8(":/icons/buttons/cutAndPaste4.bmp")));
    CopySelectedButton->setIconSize(QSize(32, 32));
    CopySelectedButton->setCheckable(false);

    vboxLayout1->addWidget(CopySelectedButton);

    TextLabel1_2 = new QLabel(ChangeTopGroupBox);
    TextLabel1_2->setObjectName(QString::fromUtf8("TextLabel1_2"));
    TextLabel1_2->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
    TextLabel1_2->setWordWrap(false);

    vboxLayout1->addWidget(TextLabel1_2);


    hboxLayout3->addLayout(vboxLayout1);

    spacerItem3 = new QSpacerItem(16, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout3->addItem(spacerItem3);

    vboxLayout2 = new QVBoxLayout();
    vboxLayout2->setSpacing(2);
    vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
    vboxLayout2->setContentsMargins(0, 0, 0, 0);
    SplitSelectedButton = new QToolButton(ChangeTopGroupBox);
    SplitSelectedButton->setObjectName(QString::fromUtf8("SplitSelectedButton"));
    sizePolicy1.setHeightForWidth(SplitSelectedButton->sizePolicy().hasHeightForWidth());
    SplitSelectedButton->setSizePolicy(sizePolicy1);
    SplitSelectedButton->setMaximumSize(QSize(33, 33));
    SplitSelectedButton->setIcon(QIcon(QString::fromUtf8(":/icons/buttons/cutAndPaste1.bmp")));
    SplitSelectedButton->setIconSize(QSize(32, 32));

    vboxLayout2->addWidget(SplitSelectedButton);

    TextLabel2 = new QLabel(ChangeTopGroupBox);
    TextLabel2->setObjectName(QString::fromUtf8("TextLabel2"));
    TextLabel2->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
    TextLabel2->setWordWrap(false);

    vboxLayout2->addWidget(TextLabel2);


    hboxLayout3->addLayout(vboxLayout2);

    spacerItem4 = new QSpacerItem(16, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout3->addItem(spacerItem4);

    vboxLayout3 = new QVBoxLayout();
    vboxLayout3->setSpacing(2);
    vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
    vboxLayout3->setContentsMargins(0, 0, 0, 0);
    DeleteSelectedButton = new QToolButton(ChangeTopGroupBox);
    DeleteSelectedButton->setObjectName(QString::fromUtf8("DeleteSelectedButton"));
    sizePolicy1.setHeightForWidth(DeleteSelectedButton->sizePolicy().hasHeightForWidth());
    DeleteSelectedButton->setSizePolicy(sizePolicy1);
    DeleteSelectedButton->setMaximumSize(QSize(33, 33));
    DeleteSelectedButton->setIcon(QIcon(QString::fromUtf8(":/icons/buttons/cutAndPaste3.bmp")));
    DeleteSelectedButton->setIconSize(QSize(32, 32));

    vboxLayout3->addWidget(DeleteSelectedButton);

    TextLabel3 = new QLabel(ChangeTopGroupBox);
    TextLabel3->setObjectName(QString::fromUtf8("TextLabel3"));
    TextLabel3->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
    TextLabel3->setWordWrap(false);

    vboxLayout3->addWidget(TextLabel3);


    hboxLayout3->addLayout(vboxLayout3);

    spacerItem5 = new QSpacerItem(16, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout3->addItem(spacerItem5);

    vboxLayout4 = new QVBoxLayout();
    vboxLayout4->setSpacing(2);
    vboxLayout4->setObjectName(QString::fromUtf8("vboxLayout4"));
    vboxLayout4->setContentsMargins(0, 0, 0, 0);
    AddOtherButton = new QToolButton(ChangeTopGroupBox);
    AddOtherButton->setObjectName(QString::fromUtf8("AddOtherButton"));
    sizePolicy1.setHeightForWidth(AddOtherButton->sizePolicy().hasHeightForWidth());
    AddOtherButton->setSizePolicy(sizePolicy1);
    AddOtherButton->setMaximumSize(QSize(33, 33));
    AddOtherButton->setIcon(QIcon(QString::fromUtf8(":/icons/buttons/cutAndPaste2.bmp")));
    AddOtherButton->setIconSize(QSize(32, 32));

    vboxLayout4->addWidget(AddOtherButton);

    TextLabel4 = new QLabel(ChangeTopGroupBox);
    TextLabel4->setObjectName(QString::fromUtf8("TextLabel4"));
    TextLabel4->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
    TextLabel4->setWordWrap(false);

    vboxLayout4->addWidget(TextLabel4);


    hboxLayout3->addLayout(vboxLayout4);


    gridLayout2->addLayout(hboxLayout3, 0, 1, 1, 1);


    gridLayout1->addWidget(ChangeTopGroupBox, 0, 1, 1, 1);

    ConectionGroupBox = new QGroupBox(ToolsTab);
    ConectionGroupBox->setObjectName(QString::fromUtf8("ConectionGroupBox"));
    sizePolicy.setHeightForWidth(ConectionGroupBox->sizePolicy().hasHeightForWidth());
    ConectionGroupBox->setSizePolicy(sizePolicy);
    gridLayout3 = new QGridLayout(ConectionGroupBox);
    gridLayout3->setSpacing(6);
    gridLayout3->setMargin(11);
    gridLayout3->setObjectName(QString::fromUtf8("gridLayout3"));
    gridLayout3->setHorizontalSpacing(5);
    gridLayout3->setVerticalSpacing(5);
    gridLayout3->setContentsMargins(7, 7, 7, 7);
    hboxLayout4 = new QHBoxLayout();
    hboxLayout4->setSpacing(6);
    hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
    hboxLayout4->setContentsMargins(0, 0, 0, 0);
    TextLabel1 = new QLabel(ConectionGroupBox);
    TextLabel1->setObjectName(QString::fromUtf8("TextLabel1"));
    TextLabel1->setWordWrap(false);

    hboxLayout4->addWidget(TextLabel1);

    MaximalAtomDistSlider = new QSlider(ConectionGroupBox);
    MaximalAtomDistSlider->setObjectName(QString::fromUtf8("MaximalAtomDistSlider"));
    sizePolicy2.setHeightForWidth(MaximalAtomDistSlider->sizePolicy().hasHeightForWidth());
    MaximalAtomDistSlider->setSizePolicy(sizePolicy2);
    MaximalAtomDistSlider->setMinimumSize(QSize(100, 0));
    MaximalAtomDistSlider->setMaximum(400);
    MaximalAtomDistSlider->setPageStep(100);
    MaximalAtomDistSlider->setOrientation(Qt::Horizontal);

    hboxLayout4->addWidget(MaximalAtomDistSlider);

    MaximalAtomDistEdit = new QLineEdit(ConectionGroupBox);
    MaximalAtomDistEdit->setObjectName(QString::fromUtf8("MaximalAtomDistEdit"));
    sizePolicy2.setHeightForWidth(MaximalAtomDistEdit->sizePolicy().hasHeightForWidth());
    MaximalAtomDistEdit->setSizePolicy(sizePolicy2);
    MaximalAtomDistEdit->setMaximumSize(QSize(40, 32767));

    hboxLayout4->addWidget(MaximalAtomDistEdit);


    gridLayout3->addLayout(hboxLayout4, 1, 0, 1, 2);

    ConnectModeButtonGroup = new QButtonGroup(ConectionGroupBox);
    ConnectModeButtonGroup->setObjectName(QString::fromUtf8("ConnectModeButtonGroup"));
    ConnectModeButtonGroup->setEnabled(true);
    QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(ConnectModeButtonGroup->sizePolicy().hasHeightForWidth());
    ConnectModeButtonGroup->setSizePolicy(sizePolicy3);
    ConnectModeButtonGroup->setMaximumSize(QSize(32767, 74));
    ConnectModeButtonGroup->setMargin(0);
    ConnectModeButtonGroup->setExclusive(true);
    gridLayout4 = new QGridLayout(ConnectModeButtonGroup);
    gridLayout4->setSpacing(6);
    gridLayout4->setMargin(11);
    gridLayout4->setObjectName(QString::fromUtf8("gridLayout4"));
    gridLayout4->setVerticalSpacing(3);
    gridLayout4->setContentsMargins(-1, 6, -1, -1);
    StandardConnectButton = new QToolButton(ConnectModeButtonGroup);
    StandardConnectButton->setObjectName(QString::fromUtf8("StandardConnectButton"));
    sizePolicy1.setHeightForWidth(StandardConnectButton->sizePolicy().hasHeightForWidth());
    StandardConnectButton->setSizePolicy(sizePolicy1);
    StandardConnectButton->setMaximumSize(QSize(33, 33));
    StandardConnectButton->setIcon(QIcon(QString::fromUtf8(":/icons/buttons/connect5.bmp")));
    StandardConnectButton->setIconSize(QSize(32, 32));
    StandardConnectButton->setCheckable(true);

    gridLayout4->addWidget(StandardConnectButton, 0, 0, 1, 1);

    BondLengthConnectButton = new QToolButton(ConnectModeButtonGroup);
    BondLengthConnectButton->setObjectName(QString::fromUtf8("BondLengthConnectButton"));
    sizePolicy1.setHeightForWidth(BondLengthConnectButton->sizePolicy().hasHeightForWidth());
    BondLengthConnectButton->setSizePolicy(sizePolicy1);
    BondLengthConnectButton->setMaximumSize(QSize(33, 33));
    BondLengthConnectButton->setIcon(QIcon(QString::fromUtf8(":/icons/buttons/connect3.bmp")));
    BondLengthConnectButton->setIconSize(QSize(32, 32));
    BondLengthConnectButton->setCheckable(true);

    gridLayout4->addWidget(BondLengthConnectButton, 0, 1, 1, 1);

    ExternalConnectButton = new QToolButton(ConnectModeButtonGroup);
    ExternalConnectButton->setObjectName(QString::fromUtf8("ExternalConnectButton"));
    sizePolicy1.setHeightForWidth(ExternalConnectButton->sizePolicy().hasHeightForWidth());
    ExternalConnectButton->setSizePolicy(sizePolicy1);
    ExternalConnectButton->setMaximumSize(QSize(33, 33));
    ExternalConnectButton->setIcon(QIcon(QString::fromUtf8(":/icons/buttons/connect1.bmp")));
    ExternalConnectButton->setIconSize(QSize(32, 32));
    ExternalConnectButton->setCheckable(true);

    gridLayout4->addWidget(ExternalConnectButton, 0, 2, 1, 1);

    AllSelectedConnectButton = new QToolButton(ConnectModeButtonGroup);
    AllSelectedConnectButton->setObjectName(QString::fromUtf8("AllSelectedConnectButton"));
    sizePolicy1.setHeightForWidth(AllSelectedConnectButton->sizePolicy().hasHeightForWidth());
    AllSelectedConnectButton->setSizePolicy(sizePolicy1);
    AllSelectedConnectButton->setMaximumSize(QSize(33, 33));
    AllSelectedConnectButton->setIcon(QIcon(QString::fromUtf8(":/icons/buttons/connect4.bmp")));
    AllSelectedConnectButton->setIconSize(QSize(32, 32));
    AllSelectedConnectButton->setCheckable(true);

    gridLayout4->addWidget(AllSelectedConnectButton, 0, 3, 1, 1);

    DistanceConnectButton = new QToolButton(ConnectModeButtonGroup);
    DistanceConnectButton->setObjectName(QString::fromUtf8("DistanceConnectButton"));
    sizePolicy1.setHeightForWidth(DistanceConnectButton->sizePolicy().hasHeightForWidth());
    DistanceConnectButton->setSizePolicy(sizePolicy1);
    DistanceConnectButton->setMaximumSize(QSize(33, 33));
    DistanceConnectButton->setIcon(QIcon(QString::fromUtf8(":/icons/buttons/connect2.bmp")));
    DistanceConnectButton->setIconSize(QSize(32, 32));
    DistanceConnectButton->setCheckable(true);

    gridLayout4->addWidget(DistanceConnectButton, 0, 4, 1, 1);

    ModeTextLabel = new QLabel(ConnectModeButtonGroup);
    ModeTextLabel->setObjectName(QString::fromUtf8("ModeTextLabel"));
    ModeTextLabel->setWordWrap(false);

    gridLayout4->addWidget(ModeTextLabel, 1, 0, 1, 5);


    gridLayout3->addWidget(ConnectModeButtonGroup, 0, 0, 1, 1);

    ConnectActionButtonGroup = new QButtonGroup(ConectionGroupBox);
    ConnectActionButtonGroup->setObjectName(QString::fromUtf8("ConnectActionButtonGroup"));
    sizePolicy3.setHeightForWidth(ConnectActionButtonGroup->sizePolicy().hasHeightForWidth());
    ConnectActionButtonGroup->setSizePolicy(sizePolicy3);
    ConnectActionButtonGroup->setMaximumSize(QSize(32767, 74));
    gridLayout5 = new QGridLayout(ConnectActionButtonGroup);
    gridLayout5->setSpacing(6);
    gridLayout5->setMargin(11);
    gridLayout5->setObjectName(QString::fromUtf8("gridLayout5"));
    gridLayout5->setVerticalSpacing(6);
    gridLayout5->setContentsMargins(-1, 6, -1, -1);
    vboxLayout5 = new QVBoxLayout();
    vboxLayout5->setSpacing(3);
    vboxLayout5->setObjectName(QString::fromUtf8("vboxLayout5"));
    vboxLayout5->setContentsMargins(0, 0, 0, 0);
    ConnectActionButton = new QToolButton(ConnectActionButtonGroup);
    ConnectActionButton->setObjectName(QString::fromUtf8("ConnectActionButton"));
    ConnectActionButton->setMaximumSize(QSize(33, 33));
    ConnectActionButton->setIcon(QIcon(QString::fromUtf8(":/icons/buttons/connectAction2.bmp")));
    ConnectActionButton->setIconSize(QSize(32, 32));

    vboxLayout5->addWidget(ConnectActionButton);

    TextLabel2_2 = new QLabel(ConnectActionButtonGroup);
    TextLabel2_2->setObjectName(QString::fromUtf8("TextLabel2_2"));
    TextLabel2_2->setAlignment(Qt::AlignCenter);
    TextLabel2_2->setWordWrap(false);

    vboxLayout5->addWidget(TextLabel2_2);


    gridLayout5->addLayout(vboxLayout5, 0, 0, 1, 1);

    vboxLayout6 = new QVBoxLayout();
    vboxLayout6->setSpacing(3);
    vboxLayout6->setObjectName(QString::fromUtf8("vboxLayout6"));
    vboxLayout6->setContentsMargins(0, 0, 0, 0);
    DisconnectActionButton = new QToolButton(ConnectActionButtonGroup);
    DisconnectActionButton->setObjectName(QString::fromUtf8("DisconnectActionButton"));
    DisconnectActionButton->setMaximumSize(QSize(33, 33));
    DisconnectActionButton->setIcon(QIcon(QString::fromUtf8(":/icons/buttons/connectAction1.bmp")));
    DisconnectActionButton->setIconSize(QSize(32, 32));

    vboxLayout6->addWidget(DisconnectActionButton);

    TextLabel3_2 = new QLabel(ConnectActionButtonGroup);
    TextLabel3_2->setObjectName(QString::fromUtf8("TextLabel3_2"));
    TextLabel3_2->setAlignment(Qt::AlignCenter);
    TextLabel3_2->setWordWrap(false);

    vboxLayout6->addWidget(TextLabel3_2);


    gridLayout5->addLayout(vboxLayout6, 0, 1, 1, 1);


    gridLayout3->addWidget(ConnectActionButtonGroup, 0, 1, 1, 1);


    gridLayout1->addWidget(ConectionGroupBox, 1, 1, 2, 1);

    spacerItem6 = new QSpacerItem(50, 16, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout1->addItem(spacerItem6, 1, 2, 1, 1);

    spacerItem7 = new QSpacerItem(51, 16, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout1->addItem(spacerItem7, 2, 0, 1, 1);

    spacerItem8 = new QSpacerItem(322, 81, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout1->addItem(spacerItem8, 3, 1, 1, 1);

    MainTab->addTab(ToolsTab, QString());
    BuildingTab = new QWidget();
    BuildingTab->setObjectName(QString::fromUtf8("BuildingTab"));
    gridLayout6 = new QGridLayout(BuildingTab);
    gridLayout6->setSpacing(6);
    gridLayout6->setMargin(11);
    gridLayout6->setObjectName(QString::fromUtf8("gridLayout6"));
    buildingFrame = new QFrame(BuildingTab);
    buildingFrame->setObjectName(QString::fromUtf8("buildingFrame"));
    sizePolicy1.setHeightForWidth(buildingFrame->sizePolicy().hasHeightForWidth());
    buildingFrame->setSizePolicy(sizePolicy1);
    buildingFrame->setMinimumSize(QSize(460, 220));
    buildingFrame->setFrameShape(QFrame::NoFrame);
    buildingFrame->setFrameShadow(QFrame::Plain);
    buildingFrame->setLineWidth(0);
    vboxLayout7 = new QVBoxLayout(buildingFrame);
    vboxLayout7->setSpacing(6);
    vboxLayout7->setMargin(11);
    vboxLayout7->setObjectName(QString::fromUtf8("vboxLayout7"));
    vboxLayout8 = new QVBoxLayout();
    vboxLayout8->setSpacing(6);
    vboxLayout8->setObjectName(QString::fromUtf8("vboxLayout8"));
    hboxLayout5 = new QHBoxLayout();
    hboxLayout5->setSpacing(6);
    hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
    atomsGroupBox = new QGroupBox(buildingFrame);
    atomsGroupBox->setObjectName(QString::fromUtf8("atomsGroupBox"));
    sizePolicy1.setHeightForWidth(atomsGroupBox->sizePolicy().hasHeightForWidth());
    atomsGroupBox->setSizePolicy(sizePolicy1);
    gridLayout7 = new QGridLayout(atomsGroupBox);
    gridLayout7->setSpacing(6);
    gridLayout7->setMargin(11);
    gridLayout7->setObjectName(QString::fromUtf8("gridLayout7"));
    gridLayout7->setHorizontalSpacing(0);
    gridLayout7->setVerticalSpacing(0);
    atomCButton = new QToolButton(atomsGroupBox);
    atomCButton->setObjectName(QString::fromUtf8("atomCButton"));
    atomCButton->setMinimumSize(QSize(24, 24));

    gridLayout7->addWidget(atomCButton, 0, 0, 1, 1);

    atomHButton = new QToolButton(atomsGroupBox);
    atomHButton->setObjectName(QString::fromUtf8("atomHButton"));
    atomHButton->setMinimumSize(QSize(24, 24));

    gridLayout7->addWidget(atomHButton, 0, 1, 1, 1);

    atomOButton = new QToolButton(atomsGroupBox);
    atomOButton->setObjectName(QString::fromUtf8("atomOButton"));
    atomOButton->setMinimumSize(QSize(24, 24));

    gridLayout7->addWidget(atomOButton, 0, 2, 1, 1);

    atomPlusButton = new QToolButton(atomsGroupBox);
    atomPlusButton->setObjectName(QString::fromUtf8("atomPlusButton"));
    atomPlusButton->setMinimumSize(QSize(24, 24));

    gridLayout7->addWidget(atomPlusButton, 0, 3, 1, 1);

    atomMinusButton = new QToolButton(atomsGroupBox);
    atomMinusButton->setObjectName(QString::fromUtf8("atomMinusButton"));
    atomMinusButton->setMinimumSize(QSize(24, 24));

    gridLayout7->addWidget(atomMinusButton, 0, 4, 1, 1);

    atomNButton = new QToolButton(atomsGroupBox);
    atomNButton->setObjectName(QString::fromUtf8("atomNButton"));
    atomNButton->setMinimumSize(QSize(24, 24));

    gridLayout7->addWidget(atomNButton, 1, 0, 1, 1);

    atomSButton = new QToolButton(atomsGroupBox);
    atomSButton->setObjectName(QString::fromUtf8("atomSButton"));
    atomSButton->setMinimumSize(QSize(24, 24));

    gridLayout7->addWidget(atomSButton, 1, 1, 1, 1);

    atomPButton = new QToolButton(atomsGroupBox);
    atomPButton->setObjectName(QString::fromUtf8("atomPButton"));
    atomPButton->setMinimumSize(QSize(24, 24));

    gridLayout7->addWidget(atomPButton, 1, 2, 1, 1);

    atomValencyPlusButton = new QToolButton(atomsGroupBox);
    atomValencyPlusButton->setObjectName(QString::fromUtf8("atomValencyPlusButton"));
    atomValencyPlusButton->setMinimumSize(QSize(24, 24));

    gridLayout7->addWidget(atomValencyPlusButton, 1, 3, 1, 1);

    atomValencyMinusButton = new QToolButton(atomsGroupBox);
    atomValencyMinusButton->setObjectName(QString::fromUtf8("atomValencyMinusButton"));
    atomValencyMinusButton->setMinimumSize(QSize(24, 24));

    gridLayout7->addWidget(atomValencyMinusButton, 1, 4, 1, 1);

    atomFButton = new QToolButton(atomsGroupBox);
    atomFButton->setObjectName(QString::fromUtf8("atomFButton"));
    atomFButton->setMinimumSize(QSize(24, 24));

    gridLayout7->addWidget(atomFButton, 2, 0, 1, 1);

    atomClButton = new QToolButton(atomsGroupBox);
    atomClButton->setObjectName(QString::fromUtf8("atomClButton"));
    atomClButton->setMinimumSize(QSize(24, 24));

    gridLayout7->addWidget(atomClButton, 2, 1, 1, 1);

    atomElementSelectorButton = new QToolButton(atomsGroupBox);
    atomElementSelectorButton->setObjectName(QString::fromUtf8("atomElementSelectorButton"));
    atomElementSelectorButton->setMinimumSize(QSize(24, 24));

    gridLayout7->addWidget(atomElementSelectorButton, 2, 2, 1, 1);

    atomDeleteButton = new QToolButton(atomsGroupBox);
    atomDeleteButton->setObjectName(QString::fromUtf8("atomDeleteButton"));
    atomDeleteButton->setMinimumSize(QSize(48, 24));

    gridLayout7->addWidget(atomDeleteButton, 2, 3, 1, 2);


    hboxLayout5->addWidget(atomsGroupBox);

    bondsGroupBox = new QGroupBox(buildingFrame);
    bondsGroupBox->setObjectName(QString::fromUtf8("bondsGroupBox"));
    sizePolicy1.setHeightForWidth(bondsGroupBox->sizePolicy().hasHeightForWidth());
    bondsGroupBox->setSizePolicy(sizePolicy1);
    gridLayout8 = new QGridLayout(bondsGroupBox);
    gridLayout8->setSpacing(6);
    gridLayout8->setMargin(11);
    gridLayout8->setObjectName(QString::fromUtf8("gridLayout8"));
    gridLayout8->setHorizontalSpacing(0);
    gridLayout8->setVerticalSpacing(0);
    bondSingleButton = new QToolButton(bondsGroupBox);
    bondSingleButton->setObjectName(QString::fromUtf8("bondSingleButton"));
    bondSingleButton->setMinimumSize(QSize(24, 24));

    gridLayout8->addWidget(bondSingleButton, 0, 0, 1, 1);

    bondDoubleButton = new QToolButton(bondsGroupBox);
    bondDoubleButton->setObjectName(QString::fromUtf8("bondDoubleButton"));
    bondDoubleButton->setMinimumSize(QSize(24, 24));

    gridLayout8->addWidget(bondDoubleButton, 0, 1, 1, 1);

    bondTripleButton = new QToolButton(bondsGroupBox);
    bondTripleButton->setObjectName(QString::fromUtf8("bondTripleButton"));
    bondTripleButton->setMinimumSize(QSize(24, 24));

    gridLayout8->addWidget(bondTripleButton, 1, 0, 1, 1);

    bondAromaticButton = new QToolButton(bondsGroupBox);
    bondAromaticButton->setObjectName(QString::fromUtf8("bondAromaticButton"));
    bondAromaticButton->setMinimumSize(QSize(24, 24));

    gridLayout8->addWidget(bondAromaticButton, 1, 1, 1, 1);

    bondDeleteButton = new QToolButton(bondsGroupBox);
    bondDeleteButton->setObjectName(QString::fromUtf8("bondDeleteButton"));
    bondDeleteButton->setMinimumSize(QSize(48, 24));

    gridLayout8->addWidget(bondDeleteButton, 2, 0, 1, 2);


    hboxLayout5->addWidget(bondsGroupBox);

    carbonChainGroupBox = new QGroupBox(buildingFrame);
    carbonChainGroupBox->setObjectName(QString::fromUtf8("carbonChainGroupBox"));
    carbonChainGroupBox->setEnabled(true);
    sizePolicy1.setHeightForWidth(carbonChainGroupBox->sizePolicy().hasHeightForWidth());
    carbonChainGroupBox->setSizePolicy(sizePolicy1);
    carbonChainGroupBox->setMinimumSize(QSize(0, 0));
    carbonChainGroupBox->setFlat(false);
    carbonChainGroupBox->setCheckable(false);
    gridLayout9 = new QGridLayout(carbonChainGroupBox);
    gridLayout9->setSpacing(6);
    gridLayout9->setMargin(11);
    gridLayout9->setObjectName(QString::fromUtf8("gridLayout9"));
    gridLayout9->setHorizontalSpacing(0);
    gridLayout9->setVerticalSpacing(0);
    carbonChainLengthLineEdit = new QLineEdit(carbonChainGroupBox);
    carbonChainLengthLineEdit->setObjectName(QString::fromUtf8("carbonChainLengthLineEdit"));
    sizePolicy1.setHeightForWidth(carbonChainLengthLineEdit->sizePolicy().hasHeightForWidth());
    carbonChainLengthLineEdit->setSizePolicy(sizePolicy1);
    carbonChainLengthLineEdit->setMinimumSize(QSize(50, 24));
    carbonChainLengthLineEdit->setMaxLength(3);
    carbonChainLengthLineEdit->setAlignment(Qt::AlignRight);

    gridLayout9->addWidget(carbonChainLengthLineEdit, 0, 0, 1, 1);

    carbonChainAddRingButton = new QToolButton(carbonChainGroupBox);
    carbonChainAddRingButton->setObjectName(QString::fromUtf8("carbonChainAddRingButton"));
    carbonChainAddRingButton->setMinimumSize(QSize(95, 24));

    gridLayout9->addWidget(carbonChainAddRingButton, 0, 1, 1, 1);

    carbonChainHybridizationButtonGroup = new QButtonGroup(carbonChainGroupBox);
    carbonChainHybridizationButtonGroup->setObjectName(QString::fromUtf8("carbonChainHybridizationButtonGroup"));
    sizePolicy1.setHeightForWidth(carbonChainHybridizationButtonGroup->sizePolicy().hasHeightForWidth());
    carbonChainHybridizationButtonGroup->setSizePolicy(sizePolicy1);
    carbonChainHybridizationButtonGroup->setFlat(true);
    carbonChainHybridizationButtonGroup->setLineWidth(0);
    carbonChainHybridizationButtonGroup->setExclusive(true);
    gridLayout10 = new QGridLayout(carbonChainHybridizationButtonGroup);
    gridLayout10->setSpacing(6);
    gridLayout10->setMargin(11);
    gridLayout10->setObjectName(QString::fromUtf8("gridLayout10"));
    gridLayout10->setHorizontalSpacing(0);
    gridLayout10->setVerticalSpacing(0);
    gridLayout10->setContentsMargins(0, 0, 0, 0);
    carbonChainSp2Button = new QToolButton(carbonChainHybridizationButtonGroup);
    carbonChainSp2Button->setObjectName(QString::fromUtf8("carbonChainSp2Button"));
    carbonChainSp2Button->setMinimumSize(QSize(50, 24));
    carbonChainSp2Button->setCheckable(true);

    gridLayout10->addWidget(carbonChainSp2Button, 0, 0, 1, 1);

    carbonChainSp3Button = new QToolButton(carbonChainHybridizationButtonGroup);
    carbonChainSp3Button->setObjectName(QString::fromUtf8("carbonChainSp3Button"));
    carbonChainSp3Button->setMinimumSize(QSize(50, 24));
    carbonChainSp3Button->setCheckable(true);
    carbonChainSp3Button->setChecked(true);

    gridLayout10->addWidget(carbonChainSp3Button, 1, 0, 1, 1);


    gridLayout9->addWidget(carbonChainHybridizationButtonGroup, 1, 0, 2, 1);

    carbonChainAddTransButton = new QToolButton(carbonChainGroupBox);
    carbonChainAddTransButton->setObjectName(QString::fromUtf8("carbonChainAddTransButton"));
    carbonChainAddTransButton->setMinimumSize(QSize(95, 24));

    gridLayout9->addWidget(carbonChainAddTransButton, 1, 1, 1, 1);

    carbonChainAddCisButton = new QToolButton(carbonChainGroupBox);
    carbonChainAddCisButton->setObjectName(QString::fromUtf8("carbonChainAddCisButton"));
    carbonChainAddCisButton->setMinimumSize(QSize(95, 24));

    gridLayout9->addWidget(carbonChainAddCisButton, 2, 1, 1, 1);


    hboxLayout5->addWidget(carbonChainGroupBox);


    vboxLayout8->addLayout(hboxLayout5);

    hboxLayout6 = new QHBoxLayout();
    hboxLayout6->setSpacing(6);
    hboxLayout6->setObjectName(QString::fromUtf8("hboxLayout6"));
    groupBox10 = new QGroupBox(buildingFrame);
    groupBox10->setObjectName(QString::fromUtf8("groupBox10"));
    hboxLayout7 = new QHBoxLayout(groupBox10);
    hboxLayout7->setSpacing(6);
    hboxLayout7->setMargin(11);
    hboxLayout7->setObjectName(QString::fromUtf8("hboxLayout7"));
    relaxButton = new QToolButton(groupBox10);
    relaxButton->setObjectName(QString::fromUtf8("relaxButton"));
    relaxButton->setEnabled(true);

    hboxLayout7->addWidget(relaxButton);

    relaxAllButton = new QToolButton(groupBox10);
    relaxAllButton->setObjectName(QString::fromUtf8("relaxAllButton"));
    relaxAllButton->setEnabled(true);

    hboxLayout7->addWidget(relaxAllButton);

    minimizeAllButton = new QToolButton(groupBox10);
    minimizeAllButton->setObjectName(QString::fromUtf8("minimizeAllButton"));
    minimizeAllButton->setEnabled(true);

    hboxLayout7->addWidget(minimizeAllButton);

    geometryChiralityButton = new QToolButton(groupBox10);
    geometryChiralityButton->setObjectName(QString::fromUtf8("geometryChiralityButton"));
    geometryChiralityButton->setEnabled(true);

    hboxLayout7->addWidget(geometryChiralityButton);


    hboxLayout6->addWidget(groupBox10);

    smilesStringGroupBox = new QGroupBox(buildingFrame);
    smilesStringGroupBox->setObjectName(QString::fromUtf8("smilesStringGroupBox"));
    smilesStringGroupBox->setEnabled(true);
    QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy4.setHorizontalStretch(0);
    sizePolicy4.setVerticalStretch(0);
    sizePolicy4.setHeightForWidth(smilesStringGroupBox->sizePolicy().hasHeightForWidth());
    smilesStringGroupBox->setSizePolicy(sizePolicy4);
    hboxLayout8 = new QHBoxLayout(smilesStringGroupBox);
    hboxLayout8->setSpacing(6);
    hboxLayout8->setMargin(11);
    hboxLayout8->setObjectName(QString::fromUtf8("hboxLayout8"));
    smilesStringLineEdit = new QLineEdit(smilesStringGroupBox);
    smilesStringLineEdit->setObjectName(QString::fromUtf8("smilesStringLineEdit"));

    hboxLayout8->addWidget(smilesStringLineEdit);

    smilesStringAddButton = new QToolButton(smilesStringGroupBox);
    smilesStringAddButton->setObjectName(QString::fromUtf8("smilesStringAddButton"));

    hboxLayout8->addWidget(smilesStringAddButton);


    hboxLayout6->addWidget(smilesStringGroupBox);


    vboxLayout8->addLayout(hboxLayout6);


    vboxLayout7->addLayout(vboxLayout8);


    gridLayout6->addWidget(buildingFrame, 0, 1, 2, 1);

    spacerItem9 = new QSpacerItem(30, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout6->addItem(spacerItem9, 0, 2, 1, 1);

    spacerItem10 = new QSpacerItem(16, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout6->addItem(spacerItem10, 1, 0, 1, 1);

    spacerItem11 = new QSpacerItem(460, 71, QSizePolicy::Minimum, QSizePolicy::Expanding);

    gridLayout6->addItem(spacerItem11, 2, 1, 1, 1);

    MainTab->addTab(BuildingTab, QString());

    vboxLayout->addWidget(MainTab);

    hboxLayout9 = new QHBoxLayout();
    hboxLayout9->setSpacing(6);
    hboxLayout9->setObjectName(QString::fromUtf8("hboxLayout9"));
    hboxLayout9->setContentsMargins(0, 0, 0, 0);
    okButton = new QPushButton(widget);
    okButton->setObjectName(QString::fromUtf8("okButton"));
    sizePolicy1.setHeightForWidth(okButton->sizePolicy().hasHeightForWidth());
    okButton->setSizePolicy(sizePolicy1);

    hboxLayout9->addWidget(okButton);

    undoButton = new QPushButton(widget);
    undoButton->setObjectName(QString::fromUtf8("undoButton"));
    sizePolicy1.setHeightForWidth(undoButton->sizePolicy().hasHeightForWidth());
    undoButton->setSizePolicy(sizePolicy1);

    hboxLayout9->addWidget(undoButton);

    applyButton = new QPushButton(widget);
    applyButton->setObjectName(QString::fromUtf8("applyButton"));
    sizePolicy1.setHeightForWidth(applyButton->sizePolicy().hasHeightForWidth());
    applyButton->setSizePolicy(sizePolicy1);

    hboxLayout9->addWidget(applyButton);

    resetButton = new QPushButton(widget);
    resetButton->setObjectName(QString::fromUtf8("resetButton"));
    sizePolicy1.setHeightForWidth(resetButton->sizePolicy().hasHeightForWidth());
    resetButton->setSizePolicy(sizePolicy1);

    hboxLayout9->addWidget(resetButton);

    cancelButton = new QPushButton(widget);
    cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
    sizePolicy1.setHeightForWidth(cancelButton->sizePolicy().hasHeightForWidth());
    cancelButton->setSizePolicy(sizePolicy1);

    hboxLayout9->addWidget(cancelButton);


    vboxLayout->addLayout(hboxLayout9);

    MolEditorBase->setCentralWidget(widget);

    retranslateUi(MolEditorBase);

    MainTab->setCurrentIndex(0);


    QMetaObject::connectSlotsByName(MolEditorBase);
    } // setupUi

    void retranslateUi(QMainWindow *MolEditorBase)
    {
    MolEditorBase->setWindowTitle(QApplication::translate("MolEditorBase", "Molecule Editor", 0, QApplication::UnicodeUTF8));
    MainTab->setToolTip(QString());
    MainTab->setWhatsThis(QString());
    bondLenghtGroupBox->setTitle(QApplication::translate("MolEditorBase", "Bond Length", 0, QApplication::UnicodeUTF8));
    TextLabel4_4_2_2_3_2_2_2->setText(QApplication::translate("MolEditorBase", "length [\303\205]", 0, QApplication::UnicodeUTF8));
    bondLengthLineView->setToolTip(QApplication::translate("MolEditorBase", "current bond length", 0, QApplication::UnicodeUTF8));
    bondLengthLineView->setText(QApplication::translate("MolEditorBase", "0", 0, QApplication::UnicodeUTF8));
    bondLengthLineEdit->setText(QApplication::translate("MolEditorBase", "0", 0, QApplication::UnicodeUTF8));
    absoluteBondLengthButton->setToolTip(QApplication::translate("MolEditorBase", "set to absolute length", 0, QApplication::UnicodeUTF8));
    absoluteBondLengthButton->setText(QString());
    relativeBondLengthButton->setToolTip(QApplication::translate("MolEditorBase", "stretch relative to current length", 0, QApplication::UnicodeUTF8));
    relativeBondLengthButton->setText(QString());
    showStretchDraggerButton->setToolTip(QApplication::translate("MolEditorBase", "show dragger", 0, QApplication::UnicodeUTF8));
    showStretchDraggerButton->setText(QString());
    torsionGroupBox->setTitle(QApplication::translate("MolEditorBase", "Torsion", 0, QApplication::UnicodeUTF8));
    TextLabel4_4_2_2_2->setText(QApplication::translate("MolEditorBase", "angle [\302\260]", 0, QApplication::UnicodeUTF8));
    bondTorsionLineEdit->setToolTip(QApplication::translate("MolEditorBase", "move relative to current position", 0, QApplication::UnicodeUTF8));
    bondTorsionLineEdit->setText(QApplication::translate("MolEditorBase", "0", 0, QApplication::UnicodeUTF8));
    bondTorsionLineView->setToolTip(QApplication::translate("MolEditorBase", "current bond torsion", 0, QApplication::UnicodeUTF8));
    bondTorsionLineView->setText(QApplication::translate("MolEditorBase", "0", 0, QApplication::UnicodeUTF8));
    absoluteBondTorsionButton->setToolTip(QApplication::translate("MolEditorBase", "set to absolute torsion", 0, QApplication::UnicodeUTF8));
    absoluteBondTorsionButton->setText(QString());
    relativeBondTorsionButton->setToolTip(QApplication::translate("MolEditorBase", "rotate relative to current torsion", 0, QApplication::UnicodeUTF8));
    relativeBondTorsionButton->setText(QString());
    showRotationDraggerButton->setToolTip(QApplication::translate("MolEditorBase", "show dragger", 0, QApplication::UnicodeUTF8));
    showRotationDraggerButton->setText(QString());
    positionButtonGroup->setTitle(QApplication::translate("MolEditorBase", "Position", 0, QApplication::UnicodeUTF8));
    moveXLineView->setToolTip(QApplication::translate("MolEditorBase", "current x", 0, QApplication::UnicodeUTF8));
    moveXLineView->setText(QApplication::translate("MolEditorBase", "0", 0, QApplication::UnicodeUTF8));
    moveYLineView->setToolTip(QApplication::translate("MolEditorBase", "current y", 0, QApplication::UnicodeUTF8));
    moveYLineView->setText(QApplication::translate("MolEditorBase", "0", 0, QApplication::UnicodeUTF8));
    moveZLineView->setToolTip(QApplication::translate("MolEditorBase", "current z", 0, QApplication::UnicodeUTF8));
    moveZLineView->setText(QApplication::translate("MolEditorBase", "0", 0, QApplication::UnicodeUTF8));
    moveXLineEdit->setText(QApplication::translate("MolEditorBase", "0", 0, QApplication::UnicodeUTF8));
    moveYLineEdit->setText(QApplication::translate("MolEditorBase", "0", 0, QApplication::UnicodeUTF8));
    moveZLineEdit->setText(QApplication::translate("MolEditorBase", "0", 0, QApplication::UnicodeUTF8));
    TextLabel2_4->setText(QApplication::translate("MolEditorBase", "x", 0, QApplication::UnicodeUTF8));
    TextLabel2_2_2->setToolTip(QApplication::translate("MolEditorBase", "move relative to current position", 0, QApplication::UnicodeUTF8));
    TextLabel2_2_2->setText(QApplication::translate("MolEditorBase", "y", 0, QApplication::UnicodeUTF8));
    TextLabel2_3_2->setText(QApplication::translate("MolEditorBase", "z", 0, QApplication::UnicodeUTF8));
    showMoveDraggerButton->setToolTip(QApplication::translate("MolEditorBase", "show dragger", 0, QApplication::UnicodeUTF8));
    showMoveDraggerButton->setText(QString());
    relativeMoveButton->setToolTip(QApplication::translate("MolEditorBase", "move relative to current position", 0, QApplication::UnicodeUTF8));
    relativeMoveButton->setText(QString());
    absoluteMoveButton->setToolTip(QApplication::translate("MolEditorBase", "move to absolute position", 0, QApplication::UnicodeUTF8));
    absoluteMoveButton->setText(QString());
    bondAngleGroupBox->setTitle(QApplication::translate("MolEditorBase", "Bond Angle", 0, QApplication::UnicodeUTF8));
    TextLabel4_4_2_2_3_2_3->setText(QApplication::translate("MolEditorBase", "angle [\302\260]", 0, QApplication::UnicodeUTF8));
    bondAngleLineView->setToolTip(QApplication::translate("MolEditorBase", "current bond angle", 0, QApplication::UnicodeUTF8));
    bondAngleLineView->setText(QApplication::translate("MolEditorBase", "0", 0, QApplication::UnicodeUTF8));
    bondAngleLineEdit->setText(QApplication::translate("MolEditorBase", "0", 0, QApplication::UnicodeUTF8));
    absoluteBondAngleButton->setToolTip(QApplication::translate("MolEditorBase", "set to absolute angle", 0, QApplication::UnicodeUTF8));
    absoluteBondAngleButton->setText(QString());
    relativeBondAngleButton->setToolTip(QApplication::translate("MolEditorBase", "bend relative ro current angle", 0, QApplication::UnicodeUTF8));
    relativeBondAngleButton->setText(QString());
    showBendDraggerButton->setToolTip(QApplication::translate("MolEditorBase", "show dragger", 0, QApplication::UnicodeUTF8));
    showBendDraggerButton->setText(QString());
    symmetricBondAngleButton->setToolTip(QApplication::translate("MolEditorBase", "apply symmetrically", 0, QApplication::UnicodeUTF8));
    symmetricBondAngleButton->setText(QString());
    MainTab->setTabText(MainTab->indexOf(TransformTab), QApplication::translate("MolEditorBase", "Transform", 0, QApplication::UnicodeUTF8));
    ChangeTopGroupBox->setTitle(QApplication::translate("MolEditorBase", "Change Topology", 0, QApplication::UnicodeUTF8));
    CopySelectedButton->setToolTip(QApplication::translate("MolEditorBase", "copy selected atoms into new molecule", 0, QApplication::UnicodeUTF8));
    CopySelectedButton->setText(QString());
    TextLabel1_2->setText(QApplication::translate("MolEditorBase", "Copy", 0, QApplication::UnicodeUTF8));
    SplitSelectedButton->setToolTip(QApplication::translate("MolEditorBase", "move selected atoms into new molecule", 0, QApplication::UnicodeUTF8));
    SplitSelectedButton->setText(QString());
    TextLabel2->setText(QApplication::translate("MolEditorBase", "Split", 0, QApplication::UnicodeUTF8));
    DeleteSelectedButton->setToolTip(QApplication::translate("MolEditorBase", "delete selected atoms", 0, QApplication::UnicodeUTF8));
    DeleteSelectedButton->setText(QString());
    TextLabel3->setText(QApplication::translate("MolEditorBase", "Cut", 0, QApplication::UnicodeUTF8));
    AddOtherButton->setToolTip(QApplication::translate("MolEditorBase", "add another molecule from the workarea", 0, QApplication::UnicodeUTF8));
    AddOtherButton->setText(QString());
    TextLabel4->setText(QApplication::translate("MolEditorBase", "Add", 0, QApplication::UnicodeUTF8));
    ConectionGroupBox->setTitle(QApplication::translate("MolEditorBase", "Connection of Selected Atoms", 0, QApplication::UnicodeUTF8));
    TextLabel1->setText(QApplication::translate("MolEditorBase", "Maximal Atom Distance:", 0, QApplication::UnicodeUTF8));
    MaximalAtomDistSlider->setToolTip(QApplication::translate("MolEditorBase", "set cutoff distance", 0, QApplication::UnicodeUTF8));
    MaximalAtomDistEdit->setToolTip(QApplication::translate("MolEditorBase", "set cutoff distance", 0, QApplication::UnicodeUTF8));
    MaximalAtomDistEdit->setWhatsThis(QString());
    ConnectModeButtonGroup->setTitle(QApplication::translate("MolEditorBase", "Mode", 0, QApplication::UnicodeUTF8));
    StandardConnectButton->setToolTip(QApplication::translate("MolEditorBase", "use the standard residue database", 0, QApplication::UnicodeUTF8));
    StandardConnectButton->setText(QString());
    BondLengthConnectButton->setToolTip(QApplication::translate("MolEditorBase", "use the bond-length table", 0, QApplication::UnicodeUTF8));
    BondLengthConnectButton->setText(QString());
    ExternalConnectButton->setToolTip(QApplication::translate("MolEditorBase", "bonds leading out of the selected area", 0, QApplication::UnicodeUTF8));
    ExternalConnectButton->setText(QString());
    AllSelectedConnectButton->setToolTip(QApplication::translate("MolEditorBase", "all bonds between selected atoms", 0, QApplication::UnicodeUTF8));
    AllSelectedConnectButton->setText(QString());
    DistanceConnectButton->setToolTip(QApplication::translate("MolEditorBase", "all bonds between neighboring atoms as specified by the maximal atom distance", 0, QApplication::UnicodeUTF8));
    DistanceConnectButton->setText(QString());
    ModeTextLabel->setText(QApplication::translate("MolEditorBase", "Current Mode:", 0, QApplication::UnicodeUTF8));
    ConnectActionButtonGroup->setTitle(QApplication::translate("MolEditorBase", "Action", 0, QApplication::UnicodeUTF8));
    ConnectActionButton->setToolTip(QApplication::translate("MolEditorBase", "add bonds in current mode", 0, QApplication::UnicodeUTF8));
    ConnectActionButton->setText(QString());
    TextLabel2_2->setText(QApplication::translate("MolEditorBase", "Add", 0, QApplication::UnicodeUTF8));
    DisconnectActionButton->setToolTip(QApplication::translate("MolEditorBase", "remove bonds in current mode", 0, QApplication::UnicodeUTF8));
    DisconnectActionButton->setText(QString());
    TextLabel3_2->setText(QApplication::translate("MolEditorBase", "Cut", 0, QApplication::UnicodeUTF8));
    MainTab->setTabText(MainTab->indexOf(ToolsTab), QApplication::translate("MolEditorBase", "Tools", 0, QApplication::UnicodeUTF8));
    atomsGroupBox->setTitle(QApplication::translate("MolEditorBase", "Atoms", 0, QApplication::UnicodeUTF8));
    atomCButton->setToolTip(QApplication::translate("MolEditorBase", "replace atom with carbon", 0, QApplication::UnicodeUTF8));
    atomCButton->setText(QApplication::translate("MolEditorBase", "C", 0, QApplication::UnicodeUTF8));
    atomHButton->setToolTip(QApplication::translate("MolEditorBase", "replace atom with hydrogen", 0, QApplication::UnicodeUTF8));
    atomHButton->setText(QApplication::translate("MolEditorBase", "H", 0, QApplication::UnicodeUTF8));
    atomOButton->setToolTip(QApplication::translate("MolEditorBase", "replace atom with oxygen", 0, QApplication::UnicodeUTF8));
    atomOButton->setText(QApplication::translate("MolEditorBase", "O", 0, QApplication::UnicodeUTF8));
    atomPlusButton->setToolTip(QApplication::translate("MolEditorBase", "increases formal charge of selected atom by one", 0, QApplication::UnicodeUTF8));
    atomPlusButton->setText(QApplication::translate("MolEditorBase", "+", 0, QApplication::UnicodeUTF8));
    atomMinusButton->setToolTip(QApplication::translate("MolEditorBase", "decreases formal charge of selected atom by one", 0, QApplication::UnicodeUTF8));
    atomMinusButton->setText(QApplication::translate("MolEditorBase", "-", 0, QApplication::UnicodeUTF8));
    atomNButton->setToolTip(QApplication::translate("MolEditorBase", "replace atom with nitrogen", 0, QApplication::UnicodeUTF8));
    atomNButton->setText(QApplication::translate("MolEditorBase", "N", 0, QApplication::UnicodeUTF8));
    atomSButton->setToolTip(QApplication::translate("MolEditorBase", "replace atom with sulphur", 0, QApplication::UnicodeUTF8));
    atomSButton->setText(QApplication::translate("MolEditorBase", "S", 0, QApplication::UnicodeUTF8));
    atomPButton->setToolTip(QApplication::translate("MolEditorBase", "replace atom with phosphor", 0, QApplication::UnicodeUTF8));
    atomPButton->setText(QApplication::translate("MolEditorBase", "P", 0, QApplication::UnicodeUTF8));
    atomValencyPlusButton->setToolTip(QApplication::translate("MolEditorBase", "increases valency of selected atom by one", 0, QApplication::UnicodeUTF8));
    atomValencyPlusButton->setText(QApplication::translate("MolEditorBase", "V+", 0, QApplication::UnicodeUTF8));
    atomValencyMinusButton->setToolTip(QApplication::translate("MolEditorBase", "decreases valency of selected atom by one", 0, QApplication::UnicodeUTF8));
    atomValencyMinusButton->setText(QApplication::translate("MolEditorBase", "V-", 0, QApplication::UnicodeUTF8));
    atomFButton->setToolTip(QApplication::translate("MolEditorBase", "replace atom with fluor", 0, QApplication::UnicodeUTF8));
    atomFButton->setText(QApplication::translate("MolEditorBase", "F", 0, QApplication::UnicodeUTF8));
    atomClButton->setToolTip(QApplication::translate("MolEditorBase", "replace atom with chlor", 0, QApplication::UnicodeUTF8));
    atomClButton->setText(QApplication::translate("MolEditorBase", "Cl", 0, QApplication::UnicodeUTF8));
    atomElementSelectorButton->setToolTip(QApplication::translate("MolEditorBase", "show periodic table", 0, QApplication::UnicodeUTF8));
    atomElementSelectorButton->setText(QApplication::translate("MolEditorBase", "->", 0, QApplication::UnicodeUTF8));
    atomDeleteButton->setToolTip(QApplication::translate("MolEditorBase", "deletes selected atoms", 0, QApplication::UnicodeUTF8));
    atomDeleteButton->setText(QApplication::translate("MolEditorBase", "Delete", 0, QApplication::UnicodeUTF8));
    bondsGroupBox->setTitle(QApplication::translate("MolEditorBase", "Bonds", 0, QApplication::UnicodeUTF8));
    bondSingleButton->setToolTip(QApplication::translate("MolEditorBase", "set bond order to single", 0, QApplication::UnicodeUTF8));
    bondSingleButton->setText(QApplication::translate("MolEditorBase", "-", 0, QApplication::UnicodeUTF8));
    bondDoubleButton->setToolTip(QApplication::translate("MolEditorBase", "set bond order to double", 0, QApplication::UnicodeUTF8));
    bondDoubleButton->setText(QApplication::translate("MolEditorBase", "=", 0, QApplication::UnicodeUTF8));
    bondTripleButton->setToolTip(QApplication::translate("MolEditorBase", "set bond order to triple", 0, QApplication::UnicodeUTF8));
    bondTripleButton->setText(QApplication::translate("MolEditorBase", "#", 0, QApplication::UnicodeUTF8));
    bondAromaticButton->setToolTip(QApplication::translate("MolEditorBase", "set bond order to aromatic", 0, QApplication::UnicodeUTF8));
    bondAromaticButton->setText(QApplication::translate("MolEditorBase", "~", 0, QApplication::UnicodeUTF8));
    bondDeleteButton->setToolTip(QApplication::translate("MolEditorBase", "delete  bond", 0, QApplication::UnicodeUTF8));
    bondDeleteButton->setText(QApplication::translate("MolEditorBase", "Delete", 0, QApplication::UnicodeUTF8));
    carbonChainGroupBox->setTitle(QApplication::translate("MolEditorBase", "Carbon Chains / Rings", 0, QApplication::UnicodeUTF8));
    carbonChainLengthLineEdit->setText(QApplication::translate("MolEditorBase", "6", 0, QApplication::UnicodeUTF8));
    carbonChainAddRingButton->setToolTip(QApplication::translate("MolEditorBase", "replace atom with ring", 0, QApplication::UnicodeUTF8));
    carbonChainAddRingButton->setText(QApplication::translate("MolEditorBase", "Add Ring", 0, QApplication::UnicodeUTF8));
    carbonChainHybridizationButtonGroup->setTitle(QString());
    carbonChainSp2Button->setText(QApplication::translate("MolEditorBase", "sp2", 0, QApplication::UnicodeUTF8));
    carbonChainSp3Button->setText(QApplication::translate("MolEditorBase", "sp3", 0, QApplication::UnicodeUTF8));
    carbonChainAddTransButton->setToolTip(QApplication::translate("MolEditorBase", "replace atom with chain", 0, QApplication::UnicodeUTF8));
    carbonChainAddTransButton->setText(QApplication::translate("MolEditorBase", "Add Trans Chain", 0, QApplication::UnicodeUTF8));
    carbonChainAddCisButton->setToolTip(QApplication::translate("MolEditorBase", "replace atom with chain", 0, QApplication::UnicodeUTF8));
    carbonChainAddCisButton->setText(QApplication::translate("MolEditorBase", "Add Cis Chain", 0, QApplication::UnicodeUTF8));
    groupBox10->setTitle(QApplication::translate("MolEditorBase", "Geometry", 0, QApplication::UnicodeUTF8));
    relaxButton->setToolTip(QApplication::translate("MolEditorBase", "switch chiral positions", 0, QApplication::UnicodeUTF8));
    relaxButton->setText(QApplication::translate("MolEditorBase", "Relax", 0, QApplication::UnicodeUTF8));
    relaxAllButton->setToolTip(QApplication::translate("MolEditorBase", "switch chiral positions", 0, QApplication::UnicodeUTF8));
    relaxAllButton->setText(QApplication::translate("MolEditorBase", "Relax All", 0, QApplication::UnicodeUTF8));
    minimizeAllButton->setToolTip(QApplication::translate("MolEditorBase", "switch chiral positions", 0, QApplication::UnicodeUTF8));
    minimizeAllButton->setText(QApplication::translate("MolEditorBase", "Optimize All", 0, QApplication::UnicodeUTF8));
    geometryChiralityButton->setToolTip(QApplication::translate("MolEditorBase", "switch chiral positions", 0, QApplication::UnicodeUTF8));
    geometryChiralityButton->setText(QApplication::translate("MolEditorBase", "Chirality", 0, QApplication::UnicodeUTF8));
    smilesStringGroupBox->setTitle(QApplication::translate("MolEditorBase", "SMILES String", 0, QApplication::UnicodeUTF8));
    smilesStringAddButton->setToolTip(QApplication::translate("MolEditorBase", "replace atom with smiles string", 0, QApplication::UnicodeUTF8));
    smilesStringAddButton->setText(QApplication::translate("MolEditorBase", "Add", 0, QApplication::UnicodeUTF8));
    MainTab->setTabText(MainTab->indexOf(BuildingTab), QApplication::translate("MolEditorBase", "Building", 0, QApplication::UnicodeUTF8));
    okButton->setToolTip(QApplication::translate("MolEditorBase", "accept changes", 0, QApplication::UnicodeUTF8));
    okButton->setText(QApplication::translate("MolEditorBase", "OK", 0, QApplication::UnicodeUTF8));
    undoButton->setToolTip(QApplication::translate("MolEditorBase", "undo last transformation (CTRL+z)", 0, QApplication::UnicodeUTF8));
    undoButton->setText(QApplication::translate("MolEditorBase", "Undo", 0, QApplication::UnicodeUTF8));
    undoButton->setShortcut(QApplication::translate("MolEditorBase", "Ctrl+Z", 0, QApplication::UnicodeUTF8));
    applyButton->setToolTip(QApplication::translate("MolEditorBase", "undo last transformation (CTRL+z)", 0, QApplication::UnicodeUTF8));
    applyButton->setText(QApplication::translate("MolEditorBase", "Apply", 0, QApplication::UnicodeUTF8));
    applyButton->setShortcut(QString());
    resetButton->setToolTip(QApplication::translate("MolEditorBase", "reset to initial molecule (CTRL+r)", 0, QApplication::UnicodeUTF8));
    resetButton->setText(QApplication::translate("MolEditorBase", "Reset", 0, QApplication::UnicodeUTF8));
    resetButton->setShortcut(QApplication::translate("MolEditorBase", "Ctrl+R", 0, QApplication::UnicodeUTF8));
    cancelButton->setToolTip(QApplication::translate("MolEditorBase", "discard changes", 0, QApplication::UnicodeUTF8));
    cancelButton->setText(QApplication::translate("MolEditorBase", "Cancel", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(MolEditorBase);
    } // retranslateUi

};

namespace Ui {
    class MolEditorBase: public Ui_MolEditorBase {};
} // namespace Ui

#endif // QXMOLEDITORBASE_H

/// @}
