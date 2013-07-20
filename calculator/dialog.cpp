/*File:dialog.cpp
 *- - - - - - - - - - -
 *Description: Implemenation of graphical user interface in Qt framework
 */

#include "dialog.h"
#include "lexer.h"
#include "expevaluator.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QKeyEvent>


Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{

    QVBoxLayout* mainLayout=new QVBoxLayout(this);
    QHBoxLayout* buttonLayout=new QHBoxLayout;
    QPushButton* clearButton=new QPushButton(tr("Clear"));
    QPushButton* quitButton=new QPushButton(tr("Quit"));

    expressionOutput=new QTextEdit;

    // user can't modify output
    expressionOutput->setReadOnly(true);


    expressionInput=new QLineEdit(tr("4+5-1*2"));

    // adds widgets to the layout
    mainLayout->addWidget(expressionOutput);
    mainLayout->addWidget(expressionInput);
    mainLayout->addLayout(buttonLayout);

    // moves buttons to the right side
    buttonLayout->addStretch();

    // adds buttons to the buttonLayout
    buttonLayout->addWidget(clearButton);
    buttonLayout->addWidget(quitButton);

    // handles quitButton click
    connect(quitButton,SIGNAL (clicked()),this, SLOT(accept()));
    connect(clearButton,SIGNAL(clicked()),this,SLOT(clearOutput()));

}

Dialog::~Dialog()
{

}

// handles enter key press event
void Dialog::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return){

        QString expression=expressionInput->text();

        int leftParenthesis=0;
        int rightParenthesis=0;
        leftParenthesis=expression.count("(");
        rightParenthesis=expression.count(")");

        userVariables.insert("pi",3.14);
        userVariables.insert("e",2.718);

        if (leftParenthesis!=rightParenthesis) {
            QMessageBox mBox;
            mBox.setText("Parenthesis missmatch!");
            mBox.exec();

        } else {

            QString lexem;
            Lexer lexer(expressionInput->text());
            expEvaluator userExp;


            while(lexer.hasMoreLexems()) {

                lexem=lexer.nextLexem();

                if (userVariables.contains(lexem))
                    userExp.setLexems(QString::number(userVariables.value(lexem)));
                else
                    userExp.setLexems(lexem);

            }

            if (userExp.getLexem(1)=="=")

            {
                QString variableName;
                double variableValue;

                variableName=userExp.getLexem(0);

                userExp.removeLexem();
                userExp.removeLexem();

                variableValue=userExp.evaluateExpression();

                userVariables.insert(variableName,variableValue);

            }

            QString answer=QString::number(userExp.evaluateExpression());
            expressionOutput->append(answer);


        }



    }
}

// handles clear button click
void Dialog::clearOutput() {
    expressionOutput->clear();
}

