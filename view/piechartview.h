#ifndef PIECHARTVIEW_H
#define PIECHARTVIEW_H

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QHBoxLayout>
#include "view/view.h"

QT_CHARTS_USE_NAMESPACE

/**
 * @brief The PieChartView class VIEW della schermata pieChart
 * Mostra un grafico pieChart
 */
class PieChartView : public View{
    Q_OBJECT
protected:
    QPieSeries* series;
    QChart* chart;
    /**
     * @brief connectViewSignals Metodo virtuale che serve a collegare i segnali dei singoli
     * Widget ai segnali della View
     */
    void connectViewSignals() const override;

public:
    explicit PieChartView(const QSize& = QSize(800, 500), View* = nullptr);

    /**
     * @brief insertSlice Metodo che serve ad inserire
     * una nuova razza nel grafico a torta
     * @param razza razza da aggiungere
     * @param occorrenze occorrenze della slice
     */
    virtual void insertRazza(const QString&, uint);

    /**
     * @brief applyGraphics Metodo virtuale che imposta le caratteristiche grafiche
     * per le fetta della PieChart impostando il titolo e il label,
     * mostrando il nome della slice e la percentuale di utilizzo
     */
    virtual void applyGraphics();
};

#endif // PIECHARTVIEW_H
