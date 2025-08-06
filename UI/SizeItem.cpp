#include "SizeItem.h"

SizeItem::SizeItem(const QString& sizeText)
    : QTableWidgetItem(sizeText), m_size(parseSize(sizeText)) {}

bool SizeItem::operator< (const QTableWidgetItem& other) const {
    auto otherItem = dynamic_cast<const SizeItem*>(&other);

    if (otherItem)
        return m_size < otherItem->m_size;

    return QTableWidgetItem::operator<(other);
}

qint64 SizeItem::parseSize(const QString &text) {
    QString t = text.trimmed().toUpper();
    double number = t.section(' ', 0, 0).toDouble();
    QString unit = t.section(' ', 1, 1);

    if (unit == "KB") return static_cast<qint64>(number * 1024);
    if (unit == "MB") return static_cast<qint64>(number * 1024 * 1024);
    if (unit == "GB") return static_cast<qint64>(number * 1024 * 1024 * 1024);
    if (unit == "B") return static_cast<qint64>(number);

    return 0;
}
