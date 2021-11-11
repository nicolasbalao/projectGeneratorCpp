#include "../includes/MainWindow.h"

using namespace std;

// CONSTRUCTEUR
MainWindow::MainWindow() : QWidget()
{
    //! HBOXLAYOUT MAIN
    m_layoutMain = new QVBoxLayout;

    //?DEF CLASS
    m_groupDefProject = new QGroupBox;
    m_groupDefProject->setTitle("Définition de la classe");

    m_formDefProject = new QFormLayout;

    m_nomProject = new QLineEdit;

    m_layoutDir = new QHBoxLayout;
    m_buttonSearchDir = new QPushButton("Search");
    m_pathDirectory = new QLineEdit;

    QObject::connect(m_buttonSearchDir, SIGNAL(clicked()), this, SLOT(chooseDirectory()));

    m_pathDirectory->setText("/home/tengu/Documents/");
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
    //! ADD TO MAIN LAYOUT
    m_layoutMain->addWidget(m_groupDefProject);
    m_layoutMain->addWidget(m_groupDefOptions);
    m_layoutMain->addWidget(m_groupRemark);
    m_layoutMain->addLayout(m_layoutButton);

    //* ADD LAYOUT TO THE WINDOW
    this->setLayout(m_layoutMain);
}

void MainWindow::chooseDirectory()
{
    m_pathDirectory->setText(QFileDialog::getExistingDirectory(this, tr("Open directory"), "/home/tengu/Documents", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks));
}

void MainWindow::generate() const
{
    QString path;
    path.append(m_pathDirectory->text() + "/" + m_nomProject->text());

    filesystem::create_directories(path.toStdString());

    if (m_includes->isChecked() == true && m_src->isChecked() == true)
    {
        filesystem::create_directories(path.toStdString() + "/src");
        filesystem::create_directories(path.toStdString() + "/includes");
    }

    ////Modif main commentaire Projet
    ofstream mainFile(path.toStdString() + "/src/main.cpp");

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
    ofstream cmakeFile(path.toStdString() + "/CMakeLists.txt");

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
}