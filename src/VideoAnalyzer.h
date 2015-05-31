
#include "Homography.h"
#include "SheetDetection.h"
#include "InkDetection.h"
#include "ButtonManager.h"

#ifndef VIDEOANALYZER_H
#define	VIDEOANALYZER_H

class VideoAnalyzer {
public:
    VideoAnalyzer();
    VideoAnalyzer(int cap);
    VideoAnalyzer(String videoName);
    VideoAnalyzer(const VideoAnalyzer& orig);

    virtual ~VideoAnalyzer();
    void videoStarter();
    void videoPlayer();
    void dataInitializer();
    void frameAnalysis();
    void frameMapping();
    void getDifference();
    void imagesShow();
    void shutDown();
    void save();
private:
    bool isVideoSourceOpen;
    int webcam; // -1 if loading video
    int counter; // checks if is it time to update the draw
    String videoName; // if capture > 0 it does not care
    VideoCapture cap;

    ButtonManager digitFinder;
    SheetDetection sheetDetector;
    InkDetection inkDetector;
    Mat firstFrame; //reference frame for the difference operation
    Mat grayFrame; //grayscale frame
    Mat frame; //colored frame 
    Mat draw; //not rectified version of the draw
    Mat buffer; //contains the summation of identified parts of the draw (at each frame)
    Mat mappedDraw; //rectified version of the draw
    Mat areaOfButtonsHand; //ROI of the hand in the area of interactive functionalities
    Mat roiRect; //estimated rectangular ROI of the hand
    Mat roiHand; //estimated convex ROI of the hand
    Mat coloredDraw; //non rectified version of the colored draw
    Mat coloredMappedDraw;//rectified version of the colored draw
    Mat difference;//difference image between grayframe and first frame
    Rect areaButtons;//rectangle for the identification of interactive functionalities

};

#endif	/* VIDEOANALYZER_H */

