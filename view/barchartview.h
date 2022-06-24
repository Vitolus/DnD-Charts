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
private:
    QChart* chart;
    QBarSeries* series;
    QList<QBarSet*> listaSetClassi;
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
     * rappresentante una barra per ciascuna classe
     * @param classe classe titolo del set
     * @param livello livello medio per ogni classe
     */
    void insertSetClasse(const QString&, uint);

    /**
     * @brief applySetsOnChart Metodo che aggiunge i sets alla series
     * successivemente applica la series al chart e nomina gli assi
     * @param listaClassi, lista delle classi da mostrare sul grafico
     */
    void applySetsOnChart();

};

#endif // BARCHARTVIEW_H
