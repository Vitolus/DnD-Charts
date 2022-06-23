#include "ctrl/homectrl.h"
#include <QSize>
#include <QApplication>

int main(int argc, char* argv[]){
    QApplication a(argc, argv);
    HomeView* homeView= new HomeView();
    HomeCtrl* homeCtrl= new HomeCtrl(homeView);
    homeCtrl->showView();
    return a.exec();
}
