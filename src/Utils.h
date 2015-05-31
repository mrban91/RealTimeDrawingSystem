
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/core/core.hpp>

#ifndef UTILS_H
#define	UTILS_H

using namespace std;
using namespace cv;

/**
 * Class containing some usefull function fot the processing
 */
class Utils {
public:
    Utils();
    Utils(const Utils& orig);
    virtual ~Utils();
    
    vector<int> getBiggest(vector<double> values, int num);   
    void uniqueValues(Mat& input, int &codeButton , int &areaPressed);
    void applyFilter(Mat& input);
private:
};

#endif	/* UTILS_H */

