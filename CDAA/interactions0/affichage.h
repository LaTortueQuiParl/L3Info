#include <QObject>
#include <QWidget>
#include <QTextEdit>
#include <QLCDNumber>
#include <QHBoxLayout>
#include <QLCDNumber>

class Affichage : public QWidget
{
    Q_OBJECT
public :
    explicit Affichage ( QWidget * parent = nullptr ) ;
    QTextEdit * zoneTexte ;
    QLCDNumber * LCDnbEvents ;
    QHBoxLayout * Hlayout;
    int nbEvents ;

signals :
    void LCDupdate(int);
    void textAppend(QString);

public slots :
    void recvData(QString);
};
