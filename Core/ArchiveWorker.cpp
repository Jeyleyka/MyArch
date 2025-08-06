#include "ArchiveWorker.h"

ArchiveWorker::ArchiveWorker(const QString& archivePath, const QStringList& inputFiles, QObject* parent)
    : QObject(parent), archivePath(archivePath), inputFiles(inputFiles), currentArchiveSize(0), filesProcessed(0) {}

void ArchiveWorker::process() {
    QProcess* zip = new QProcess(this);
    zip->setProgram("D:/Work/Archiver/zip/bin/zip.exe");

    QStringList args;
    args << "-r" << archivePath;

    QString baseDir;
    QStringList topLevelItems;

    QIcon folderIcon(":/Resources/fold.png");
    QIcon fileIcon(":/Resources/document.png");

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
    qint64 totalSize = 0;  // Здесь суммируем размер

    for (const QString& path : topLevelItems) {
        QFileInfo info(path);
        QString relativePath = base.relativeFilePath(path);
        args << relativePath;

        QString name = info.fileName();
        if (info.isDir()) {
            emit entryAdded(folderIcon, name, "-", "Folder");
            emit quickLogUpdated("Added folder: " + name);
        } else {
            qint64 sizeBytes = info.size();
            totalSize += sizeBytes;

            QString sizeStr = QString::number(sizeBytes / 1024.0, 'f', 2) + " KB";
            emit entryAdded(fileIcon, name, sizeStr, "File");
            emit quickLogUpdated("Added file: " + name);
        }

        count++;
        int progress = static_cast<int>((count / static_cast<double>(total)) * 99);
        emit progressUpdated(progress);
    }

    zip->setArguments(args);

    connect(zip, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, [this, zip, total](int exitCode, QProcess::ExitStatus) {
                if (exitCode == 0) {
                    QFileInfo info(archivePath);
                    qint64 finalSize = info.size();
                    emit progressUpdated(100);  // Завершено, передаем -1 чтобы показать окончание
                    emit finished();
                    emit showFinishedSize(finalSize);
                } else {
                    emit errorOccurred("Failed to create archive:\n" + zip->readAllStandardError());
                    emit finished();
                }
                zip->deleteLater();
            });

    zip->start();
}


