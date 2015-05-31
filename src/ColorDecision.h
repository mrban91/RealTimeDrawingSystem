
#ifndef COLORDECISION_H
#define	COLORDECISION_H

class ColorDecision {
public:
    ColorDecision();
    ColorDecision(const ColorDecision& orig);
    virtual ~ColorDecision();
    int B;
    int G;
    int R;
    bool chosen;
private:
};

#endif	/* COLORDECISION_H */

