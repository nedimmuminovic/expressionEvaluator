#include <QString>
#include <QtTest>
#include "../expressionEvaluator/lexer.cpp"
#include "../expressionEvaluator/expEvaluator.cpp"


class ExpressionTest : public QObject
{
    Q_OBJECT
    
public:
    ExpressionTest();
    
private Q_SLOTS:
     void storeLexems(Lexer &lexer, expEvaluator &expEval);
    void testCase1();

};

ExpressionTest::ExpressionTest()
{

}

void ExpressionTest::storeLexems(Lexer &lexer,expEvaluator &expEval){

 QString lexem;
while(lexer.hasMoreLexems()) {

     lexem=lexer.nextLexem();
     expEval.setLexems(lexem);


} //end of while

}

void ExpressionTest::testCase1()
{

    Lexer *lexer=new Lexer("1.5-0.5");
    expEvaluator *expEval=new expEvaluator;
    storeLexems(*lexer,*expEval);
    QVERIFY(expEval->evaluateExpression()==1.0);
    delete lexer;

    lexer=new Lexer("6");
    storeLexems(*lexer,*expEval);
    QVERIFY(expEval->evaluateExpression()==6.0);
    delete lexer;

    lexer=new Lexer("6+3-1/2*2^2");
    storeLexems(*lexer,*expEval);
    QVERIFY(expEval->evaluateExpression()==7.0);
    delete lexer;

    lexer=new Lexer("-1-2-3");
    storeLexems(*lexer,*expEval);
    QVERIFY(expEval->evaluateExpression()==-6.0);
    delete lexer;

    lexer=new Lexer("sqrt(9)+sqrt(10)");
    storeLexems(*lexer,*expEval);
    QVERIFY(expEval->evaluateExpression()==6.16228);
    delete lexer;

    lexer=new Lexer("1.5+2.5/3*6-6");
    storeLexems(*lexer,*expEval);
    QVERIFY(expEval->evaluateExpression()==0.5);
    delete lexer;

    lexer=new Lexer("8-(-3-4)");
    storeLexems(*lexer,*expEval);
    QVERIFY(expEval->evaluateExpression()==15);
    delete lexer;

    lexer=new Lexer("15*(-2)");
    storeLexems(*lexer,*expEval);
    QVERIFY(expEval->evaluateExpression()==-30);
    delete lexer;

    delete expEval;


}

QTEST_APPLESS_MAIN(ExpressionTest)

#include "tst_expressiontest.moc"
