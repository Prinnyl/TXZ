#ifndef MYDATA_H
#define MYDATA_H

#include <QObject>
#include <QMap>
#include <QVector>

class MyData : public QObject
{
    Q_OBJECT
public:
    explicit MyData(QObject *parent = nullptr);
    QMap<int, QVector<QVector<int>>> dataSelect;
    void forData(QMap<int, QVector<QVector<int>>> &myDataSelect, int include, int (*array)[10]);

signals:

public slots:
};

#endif // MYDATA_H
