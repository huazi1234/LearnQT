#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QMenuBar>
#include "logichandle.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
private slots:
    void choosebtn();
    void OnSetSize();
private:
    void InitUI();
    void TestLayout();
public:
    void SetSize(int nSize);

    void DisplayLayout();
private:
    Ui::Dialog *ui;

    int m_nSize;
    LogicHandle lay;
    QGridLayout *pLayout;

    typedef QVector<QPushButton*> btnVec;
    QVector<btnVec> m_vecBtnLayout;

    QVBoxLayout* layout;
    QMenuBar* menuBar;
    QAction* actionSize;

};
#endif // DIALOG_H
