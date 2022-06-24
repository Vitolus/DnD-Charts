#include "barchartctrl.h"

BarChartCtrl::BarChartCtrl(BarChartView* v, BarChartModel* m, Ctrl* parent) :
    Ctrl(v, m, parent){
    for(QMap<QString, uint>::const_iterator it= getModel()->getLivelliMedi().cbegin();
        it != getModel()->getLivelliMedi().cend(); it++){
        getView()->insertSetClasse(it.key(), it.value());
    }
    getView()->applySetsOnChart();
}

BarChartView *BarChartCtrl::getView() const{
    return static_cast<BarChartView*>(view);
}

BarChartModel *BarChartCtrl::getModel() const{
    return static_cast<BarChartModel*>(model);
}

void BarChartCtrl::onViewClosed() const{delete this;}
