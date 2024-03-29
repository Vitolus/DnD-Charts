#include "record.h"

Record::Record(QString r, QString c, QString a, uint l)
    : razza(r), classe(c), allineamento(a), livello(l){}

const QString &Record::getRazza() const{return razza;}
void Record::setRazza(const QString &newRazza){razza = newRazza;}

const QString &Record::getClasse() const{return classe;}
void Record::setClasse(const QString &newClasse){classe = newClasse;}

const QString &Record::getAllineamento() const{return allineamento;}
void Record::setAllineamento(const QString &newAllineamento){allineamento = newAllineamento;}

uint Record::getLivello() const{return livello;}
void Record::setLivello(uint newLivello){livello = newLivello;}
