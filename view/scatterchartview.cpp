#include "scatterchartview.h"

void ScatterChartView::connectViewSignals() const{}

ScatterChartView::ScatterChartView(const QSize &size, View *parent) :
    View(size, parent), chart(new QChart()){
    QHBoxLayout* mainLayout= new QHBoxLayout;
    chart->setTitle("Allineamento medio per classe");
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

void ScatterChartView::insertAllineamento(const QString &classe, const std::pair<uint, uint> allineamento){
    QScatterSeries* scatter= new QScatterSeries;
    scatter->setName(classe);
    scatter->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    scatter->setMarkerSize(15.0);
    scatter->append(allineamento.first, allineamento.second);
    allineamentiSerie.push_back(scatter);
}

void ScatterChartView::applyChartSeries(){
    chart->removeAllSeries();
    for(auto a : allineamentiSerie){
        chart->addSeries(a);
    }
    chart->createDefaultAxes();
    if(chart->axisX() && chart->axisY()){
       chart->axisX()->setTitleText("<- Legale | Caotico ->");
       chart->axisY()->setTitleText("<- Malvagio | Buono ->");
    }
}
