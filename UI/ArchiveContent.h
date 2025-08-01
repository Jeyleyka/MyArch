#ifndef ARCHIVECONTENT_H
#define ARCHIVECONTENT_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QIcon>

class ArchiveContent : public QWidget
{
    Q_OBJECT

public:
    explicit ArchiveContent(QWidget *parent = nullptr);

private:
    QLabel* titleLabel;
    QListWidget* contentList;

    void setupUI();
    void populateDummyContent(); // Для примера
};

#endif // ARCHIVECONTENT_H
