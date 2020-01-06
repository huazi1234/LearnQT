#ifndef LOGICHANDLE_H
#define LOGICHANDLE_H

#include <QVector>
#include <QPoint>
class LogicHandle
{
public:
    LogicHandle();


private:
    int m_nSize;

    typedef QVector<quint8> ivec;

    QVector<ivec> m_vecLayout;
    QVector<ivec> m_vecResLayout;


public:
    void SetSize(int nSize);
    int GetSize();

    void AllocVec2D();
    void GenResVec2D();

    bool SetValue(QPoint pos,quint8 nValue);

    bool Move(QPoint pos);
    bool CanMove(QPoint pos);
    bool IsDone();

    bool GetSpacePos(QPoint& pt);

    bool GenInitLayOut();
    bool IsCanSolve();
    void PrintLayOut();

    bool Init(int nSize);
    bool GetLayoutValuePos(QString strText,QPoint& pt);
    bool GetLayoutValue(quint8 x,quint8 y,quint8 & nValue);

    void GetLayOutList(ivec& vecCur);
    void GetResList(ivec& vecCur);
    void GetList(QVector<ivec>& vecGrid, ivec& vecCur);
    //计算序列的逆序数
    int CalcReverseCount(ivec& vecCur);

    void ClearLayOut();
    bool InitLayout();
};

#endif // LOGICHANDLE_H
