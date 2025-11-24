#include <QApplication>
#include <iostream>
using namespace std;
#include <QPushButton>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QPushButton button("Hello Qt!");
    button.show();

    return app.exec();
}

