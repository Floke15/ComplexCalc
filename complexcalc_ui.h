/********************************************************************************
** Form generated from reading UI file 'complexcalc.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMPLEXCALC_H
#define UI_COMPLEXCALC_H

#include "openglwindow.h"

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

QT_BEGIN_NAMESPACE

namespace Ui {
  class ComplexCalcUI
  {
  public:
    QWidget* centralWidget;
    QVBoxLayout* verticalLayout_2;
    QWidget* widget;
    QGridLayout* gridLayout;
    QPushButton* pushButton;
    Qt3DExtras::Qt3DWindow* openGL3DWindow;
    QTextEdit* textEdit;
    QListWidget* listWidget;
    QSlider* horizontalSlider;

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

      openGL3DWindow = new OpenGLWindow();
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

      pushButton->setText(QCoreApplication::translate("ComplexCalcClass", "neue Variable", nullptr));

      QMetaObject::connectSlotsByName(ComplexCalcClass);
    } // setupUi
  };
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMPLEXCALC_H
