#include "triangleitem.h"

#include <QPainter>
#include <QRandomGenerator>

TriangleItem::TriangleItem(QQuickItem *parent): QQuickPaintedItem (parent)
{
    m_colorAnimation = new QVariantAnimation(this);
    m_colorAnimation->setDuration(1000);
    m_interpolationAnimation = new QVariantAnimation { this };
    m_interpolationAnimation->setDuration(900);
    m_interpolationAnimation->setEasingCurve(QEasingCurve::OutCubic);

    m_interpolationAnimWithDelay = new QSequentialAnimationGroup(this);
    m_interpolationAnimWithDelay->addAnimation(m_interpolationAnimation);


//    connect(this, &TriangleItem::srcPointsChanged, [this]() { this->update(); });
    connect(this, &TriangleItem::srcPointsChanged, this, &TriangleItem::setUpContent);
    connect(this, &TriangleItem::destPointsChanged, this, &TriangleItem::setUpContent);

//    connect(this, &TriangleItem::interpolationChanged, this, &TriangleItem::setUpContent);
    connect(this, &TriangleItem::destPointsChanged, this, &TriangleItem::setUpContent);
    connect(m_colorAnimation, &QVariantAnimation::valueChanged, [this](const QVariant& v) {
        m_animatedColor = v.value<QColor>();
        this->update();
    });

    connect(m_colorAnimation, &QVariantAnimation::finished,
            this, &TriangleItem::setUpColorAnimation);

    connect(this, &TriangleItem::colorChanged, [this] {
        m_colorAnimation->stop();
        this->setUpColorAnimation();
        this->update();
    });

    connect(m_interpolationAnimation, &QVariantAnimation::valueChanged, [this](const QVariant& v) {
        m_interpolation = v.toReal();
        this->setUpContent();
        this->update();
    });
}

void TriangleItem::paint(QPainter *painter)
{
    if(m_srcPoints.empty())
        return;
    painter->setRenderHint(QPainter::Antialiasing);

    painter->setPen(QColor(Qt::transparent));
    painter->setBrush(m_animatedColor);

    painter->drawPolygon(m_polygon);
}

QColor TriangleItem::color() const
{
    return m_color;
}

QVector<QPointF> TriangleItem::srcPoints() const
{
    return m_srcPoints;
}

QVector<QPointF> TriangleItem::destPoints() const
{
    return m_destPoints;
}

void TriangleItem::setUpColorAnimation()
{
    m_colorAnimation->setStartValue(m_color);
    const double diff = QRandomGenerator::global()->bounded(0.7) - 0.35;
    m_colorAnimation->setKeyValueAt(0.5, m_color.lighter(
                                        static_cast<int>(100. +
                                                         (255 - m_color.lightness()) * diff)));
    m_colorAnimation->setEndValue(m_color);
    if(m_runColorAnimation)
        m_colorAnimation->start();
}

void TriangleItem::setUpContent()
{

    if(m_srcPoints.empty() || m_destPoints.empty())
        return;

    m_polygon.clear();
    QMatrix4x4 transMatrix;
    transMatrix = m_currentTransformation;

    for(int i = 0; i < m_srcPoints.length(); i++) {
        const QPointF srcPoint = m_srcPoints.at(i);
        const QPointF destPoint = transMatrix.inverted().map(m_destPoints.at(i));
        m_polygon << srcPoint + (destPoint - srcPoint) * m_interpolation;
    }

    const QPointF pos = m_polygon.boundingRect().topLeft();
    this->setPosition(pos);
    this->setSize(m_polygon.boundingRect().size());
    m_polygon.translate(-pos.x(), -pos.y());
    this->update();
}

void TriangleItem::setRawInterpolation(qreal i)
{
    m_interpolation = i;
}

void TriangleItem::setAnimationDelay(int delay)
{
    m_interpolationAnimWithDelay->insertPause(0, delay);
}

void TriangleItem::interpolate(bool inverted)
{
    m_interpolationAnimWithDelay->stop();
    m_interpolationAnimation->setCurrentTime(0);

    if(inverted) {
        m_interpolationAnimation->setStartValue(1.);
        m_interpolationAnimation->setEndValue(0.);
    }

    else {
        m_interpolationAnimation->setStartValue(0.);
        m_interpolationAnimation->setEndValue(1.);
    }
    m_interpolationAnimWithDelay->start();
}

void TriangleItem::setCurrentTransformation(const QMatrix4x4& currentTransformation)
{
    m_currentTransformation = currentTransformation;
}

void TriangleItem::setColor(QColor color)
{
    if (m_color == color)
        return;

    m_color = color;
    m_animatedColor = color;
    emit colorChanged(m_color);
}

void TriangleItem::setSrcPoints(QVector<QPointF> srcPoints)
{
   this->setSize(QSizeF{100, 100});
    if (m_srcPoints == srcPoints)
        return;

    m_srcPoints = srcPoints;
    emit srcPointsChanged(m_srcPoints);
}

void TriangleItem::setDestPoints(QVector<QPointF> destPoints)
{
    if (m_destPoints == destPoints)
        return;

    m_destPoints = destPoints;
    emit destPointsChanged(m_destPoints);
}
