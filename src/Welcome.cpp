
#include "Welcome.h"
#include "Parameters.h"
#include "VideoAnalyzer.h"
#include "Utils.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/core/core.hpp>
#include <Windows.h>
#include <process.h>
#include <QFileDialog>
#include <QMessageBox>


using namespace cv;
using namespace std;

int defaultBufferSize = 10; //number of frames to be summed before processing
int defaultKernelSize = 22; //size of the kernel for the adaptive threshold
int defaultHandThreshold = 40; //threshold for the hand identification
int defaultDrawThShift = 8; //bias to the threshold computed in the adaptive threshold function
int bufferDim = defaultBufferSize;
int kernelSize = defaultKernelSize * 2 + 1;
int handThreshold = defaultHandThreshold;
int DrawThShift = defaultDrawThShift;
int device = 0; //ID of the acquisition source 

bool showROIHand = false;
bool showDifference = false;
bool showVideo = false;

bool imageClean = false;
bool toStop = false;
bool isVideoPreview = false;
bool isVideoPlay = false;
bool isStart = true;
bool goOn = false;

string saveFile = ""; //filename for the saved draw
string fileName = ""; //filename of the loaded video

VideoCapture cap;

/**
 *  Thread for video preview of the webcam
 */
void threadVideoPreview(void *) {

    Mat frame;
    cap.open(device);
    namedWindow("Video Preview", WINDOW_NORMAL);
    HWND hwnd = (HWND) cvGetWindowHandle("Video Preview");
    while (cap.read(frame) && goOn && IsWindowVisible(hwnd)) {
        imshow("Video Preview", frame);
        if (waitKey(30) == 27) {
            break;
        }
    }
    destroyWindow("Video Preview");
    cap.release();
}

/**
 *  Thread for drawing acquisition via webcam
 */
void threadLive(void *) {
    VideoAnalyzer v(device);
    v.videoPlayer();
    isStart = true;
}

/**
 *  Thread for drawing acquisition via video file
 */
void threadFile(void *) {
    VideoAnalyzer v(fileName);
    v.videoPlayer();
    isStart = true;
}

Welcome::Welcome() {

    widget.setupUi(this);
    connect(widget.Start, SIGNAL(clicked()), this, SLOT(startDrawing()));
    connect(widget.roiHand, SIGNAL(clicked()), this, SLOT(changedROIHand()));
    connect(widget.imageCl, SIGNAL(clicked()), this, SLOT(changedImageClean()));
    connect(widget.difference, SIGNAL(clicked()), this, SLOT(changedDifference()));
    connect(widget.originalVideo, SIGNAL(clicked()), this, SLOT(changedVideo()));
    connect(widget.cameraOptions, SIGNAL(clicked()), this, SLOT(cameraOptions()));
    connect(widget.loadFile, SIGNAL(clicked()), this, SLOT(loadFile()));
    connect(widget.startVideo, SIGNAL(clicked()), this, SLOT(playVideo()));
    connect(widget.defaultSettings, SIGNAL(clicked()), this, SLOT(defaultParameters()));
    connect(widget.device, SIGNAL(valueChanged(int)), this, SLOT(changeDevice()));
    connect(widget.bufferSize, SIGNAL(valueChanged(int)), this, SLOT(valueChanged()));
    connect(widget.kernelSize, SIGNAL(valueChanged(int)), this, SLOT(valueChanged()));
    connect(widget.handIdentThr, SIGNAL(valueChanged(int)), this, SLOT(valueChanged()));
    connect(widget.drawTh, SIGNAL(valueChanged(int)), this, SLOT(valueChanged()));
    connect(widget.Videopreview, SIGNAL(clicked()), this, SLOT(videoPreview()));
    connect(widget.finishDraw, SIGNAL(clicked()), this, SLOT(finishDraw()));
    connect(widget.Exit, SIGNAL(clicked()), this, SLOT(exitProgram()));
    connect(widget.saveSketch, SIGNAL(clicked()), this, SLOT(save()));
    connect(widget.filtering, SIGNAL(clicked()), this, SLOT(bilinearFilter()));

    widget.Exit->setVisible(true);
    widget.roiHand->setVisible(false);
    widget.saveSketch->setVisible(false);
    widget.difference->setVisible(false);
    widget.originalVideo->setVisible(false);
    widget.imageCl->setVisible(false);
    widget.Start->setVisible(true);
    widget.finishDraw->setVisible(false);
    widget.startVideo->setEnabled(false);
    widget.bufferSize->setValue(defaultBufferSize);
    widget.kernelSize->setValue(defaultKernelSize);
    widget.handIdentThr->setValue(defaultHandThreshold);
    widget.drawTh->setValue(defaultDrawThShift);
    widget.defaultSettings->setChecked(true);
}

Welcome::~Welcome() {
}

/**
 * Start the drawing via webcam/pause the drawing
 */
void Welcome::startDrawing() {

    if (!isVideoPlay) {
        if (isStart) { //first video start
            toStop = false;
            isStart = false;
            goOn = false;
            widget.startVideo->setEnabled(false);
            TerminateThread(myhandeForStarting, -1);
            enableMenu();
            myhandleForApp = (HANDLE) _beginthread(&threadLive, 0, 0);
        } else { //video resume
            ResumeThread(myhandleForApp);
        }
        isVideoPlay = true;
        widget.Start->setText("Pause drawing");
    } else { //video pause
        SuspendThread(myhandleForApp);
        isVideoPlay = false;
        widget.Start->setText("Start drawing");
    }
}

/**
 * Play the video file/pause the video
 */
void Welcome::playVideo() {

    if (!isVideoPlay) {//first video start
        if (isStart & (fileName.compare("") != 0)) {
            toStop = false;
            goOn = false;
            isStart = false;
            widget.Start->setEnabled(false);
            TerminateThread(myhandeForStarting, -1);
            enableMenu();
            myhandleForApp = (HANDLE) _beginthread(&threadFile, 0, 0);
        } else {//resume
            ResumeThread(myhandleForApp);
        }
        isVideoPlay = true;
        widget.startVideo->setText("Stop video");
    } else {//pause
        SuspendThread(myhandleForApp);
        isVideoPlay = false;
        widget.startVideo->setText("Play video");
    }
}

void Welcome::defaultParameters() {

    if (widget.defaultSettings->isChecked()) {
        widget.bufferSize->setValue(defaultBufferSize);
        widget.kernelSize->setValue(defaultKernelSize);
        widget.handIdentThr->setValue(defaultHandThreshold);
        widget.drawTh->setValue(defaultDrawThShift);
    }
}

/**
 * Prepare the menu for the drawing session
 */
void Welcome::enableMenu() {

    widget.finishDraw->setVisible(true);
    widget.cameraOptions->setEnabled(false);
    widget.loadFile->setEnabled(false);
    widget.device->setEnabled(false);
    widget.Videopreview->setText("Video Preview");
    widget.Videopreview->setEnabled(false);
    widget.roiHand->setVisible(true);
    widget.saveSketch->setVisible(true);
    widget.filtering->setEnabled(false);
    widget.difference->setVisible(true);
    widget.originalVideo->setVisible(true);
    widget.imageCl->setVisible(true);
}

/**
 * Restore the menu back from the drawing session
 */
void Welcome::restoreMenu() {

    widget.saveSketch->setVisible(false);
    widget.roiHand->setChecked(false);
    widget.roiHand->setVisible(false);
    widget.difference->setVisible(false);
    widget.difference->setChecked(false);
    widget.originalVideo->setChecked(false);
    widget.originalVideo->setVisible(false);
    widget.imageCl->setVisible(false);
    widget.startVideo->setText("Play video");
    if (fileName.compare("") != 0) {
        widget.startVideo->setEnabled(true);
    }
    widget.Start->setText("Start drawing");
    widget.Start->setEnabled(true);
    widget.loadFile->setEnabled(true);
    widget.Videopreview->setEnabled(true);
    widget.cameraOptions->setEnabled(true);
    widget.filtering->setEnabled(true);
    widget.finishDraw->setVisible(false);
    widget.device->setEnabled(true);
    goOn = false;
    toStop = true;
    isStart = true;
    isVideoPlay = false;
    isVideoPreview = false;
    showROIHand = false;
    showDifference = false;
    showVideo = false;
    imageClean = false;
    saveFile = "";
}

void Welcome::valueChanged() {

    bufferDim = widget.bufferSize->value();
    kernelSize = widget.kernelSize->value();
    handThreshold = widget.handIdentThr->value();
    DrawThShift = widget.drawTh->value();

    kernelSize = kernelSize * 2 + 1;

    widget.Blabel->setText(QString::number(bufferDim));
    widget.KLabel->setText(QString::number(kernelSize));
    widget.HLabel->setText(QString::number(handThreshold));
    widget.labelDrawTh->setText(QString::number(DrawThShift));

    if ((handThreshold == defaultHandThreshold) & (bufferDim == defaultBufferSize) & (kernelSize == (defaultKernelSize * 2 + 1)) & (DrawThShift == defaultDrawThShift)) {
        widget.defaultSettings->setChecked(true);
    } else {
        widget.defaultSettings->setChecked(false);
    }
}

void Welcome::videoPreview() {

    if (!isVideoPreview && !goOn) {
        goOn = true;
        widget.filtering->setEnabled(false);
        widget.device->setEnabled(false);
        widget.Start->setEnabled(false);
        widget.startVideo->setEnabled(false);
        widget.cameraOptions->setEnabled(false);
        myhandeForStarting = (HANDLE) _beginthread(&threadVideoPreview, 0, 0);
        widget.Videopreview->setText("Stop Preview");
        isVideoPreview = true;
    } else {
        goOn = false;
        isVideoPreview = false;
        widget.filtering->setEnabled(true);
        widget.device->setEnabled(true);
        widget.Start->setEnabled(true);
        if (fileName.compare("") != 0) {
            widget.startVideo->setEnabled(true);
        }
        widget.cameraOptions->setEnabled(true);
        widget.Videopreview->setText("Video Preview");
        destroyWindow("Video Preview");
        cap.release();
    }
}

/**
 * Gives the user the possibility  load a video file
 */
void Welcome::loadFile() {
    
    QString f = QFileDialog::getOpenFileName(
            this,
            tr("Select a video file"),
            "C://",
            tr("Video file (*.avi *.wmv *.mov *.flv *.mp4);;All files (*.*) ")
            );
    QFileInfo file(f);
    if (!file.fileName().isEmpty()) {
        widget.fileName->setText(file.fileName());
        if (!isVideoPreview){
        widget.startVideo->setEnabled(true);
        }
        fileName = f.toStdString();
    }
}

/**
 * Give the user the possibility to select the output path
 */
void Welcome::save() {
    QString f = QFileDialog::getSaveFileName(0,
            "Select an output file",
            QDir::currentPath(),
            tr("Image Files (*.jpg)")
            );
    QFileInfo file(f);
    if (file.suffix().toStdString().compare("jpg") != 0) {
        saveFile += ".jpg";
    } else {
        saveFile = f.toStdString();
    }
}
/**
 * Applies a bilinear filter. 
 */
void Welcome::bilinearFilter() {
    QWidget::setEnabled(false);
    widget.filtering->setText("Filtering...");
    string fileToFilter, filteredFile;
    QString f = QFileDialog::getOpenFileName(
            this,
            tr("Select an image file"),
            "C://",
            tr("Image file (*.jpg);;All files (*.*) ")
            );
    QFileInfo file(f);
    if (!file.fileName().isEmpty()) {
        widget.fileName->setText(file.fileName());
        widget.startVideo->setEnabled(true);
        fileToFilter = f.toStdString();
        Mat toFilter = imread(fileToFilter, IMREAD_COLOR);
        if (!toFilter.data) {
            QWidget::setEnabled(true);
            widget.filtering->setText("Filter application");
            return;
        }
        Utils utils;
        utils.applyFilter(toFilter);
        
        f = QFileDialog::getSaveFileName(0,
                "Select an output file",
                QDir::currentPath(),
                tr("Image Files (*.jpg)")
                );
        QFileInfo file(f);
        if (file.fileName().isEmpty()){
            QWidget::setEnabled(true);
            widget.filtering->setText("Filter application");
            return;
        }
        if (file.suffix().toStdString().compare("jpg") != 0) {
            filteredFile += ".jpg";
        } else {
            filteredFile = f.toStdString();
        }
        imwrite(filteredFile, toFilter);
    }
    QWidget::setEnabled(true);
    widget.filtering->setText("Filter application");
}

/**
 * Exit the programm
 */
void Welcome::exitProgram() {
    TerminateThread(myhandeForStarting, -1);
    TerminateThread(myhandleForApp, -1);
    QApplication::quit();
}

void Welcome::finishDraw() {
    ResumeThread(myhandleForApp);
    restoreMenu();
    //TerminateThread(myhandleForApp, -1);
}

void Welcome::changedROIHand() {
    showROIHand = widget.roiHand->isChecked();
}

void Welcome::changedDifference() {
    showDifference = widget.difference->isChecked();
}

void Welcome::changedVideo() {
    showVideo = widget.originalVideo->isChecked();
}

void Welcome::changedImageClean() {
    imageClean = true;
}

void Welcome::changeDevice() {
    device = widget.device->value();
}

void Welcome::cameraOptions() {
    cap.open(device);
    cap.set(CV_CAP_PROP_SETTINGS, 1);
}
