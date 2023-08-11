#include <QApplication>
#include <QWidget>
#include <QMouseEvent>
#include <QPainter>

class Widget : public QWidget {
    //cpp中不处理Q_OBJECT
    //Q_OBJECT
public:
    explicit Widget(QWidget *parent = nullptr): QWidget(parent){
    }
protected:
    void mousePressEvent(QMouseEvent *event) override{
        pressP = event->localPos();

        QPointF centerP;
        for(int i = 0; i<pointList.size(); i++)
            centerP += pointList[i];
        centerP /= pointList.size();

        centerP = pressP - centerP;
        for(int i = 0; i<pointList.size(); i++)
            pointList[i] += centerP;
        update();
    }

    void mouseMoveEvent(QMouseEvent *event) override{
        moveP = event->localPos() - pressP;
        update();
    }

    void mouseReleaseEvent(QMouseEvent *) override{
        for(int i = 0; i<pointList.size(); i++)
            pointList[i] += moveP;

        moveP.rx() = 0.0;
        moveP.ry() = 0.0;
    }

    void wheelEvent(QWheelEvent *event) override{
        qreal scale;
        if(event->delta()>0){
            scale = 1.1;
        }else{
            scale = 0.9;
        }

        QPointF curP = event->posF();
        for(int i = 0; i<pointList.size(); i++)
            pointList[i] = scale * (pointList[i]-curP) + curP;

        update();
    }

    void paintEvent(QPaintEvent *) override{

        QPainter painter(this);
        painter.setPen(QColor(255,0,0));
        painter.setBrush(Qt::red);

        QPolygonF polygon;
        for(int i = 0; i<pointList.size(); i++)
            polygon << pointList[i] + moveP;

        painter.drawPolygon(polygon);
    }

private:
    QVector<QPointF> pointList{{20.0, 20.0},{250.0,120.0},{50.0,250.0},{20.0,350.0}};
    QPointF pressP;
    QPointF moveP;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
