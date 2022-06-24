#include "view/homeview.h"

HomeView::HomeView(const QSize& s, View* parent) : View(s, parent){
    QHBoxLayout* mainLayout= new QHBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    mainLayout->addLayout(createButtonsLayout());
    mainLayout->addLayout(createDescriptionLayout(tr(
    "Dungeons & Data è un programma di statistica utile a mostrare\n"
    "alcune preferenze dei giocatori di D&D.\n"
    "Si tiene traccia di alcune informazioni di ogni personaggio:\n"
    "- Razza\n"
    "- Classe\n"
    "- Allineamento\n"
    "- Livello\n"
    "\n"
    "Questo programma, offre dei grafici utili ad esaminare informazioni\n")));
    setLayout(mainLayout);
    connectViewSignals();
}

QLayout* HomeView::createButtonsLayout(){
    QVBoxLayout* buttonsLayout= new QVBoxLayout;
    buttonsLayout->setMargin(10);
    buttonsLayout->setSpacing(50);
    buttonsLayout->setContentsMargins(25, 50, 12, 50);
    buttonsLayout->setAlignment(Qt::AlignCenter);

    newButton= new QPushButton("New", this);
    openButton= new QPushButton("Open", this);
    newButton->setFixedSize(150, 70);
    openButton->setFixedSize(150, 70);

    buttonsLayout->addWidget(newButton);
    buttonsLayout->addWidget(openButton);
    return buttonsLayout;
}

QLayout* HomeView::createDescriptionLayout(const QString& description){
    QVBoxLayout* descrLayout= new QVBoxLayout;
    QLabel* desc= new QLabel(description, this);
    QFont f("Calibri", 9);
    desc->setFont(f);
    descrLayout->addWidget(desc, Qt::AlignJustify);

    QHBoxLayout* groupLayout= new QHBoxLayout;
    groupLayout->setMargin(10);
    groupLayout->setSpacing(25);
    groupLayout->setContentsMargins(12, 50, 25, 50);
    QGroupBox* group= new QGroupBox("Descrizione Programma", this);
    group->setLayout(descrLayout);
    groupLayout->addWidget(group);
    return groupLayout;
}

void HomeView::connectViewSignals() const{
    connect(newButton, SIGNAL(clicked()), this, SIGNAL(newDungeon()));
    connect(openButton, SIGNAL(clicked()), this, SIGNAL(openDungeon()));
}


void HomeView::closeEvent(QCloseEvent* event){
    if(!event->spontaneous()) return;
    if(!showQuestionDialog(2, "Exit", "Chiudere l'applicazione?\n"))
        event->ignore();
    else{
        event->accept();
        emit viewClosed();
    }
}



