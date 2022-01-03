#include "fileManager.h"

void swap(Statistics* a, Statistics* b) {
    Statistics c;
    c = *a;
    *a = *b;
    *b = c;
}

sf::String fileManager::statsfromfile(std::string fileName) {
    std::ifstream fin(fileName, std::ios::binary);
    if (!fin.is_open()) throw 1;

    sf::String strFile;
    std::string strLine;
    std::string curstr;
    int keys;
    int fkeys;
    int _time;
    float accuracy;
    float speed;

    while (fin) {
        fin.read((char*)&keys, sizeof(int));
        fin.read((char*)&fkeys, sizeof(int));
        fin.read((char*)&_time, sizeof(int));
        accuracy = (double)(keys - fkeys) / (double)keys;
        speed = (double)keys / (double)_time;
        std::string acc = std::to_string((std::floor(accuracy * 100)) / 100);
        std::string spd = std::to_string(((speed)));
        acc.erase(acc.begin() + 4);
        spd.erase(spd.begin() + 4);
        std::stringstream strstr;
        strstr << std::setw(7) << std::right << std::to_string(keys)
            << "\t" << std::setw(9) << std::to_string(fkeys)
            << "\t" << std::setw(7) << std::to_string(_time)
            << "\t" << std::setw(9) << ((std::trunc(accuracy * 100)) / 100)
            << "\t" << std::setw(9) << ((std::trunc(speed * 100)) / 100);
        curstr = strstr.str() + "\n";
        strLine += curstr;
    }
    strLine.erase(strLine.size() - curstr.size() - 1, curstr.size());
    strFile = strLine;
    fin.close();
    return strFile;
}

void fileManager::statsToVarFile(std::string fileName, Statistics* stats, int var) {
    std::fstream fin(fileName, std::ios::binary);
    int num;
    int keys;
    int fkeys;
    int _time;
    float accuracy;
    float speed;

    std::ofstream fout(fileName, std::ios::binary | std::ios::app);
    if (!fout.is_open()) {
        throw 1;
    }

    num = (*stats).getPressed();
    fout.write((char*)&num, sizeof(int));

    num = (*stats).getMistNum();
    fout.write((char*)&num, sizeof(int));

    num = (*stats).getTime();
    fout.write((char*)&num, sizeof(int));

    return;
}

//var: 0 - speed, 1 - acc, 2 -keys, 3 - mistakes
void fileManager::sortFile(std::string fileName, int var) {
    std::vector<Statistics> arr(1);
    std::ifstream fin(fileName, std::ios::binary);
    int num;
    if (!fin) throw 1;

    while (fin) {
        fin.read((char*)&num, sizeof(int));
        arr[arr.size() - 1].setPressed(num);

        fin.read((char*)&num, sizeof(int));
        arr[arr.size() - 1].setMistNum(num);

        fin.read((char*)&num, sizeof(int));
        arr[arr.size() - 1].setTime(num);

        arr.push_back(Statistics());
    };

    arr.erase(arr.end() - 1);
    for (int i = 0; i < arr.size() - 1; i++) {
        for (int j = i + 1; j < arr.size(); j++) {
            switch (var) {
            case 0: {
                if (arr[j].getSpeed() > arr[i].getSpeed()) {
                    swap(&arr[j], &arr[i]);
                }
                break;
            }
            case 1: {
                if (arr[j].getAccuracy() > arr[i].getAccuracy()) {
                    swap(&arr[j], &arr[i]);
                }
                break;
            }
            case 2: {
                if (arr[j].getPressed() > arr[i].getPressed()) {
                    swap(&arr[j], &arr[i]);
                }
                break;
            }
            case 3: {
                if (arr[j].getMistNum() > arr[i].getMistNum()) {
                    swap(&arr[j], &arr[i]);
                }
                break;
            }
            }
        }
    }
    fin.close();

    std::ofstream fout(fileName, std::ios::binary);

    for (int i = 0; i < arr.size() - 1 && i < 9; i++) {
        num = arr[i].getPressed();
        fout.write((char*)&num, sizeof(int));

        num = arr[i].getMistNum();
        fout.write((char*)&num, sizeof(int));

        num = arr[i].getTime();
        fout.write((char*)&num, sizeof(int));
        
    }
    fout.close();
}