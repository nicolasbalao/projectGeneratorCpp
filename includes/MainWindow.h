/*
Créateur: Nicolas Balao

Description Fentre:
-HboxLayout: layoutMain
    -GroupBox: groupDefClass
        -FormLayout: formClass
            nom
            classe mere
    -GroupeBox: groupOption
        -FormLayout: formOption
            - check Box: protégé le header...
            -check box: générer un constructeur
            -check box: générer un destructeur
    -GroupeBox avec un check box : groupremarkaire
        - FormLayout: formCommentaire
            - Auteur:
            -Date de création: date picker
            -Role de la classe: Grand text


*/

#ifndef DEF_MAINWINDOW
#define DEF_MAINWINDOW

#include <iostream>
#include <filesystem>
#include <fstream>

//#include <string>

#include <QWidget>
#include <QApplication>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QDateEdit>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStringList>
#include <QString>
#include <QFileDialog>
#include <QLabel>

class MainWindow : public QWidget
{

    //SLOT PERSO
    Q_OBJECT

protected:
    QVBoxLayout *m_layoutMain; // layout de toute la fenêtre
    // DEF CLASS
    QGroupBox *m_groupDefProject;
    QFormLayout *m_formDefProject;
    QLineEdit *m_nomProject;
    QLineEdit *m_pathDirectory;
    QHBoxLayout *m_layoutDir;
    QPushButton *m_buttonSearchDir;

    // OPTIONS
    QGroupBox *m_groupDefOptions;
    QVBoxLayout *m_layoutOption;
    QCheckBox *m_includes;
    QCheckBox *m_src;
    QCheckBox *m_qt;

    //remark
    QGroupBox *m_groupRemark;
    QFormLayout *m_formRemark;
    QLineEdit *m_auteur;
    QTextEdit *m_textRemark;

    //button
    QHBoxLayout *m_layoutButton;
    QPushButton *m_quitter;
    QPushButton *m_genere;

public:
    MainWindow();

public slots:
    void chooseDirectory();
    void generate() const;
};

#endif