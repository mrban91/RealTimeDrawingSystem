
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/core/core.hpp>
#include "Homography.h"
#include "Cross.h"
#include "CalibrationData.h"

#ifndef SHEETDETECTION_H
#define	SHEETDETECTION_H
using namespace cv;

/**
 * Class that compute and save the calibration data useful for the successive step
 */
class SheetDetection {
public:
    SheetDetection();
    SheetDetection(const SheetDetection& orig);
    virtual ~SheetDetection();
    
    vector<Cross* > findCrosses(Mat& input);
    void sheetIdentification(Mat& src);
    void manageCrosses(Mat& src, vector<Cross*> cross);
    void decideColor(vector<Cross*> crosses);
    void cropFrame(Mat& src);
    
    CalibrationData calib; 
private:
   double angle(cv::Point pt1, cv::Point pt2, cv::Point pt0);
};

#endif	/* SHEETDETECTION_H */

