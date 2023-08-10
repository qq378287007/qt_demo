#include <QApplication>
#include <QListWidget>
#include <QLabel>
#include <QHBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QListWidget *listWidget = new QListWidget();

    QListWidgetItem* item;
    QWidget *widget;
    QLabel *leftLabel;
    QLabel *rightLabel;
    QHBoxLayout *wLayout;

    for(int i=0; i<22; i++){
        item = new QListWidgetItem();
        item->setSizeHint(QSize(200, 30));
        listWidget->addItem(item);

        widget = new QWidget();
        leftLabel = new QLabel(QString("left%1").arg(i));
        rightLabel = new QLabel(QString("right%1").arg(i));
        wLayout = new QHBoxLayout();
        wLayout->setMargin(0);
        wLayout->setSpacing(0);
        wLayout->setContentsMargins(0,0,0,0);
        wLayout->addWidget(leftLabel);
        wLayout->addStretch();
        wLayout->addWidget(rightLabel);
        widget->setLayout(wLayout);

        listWidget->setItemWidget(item, widget);
    }

    listWidget->show();
    return a.exec();
}
