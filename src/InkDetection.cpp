
#include "InkDetection.h"
using namespace cv;
using namespace std;

//user defined parameters via GUI
extern int handThreshold;
extern int kernelSize;
extern int bufferDim;
extern int DrawThShift;

InkDetection::InkDetection() {
    color.val[0] = 0;
    color.val[1] = 0;
    color.val[2] = 0;
}

InkDetection::InkDetection(const InkDetection& orig) {
}

InkDetection::~InkDetection() {
}

/**
 * Function that identifies the hand by using the difference image between the current
 * frame and a frame in which the hand is not present. 
 * 
 * @param src Input image
 * @param roiRect identified hand using as a ROI a rect
 * @param roiHand identified hand using as a ROI the original region
 * @param found true if hand has been found
 */
void InkDetection::handIdentification(Mat& diff, Mat & roiRect, Mat & roiHand, bool& found) {
 
    Mat zeroMat = Mat::zeros(diff.rows, diff.cols, diff.type());
    Mat result, temp;
    Mat source = diff.clone();
    vector<Vec4i> hierarchy;
    hierarchy.clear();
    vector<vector<Point> > contours;
    int dilation_size = 2;
    
    threshold(diff, result, handThreshold, 255, THRESH_BINARY); 
    Mat element = getStructuringElement(MORPH_RECT, Size(2 * dilation_size + 1, 2 * dilation_size + 1), Point(dilation_size, dilation_size));
    erode(result, temp, element, Point(-1, -1), 1); 
    dilate(temp, result, element, Point(-1, -1), 6);

    findContours(result, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    if (contours.size() != 0) {
        vector<vector<Point> > convexContours(contours.size());
        vector<Rect> boundRect(contours.size());
        for (int i = 0; i < contours.size(); i++) { //approximates all the contours as bounding rects and convex polygons
         // approxPolyDP(Mat(contours[i]), convexContours[i], arcLength(Mat(contours[i]), true)*0.02, true); // alternative to convexHull
            boundRect[i] = boundingRect(contours[i]); // rectangular roi
            convexHull(contours[i], convexContours[i]);  
        }
        
        int maxIndex = 0;
        double maxArea = boundRect[0].area();
        Mat tmp = Mat::zeros(source.rows, source.cols, 0);
        for (int z = 0; z < boundRect.size(); z++) {  // identify the contour with the biggets area
            if (boundRect[z].area() > maxArea) {
                maxArea = boundRect[z].area();
                maxIndex = z;
            }
            tmp = Mat::zeros(source.rows, source.cols, 0);
        }
        if (boundRect[maxIndex].area() > 5000) {
            Mat toRemoveHand = Mat::zeros(source.rows, source.cols, 0); 
            Mat toRemoveRect = Mat::zeros(source.rows, source.cols, 0);
            fillConvexPoly(toRemoveHand, convexContours[maxIndex], Scalar(255), 8, 0); // set convex roi
            Mat roi = toRemoveRect(Rect(boundRect[maxIndex].x, boundRect[maxIndex].y, boundRect[maxIndex].width, boundRect[maxIndex].height)); // Set rectangular roi
            roi.setTo(255);
            roiRect = toRemoveRect.clone();
            roiHand = toRemoveHand.clone();
            found = true;
        } else { // not found
            found = false;
            roiRect = zeroMat.clone();
            roiHand = zeroMat.clone();
        }
    } else { // not found
        found = false;
        roiRect = zeroMat.clone();
        roiHand = zeroMat.clone();      
    }
}

/**
 * Function that identifies the draw. To avoid/reduce the artifacts a buffer is used.
 * The buffer is a matrix of the size of the frame. At every frame the draw is identified and is added
 * to the buffer. When the buffer is full only the parts of the draw that have appeared in
 * all the previous bufferDim frames are considered
 * 
 * @param frame Input image
 * @param draw Black&White draw (not homographed)
 * @param buffer Buffer containig the sum of the previous draw
 * @param counter Counter to check when the buffer is full
 * @param roiHand Roi fo the hand (can be rectangular or convex)
 * @param coloredDraw Draw with color (not homographed)
 */
void InkDetection::drawIdentification(const Mat& grayFrame, Mat& draw, Mat& buffer, int& counter, Mat& roiHand,Mat& coloredDraw) {

    Mat grayF, drawOr, bufferTh, drawOrBuffer,roi;
    if (counter < bufferDim) {
        adaptiveThreshold(grayFrame, grayF, 1, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, kernelSize,DrawThShift);
        bitwise_not(roiHand, roi, noArray());
        bitwise_and(roi, grayF, grayF, noArray()); // do not consider the part identified as hand
        if (counter == 0) {
            buffer = Mat(grayFrame.rows, grayFrame.cols, 0, double(0));
        }
        buffer = buffer + grayF; // update the buffer
        counter = counter + 1;
    }

    if (counter == bufferDim) { // if the buffer is full (parameters defined by GUI))
        bitwise_not(draw, drawOr, noArray());
        threshold(buffer, bufferTh, bufferDim - 1, 255, THRESH_BINARY); // consider only the parts that have appeared in all the frame of the buffer 
        bitwise_and(bufferTh, drawOr, drawOrBuffer, noArray()); // get the new part of the draw  
        bitwise_or(drawOrBuffer, draw, draw, noArray()); // add the new part to the black&white image

        coloredDraw.setTo(color, drawOrBuffer); // add the new part to the color draw

        buffer = Mat(grayFrame.rows, grayFrame.cols, 0, double(0)); // re-initialize the buffer
        counter = 0;
    }
}

/**
 * This method is used to remove the artifacts created by the hand.
 * The method is called buìy the user via GUI
 * 
 * @param frame Input image
 * @param draw Colored draw
 * @param roiHand Roi of the hand
 */
void InkDetection::cleanDraw(const Mat& frame, Mat& draw, Mat& roiHand) {
    Mat grayFrame = frame.clone();
    Mat roiTemp = roiHand.clone();
    bitwise_not(roiTemp,roiTemp);
    adaptiveThreshold(grayFrame, grayFrame, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, kernelSize, DrawThShift);
    bitwise_not(grayFrame, grayFrame);
    bitwise_and(roiTemp,grayFrame,grayFrame);
    draw.setTo(Scalar(255, 255, 255), grayFrame);
}
