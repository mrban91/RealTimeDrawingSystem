
#include "Cross.h"
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

Cross::Cross() {
}

Cross::Cross(const Cross& orig) {
}

Cross::~Cross() {
}
/**
 * Initialize a cross and computes its attributes.
 * 
 * @param incontour set of points that describe the cross
 */
void Cross::initialize(vector<Point> incontour) {
    
    for (int u = 0; u < incontour.size(); u++) {
        contour.push_back(incontour[u]);
    }
    vector<Moments> mu; // moments 
    vector<Point2i> mc; // mass center
    mu.push_back(moments(incontour, false));
    mc.push_back(Point2f(mu[mu.size() - 1].m10 / mu[mu.size() - 1].m00, mu[mu.size() - 1].m01 / mu[mu.size() - 1].m00));
    center = mc[0];
    area = contourArea(contour);
}

/**
 * Computes an hsv estimation of the color of the cross.
 * 
 * @param src input matrix containing the cross
 */
void Cross::computeHSV(const Mat& src) {

    Mat subset = src.operator()(Rect(center.x - 4, center.y - 4, 8, 8)); // subset of pixel of the entire cross
    Mat tmp;
    cvtColor(subset,tmp,CV_BGR2HSV); 
    double h, s, v;
    Scalar a = mean(tmp);
    // conversion in common HSV scale is needed
    // @see http://stackoverflow.com/questions/10948589/choosing-correct-hsv-values-for-opencv-thresholding-with-inranges
    h = a.val[0]*360/179; 
    s = a.val[1]*100/255;
    v = a.val[2]*100/255;
    
    col = Scalar(h,s,v);
}

