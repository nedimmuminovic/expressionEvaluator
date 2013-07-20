#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMap>
#include <QMessageBox>

//forward declaration
class QLineEdit;
class QTextEdit;
class QPushButton;

class Dialog : public QDialog
{
    Q_OBJECT
    
public:

    Dialog(QWidget *parent = 0);
    ~Dialog();


private:

    QPushButton* clearButton;
    QLineEdit* expressionInput;
    QTextEdit* expressionOutput;
    QMap <QString,double> userVariables;


protected:
    void keyPressEvent(QKeyEvent * e);
private slots:
    void clearOutput();
};

#endif // DIALOG_H
