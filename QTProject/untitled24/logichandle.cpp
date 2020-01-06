#include "logichandle.h"
#include <QTime>
#include <QDebug>
LogicHandle::LogicHandle()
{

}


void LogicHandle::SetSize(int nSize)
{
    m_nSize = nSize;
}

int LogicHandle::GetSize()
{
    return m_nSize;
}

void LogicHandle::AllocVec2D()
{
    if(m_nSize <= 0)
    {
        return;
    }
    //m_vecLayout.resize(m_nSize);
    for(int i = 0;i < m_nSize;i++)
    {
        ivec vecTemp;
        vecTemp.resize(m_nSize);
        for(int j = 0;j < m_nSize;j++)
        {
            vecTemp[j] = 0;
        }
        m_vecLayout.push_back(vecTemp);
    }
}

void LogicHandle::GenResVec2D()
{
    if(m_nSize <= 0)
    {
        return;
    }
    quint8 nValue = 1;
    //m_vecResLayout.resize(m_nSize);
    for(int i = 0;i < m_nSize;i++)
    {
        ivec vecTemp;
        vecTemp.resize(m_nSize);
        for(int j = 0;j < m_nSize;j++)
        {
            vecTemp[j] = nValue;
            nValue++;
        }
        m_vecResLayout.push_back(vecTemp);

    }
    m_vecResLayout[m_nSize-1][m_nSize-1] = 0;
}
bool LogicHandle::SetValue(QPoint pos,quint8 nValue)
{
    if(pos.x() < 0 || pos.x() >= m_nSize || pos.y() < 0 || pos.y() >= m_nSize)
    {
        return false;
    }
    m_vecLayout[pos.x()][pos.y()] = nValue;
    return true;
}
bool LogicHandle::Move(QPoint pos)
{
    bool bCanMove = false;
    bCanMove = CanMove(pos);
    QPoint ptSpace;
    bool bRes = GetSpacePos(ptSpace);
    if(bCanMove == true && bRes == true)
    {
        m_vecLayout[ptSpace.x()][ptSpace.y()] = m_vecLayout[pos.x()][pos.y()];
        m_vecLayout[pos.x()][pos.y()] = 0;
        return true;
    }
    else
    {
        return false;
    }

}
bool LogicHandle::CanMove(QPoint pos)
{
    QPoint ptSpace;
    GetSpacePos(ptSpace);
    //不是同一点
    if( pos.x() == ptSpace.x() && pos.y() == ptSpace.y())
    {
        return false;
    }
   //left
    if( (pos.x() == (ptSpace.x() - 1)) && ((ptSpace.x() - 1) >= 0) && pos.y() == ptSpace.y())
    {
        return true;
    }
    //right
    if( (pos.x() == (ptSpace.x() + 1)) && ((ptSpace.x() + 1) < m_nSize) && pos.y() == ptSpace.y())
    {
        return true;
    }
    //top
    if( (pos.x() == (ptSpace.x()))  && (pos.y() == (ptSpace.y() - 1)) && ((ptSpace.y() - 1) >= 0))
    {
        return true;
    }
    //bottom
    if( (pos.x() == (ptSpace.x())) && (pos.y() == (ptSpace.y() + 1) )&& ((ptSpace.y() + 1) < m_nSize))
    {
        return true;
    }
    return false;
}
bool LogicHandle::IsDone()
{
    for(int i = 0;i < m_nSize;i++)
    {
        for(int j = 0;j < m_nSize;j++)
        {
            if(m_vecResLayout[i][j] != m_vecLayout[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

bool LogicHandle::GetSpacePos(QPoint& pt)
{
    for(int i = 0;i < m_nSize;i++)
    {
        for(int j = 0;j < m_nSize;j++)
        {
            if(0 == m_vecLayout[i][j])
            {
                pt.setX(i);
                pt.setY(j);
                return true;
            }
        }
    }
    return false;
}

//方法1
//随机生成，检查是否可解，知道可解
bool LogicHandle::InitLayout()
{
    int nCnt = 0;
    while(true)
    {
        GenInitLayOut();
        nCnt++;
        qDebug() << QString("%1").arg(nCnt);
        if(IsCanSolve() == true)
        {
            break;
        }
        else
        {
            ClearLayOut();
        }
    }

    qDebug() <<"Suc";
    qDebug() << QString("%1").arg(nCnt);

    PrintLayOut();
    return true;
}


//方法2
//对结果进行 随机乱序，只有左，右，上，下4种方向
//1）移动打乱的方法（不推荐）
//以3x3为例，创建了9个方块（第9个方块为空缺方块，命名为方块9），将9个方块按正确答案的顺序排列，然后移动一定次数的方块9，并通过以下2点规则进行移动：

//边界时，只能向非边界方向移动
//移动方向不得与上一次移动方向相反，即不得回退
//通过方块9的不断移动，打乱其他方块的位置。这样可以保证一定有解。


bool LogicHandle::GenInitLayOut()
{
    //随机生成0~m_nSize-1的序列
    ivec vec;
    int nSize = m_nSize*m_nSize;
    vec.resize(nSize);
    for(int i = 0;i< nSize;i++)
    {
        vec[i] = i;
    }
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int m = 0;m < nSize;m++)
    {
        int nTemp = qrand() % (nSize-m);
        int xPos = m / m_nSize;
        int yPos = m % m_nSize;
        m_vecLayout[xPos][yPos] = vec[nTemp];

        //swap
        quint8 n = vec[nSize-1-m];
        vec[nSize-1-m] = vec[nTemp];
        vec[nTemp] = n;
    }
    return true;
}
void LogicHandle::ClearLayOut()
{
    for(int i = 0;i < m_nSize;i++)
    {
        QString strLog,strTemp;
        for(int j = 0;j < m_nSize;j++)
        {
            m_vecLayout[i][j] = 0;
        }
    }
}

void LogicHandle::PrintLayOut()
{
    for(int i = 0;i < m_nSize;i++)
    {
        QString strLog,strTemp;
        for(int j = 0;j < m_nSize;j++)
        {
            strTemp = QString("%1").arg(m_vecLayout[i][j]);
            strLog += strTemp;
            strLog += QString(" ");
        }
        qDebug()<<strLog;
    }
}

bool LogicHandle::IsCanSolve()
{
    ivec vecCur;

//    m_vecLayout[0][0] = 3;
//    m_vecLayout[0][1] = 0;
//    m_vecLayout[1][0] = 1;
//    m_vecLayout[1][1] = 2;

    GetLayOutList(vecCur);
    int CurRevCnt =  CalcReverseCount(vecCur);

    ivec vecRes;
    GetResList(vecRes);
    int ResRevCnt = 0 ;
    //ResRevCnt =  CalcReverseCount(vecRes);

    int m_nSpaceRowInit = m_nSize - 1;
    QPoint pt;
    GetSpacePos(pt);
    int m_nSpaceRowCur = pt.x();

    if(m_nSize % 2 == 1)
    {
        if((CurRevCnt %2) != (ResRevCnt %2) )
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        if( CurRevCnt %2 == 0 && (m_nSpaceRowCur - m_nSpaceRowInit) %2 == 0)
        {
           return true;
        }
        else if( CurRevCnt %2 == 1 && (m_nSpaceRowCur - m_nSpaceRowInit) %2 == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

//    数字华容道，必然有解，只存在于如下3个细分情形：

//    若格子列数为奇数，则逆序数必须为偶数；
//    若格子列数为偶数，且逆序数为偶数，则当前空格所在行数与初始空格所在行数的差为偶数；
//    若格子列数为偶数，且逆序数为奇数，则当前空格所在行数与初始空格所在行数的差为奇数。

//    return true;
}
bool LogicHandle::Init(int nSize)
{

    SetSize(nSize);
    AllocVec2D();
    GenResVec2D();
    //GenInitLayOut();
    InitLayout();
    return true;
}
bool LogicHandle::GetLayoutValuePos(QString strText,QPoint& pt)
{
    quint8 value = strText.toUInt();
    for(int i = 0;i < m_nSize;i++)
    {
        for(int j = 0;j < m_nSize;j++)
        {
            if(m_vecLayout[i][j] == value)
            {
                pt.setX(i);
                pt.setY(j);
                return true;
            }
        }
    }
    return false;
}
bool LogicHandle::GetLayoutValue(quint8 x,quint8 y,quint8 & nValue)
{
    if(x >= 0 && x < m_nSize && y >= 0 && y < m_nSize)
    {
        nValue = m_vecLayout[x][y];
        return true;
    }
    else
    {
        return false;
    }
}
void LogicHandle::GetLayOutList(ivec& vecCur)
{
    GetList(m_vecLayout, vecCur);
}
void LogicHandle::GetResList(ivec& vecCur)
{
    GetList(m_vecResLayout, vecCur);
}
//忽略空格的位置，得到当前数值的序列
void LogicHandle::GetList(QVector<ivec>& vecGrid, ivec& vecCur)
{
    vecCur.clear();
    for(int i = 0;i < m_nSize;i++)
    {
        for(int j = 0;j < m_nSize;j++)
        {
            if(vecGrid[i][j] > 0 )
            {
                vecCur.push_back(vecGrid[i][j]);
            }
        }
   }
}

int LogicHandle::CalcReverseCount(ivec& vecCur)
{
    int nReverseCount = 0;
    int nCnt = vecCur.size();
    for(int i = 0;i < nCnt-1;i++)
    {
        quint8 uTemp = vecCur[i];
        for(int j = i;j < nCnt;j++)
        {
            if(vecCur[j] < uTemp)
            {
                nReverseCount++;
            }
        }
    }
    return nReverseCount;
}
