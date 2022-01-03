#include "button.h"
#include "Statistics.h"
#include "FText.h"
#include "functions.cpp"
#include "Header.h"
#include "fileManager.h"

using namespace sf;

bool is_empty(std::ifstream& pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
}

bool complain(String cur, String entered) {
    if (cur == entered) {
        return true;
    }
    return false;
}

int main()
{
    VideoMode desktopMode = VideoMode::getDesktopMode();
    RenderWindow window(sf::VideoMode(910, 512,
        desktopMode.bitsPerPixel), "keyTrainee");
    window.setFramerateLimit(10);

    std::ofstream("statsSpeed", std::ios::binary);

    String line;
    std::string str;
    std::ifstream fin("Text.txt");

    while (!fin.eof()) {
        getline(fin, str);
        line += str;
        str.clear();
    }
    bool isGame = false;
    bool isStats = false;
    int curPosOrigin = 0;
    int curPosFormat = 0;
    int RGBTrig = 0; // 1 - green; 2 - red;
    int bckspsTrig = 0;

    float fx = 0;
    float fy = 0;

    int lastPos = 0;
    int sentNum = 0;
    int size = line.getSize();
    int const maxCount = 80;
    String c = "";
    std::vector<String> arr(1);
    while (lastPos < size) {
        c = line[lastPos];
        arr[sentNum] += c;
        lastPos++;
        if ((c == '.') || (c == '!') || (c == '?')) {
            sentNum++;
            arr.push_back("");
            c = line[lastPos];
            lastPos++;
        }
    }
    sentNum = 0;
    for (int i = 0; i < arr.size() - 1; i++) {
        if (i + 1 < arr.size()) {
            if (arr[i].getSize() + arr[i + 1].getSize() <= maxCount) {
                if (i + 2 < arr.size()) {
                    if (arr[i].getSize() + arr[i + 1].getSize() + arr[i + 2].getSize() <= maxCount) {
                        arr[i] += arr[i + 1] + arr[i + 2];
                        arr.erase(arr.begin() + i + 2);
                        arr.erase(arr.begin() + i + 1);
                    }
                    else {
                        arr[i] += arr[i + 1];
                        arr.erase(arr.begin() + i + 1);
                    }
                }
                else {
                    arr[i] += arr[i + 1];
                    arr.erase(arr.begin() + i + 1);
                    // arr.erase(arr.begin() + i);
                }
            }
        }
    }

    for (int i = 0; i < arr.size(); i++) {
        if (arr[i].getSize() > maxCount) {
            if (i == arr.size() - 1) {
                arr.push_back("");
            }
            else {
                arr.insert(arr.begin() + i + 1, "");
            }
            arr[i + 1] = arr[i].substring(arr[i].getSize() / 2, arr[i].getSize() - arr[i].getSize() / 2);
            arr[i].erase(arr[i].getSize() / 2, arr[i].getSize() - arr[i].getSize() / 2);
        }
    }

    fileManager FM;
    

    int par2sort = 0;
    std::string fileStats = "statsAcc";
    String LineToShow;
    ///////</returns>

    Font font;
    font.loadFromFile("Fonts/arialmt.ttf");

    Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(Color::White);
    str = arr[1] + "\n" + arr[2];
    text.setString(str);
    str.clear();

    String FLineOrigin = arr[0] + " " + " ";
    String FLineFormat = "%5" + FLineOrigin;
    FLineFormat.insert(3, "%1");

    FText ftext;
    ftext.setString(FLineFormat);
    ftext.setFont(font);
    ftext.setCharacterSize(20);
    ftext.setFillColor(Color::White);
    ftext.setOutlineColor(Color::Yellow);

    Text sessStats;
    sessStats.setFont(font);
    sessStats.setCharacterSize(20);
    sessStats.setFillColor(Color::White);;


    //THREE MAIN BUTTONS
    Button* startButton = new Button(Vector2f(25.f, 380.f), Vector2f(200.f, 100.f), &window);
    (*startButton).setButtonTexture("200x100.png", Vector2i(0, 0), Vector2i(200, 100));
    (*startButton).setMouseClickButton(Mouse::Button::Left);

    Button* exitButton = new Button(Vector2f(685.f, 380.f), Vector2f(200.f, 100.f), &window);
    (*exitButton).setButtonTexture("exit.png", Vector2i(0, 0), Vector2i(200, 100));
    (*exitButton).setMouseClickButton(Mouse::Button::Left);

    Button* statsButton = new Button(Vector2f(355.f, 380.f), Vector2f(200.f, 100.f), &window);
    (*statsButton).setButtonTexture("stats.png", Vector2i(0, 0), Vector2i(200, 100));
    (*statsButton).setMouseClickButton(Mouse::Button::Left);



    //SET TIME OF SESSION
    Button* oneMin = new Button(Vector2f(25.f, 330.f), Vector2f(50.f, 50.f), &window);
    (*oneMin).setButtonTexture("timeonetrue.png", Vector2i(1, 1), Vector2i(49, 49));
    (*oneMin).setMouseClickButton(Mouse::Button::Left);

    Button* twoMin = new Button(Vector2f(75.f, 330.f), Vector2f(50.f, 50.f), &window);
    (*twoMin).setButtonTexture("timetwofalse.png", Vector2i(50, 0), Vector2i(50, 50));
    (*twoMin).setMouseClickButton(Mouse::Button::Left);

    Button* threeMin = new Button(Vector2f(125.f, 330.f), Vector2f(50.f, 50.f), &window);
    (*threeMin).setButtonTexture("timethreefalse.png", Vector2i(100, 0), Vector2i(50, 50));
    (*threeMin).setMouseClickButton(Mouse::Button::Left);

    Button* fourMin = new Button(Vector2f(175.f, 330.f), Vector2f(50.f, 50.f), &window);
    (*fourMin).setButtonTexture("timefourfalse.png", Vector2i(150, 0), Vector2i(50, 50));
    (*fourMin).setMouseClickButton(Mouse::Button::Left);



    //PARAMETER TO SHOW STATS
    //A - accuracy
    //M - mistakes
    //K - keys pressed
    //S - speed
    Button* accBut = new Button(Vector2f(355.f, 330.f), Vector2f(50.f, 50.f), &window);
    (*accBut).setButtonTexture("stAtrue.png", Vector2i(1, 1), Vector2i(49, 49));
    (*accBut).setMouseClickButton(Mouse::Button::Left);

    Button* keyBut = new Button(Vector2f(405.f, 330.f), Vector2f(50.f, 50.f), &window);
    (*keyBut).setButtonTexture("stKfalse.png", Vector2i(1, 0), Vector2i(50, 50));
    (*keyBut).setMouseClickButton(Mouse::Button::Left);

    Button* misBut = new Button(Vector2f(455.f, 330.f), Vector2f(50.f, 50.f), &window);
    (*misBut).setButtonTexture("stMfalse.png", Vector2i(0, 0), Vector2i(50, 50));
    (*misBut).setMouseClickButton(Mouse::Button::Left);

    Button* spdBut = new Button(Vector2f(505.f, 330.f), Vector2f(50.f, 50.f), &window);
    (*spdBut).setButtonTexture("stSfalse.png", Vector2i(0, 0), Vector2i(50, 50));
    (*spdBut).setMouseClickButton(Mouse::Button::Left);





    //SOME JUNK HERE
    Clock clock;
    int sessTime = 20;

    Statistics statistics;
    Sprite current;
    String test;

    try {
        //MAIN WHILE
        while (window.isOpen())
        {

            //SHOW NEW TRIPLE OF SENTENSES P.S. idfk why "triple" but it doesnt matter
            if ((curPosOrigin == FLineOrigin.getSize() - 2)) {
                window.clear();
                sentNum++;
                FLineFormat.clear();
                FLineOrigin.clear();
                FLineOrigin = arr[sentNum] + " " + " ";
                FLineFormat = "%5" + FLineOrigin;
                FLineFormat.insert(3, "%1");
                RGBTrig = 0;
                str.clear();
                str = arr[sentNum + 1];
                str += "\n" + arr[sentNum + 2];
                text.setString(str);
                ftext.setString(FLineFormat);
                curPosFormat = 0;
                curPosOrigin = 0;
            }

            // check all the window's events that were triggered since the last iteration of the loop
            Event event;
            while (window.pollEvent(event))
            {
                // "close requested" event: we close the window
                if (event.type == Event::Closed) {
                    window.close();
                }

                else if (event.type == Event::KeyPressed) {
                    if (isGame) {
                        if ((event.key.code == Keyboard::BackSpace) ||
                            (event.key.code == Keyboard::Backspace) ||
                            (event.key.code == Keyboard::BackSlash) ||
                            (event.key.code == Keyboard::Backslash))
                        {
                            statistics.press();
                            statistics.fKey();

                            if (curPosOrigin != 0) {
                                FLineFormat.erase(curPosFormat + 3, 2);
                                FLineFormat.erase(curPosFormat, 2);
                                curPosFormat--;
                                FLineFormat.insert(curPosFormat, "%5");
                                FLineFormat.insert(curPosFormat + 3, "%1");
                                ftext.setString(FLineFormat);
                                curPosOrigin--;
                                bckspsTrig = 1;
                                String strToCheck = FLineFormat.substring(curPosFormat - 2, 2);
                                if ((strToCheck == "%2") || (strToCheck == "%3")) {
                                    FLineFormat.erase(curPosFormat - 2, 2);
                                    curPosFormat -= 2;
                                    test = strToCheck;
                                }
                                strToCheck.clear();
                            }
                            else {
                                RGBTrig = 0;
                            }
                        }
                        else {
                            bckspsTrig = 0;
                        }

                    }

                }
                else if (event.type == Event::TextEntered) {
                    if ((isGame) && (!bckspsTrig)) {
                        if (FLineOrigin[curPosOrigin] == static_cast <char>(Keyboard::Enter)) {
                            curPosOrigin++;
                        }
                        else if (FLineOrigin[curPosOrigin] == static_cast <char>(Keyboard::Return)) {
                            curPosOrigin++;

                        }
                        else if (event.text.unicode == Keyboard::Backspace) {

                        }
                        else if (event.text.unicode == Keyboard::BackSpace) {

                        }
                        else if (event.text.unicode == Keyboard::BackSlash) {

                        }
                        else if (event.text.unicode == Keyboard::Backslash) {

                        }
                        else {
                            if (complain(FLineOrigin[curPosOrigin], static_cast<char>(event.text.unicode))) {
                                statistics.press();
                                if (RGBTrig != 1) {
                                    FLineFormat.erase(curPosFormat, 2);
                                    FLineFormat.insert(curPosFormat, "%3");
                                    curPosFormat += 3;
                                }
                                else {
                                    FLineFormat.erase(curPosFormat, 2);
                                    curPosFormat++;
                                }
                                RGBTrig = 1; //1 - green;
                                curPosOrigin++;
                            }
                            else {
                                if (event.text.unicode == Keyboard::Backspace) {

                                }
                                else if (event.text.unicode == Keyboard::BackSpace) {

                                }
                                else if (event.text.unicode == Keyboard::BackSlash) {

                                }
                                else if (event.text.unicode == Keyboard::Backslash) {

                                }
                                else {
                                    statistics.press();
                                    statistics.fKey();
                                    if (RGBTrig != 2) {
                                        FLineFormat.erase(curPosFormat, 2);
                                        FLineFormat.insert(curPosFormat, "%2");
                                        curPosFormat += 3;
                                    }
                                    else {
                                        FLineFormat.erase(curPosFormat, 2);
                                        curPosFormat++;
                                    }
                                    RGBTrig = 2; // 2 - red;
                                    curPosOrigin++;
                                }
                            }
                        }
                        FLineFormat.erase(curPosFormat, 2);
                        FLineFormat.insert(curPosFormat, "%5");
                        FLineFormat.insert(curPosFormat + 3, "%1");
                        ftext.setString(FLineFormat);
                        std::string striri = FLineFormat.toAnsiString();
                        std::cout << striri << std::endl;
                    }
                }

                if (event.type == Event::MouseButtonPressed) {//если нажата клавиша мыши
                    if (event.key.code == Mouse::Left) {//а именно левая
                        if (!isGame) {
                            //SET SESSION TIME
                            if ((*oneMin).ButtonSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                                sessTime = 60;
                                (*oneMin).setButtonTexture("timeonetrue.png", Vector2i(0, 0), Vector2i(50, 50));
                                (*twoMin).setButtonTexture("timetwofalse.png", Vector2i(0, 0), Vector2i(50, 50));
                                (*threeMin).setButtonTexture("timethreefalse.png", Vector2i(0, 0), Vector2i(50, 50));
                                (*fourMin).setButtonTexture("timefourfalse.png", Vector2i(0, 0), Vector2i(50, 50));
                                statistics.setTime(sessTime);
                            }
                            else if ((*twoMin).ButtonSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                                sessTime = 120;
                                (*oneMin).setButtonTexture("timeonefalse.png", Vector2i(0, 0), Vector2i(50, 50));
                                (*twoMin).setButtonTexture("timetwotrue.png", Vector2i(0, 0), Vector2i(50, 50));
                                (*threeMin).setButtonTexture("timethreefalse.png", Vector2i(0, 0), Vector2i(50, 50));
                                (*fourMin).setButtonTexture("timefourfalse.png", Vector2i(0, 0), Vector2i(50, 50));
                                statistics.setTime(sessTime);
                            }
                            else if ((*threeMin).ButtonSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                                sessTime = 180;
                                (*oneMin).setButtonTexture("timeonefalse.png", Vector2i(0, 0), Vector2i(50, 50));
                                (*twoMin).setButtonTexture("timetwofalse.png", Vector2i(0, 0), Vector2i(50, 50));
                                (*threeMin).setButtonTexture("timethreetrue.png", Vector2i(0, 0), Vector2i(50, 50));
                                (*fourMin).setButtonTexture("timefourfalse.png", Vector2i(0, 0), Vector2i(50, 50));
                                statistics.setTime(sessTime);
                            }
                            else if ((*fourMin).ButtonSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                                sessTime = 240;
                                (*oneMin).setButtonTexture("timeonefalse.png", Vector2i(0, 0), Vector2i(50, 50));
                                (*twoMin).setButtonTexture("timetwofalse.png", Vector2i(0, 0), Vector2i(50, 50));
                                (*threeMin).setButtonTexture("timethreefalse.png", Vector2i(0, 0), Vector2i(50, 50));
                                (*fourMin).setButtonTexture("timefourtrue.png", Vector2i(0, 0), Vector2i(50, 50));
                                statistics.setTime(sessTime);
                            }

                            //SET STATS FILE TO SHOW
                            if ((*accBut).ButtonSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                                (*accBut).setButtonTexture("stAtrue.png", Vector2i(0, 0), Vector2i(50, 50));
                                (*keyBut).setButtonTexture("stKfalse.png", Vector2i(0, 0), Vector2i(50, 50));
                                (*misBut).setButtonTexture("stMfalse.png", Vector2i(0, 0), Vector2i(50, 50));
                                (*spdBut).setButtonTexture("stSfalse.png", Vector2i(0, 0), Vector2i(50, 50));
                                fileStats = "statsAcc";
                                par2sort = 1;
                            }
                            else if ((*keyBut).ButtonSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                                (*accBut).setButtonTexture("stAfalse.png", Vector2i(0, 0), Vector2i(50, 50));
                                (*keyBut).setButtonTexture("stKtrue.png", Vector2i(0, 0), Vector2i(50, 50));
                                (*misBut).setButtonTexture("stMfalse.png", Vector2i(0, 0), Vector2i(50, 50));
                                (*spdBut).setButtonTexture("stSfalse.png", Vector2i(0, 0), Vector2i(50, 50));
                                fileStats = "statsKeys";
                                par2sort = 0;
                            }
                            else if ((*misBut).ButtonSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                                (*accBut).setButtonTexture("stAfalse.png", Vector2i(0, 0), Vector2i(50, 50));
                                (*keyBut).setButtonTexture("stKfalse.png", Vector2i(0, 0), Vector2i(50, 50));
                                (*misBut).setButtonTexture("stMtrue.png", Vector2i(0, 0), Vector2i(50, 50));
                                (*spdBut).setButtonTexture("stSfalse.png", Vector2i(0, 0), Vector2i(50, 50));
                                fileStats = "statsMist";
                                par2sort = 2;
                            }
                            else if ((*spdBut).ButtonSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                                (*accBut).setButtonTexture("stAfalse.png", Vector2i(0, 0), Vector2i(50, 50));
                                (*keyBut).setButtonTexture("stKfalse.png", Vector2i(0, 0), Vector2i(50, 50));
                                (*misBut).setButtonTexture("stMfalse.png", Vector2i(0, 0), Vector2i(50, 50));
                                (*spdBut).setButtonTexture("stStrue.png", Vector2i(0, 0), Vector2i(50, 50));
                                fileStats = "statsSpeed";
                                par2sort = 3;
                            }


                            //STATS SHOW
                            if ((*statsButton).ButtonSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                                isGame = false;
                                isStats = true;
                                str = "\tKeys\tMistakes\tTime\tAccuracy\tSpeed\n";
                                FM.sortFile(fileStats, par2sort);
                                str += FM.statsfromfile(fileStats);
                                LineToShow = str;
                                window.clear();
                                sessStats.setString(str);
                            }
                            //GET START COMM
                            if ((*startButton).ButtonSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                                isGame = true;
                                isStats = false;
                                curPosFormat = 0;
                                curPosOrigin = 0;
                                sentNum = 0;
                                RGBTrig = 0;
                                FLineOrigin = arr[sentNum] + " " + " ";
                                FLineFormat = "%5" + FLineOrigin;
                                FLineFormat.insert(3, "%1");

                                str = arr[sentNum + 1] + "\n" + arr[sentNum + 2];
                                text.setString(str);
                                text.setPosition(0, 20);
                                str.clear();
                                ftext.setString(FLineFormat);
                                clock.restart();
                                statistics.nullAll();
                            }

                        }
                        //EXIT COMM
                        if ((*exitButton).ButtonSprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                            exit(0);
                            return 0;
                        }
                    }
                }

            }
            window.clear();
            if ((*oneMin).draw()) {
            }
            if ((*twoMin).draw()) {
            }
            if ((*threeMin).draw()) {
            }
            if ((*fourMin).draw()) {
            }
            if ((*accBut).draw()) {
            }
            if ((*keyBut).draw()) {
            }
            if ((*misBut).draw()) {
            }
            if ((*spdBut).draw()) {
            }
            if ((*startButton).draw()) {
            }
            if ((*exitButton).draw()) {
            }
            if ((*statsButton).draw()) {
            }
            

            if ((isGame) && (!isStats) && (clock.getElapsedTime().asSeconds() > sessTime)) {
                isGame = false;
                isStats = true;
                window.clear();
                LineToShow.clear();
                if (statistics.getPressed() == 0) {
                    LineToShow += "Keys pressed: 0";
                }
                else {
                    LineToShow += "Keys pressed: " + std::to_string(statistics.getPressed()) + "\n";
                    LineToShow += "Mistakes: " + std::to_string(statistics.getMistNum()) + "\n";
                    statistics.setTime(sessTime);
                    LineToShow += "Speed: " + std::to_string(trunc(statistics.getSpeed()*100)/100) + " keys/minute" "\n";
                    LineToShow += "Accuracy " + std::to_string(statistics.getAccuracy()) + "%" + "\n";

                    FM.statsToVarFile("statsSpeed", &statistics, 0);
                    FM.statsToVarFile("statsAcc", &statistics, 1);
                    FM.statsToVarFile("statsKeys", &statistics, 2);
                    FM.statsToVarFile("statsMist", &statistics, 3);
                }            

                sessStats.setString(LineToShow);
            }

            if ((isGame) && (!isStats) && (clock.getElapsedTime().asSeconds() < sessTime)) {
                text.setPosition(0, 20);
            }
            if (isGame) {
                window.draw(text);
                window.draw(ftext);
            }
            if (isStats) {
                window.draw(sessStats);
            }
            window.display();
        }
    } 
    catch(int) {
        text.setString("ERROR. PROGRAM EXIT LAUNCHING...");
        window.clear();
        window.draw(text);
        window.display();
        Sleep(5000);
        exit(1);
        return 1;
    }
    return 0;
}