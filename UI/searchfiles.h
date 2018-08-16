#ifndef SEARCHFILES_H
#define SEARCHFILES_H

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QTableWidget>
#include <QDir>
#include <QGridLayout>


class SearchFiles : public QWidget
{
    Q_OBJECT

public:
SearchFiles(QWidget *parent = 0);

private slots:
    void browse();
    void find();
    void openFileOfItem(int row, int column);

private:
    QStringList findFiles(const QStringList &files, const QString &text);
    void showFiles(const QStringList &files);
    QPushButton *createButton(const QString &text, const char *member);
    QComboBox *createComboBox(const QString &text = QString());
    void createFilesTable();

    QComboBox *fileComboBox;
    QComboBox *textComboBox;
    QComboBox *directoryComboBox;
    QLabel *fileLabel;
    QLabel *textLabel;
    QLabel *directoryLabel;
    QLabel *filesFoundLabel;
    QPushButton *browseButton;
    QPushButton *findButton;
    QTableWidget *filesTable;

    QDir currentDir;
};

#endif // SEARCHFILES_H
