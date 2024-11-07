#include "tabledialog.h"
#include "ui_tabledialog.h"

TableDialog::TableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)  // Используем Ui::Dialog, без наследования
{
    ui->setupUi(this);


}

TableDialog::~TableDialog()
{
    delete ui;
}

int TableDialog::getRowCount() const
{
    return ui->rowsSpinBox->value();
}

int TableDialog::getColumnCount() const
{
    return ui->columnsSpinBox->value();
}

void TableDialog::on_okButton_clicked()
{
    accept();
}
