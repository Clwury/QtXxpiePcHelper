#include "albumitemdelegate.h"

albumItemDelegate::albumItemDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

QSize albumItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(236, 190);
}

void albumItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.isValid())
    {
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);

        QVariant variant = index.data(Qt::UserRole);
        ImageView *imageItem = variant.value<ImageView *>();

        ImageView::STATE state = ImageView::STATE(index.data(Qt::UserRole + 1).toInt());
        QJsonObject albumInfo = index.data(Qt::UserRole + 2).toJsonObject();

        QStyleOptionViewItem viewOption(option);

        QRectF rect;
        rect.setX(option.rect.x());
        rect.setY(option.rect.y());
        rect.setWidth(option.rect.width() - 1);
        rect.setHeight(option.rect.height() - 1);

        painter->setPen(QColor("#e3e3e5"));
        painter->drawRoundedRect(rect, 5, 5);



//        float x = (imageItem->getPixmap().width() - 236) / 2;
//        float y = (imageItem->getPixmap().height() - 140) / 2;
//        QRectF albumCoverSource = QRectF(x, y, 236, 140);
//        QRectF albumCoverRect = QRectF(rect.left(), rect.top(), 236, 140);
//        if (state == ImageView::STATE::loading || state == ImageView::STATE::failed)
//        {
//            painter->drawPixmap(rect.left(), rect.top(), 236, 140, imageItem->getPixmap());
//        } else if (state == ImageView::STATE::succeed) {
//            painter->drawPixmap(albumCoverRect, imageItem->getPixmap(), albumCoverSource);
//        }

//        painter->setPen(QColor("#000000"));
//        painter->setFont(QFont("Hiragino Sans GB", 12));
//        QFontMetrics fontMetrics(QFont("Hiragino Sans GB", 12));
//        QString albumNameText = fontMetrics.elidedText(albumInfo.value("task_name").toString(), Qt::ElideRight, rect.width());

//        QRectF albumNameRect = QRectF(albumCoverRect.left() + 3, albumCoverRect.bottom() + 3, rect.width(), 20);
//        painter->drawText(albumNameRect, Qt::AlignLeft, albumNameText);

//        QFontMetrics sFontMetrics(QFont("Hiragino Sans GB", 10));
//        QString createdTimeText = sFontMetrics.elidedText("创建时间：" + albumInfo.value("create_time").toString(), Qt::ElideRight, rect.width());
//        QRectF createdTimeRect = QRectF(albumCoverRect.left() + 3, albumNameRect.bottom() + 2, rect.width(), 20);
//        painter->drawText(createdTimeRect, Qt::AlignLeft, createdTimeText);

        painter->restore();
    }
}
