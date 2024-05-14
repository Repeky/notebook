#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), textEdit(new QTextEdit(this)) {
    setCentralWidget(textEdit);

    createActions();
    createMenus();
    createToolBars();
}

MainWindow::~MainWindow() {}

void MainWindow::createActions() {
    newAct = new QAction(tr("&New"), this);
    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

    openAct = new QAction(tr("&Open..."), this);
    connect(openAct, &QAction::triggered, this, QOverload<>::of(&MainWindow::openFile));

    saveAct = new QAction(tr("&Save"), this);
    connect(saveAct, &QAction::triggered, this, &MainWindow::saveFile);

    saveAsAct = new QAction(tr("Save &As..."), this);
    connect(saveAsAct, &QAction::triggered, this, &MainWindow::saveFileAs);

    exitAct = new QAction(tr("E&xit"), this);
    connect(exitAct, &QAction::triggered, this, &QWidget::close);

    undoAct = new QAction(tr("&Undo"), this);
    connect(undoAct, &QAction::triggered, this, &MainWindow::undo);
}

void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    menuBar()->addAction(undoAct);
}

void MainWindow::createToolBars() {
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
    fileToolBar->addAction(saveAsAct);
    fileToolBar->addAction(undoAct);
}

void MainWindow::newFile() {
    textEdit->clear();
    currentFile.clear();
}

void MainWindow::newFileWithExtension(const QString &extension) {
    textEdit->clear();
    currentFile = QString("untitled.%1").arg(extension);
}

void MainWindow::openFile() {
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty()) {
        openFile(fileName);
    }
}

void MainWindow::openFile(const QString &fileName) {
    QFile file(fileName);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        textEdit->setPlainText(file.readAll());
        currentFile = fileName;
        statusBar()->showMessage(tr("File loaded"), 2000);
    } else {
        QMessageBox::warning(this, tr("Error"), tr("Could not open file"));
    }
}

void MainWindow::saveFile() {
    if (currentFile.isEmpty()) {
        saveFileAs();
    } else {
        QFile file(currentFile);
        if (file.open(QFile::WriteOnly | QFile::Text)) {
            file.write(textEdit->toPlainText().toUtf8());
            statusBar()->showMessage(tr("File saved"), 2000);
        } else {
            QMessageBox::warning(this, tr("Error"), tr("Could not save file"));
        }
    }
}

void MainWindow::saveFileAs() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text Files (*.txt);;All Files (*)"));
    if (!fileName.isEmpty()) {
        currentFile = fileName;
        saveFile();
    }
}

void MainWindow::undo() {
    textEdit->undo();
}
