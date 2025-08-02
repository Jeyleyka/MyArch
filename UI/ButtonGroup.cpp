#include "ButtonGroup.h"

ButtonGroup::ButtonGroup(QWidget *parent)
    : QWidget{parent}
{
    this->container = new QWidget(this);
    this->container->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    this->addArchBtn = new QPushButton(this);
    this->addArchBtn->setIcon(QIcon(":/Resources/addArch.png"));
    this->addArchBtn->setIconSize(QSize(28,28));
    this->addArchBtn->setText("Create archive");
    this->addArchBtn->setFixedSize(200, 50);
    this->addArchBtn->setStyleSheet(R"(
        QPushButton {
            color: #C9DDE9;
             font-size: 18px;
             border: none;
             border-radius: 5px;
             background-color: #1F2934;
        }
        QPushButton::hover {
            background-color: #3A4D61;
        }
    )");

    connect(this->addArchBtn, &QPushButton::clicked, this, &ButtonGroup::createArchiveRequested);

    this->structArchBtn = new QPushButton(this);
    this->structArchBtn->setIcon(QIcon(":/Resources/folder.png"));
    this->structArchBtn->setIconSize(QSize(28,28));
    this->structArchBtn->setText("Archive structure");
    this->structArchBtn->setFixedSize(200, 50);
    this->structArchBtn->setStyleSheet(R"(
        QPushButton {
            color: #C9DDE9;
             font-size: 18px;
             border: none;
             border-radius: 5px;
             background-color: #1F2934;
        }
        QPushButton::hover {
            background-color: #3A4D61;
        }
    )");

    this->containerLayout = new QVBoxLayout(this->container);
    this->containerLayout->setContentsMargins(0,0,0,0);
    this->containerLayout->setSpacing(0);
    this->containerLayout->addWidget(this->addArchBtn, Qt::AlignTop);
    this->containerLayout->setSpacing(10);
    this->containerLayout->addWidget(this->structArchBtn);

    this->mainLayout = new QVBoxLayout(this);
    this->mainLayout->setContentsMargins(10,0,0,0);
    this->mainLayout->setSpacing(0);
    this->mainLayout->addWidget(container, 0, Qt::AlignTop);
}
