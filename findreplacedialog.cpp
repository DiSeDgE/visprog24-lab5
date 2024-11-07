#include "findreplacedialog.h"
#include "ui_findreplacedialog.h"

FindReplaceDialog::FindReplaceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindReplaceDialog)
{
    ui->setupUi(this);

    // Connect the signals for find, replace, and replace all buttons
    connect(ui->findNextButton, &QPushButton::clicked, this, &FindReplaceDialog::findNext);
    connect(ui->replaceButton, &QPushButton::clicked, this, &FindReplaceDialog::replace);
    connect(ui->replaceAllButton, &QPushButton::clicked, this, &FindReplaceDialog::replaceAll);
}

FindReplaceDialog::~FindReplaceDialog()
{
    delete ui;
}

QString FindReplaceDialog::getSearchText() const
{
    return ui->findLineEdit->text();
}

QString FindReplaceDialog::getReplaceText() const
{
    return ui->replaceLineEdit->text();
}

bool FindReplaceDialog::isCaseSensitive() const
{
    return ui->caseCheckBox->isChecked();
}
