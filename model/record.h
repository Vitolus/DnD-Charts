#ifndef RECORD_H
#define RECORD_H

#include <QString>

class Record{
    QString razza;
    QString classe;
    QString allineamento;
    uint livello;
public:
    /**
     * @brief Record Costruttore
     * @param r Razza
     * @param c classe
     * @param a allineamento
     * @param l livello
     */
    explicit Record(QString, QString, QString, uint);

    const QString &getRazza() const;
    void setRazza(const QString &newRazza);

    const QString &getClasse() const;
    void setClasse(const QString &newClasse);

    const QString &getAllineamento() const;
    void setAllineamento(const QString &newAllineamento);

    uint getLivello() const;
    void setLivello(uint newLivello);
};
#endif // RECORD_H
