#include "cconfighandle.h"
#include <QDir>
#include <QMessageBox>


ST_PARAMETER_CONFIG  CConfigHandle::m_configParameter;
CConfigHandle::CConfigHandle()
{
    m_setting =new QSettings(GetIniFilePath()+"config.ini", QSettings::IniFormat);
}

void CConfigHandle::LoadData()
{
    //加载数据到结构中
    //创建配置文件

//    QString dlgTitle="Receive";
//    QString strInfo=GetIniFilePath();
//    QMessageBox::information(nullptr, dlgTitle, strInfo,
//                              QMessageBox::Ok,QMessageBox::NoButton);


    //m_setting =new QSettings(GetIniFilePath()+"config.ini", QSettings::IniFormat);
    //参数1，代表新建ini文件的位置的绝对路径；  参数2，将设置存储在ini文件中
    //MessageBox(m_setting->fileName());
    m_setting->beginGroup(SECTION_CONFIG_SETTING);

    int nSize = m_setting->value(ENTRY_CONFIG_SIZE).toInt();
    m_configParameter.nSize = nSize;

    m_setting->endGroup();




}

void CConfigHandle::SaveData()
{

    //m_setting =new QSettings(GetIniFilePath()+"config.ini", QSettings::IniFormat);
    //参数1，代表新建ini文件的位置的绝对路径；  参数2，将设置存储在ini文件中
    //MessageBox(m_setting->fileName());
    m_setting->beginGroup(SECTION_CONFIG_SETTING);
    QVariant vt;
    vt.setValue(m_configParameter.nSize);
    m_setting->setValue(ENTRY_CONFIG_SIZE,vt);
    m_setting->endGroup();
}

void CConfigHandle::SetSize(int nSize)
{
    m_configParameter.nSize = nSize;
}
int CConfigHandle::GetSize()
{
    return m_configParameter.nSize;
}
PST_PARAMETER_CONFIG CConfigHandle::GetConfigParameter()
{
    return &m_configParameter;
}

QString CConfigHandle::GetIniFilePath()
{
    QString strIniFilePath;
    QString path;
    QDir dir;
    path=dir.currentPath();
    strIniFilePath = path+"/debug/Parameters/";


//    QString dlgTitle="Receive";
//    QString strInfo=strIniFilePath;
//    QMessageBox::information(nullptr, dlgTitle, strInfo,
//                              QMessageBox::Ok,QMessageBox::NoButton);
    return strIniFilePath;
}

