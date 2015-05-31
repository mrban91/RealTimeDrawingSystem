
#include "Welcome.h"
#include "Introduction.h"

#include <string>

#ifndef PARAMETERS_H
#define	PARAMETERS_H
extern int bufferDim; // size of the buffer in draw identification
extern int kernelSize; // size of the kernel for the adaptiveTreshold
extern int handThreshold; // treshold value for the hand identification
extern int DrawThShift; // shift of the treshold in adaptivetreshold
extern bool showROIHand; // show or not the roi of the hand image
extern bool showDifference; // show or not the difference image
extern bool showVideo; // show or not the original video
extern bool imageClean; // clean or not the draw
extern bool toStop; // boolean to kill the drawing acquisition 
extern std::string saveFile;

class Parameters {
public:
    Parameters();
    virtual ~Parameters();
    
private:

};

#endif	/* PARAMETERS_H */

