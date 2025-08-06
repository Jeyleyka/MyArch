#include "ArchiveContent.h"

ArchiveContent::ArchiveContent(QWidget *parent)
    : QWidget(parent), sorted(false)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 10, 0);
    mainLayout->setSpacing(0);

    QHBoxLayout* headerLayout = new QHBoxLayout(this);

    this->titleLabel = new QLabel(tr("Archive contents"), this);
    this->titleLabel->setStyleSheet("color: #C9DDE9; font-size: 21px; font-weight: 600; background-color: #1F2934; border-radius: 5px; padding-left: 5px;");
    this->titleLabel->setFixedSize(250,50);
    headerLayout->addWidget(this->titleLabel, 0, Qt::AlignLeft);

    this->findFiles = new QLineEdit(this);
    this->findFiles->setStyleSheet("color: #C9DDE9; font-size: 21px; font-weight: 600; background-color: #1F2934; border-radius: 5px; padding-left: 5px;");
    this->findFiles->setFixedSize(300,50);
    this->findFiles->setPlaceholderText("Find file or folder...");
    headerLayout->addWidget(this->findFiles);

    mainLayout->addLayout(headerLayout);

    table = new QTableWidget(this);
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels({tr("Name"), tr("Size"), tr("Type")});

    connect(this->findFiles, &QLineEdit::textChanged, this, &ArchiveContent::filterTable);

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

    this->table->verticalScrollBar()->setStyleSheet(R"(
    QScrollBar:vertical {
        background: #1F2934;
        width: 10px;
        margin: 0px 0px 0px 0px;
        border-radius: 5px;
    }

    QScrollBar::handle:vertical {
        background: #3B82F6;
        min-height: 25px;
        border-radius: 5px;
    }

    QScrollBar::handle:vertical:hover {
        background: #60A5FA;
    }

    QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
        background: none;
        height: 0px;
    }

    QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {
        background: none;
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

QTableWidget* ArchiveContent::getTable() const {
    return this->table;
}

void ArchiveContent::addEntry(const QIcon& icon, const QString &name, const QString &size, const QString &type) {
    int row = this->table->rowCount();
    this->table->insertRow(row);

    QTableWidgetItem* nameItem = new QTableWidgetItem(icon, name);
    QTableWidgetItem* sizeItem = new QTableWidgetItem(size);
    QTableWidgetItem* typeItem = new QTableWidgetItem(type);

    this->table->setItem(row, 0, nameItem);
    this->table->setItem(row, 1, sizeItem);
    this->table->setItem(row, 2, typeItem);
}

void ArchiveContent::filterTable(const QString &text) {
    for (int row = 0; row < this->table->rowCount(); ++row) {
        bool match = false;

        QString fileName = this->table->item(row, 0)->text();

        if (fileName.contains(text, Qt::CaseInsensitive))
            match = true;

        this->table->setRowHidden(row, !match);
    }
}
