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


    wordList << "sin(" << "cos(" << "sqrt(" << "log("<< "toRadians(";
    completer=new QCompleter(wordList,this);

    completer->setCaseSensitivity(Qt::CaseInsensitive);
    expressionInput->setCompleter(completer);

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

// destructor
Dialog::~Dialog()
{

}





// handles enter key press event
void Dialog::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return){

        userVariables.insert("pi",3.14);
        userVariables.insert("e",2.718);

        QString lexem;
        bool parenthesis;
        Lexer lexer(expressionInput->text());
        expEvaluator userExp;

        parenthesis=userExp.parenthesisCheck(expressionInput->text());

        if (parenthesis) {

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

                //expressionOutput->append(variableName+"="+variableValue);

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

