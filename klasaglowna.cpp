#include "klasaglowna.h"
#include "ui_klasaglowna.h"

KlasaGlowna::KlasaGlowna(QWidget *parent) : QMainWindow(parent), ui(new Ui::KlasaGlowna){
    ui->setupUi(this);
}

KlasaGlowna::~KlasaGlowna(){
    delete ui;
}

void KlasaGlowna::on_pushButton_budynek_clicked(){

    QString nazwa_pliku = QFileDialog::getOpenFileName(this,tr("Otwórz plik"),"","Pliki path (*.path);;Wszystkie pliki (*.*)");
    QMessageBox::information(this,tr("Nazwa pliku: "),nazwa_pliku);

    std::ifstream plik(nazwa_pliku.toStdString().c_str());

    bool poczatek_pliku = true;
    int liczba_klatek = 0;
    pozycja polozenie;

    if(poczatek_pliku){
        plik >> liczba_klatek;
        poczatek_pliku = false;
    }

    for(int i=0;i<liczba_klatek;i++){
        /// jeśli kierunki obrotu są złe to tutaj zmieniamy kolejność wczytywania zmiennych z pliku .path
        plik >> polozenie._x >> polozenie._y >> polozenie._z >> polozenie._ya >> polozenie._pi >> polozenie._ro;
        ui->okno_3d->_wektor_pozycji.push_back(polozenie);
    }
    plik.close();

    /// tu może być przekroczony zakres
    ui->suwak->setRange(0,ui->okno_3d->_wektor_pozycji.size());
    ui->suwak->setSliderPosition(ui->okno_3d->_wektor_pozycji.size());
    ui->okno_3d->_aktualna_klatka = ui->okno_3d->_wektor_pozycji.size();
    ui->okno_3d->update();
}

void KlasaGlowna::on_suwak_sliderMoved(int position){
    ui->okno_3d->_aktualna_klatka = position;
    ui->graphicsView->obrot_x(ui->okno_3d->_wektor_pozycji[position]._ro * 16);
    ui->graphicsView->obrot_y(ui->okno_3d->_wektor_pozycji[position]._pi * 16);
    ui->graphicsView->obrot_z(ui->okno_3d->_wektor_pozycji[position]._ya * 16);
}
