
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"


#ifndef BUTTON_H
#define	BUTTON_H
using namespace cv;
/**
 * Container for buttons that allow interactive functionalities.
 * Every button, when pressed, changes the color of the line.
 * The user can select the color once a new button is created in the area of interactive 
 * functionalities. 
 */
class Button {
public:
    Button();
    Button(const Button& orig);
    virtual ~Button();
    Button(vector<Point> inContour, int inCounterAssociated, int R, int G, int B);
    
    int counterAssociated; //counter for evaluation of the occlusion
    double area; //area of the button in pixel
    vector<Point> contour; //set of points of the contour of the button
    Scalar color; //RGB color of the button
    bool currentlyPressed; //if true, the button area is currently occluded
private:
};

#endif	/* BUTTON_H */