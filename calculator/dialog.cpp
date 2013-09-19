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

    userVariables.insert("pi",3.14);
    userVariables.insert("e",2.718);

    QVBoxLayout* mainLayout=new QVBoxLayout(this);
    QHBoxLayout* buttonLayout=new QHBoxLayout;
    QPushButton* clearButton=new QPushButton(tr("Clear"));
    QPushButton* quitButton=new QPushButton(tr("Quit"));

    expressionOutput=new QTextEdit;

    // user can't modify output
    expressionOutput->setReadOnly(true);
    expressionOutput->setText("Usage examples\n"
                              "a=10 \n"
                              "a+5*2 \n"
                              "a^2 \n"
                              "sin(cos(1)) \n"
                              "sin(cos(0.5+3)) \n"
                              "1.25+1.5*3+1 \n"
                              "-1-5-6 \n"
                              "sqrt(9) \n"
                              "log(10)\n"
                              "sin(toRadians(30)) \n"
                              "pi+3^2\n"
                              "1+e"
                              );


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
    if (event->key() == Qt::Key_Return)
        showResult();

}

// handles clear button click
void Dialog::clearOutput() {
    expressionOutput->clear();
}

void Dialog::showResult() {

    QString lexem;
    Lexer lexer(expressionInput->text());
    expEvaluator userExp;
    QString userInput = expressionInput->text();
   bool parenthesis=userExp.parenthesisCheck(expressionInput->text());

   if (userInput.count("=") > 1){
       QMessageBox mBox;
       mBox.setText("Found multiple = signs. Please use only one!");
       mBox.exec();

   } else if (parenthesis) {

       while(lexer.hasMoreLexems()) {

           lexem=lexer.nextLexem();

           if (userVariables.contains(lexem) && !userInput.contains("="))
               userExp.setLexems(QString::number(userVariables.value(lexem)));
           else
               userExp.setLexems(lexem);

       }

       double result = 0;

       QString variableName="";

       if (userExp.lexems.length() > 1 && userExp.lexems[1] == "=") {

           variableName = userExp.lexems[0];
           userExp.lexems.removeFirst();

           userExp.lexems.removeFirst();

           result = userExp.evaluateExpression();
           userVariables.insert(variableName, result);

       }

       else

           result = userExp.evaluateExpression();


       QString answer=QString::number(result);
       expressionOutput->append(variableName+"="+answer);

   }

}

