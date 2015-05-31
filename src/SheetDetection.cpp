
#include "SheetDetection.h"
#include "Utils.h"     

using namespace cv;
using namespace std;

SheetDetection::SheetDetection() {
}

SheetDetection::SheetDetection(const SheetDetection& orig) {
}

SheetDetection::~SheetDetection() {
}
/**
 * Computes the angle given 3 points as input.
 * 
 * @param pt1 first point
 * @param pt2 second point
 * @param pt0 vertex point
 * @return angle in radiants
 */
double SheetDetection::angle(cv::Point pt1, cv::Point pt2, cv::Point pt0) {
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    double result = (dx1 * dx2 + dy1 * dy2) / sqrt((dx1 * dx1 + dy1 * dy1)*(dx2 * dx2 + dy2 * dy2) + 1e-10);
    return result;
}

/**
 * Identifies the references crosses inside the frame
 * 
 * @param input Input image
 * @return vector of pointer to crossed
 */
vector<Cross *> SheetDetection::findCrosses(Mat& input) {

    Mat src_gray, canny_output;
    vector<Vec4i> hierarchy;
    vector<Cross*> crosses;
    vector<Rect> rectangulars;
    vector<vector<Point> > contours, realCrosses;
    vector<Point> approx;
    vector<int> concOrconv;
    int vtc, is_conv, is_conc, x_cent, y_cent, check, sum;
    double cos_angle;
    bool correct;
    vector<double> savedAngle;
    Point2f pt;
    Rect ROI;
    Cross* toAdd;


    // Convert the image to grayscale
    cvtColor(input, src_gray, CV_BGR2GRAY);

    for (int iterTh = 20; iterTh < 200; iterTh = iterTh + 10) {

        // Contours identifiction
        threshold(src_gray, canny_output, iterTh, 255, 0);
        contours.clear();
        hierarchy.clear();
        findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
        for (int i = 0; i < contours.size(); i++) {
            // Approximate contour with accuracy proportional
            // to the contour perimeter
            approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);
            if ((approx.size() == 12) &&(fabs(contourArea(contours[i])) > 50)&&(!isContourConvex(contours[i]))) {//possible cross candidate
                is_conc = 0;
                is_conv = 0;
                correct = true;
                vtc = approx.size();
                concOrconv.clear();
                savedAngle.clear();
                for (int j = 2; j < vtc + 2; j++) { //computes angles and checks their concvavity/convexity
                    cos_angle = angle(approx[j % vtc], approx[j - 2], approx[j - 1]);
                    cos_angle = acos(cos_angle)*180 / 3.14;
                    x_cent = (approx[j % vtc].x + approx[j - 2].x) / 2;
                    y_cent = (approx[j % vtc].y + approx[j - 2].y) / 2;
                    pt.x = x_cent;
                    pt.y = y_cent;
                    check = pointPolygonTest(approx, pt, false);
                    if (check == 1) { //1 convex
                        cos_angle = cos_angle + 180;
                        is_conv++;
                    } else if (check == -1) { //-1 concave
                        is_conc++;
                    }
                    if (!(((cos_angle > 40) & (cos_angle < 190)) | ((cos_angle > 210) & (cos_angle < 350)))) {
                        correct = false;
                    }
                    concOrconv.push_back(check);
                }
                sum = 0;
                if (is_conc == 4 && is_conv == 8) { //pattern matching condition 
                    for (int z = 0; z < concOrconv.size(); z++) {

                        if (z == concOrconv.size() - 1) {
                            sum = concOrconv[z] + concOrconv[0] + concOrconv[1];
                        } else if (z == concOrconv.size() - 2) {
                            sum = concOrconv[z] + concOrconv[concOrconv.size() - 1] + concOrconv[0];
                        } else {
                            sum = concOrconv[z] + concOrconv[z + 1] + concOrconv[z + 2];
                        }
                        if (sum != 1) {
                            correct = false;
                            break;
                        }
                    }
                    if (correct) {//is a real cross!
                        ROI = boundingRect(contours[i]);
                        if (rectangulars.size() == 0) {//first cross acquired
                            rectangulars.push_back(ROI);
                            realCrosses.push_back(contours[i]);
                            toAdd = new Cross();
                            toAdd->initialize(contours[i]);
                            crosses.push_back(toAdd);
                        } else {
                            double result = 0;
                            for (int lol = 0; lol < rectangulars.size(); lol++) { //checks if it overlaps
                                Rect inter = (ROI & rectangulars[lol]);
                                double intersection_area = inter.area();
                                result = intersection_area + result;
                            }
                            if (result == 0) {
                                rectangulars.push_back(ROI);
                                realCrosses.push_back(contours[i]);
                                toAdd = new Cross();
                                toAdd->initialize(contours[i]);
                                crosses.push_back(toAdd);
                            }
                        }
                    }
                }
            }
        }
    }
    return crosses;
}

/**
 * Compute the color of the crosses and identify thei positions in the sheet.
 * [The green crosses for now are not used. They could be used in future devlopments]
 * 
 * @param src Input image
 * @param cross Vector of pointer to cross
 */
void SheetDetection::manageCrosses(Mat& src, vector<Cross*> cross) {

    if (cross.size() < 6) {
        calib.isDone = false;
        return; 
    }
    double dist1, dist2, dist1Green, dist2Green;
    int j;
    vector<Cross*> boundRight, boundLeft, crosses, crossesBlack, crossesRed, crossesGreen;
    vector<double> areas;
    vector<int> idx;
    Utils tools;

    for (j = 0; j < cross.size(); j++) { 
        areas.push_back(cross[j]->area);
    }
    idx = tools.getBiggest(areas, 6); // get the biggets six aread

    for (j = 0; j < idx.size(); j++) { // save only the good ones and separate them by color
        cross[idx[j]]->computeHSV(src); 
        crosses.push_back(cross[idx[j]]);
    }
    decideColor(crosses);
    for (j = 0; j < idx.size(); j++) {
        if (crosses[j]->color == 0) {
            crossesBlack.push_back(cross[idx[j]]);
        } else if (crosses[j]->color == 1) {
            crossesRed.push_back(cross[idx[j]]);
        } else if (crosses[j]->color == 2) {
            crossesGreen.push_back(cross[idx[j]]);
        }
    }
    if ((crossesRed.size() == 2) && (crossesBlack.size() == 2)&&(crossesGreen.size() == 2)) {
        dist1 = norm(crossesBlack[0]->center - crossesRed[0]->center);
        dist2 = norm(crossesBlack[0]->center - crossesRed[1]->center);
        dist1Green = norm(crossesBlack[0]->center - crossesGreen[0]->center); 
        dist2Green = norm(crossesBlack[0]->center - crossesGreen[1]->center);

        if (crossesBlack[0]->center.x < crossesBlack[1]->center.x) { // idetify the two Black-Red couples
            boundLeft.push_back(crossesBlack[0]);
            boundRight.push_back(crossesBlack[1]);
            if (dist1Green < dist2Green) {
                boundLeft.push_back(crossesGreen[0]);
                boundRight.push_back(crossesGreen[1]);
            } else {
                boundLeft.push_back(crossesGreen[1]);
                boundRight.push_back(crossesGreen[0]);
            }
            if (dist1 < dist2) {
                boundLeft.push_back(crossesRed[0]);
                boundRight.push_back(crossesRed[1]);
            } else {
                boundLeft.push_back(crossesRed[1]);
                boundRight.push_back(crossesRed[0]);
            }
        } else {
            boundLeft.push_back(crossesBlack[1]);
            boundRight.push_back(crossesBlack[0]);
            if (dist1Green < dist2Green) {
                boundLeft.push_back(crossesGreen[1]);
                boundRight.push_back(crossesGreen[0]);
            } else {
                boundLeft.push_back(crossesGreen[0]);
                boundRight.push_back(crossesGreen[1]);
            }
            if (dist1 < dist2) {
                boundLeft.push_back(crossesRed[1]);
                boundRight.push_back(crossesRed[0]);
            } else {
                boundLeft.push_back(crossesRed[0]);
                boundRight.push_back(crossesRed[1]);
            }
        }

        calib.vertex.push_back(boundLeft[0]->center);
        calib.vertex.push_back(boundLeft[2]->center);
        calib.vertex.push_back(boundRight[2]->center);
        calib.vertex.push_back(boundRight[0]->center);
        calib.leftCrosses = boundLeft;
        calib.rightCrosses = boundRight;

        calib.isDone = true;
        return;
    }
    calib.isDone = false;
    return;
}

/**
 * Call all the calibration functions and computes the homography
 * 
 * @param src Input image
 */
void SheetDetection::sheetIdentification(Mat& src) {

    if (calib.isDone && calib.transmMatrix.isDone) {
        return;
    } else {
        vector<Cross*> cross = findCrosses(src);
        if (cross.size() == 6) {
            manageCrosses(src, cross);
            if (calib.isDone) {
                Mat out;
                cropFrame(src); 
                calib.transmMatrix.doHomography(src, out, calib.vertex);
                if (calib.transmMatrix.isDone) {
                    Point2f pt(out.cols / 2., out.rows / 2.);
                    calib.rotMatrix = getRotationMatrix2D(pt, 180, 1.0);
                    return;
                } else {
                    calib.transmMatrix.isDone = false;
                    calib.isDone = false;
                    return;
                }
            }
        }
    }
}

/**
 * Crop the frame according to the identified crosses to reduce the size of the image to 
 * analyze and remap the crosses position accordingly to the crop.
 * 
 * @param src Input image
 */
void SheetDetection::cropFrame(Mat& src){
    
    calib.toCrop = boundingRect( Mat(calib.vertex) );
    for(int i = 0; i < calib.vertex.size(); i++){
        calib.vertex[i].x = calib.vertex[i].x - calib.toCrop.x;
        calib.vertex[i].y = calib.vertex[i].y - calib.toCrop.y;
    }
    src = src(calib.toCrop);
}

/**
 * Decide the color of the crosses
 * 
 * @param crosses vector of pointer to cross
 */
void SheetDetection::decideColor(vector<Cross *> crosses) {

    Utils tools;
    vector <double> h, v;
    vector <int> idx;
    vector <bool> colorCross;
    int i;
    for (i = 0; i < crosses.size(); i++) {  
        colorCross.push_back(true);
        h.push_back(crosses[i]->col.val[0]);
        v.push_back(-crosses[i]->col.val[2]);
    }
    idx = tools.getBiggest(v, 2);
    for (i = 0; i < idx.size(); i++) {
        crosses[idx[i]]->color = 0; // the crosses with lowest brightness are the blacks one
        colorCross[idx[i]] = false;
    }
    for (i = 0; i < crosses.size(); i++) {
        if (colorCross[i]) {
            if ((h[i] > 60) & (h[i] < 240)) {
                crosses[i]->color = 2;  // green
            } else {
                crosses[i]->color = 1; // red
            }
        }
    }
}