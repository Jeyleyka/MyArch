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

#include "SizeItem.h"

class ArchiveContent : public QWidget {
    Q_OBJECT
public:
    explicit ArchiveContent(QWidget *parent = nullptr);

    QTableWidget* getTable() const;

public slots:
    void addEntry(const QIcon& icon, const QString& name, const QString& size, const QString& type);

private:
    QLabel *titleLabel;
    QTableWidget *table;

    bool sorted;
};


#endif // ARCHIVECONTENT_H
