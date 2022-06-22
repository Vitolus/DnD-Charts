#include "piechartctrl.h"

PieChartCtrl::PieChartCtrl(PieChartView* v, PieChartModel* m, Ctrl* parent) :
    Ctrl(v, m, parent){

    for(QMap<QString, uint>::const_iterator it= getModel()->getRazzeOccurrences().cbegin();
        it != getModel()->getRazzeOccurrences().cend(); it++){
        getView()->insertRazza(it.key(), it.value());
    }
    getView()->applyGraphics();
}

PieChartView *PieChartCtrl::getView() const{
    return static_cast<PieChartView*>(view);
}

PieChartModel *PieChartCtrl::getModel() const{
    return static_cast<PieChartModel*>(model);
}

void PieChartCtrl::onViewClosed() const{delete this;}
