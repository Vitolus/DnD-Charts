#ifndef SCATTERCHARTVIEW_H
#define SCATTERCHARTVIEW_H

#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>
#include <QHBoxLayout>
#include "view/view.h"

QT_CHARTS_USE_NAMESPACE

class ScatterChartView : public View{
    Q_OBJECT
private:
    QChart* chart;
    QList<QScatterSeries*> allineamentiSerie;
    /**
     * @brief connectViewSignals Metodo virtuale che serve a collegare i segnali dei singoli
     * Widget ai segnali della View
     */
    void connectViewSignals() const override;
public:
    /**
     * @brief ScatterChartView  Costruttore della View ScatterChart
     * @param size Grandezza della schermata
     * @param parent padre(view) della vista che ha invocato la suddetta vista
     */
    explicit ScatterChartView(const QSize& = QSize(800, 500), View* = nullptr);

    /**
     * @brief insertAllineamento Metodo che serve ad inserire i dati di una classe,
     * questi dati saranno elaborati e per ciascuna classe sarà creato un punto nel grafico.
     * Il Punto viene rappresentato dalle coordinate x,y date dall'allineamento.
     * @param classe classe identificante il punto
     * @param allineamento coordinate del punto sul grafo
     */
    void insertAllineamento(const QString&, const std::pair<uint, uint>);

    /**
     * @brief applyChartSeries Metodo che applica le serie create (insieme di punti)
     * e le mostra al grafico chart.
     */
    void applyChartSeries();
};

#endif // SCATTERCHARTVIEW_H
