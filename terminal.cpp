#include <QApplication>
#include <QMainWindow>
#include <QLineEdit>
#include <QKeyEvent>
#include <QString> 
#include <QTextEdit> 
#include <QVBoxLayout>
#include <fstream>
#include "include/integration.h"
#include <unistd.h>
#include <fcntl.h>
#include <cstdio>
#include <iostream>
#include <fstream>

class Terminal:public QMainWindow{

    public:
        QString prompt = "user@minishell:$ ";
        QTextEdit* text;
        QLineEdit* echoLineEdit;

        Terminal(){ 
            setWindowTitle("Mini Shell");
            resize(950, 600);
            QWidget* central=new QWidget(this);
            QVBoxLayout* layout=new QVBoxLayout(central);

            text=new QTextEdit(central);
            text->setHtml(R"(
                <html>
                <body style="background-color:#300A24; color:white;
                            font-family:Consolas;">


                </body>
                </html>
            )");
               
            //setCentralWidget(text);
            echoLineEdit = new QLineEdit(central);
            echoLineEdit->setPlaceholderText("Type your command HERE");
            echoLineEdit->setStyleSheet(
            "QLineEdit {"
            "background-color: #300A24;"
            "color: white;"
            "padding:15px;"
            "font-family: Consolas;"
            "}");
            layout->addWidget(text);
            layout->addWidget(echoLineEdit);
            setCentralWidget(central);

            //echolineedit obj from the class qlineedit in this object if it detects enter it will exec a lambda function
            connect(echoLineEdit, &QLineEdit::returnPressed,this,[this]{ handleClick();});
            layout->setSpacing(0);
        
        }
        void handleClick(){
            QString command=echoLineEdit->text();   //retrieve the 
            echoLineEdit->clear();
            //adds the command next to the prompt 
            QString html ="<span style='color: #1ed124; font-size: 16px; font-weight: bold;'>user@minishell</span><span style='color: #fcfeff; font-size: 16px; font-weight: bold;'>:</span><span style='color: #1e4781; font-size: 16px; font-weight: bold;'></span><span style='color: #fcfeff; font-size: 16px; font-weight: bold;'>$</span> <span style='color: #fdf902; font-size: 16px;'>%1</span>";
            html=html.arg(command);
            text->append(html);
            executeCommand(command);
        }

        void executeCommand(QString command){//convert from Qstring to char
            int fd= open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
            int saved= dup(STDOUT_FILENO);
            
            dup2(fd,STDOUT_FILENO);
            QByteArray input=command.toLocal8Bit();
            char* in=input.data();
            partition* liste = tokenize_input(in);
            args* head = parser(liste);
            integration(head);
            fflush(stdout);
            std::cout.flush();
            dup2(saved,STDOUT_FILENO); //get back to the stdout mode 
            ::close(fd); //cause Qmainwindow has close as well 
        
            std::ifstream file("output.txt");
            std::string line;

            while (std::getline(file, line)) {
                QString cmd=QString::fromStdString(line);
                QString html ="<span style='color: #1136c8; font-size: 16px;'>%1</span>";
                html=html.arg(cmd.toHtmlEscaped());
                text->append(html);
            }
            file.close();
            ::close(saved);
        }

     
};








int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Terminal window;
    window.show();
    return app.exec();
}
