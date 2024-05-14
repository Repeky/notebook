#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QStatusBar>

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void openFile(const QString &fileName);

    void newFileWithExtension(const QString &extension);  // Новая функция

private slots:

    void newFile();

    void openFile();

    void saveFile();

    void saveFileAs();

    void undo();

private:
    void createActions();

    void createMenus();

    void createToolBars();

    QTextEdit *textEdit;
    QString currentFile;

    QMenu *fileMenu;
    QToolBar *fileToolBar;

    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *exitAct;
    QAction *undoAct;
};

#endif // MAINWINDOW_H
