#include <iostream>
#include <stdio.h>
#include <iomanip>
#include "Student.cpp"
#include "List.h"
#include <fstream>
#include <limits>
#include <locale>
#define clearscr std::string clear(100,'\n'); std::cout << clear;
class mainmenu
{
    private:
    int tik = 0;
    int count;
    Student *students;
    std::string entlist[13] = {" фамилию", " имя", " отчество", " день рождения", " месяц рождения", " год рождения", " год поступления", " институт", " кафедру", " группу", " номер зачётной книжки", " пол" };
    public:
    void tasker(int choise)
    {
        if (choise == 1)
        {
            clearscr
            std::cout << "Введите колличество студентов: ";
            std::cin >> count;
            tik = 1;
            createbd(count);
            menu();
        }
        if (choise == 2)
        {
            printstudents();
            menu();
        }
        if (choise == 3)
        {
            clearscr
            int N;
            int subchoise;
            std::cout << "Что вы хотите изменить ? (1 - данные студента, 2 - данные сессий студента): ";
            std::cin >> subchoise;
            std::cout << std::endl << "Введите ID для изменения: ";
            std::cin >> N;
            editstudent(N, subchoise);
            menu();
        }
        if (choise == 4)
        {
            int notexiststud;
            std::cout << std::endl << "Введите ID студента: ";
            std::cin >> notexiststud;
            delstudent(notexiststud);
            menu();
        }
        if (choise == 5)
        {
            maketask();
            menu();
        }
        if (choise == 0)
        {
            if (tik)
            {
                writedb();
            }
            std::exit(0);
        }
        if (choise == 6)
        {
            readdb();
            menu();
        }
    }
    void createbd(int S)
    {
            students = new Student[S];
    }
    void printstudents()
    {
        char Q[21];
        for (int i = 0; i < count +1; i++)
        {
            if(students[i].exist == 1) 
            {
                std::cout << std::endl << "ID студента  - " << i+1 << std::endl;
                students[i].get_data();
            }
        }
        std::cout << "Введите любой символ для продолжения -> ";
        std::cin >> Q;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    void editstudent(int N, int subchoise)
    {
        students[N-1].exist = 1;
        if (subchoise == 1)
        {   for (int i = 1; i < 13; i++)
            {
                char value[21];
                std::cout << std::endl << "Введите" << entlist[i-1] << ": ";
                std::cin >> value;
                students[N-1].set_data(i, &value[0]);
            }
        }
        if (subchoise == 2)
        {
            int snum;
            int stop;
            std::cout << std::endl << "Введите номер сессии :";
            std::cin >> snum;
            if (students[N-1].seslim < snum)
            {
                students[N-1].seslim = snum -1;
            }
            std::cout << std::endl << "Введите количество предметов :";
            std::cin >> stop;
            students[N-1].SetActivitySubjectLimit(snum-1,stop);
            for (int i = 1; i <= stop; i++)
            {
                char subvalue[21];
                char value;
                std::cout << std::endl << "Введите название предмета (лимит 21 символ): ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.getline(subvalue,21);
                std::cout << std::endl << "Введите оценку по этому предмету: ";
                std::cin >> value;
                students[N-1].set_activity(i, snum -1, &subvalue[0], value);
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    void delstudent(int killid)
    {
        students[killid].exist = 0;
    }
    void maketask()
    {
        std::string group;
        std::cout << "Введите группу -> ";
        std::cin >> group;
        int goodid[30];
        int maxgoodid = 0;
        int badid[30];
        int maxbadid = 0;
        for (int i = 0; i <= count; i++)
        {
            if (group == students[i].GetGroup())
            {
                students[i].taskworker();
                if (students[i].goodstudent)
                {
                    goodid[maxgoodid] = i;
                    maxgoodid++;
                }
                else
                {
                    badid[maxbadid] = i;
                    maxbadid++;
                }
            }
        }
        int max1 = goodid[0];
        int max2 = goodid[1];
        int min1 = goodid[0];
        int min2 = goodid[1];
        for (int i = 0; i < maxgoodid; i++)
        {
            if (students[goodid[i]].score  > students[max1].score )
            {
                max1 = goodid[i];
            }
            if(students[goodid[i]].score < students[min1].score)
            {
                min1 = goodid[i];
            }
        }
        for (int i = 0; i < maxgoodid; i++)
        {
            if (students[goodid[i]].score  > students[max2].score and goodid[i] != max1 )
            {
                max2 = goodid[i];
            }
            if(students[goodid[i]].score < students[min2].score and goodid[i] != min1)
            {
                min2 = goodid[i];
            }
        }
        std::cout << "Самые успевающие из хорошей группы: " << std::endl;
        students[max1].get_data();
        students[max2].get_data();
        std::cout << "Самые неуспевающие из хорошей группы: " << std::endl;
        students[min1].get_data();
        students[min2].get_data();


        max1 = badid[0];
        max2 = badid[1];
        min1 = badid[0];
        min2 = badid[1];
        for (int i = 0; i < maxbadid; i++)
        {
            if (students[badid[i]].score  > students[max1].score )
            {
                max1 = badid[i];
            }
            if(students[badid[i]].score < students[min1].score)
            {
                min1 = badid[i];
            }
        }
        for (int i = 0; i < maxbadid; i++)
        {
            if (students[badid[i]].score  > students[max2].score and badid[i] != max1 )
            {
                max2 = badid[i];
            }
            if(students[badid[i]].score < students[min2].score and badid[i] != min1)
            {
                min2 = badid[i];
            }
        }
        std::cout << "Самые успевающие из плохой группы: " << std::endl;
        students[max1].get_data();
        students[max2].get_data();
        std::cout << "Самые неуспевающие из плохой группы: " << std::endl;
        students[min1].get_data();
        students[min2].get_data();
        char Q[21];
        std::cout << "Введите любой символ для продолжения -> ";
        std::cin >> Q;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    }
    void menu()
    {
        clearscr
        std::string vertical (50, '*');
        int choise;
        std::cout  << std::setw(50) << vertical << std::endl;
        std::cout  << '*' << " Выберите действие:" << std::setw(30) << '*' << std::endl;
        std::cout  << '*' << " 1) Создать базу студентов " << std::setw(22) << '*' << std::endl;
        std::cout  << '*' << " 2) Вывести список студентов и их данные " << std::setw(8) << '*' << std::endl;
        std::cout  <<  '*' << " 3) Изменить данные студента "   << std::setw(20) << '*' << std::endl;
        std::cout  << '*' << " 4) Удалить студента " << std::setw(28) << '*' << std::endl;
        std::cout  << '*' << " 5) Сделать задание " << std::setw(29) << '*' << std::endl;
        std::cout  << '*' << " 6) Прочесть базу " << std::setw(31) << '*' << std::endl;
        std::cout  << '*' << " 0) Выход " << std::setw(39) << '*' << std::endl;
        std::cout  << std::setw(50) << vertical;
        std::cout << std::endl << "->";
        std::cin >> choise;
        tasker(choise);

    }
    mainmenu()
    {
        menu();
    }
    ~mainmenu()
    {
            if (tik == 1)
            {
                delete[] students;
                students = nullptr;
            }
    }
    void writedb()
    {
        std::ofstream file;
        file.open("db.bin", std::ios::binary);
        file << count << std::endl;
        for (int i=0; i <= count; i ++)
        {
            if (students[i].exist == 1)
            {
                file << students[i].GetSurname() << std::endl;
                file << students[i].GetName() << std::endl;
                file << students[i].GetPatronymic() << std::endl;
                file << students[i].GetBirthday() << std::endl;
                file << students[i].GetBirthmonth() << std::endl;
                file << students[i].GetBirthyear() << std::endl;
                file << students[i].GetEnterdate() << std::endl;
                file << students[i].GetDepartment() << std::endl;
                file << students[i].GetFaculty() << std::endl;
                file << students[i].GetGroup() << std::endl;
                file << students[i].GetGradebook() << std::endl;
                file << students[i].GetSex() << std::endl;
                file << students[i].seslim << std::endl;
                for (int b = 0; b <= students[i].seslim ;b++)
                {
                    file << students[i].GetActivitySubjectLimit(b) << std::endl;
                }
                for (int b = 0; b <=students[i].seslim ;b++)
                {
                    for (int c = 0; c <= students[i].GetActivitySubjectLimit(b); c++)
                    {
                        file << students[i].GetActivitySubject(b,c) << std::endl;
                    }
                    file << students[i].GetActivityValue(b) << std::endl;
                }
            }
        }
        file.close();
    }
    void readdb() {
    std::ifstream file("db.bin", std::ios::binary);
    int oldcount;
    std::string line;
    std::getline(file, line);
    std::istringstream iss(line);
    iss >> oldcount;
    count = oldcount;
    std::string surname, name, patronymic, birthday, birthmonth, birthyear, enterdate, department, faculty, group, gradebook, sex;
    int seslim, subjlim;
    students = new Student[oldcount];
    tik = 1;
    for (int i = 0; i < oldcount; i++) {
        if (file.eof())
            break;
        students[i].exist = 1;
        std::getline(file, surname);
        std::getline(file, name);
        std::getline(file, patronymic);
        std::getline(file, birthday);
        std::getline(file, birthmonth);
        std::getline(file, birthyear);
        std::getline(file, enterdate);
        std::getline(file, department);
        std::getline(file, faculty);
        std::getline(file, group);
        std::getline(file, gradebook);
        std::getline(file, sex);
        students[i].set_data(1, surname.c_str());
        students[i].set_data(2, name.c_str());
        students[i].set_data(3, patronymic.c_str());
        students[i].set_data(4, birthday.c_str());
        students[i].set_data(5, birthmonth.c_str());
        students[i].set_data(6, birthyear.c_str());
        students[i].set_data(7, enterdate.c_str());
        students[i].set_data(8, department.c_str());
        students[i].set_data(9, faculty.c_str());
        students[i].set_data(10,group.c_str());
        students[i].set_data(11, gradebook.c_str());
        students[i].set_data(12, sex.c_str());
        std::string line;
        std::getline(file, line);
        std::istringstream iss(line);
        iss >> seslim;
        students[i].seslim = seslim;
        for (int b = 0; b <= seslim; b++) {
            std::string line;
            std::getline(file, line);
            std::istringstream iss(line);
            iss >> subjlim;
            students[i].SetActivitySubjectLimit(b, subjlim);
        }
        std::string subject, value;
        for (int b = 0; b <= seslim; b++) {
            for (int c = 0; c <= students[i].GetActivitySubjectLimit(b); c++) {
                std::getline(file, subject);
                students[i].set_activity(c+1, b, subject.c_str(), '0');
            }
            std::getline(file, value);
            students[i].set_activity(11, b, value.c_str(), '0');
        }
    }
    file.close();
}
};



