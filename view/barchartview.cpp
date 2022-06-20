#include "barchartview.h"

void BarChartView::connectViewSignals() const{}

BarChartView::BarChartView(const QSize& size, View* parent) :
    View(size, parent), chart(new QChart()), series(new QBarSeries()),
    chartScroll(new QScrollBar(Qt::Horizontal,this)){
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
    mainLayout->addWidget(chartScroll);
    setLayout(mainLayout);
    setMinimumSize(800, 500);
    resize(size);
    connectViewSignals();
}

void BarChartView::insertSetClasse(const QString &classe, uint livelloMedio){
    QBarSet* set= new QBarSet(classe);
            *set << livelloMedio;
        listaSetClassi.push_back(set);
}

void BarChartView::applySetsOnChart(){
    for(auto s : listaSetClassi)
        series->append(s);
    chart->addSeries(series);
}

void BarChartView::applyAxis(const QStringList &classi, const uint maxY){
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(classi);
    //Set range per il grafico, massimo 7 classi mostrate per volta
    //Se il numero di classi disponibili è più grande di 7 imposto un range dalla prima alla 7 classe
    //Se il numero di classi disponibile è più piccolo di 7 imposto un range dalla prima all'ultima
    axisX->setRange(classi.at(0), (classi.length()>maxVisClassi)? classi.at(maxVisClassi-1) : classi.last());
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    QValueAxis *axisY= new QValueAxis();
    axisY->setRange(0, maxY);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    if(chart->axisX() && chart->axisY()){
       chart->axisX()->setTitleText("Classi");
       chart->axisY()->setTitleText("Livello");
    }
    //Scrolling
    //Imposto il range della scrllbar da 0 al classi.lenght - maxVisClassi
    //il range finisce a mesiA.lenght - mesiVisibili perchè così
    //posso mostrare da v a v+mesivisibili
    chartScroll->setRange(0, classi.length()-maxVisClassi);
    //Creo una connessione per la scrollbar in maniera che al variare del suo valore
    //mostro sul cahrt a partire da valore selezionato a + classi visibili
    int max = maxVisClassi;
    connect(chartScroll, &QAbstractSlider::valueChanged, this, [max, classi, this](int v){
        chart->axisX()->setRange(classi.at(v),classi.at(v+(max-1)));
    });
}


