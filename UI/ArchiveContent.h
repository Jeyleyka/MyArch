#ifndef ARCHIVECONTENT_H
#define ARCHIVECONTENT_H

#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QFont>
#include <QFileIconProvider>
#include <QFileInfo>

class ArchiveContent : public QWidget {
    Q_OBJECT
public:
    explicit ArchiveContent(QWidget *parent = nullptr);



private:
    QLabel *titleLabel;
    QTableWidget *table;

    bool sorted;
};


#endif // ARCHIVECONTENT_H
