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
#include <QLineEdit>
#include <QScrollBar>

#include "../SizeItem/SizeItem.h"

class ArchiveContent : public QWidget {
    Q_OBJECT
public:
    explicit ArchiveContent(QWidget *parent = nullptr);

    QTableWidget* getTable() const;

public slots:
    void addEntry(const QIcon& icon, const QString& name, const QString& size, const QString& type);

private slots:
    void filterTable(const QString& text);

private:
    QLabel *titleLabel;
    QLineEdit* findFiles;
    QTableWidget *table;

    bool sorted;
};


#endif // ARCHIVECONTENT_H
