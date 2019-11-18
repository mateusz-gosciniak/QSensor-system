#ifndef SZTUCZNY_HORYZONT_H
#define SZTUCZNY_HORYZONT_H

#include <QWidget>
#include <QGraphicsView>

#include <QGraphicsScene>
#include <QLinearGradient>
#include <QGraphicsItemGroup>
#include <QGraphicsLineItem>
#include <QGraphicsPolygonItem>

#include <QPolygonF>
#include <QVector>
#include <QPointF>
#include <QRectF>

class sztuczny_horyzont : public  QGraphicsView{
    Q_OBJECT

public:
    explicit sztuczny_horyzont(QWidget *parent = 0);
    ~sztuczny_horyzont();

public slots:
    void obrot_x(int kat);
    void obrot_y(int kat);
    void obrot_z(int kat);

private:
    QGraphicsScene _scena;

    QLinearGradient _tlo_gradient;
    QGraphicsRectItem _tlo;

    QGraphicsItemGroup _celownik;
    QGraphicsLineItem _lpowpp, _lpowp, _lswgnpo, _lswdnp, _lswdnl, _lswgnl, _lpowl, _lpowlp, _lswgnp;

    QPolygonF _samolot_wspolrzedne;
    QGraphicsPolygonItem _samolot;

    void rysuj_tlo();
    void rysuj_samolot();
    void rysuj_celownik();
};

#endif // SZTUCZNY_HORYZONT_H
