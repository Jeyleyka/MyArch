#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->container = new QWidget(this);
    this->container->setStyleSheet("background-color: #141F26");

    this->mainLayout = new QVBoxLayout(this->container);
    this->mainLayout->setContentsMargins(0, 0, 0, 0);
    this->mainLayout->setSpacing(0);

    // Футер — в самом верху
    this->footer = new Footer(this);
    this->mainLayout->addWidget(this->footer, 0, Qt::AlignTop);

    // Группа кнопок
    this->buttonGroup = new ButtonGroup(this);

    connect(this->buttonGroup, &ButtonGroup::createArchiveRequested, this, &MainWindow::handleCreateArchive);

    // Вертикальная линия
    this->vertLine = new QFrame(this);
    this->vertLine->setFrameShape(QFrame::VLine);
    this->vertLine->setFrameShadow(QFrame::Plain);
    this->vertLine->setLineWidth(1);
    this->vertLine->setStyleSheet("background-color: #3F4D60;");
    this->vertLine->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    this->archiveContent = new ArchiveContent(this);

    connect(this->archiveContent->getTable()->horizontalHeader(), &QHeaderView::sectionClicked, this, &MainWindow::onSectionClicked);

    this->archiveInfo = new ArchiveInfo(this);

    QVBoxLayout* archiveLayout = new QVBoxLayout();
    archiveLayout->addWidget(this->archiveContent);
    archiveLayout->addWidget(this->archiveInfo);

    // Горизонтальный блок кнопок + линии
    QHBoxLayout* blockLayout = new QHBoxLayout();
    blockLayout->setContentsMargins(10, 0, 0, 0);  // немного слева
    blockLayout->setSpacing(10);
    blockLayout->addWidget(this->buttonGroup);
    blockLayout->addWidget(this->vertLine);
    blockLayout->addLayout(archiveLayout);
    blockLayout->addStretch(); // чтобы "оттолкнуть" блок влево, а не вправо

    // Обёртка для отступа от футера
    QWidget* blockWrapper = new QWidget(this);
    QVBoxLayout* wrapperLayout = new QVBoxLayout(blockWrapper);
    wrapperLayout->setContentsMargins(0, 10, 0, 10);  // отступ сверху (от футера)
    wrapperLayout->setSpacing(0);
    wrapperLayout->addLayout(blockLayout);
    blockWrapper->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    // Добавляем в главный layout
    this->mainLayout->addWidget(blockWrapper);

    // Завершение
    this->setCentralWidget(this->container);
    this->resize(1280, 720);
}

MainWindow::~MainWindow() {}

void MainWindow::handleCreateArchive() {
    QMessageBox::StandardButton choice = QMessageBox::question(this, "MyArch", "Do you want to archive a folder", QMessageBox::Yes | QMessageBox::No);

    QStringList inputFiles;

    if (choice == QMessageBox::Yes) {
        QString folder = QFileDialog::getExistingDirectory(this, "Select folder to archive");

        if (folder.isEmpty()) return;

        inputFiles << folder;
    } else {
        inputFiles = QFileDialog::getOpenFileNames(this, "Select files to archive");

        if (inputFiles.isEmpty()) return;
    }

    QString archivePath = QFileDialog::getSaveFileName(this, "Save archive", "", "ZIP archive(*.zip)");

    if (archivePath.isEmpty()) return;

    if (!archivePath.endsWith(".zip"))
        archivePath += ".zip";

    ArchiveWorker* worker = new ArchiveWorker(archivePath, inputFiles);
    QThread* thread = new QThread;

    worker->moveToThread(thread);
    worker->setParent(nullptr);

    connect(thread, &QThread::started, worker, &ArchiveWorker::process);
    connect(worker, &ArchiveWorker::entryAdded, this->archiveContent, &ArchiveContent::addEntry, Qt::QueuedConnection);
    connect(worker, &ArchiveWorker::quickLogUpdated, this, [this](const QString& name) {
        this->archiveInfo->getFastLog()->setText(name);
    });
    connect(worker, &ArchiveWorker::progressUpdated, this->archiveInfo, &ArchiveInfo::setProgress);
    connect(worker, &ArchiveWorker::progressUpdated, this, [this](int value) {
        if (value < 100)
            this->smoothlyFillProgressBar(value);
        else
            smoothlyFillProgressBar(100);
    });

    connect(worker, &ArchiveWorker::showFinishedSize, this, [this](qint64 finalSize) {
        this->archiveInfo->getArchSize()->setText(
            "Archive size: " + QString::number(finalSize / (1024.0 * 1024.0), 'f', 2) + " MB");
        this->archiveInfo->getFastLog()->setText("Archiving completed");
    });
    connect(worker, &ArchiveWorker::finished, thread, &QThread::quit);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    connect(thread, &QThread::finished, worker, &QObject::deleteLater);
    connect(worker, &ArchiveWorker::finished, this, &MainWindow::onArchiveFinished);

    thread->start();
}

void MainWindow::onArchiveFinished() {
    QMessageBox::information(this, "Success", "Archive created successfully.");
}

void MainWindow::smoothlyFillProgressBar(int targetValue) {
    int current = this->archiveInfo->getProgressBar()->value();
    int step = (targetValue - current) / 10;

    if (step == 0) step = (targetValue > current) ? 1 : -1;

    for (int i = current; i != targetValue; i += step) {
        this->archiveInfo->getProgressBar()->setValue(i);
        QThread::msleep(15);  // скорость "анимации"
        QCoreApplication::processEvents();
    }

    this->archiveInfo->getProgressBar()->setValue(targetValue);
}

void MainWindow::onSectionClicked(int column) {
    static bool ascending = false;

    if (column == SIZE_COLUMN_INDEX) {
        this->archiveContent->getTable()->sortItems(column, ascending ? Qt::AscendingOrder : Qt::DescendingOrder);
        ascending = !ascending;
    }
}
