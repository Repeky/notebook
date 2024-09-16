#include <mainwindow.h>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), textEdit(new QTextEdit(this)), isTextChanged(false) {
    setCentralWidget(textEdit);
    setWindowIcon(QIcon(":/img/icon-book.png"));

    setMinimumSize(800, 600);
    resize(1024, 768);

    connect(textEdit, &QTextEdit::textChanged, [this]() { isTextChanged = true; });

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
    if (maybeSave()) {
        textEdit->clear();
        currentFile.clear();
        isTextChanged = false;
    }
}

void MainWindow::newFileWithExtension(const QString &extension) {
    if (maybeSave()) {
        textEdit->clear();
        currentFile = QString("untitled.%1").arg(extension);
        isTextChanged = false;
    }
}

void MainWindow::openFile() {
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this);
        if (!fileName.isEmpty()) {
            openFile(fileName);
        }
    }
}

void MainWindow::openFile(const QString &fileName) {
    QFile file(fileName);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        textEdit->setPlainText(file.readAll());
        currentFile = fileName;
        isTextChanged = false;
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
            isTextChanged = false;
            statusBar()->showMessage(tr("File saved"), 2000);
        } else {
            QMessageBox::warning(this, tr("Error"), tr("Could not save file"));
        }
    }
}

void MainWindow::saveFileAs() {
    QString defaultDir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), defaultDir + "/untitled.txt",
                                                    tr("Text Files (*.txt);;All Files (*)"));
    if (!fileName.isEmpty()) {
        currentFile = fileName;
        saveFile();
    }
}

void MainWindow::undo() {
    textEdit->undo();
}

void MainWindow::wheelEvent(QWheelEvent *event) {
    if (event->modifiers() == Qt::ControlModifier) {
        if (event->angleDelta().y() > 0) {
            textEdit->zoomIn();
        } else {
            textEdit->zoomOut();
        }
        event->accept();
    } else {
        QMainWindow::wheelEvent(event);
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}

bool MainWindow::maybeSave() {
    if (isTextChanged) {
        QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("Application"),
                                                               tr("The document has been modified.\nDo you want to save your changes?"),
                                                               QMessageBox::Save | QMessageBox::Discard |
                                                               QMessageBox::Cancel);
        if (ret == QMessageBox::Save) {
            return saveFile(), true;
        } else if (ret == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}
