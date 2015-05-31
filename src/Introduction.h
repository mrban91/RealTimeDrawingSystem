
#ifndef _INTRODUCTION_H
#define	_INTRODUCTION_H

#include "ui_Introduction.h"

class Introduction : public QDialog {
    Q_OBJECT
public:
    
    Introduction();
    virtual ~Introduction();
    public slots:
        void start ();
private:
    Ui::Introduction widget;
};

#endif	/* _INTRODUCTION_H */
