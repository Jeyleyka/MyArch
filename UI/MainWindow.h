#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QFileDialog>
#include <QMessageBox>
#include <QThread>
#include <QTimer>

#include "Footer.h"
#include "ButtonGroup.h"
#include "ArchiveContent.h"
#include "ArchiveInfo.h"
#include "../Core/ArchiveWorker.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleCreateArchive();
    void onArchiveFinished();
    void smoothlyFillProgressBar(int targetValue);
    void onSectionClicked(int column);
    void onUpdateArchSize(qint64 bytesWritten, int filesProcessed, int totalFiles);

private:
    Footer* footer;
    ButtonGroup* buttonGroup;
    ArchiveContent* archiveContent;
    ArchiveInfo* archiveInfo;

    QVBoxLayout* mainLayout;

    QHBoxLayout* blockLayout;

    QWidget *container;

    QFrame* vertLine;

    static constexpr int SIZE_COLUMN_INDEX = 1;
};
#endif // MAINWINDOW_H
