
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/core/core.hpp>

#ifndef HOMOGRAPHY_H
#define	HOMOGRAPHY_H

using namespace cv;

/**
 * Class representing the transformation
 */
class Homography {
public:
    Homography();
    Homography(const Homography& orig);
    virtual ~Homography();

    void doHomography(const Mat& src, Mat& out, vector<Point> inCorners);
    bool isDone; // boolean to check if the homographt has been computed succesfully
    Matx33f tranformation; // Matrix containing the transformation
private:
    void sortCorners(vector<Point2f>& corners, Point2f center);
};

#endif	/* HOMOGRAPHY_H */

