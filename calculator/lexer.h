#ifndef LEXER_H
#define LEXER_H
#include <QString>
//#include <QMessageBox>

/* Class Lexer
 *- - - - - - - - - -
 * Takes input from user and splits input into logical units called lexems.
 *Uses index based splitting.
 */

class Lexer
{
public:

    /* Constructor: Lexer
     *Usage: Lexer lexer(str);
     *- - - - - - - - - - - - - - - - - - - - -
     * Initializes a lexer object. Lexer stream comes from string str
     */

    Lexer(const QString  &expression);

    /*Method: hasMoreLexems()
     *Usage: if(lexer.hasMoreLexems) . . .
     *- - - - - - - - - - - - - - - - - - - - - - - - - - - - -
     *Returns true if there is more operators and operands left to read
     */

    bool hasMoreLexems();

    /* Function: nextLexem()
     *Usage:  lexer.nextLexem();
     * - - - - - - - - - - - - - - - - - - - - -
     *Returns the nextLexem from a stream.
     *Additionaly removes space from user input and handles unary - by adding 0 in front of (-number) and at index 0
     *in case -number-number
     */
    QString nextLexem();

private:
    int expressionIndex;
    QString expression;

};

#endif // LEXER_H
