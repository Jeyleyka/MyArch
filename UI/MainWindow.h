#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>

#include "Footer.h"
#include "ButtonGroup.h"
#include "ArchiveContent.h"
#include "ArchiveInfo.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Footer* footer;
    ButtonGroup* buttonGroup;
    ArchiveContent* archiveContent;
    ArchiveInfo* archiveInfo;

    QVBoxLayout* mainLayout;

    QHBoxLayout* blockLayout;

    QWidget *container;

    QFrame* vertLine;
};
#endif // MAINWINDOW_H
