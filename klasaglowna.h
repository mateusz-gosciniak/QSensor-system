#ifndef KLASAGLOWNA_H
#define KLASAGLOWNA_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>

#include <fstream>

namespace Ui {
class KlasaGlowna;
}

class KlasaGlowna : public QMainWindow
{
    Q_OBJECT

public:
    explicit KlasaGlowna(QWidget *parent = 0);
    ~KlasaGlowna();

private slots:
    void on_pushButton_budynek_clicked();

    void on_suwak_sliderMoved(int position);

private:
    Ui::KlasaGlowna *ui;
};

#endif // KLASAGLOWNA_H
