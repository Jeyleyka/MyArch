#ifndef ARCHIVEMANAGER_H
#define ARCHIVEMANAGER_H

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

class ArchiveManager
{
public:
    static bool createArchive(const QString &zipPath, const QStringList &filePaths);
};

#endif // ARCHIVEMANAGER_H
