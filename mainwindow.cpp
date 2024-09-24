#include "mainwindow.h"
#include "ColorFillButton.h"
#include "ColorFillButton.h"
#include "circlewidget.h"
#include <QGridLayout>
#include <QSignalMapper>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <random>
#include <QMessageBox>
#include <QTimer>
#include <QDebug>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), numOfInccorect(0), alphabet("QWERTYUIOPASDFGHJKLZXCVBNM"), currentMorseCode("") {

    setWindowTitle("MORSE CODE");
    //QTimer *timer = new QTimer(this);
    QFont fontn("Arial",38);

    QString buttonStyle =
        "QPushButton {"
        "   background-color: #A9A9A9;"  // DarkGray
        "   color: black;"               // Boja teksta
        "   border: 2px solid black;"    // Ivica
        "   border-radius: 5px;"         // Zaobljeni uglovi
        "}"
        "QPushButton:hover {"
        "   background-color: #808080;"  // Tamnija siva kada se pređe mišem preko dugmeta
        "}"
        "QPushButton:pressed {"
        "   background-color: #696969;"  // Još tamnija siva kada je dugme pritisnuto
        "}";

    this->setStyleSheet("background-color: lightgray;");


    QWidget *centralWidget = new QWidget(this); // koristi se obicno jer koristim MainWindow
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    stackedWidget = new QStackedWidget();

    nextLevelPage = new QWidget();
    QVBoxLayout *nextLevelLayout = new QVBoxLayout(nextLevelPage);
    nextLevelLabel = new QLabel ("NEXT LEVEL",this);
    nextLevelLabel->setAlignment(Qt::AlignHCenter);
    nextLevelLabel->setFont(fontn);
    nextLevelLayout->addWidget(nextLevelLabel);

    nextLevelPage->setLayout(nextLevelLayout);




    //LEVEL 1 PAGE START
    level1Page = new QWidget();
    QVBoxLayout *level1Layout = new QVBoxLayout(level1Page);
    QSignalMapper *signalMapperlevel1 = new QSignalMapper(this);

    QMap<QString, int> variableMap;
    variableMap = creatingVariable(1);


    createButtonsDependOnLevel(signalMapperlevel1, level1Layout, 1, level1Page);




    //POCETNA STRANA *START PAGE*
    startPage = new QWidget();
    QVBoxLayout *startLayout = new QVBoxLayout(startPage);
    startLayout->setAlignment(Qt::AlignCenter);
    QPushButton *learnButton = new QPushButton("LEARN",startPage);
    learnButton->setStyleSheet(buttonStyle);
    learnButton->setFixedSize(200, 50);
    startLayout->addWidget(learnButton);
    connect(learnButton, &QPushButton::clicked, this, &MainWindow::playGame);

    QPushButton *randomButton = new QPushButton("PLAY",startPage);
    randomButton->setStyleSheet(buttonStyle);
    randomButton->setFixedSize(200, 50);
    startLayout->addWidget(randomButton);
    connect(randomButton, &QPushButton::clicked, this, &MainWindow::playRandomGame);

    QPushButton *gameButton = new QPushButton("START GAME",startPage);
    gameButton->setStyleSheet(buttonStyle);
    gameButton->setFixedSize(200, 50);
    startLayout->addWidget(gameButton);
    connect(gameButton, &QPushButton::clicked, this, &MainWindow::startGame);


    startPage->setLayout(startLayout);

    //DRUGI LEJAUT *GAME PAGE*
    gamePage = new QWidget();
    QVBoxLayout *gamelayout = new QVBoxLayout(gamePage);
    gamelayout->setAlignment(Qt::AlignCenter);
    randomLetters = new QLabel ("",this);
    randomLetters->setAlignment(Qt::AlignHCenter);
    randomLetters->setFont(fontn);


    // Kreiraj dugmad sa slovima alfabeta
    QSignalMapper *signalMapper1 = new QSignalMapper(this);

    createButtons(signalMapper1,gamelayout,0, gamePage);
    gamelayout->addWidget(randomLetters);

    QPushButton *playButton = new QPushButton("RANDOM",gamePage);
    QHBoxLayout *horizontalLayout1 = new QHBoxLayout();
     playButton->setFixedSize(300, 50);
    horizontalLayout1->addStretch();  // Prazan prostor levo
    horizontalLayout1->addWidget(playButton);  // Dodaj prvo dugme
    horizontalLayout1->addStretch();
    //gamelayout->setAlignment(Qt::AlignCenter);


    //gamelayout->addWidget(playButton);  // Dodaj dugme u layout

    //gamelayout->addWidget(playButton);
    connect(playButton, &QPushButton::clicked, this, &MainWindow::randomMorseCode);

    QPushButton *back1 = new QPushButton("BACK",gamePage);
    QHBoxLayout *horizontalLayout2 = new QHBoxLayout();
    back1->setFixedSize(100, 50);
    horizontalLayout2->addStretch();  // Prazan prostor levo
    horizontalLayout2->addWidget(back1);  // Dodaj drugo dugme
    horizontalLayout2->addStretch();

    //gamelayout->addStretch();  // Dodaj prazan prostor pre dugmeta
    //gamelayout->addWidget(back1);  // Dodaj dugme u layout
    //gamelayout->addStretch();
    //gamelayout->addWidget(back1);
    connect(back1, &QPushButton::clicked, this, &MainWindow::backButton);

    gamelayout->addLayout(horizontalLayout1);
    gamelayout->addLayout(horizontalLayout2);

    //gamelayout->addWidget(randomLetters);

    gamePage->setLayout(gamelayout);



    //PRVI LEJAUT *LEARN PAGE*
    learnPage = new QWidget();
    QVBoxLayout *learnlayout = new QVBoxLayout(learnPage);

    hoverLabel = new QLabel("", this);
    hoverLabel->setAlignment(Qt::AlignHCenter);


    QFont font("Arial",38);
    hoverLabel->setFont(font);

    learnlayout->addWidget(hoverLabel);

    // Kreiraj dugmad sa slovima alfabeta
    QSignalMapper *signalMapper = new QSignalMapper(this);

    createButtons(signalMapper,learnlayout, 1, learnPage);



    QPushButton *back = new QPushButton("BACK",this);
    learnlayout->addWidget(back);
    connect(back, &QPushButton::clicked, this, &MainWindow::backButton);

    learnPage->setLayout(learnlayout);



    stackedWidget->addWidget(startPage);
    stackedWidget->addWidget(learnPage);
    stackedWidget->addWidget(gamePage);
    stackedWidget->addWidget(level1Page);
    stackedWidget->addWidget(nextLevelPage);



    mainLayout->addWidget(stackedWidget);
    centralWidget->setLayout(mainLayout);

    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow() {
    for (auto button : buttons) {
        delete button;
    }
    delete hoverLabel;
    //delete circle;
}

void MainWindow::showLetterInfo(int index) {
    QString letter = alphabet.at(index);
    hoverLabel->setText(letterInfo.value(letter, "Nema informacija"));
}

void MainWindow::clearInfo() {
    hoverLabel->setText("");
}

void MainWindow::playGame()
{
    stackedWidget->setCurrentWidget(learnPage);
}

void MainWindow::playRandomGame()
{
    stackedWidget->setCurrentWidget(gamePage);
}

void MainWindow::backButton()
{
    stackedWidget->setCurrentWidget(startPage);
}

void MainWindow::startGame()
{
    stackedWidget->setCurrentWidget(level1Page);
    showInfoLevel(1);

}



QString MainWindow::getRandomMorseCode(const QMap<QString, QString>& letterInfo) {
    // Kreiraj listu svih ključeva (slova) iz mape
    QList<QString> keys = letterInfo.keys();

    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<> dist(0, keys.size() - 1);


    QString randomKey = keys[dist(g)]; //randomizuje kljuceve

    return randomKey; //opcija da ona meni prvo vrati kljuc jer je mozda lakse;
}

void MainWindow::randomMorseCode() {

    QString randomMorse = getRandomMorseCode(letterInfo);
    randomLetters->setText(letterInfo[randomMorse]); //ispusuje u labelu iznad tastature morsov code koji je randomizovan tipa .-

    currentMorseCode = randomMorse;
}

void MainWindow::checkAnswer(int index) {
    QString selectedLetter = alphabet.at(index);
    letterLabel->setText("Tacno");
    if (selectedLetter == currentMorseCode) {
        randomLetters->setText("Tacno");
        letterLabel->setText("Tacno");

        QTimer::singleShot(700, nullptr, [&]()
        {
            randomMorseCode();
        });

    } else {
        randomLetters->setText("Netacno,pokusaj ponovo");
        QTimer::singleShot(700, this, [this]()
        {
            randomLetters->setText(letterInfo.value(currentMorseCode));
        });

    }
}

void MainWindow::createButtons(QSignalMapper* signalMapper, QVBoxLayout* layout, int x, QWidget* widget)
{
    int index = 0;
    // Prvih 10 dugmadi
    QHBoxLayout *horizontal1 = new QHBoxLayout(widget);
    for (int row = 1; row <= 10; ++row) {
        if (index < alphabet.size()) {
            QPushButton *button = new QPushButton(alphabet.at(index), this);
            button->setFixedSize(50, 50);
            buttons.append(button);
            horizontal1->addWidget(button);

            connect(button, &QPushButton::pressed, signalMapper, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));
            if(x == 1)
            {
                connect(button, &QPushButton::released, this, &MainWindow::clearInfo);
            }

            signalMapper->setMapping(button, index);

            ++index;
        }
    }


    QHBoxLayout *horizontal2 = new QHBoxLayout(widget);
    horizontal2->addSpacing(15);
    // drugih 9 dugmadi
    for (int col = 1; col <= 9; ++col) {
        if (index < alphabet.size()) {
            QPushButton *button = new QPushButton(alphabet.at(index), this);
            button->setFixedSize(50, 50);
            //button->setStyleSheet(buttonStyle);
            buttons.append(button);
            horizontal2->addWidget(button);

            connect(button, &QPushButton::pressed, signalMapper, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));
            if(x == 1)
            {
                connect(button, &QPushButton::released, this, &MainWindow::clearInfo);
            }
            signalMapper->setMapping(button, index);
            ++index;
        }
    }
    horizontal2->addSpacing(15);

    QHBoxLayout *horizontal3 = new QHBoxLayout(widget);
    horizontal3->addSpacing(45);
    // poslednjih 7 dugmadi
    for (int col = 1; col <= 7; ++col) {
        if (index < alphabet.size()) {
            QPushButton *button = new QPushButton(alphabet.at(index), this);
            button->setFixedSize(50, 50);
            buttons.append(button);
            horizontal3->addWidget(button);

            connect(button, &QPushButton::pressed, signalMapper, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));
            if(x == 1)
            {
                connect(button, &QPushButton::released, this, &MainWindow::clearInfo);
            }

            signalMapper->setMapping(button, index);
            ++index;
        }
    }
    horizontal3->addSpacing(90);

    layout->addLayout(horizontal1);
    layout->addLayout(horizontal2);
    layout->addLayout(horizontal3);

    if(x == 1)
    {
         connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(showLetterInfo(int)));
    }
    else
    {
        connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(checkAnswer(int)));

    }
}


void MainWindow::checkAnswer1(MainWindow::ButtonInfo info) {
    //qDebug() << "checkAnswer1 called, index:" << info.index << "level:" << info.level;
    int index = info.index;
    int level = info.level;
    //int fillButton = info.fillButtonIndex;


    //letterLabel->setText("Tacno");
    QList<QString> letters = levels[level]; //dobijam listu slova koja se koristi u zadatom nivou
    QString selectedLetter = letters.at(index);

    int p = 100/letters.size();

    if (selectedLetter == currentMorseCode)
    {
        //responseLabel->setText("Tacno");
        for (int i = 0; i < letters.size(); ++i)
        {
            if(selectedLetter == letters[i])
            {
                if(variableMap[selectedLetter] < 5)
                {
                    variableMap[selectedLetter]++;
                    //LOGIKA ZA PROGRES BAR
                    if(variableMap[selectedLetter] == 5)
                    {
                        qDebug() << "Variabala" << selectedLetter << "ima" << variableMap[selectedLetter] << " poena" ;
                        for (int x = 0; x < letters.size(); ++x)
                        {
                            if(selectedLetter == letters[x])
                            {
                                if(progressBarMap[letters[x]] == 0)
                                {
                                    progress = progress + p;
                                    progressBarMap[letters[x]]++;
                                    progressBar->setValue(progress);
                                    qDebug() << "PROGRESS JE" << progress;
                                }
                            }
                        }
                    }
                    //KRAJ LOGIKE ZA PROGRESS BAR
                    //scoreLabel->setText(QString::fromStdString(std::to_string(variableMap[selectedLetter])));
                    int m = 0;
                    for (int x = 0; x < letters.size(); ++x)
                    {
                        if(variableMap[letters[x]] == 5)
                        {
                            m++;
                            if(m == letters.size())
                            {
                                if (nextLevelPage && stackedWidget->indexOf(nextLevelPage) != -1) {
                                    //qDebug() << "nextLevelWidget POSTOJI";

                                    stackedWidget->setCurrentWidget(nextLevelPage);  // Promeni trenutni widget
                                }

                                //delete levelPage;
                                //qDebug() << "usao da napravi widget za nextlevel!!!" << m;
                                responseLabel->setText("NEXT LEVEL");
                                m = info.level + 1;
                               // stackedWidget->setCurrentWidget(nextLevelPage);
                                 createLevelWidget(m);

                                //stackedWidget->setCurrentWidget(levelPage);
                                //qDebug() << "INFOLEVEL" << info.level;

                            }
                        }

                    }

                }

            }

        }


    }
    else
    {
        //int k;
        if(numOfInccorect == 2)
        {

            circle3->setFilled(true);
            numOfInccorect = 0;

            //QThread::sleep(5);
            createLevelWidget(info.level);
            //stackedWidget->setCurrentWidget(levelPage);


        }
        else
        {
            numOfInccorect = numOfInccorect + 1;
            if (numOfInccorect == 1) {
                circle1->setFilled(true);
            } else if (numOfInccorect == 2) {
                circle2->setFilled(true);

            }

        }
        //responseLabel->setText("Netacno");


        for (int i = 0; i < letters.size(); ++i)
        {
            if(currentMorseCode == letters[i])
            {
                if(variableMap[currentMorseCode] > 0)
                {
                    variableMap[currentMorseCode]--;
                    //scoreLabel->setText(QString::fromStdString(std::to_string(variableMap[currentMorseCode])));

                }

            }

        }

    }
    letterLabel->setText( letterInfo[getRandomMorseCodeForLevel(info.level)]);
}

QString MainWindow::getRandomMorseCodeForLevel(int level) {

    QList<QString> letters = levels.value(level);

    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<> dist(0, letters.size() - 1);

    QString randomLetter = letters[dist(g)];

    currentMorseCode = randomLetter;

    return randomLetter;

}

QMap<QString, int> MainWindow::creatingVariable(int level)
{

    QList<QString> letters = levels.value(level);
    for (int i = 0; i < letters.size(); ++i)
    {
        variableMap.insert(letters[i],0);
        progressBarMap.insert(letters[i],0);
    }

    return variableMap;
}


void MainWindow::createLevelWidget(int level)
{
    /*if (levelPage != nullptr) {
        qDebug() << "Usao u brisanje WIDGETA";
        //stackedWidget->setCurrentWidget(nextLevelPage);  // Prebaci na drugi widget
        stackedWidget->removeWidget(levelPage);  // Ukloni iz stackedWidget
        levelPage->deleteLater();  // Odloži brisanje
        levelPage = nullptr;  // Postavi pokazivač na nullptr
    }*/

    numOfInccorect = 0;
    progress = 0;
    showInfoLevel(level);

    levelPage = new QWidget(stackedWidget);
    level2Layout = new QVBoxLayout(levelPage);
    signalMapperlevel2 = new QSignalMapper(this);

    createButtonsDependOnLevel(signalMapperlevel2, level2Layout, level, levelPage);
    //ClearFillButtons(buttonsFill);

    stackedWidget->addWidget(levelPage);
    stackedWidget->setCurrentWidget(levelPage);

    QMap<QString, int> variableMap;
    variableMap = creatingVariable(level);

    return;
}


void MainWindow::showInfoLevel(int level)
{
    QDialog dialog;
    dialog.setWindowTitle(QString("LEVEL %1").arg(level).toUpper());

    dialog.setMinimumSize(400, 300);

    QVBoxLayout *layout = new QVBoxLayout;

    QList<QString> letters = newLetters.value(level);

    QLabel  *letterOne = new QLabel(letters[0]+ ("     =>     ") + letterInfo[letters[0]]);
    letterOne->setStyleSheet("border: 2px solid black; padding: 5px;");
    letterOne->setAlignment(Qt::AlignCenter);
    QFont font1 = letterOne->font();
    font1.setPointSize(20);
    letterOne->setFont(font1);

    QLabel  *letterTwo = new QLabel(letters[1]+ ("     =>     ") + letterInfo[letters[1]]);
    letterTwo->setStyleSheet("border: 2px solid black; padding: 5px;");
    letterTwo->setAlignment(Qt::AlignCenter);
    QFont font2 = letterTwo->font();
    font2.setPointSize(20);
    letterTwo->setFont(font2);

    layout->addWidget(letterOne);
     layout->addWidget(letterTwo);

    QPushButton *okButton = new QPushButton("OK");
    layout->addWidget(okButton);
    QObject::connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);

    dialog.setLayout(layout);

    dialog.exec();
}

void MainWindow::createButtonsDependOnLevel(QSignalMapper* signalMapper, QVBoxLayout* layout, int level, QWidget* widget)
{
    QHBoxLayout *circlelayout = new QHBoxLayout(widget);
    circlelayout->setAlignment(Qt::AlignCenter);
    circle1 = new CircleWidget(widget);
    circlelayout->addWidget(circle1);

    circle2 = new CircleWidget(widget);
    circlelayout->addWidget(circle2);

    circle3 = new CircleWidget(widget);
    circlelayout->addWidget(circle3);
    layout->addLayout(circlelayout);

    QFont fontn("Arial",38);
    /*scoreLabel = new QLabel ("",widget);
    scoreLabel->setAlignment(Qt::AlignHCenter);
    scoreLabel->setFont(fontn);*/

    letterLabel = new QLabel ("",widget);
    letterLabel->setAlignment(Qt::AlignHCenter);
    letterLabel->setFont(fontn);

    progressBar = new QProgressBar(widget);
    progressBar->setAlignment(Qt::AlignHCenter);
    progressBar->setMinimum(0);    // Minimalna vrednost (npr. 0%)
    progressBar->setMaximum(100);  // Maksimalna vrednost (npr. 100%)


    responseLabel = new QLabel ("",widget);
    responseLabel->setAlignment(Qt::AlignHCenter);
    responseLabel->setFont(fontn);

    QString level1 = getRandomMorseCodeForLevel(level);
    letterLabel->setText(letterInfo[level1]);
    //layout->addWidget(scoreLabel);
    layout->addWidget(letterLabel);
    layout->addWidget(progressBar);


    QList<QString> letters = levels.value(level);

    int index = 0;
    // Prvih 10 dugmadi
    QHBoxLayout *horizontal1 = new QHBoxLayout(widget);
    for (int row = 1; row <= 10; ++row) {
        if (index < alphabet.size()) {
            QPushButton *button = new QPushButton(alphabet.at(index), widget);
            button->setFixedSize(50, 50);
            //button->setFilledParts(0);
            //buttonsFill.insert(index, button);
            buttons.append(button);
            horizontal1->addWidget(button);

            for (int i = 0; i < letters.size(); ++i) {

                if(letters[i] == alphabet.at(index)){


                    button->setStyleSheet(
                        "QPushButton {"
                        "   background-color: #A9A9A9;"  // DarkGray
                        "   color: white;"               // Boja teksta
                        "   border: 2px solid black;"    // Ivica
                        "   border-radius: 5px;"         // Zaobljeni uglovi
                        "}"
                        );


                    MainWindow::ButtonInfo info;
                    info.index = i;
                    info.level = level;
                    //info.fillButtonIndex = index;

                    connect(button, &QPushButton::pressed, [this, info]() {
                        //qDebug() << "Button pressed, info index:" << info.index << "level:" << info.level;
                        checkAnswer1(info);
                    });
                }

            }


            ++index;
        }
    }




    QHBoxLayout *horizontal2 = new QHBoxLayout(widget);
    horizontal2->addSpacing(15);
    // drugih 9 dugmadi
    for (int col = 1; col <= 9; ++col) {
        if (index < alphabet.size()) {
            QPushButton *button = new QPushButton(alphabet.at(index), widget);
            button->setFixedSize(50, 50);
            //button->setFilledParts(0);
            //buttonsFill.insert(index, button);
            buttons.append(button);
            horizontal2->addWidget(button);

            for (int i = 0; i < letters.size(); ++i) {

                if(letters[i] == alphabet.at(index)){


                    button->setStyleSheet(
                        "QPushButton {"
                        "   background-color: #A9A9A9;"  // DarkGray
                        "   color: white;"               // Boja teksta
                        "   border: 2px solid black;"    // Ivica
                        "   border-radius: 5px;"         // Zaobljeni uglovi
                        "}"
                        );


                    MainWindow::ButtonInfo info;
                    info.index = i;
                    info.level = level;
                    //info.fillButtonIndex = index;

                    connect(button, &QPushButton::pressed, [this, info]() {
                        //qDebug() << "Button pressed, info index:" << info.index << "level:" << info.level;
                        checkAnswer1(info);
                    });
                }

            }
            ++index;
        }
    }
    horizontal2->addSpacing(15);

    QHBoxLayout *horizontal3 = new QHBoxLayout(widget);
    horizontal3->addSpacing(45);
    // poslednjih 7 dugmadi
    for (int col = 1; col <= 7; ++col) {
        if (index < alphabet.size()) {
            QPushButton *button = new QPushButton(alphabet.at(index), widget);
            button->setFixedSize(50, 50);
            //button->setFilledParts(0);
            //buttonsFill.insert(index, button);
            buttons.append(button);
            horizontal3->addWidget(button);

            for (int i = 0; i < letters.size(); ++i) {

                if(letters[i] == alphabet.at(index)){


                    button->setStyleSheet(
                        "QPushButton {"
                        "   background-color: #A9A9A9;"  // DarkGray
                        "   color: white;"               // Boja teksta
                        "   border: 2px solid black;"    // Ivica
                        "   border-radius: 5px;"         // Zaobljeni uglovi
                        "}"
                        );


                    MainWindow::ButtonInfo info;
                    info.index = i;
                    info.level = level;
                    //info.fillButtonIndex = index;

                    connect(button, &QPushButton::pressed, [this, info]() {
                        //qDebug() << "Button pressed, info index:" << info.index << "level:" << info.level;
                        checkAnswer1(info);
                    });
                }

            }
            ++index;
        }
    }
    horizontal3->addSpacing(90);


    layout->addLayout(horizontal1);
    layout->addLayout(horizontal2);
    layout->addLayout(horizontal3);




}

void MainWindow::ClearFillButtons(QVector<ColorFillButton*> buttons)
{
    for(int i = 0; i < alphabet.size(); ++i)
    {
        qDebug() << "Koliko puta on ovde udje" << i;
        buttons[i]->setFilledParts(0);
    }
}



