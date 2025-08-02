#ifndef BUTTONGROUP_H
#define BUTTONGROUP_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFrame>

class ButtonGroup : public QWidget
{
    Q_OBJECT
public:
    explicit ButtonGroup(QWidget *parent = nullptr);

signals:
    void createArchiveRequested();

private:
    QWidget* container;

    QVBoxLayout* containerLayout;
    QVBoxLayout* mainLayout;

    QPushButton* addArchBtn;
    QPushButton* structArchBtn;

    // QFrame* vertLine;
};

#endif // BUTTONGROUP_H
