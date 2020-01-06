#include "dialog.h"
#include "ui_dialog.h"
#include "CConfigHandle.h"
#include "SizeSetting.h"
#include <QDebug>
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    InitUI();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::SetSize(int nSize)
{
    m_nSize = nSize;
}
void Dialog::InitUI()
{
    CConfigHandle handle;
    handle.LoadData();
    resize(500,500);
    SetSize(handle.GetSize());

    //layout = new QVBoxLayout(this);
    menuBar = new QMenuBar(this);
    menuBar->setGeometry(QRect(0, 0, 400, 24));
    QMenu* menuSetting = menuBar->addMenu(tr("&Setting"));
    actionSize = menuSetting->addAction(tr("&Size"));
    //actionNew->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));

    //layout->setMenuBar(menuBar);
    //setLayout(layout);

    //LogicHandle lay;
    lay.Init(m_nSize);

    QGridLayout *pLayout = new QGridLayout(this);
    for(int i = 0;i < m_nSize;i++)
    {
        btnVec vec;
        vec.resize(m_nSize);
        m_vecBtnLayout.push_back(vec);
    }
//    pLayout->setHorizontalSpacing(0);
//    pLayout->setVerticalSpacing(0);
    for(int i = 0;i < m_nSize;i++)
    {
        btnVec vec;
        vec.resize(m_nSize);
        for(int j = 0;j < m_nSize;j++)
        {
            quint8 nValue = 0;
            m_vecBtnLayout[i][j] = new QPushButton(QString("%1").arg(nValue));
            m_vecBtnLayout[i][j]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
            pLayout->addWidget(m_vecBtnLayout[i][j], i, j);
            connect(m_vecBtnLayout[i][j], SIGNAL(clicked()), this, SLOT(choosebtn()));
        }
    }
    pLayout->setMenuBar(menuBar);

    connect(actionSize, SIGNAL(triggered()), this, SLOT(OnSetSize()));

    setLayout(pLayout);
    DisplayLayout();



}
void Dialog::DisplayLayout()
{
    for(quint8 i = 0;i < m_nSize;i++)
    {
        for(quint8 j = 0;j < m_nSize;j++)
        {
            quint8 nValue = 0;
            lay.GetLayoutValue(i,j,nValue);
            m_vecBtnLayout[i][j]->setText(QString("%1").arg(nValue));
            if(nValue == 0)
            {
                m_vecBtnLayout[i][j]->hide();
            }
            else
            {
               m_vecBtnLayout[i][j]->show();
            }
        }
    }
}

void Dialog::TestLayout()
{
//    LogicHandle lay;
//    lay.Init(4);
//    lay.PrintLayOut();
}

void Dialog::choosebtn()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    QString strText = btn->text();
    if(strText.toUInt() == 0)
    {
        return;
    }
    QPoint pos;
    lay.GetLayoutValuePos(strText,pos);
    if(lay.CanMove(pos) == true)
    {
        lay.Move(pos);
        DisplayLayout();
    }
    lay.GetLayoutValuePos(strText,pos);
    m_vecBtnLayout[pos.x()][pos.y()]->setFocus();
}

void Dialog::OnSetSize()
{
    //设置值到INI里
    SizeSetting* childDialog = new SizeSetting(this);
    int resutl = childDialog ->exec();
    if (resutl == QDialog::Accepted)
    {
        qDebug() << "You Choose Ok";
    }
    else
    {
        qDebug() << "You Choose Cancel";
    }

}



