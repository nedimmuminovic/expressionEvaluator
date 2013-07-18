/*File:lexer.cpp
 *- - - - - - - - - - -
 *Description: Implements the lexer used for extracting operands and operators from a string
 */

#include "lexer.h"

Lexer::Lexer(QString expression)
{
    expressionIndex=0;
    this->expression=expression;
}

bool Lexer::hasMoreLexems()
{
    return expressionIndex < expression.length();

}

QString Lexer::nextLexem()
{
    /* remove space from user input*/
    expression=expression.simplified();
    expression.replace(" ","");

    /* handles unary minus*/
    expression=expression.replace("(-","(0-");

    /*handles unary minus at the begginig of expression by adding 0*/
    if (expression.indexOf("-")==0)
        expression="0"+expression;

    QChar character=expression[expressionIndex];


    if (expressionIndex >= expression.length())
        return "";

    else if (character.isLetterOrNumber()) {

        int startIndex=expressionIndex;

        while(expressionIndex < expression.length() && (character.isLetterOrNumber() || character=='.')) {

            expressionIndex++;
            character=expression[expressionIndex];
        }

        return expression.mid(startIndex,expressionIndex-startIndex);
    }

    else
        return QString(1,expression[expressionIndex++]);


}


