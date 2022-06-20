#ifndef PIECHARTOVIEW_H
#define PIECHARTOVIEW_H

#include "view/piechartview.h"

/**
 * @brief The PieChartOView class Classe derivata da PieChartView
 * è la View per mostrare un grafico a torta con occorrenze
 */
class PieChartOView : public PieChartView{
    Q_OBJECT
public:
    explicit PieChartOView(QSize = QSize(800, 500), View* = nullptr);

    /**
     * @brief insertSlice Metodo virtuale che serve ad inserire una nuova slice
     * nel grafico a torta con anche il numero di occorezze
     * @param slice slice da inserire
     * @param occorrenze occorenze della slice
     */
    void insertSlice(const QString&, uint) override;

    /**
     * @brief applyGraphics Metodo virtuale che imposta le caratteristiche grafiche
     * per le fetta della PieChart impostando il titolo e il label,
     * mostrando il nome della slice e il numero di occorrenze
     */
    void applyGraphics() override;
};

#endif // PIECHARTOVIEW_H
