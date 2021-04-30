#include "itemdelegate.h"

ItemDelegate::ItemDelegate()
{

}

QSize ItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(140, 160);
}

void ItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.isValid())
    {
        painter->save();

        QVariant variant = index.data(Qt::UserRole);
        ImageView imageItem = variant.value<ImageView>();

        QStyleOptionViewItem viewOption(option);

        QRectF rect;
        rect.setX(option.rect.x());
        rect.setY(option.rect.y());
        rect.setWidth(option.rect.width() - 1);
        rect.setHeight(option.rect.height() - 1);

        QPainterPath path;
        path.moveTo(rect.topRight());
        path.lineTo(rect.topLeft());
        path.quadTo(rect.topLeft(), rect.topLeft());
        path.lineTo(rect.bottomLeft());
        path.quadTo(rect.bottomLeft(), rect.bottomLeft());
        path.lineTo(rect.bottomRight());
        path.quadTo(rect.bottomRight(), rect.bottomRight());
        path.lineTo(rect.topRight());
        path.quadTo(rect.topRight(), rect.topRight());

        // 鼠标悬停或选中
        if (option.state.testFlag(QStyle::State_MouseOver))
        {
            painter->setPen(QPen(QColor("#ebeced")));
            painter->setBrush(QColor("#ebeced"));
            painter->drawPath(path);
        } else if (option.state.testFlag(QStyle::State_Selected)) {
            painter->setPen(QPen(QColor("#e3e3e5")));
            painter->setBrush(QColor("#e3e3e5"));
            painter->drawPath(path);
        }

        // 绘制缩略图和文件名
        QRect thumbnailRect = QRect(rect.left() + 10, rect.top() + 10, 120, 120);
        QRect fileNameRect = QRect(thumbnailRect.bottom() + 10, rect.left() + 10, 100, 20);

        painter->drawPixmap(rect.left() + 10, rect.top() + 10, 120, 120, imageItem.getSucceedPixmap());

        painter->setPen(QPen(Qt::gray));
        painter->setFont(QFont("Times", 10));
        painter->drawText(fileNameRect, imageItem.getFileName());

        painter->restore();
    }
}
