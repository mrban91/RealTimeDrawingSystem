
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/core/core.hpp>


#ifndef CROSS_H
#define	CROSS_H

using namespace cv;
using namespace std;

/**
 * Container for each cross found during the calibration procedure. 
 */
class Cross {
public:
    Cross();
    Cross(const Cross& orig);
    virtual ~Cross();
    
    void initialize(vector<Point> incontour);
    void computeHSV(const Mat& src);
    
    vector<Point> contour; // points of the contour of the cross
    Point2i center; // center point of the cross
    int color; // estimated color of the cross: 0 = black, 1 = red, 2 = green
    Scalar col; // hsv color of the cross
    double area; // area in pixel of the cross
    double sizeDiag; // maximum diagonal of the cross
private:
};

#endif	/* CROSS_H */

