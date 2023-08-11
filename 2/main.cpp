#include <QApplication>
#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QtMath>
#include <QDebug>

class Widget : public QWidget {
public:
    explicit Widget(QWidget *parent = nullptr): QWidget(parent){}
protected:
    void mousePressEvent(QMouseEvent *event) override{
        pressP = event->localPos();
    }

    void mouseMoveEvent(QMouseEvent *event) override{
        moveP = event->localPos() - pressP;
        update();
    }

    void mouseReleaseEvent(QMouseEvent *) override{
        offsetP += moveP;
        moveP = QPointF(0.0, 0.0);
        update();
    }

    void wheelEvent(QWheelEvent *event) override{
        int n = event->delta()/120;
        qreal k2 = pow(mScaleBase, n);
        mScale *= k2;
        offsetP = k2 * offsetP + (1.0 - k2) * event->posF();
        update();
    }

    void paintEvent(QPaintEvent *) override{
        QPainter painter(this);
        painter.save();

        painter.setPen(QColor(255,0,0));
        painter.setBrush(Qt::red);
        QPointF tmpP = offsetP + moveP;

        QTransform transform;
        transform.translate(tmpP.x(), tmpP.y());
        transform.scale(mScale, mScale);
        painter.setTransform(transform);

        QPolygonF mPolygon;
        for(int i=0; i<3; i++)
            //mPolygon<<mScale * mPs[i] + tmpP;//与transform等价
            mPolygon<<mPs[i] ;
        painter.drawPolygon(mPolygon);

        painter.restore();

        //计算屏幕上的每一个像素
        QImage pic(size(),QImage::Format_RGB888);
        pic.fill(Qt::white);

        for(int row=0;row<height();row++){
            qreal y = row+0.5;
            for(int col=0;col<width();col++){
                qreal x = col+0.5;
                QPointF p{x,y};
                if(mPolygon.containsPoint((p-tmpP) / mScale, Qt::WindingFill))
                    pic.setPixelColor(x,y,Qt::red);
            }
        }
        painter.drawImage(rect(), pic);
    }

private:
    QVector<QPointF> mPs{{20.0, 20.0}, {250.0,120.0}, {50.0,250.0}};
    qreal mScaleBase{1.1};
    qreal mScale{1.0};
    QPointF offsetP{0.0, 0.0};
    QPointF pressP{0.0, 0.0};
    QPointF moveP{0.0, 0.0};
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
