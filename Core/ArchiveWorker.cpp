#include "ArchiveWorker.h"

ArchiveWorker::ArchiveWorker(const QString& archivePath, const QStringList& inputFiles, QObject* parent)
    : QObject(parent), archivePath(archivePath), inputFiles(inputFiles), totalUncompressedSize(0) {}


void ArchiveWorker::process() {
    QProcess* zip = new QProcess(this);
    zip->setProgram("D:/zip/bin/zip.exe");

    QStringList args;
    args << "-r" << archivePath;

    QString baseDir;
    QStringList topLevelItems;

    for (const QString& path : inputFiles) {
        QFileInfo info(path);
        if (info.isDir()) {
            if (baseDir.isEmpty())
                baseDir = info.absolutePath();

            QDir dir(path);
            QFileInfoList entries = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries, QDir::DirsFirst);

            for (const QFileInfo& entry : entries) {
                topLevelItems << entry.absoluteFilePath();
            }

            topLevelItems << path;  // сама папка
        } else {
            if (baseDir.isEmpty())
                baseDir = info.absoluteDir().absolutePath();

            topLevelItems << path;
        }
    }

    QDir base(baseDir);
    zip->setWorkingDirectory(baseDir);

    int total = topLevelItems.size();
    int count = 0;

    for (const QString& path : topLevelItems) {
        QFileInfo info(path);
        QString relativePath = base.relativeFilePath(path);
        args << relativePath;

        QString name = info.fileName();
        if (info.isDir()) {
            emit entryAdded(name, "-", "Folder");
        } else {
            QString sizeStr = QString::number(info.size() / 1024.0, 'f', 2) + " KB";
            emit entryAdded(name, sizeStr, "File");
        }

        count++;
        int progress = static_cast<int>((count / static_cast<double>(total)) * 99);
        emit progressUpdated(progress);
    }

    zip->setArguments(args);

    connect(zip, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, [this, zip](int exitCode, QProcess::ExitStatus) {
                if (exitCode == 0) {
                    emit progressUpdated(100);  // Завершено
                    emit finished();
                } else {
                    emit errorOccurred("Failed to create archive:\n" + zip->readAllStandardError());
                    emit finished();
                }
                zip->deleteLater();
            });

    zip->start();
}


