#include "ArchiveContent.h"

ArchiveContent::ArchiveContent(QWidget *parent)
    : QWidget(parent), sorted(false)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 10, 0);
    mainLayout->setSpacing(0);

    titleLabel = new QLabel(tr("Archive contents"), this);
    titleLabel->setStyleSheet("color: #C9DDE9; font-size: 21px; font-weight: 600; background-color: #1F2934; border-radius: 5px; padding-left: 5px;");
    titleLabel->setFixedSize(250,50);
    mainLayout->addWidget(titleLabel);

    table = new QTableWidget(this);
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels({tr("Name"), tr("Size"), tr("Type")});

    QTableWidgetItem *sizeHeaderItem = new QTableWidgetItem();
    sizeHeaderItem->setData(Qt::DisplayRole, QVariant());
    sizeHeaderItem->setText("Size");
    table->setHorizontalHeaderItem(1, sizeHeaderItem);

    QIcon sortIcon(":/Resources/down-arrow.png");
    sizeHeaderItem->setIcon(sortIcon);
    sizeHeaderItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    // Внешний вид таблицы
    table->setShowGrid(false);
    table->setFrameStyle(QFrame::NoFrame);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionMode(QAbstractItemView::NoSelection);
    table->setFocusPolicy(Qt::NoFocus);
    table->verticalHeader()->setVisible(false);
    table->setFixedSize(800, 400);
    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    table->setStyleSheet(R"(
        QTableWidget {
            background-color: #18222B;
            color: #FFFFFF;
            font-size: 18px;
            border: none;
        }
        QHeaderView::section {
            background-color: #212A36;
            color: #A9B7C6;
            padding: 6px;
            font-size: 15px;
            border: none;
            font-weight: bold;
        }
        QTableWidget::item {
            border: none;
            padding: 6px;
            color: #FFFFFF;
        }
    )");

    // Настройки заголовков
    QHeaderView *header = table->horizontalHeader();
    header->setStretchLastSection(false); // Последняя колонка не растягивается
    header->setSectionsClickable(true);
    header->setHighlightSections(false);
    header->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    header->setSectionResizeMode(QHeaderView::Interactive);

    int totalWidth = table->viewport()->width();

    table->setColumnWidth(0, totalWidth * 0.6);
    table->setColumnWidth(1, totalWidth * 0.2);
    table->setColumnWidth(2, totalWidth * 0.2);

    QIcon fileIcon(":/Resources/document.png");
    QTableWidgetItem *fileItem = new QTableWidgetItem("main.cpp");
    fileItem->setIcon(fileIcon);
    table->setIconSize(QSize(24, 24));

    // table->insertRow(0);
    // table->setItem(0, 0, fileItem);
    // table->setItem(0, 1, new QTableWidgetItem("Text File"));
    // table->setItem(0, 2, new QTableWidgetItem("C++ Source"));

    // table->insertRow(1);
    // table->setItem(1, 0, new QTableWidgetItem("image.png"));
    // table->setItem(1, 1, new QTableWidgetItem("120 KB"));
    // table->setItem(1, 2, new QTableWidgetItem("PNG File"));

    // Обработка клика по заголовку
    connect(header, &QHeaderView::sectionClicked, this, [=](int index) {
        if (index == 1) {
            if (!this->sorted) {
                QIcon sortIcon(":/Resources/up-arrow.png");
                sizeHeaderItem->setIcon(sortIcon);
                this->sorted = true;
            }
            else {
                QIcon sortIcon(":/Resources/down-arrow.png");
                sizeHeaderItem->setIcon(sortIcon);
                this->sorted = false;
            }

            sizeHeaderItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        }

        qDebug() << "Клик по заголовку столбца:" << index << "sorted: " << this->sorted;
    });

    mainLayout->addWidget(table);
    mainLayout->addStretch();
}

void ArchiveContent::addEntry(const QString &name, const QString &size, const QString &type) {
    int row = this->table->rowCount();
    this->table->insertRow(row);

    this->table->setItem(row, 0, new QTableWidgetItem(name));
    this->table->setItem(row, 1, new QTableWidgetItem(size));
    this->table->setItem(row, 2, new QTableWidgetItem(type));
}
