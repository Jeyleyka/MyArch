#include "ArchiveManager.h"

bool ArchiveManager::createArchive(const QString &zipPath, const QStringList &filePaths)
{
    if (zipPath.isEmpty() || filePaths.isEmpty())
        return false;

    QProcess zip;
    zip.setProgram("D:/zip/bin/zip.exe");


    QStringList args;
    args << "-r" << zipPath;

    if (filePaths.size() == 1) {
        QFileInfo info(filePaths.first());

        if (info.isDir()) {
            zip.setWorkingDirectory(info.absoluteDir().absolutePath());
            args << info.fileName();
        } else {
            zip.setWorkingDirectory(info.absoluteDir().absolutePath());
            args << info.fileName();
        }
    } else {
        QFileInfo baseInfo(filePaths.first());
        QString baseDir = baseInfo.absoluteDir().absolutePath();
        zip.setWorkingDirectory(baseDir);

        for (const QString& path : filePaths) {
            QFileInfo info(path);

            if (info.absoluteDir().absolutePath() != baseDir) {
                qWarning() << "All files must be in the same directory.";
                return false;
            }

            args << info.fileName();
        }
    }


    zip.setArguments(args);
    zip.start();
    zip.waitForFinished();

    if (zip.exitCode() != 0)
        qDebug() << "Error:" << zip.readAllStandardError();

    return true;
}


