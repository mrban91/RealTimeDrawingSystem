
#include "Welcome.h"
#include "Introduction.h"
#include <QApplication>


using namespace std;

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    app.setStyle("Fusion");
    app.doubleClickInterval();
    Welcome welcome;
    welcome.show(); //starts the GUI
    welcome.introduction.show(); //shows welcome message

    return app.exec();
}
