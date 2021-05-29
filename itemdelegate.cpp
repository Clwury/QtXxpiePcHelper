#include "itemdelegate.h"

ItemDelegate::ItemDelegate()
{

}

QSize ItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
//    qDebug() << "item resize";
    return QSize(140, 160);
}

void ItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.isValid())
    {
        painter->save();

        QVariant variant = index.data(Qt::UserRole);
        ImageView *imageItem = variant.value<ImageView *>();

        int i = index.data(Qt::UserRole + 1).toInt();

        QStyleOptionViewItem viewOption(option);

        QRectF rect;
//        qDebug() << "item area" << option.rect.x() << option.rect.y() << option.rect.width() << option.rect.height();
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
        } else {
            painter->setPen(QPen(Qt::white));
            painter->setBrush(Qt::NoBrush);
            painter->drawPath(path);
        }

        // 绘制缩略图和文件名
        QRect thumbnailRect = QRect(rect.left() + 10, rect.top() + 10, 120, 120);
        QRect fileNameRect = QRect(rect.left(), thumbnailRect.bottom() + 10, rect.width(), 20);
//        qDebug() << "获取缩略图信息" << index.row() << imageItem->getFileName() << imageItem->getSucceedPixmap();
        if (imageItem->getState() == ImageView::STATE::loading)
        {
            painter->drawPixmap(rect.left() + 10, rect.top() + 10, 120, 120, imageItem->getPixmap());
        } else if (imageItem->getState() == ImageView::STATE::succeed) {
            if (imageItem->getType() == ImageView::TYPE::image)
            {
                painter->drawPixmap(rect.left() + 10, rect.top() + 10, 120, 120, imageItem->getPixmap());
            } else if (imageItem->getType() == ImageView::TYPE::addImageBtn) {
                painter->drawPixmap(rect.left() + 40, rect.top() + 40, 60, 60, imageItem->getPixmap());
            } else if (imageItem->getType() == ImageView::TYPE::subAlbum) {
                painter->drawPixmap(rect.left() + 30, rect.top() + 38, 80, 64, imageItem->getPixmap());
            }

        } else if (imageItem->getState() == ImageView::STATE::failed) {
            painter->drawPixmap(rect.left() + 10, rect.top() + 25, 120, 90, imageItem->getPixmap());
        }

        painter->setPen(QPen(QColor("#000000")));
        painter->setFont(QFont("Times", 12));
        QFontMetrics fontMetrics(QFont("Times", 12));
        QString fileNameText = fontMetrics.elidedText(imageItem->getFileName(), Qt::ElideRight, rect.width());
        painter->drawText(fileNameRect, Qt::AlignCenter, fileNameText);

        painter->restore();
    }
}
