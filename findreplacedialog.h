#ifndef FINDREPLACEDIALOG_H
#define FINDREPLACEDIALOG_H

#include <QDialog>

namespace Ui {
class FindReplaceDialog;
}

class FindReplaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindReplaceDialog(QWidget *parent = nullptr);
    ~FindReplaceDialog();

    QString getSearchText() const;
    QString getReplaceText() const;
    bool isCaseSensitive() const;

signals:
    void findNext();
    void replace();
    void replaceAll();

private:
    Ui::FindReplaceDialog *ui;
};

#endif // FINDREPLACEDIALOG_H
