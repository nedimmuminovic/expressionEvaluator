#include <QString>
#include <QtTest>
#include "../expressionEvaluator/expevaluator.cpp"
#include "../expressionEvaluator/lexer.cpp"

class ExpressionTest : public QObject
{
    Q_OBJECT
    
public:
    ExpressionTest();
    
private Q_SLOTS:
    void testCase1();
};

ExpressionTest::ExpressionTest()
{

}

void ExpressionTest::testCase1()
{
    QString lexem;

    Lexer lexer("1.5-0.5");
    expEvaluator expEval;

   while(lexer.hasMoreLexems()) {

        lexem=lexer.nextLexem();
        expEval.setLexems(lexem);


   } //end of while

    QVERIFY(expEval.evaluateExpression()==1.0);

}

QTEST_APPLESS_MAIN(ExpressionTest)

#include "tst_expressiontest.moc"
