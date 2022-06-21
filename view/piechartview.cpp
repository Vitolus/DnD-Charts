#include "piechartview.h"

void PieChartView::connectViewSignals() const{}

PieChartView::PieChartView(const QSize& size, View *parent) :
     View(size, parent), series(new QPieSeries()), chart(new QChart()){
    QHBoxLayout* mainLayout = new QHBoxLayout;
    chart->addSeries(series);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setTheme(QChart::ChartThemeDark);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setAnimationDuration(1500);
    QChartView* chartView= new QChartView(chart, this);
    chartView->setRenderHint(QPainter::Antialiasing);
    mainLayout->addWidget(chartView);
    setLayout(mainLayout);
    setMinimumSize(800, 500);
    resize(size);
    connectViewSignals();
}

void PieChartView::insertSlice(const QString& slice, uint occorrenze){
    series->append(slice, occorrenze);
}

void PieChartView::applyGraphics(){
    for(QPieSlice* slice : series->slices()){
        slice->setExploded();
        slice->setLabelVisible();
        slice->setPen(QPen(Qt::darkGreen, 2));
        slice->setLabel(slice->label() + tr(" ") +
                        QString::number((slice->percentage()*100), 'f', 1) + " %");
    }
    chart->setTitle("Percentuale di scelta");
}
