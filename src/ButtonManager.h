
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/core/core.hpp>
#include "Button.h"
#ifndef BUTTONMAGER_H
#define	BUTTONMAGER_H

using namespace cv;
using namespace std;

/**
 * Identifies, stores and manages buttons.
 */
class ButtonManager { 
public:
    ButtonManager();
    ButtonManager(const ButtonManager& orig);
    virtual ~ButtonManager();
    void initialize(Mat grayFrameH);
    void findNewButtons(const Mat &source); 
    void drawButtons(const Mat& draw);
    void buttonPressed(const Mat& roiHand, Scalar& color);

    Mat firstFrame; //contains the first homographed frame in the area of interactive functionalities
    bool firstAcquisition; //if true, the first frame is acquired
    Mat areaWithButtons; //contains the area of interactive functionalities with every button filled with an unique scalar
    vector <Rect> areaButtons; //each rect is the bounding rect of one button
    int colorCounter;  //progressive counter for occlusion evaluation
    vector <Button *> buttons; //contains all the buttons in the area of interactive functionalities
private:

};

#endif	/* BUTTONMAGER_H */

