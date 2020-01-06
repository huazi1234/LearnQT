#ifndef CCONFIGHANDLE_H
#define CCONFIGHANDLE_H
#include "common.h"
#include <QSettings>
class CConfigHandle
{
public:
    CConfigHandle();
    void LoadData();
    void SaveData();
public:
    QSettings* m_setting;
    static ST_PARAMETER_CONFIG  m_configParameter;


public:

    QString GetIniFilePath();

    int GetSize();
    void SetSize(int nSize);

    PST_PARAMETER_CONFIG GetConfigParameter();

};



#endif // CCONFIGHANDLE_H
