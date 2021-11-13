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
#include <QTabWidget>
#include <QTreeView>
#include <QFileSystemModel>

class MainWindow : public QWidget
{

    //SLOT PERSO
    Q_OBJECT

protected:
    QVBoxLayout *m_layoutTab;
    QTabWidget *m_tabBar;
    QString *m_path;

    //Page
    QWidget *m_pageCreate;
    QWidget *m_pageManage;

    //=======PAGE CREATE ============//
    QVBoxLayout *m_layoutCreatePage; // layout de toute la fenêtre
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
    QPushButton *m_buttonGoTo;
    QPushButton *m_genere;

    //========PAGE MANAGE======//

    QVBoxLayout *m_layoutManagePage;
    QFileSystemModel *m_modelFileView;
    QTreeView *m_treeView;

    QGroupBox *m_classOption;
    QFormLayout *m_layoutClassOption;
    QLineEdit *m_nomClass;
    QLineEdit *m_nomClassMere;
    QPushButton *m_buttonGenereClass;

    QGroupBox *m_classRemark;
    QFormLayout *m_classFormRemark;
    QLineEdit *m_classRemarkAuteur;
    QTextEdit *m_classTextRemark;

public:
    MainWindow();

public slots:
    void chooseDirectory();
    void generateProject();
    void generateClass();
    void goToDirectory();
};

#endif