/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen_file;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    GLwidget *widgetGL;
    QGroupBox *gB_Config;
    QVBoxLayout *verticalLayout;
    QCheckBox *checkBox_transparency;
    QWidget *widget_ss;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QSlider *horizontalSlider;
    QSpinBox *spinBox;
    QCheckBox *checkBox_spotlights;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_close;
    QMenuBar *menuBar;
    QMenu *menuOpen_file;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::ApplicationModal);
        MainWindow->resize(860, 549);
        actionOpen_file = new QAction(MainWindow);
        actionOpen_file->setObjectName(QStringLiteral("actionOpen_file"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(1);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 3, 3, 3);
        widgetGL = new GLwidget(centralWidget);
        widgetGL->setObjectName(QStringLiteral("widgetGL"));

        horizontalLayout->addWidget(widgetGL);

        gB_Config = new QGroupBox(centralWidget);
        gB_Config->setObjectName(QStringLiteral("gB_Config"));
        gB_Config->setMinimumSize(QSize(201, 0));
        gB_Config->setMaximumSize(QSize(201, 16777215));
        QFont font;
        font.setFamily(QStringLiteral("Felix Titling"));
        font.setPointSize(16);
        font.setKerning(true);
        gB_Config->setFont(font);
        gB_Config->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        verticalLayout = new QVBoxLayout(gB_Config);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        checkBox_transparency = new QCheckBox(gB_Config);
        checkBox_transparency->setObjectName(QStringLiteral("checkBox_transparency"));
        QFont font1;
        font1.setPointSize(12);
        checkBox_transparency->setFont(font1);
        checkBox_transparency->setChecked(false);

        verticalLayout->addWidget(checkBox_transparency);

        widget_ss = new QWidget(gB_Config);
        widget_ss->setObjectName(QStringLiteral("widget_ss"));
        widget_ss->setEnabled(true);
        widget_ss->setMouseTracking(false);
        widget_ss->setFocusPolicy(Qt::NoFocus);
        gridLayout = new QGridLayout(widget_ss);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSlider = new QSlider(widget_ss);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setCursor(QCursor(Qt::PointingHandCursor));
        horizontalSlider->setMinimum(1);
        horizontalSlider->setMaximum(100);
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(horizontalSlider);

        spinBox = new QSpinBox(widget_ss);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setFont(font1);
        spinBox->setMinimum(1);
        spinBox->setMaximum(100);

        horizontalLayout_2->addWidget(spinBox);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);


        verticalLayout->addWidget(widget_ss);

        checkBox_spotlights = new QCheckBox(gB_Config);
        checkBox_spotlights->setObjectName(QStringLiteral("checkBox_spotlights"));
        checkBox_spotlights->setFont(font1);

        verticalLayout->addWidget(checkBox_spotlights);

        verticalSpacer = new QSpacerItem(20, 397, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        pushButton_close = new QPushButton(gB_Config);
        pushButton_close->setObjectName(QStringLiteral("pushButton_close"));
        pushButton_close->setMinimumSize(QSize(80, 23));
        pushButton_close->setMaximumSize(QSize(80, 23));
        QFont font2;
        font2.setFamily(QStringLiteral("Arial"));
        font2.setPointSize(9);
        pushButton_close->setFont(font2);
        pushButton_close->setFocusPolicy(Qt::StrongFocus);
        pushButton_close->setToolTipDuration(-1);
        pushButton_close->setLayoutDirection(Qt::LeftToRight);
        pushButton_close->setAutoDefault(false);
        pushButton_close->setFlat(false);

        verticalLayout->addWidget(pushButton_close, 0, Qt::AlignHCenter);


        horizontalLayout->addWidget(gB_Config);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 860, 20));
        menuOpen_file = new QMenu(menuBar);
        menuOpen_file->setObjectName(QStringLiteral("menuOpen_file"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        menuBar->addAction(menuOpen_file->menuAction());
        menuOpen_file->addAction(actionOpen_file);

        retranslateUi(MainWindow);
        QObject::connect(pushButton_close, SIGNAL(clicked()), MainWindow, SLOT(close()));
        QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));
        QObject::connect(spinBox, SIGNAL(valueChanged(int)), horizontalSlider, SLOT(setValue(int)));
        QObject::connect(checkBox_transparency, SIGNAL(clicked(bool)), widget_ss, SLOT(setVisible(bool)));

        pushButton_close->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "OpenGL", Q_NULLPTR));
        actionOpen_file->setText(QApplication::translate("MainWindow", "Open file...", Q_NULLPTR));
        gB_Config->setTitle(QApplication::translate("MainWindow", "Configurations", Q_NULLPTR));
        checkBox_transparency->setText(QApplication::translate("MainWindow", "\320\237\321\200\320\276\320\267\321\200\320\260\321\207\320\275\320\276\321\201\321\202\321\214", Q_NULLPTR));
        checkBox_spotlights->setText(QApplication::translate("MainWindow", "\320\237\321\200\320\276\320\266\320\265\320\272\321\202\320\276\321\200\320\260", Q_NULLPTR));
        pushButton_close->setText(QApplication::translate("MainWindow", "&Quit", Q_NULLPTR));
        menuOpen_file->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
