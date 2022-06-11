#ifndef RECORD_H
#define RECORD_H

#include <QString>
#include <QDate>

class Record{
    QString razza;
    QString classe;
    QString allineamento;
    unsigned int livello;
public:
    /**
     * @brief Record Costruttore
     * @param r Razza
     * @param c classe
     * @param a allineamento
     * @param l livello
     */
    explicit Record(QString r, QString c,QString a, unsigned int l);
    const QString &getRazza() const;
    void setRazza(const QString &newRazza);
    const QString &getClasse() const;
    void setClasse(const QString &newClasse);
    const QString &getAllineamento() const;
    void setAllineamento(const QString &newAllineamento);
    unsigned int getLivello() const;
    void setLivello(unsigned int newLivello);
};
#endif // RECORD_H
