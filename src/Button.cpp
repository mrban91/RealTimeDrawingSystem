
#include "Button.h"

Button::Button() {
}
/**
 * Constructor for a new button.
 * 
 * @param inContour set of points that define the contour of the button
 * @param inCounterAssociated counter for evaluating the occlusion
 * @param R red component
 * @param G green component
 * @param B blue component
 */
Button::Button(vector<Point> inContour, int inCounterAssociated, int R, int G, int B) {
    
    contour=inContour;
    counterAssociated=inCounterAssociated;
    color.val[0] = B;
    color.val[1] = G;
    color.val[2] = R;

    area = contourArea(inContour);
    currentlyPressed=false;
}

Button::Button(const Button& orig) {
}

Button::~Button() {
}
