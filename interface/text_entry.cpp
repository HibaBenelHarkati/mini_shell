#include <QApplication>
#include <QMainWindow>
#include <QTextEdit>


class MainWindow : public QMainWindow {
public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent){
        setWindowTitle("Terminal");
        resize(1400, 1000);
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow main_window;

    main_window.show();

    return app.exec();
}
