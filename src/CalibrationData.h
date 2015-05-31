
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/core/core.hpp>
#include "Homography.h"
#include "Cross.h"


#ifndef CALIBRATIONDATA_H
#define	CALIBRATIONDATA_H

/**
 * Class containig all the data obtained by the calibration 
 */
class CalibrationData { 
public:
    CalibrationData();
    CalibrationData(const CalibrationData& orig);
    virtual ~CalibrationData();
    vector<Point> vertex;  // vector containing the 4 vertex of the shhet in clockwise order (no rotated image!))
    vector<Cross* > leftCrosses, rightCrosses; // vector containning all the crosses and infos
    
    Rect toCrop; //bounding rect containing the sheet of paper used to crop the frame
    Homography transmMatrix; //trasformation matrix used for the rectification
    Mat rotMatrix; //matrix for the flip of the draw
    bool isDone; //if yes the calibration was succesfully performed
};

#endif	/* CALIBRATIONDATA_H */

