#include <QApplication>
#include <QPushButton>

int main(int argc, char **argv)
{
 QApplication app (argc, argv);
 // Create a container window
 QWidget window;
 window.setFixedSize(1, 1000);
 window.show();
return app.exec();
}
