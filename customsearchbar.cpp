#include "customsearchbar.h"

customSearchBar::customSearchBar()
{
    QHBoxLayout *hLayout  = new QHBoxLayout;
    QPushButton *searchBtn = new QPushButton;
    searchBtn->setFixedSize(16, 16);
    searchBtn->setCursor(Qt::PointingHandCursor);
    searchBtn->setToolTip("搜索");
    searchBtn->setStyleSheet("QPushButton{ border-image: url(:/images/search-icon.svg);"
                                          "background:transparent;}");
    setPlaceholderText("搜索");
    hLayout->addWidget(searchBtn);
    hLayout->addStretch();
    hLayout->setContentsMargins(8, 0, 0, 0);
    setTextMargins(13+8+2, 0, 0, 0);
    setContentsMargins(0, 0, 0, 0);
    setLayout(hLayout);
    setStyleSheet("height: 30px;background: #ffffff;border: 1px solid #eaeaea;border-radius: 16px;");
    setAttribute(Qt::WA_MacShowFocusRect, 0);
}
