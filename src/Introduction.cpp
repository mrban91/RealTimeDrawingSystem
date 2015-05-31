
#include "Introduction.h"
#include "Welcome.h"

Introduction::Introduction() {
    widget.setupUi(this);
     connect(widget.pushButton, SIGNAL(clicked()), this, SLOT(start()));
}

Introduction::~Introduction() {
}
void Introduction::start()
{   
    close();
}
