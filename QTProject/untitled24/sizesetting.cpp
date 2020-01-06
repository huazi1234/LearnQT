#include "sizesetting.h"
#include "ui_sizesetting.h"
#include "CConfigHandle.h"
#include "common.h"

SizeSetting::SizeSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SizeSetting)
{
    ui->setupUi(this);
    CConfigHandle handle;
    handle.LoadData();
    ui->lineEdit_Size->setText(QString("%1").arg(handle.GetSize()));
}

SizeSetting::~SizeSetting()
{
    delete ui;
}
void SizeSetting::OnOk()
{
    int nSize = ui->lineEdit_Size->text().toUInt();
    //((Dialog*)parent)->SetSize(nSize);


    CConfigHandle handle;
    handle.SetSize(nSize);
    handle.SaveData();
    accept();
}

void SizeSetting::OnCancel()
{
    //rejected();
    accept();
}


