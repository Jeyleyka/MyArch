#ifndef ARCHIVEWORKER_H
#define ARCHIVEWORKER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QProcess>
#include <QDir>
#include <QFileDialog>
#include <QListView>
#include <QTreeView>
#include <QDirIterator>

class ArchiveWorker : public QObject
{
    Q_OBJECT
public:
    explicit ArchiveWorker(const QString& archivePath, const QStringList& inputFiles, QObject* parent = nullptr);

public slots:
    void process();

signals:
    void entryAdded(const QIcon& icon, const QString& name, const QString& size, const QString& type);
    void finished();
    void showFinishedSize(qint64 finalSize);
    void errorOccurred(const QString &message);
    void progressUpdated(int percent);
    void progressStep(const QString& currentFile);
    void quickLogUpdated(const QString& name);

private:
    QString archivePath;
    QStringList inputFiles;
    qint64 currentArchiveSize;
    int filesProcessed;
};

#endif // ARCHIVEWORKER_H
