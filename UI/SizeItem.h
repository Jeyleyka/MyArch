#ifndef SIZEITEM_H
#define SIZEITEM_H

#include <QTableWidget>

class SizeItem : public QTableWidgetItem
{
public:
    explicit SizeItem(const QString& sizeText);

    bool operator< (const QTableWidgetItem& other) const override;

private:
    static qint64 parseSize(const QString& text);

    qulonglong m_size;
};

#endif // SIZEITEM_H
