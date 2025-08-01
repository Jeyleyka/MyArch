#include "Footer.h"

Footer::Footer(QWidget *parent)
    : QWidget{parent}
{
    this->container = new QWidget(this);
    this->container->setStyleSheet("background-color: #253240; margin: 0px; padding: 0px;");
    this->container->setFixedHeight(70);
    this->container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    this->title = new QLabel("MyArch", this);
    this->title->setStyleSheet("color: #C9DDE9; font-size: 25px; font-weight: bold; padding-left: 10px;");

    this->changeThemeBtn = new QPushButton(this);
    this->changeThemeBtn->setIcon(QIcon(":/Resources/exchange.png"));
    this->changeThemeBtn->setIconSize(QSize(24,24));
    this->changeThemeBtn->setFixedSize(24,24);
    this->changeThemeBtn->setStyleSheet("border: none");

    this->settingsBtn = new QPushButton(this);
    this->settingsBtn->setIcon(QIcon(":/Resources/setting.png"));
    this->settingsBtn->setIconSize(QSize(24,24));
    this->settingsBtn->setText("Settings");
    this->settingsBtn->setStyleSheet("color: #C9DDE9; font-size: 19px; border: none; margin-right: 10px;");
    this->settingsBtn->setFixedWidth(120);

    this->containerLayout = new QHBoxLayout(this->container);
    this->containerLayout->setContentsMargins(0, 0, 0, 0);
    this->containerLayout->setSpacing(0);
    this->containerLayout->addWidget(this->title);
    this->containerLayout->addWidget(this->changeThemeBtn);
    this->containerLayout->setSpacing(30);
    this->containerLayout->addWidget(this->settingsBtn);

    this->mainLayout = new QVBoxLayout(this);
    this->mainLayout->setContentsMargins(0, 0, 0, 0);
    this->mainLayout->setSpacing(0);
    this->mainLayout->addWidget(this->container);
}
