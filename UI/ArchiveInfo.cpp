#include "ArchiveInfo.h"

ArchiveInfo::ArchiveInfo(QWidget *parent)
    : QWidget{parent}
{
    this->container = new QWidget(this);
    this->container->setFixedSize(800, 200);
    this->container->setStyleSheet("background-color: #18222B; border-radius: 5px;");

    this->progressLabel = new QLabel("Progress of the operation", this);
    this->progressLabel->setStyleSheet("color: #C9DDE9; font-size: 21px; font-weight: 600;");

    this->progressBar = new QProgressBar(this);
    this->progressBar->setRange(0, 100);
    this->progressBar->setValue(0);
    this->progressBar->setTextVisible(false);
    this->progressBar->setFixedHeight(18);
    this->progressBar->setStyleSheet(R"(
        QProgressBar {
            background-color: #161E27;
            border: none;
            border-radius: 5px;
        }
        QProgressBar::chunk {
            background-color: #212A36;
            border-radius: 5px;
        }
    )");

    auto makeLine = []() {
        QFrame* horizLine = new QFrame();
        horizLine->setFrameShape(QFrame::HLine);
        horizLine->setFrameShadow(QFrame::Plain);
        horizLine->setFixedHeight(1);
        horizLine->setStyleSheet("background-color: #3F4D60;");
        horizLine->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        return horizLine;
    };

    this->archSize = new QLabel("Size of archive", this);
    this->archSize->setStyleSheet("color: #C9DDE9; font-size: 19px; font-weight: 500;");

    this->fastLog = new QLabel("Quick operation log", this);
    this->fastLog->setStyleSheet("color: #C9DDE9; font-size: 19px; font-weight: 500;");

    this->containerLayout = new QVBoxLayout(this->container);
    this->containerLayout->addWidget(this->progressLabel);
    this->containerLayout->addWidget(this->progressBar);
    this->containerLayout->setSpacing(17);
    this->containerLayout->addWidget(makeLine());
    this->containerLayout->addWidget(this->archSize);
    this->containerLayout->addWidget(makeLine());
    this->containerLayout->addWidget(this->fastLog);

    this->mainLayout = new QVBoxLayout(this);
    this->mainLayout->setContentsMargins(0,0,0,0);
    this->mainLayout->setSpacing(0);
    this->mainLayout->addWidget(this->container);
}

QProgressBar* ArchiveInfo::getProgressBar() const {
    return this->progressBar;
}

QLabel* ArchiveInfo::getArchSize() const {
    return this->archSize;
}

QLabel* ArchiveInfo::getFastLog() const {
    return this->fastLog;
}

void ArchiveInfo::setProgress(int value) {
    int current = this->progressBar->value();

    while (current < value) {
        ++current;
        this->progressBar->setValue(current);
        QThread::msleep(20);
        QCoreApplication::processEvents();
    }
}
