#include "scatterchartctrl.h"


ScatterChartCtrl::ScatterChartCtrl(ScatterChartView* v, ScatterChartModel* m, Ctrl* parent) :
    Ctrl(v, m, parent){

    for(QMap<QString, std::pair<uint, uint>>::const_iterator it= getModel()->getAllineamentiMedi().cbegin();
        it != getModel()->getAllineamentiMedi().cend(); it++){
        getView()->insertAllineamento(it.key(), it.value());
    }
    getView()->applyChartSeries();
}

ScatterChartView *ScatterChartCtrl::getView() const{
    return static_cast<ScatterChartView*>(view);
}

ScatterChartModel *ScatterChartCtrl::getModel() const{
    return static_cast<ScatterChartModel*>(model);
}

void ScatterChartCtrl::onViewClosed() const{delete this;}
