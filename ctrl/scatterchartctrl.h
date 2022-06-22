#ifndef SCATTERCHARTCTRL_H
#define SCATTERCHARTCTRL_H

#include "ctrl/ctrl.h"
#include "view/scatterchartview.h"
#include "model/scatterchartmodel.h"

/**
 * @brief ScatterChartCtrl classe Controller della schermata ScatterChart
 * Si occupa di elaborare i dati dal model e mostrarli sulla view
 */
class ScatterChartCtrl : public Ctrl{
    Q_OBJECT
public:
    /**
     * @brief ScatterChartCtrl Costruttore che si occupa di creare un controller
     * per la schermata scatterChartView
     * @param v view
     * @param m model
     * @param parent Controller parent
     */
    ScatterChartCtrl(ScatterChartView*, ScatterChartModel*, Ctrl* = nullptr);

    /**
     * @brief getView Metodo virtuale che restituisce la view al tipo corrente ScatterChartView
     * @return View
     */
    ScatterChartView* getView() const override;

    /**
     * @brief getModel Metodo virtuale che restituisce il model al tipo corrente ScatterChartModel
     * @return Model
     */
    ScatterChartModel* getModel() const override;

public slots:
    /**
     * @brief onViewClosed Metodo virtuale che definisce il cosa fare alla chiusura della schermata
     */
    void onViewClosed() const override;
};

#endif // SCATTERCHARTCTRL_H
