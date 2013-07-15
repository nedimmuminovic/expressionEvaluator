#ifndef LEXER_H
#define LEXER_H
#include <QString>
#include <QMessageBox>

class Lexer
{
public:
    Lexer(QString expression);
    bool hasMoreTokens();
    QString nextToken();

    QString getTokenType(QString);


private:
    int expressionIndex;
    QString expression;

};

#endif // LEXER_H
