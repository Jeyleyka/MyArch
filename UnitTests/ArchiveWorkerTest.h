#ifndef ARCHIVEWORKERTEST_H
#define ARCHIVEWORKERTEST_H

#include <QObject>
#include <QtTest/QTest>
#include <QSignalSpy>
#include <QFile>

#include "../Core/ArchiveWorker.h"

class ArchiveWorkerTest : public QObject
{
    Q_OBJECT

private slots:
    void testCreateArchive();
};

#endif // ARCHIVEWORKERTEST_H
