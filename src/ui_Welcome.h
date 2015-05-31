/********************************************************************************
** Form generated from reading UI file 'Welcome.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WELCOME_H
#define UI_WELCOME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_Welcome
{
public:
    QGridLayout *gridLayout;
    QCheckBox *defaultSettings;
    QPushButton *startVideo;
    QSlider *kernelSize;
    QPushButton *cameraOptions;
    QLabel *labelDrawTh;
    QSlider *bufferSize;
    QLabel *Blabel;
    QLabel *label_4;
    QCheckBox *originalVideo;
    QSpinBox *device;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *saveSketch;
    QCheckBox *difference;
    QCheckBox *roiHand;
    QPushButton *Start;
    QLabel *KLabel;
    QPushButton *Videopreview;
    QLabel *HLabel;
    QPushButton *finishDraw;
    QLabel *fileName;
    QPushButton *imageCl;
    QLabel *label;
    QPushButton *loadFile;
    QSlider *handIdentThr;
    QSlider *drawTh;
    QPushButton *filtering;
    QPushButton *Exit;

    void setupUi(QDialog *Welcome)
    {
        if (Welcome->objectName().isEmpty())
            Welcome->setObjectName(QStringLiteral("Welcome"));
        Welcome->resize(653, 490);
        Welcome->setStyleSheet(QStringLiteral(""));
        gridLayout = new QGridLayout(Welcome);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(8);
        defaultSettings = new QCheckBox(Welcome);
        defaultSettings->setObjectName(QStringLiteral("defaultSettings"));

        gridLayout->addWidget(defaultSettings, 6, 0, 1, 1);

        startVideo = new QPushButton(Welcome);
        startVideo->setObjectName(QStringLiteral("startVideo"));

        gridLayout->addWidget(startVideo, 11, 2, 1, 1);

        kernelSize = new QSlider(Welcome);
        kernelSize->setObjectName(QStringLiteral("kernelSize"));
        kernelSize->setMinimum(1);
        kernelSize->setMaximum(99);
        kernelSize->setSingleStep(1);
        kernelSize->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(kernelSize, 1, 2, 1, 1);

        cameraOptions = new QPushButton(Welcome);
        cameraOptions->setObjectName(QStringLiteral("cameraOptions"));

        gridLayout->addWidget(cameraOptions, 6, 2, 1, 1);

        labelDrawTh = new QLabel(Welcome);
        labelDrawTh->setObjectName(QStringLiteral("labelDrawTh"));

        gridLayout->addWidget(labelDrawTh, 4, 3, 1, 1);

        bufferSize = new QSlider(Welcome);
        bufferSize->setObjectName(QStringLiteral("bufferSize"));
        bufferSize->setMinimum(2);
        bufferSize->setMaximum(40);
        bufferSize->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(bufferSize, 0, 2, 1, 1);

        Blabel = new QLabel(Welcome);
        Blabel->setObjectName(QStringLiteral("Blabel"));

        gridLayout->addWidget(Blabel, 0, 3, 1, 1);

        label_4 = new QLabel(Welcome);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 4, 0, 1, 1);

        originalVideo = new QCheckBox(Welcome);
        originalVideo->setObjectName(QStringLiteral("originalVideo"));

        gridLayout->addWidget(originalVideo, 14, 2, 1, 1);

        device = new QSpinBox(Welcome);
        device->setObjectName(QStringLiteral("device"));

        gridLayout->addWidget(device, 7, 2, 1, 1, Qt::AlignLeft);

        label_2 = new QLabel(Welcome);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(Welcome);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        saveSketch = new QPushButton(Welcome);
        saveSketch->setObjectName(QStringLiteral("saveSketch"));

        gridLayout->addWidget(saveSketch, 19, 0, 1, 1);

        difference = new QCheckBox(Welcome);
        difference->setObjectName(QStringLiteral("difference"));

        gridLayout->addWidget(difference, 15, 0, 1, 1);

        roiHand = new QCheckBox(Welcome);
        roiHand->setObjectName(QStringLiteral("roiHand"));

        gridLayout->addWidget(roiHand, 15, 2, 1, 1);

        Start = new QPushButton(Welcome);
        Start->setObjectName(QStringLiteral("Start"));

        gridLayout->addWidget(Start, 12, 2, 1, 1);

        KLabel = new QLabel(Welcome);
        KLabel->setObjectName(QStringLiteral("KLabel"));

        gridLayout->addWidget(KLabel, 1, 3, 1, 1);

        Videopreview = new QPushButton(Welcome);
        Videopreview->setObjectName(QStringLiteral("Videopreview"));

        gridLayout->addWidget(Videopreview, 7, 0, 1, 1);

        HLabel = new QLabel(Welcome);
        HLabel->setObjectName(QStringLiteral("HLabel"));

        gridLayout->addWidget(HLabel, 3, 3, 1, 1);

        finishDraw = new QPushButton(Welcome);
        finishDraw->setObjectName(QStringLiteral("finishDraw"));

        gridLayout->addWidget(finishDraw, 13, 2, 1, 1);

        fileName = new QLabel(Welcome);
        fileName->setObjectName(QStringLiteral("fileName"));

        gridLayout->addWidget(fileName, 10, 2, 1, 1);

        imageCl = new QPushButton(Welcome);
        imageCl->setObjectName(QStringLiteral("imageCl"));

        gridLayout->addWidget(imageCl, 14, 0, 1, 1);

        label = new QLabel(Welcome);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        loadFile = new QPushButton(Welcome);
        loadFile->setObjectName(QStringLiteral("loadFile"));

        gridLayout->addWidget(loadFile, 10, 0, 1, 1);

        handIdentThr = new QSlider(Welcome);
        handIdentThr->setObjectName(QStringLiteral("handIdentThr"));
        handIdentThr->setMinimum(25);
        handIdentThr->setMaximum(254);
        handIdentThr->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(handIdentThr, 3, 2, 1, 1);

        drawTh = new QSlider(Welcome);
        drawTh->setObjectName(QStringLiteral("drawTh"));
        drawTh->setMinimum(-10);
        drawTh->setMaximum(30);
        drawTh->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(drawTh, 4, 2, 1, 1);

        filtering = new QPushButton(Welcome);
        filtering->setObjectName(QStringLiteral("filtering"));

        gridLayout->addWidget(filtering, 20, 0, 1, 1);

        Exit = new QPushButton(Welcome);
        Exit->setObjectName(QStringLiteral("Exit"));

        gridLayout->addWidget(Exit, 20, 2, 1, 1);


        retranslateUi(Welcome);
        QObject::connect(Start, SIGNAL(clicked()), Start, SLOT(showMenu()));

        QMetaObject::connectSlotsByName(Welcome);
    } // setupUi

    void retranslateUi(QDialog *Welcome)
    {
        Welcome->setWindowTitle(QApplication::translate("Welcome", "Welcome", 0));
        defaultSettings->setText(QApplication::translate("Welcome", "Use Default Settings", 0));
        startVideo->setText(QApplication::translate("Welcome", "Play video", 0));
        cameraOptions->setText(QApplication::translate("Welcome", "Camera Options", 0));
        labelDrawTh->setText(QApplication::translate("Welcome", "TextLabel", 0));
        Blabel->setText(QApplication::translate("Welcome", "TextLabel", 0));
        label_4->setText(QApplication::translate("Welcome", "Adaptive treshold shift", 0));
        originalVideo->setText(QApplication::translate("Welcome", "Original video", 0));
        label_2->setText(QApplication::translate("Welcome", "Size of Kernel", 0));
        label_3->setText(QApplication::translate("Welcome", "Hand identification threshold", 0));
        saveSketch->setText(QApplication::translate("Welcome", "Save Sketch", 0));
        difference->setText(QApplication::translate("Welcome", "Show difference image", 0));
        roiHand->setText(QApplication::translate("Welcome", "Show ROI of the hand", 0));
        Start->setText(QApplication::translate("Welcome", "Start Drawing", 0));
        KLabel->setText(QApplication::translate("Welcome", "TextLabel", 0));
        Videopreview->setText(QApplication::translate("Welcome", "Video Preview", 0));
        HLabel->setText(QApplication::translate("Welcome", "TextLabel", 0));
        finishDraw->setText(QApplication::translate("Welcome", "Finish", 0));
        fileName->setText(QApplication::translate("Welcome", "No file loaded", 0));
        imageCl->setText(QApplication::translate("Welcome", "Clean image", 0));
        label->setText(QApplication::translate("Welcome", "Size of Buffer", 0));
        loadFile->setText(QApplication::translate("Welcome", "Load File", 0));
        filtering->setText(QApplication::translate("Welcome", "Filter application", 0));
        Exit->setText(QApplication::translate("Welcome", "Exit", 0));
    } // retranslateUi

};

namespace Ui {
    class Welcome: public Ui_Welcome {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WELCOME_H
