#include "ArchiveWorkerTest.h"

void ArchiveWorkerTest::testCreateArchive() {
    QString archivePath = "test_output.zip";
    QStringList inputFiles = { "test_file.txt" };

    QFile f("test_file.txt");
    f.open(QIODevice::WriteOnly);
    f.write("Hello Test");
    f.close();

    ArchiveWorker worker(archivePath, inputFiles);

    QSignalSpy finishedSpy(&worker, &ArchiveWorker::finished);
    QSignalSpy errorSpy(&worker, &ArchiveWorker::errorOccurred);
    QSignalSpy fileSpy(&worker, &ArchiveWorker::showFinishedSize);
    QSignalSpy addFileInTableSpy(&worker, &ArchiveWorker::entryAdded);

    worker.process();

    QVERIFY(finishedSpy.wait(5000));
    QCOMPARE(errorSpy.count(), 0);
    QCOMPARE(finishedSpy.count(), 1);

    int waitTime = 0;
    while (fileSpy.count() < 1 && waitTime < 5000) {
        QTest::qWait(100);
        waitTime += 100;
    }

    QCOMPARE(fileSpy.count(), 1);

    QVariant sizeVariant = fileSpy.takeFirst().at(0);
    QString sizeString = sizeVariant.toString();
    QVERIFY(!sizeString.isEmpty());

    int waitTime2 = 0;
    while (addFileInTableSpy.count() < 1 && waitTime2 < 5000) {
        QTest::qWait(100);
        waitTime2 += 100;
    }

    QCOMPARE(addFileInTableSpy.count(), 1);

    QVERIFY(QFile::exists(archivePath));

    QFile::remove("test_file.txt");
    QFile::remove(archivePath);
}

QTEST_MAIN(ArchiveWorkerTest)
#include "ArchiveWorkerTest.moc"
