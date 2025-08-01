#ifndef FOOTER_H
#define FOOTER_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class Footer : public QWidget
{
    Q_OBJECT

public:
    explicit Footer(QWidget *parent = nullptr);

signals:

private:
    QVBoxLayout* mainLayout;

    QHBoxLayout* containerLayout;

    QWidget* container;

    QLabel* title;

    QPushButton* changeThemeBtn;
    QPushButton* settingsBtn;
};

#endif // FOOTER_H
