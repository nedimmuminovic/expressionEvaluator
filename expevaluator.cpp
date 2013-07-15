#include "expevaluator.h"

/*
            QMessageBox mBox;

            mBox.setText(userLexem);
            mBox.exec();
*/

 QString expEvaluator::getLexem(int lexemIndex){
    return lexems.at(lexemIndex);
 }

 void expEvaluator::removeLexem(){
    lexems.removeFirst();
 }

bool expEvaluator::isOperator(QString userExpression) {
    return userExpression=="+" || userExpression=="-" || userExpression=="*"
            || userExpression=="/" || userExpression=="^";
}


 void expEvaluator::setLexems(QString lexemValue) {
    lexems.append(lexemValue);
 }

double expEvaluator::evaluateExpression() {


    double answer=0.0;
    QString userLexem;

    int  lexemPrecedence=0;
    int lexemAssociativity=0;

    if (lexems.length()==1)
        return lexems.at(0).toDouble();

        for (int i = 0; i < lexems.size(); ++i) {

            userLexem=lexems.at(i);
            lexemPrecedence=precedence.value(userLexem).first;
            lexemAssociativity=precedence.value(userLexem).second;


            if (userLexem.at(0).isDigit())
                output.append(userLexem);

            if (userLexem=="sin")
                 stack.push(userLexem);

            if (userLexem=="cos")
                stack.push(userLexem);

            if (isOperator(userLexem)) {

                while ( !stack.empty() && isOperator(stack.top() ) )
                {

                    if (
                            (lexemAssociativity==LEFT_ASSOC &&
                             lexemPrecedence <= precedence.value(stack.top()).first)

                            ||

                            ( lexemAssociativity==RIGHT_ASSOC &&
                              lexemPrecedence < precedence.value(stack.top()).first)
                            ) {


                        output.append(stack.pop());
                        continue;

                    } //end if

                    break;

                } // end while

                stack.push(userLexem);

            } //end of outer if

            if (userLexem=="("){
                stack.push(userLexem);
            }

            if (userLexem==")") {

                while (!stack.empty()  && stack.top() != "(")
                    output.append(stack.pop());

                stack.pop();

            }

        } // end for

        while(!stack.empty() && stack.top() != "(" ) {
            output.append(stack.pop());

        }

        QString lexem;

    // calculate reverse polish notation
    for (int i = 0; i < output.size(); ++i) {

         lexem=output.at(i);
        //double result=0.0;
        if (output.at(i).at(0).isDigit())
            stack.push(output.at(i));

        if (isOperator(output.at(i))) {
            double secondOperand;
            double firstOperand;
            secondOperand=stack.pop().toDouble();
            firstOperand=stack.pop().toDouble();

            if (lexem=="+") {
                answer=firstOperand+secondOperand;
                stack.push(QString::number(answer));
            }

            if (lexem=="*") {
                answer=firstOperand*secondOperand;
                stack.push(QString::number(answer));
            }

            if (lexem=="/") {
                answer=firstOperand*secondOperand;
                stack.push(QString::number(answer));
            }

            if (lexem=="-") {
                answer=firstOperand-secondOperand;
                stack.push(QString::number(answer));
            }

            if (lexem=="^") {
                answer=pow(firstOperand,secondOperand);
                stack.push(QString::number(answer));
            }


            } // end if operator

        if (lexem=="sin") {
            double result=0.0;
            result=stack.pop().toDouble();
            answer=sin(result);
            stack.push(QString::number(answer));

        }

        if (lexem=="cos") {
            double result=0.0;
            result=stack.pop().toDouble();
            answer=cos(result);
            stack.push(QString::number(answer));

        }


    }
    // removes all lexems
    lexems.clear();

    return answer;
} // method end
