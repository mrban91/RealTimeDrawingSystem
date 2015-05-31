
#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "VideoAnalyzer.h"
#include "Utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <process.h>


using namespace cv;
using namespace std;

extern bool showROIHand; //global variables
extern bool showDifference;
extern bool showVideo;
extern bool imageClean;
extern bool toStop;
extern string saveFile;



VideoAnalyzer::VideoAnalyzer() {

    webcam = 0;
    counter = 0;
    videoName = "";
    isVideoSourceOpen = false;
}

VideoAnalyzer::VideoAnalyzer(String videoN) {

    isVideoSourceOpen = false;
    webcam = -1;
    counter = 0;
    videoName = videoN;
}

VideoAnalyzer::VideoAnalyzer(int cap) {

    isVideoSourceOpen = false;
    webcam = cap;
    counter = 0;
    videoName = "";
}

VideoAnalyzer::VideoAnalyzer(const VideoAnalyzer& orig) {
}

VideoAnalyzer::~VideoAnalyzer() {
}

/**
 * Initialize all the data after the calibration is doen
 */
void VideoAnalyzer::dataInitializer() {

    draw = Mat(frame.rows, frame.cols, 0, double(0));
    coloredDraw = Mat(frame.rows, frame.cols, 16);
    coloredDraw.setTo(Scalar(255, 255, 255), noArray());
    mappedDraw = Mat(210 * 5, 297 * 5, 0, double(0)); //size of A4 sheet
    coloredMappedDraw = Mat(210 * 5, 297 * 5, 16);
    coloredMappedDraw.setTo(Scalar(255, 255, 255), noArray());
    buffer = Mat(frame.rows, frame.cols, 0, double(0));
    cvtColor(frame, grayFrame, CV_BGR2GRAY);
    firstFrame = grayFrame.clone();

    Mat grayFrameH;
    warpPerspective(firstFrame, grayFrameH, sheetDetector.calib.transmMatrix.tranformation, mappedDraw.size());
    digitFinder.initialize(grayFrameH);

    int dist = mappedDraw.cols / 24; //distance from between the border and the cross
    areaButtons = Rect(dist, 0, mappedDraw.cols - dist - dist, mappedDraw.rows / 6);

    namedWindow("DRAW", WINDOW_NORMAL);

}

/**
 * Try to open the videosource.
 * If the source if a wecam if it try for a maximum of 3 frame to read a frame.
 * If it is not succesfull it stop and exit
 */
void VideoAnalyzer::videoStarter() {

    if (videoName.size() == 0) {
        cap.open(webcam);
    } else {
        cap.open(videoName);
    }

    if (!cap.isOpened()) // if not success, exit program
    {
        cout << "Cannot open the video source" << endl;
        isVideoSourceOpen = false;
    }

    cap.set(CV_CAP_PROP_FRAME_WIDTH, 2000); //set the resolution to the highest possible
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 2000);

    Mat tempFrame;
    int counter = 1;
    while ((!cap.read(tempFrame)) & (counter < 3)) { //test the availability of the video source
        counter++;
    }
    if (counter == 3) {
        cout << "Cannot open the video source" << endl;
        isVideoSourceOpen = false;
    } else {
        isVideoSourceOpen = true;
    }
}

/**
 * Call the method that open the source and read all the frame using a while 
 * loop
 */
void VideoAnalyzer::videoPlayer() {

    VideoAnalyzer::videoStarter();
    if (isVideoSourceOpen) {
        while (cap.read(frame) & !toStop) {
            frameAnalysis();
            if (waitKey(30) == 27) break;
        }
        shutDown();
        return;
    }
}

/**
 * Perform the calibration if it is the first frame. If not it call all the method
 * needed for the frame analysis
 */
void VideoAnalyzer::frameAnalysis() {

    if ((!sheetDetector.calib.isDone) & (!sheetDetector.calib.transmMatrix.isDone)) {
        sheetDetector.sheetIdentification(frame);
        if ((sheetDetector.calib.isDone) & (sheetDetector.calib.transmMatrix.isDone)) {
            VideoAnalyzer::dataInitializer();
        }
    } else {
        frame = frame(sheetDetector.calib.toCrop); // crop the frame

        getDifference();
        inkDetector.drawIdentification(grayFrame, draw, buffer, counter, roiRect, coloredDraw);
        frameMapping();

        double min, max;
        minMaxIdx(areaOfButtonsHand, &min, &max);
        if (max == 0 && counter == 0) {
            digitFinder.findNewButtons(mappedDraw);
        }

        if (max > 0) {
            digitFinder.buttonPressed(areaOfButtonsHand, inkDetector.color);
        }

        imagesShow();
        save();
    }
}

/**
 *  Perform the homography on the Black&White and colored draw and update the
 *  buttons on the defined area
 */
void VideoAnalyzer::frameMapping() {

    if (counter == 0) { //only when the draw is updated
        warpPerspective(draw, mappedDraw, sheetDetector.calib.transmMatrix.tranformation, mappedDraw.size());
        warpAffine(mappedDraw, mappedDraw, sheetDetector.calib.rotMatrix, Size(mappedDraw.cols, mappedDraw.rows));
        warpPerspective(coloredDraw, coloredMappedDraw, sheetDetector.calib.transmMatrix.tranformation, coloredMappedDraw.size());
        warpAffine(coloredMappedDraw, coloredMappedDraw, sheetDetector.calib.rotMatrix, Size(coloredMappedDraw.cols, coloredMappedDraw.rows));
        digitFinder.drawButtons(coloredMappedDraw);
        bitwise_not(mappedDraw, mappedDraw);
    }
}

/**
 * Call the function that identify the hand.  If the hand is not found it update the
 * reference frame. It select the area where the buttons are and if the user request
 * it clean the draw.
 */
void VideoAnalyzer::getDifference() {

    Mat notDraw;
    bool found = false;

    cvtColor(frame, grayFrame, CV_BGR2GRAY);
    bitwise_not(draw, notDraw); // al this will have to go in difference
    difference = abs(grayFrame - firstFrame);
    bitwise_and(notDraw, difference, difference);

    inkDetector.handIdentification(difference, roiRect, roiHand, found);

    if (!found) { // if the hand is not found update the reference frame (improve rubostness to variation of light)
        firstFrame = grayFrame.clone();
    }

    if (imageClean) {
        inkDetector.cleanDraw(grayFrame, coloredDraw, roiHand);
        imageClean = false;
    }

    Mat tempHand;
    warpPerspective(roiHand, tempHand, sheetDetector.calib.transmMatrix.tranformation, mappedDraw.size());
    warpAffine(tempHand, tempHand, sheetDetector.calib.rotMatrix, mappedDraw.size());
    areaOfButtonsHand = tempHand(areaButtons);
}


/**
 * Cut the colored draw to eliminate the unwanted area and save the image
 */
void VideoAnalyzer::save() {
    
    if (saveFile.compare("") != 0) {
        int dist = coloredMappedDraw.cols / 24;
        Rect cutDraw(dist, (coloredMappedDraw.rows / 6), coloredMappedDraw.cols - dist - dist, 5 * (coloredMappedDraw.rows / 6));
        Mat drawToSave = coloredMappedDraw(cutDraw).clone();
        imwrite(saveFile, drawToSave); //non filtered version
    }
}

/**
 * Show the window accordingly to what is chhosed by the user
 */
void VideoAnalyzer::imagesShow() {

    imshow("DRAW", coloredMappedDraw);

    if (showROIHand) {
        imshow("Roi of the hand", roiHand);
    } else {
        destroyWindow("Roi of the hand");
    }

    if (showDifference) {
        imshow("Difference Image", difference);
    } else {
        destroyWindow("Difference Image");
    }

    if (showVideo) {
        imshow("Original video", frame);
    } else {
        destroyWindow("Original video");
    }
}

/**
 * Close all the window, release the video source handle and save the image.
 */
void VideoAnalyzer::shutDown() {
    destroyAllWindows();
    destroyWindow("DRAW");
    cap.release();
    if (sheetDetector.calib.isDone) {
        saveFile = "autoSaveDraw.jpg";
        save();
    }
}