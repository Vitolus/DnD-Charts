#ifndef BARCHARTVIEW_H
#define BARCHARTVIEW_H

#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QScrollBar>
#include <QHBoxLayout>
#include <map>
#include "view/view.h"

QT_CHARTS_USE_NAMESPACE

class BarChartView : public View{
    Q_OBJECT
protected:
    QChart* chart;
    QBarSeries* series;
    QList<QBarSet*> listaSetClassi;
    QScrollBar* chartScroll;
    //Parametro che indica quante classi mostrare alla volta nel grafico
    int maxVisClassi= 7;

    /**
     * @brief connectViewSignals Metodo virtuale che serve a collegare
     * i segnali dei singoli Widget ai segnali della View
     */
    void connectViewSignals() const override;

public:
    /**
     * @brief BarChartView Costruttore della View
     * @param size size della window
     * @param parent view parente invocante
     */
    explicit BarChartView(const QSize& = QSize(800, 500), View* = nullptr);

    /**
     * @brief insertSetClasse Metodo che serve ad inserire un SET di dati
     * Un set di dati in questo caso rappresenta una barra per ciascun meseA
     * cioè ciascuna data.
     * @param materiale materiale titolo del set
     * @param consumiMesi consumi per ogni meseA del set, per ogni barra
     */
    void insertSetClasse(const QString&, uint);

    /**
     * @brief applySetsOnChart Metodo che aggiunge i sets allla series
     * successivemente applica la series al chart.
     * in pratica mostra i dati al chart.
     */
    void applySetsOnChart();

    /**
     * @brief applyAxis Metodo che imposta i dettagli degli Assi
     * impostandone la grandezza e la descrizione
     * @param mesi lista dei meseA con la descrizione per l'asse X
     * @param maxY massimo intero dei dati da rapresentare, appunto con la
     * granzza massima del asse y
     */
    void applyAxis(const QStringList& mesi, const uint maxY);

};

#endif // BARCHARTVIEW_H
