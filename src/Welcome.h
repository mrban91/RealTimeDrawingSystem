
#ifndef _WELCOME_H
#define	_WELCOME_H

#include "ui_Welcome.h"
 #include <Windows.h>
#include <stdio.h>
#include "Introduction.h"

/**
 * Class managing the GUI and user define parameters
 */
class Welcome : public QDialog {
    Q_OBJECT
public:
    Welcome();
    virtual ~Welcome();
    HANDLE myhandeForStarting;
    HANDLE myhandleForApp;
    Introduction introduction;
public slots:
    void startDrawing();
    void changedROIHand();
    void changedDifference();
    void changedVideo();
    void changedImageClean();
    void cameraOptions();
    void loadFile();
    void playVideo();
    void defaultParameters();
    void enableMenu();
    void restoreMenu();
    void changeDevice();
    void valueChanged();
    void videoPreview();
    void finishDraw();
    void bilinearFilter();
    void save();
    void exitProgram();
private:
    Ui::Welcome widget;
};

#endif	/* _WELCOME_H */
