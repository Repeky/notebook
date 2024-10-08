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
#include <QWheelEvent>
#include <QCloseEvent>
#include <QIcon>

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void openFile(const QString &fileName);

    void newFileWithExtension(const QString &extension);

protected:
    void wheelEvent(QWheelEvent *event) override;

    void closeEvent(QCloseEvent *event) override;

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

    bool maybeSave();

    QTextEdit *textEdit;
    QString currentFile;
    bool isTextChanged;

    QMenu *fileMenu{};
    QToolBar *fileToolBar{};

    QAction *newAct{};
    QAction *openAct{};
    QAction *saveAct{};
    QAction *saveAsAct{};
    QAction *exitAct{};
    QAction *undoAct{};
};

#endif