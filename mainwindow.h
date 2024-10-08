#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVector>
#include <QMap>
#include <QStackedWidget>
#include <QSignalMapper>
#include <QWidget>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QElapsedTimer>
#include <QTimer>

#include "circlewidget.h"
#include "ColorFillButton.h"

//#include <circlewidget.h>





class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void showLetterInfo(int index);  // Slot za prikaz informacija
    void clearInfo();  // Slot za brisanje informacija
    void playGame();
    void gameStart();
    void backButton();
    void startGame();
    void randomMorseCode();
    void randomMorseCodeForLevel();
    void playRandomGame();
    void checkAnswer(int index);
    void createButtons(QSignalMapper* signalMapper, QVBoxLayout* layout, int x, QWidget* widget);
    QString getRandomMorseCodeForLevel(int level);
    QMap<QString, int> creatingVariable(int level);
    void createLevelWidget(int level);
    void ClearFillButtons(QVector<ColorFillButton*> buttons);

    void createButtonsDependOnLevel(QSignalMapper* signalMapper, QVBoxLayout* layout, int level, QWidget* widget);

    QString getRandomMorseCode(const QMap<QString, QString>& letterInfo);
    void showInfoLevel (int level);
    void checkButtonState();
    void onIdleTimeout();
    void addLetters();


private:
    struct ButtonInfo {
        int index;
        int level;
        //int fillButtonIndex;
    };

    void checkAnswer1(MainWindow::ButtonInfo info);
    int currentLevel = 1;

    QVBoxLayout *level2Layout;          // Layout koji će se koristiti u drugim funkcijama
    QSignalMapper *signalMapperlevel2;

    QLabel *hoverLabel;  // Oznaka koja će prikazivati informaciju
    QLabel *randomLetters;
    QLabel *letterLabel;
    QLabel *answerLabel;
    QLabel *scoreLabel;
    QLabel *responseLabel;
    QLabel *resultLabel;
    QLabel *outputLabel;
     QLabel *nextLevelLabel;
    QProgressBar *progressBar;
    //QTimer *timer;
    QVector<QPushButton*> buttons;  // Niz dugmadi
    QVector<ColorFillButton*> buttonsFill;
    QPushButton *newwindow;
    QPushButton *window;
    QString alphabet;  // String sa slovima alfabeta
    QMap<QString,int> variableMap;
    QMap<QString,int> progressBarMap;
    QMap<QString, QString> letterInfo {
    {"A", ".-"},
    {"B", "-..."},
    {"C", "-.-."},
    {"D", "-.."},
    {"E", "."},
    {"F", "..-."},
    {"G", "--."},
    {"H", "...."},
    {"I", ".."},
    {"J", ".---"},
    {"K", "-.-"},
    {"L", ".-.."},
    {"M", "--"},
    {"N", "-."},
    {"O", "---"},
    {"P", ".--."},
    {"Q", "--.-"},
    {"R", ".-."},
    {"S", "..."},
    {"T", "-"},
    {"U", "..-"},
    {"V", "...-"},
    {"W", ".--"},
    {"X", "-..-"},
    {"Y", "-.--"},
        {"Z", "--.."}};

    QMap<int, QList<QString>> levels = {
        {1, {"E", "T"}},
        {2, {"E", "T", "A", "N"}},
        {3, {"E", "T", "A", "N", "I", "M"}},
        {4, {"E", "T", "A", "N", "I", "M", "S", "O"}}
    };
    QMap<int, QList<QString>> newLetters = {
        {1, {"E", "T"}},
        {2, {"A", "N"}},
        {3, {"I", "M"}},
        {4, {"S", "O"}}
    };
    // Mapa sa informacijama o svakom slovu
    QStackedWidget *stackedWidget;
    QStackedWidget *stackedWidgetLevels;
    QWidget *startPage;
    QWidget *gamePage;
    QWidget *learnPage;
    QWidget *levelsPage;
    QWidget *buttonPage;
    QWidget *level1Page;
    QWidget *levelPage;
     QWidget *nextLevelPage;
     QString currentMorseCode;
    int numOfInccorect;
     int progress;
     CircleWidget *circle1;
     CircleWidget *circle2;
     CircleWidget *circle3;
     QElapsedTimer timer;
     QString buttonPresses;  // String koji čuva niz tačaka i crta
     QTimer *idleTimer;
     bool isPressed;





};

#endif // MAINWINDOW_H
