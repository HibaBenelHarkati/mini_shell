#include <QApplication>
#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QWidget>
#include <QTextCursor>
#include <QFont>

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

#include "include/parser.h"
#include "include/builtins.h"
#include "include/pipe_exec.h"
#include "include/redirections.h"
#include "include/tokenizer.h"
#include "include/process.h"


// ========================================
// TON MOTEUR SHELL
// ========================================

void integration(args* cmd)
{
    args* temp = cmd;

    if (temp->next_part != NULL) {
        exec_pipe(temp);
    }
    else if (temp->ptr1 != NULL) {
        redirect_exec(temp);
    }
    else if (strcmp(temp->argv[0], "cd") == 0) {
        exec_cd(temp);
    }
    else if (strcmp(temp->argv[0], "echo") == 0) {
        exec_echo(temp);
    }
    else if (strcmp(temp->argv[0], "pwd") == 0) {
        exec_pwd();
    }
    else {
        pid_t pid = fork();

        if (pid == 0) {
            exec_cmd(temp);
            _exit(EXIT_SUCCESS);
        }
        else if (pid > 0) {
            waitpid(pid, NULL, 0);
        }
        else {
            perror("fork");
        }
    }
}


// ========================================
// INTERFACE TERMINAL
// ========================================

class Terminal : public QMainWindow
{
public:

    QTextEdit *terminal;
    QLineEdit *input;

    Terminal()
    {
        setWindowTitle("Mini Shell");
        resize(950, 600);

        // Zone principale
        QWidget *central = new QWidget();

        // Affichage terminal
        terminal = new QTextEdit();
        terminal->setReadOnly(true);

        // Police
        QFont font("Monospace", 11);
        font.setStyleHint(QFont::Monospace);

        terminal->setFont(font);

        // Saisie
        input = new QLineEdit();

        input->setFont(font);
        input->setPlaceholderText("Enter command...");

        // DARK MODE
        setStyleSheet(R"(
            QMainWindow {
                background-color: #111827;
            }

            QTextEdit {
                background-color: #0b1120;
                color: #d1fae5;
                border: none;
                padding: 15px;
                selection-background-color: #2563eb;
            }

            QLineEdit {
                background-color: #111827;
                color: #34d399;
                border: 1px solid #374151;
                border-radius: 6px;
                padding: 12px;
            }

            QLineEdit:focus {
                border: 1px solid #10b981;
            }
        )");

        // Layout
        QVBoxLayout *layout = new QVBoxLayout();

        layout->addWidget(terminal);
        layout->addWidget(input);

        layout->setContentsMargins(12, 12, 12, 12);
        layout->setSpacing(10);

        central->setLayout(layout);

        setCentralWidget(central);

        // Message de bienvenue
        terminal->append("<span style='color:#34d399;'>"
                         "Welcome to Mini Shell!"
                         "</span>");

        terminal->append("Type a command to get started.\n");

        showPrompt();

        // Entrée
        connect(input, &QLineEdit::returnPressed,
                this, [this]() {

            QString command = input->text();

            if (command.isEmpty())
                return;

            terminal->moveCursor(QTextCursor::End);

            terminal->insertPlainText(command + "\n");

            input->clear();

            // Conversion
            QByteArray bytes = command.toLocal8Bit();

            char* cmd = strdup(bytes.constData());

            // Tokenizer
            partition* liste = tokenize_input(cmd);

            // Parser
            args* head = parser(liste);

            if (head != nullptr && head->argv != nullptr) {

                integration(head);
            }

            free(cmd);

            showPrompt();
        });
    }


    // ========================================
    // PROMPT
    // ========================================

    void showPrompt()
    {
        char cwd[1024];

        getcwd(cwd, sizeof(cwd));

        QString path = QString::fromLocal8Bit(cwd);

        terminal->moveCursor(QTextCursor::End);

        terminal->insertHtml(
            "<span style='color:#34d399;'>hiba@mini-shell</span>"
            "<span style='color:#64748b;'>:</span>"
            "<span style='color:#60a5fa;'>" +
            path.toHtmlEscaped() +
            "</span>"
            "<span style='color:#facc15;'> $ </span>"
        );

        terminal->moveCursor(QTextCursor::End);
    }
};


// ========================================
// MAIN
// ========================================

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Terminal window;

    window.show();

    return app.exec();
}
