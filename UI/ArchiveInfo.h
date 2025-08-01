#ifndef ARCHIVEINFO_H
#define ARCHIVEINFO_H

#include <QWidget>
#include <QLabel>
#include <QFrame>
#include <QVBoxLayout>
#include <QProgressBar>

class ArchiveInfo : public QWidget
{
    Q_OBJECT
public:
    explicit ArchiveInfo(QWidget *parent = nullptr);

signals:

private:
    QWidget* container;

    QVBoxLayout* containerLayout;
    QVBoxLayout* mainLayout;

    QLabel* progressLabel;
    QLabel* archSize;
    QLabel* fastLog;

    QProgressBar *progressBar;

    QFrame* horizLine;
};

#endif // ARCHIVEINFO_H
