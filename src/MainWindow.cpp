#include "../includes/MainWindow.h"

using namespace std;

// CONSTRUCTEUR
MainWindow::MainWindow() : QWidget()
{

    m_path = new QString;
    m_path->append(QString::fromStdString(filesystem::current_path()));

    //!TAB
    m_tabBar = new QTabWidget;

    //==========PAGE CREATE===============//
    //! HBOXLAYOUT MAIN
    m_layoutCreatePage = new QVBoxLayout;

    //?DEF CLASS
    m_groupDefProject = new QGroupBox;
    m_groupDefProject->setTitle("Définition de la classe");

    m_formDefProject = new QFormLayout;

    m_nomProject = new QLineEdit;

    m_layoutDir = new QHBoxLayout;
    m_buttonSearchDir = new QPushButton("Search");
    m_pathDirectory = new QLineEdit;

    QObject::connect(m_buttonSearchDir, SIGNAL(clicked()), this, SLOT(chooseDirectory()));

    m_pathDirectory->setText(*m_path);
    m_layoutDir->addWidget(m_pathDirectory);
    m_layoutDir->addWidget(m_buttonSearchDir);

    m_formDefProject->addRow("&Nom:", m_nomProject);
    m_formDefProject->addRow("Directory", m_layoutDir);

    m_groupDefProject->setLayout(m_formDefProject);

    //=================================================//
    //? OPTIONS
    m_groupDefOptions = new QGroupBox;
    m_groupDefOptions->setTitle("Options");

    m_layoutOption = new QVBoxLayout;

    m_includes = new QCheckBox("Dossier includes");
    m_src = new QCheckBox("Dossier Source");
    m_qt = new QCheckBox("Projet Qt");

    m_includes->setChecked(true);
    m_src->setChecked(true);

    m_layoutOption->addWidget(m_includes);
    m_layoutOption->addWidget(m_src);
    m_layoutOption->addWidget(m_qt);

    m_groupDefOptions->setLayout(m_layoutOption);

    //=================================================//
    //?Ajouter commentaire

    m_groupRemark = new QGroupBox;
    m_groupRemark->setTitle("Ajouter Commentaires");
    m_groupRemark->setCheckable(true);
    m_groupRemark->setChecked(false);

    m_formRemark = new QFormLayout;

    m_auteur = new QLineEdit;
    m_textRemark = new QTextEdit;

    m_formRemark->addRow("&Auteur: ", m_auteur);
    m_formRemark->addRow("&commentaire: ", m_textRemark);

    m_groupRemark->setLayout(m_formRemark);

    //=========================================//
    //?Button

    m_layoutButton = new QHBoxLayout;
    m_quitter = new QPushButton;
    m_genere = new QPushButton;

    m_quitter->setText("Quitter");
    m_genere->setText("Générer !");

    m_layoutButton->addWidget(m_quitter);
    m_layoutButton->addWidget(m_genere);

    // CONNECTION
    QObject::connect(m_quitter, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(m_genere, SIGNAL(clicked()), this, SLOT(generate()));
    //===================================//
    //! ADD TO Create Page Layout
    m_layoutCreatePage->addWidget(m_groupDefProject);
    m_layoutCreatePage->addWidget(m_groupDefOptions);
    m_layoutCreatePage->addWidget(m_groupRemark);
    m_layoutCreatePage->addLayout(m_layoutButton);

    //=======PAGE MANAGE================//

    m_layoutManagePage = new QHBoxLayout;

    m_modelFileView = new QFileSystemModel;
    m_modelFileView->setRootPath(*m_path);

    m_treeView = new QTreeView;
    m_treeView->setModel(m_modelFileView);
    m_treeView->setRootIndex(m_modelFileView->index(*m_path));

    m_layoutManagePage->addWidget(m_treeView);

    //==========MAIN WINDOW ==============//
    m_pageCreate = new QWidget;
    m_pageManage = new QWidget;

    m_pageCreate->setLayout(m_layoutCreatePage);
    m_pageManage->setLayout(m_layoutManagePage);

    QTabWidget *tabs = new QTabWidget;
    tabs->addTab(m_pageCreate, tr("Create"));
    tabs->addTab(m_pageManage, tr("Manage"));

    // tabs->show();

    m_layoutTab = new QVBoxLayout;
    m_layoutTab->addWidget(tabs);

    //* ADD LAYOUT TO THE WINDOW
    this->setLayout(m_layoutTab);
}

void MainWindow::chooseDirectory()
{
    m_pathDirectory->setText(QFileDialog::getExistingDirectory(this, tr("Open directory"), *m_path, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks));
}

void MainWindow::generate() const
{

    //TEST

    m_path->clear();
    m_path->append(m_pathDirectory->text() + "/" + m_nomProject->text());

    std::cout << m_path->toStdString() << std::endl;

    filesystem::create_directories(m_path->toStdString());

    if (m_includes->isChecked() == true && m_src->isChecked() == true)
    {
        filesystem::create_directories(m_path->toStdString() + "/src");
        filesystem::create_directories(m_path->toStdString() + "/includes");
    }

    ////Modif main commentaire Projet
    ofstream mainFile(m_path->toStdString() + "/src/main.cpp");

    if (m_groupRemark->isChecked() == true)
    {

        if (mainFile)
        {
            mainFile << "/*" << endl
                     << "Auteur: " << m_auteur->text().toStdString() << endl
                     << endl
                     << "Description: " << endl
                     << m_textRemark->toPlainText().toStdString() << endl
                     << endl
                     << "*/" << endl
                     << endl;
        }
        else
        {
            cout << "Error open file main.cpp" << endl;
        }
    }

    mainFile << "#include <iostream>" << endl
             << endl
             << "using namespace std;" << endl
             << endl
             << "int main(int argc, char *agrv[])" << endl
             << "{" << endl
             << "   return 0;" << endl
             << "}" << endl;

    mainFile.close();

    //?Change project Name CMake
    /*
    #VERSION    
    cmake_minimum_required(VERSION 3.18.4)

    #PROJECT NAME
    project(projectGenerator)
    */
    ofstream cmakeFile(m_path->toStdString() + "/CMakeLists.txt");

    if (cmakeFile)
    {
        cmakeFile << "#VERSION" << endl
                  << "cmake_minimum_required(VERSION 3.18.4)" << endl
                  << endl
                  << "#PROJECT NAME" << endl
                  << "project(" << m_nomProject->text().toStdString() << ")" << endl
                  << endl
                  << endl;

        if (m_qt->isChecked() == true)
        {
            cmakeFile << "#======================= INCLUSION OF Qt =======================#" << endl
                      << "set(CMAKE_INCLUDE_CURRENT_DIR on)" << endl
                      << "set(CMAKE_AUTOMOC on)" << endl
                      << "set(CMAKE_AUTOUIC on)" << endl
                      << "set(CMAKE_PREFIX_PATH \"/home/tengu/Qt/6.2.0/gcc_64/lib/cmake\")" << endl
                      << endl
                      << "#package" << endl
                      << "find_package(Qt6 COMPONENTS Core REQUIRED)" << endl
                      << "find_package(Qt6 COMPONENTS Widgets REQUIRED)";
        }

        cmakeFile << "#=================== INCLUSION OF Project Files ====================#" << endl
                  << "set(INCLUDE_DIR \"${CMAKE_SOURCE_DIR}/includes\")" << endl
                  << "set(SOURCE_DIR \"${CMAKE_SOURCE_DIR}/src\")" << endl
                  << endl
                  << "include_directories(${INCLUDE_DIR})" << endl
                  << "include_directories(${SOURCE_DIR})" << endl
                  << endl
                  << "file(GLOB SOURCES \"${SOURCE_DIR}/*.cpp\" \"${INCLUDE_DIR}/*.h\")" << endl
                  << endl
                  << "#=================== SETUP EXECTUABLE ====================#" << endl
                  << "add_executable(${PROJECT_NAME} ${SOURCES})" << endl
                  << endl;
        if (m_qt->isChecked() == true)
        {
            cmakeFile << "#===================== LINKING LIBRARIES =======================#" << endl
                      << "target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)" << endl
                      << endl;
        }

        cmakeFile.close();
    }
    else
    {
        cout << "Error open cmake file" << endl;
    }

    m_treeView->setRootIndex(m_modelFileView->index(*m_path));
}