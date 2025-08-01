#include "ArchiveContent.h"

ArchiveContent::ArchiveContent(QWidget *parent)
    : QWidget{parent}
{
    setupUI();
    populateDummyContent();
}

void ArchiveContent::setupUI()
{
    this->setStyleSheet("background-color: #1F2934; color: white;");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(15, 15, 15, 15);
    mainLayout->setSpacing(10);

    titleLabel = new QLabel("Archive Contents", this);
    titleLabel->setStyleSheet("font-size: 20px; font-weight: bold;");
    mainLayout->addWidget(titleLabel);

    contentList = new QListWidget(this);
    contentList->setStyleSheet(R"(
        QListWidget {
            background-color: #141F26;
            border: 1px solid #3F4D60;
            font-size: 16px;
        }
        QListWidget::item {
            padding: 10px;
        }
        QListWidget::item:selected {
            background-color: #3F4D60;
        }
    )");
    contentList->setIconSize(QSize(24, 24));

    mainLayout->addWidget(contentList);
}

void ArchiveContent::populateDummyContent()
{
    QListWidgetItem* fileItem = new QListWidgetItem(QIcon(":/Resources/file.png"), "report.docx");
    contentList->addItem(fileItem);

    QListWidgetItem* folderItem = new QListWidgetItem(QIcon(":/Resources/folder.png"), "images/");
    contentList->addItem(folderItem);

    QListWidgetItem* fileItem2 = new QListWidgetItem(QIcon(":/Resources/file.png"), "data.csv");
    contentList->addItem(fileItem2);
}
