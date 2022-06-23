#ifndef HOMECTRL_H
#define HOMECTRL_H

#include <QFileDialog>
#include <QStringList>
#include <QJsonDocument>
#include "ctrl/ctrl.h"
#include "ctrl/adminctrl.h"
#include "view/homeview.h"
#include "view/adminview.h"

/**
 * @brief HomeCtrl class
 * Classe Derivata da Ctrl, è il Controller specifico per la HomeView
 * Serve a controllare tutto quello che riguarda la schermata Home del programma
 */
class HomeCtrl : public Ctrl{
    Q_OBJECT
private:
    /**
     * @brief connectViewCtrlSignalsSlots Metodo overloading
     * Questo Metodo serve a connettere i SIGNAL della AdminView ai Slot del AdminCtrl
     */
    void connectViewCtrlSignalsSlots() const;

public:
    /**
     * @brief HomeCtrl
     * @param v HomeView collegata al Controller
     * @param parent Controller Padre della schermata che ha invocato la Home
     */
    explicit HomeCtrl(HomeView*, Ctrl* = nullptr);

    /**
     * @brief getView
     * Metodo virtuale che restituisce la View del controller castata al tipo corretto
     * @return VIEW del Controller interpretata come HomeView
     */
    HomeView* getView() const override;

    Model* getModel() const override{return nullptr;}

signals:

public slots:
    /**
     * @brief onNewDungeon SLOT eseguito alla ricezione di SEGNALI di apertura di un nuovo dungeon
     */
    void onNewDungeon() const;
    /**
     * @brief onOpenProject SLOT eseguito alla ricezione di SEGNALI di apertura di un dungeon esistente
     */
    void onOpenDungeon() const;
    /**
     * @brief onViewClosed SLOT eseguito alla ricezione di SEGNALI di chiusura della view
     * Distrugge il Controller, successivamente distrugge la View e il Model
     */
    void onViewClosed() const override;
};

#endif // HOMECTRL_H
