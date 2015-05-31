
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/core/core.hpp>
#include "ButtonManager.h"
#include "InkDetection.h"
#include "ColorDecision.h"
#include "Utils.h"
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>     

using namespace cv;
using namespace std;

Mat paletteImg; //stores the palette image for color selection

ButtonManager::ButtonManager() {
}

/**
 * Sets the first frame and class parameters.
 * 
 * @param grayFrameH contains the first homographed frame 
 */
void ButtonManager::initialize(Mat grayFrameH) {

    firstAcquisition = true;
    colorCounter = 10;
    paletteImg = imread("palette.png");

    int dist = grayFrameH.cols / 24; //distance between the border and the cross
    Rect R(0, 0, grayFrameH.cols, grayFrameH.rows / 6); //identify the area of interactive functionalities with crosses
    Rect cutDraw(dist, 0, grayFrameH.cols - dist - dist, grayFrameH.rows / 6); // identify the area of interactive functionalities without crosses
    Mat areaWithCrossesAndButtons = grayFrameH(R); //crop
    firstFrame = areaWithCrossesAndButtons(cutDraw); //crop
    areaWithButtons = Mat::zeros(firstFrame.rows, firstFrame.cols, 0);
}

ButtonManager::ButtonManager(const ButtonManager& orig) {
}

ButtonManager::~ButtonManager() {
}

/**
 * Evaluates if a button is pressed.
 * If yes, the color of the line is changed accordly to the color associated to the button
 * 
 * @param roiHand contains the region of interest that represents tha hand 
 * @param colorSel current value (color) of the line in the final draw
 */
void ButtonManager::buttonPressed(const Mat& roiHand, Scalar& colorSel) {

    if (buttons.size() > 0) {
        Mat andMatrix; //contains the areas where there are buttons currenlty occluded 
        int codeButton; //scalar associated to the button most occluded
        int pressedArea; //number of pixel associated the the most frequent value
        Utils tools;
        double perctPress; // % of the total area of the button currently occluded

        threshold(roiHand, roiHand, 1, 255, THRESH_BINARY);
        bitwise_and(roiHand, areaWithButtons, andMatrix); //every button has a different scalar

        tools.uniqueValues(andMatrix, codeButton, pressedArea);

        if (codeButton == -1) {
            return;
        } else {
            for (int t = 0; t < buttons.size(); t++) {
                if (buttons[t]->counterAssociated == codeButton && buttons[t]->currentlyPressed == false) {
                    perctPress = double(pressedArea) / buttons[t]->area * 100;

                    if (perctPress > 80) {

                        colorSel = buttons[t]->color; //set the color of the line as the color associated to the button
                        for (int u = 0; u < buttons.size(); u++) {
                            buttons[u]->currentlyPressed = false;
                        }
                        buttons[t]->currentlyPressed = true;
                        return;
                    }
                }
            }
        }
    }
}

/**
 * Event handler for color decision through the palette.
 * 
 * @param event event to handle
 * @param x x coordinate
 * @param y y coordinate
 * @param 
 * @param ptr for storing the result
 */
void onMouse(int event, int x, int y, int, void *ptr) {
    ColorDecision*p = (ColorDecision*) ptr;
    if (event != CV_EVENT_LBUTTONDOWN) {
        return;
    }

    Vec3b pix = paletteImg.at<Vec3b>(y, x);
    int B = pix.val[0];
    int G = pix.val[1];
    int R = pix.val[2];

    (p->B) = B;
    (p->G) = G;
    (p->R) = R;
    (p->chosen) = true;

}

/**
 * Finds new buttons in the area of interactive functionalities.
 * 
 * @param source contains the mapped draw
 */
void ButtonManager::findNewButtons(const Mat &source) {

    if (!paletteImg.data) {
        return;
    }
    int dist = source.cols / 24; //distance between the border and the cross
    vector<vector<Point> > contours, correctContours; //contours found in the interactive functionalities
    vector<Point> polygonContour; //each polygon represents a button
    vector<Vec4i> hierarchy; //used in findContours
    Rect cutDraw(dist, 0, source.cols - dist - dist, source.rows / 6); //identify the area of interactive functionalities

    Mat roi = Mat::zeros(source.rows, source.cols, 0);
    Mat toSet = roi(cutDraw);
    toSet.setTo(255);

    Mat areaContainingButtons = source(cutDraw).clone();

    for (int i = 0; i < areaButtons.size(); i++) {
        Mat previousButton(areaContainingButtons, areaButtons[i]);
        previousButton = Scalar(255); //set to 255 the areas where other buttons are present. Only the new buttons will survive
    }

    bitwise_not(areaContainingButtons, areaContainingButtons);
    findContours(areaContainingButtons, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    if (contours.size() == 0) {
        return;
    }

    for (int i = 0; i < contours.size(); i++) {
        approxPolyDP(Mat(contours[i]), polygonContour, arcLength(Mat(contours[i]), true)*0.02, true);
        if ((contourArea(contours[i]) > 1000) && isContourConvex(polygonContour)) {
            correctContours.push_back(polygonContour); //add only polygons that are likely buttons
        }
    }

    if (correctContours.size() == 0) return;


    ColorDecision colorSelector;
    namedWindow("Palette", WINDOW_NORMAL);
    HWND hwnd = (HWND) cvGetWindowHandle("Palette");
    setMouseCallback("Palette", onMouse, &colorSelector);
    imshow("Palette", paletteImg); //show the palette for color decision
    Rect final;

    for (int i = 0; i < correctContours.size(); i++) { //the user decides the color for every button

        while (IsWindowVisible(hwnd)) {
            if (cvWaitKey(100) == 27) break;
            if (colorSelector.chosen) break;
        }

        if (!colorSelector.chosen) {
            colorSelector.B = 0;
            colorSelector.G = 0;
            colorSelector.R = 0;
            namedWindow("Palette", WINDOW_NORMAL);
            imshow("Palette", paletteImg);
            setMouseCallback("Palette", onMouse, &colorSelector);
            hwnd = (HWND) cvGetWindowHandle("Palette");
        }

        final = boundingRect(correctContours[i]);
        areaButtons.push_back(final); //add the current new button to the list of buttons

        fillConvexPoly(areaWithButtons, correctContours[i], Scalar(colorCounter), 8, 0); //fill the polygon with a unique scalar
        for (int j = 0; j < correctContours[i].size(); j++) { //remapping of the button contours
            correctContours[i][j].x = correctContours[i][j].x + dist;
        }

        Button* newButton = new Button(correctContours[i], colorCounter, colorSelector.R, colorSelector.G, colorSelector.B);
        buttons.push_back(newButton);
        colorCounter++;
        colorSelector.chosen = false;
    }
    destroyWindow("Palette");
}

/**
 * Draws the buttons directly on the final colored draw.
 * 
 * @param draw contais the final colored draw
 */
void ButtonManager::drawButtons(const Mat& draw) {

    int dist = draw.cols / 24; //distance between the border and the cross
    Rect buttonsArea(dist, 0, draw.cols - dist - dist, draw.rows / 6);
    Mat roi = draw(buttonsArea);
    roi.setTo(Scalar(255, 255, 255)); //erase all the buttons 
    for (int i = 0; i < buttons.size(); i++) {
        fillConvexPoly(draw, buttons[i]->contour, buttons[i]->color, 8, 0); //draw all the buttons
        if (buttons[i]->currentlyPressed) {
            vector<vector<Point> > contour;
            contour.push_back(buttons[i]->contour);
            drawContours(draw, contour, 0, Scalar(21, 243, 243), 8, 8); //draw a big contour around the currently selected button
        }
    }
}