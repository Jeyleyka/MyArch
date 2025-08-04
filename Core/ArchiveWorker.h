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
    void entryAdded(const QString& name, const QString& size, const QString& type);
    void finished();
    void errorOccurred(const QString &message);
    void progressUpdated(int percent);
    void progressStep(const QString& currentFile);

private:
    QString archivePath;
    QStringList inputFiles;
    qint64 totalUncompressedSize;
};

#endif // ARCHIVEWORKER_H
