
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/core/core.hpp>

#ifndef INKDETECTION_H
#define	INKDETECTION_H
using namespace cv;

/**
 * Class the perform two main tasks:
 * - identify the hand during the draw to avoid/reduce artifacts
 * - identify the draw on the paper and draw it on the digital one with the selected color
 */
class InkDetection {
public:
    InkDetection();
    InkDetection(const InkDetection& orig);
    virtual ~InkDetection();
    
    void handIdentification (Mat& diff, Mat & roiRect, Mat & roiHand, bool& found);
    void drawIdentification(const Mat& grayFrame, Mat& draw, Mat& buffer, int& counter, Mat& roiHand,Mat& coloredDraw);
    void cleanDraw(const Mat& frame, Mat& draw, Mat& roiHand);
    Scalar color; // selected color by the user (black by default)
};

#endif	/* INKDETECTION_H */

