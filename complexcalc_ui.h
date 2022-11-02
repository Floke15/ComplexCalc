/********************************************************************************
** Form generated from reading UI file 'complexcalc.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMPLEXCALC_H
#define UI_COMPLEXCALC_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <Qt3DExtras>
#include <mainglwidget.h>

QT_BEGIN_NAMESPACE

class Ui_ComplexCalcClass
{
public:
  QAction* actionopen;
  QAction* actionsave_as;
  QAction* actionrecent;
  QAction* actionclose;
  QAction* actionAbout;
  QWidget* centralWidget;
  QVBoxLayout* verticalLayout_2;
  QWidget* widget;
  QGridLayout* gridLayout;
  QPushButton* pushButton;
  MainGLWidget* openGLWidget;
  Qt3DExtras::Qt3DWindow* openGL3DWindow;
  QTextEdit* textEdit;
  QListWidget* listWidget;
  QSlider* horizontalSlider;
  QMenuBar* menuBar;
  QMenu* menuFile;
  QMenu* menuhelp;
  QStatusBar* statusBar;

  void setupUi(QMainWindow* ComplexCalcClass)
  {
    if (ComplexCalcClass->objectName().isEmpty())
      ComplexCalcClass->setObjectName("ComplexCalcClass");
    ComplexCalcClass->resize(1013, 737);
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(ComplexCalcClass->sizePolicy().hasHeightForWidth());
    ComplexCalcClass->setSizePolicy(sizePolicy);
    actionopen = new QAction(ComplexCalcClass);
    actionopen->setObjectName("actionopen");
    actionsave_as = new QAction(ComplexCalcClass);
    actionsave_as->setObjectName("actionsave_as");
    actionrecent = new QAction(ComplexCalcClass);
    actionrecent->setObjectName("actionrecent");
    actionclose = new QAction(ComplexCalcClass);
    actionclose->setObjectName("actionclose");
    actionAbout = new QAction(ComplexCalcClass);
    actionAbout->setObjectName("actionAbout");
    centralWidget = new QWidget(ComplexCalcClass);
    centralWidget->setObjectName("centralWidget");
    verticalLayout_2 = new QVBoxLayout(centralWidget);
    verticalLayout_2->setSpacing(6);
    verticalLayout_2->setContentsMargins(11, 11, 11, 11);
    verticalLayout_2->setObjectName("verticalLayout_2");
    widget = new QWidget(centralWidget);
    widget->setObjectName("widget");
    gridLayout = new QGridLayout(widget);
    gridLayout->setSpacing(6);
    gridLayout->setContentsMargins(11, 11, 11, 11);
    gridLayout->setObjectName("gridLayout");
    pushButton = new QPushButton(widget);
    pushButton->setObjectName("pushButton");
    QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
    pushButton->setSizePolicy(sizePolicy1);

    gridLayout->addWidget(pushButton, 0, 1, 1, 1);

    /*openGLWidget = new MainGLWidget(widget);
    openGLWidget->setObjectName("openGLWidget");

    gridLayout->addWidget(openGLWidget, 1, 0, 1, 1);*/

    openGL3DWindow = new Qt3DExtras::Qt3DWindow();
    openGL3DWindow->defaultFrameGraph()->setClearColor(QColor(QRgb(0xFF0000)));
    gridLayout->addWidget(QWidget::createWindowContainer(openGL3DWindow));

    textEdit = new QTextEdit(widget);
    textEdit->setObjectName("textEdit");
    QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
    textEdit->setSizePolicy(sizePolicy2);
    textEdit->setMinimumSize(QSize(0, 0));
    textEdit->setMaximumSize(QSize(16777215, 20));
    textEdit->setInputMethodHints(Qt::ImhNone);
    textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    textEdit->setLineWrapMode(QTextEdit::NoWrap);

    gridLayout->addWidget(textEdit, 0, 0, 1, 1);

    listWidget = new QListWidget(widget);
    listWidget->setObjectName("listWidget");
    QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
    listWidget->setSizePolicy(sizePolicy3);

    gridLayout->addWidget(listWidget, 1, 1, 1, 1);


    verticalLayout_2->addWidget(widget);

    horizontalSlider = new QSlider(centralWidget);
    horizontalSlider->setObjectName("horizontalSlider");
    horizontalSlider->setOrientation(Qt::Horizontal);

    verticalLayout_2->addWidget(horizontalSlider);

    ComplexCalcClass->setCentralWidget(centralWidget);
    menuBar = new QMenuBar(ComplexCalcClass);
    menuBar->setObjectName("menuBar");
    menuBar->setGeometry(QRect(0, 0, 1013, 22));
    menuFile = new QMenu(menuBar);
    menuFile->setObjectName("menuFile");
    menuhelp = new QMenu(menuBar);
    menuhelp->setObjectName("menuhelp");
    ComplexCalcClass->setMenuBar(menuBar);
    statusBar = new QStatusBar(ComplexCalcClass);
    statusBar->setObjectName("statusBar");
    ComplexCalcClass->setStatusBar(statusBar);

    menuBar->addAction(menuFile->menuAction());
    menuBar->addAction(menuhelp->menuAction());
    menuFile->addAction(actionopen);
    menuFile->addAction(actionsave_as);
    menuFile->addAction(actionrecent);
    menuFile->addAction(actionclose);
    menuhelp->addAction(actionAbout);

    retranslateUi(ComplexCalcClass);

    QMetaObject::connectSlotsByName(ComplexCalcClass);
  } // setupUi

  void retranslateUi(QMainWindow* ComplexCalcClass)
  {
    ComplexCalcClass->setWindowTitle(QCoreApplication::translate("ComplexCalcClass", "ComplexCalc", nullptr));
    actionopen->setText(QCoreApplication::translate("ComplexCalcClass", "open", nullptr));
    actionsave_as->setText(QCoreApplication::translate("ComplexCalcClass", "save as", nullptr));
    actionrecent->setText(QCoreApplication::translate("ComplexCalcClass", "recent", nullptr));
    actionclose->setText(QCoreApplication::translate("ComplexCalcClass", "close", nullptr));
    actionAbout->setText(QCoreApplication::translate("ComplexCalcClass", "About", nullptr));
    pushButton->setText(QCoreApplication::translate("ComplexCalcClass", "neue Variable", nullptr));
    menuFile->setTitle(QCoreApplication::translate("ComplexCalcClass", "File", nullptr));
    menuhelp->setTitle(QCoreApplication::translate("ComplexCalcClass", "Help", nullptr));
  } // retranslateUi

};

namespace Ui {
  class ComplexCalcClass : public Ui_ComplexCalcClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMPLEXCALC_H
