#include "albumitemdelegate.h"

albumItemDelegate::albumItemDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

QSize albumItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    return QSize(260, 66);
}

void albumItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.isValid())
    {
        painter->save();

        QVariant variant = index.data(Qt::UserRole);
        ImageView *imageItem = variant.value<ImageView *>();

//        ImageView::STATE state = ImageView::STATE(index.data(Qt::UserRole + 1).toInt());
        QJsonObject albumInfo = index.data(Qt::UserRole + 2).toJsonObject();

        QStyleOptionViewItem viewOption(option);

        QRectF rect;
        rect.setX(option.rect.x());
        rect.setY(option.rect.y());
        rect.setWidth(option.rect.width() - 1);
        rect.setHeight(option.rect.height() - 1);
        qInfo() << "item size: " << rect;

//        painter->setPen(QColor("#e3e3e5"));
//        painter->drawRoundedRect(rect, 5, 5);

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

        // 鼠标选中
        if (option.state.testFlag(QStyle::State_Selected)) {
            painter->setPen(QPen(QColor("#e3e3e5")));
            painter->setBrush(QColor("#e3e3e5"));
            painter->drawPath(path);
        } else {
            painter->setPen(QPen(Qt::white));
            painter->setBrush(Qt::NoBrush);
            painter->drawPath(path);
        }

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
        // 绘制封面
        QRect albumCoverRect(rect.x() + 12, rect.y() + 15, 36, 36);
        qInfo() << "albumCoverRect: " << albumCoverRect;
        QPixmap newPixmap = imageItem->getPixmap().scaled(36, 36, Qt::KeepAspectRatio, Qt::SmoothTransformation);
//        QPixmap mask;
//        mask.load(":/images/mask.png");
//        newPixmap.setMask(QBitmap(mask));
//        QPixmap rectBackground(36, 36);
//        rectBackground.fill(Qt::transparent);
//        QPainter _painter(&rectBackground);

        painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform); // 抗锯齿和平滑处理
        // 图片裁切圆角
        QPainterPath roundPath;
        roundPath.addRoundedRect(albumCoverRect, 3, 3);
//        painter->setClipPath(roundPath);
//        painter->drawPixmap(rect.x() + 12, rect.y() + 15, 36, 36, newPixmap);

        QBrush brush = QBrush(newPixmap);
        painter->setBrush(brush);
        painter->setBrushOrigin(rect.x() + 12, rect.y() + 15);
        QPolygon p = roundPath.toFillPolygon().toPolygon();
        painter->drawRoundedRect(p.boundingRect(), 3, 3);


        painter->setPen(QColor("#000000"));
        painter->setFont(QFont("PingFang SC", 14, 57));
        QFontMetrics fontMetrics(QFont("PingFang SC", 14, 57));
        QString albumNameText = fontMetrics.elidedText(albumInfo.value("task_name").toString(), Qt::ElideRight, 180);
        QRect albumNameRect = QRect(albumCoverRect.x() + albumCoverRect.width() + 12, albumCoverRect.y(), 180, 20);
        painter->drawText(albumNameRect, Qt::AlignLeft, albumNameText);

        painter->setFont(QFont("PingFang SC", 12, 50));
        QFontMetrics timeFontMetrics(QFont("PingFang SC", 12, 50));
        qInfo() << albumInfo.value("create_time").toString() << QDateTime::fromString(albumInfo.value("create_time").toString(), Qt::ISODateWithMs);
        QString timeText = timeFontMetrics.elidedText(QDateTime::fromString(albumInfo.value("create_time").toString(), Qt::ISODateWithMs).toString("yyyy.MM.dd"), Qt::ElideRight, 180);
        QRect timeRect = QRect(albumCoverRect.x() + albumCoverRect.width() + 12, albumCoverRect.y() + 20, 180, 16);
        painter->drawText(timeRect, Qt::AlignLeft, timeText);

        painter->restore();
    }
}
