#include "ArchiveWorker.h"

ArchiveWorker::ArchiveWorker(const QString& archivePath, const QStringList& inputFiles, QObject* parent)
    : QObject(parent), archivePath(archivePath), inputFiles(inputFiles) {}


void ArchiveWorker::process() {
    QProcess* zip = new QProcess(this);
    zip->setProgram("D:/zip/bin/zip.exe");

    QStringList args;
    args << "-r" << archivePath;

    QString baseDir;
    QStringList allItems;

    for (const QString& filePath : inputFiles) {
        QFileInfo info(filePath);

        if (info.isDir()) {
            if (baseDir.isEmpty())
                baseDir = info.absolutePath();

            // Добавляем корневую папку
            allItems << filePath;

            QDir dir(filePath);

            // Вложенные папки (только на первом уровне)
            QFileInfoList subDirs = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
            for (const QFileInfo& subDir : subDirs)
                allItems << subDir.absoluteFilePath();

            // Файлы верхнего уровня
            QFileInfoList files = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
            for (const QFileInfo& file : files)
                allItems << file.absoluteFilePath();

        } else {
            if (baseDir.isEmpty())
                baseDir = info.absoluteDir().absolutePath();

            allItems << filePath;
        }
    }

    QDir base(baseDir);
    zip->setWorkingDirectory(baseDir);

    for (const QString& path : allItems) {
        QFileInfo info(path);
        QString relativePath = base.relativeFilePath(path);
        args << relativePath;

        // Добавляем в таблицу
        QString name = info.fileName();
        if (info.isDir()) {
            emit entryAdded(name, "-", "Folder");
        } else {
            QString sizeStr = QString::number(info.size() / 1024.0, 'f', 2) + " KB";
            emit entryAdded(name, sizeStr, "File");
        }
    }

    zip->setArguments(args);

    connect(zip, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, [this, zip](int exitCode, QProcess::ExitStatus) {
                if (exitCode == 0) {
                    emit finished();
                } else {
                    emit errorOccurred("Failed to create archive:\n" + zip->readAllStandardError());
                    emit finished();
                }
                zip->deleteLater();
            });

    zip->start();
}


