#include "sztuczny_horyzont.h"

///// najlepiej wywalić wszystko i zrobić na opengl

void sztuczny_horyzont::rysuj_tlo(){
        _tlo_gradient.setStart(QPointF(width(), -2));
        _tlo_gradient.setFinalStop(QPointF(width(),height()));
        _tlo_gradient.setColorAt(0, Qt::green);
        _tlo_gradient.setColorAt(0.1, Qt::blue);

        _tlo.setRect(-500,-500,1000,1000);
        _tlo.setRotation(180);
        _tlo.setBrush(QBrush(_tlo_gradient));
}

void sztuczny_horyzont::rysuj_samolot(){
    _samolot_wspolrzedne.push_back(QPointF(46,0));
    _samolot_wspolrzedne.push_back(QPointF(32.5,6));
    _samolot_wspolrzedne.push_back(QPointF(22,6));
    _samolot_wspolrzedne.push_back(QPointF(-5,47));
    _samolot_wspolrzedne.push_back(QPointF(-14.5,47));
    _samolot_wspolrzedne.push_back(QPointF(3,5));
    _samolot_wspolrzedne.push_back(QPointF(-33.5,4));
    _samolot_wspolrzedne.push_back(QPointF(-40,14.5));
    _samolot_wspolrzedne.push_back(QPointF(-47,14.5));
    _samolot_wspolrzedne.push_back(QPointF(-41,0));
    _samolot_wspolrzedne.push_back(QPointF(-47,-14.5));
    _samolot_wspolrzedne.push_back(QPointF(-40,-14.5));
    _samolot_wspolrzedne.push_back(QPointF(-33.5,-4));
    _samolot_wspolrzedne.push_back(QPointF(3,-5));
    _samolot_wspolrzedne.push_back(QPointF(-14.5,-47));
    _samolot_wspolrzedne.push_back(QPointF(-5,-47));
    _samolot_wspolrzedne.push_back(QPointF(22,-6));
    _samolot_wspolrzedne.push_back(QPointF(32.5,-6));

    _samolot.setPolygon(_samolot_wspolrzedne);
    _samolot.setRotation(-90);
    _samolot.setPos(0,170);
    _samolot.setScale(0.8);
}

void sztuczny_horyzont::rysuj_celownik(){
    // linia pozioma odchodząca w prawo przerywana
    _lpowpp.setLine(-250,0,-35,0); _lpowpp.setPen(QPen(QBrush(QColor(0,0,0)),1,Qt::DashLine));
    // linia pozioma odchodząca w prawo
    _lpowp.setLine(-35,0,-20,0); _lpowp.setPen(QPen(QBrush(QColor(0,0,0)),2,Qt::SolidLine));
    // linia skosna w górę na prawo
    _lswgnp.setLine(-20,0,-10,10); _lswgnp.setPen(QPen(QBrush(QColor(0,0,0)),2,Qt::SolidLine));
    // linia skosna w dol na prawo
    _lswdnp.setLine(0,0,10,10); _lswdnp.setPen(QPen(QBrush(QColor(0,0,0)),2,Qt::SolidLine));
    // linia skosna w dol na lewo
    _lswdnl.setLine(0,0,-10,10); _lswdnl.setPen(QPen(QBrush(QColor(0,0,0)),2,Qt::SolidLine));
    // linia skosna w górę na lewo
    _lswgnl.setLine(20,0,10,10); _lswgnl.setPen(QPen(QBrush(QColor(0,0,0)),2,Qt::SolidLine));
    // linia pozioma odchodząca w lewo
    _lpowl.setLine(35,0,20,0); _lpowl.setPen(QPen(QBrush(QColor(0,0,0)),2,Qt::SolidLine));
    // linia pozioma odchodząca w lewo przerywana
    _lpowlp.setLine(250,0,35,0); _lpowlp.setPen(QPen(QBrush(QColor(0,0,0)),1,Qt::DashLine));

    _celownik.addToGroup(&_lpowpp);
    _celownik.addToGroup(&_lpowp);
    _celownik.addToGroup(&_lswgnpo);
    _celownik.addToGroup(&_lswdnp);
    _celownik.addToGroup(&_lswdnl);
    _celownik.addToGroup(&_lswgnl);
    _celownik.addToGroup(&_lpowl);
    _celownik.addToGroup(&_lpowlp);
    _celownik.addToGroup(&_lswgnp);
}

sztuczny_horyzont::sztuczny_horyzont(QWidget *parent) : QGraphicsView(parent) {
    rysuj_celownik();
    rysuj_samolot();
    rysuj_tlo();
/// ustawienia sceny
    _scena.addItem(&_tlo);
    _scena.addItem(&_samolot);
    _scena.addItem(&_celownik);
    _celownik.setFlag(QGraphicsItem::ItemIgnoresTransformations,true);
    _samolot.setFlag(QGraphicsItem::ItemIgnoresTransformations,true);
    _tlo.setFlag(QGraphicsItem::ItemIgnoresTransformations,true);

    _scena.setBackgroundBrush(Qt::red);

    this->setScene(&_scena);
    this->show();
    this->setFixedSize(500,500);
}

sztuczny_horyzont::~sztuczny_horyzont() {}

void sztuczny_horyzont::obrot_x(int kat){
    _samolot.setRotation(kat/16+90);
}

void sztuczny_horyzont::obrot_y(int kat){
    _tlo.setPos(0,kat/16-180);
}

void sztuczny_horyzont::obrot_z(int kat){
    _tlo.setRotation(kat/16);
}
