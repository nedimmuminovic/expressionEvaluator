#ifndef EXPEVALUATOR_H
#define EXPEVALUATOR_H

#include <QMap>
#include <QPair>
#include <QStack>
#include <QString>
#include <QList>
#include <QMessageBox>
#include <cmath>

class expEvaluator
{
public:

    // constructor initilization list is used when there are const variables
    expEvaluator():LEFT_ASSOC(0),RIGHT_ASSOC(1)
    {
        precedence["^"]=QPair<int,int>(4,RIGHT_ASSOC);
        precedence["*"]=QPair<int,int>(3,LEFT_ASSOC);
        precedence["/"]=QPair<int,int>(3,LEFT_ASSOC);
        precedence["+"]=QPair<int,int> (2,LEFT_ASSOC);
        precedence["-"]=QPair<int,int>(2,LEFT_ASSOC);
    }

    //setter
    void setLexems(QString lexemValue);

    //getter
    QString getLexem(int lexemIndex);

    //removes first element
    void removeLexem();

    double evaluateExpression();
    double evaluateVariables(QString userExpression);
    bool isOperator(QString userExpression);

     bool getAssociativity(QString userExpression);


private:

    const int LEFT_ASSOC;
    const int RIGHT_ASSOC;

    QPair <int,int> operatorPrecedence;
    QMap <QString,QPair <int,int> > precedence;
    QStack <QString> stack;
    //QList <QString> result;
    QList <QString> output;
    QList <QString> lexems;

};

#endif // EXPEVALUATOR_H
