#include "scatterchartview.h"

void ScatterChartView::connectViewSignals() const{}

ScatterChartView::ScatterChartView(const QSize &size, View *parent) :
    View(size, parent), chart(new QChart()){

    QHBoxLayout* mainLayout= new QHBoxLayout;
    chart->setTitle("Allineamento medio per classe");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->legend()->setMarkerShape(QLegend::MarkerShapeFromSeries);
    chart->setTheme(QChart::ChartThemeDark);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setAnimationDuration(1500);
    chart->setDropShadowEnabled(false);

    QChartView* chartView= new QChartView(chart, this);
    chartView->setRenderHint(QPainter::Antialiasing);
    mainLayout->addWidget(chartView);
    setLayout(mainLayout);
    setMinimumSize(800, 500);
    resize(size);
    connectViewSignals();
}

void ScatterChartView::insertAllineamento(const QString &classe, const std::pair<uint, uint> allineamento){
    allineamentiSerie.push_back(new QScatterSeries());
    allineamentiSerie.back()->setName(classe);
    allineamentiSerie.back()->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    allineamentiSerie.back()->setMarkerSize(15.0);
    allineamentiSerie.back()->append(allineamento.first, allineamento.second);

}

void ScatterChartView::applyChartSeries(){
    QValueAxis* axisX= new QValueAxis, * axisY= new QValueAxis;
    axisX->setTitleText("<-legale|caotico->");
    axisX->setRange(-5, 5);
    axisX->setMinorGridLineVisible(true);
    chart->addAxis(axisX, Qt::AlignBottom);
    axisY->setTitleText("<-malvagio|buono->");
    axisY->setRange(-5, 5);
    chart->addAxis(axisY, Qt::AlignLeft);

    for(auto a : allineamentiSerie){
        chart->addSeries(a);
        a->attachAxis(axisX);
        a->attachAxis(axisY);
    }
}
