#ifndef SIZESETTING_H
#define SIZESETTING_H

#include <QDialog>
namespace Ui {
class SizeSetting;
}

class SizeSetting : public QDialog
{
    Q_OBJECT

public:
    explicit SizeSetting(QWidget *parent = nullptr);
    ~SizeSetting();

private:
    Ui::SizeSetting *ui;
private slots:
    void OnOk();
    void OnCancel();
};

#endif // SIZESETTING_H
