
#include "Homography.h"
#include <iostream>
#include <stdio.h>      
#include <stdlib.h>           

using namespace cv;
using namespace std;

Homography::Homography() {
    isDone = false;
}

Homography::Homography(const Homography& orig) {
}

Homography::~Homography() {
}

/**
 * Compute the homography and memorixe the transformation matrix
 * 
 * @param src  Source image
 * @param out Resulting homographed matrix
 * @param inCorners The 4 points to be used in the mapping 
 */
void Homography::doHomography(const Mat& src, Mat& out, vector<Point> inCorners) {
    
    Point2f center(0, 0);
    vector<Point2f> corners;
    if (src.empty() || inCorners.size() != 4) {
        cout << "Exit homography: the corners are not 4 or Mat in empty" << endl;
        return;
    }
    corners.push_back(Point2f((float) inCorners[0].x, (float) inCorners[0].y));
    corners.push_back(Point2f((float) inCorners[1].x, (float) inCorners[1].y));
    corners.push_back(Point2f((float) inCorners[2].x, (float) inCorners[2].y));
    corners.push_back(Point2f((float) inCorners[3].x, (float) inCorners[3].y));
    
    for (int i = 0; i < corners.size(); i++)
        center += corners[i];
    
    center *= (1. / corners.size()); // mass center
    sortCorners(corners, center);
    if (corners.size() == 0) {
        cout << "Exit homography: the corners were not sorted correctly!" << endl;
        isDone = false;
        return;
    }
    out = Mat::zeros(210 * 5, 297 * 5, CV_8UC3); 

    vector<Point2f> quad_pts;
    quad_pts.push_back(Point2f(0, 0));
    quad_pts.push_back(Point2f(out.cols, 0));
    quad_pts.push_back(Point2f(out.cols, out.rows));
    quad_pts.push_back(Point2f(0, out.rows));

    tranformation = getPerspectiveTransform(corners, quad_pts);
    warpPerspective(src, out, tranformation, out.size());
    isDone = true;
}

/**
 * Sort the corners in a clockwise order. If the sorting is not succesfull it return
 * an empty vector.
 * 
 * @param corners Points to be sorted
 * @param center Mass center of the points
 */
void Homography::sortCorners(vector<Point2f>& corners, Point2f center) { 
    
    vector<Point2f> top, bot;

    for (int i = 0; i < corners.size(); i++) {
        if (corners[i].y < center.y)
            top.push_back(corners[i]);
        else
            bot.push_back(corners[i]);
    }
    corners.clear();

    if (top.size() == 2 && bot.size() == 2) {
        Point2f tl = top[0].x > top[1].x ? top[1] : top[0];
        Point2f tr = top[0].x > top[1].x ? top[0] : top[1];
        Point2f bl = bot[0].x > bot[1].x ? bot[1] : bot[0];
        Point2f br = bot[0].x > bot[1].x ? bot[0] : bot[1];
        corners.push_back(tl);
        corners.push_back(tr);
        corners.push_back(br);
        corners.push_back(bl);
    }
}



