#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;

    if (argc > 1) {
        mainWindow.openFile(QString::fromUtf8(argv[1]));
    } else {
        mainWindow.newFileWithExtension("txt"); // Устанавливаем расширение по умолчанию
    }

    mainWindow.show();
    return app.exec();
}
