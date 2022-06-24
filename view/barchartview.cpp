#include "barchartview.h"

void BarChartView::connectViewSignals() const{}

BarChartView::BarChartView(const QSize& size, View* parent) : View(size, parent), chart(new QChart()), series(new QBarSeries()){

    chart->setTheme(QChart::ChartThemeDark);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setAnimationDuration(1500);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setTitle("Livello medio per classe");
    QChartView* chartView= new QChartView(chart, this);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout* mainLayout= new QVBoxLayout;
    mainLayout->addWidget(chartView);
    setLayout(mainLayout);
    setMinimumSize(800, 500);
    resize(size);
    connectViewSignals();
}

void BarChartView::insertSetClasse(const QString& classe, uint livelloM){
    listaSetClassi.push_back(new QBarSet(classe));
    listaSetClassi.back()->append(livelloM);
}

void BarChartView::applySetsOnChart(){
    series->append(listaSetClassi);
    chart->addSeries(series);
    QValueAxis* axisY= new QValueAxis;
    axisY->setRange(0, 20);
    chart->addAxis(axisY, Qt::AlignLeft);
}

