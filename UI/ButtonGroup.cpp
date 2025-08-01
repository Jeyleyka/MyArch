#include "ButtonGroup.h"

ButtonGroup::ButtonGroup(QWidget *parent)
    : QWidget{parent}
{
    this->container = new QWidget(this);
    // this->container->setFixedHeight(parent->height());
    // this->container->setFixedHeight(100);
    this->container->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    this->addArchBtn = new QPushButton(this);
    this->addArchBtn->setIcon(QIcon(":/Resources/addArch.png"));
    this->addArchBtn->setIconSize(QSize(28,28));
    this->addArchBtn->setText("Create archive");
    this->addArchBtn->setStyleSheet("color: #C9DDE9; font-size: 18px; border: none; border-radius: 5px; background-color: #1F2934;");
    this->addArchBtn->setFixedSize(200, 50);

    this->structArchBtn = new QPushButton(this);
    this->structArchBtn->setIcon(QIcon(":/Resources/folder.png"));
    this->structArchBtn->setIconSize(QSize(28,28));
    this->structArchBtn->setText("Archive structure");
    this->structArchBtn->setStyleSheet("color: #C9DDE9; font-size: 18px; border: none; border-radius: 5px; background-color: #1F2934;");
    this->structArchBtn->setFixedSize(200, 50);

    // this->vertLine = new QFrame(this);
    // this->vertLine->setFrameShape(QFrame::VLine);
    // this->vertLine->setFrameShadow(QFrame::Plain);
    // this->vertLine->setLineWidth(1);
    // this->vertLine->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    // this->vertLine->setStyleSheet("background-color: #3F4D60;");

    this->containerLayout = new QVBoxLayout(this->container);
    this->containerLayout->setContentsMargins(0,0,0,0);
    this->containerLayout->setSpacing(0);
    this->containerLayout->addWidget(this->addArchBtn, Qt::AlignTop);
    this->containerLayout->setSpacing(10);
    this->containerLayout->addWidget(this->structArchBtn);

    // QHBoxLayout* layout = new QHBoxLayout(this->container);
    // layout->addLayout(this->containerLayout, Qt::AlignLeft | Qt::AlignTop);
    // layout->addWidget(this->vertLine);

    this->mainLayout = new QVBoxLayout(this);
    this->mainLayout->setContentsMargins(10,0,0,0);
    this->mainLayout->setSpacing(0);
    this->mainLayout->addWidget(container, 0, Qt::AlignTop);
}
