#ifndef EXPEVALUATOR_H
#define EXPEVALUATOR_H

#include <QMap>
#include <QPair>
#include <QStack>
#include <QString>
#include <QList>
#include <cmath>
#include <QMessageBox>

/* Class expEvaluator
 *- - - - - - - - - - - - - - - -
 * Takes input from lexer and stores a list of lexems into a list called lexems.
 *Iterates over a list of lexems and performs shunting yard algorithm to calculate the result.
 *Shunting yard algorithm assigns to each operator precedence and associativity.
 * Precedence list is given as:
 *operator	precedence	associativity (left 0 right 1)
    *       ^                  4	            1
    *       *                  3           	0
    *       /                   3             0
    *       +                  2             0
    *       -                   2             0
    * Shunting yard converts infix mathematical expression into postfix mathematical notation
    *which is easier for a computer to evaluate.
    *Using stacks the postfix expression evaluates a result of calculation
 */

class expEvaluator
{
public:

    expEvaluator():LEFT_ASSOC(0),RIGHT_ASSOC(1)
    {
        precedence["^"]=QPair<int,int>(4,RIGHT_ASSOC);
        precedence["*"]=QPair<int,int>(3,LEFT_ASSOC);
        precedence["/"]=QPair<int,int>(3,LEFT_ASSOC);
        precedence["+"]=QPair<int,int> (2,LEFT_ASSOC);
        precedence["-"]=QPair<int,int>(2,LEFT_ASSOC);
    }

    /*Method: setLexems(QString lexemValue)
     *Usage:  expEvaluator userExp;
     *              userExp.getLexem(int lexemIndex)
     *- - - - - - - - - - - - - - - - - - - - - - - - - - - - -
     *Appends given lexem to a list of lexems
     *Used as mutator method for other objects to change the internal data of class
     */
    void setLexems(QString lexemValue);

    /*Method: getLexem(int lexemIndex)
     *Usage:  expEvaluator userExp;
     *              userExp.getLexem(int lexemIndex)
     *- - - - - - - - - - - - - - - - - - - - - - - - - - - - -
     *Returns lexem specified by index from a list of lexems
     *Used as accessor method for other objects to access the internal data of class
     */

    QString getLexem(int lexemIndex);

    /*Method: void removeLexem()
     *Usage:  expEvaluator userExp;
     *              userExp.removeLexem();
     *- - - - - - - - - - - - - - - - - - - - - - - - - - - - -
     *Removes first lexem from a list of lexems
     */

    void removeLexem();


    /*Method: evaluateExpression()
     *Usage:  expEvaluator userExp;
     *              userExp.evaluateExpression();
     *- - - - - - - - - - - - - - - - - - - - - - - - - - - - -
     *Evaluates a mathematical expression using Shunting yard algorithm.
     *User input is splitted into lexems which are stored in a list called lexems.
     *Method uses data from  list lexems to perform calculation.
     */
    double evaluateExpression();


    /*Method: isOperator(QString userExpression)
     *Usage:  isOperator(QString)
     *- - - - - - - - - - - - - - - - - - - - - - - - - - - - -
     * Used as a helper method for method evaluateExpression().
     *Checks is a current lexem one of operators
     */

    bool isOperator(QString userExpression);

    /*Method: toRadians(double degrees)
     *Usage:  toRadians(double)
     *- - - - - - - - - - - - - - - - - - - - - - - - - - - - -
     * Used as a helper method for method evaluateExpression().
     *By default sin and cos functions takes radians as arguments
     *Using toRadians user can write expression in degrees which is then
     *converted to radians.
     *Example: toRadians(5)
     */

    double toRadians(double degrees);


    /*Method: isFunction(QString userExpression)
     *Usage:  isFunction(QString)
     *- - - - - - - - - - - - - - - - - - - - - - - - - - - - -
     * Used as a helper method for method evaluateExpression().
     *Checks is a current lexem one of defined functions:sin,cos...
     */

    bool isFunction(QString userExpression);

private:

    /*Shunting yard algorithm assigns each lexem precedence (integer from 2 to 4) and associativity (0 is left associativity 1 is right associativity)*/
    const int LEFT_ASSOC;
    const int RIGHT_ASSOC;

    /* Stores precedence and associativity as a pair of values*/
    QPair <int,int> operatorPrecedence;

    /* Maps each operator to its precedence and associativity. For example: '*':(3,1) where 1 is associativity */
    QMap <QString,QPair <int,int> > precedence;

    /* Stack data type is used for operators and operands to perform shunting yard algorithm*/
    QStack <QString> stack;

    /* Used to store input in reverse polish notation*/
    QList <QString> output;

    /* List of lexems formed from user input */
    QList <QString> lexems;

};

#endif // EXPEVALUATOR_H
