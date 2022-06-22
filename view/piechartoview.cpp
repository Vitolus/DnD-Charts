#include "piechartoview.h"

PieChartOView::PieChartOView(QSize s, View* parent) : PieChartView(s, parent){}

void PieChartOView::insertRazza(const QString& razza, uint occorrenze){
    series->append(razza + tr(" : ") + QString::number(occorrenze), occorrenze);
}

void PieChartOView::applyGraphics(){
    for(QPieSlice* slice : series->slices()){
        slice->setLabelVisible();
        slice->setPen(QPen(Qt::darkGreen, 2));
        slice->setLabelColor(Qt::white);
    }
    chart->setTitle("Occorrenze di scelta");
    series->setLabelsPosition(QPieSlice::LabelInsideHorizontal);
}
