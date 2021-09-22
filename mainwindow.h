#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class Password{
public:
    QString password;
    size_t length;
    void Init(size_t n){
        password.clear();
        length=n;
        password.reserve(length);
        m_numbers={'0','1','2','3','4','5','6','7','8','9'};
        m_lower_case.clear();
        m_lower_case.reserve(26);
        for (char i='a';i<='z';++i){
            m_lower_case.push_back(i);
        }
        m_upper_case.clear();
        m_upper_case.reserve(26);
        for (char i='A';i<='Z';++i){
            m_upper_case.push_back(i);
        }
        m_special_chars.clear();
        m_special_chars.reserve(33);
        for (char i=32;i<48;++i){
            m_special_chars.push_back(i);
        }
        m_used={{'n',-1},{'l',-1},{'u',-1},{'s',-1}};
    }
    void generate(const bool& numbers,const bool& lower_case,const bool& upper_case,const bool& special){
        if (numbers==lower_case && lower_case==upper_case && upper_case==special && special==0){
            password="Nice Try Idiot";

        }
        else{
            if(numbers) m_used[0].second++;
            if(lower_case)m_used[1].second++;
            if(upper_case)m_used[2].second++;
            if(special)m_used[3].second++;
            std::srand(std::time(NULL));
            for(int i=0;i<(int)length;i++){
                //deciding what type to choose
                auto zeroCheck =[](QVector<QPair<char,int>>& m_){
                    for (QPair<char,int> a : m_){
                        if (a.second==0)
                            return a.first;
                    }
                    return (char)0;
                };
                char choosenCase=zeroCheck(m_used);
                if(i<5 || !choosenCase){
                    int j=std::rand()%m_used.size();
                    do{
                        j=std::rand()%m_used.size();
                    }
                    while (m_used[j].second==-1);
                    choosenCase=m_used[j].first;
                }
                update(simple,choosenCase,i);
            }
        }
    }
    void generateSpecific(int numbers,int lower_case, int upper_case, int special){
        m_used={{'n',numbers},{'l',lower_case},{'u',upper_case},{'s',special}};
        std::srand(std::time(NULL));
        for(int i=0;i<(int)length;i++){
            auto nonUsedType=[](QVector<QPair<char,int>>& m){
                for(QPair<char,int> a : m){
                    if(a.second!=0)
                        return a.first;
                }
                return (char)0;
            };
            char choosenCase=nonUsedType(m_used);
            if(i<=(int)length/2 || !choosenCase){
                int j=std::rand()%m_used.size();
                do
                    j=std::rand()%m_used.size();
                while(m_used[j].second==0);
            }
            update(specific,choosenCase,i);
        }
    }
private:
    enum cases {simple,specific};
    QVector<char> m_numbers;
    QVector<char> m_lower_case;
    QVector<char> m_upper_case;
    QVector<char> m_special_chars;
    QVector<QPair<char,int>> m_used;
    void update(cases ca,char& type,int& index){
        int j;
        char tmp;
        switch (type) {
        case 'n':
            j=std::rand()%m_numbers.size();
            tmp=m_numbers[j];
            password[index]=QChar(tmp);
            m_numbers.erase(m_numbers.begin()+j);
            if(ca==simple)
                ++m_used[0].second;
            else if(ca==specific)
                --m_used[0].second;
            break;
        case 'l':
            j=std::rand()%m_lower_case.size();
            tmp=m_lower_case[j];
            password[index]=QChar(tmp);
            m_lower_case.erase(m_lower_case.begin()+j);
            if(ca==simple)
                ++m_used[1].second;
            else if(ca==specific)
                --m_used[1].second;
            break;
        case 'u':
            j=std::rand()%m_upper_case.size();
            tmp=m_upper_case[j];
            password[index]=QChar(tmp);
            m_upper_case.erase(m_upper_case.begin()+j);
            if(ca==simple)
                ++m_used[2].second;
            else if(ca==specific)
                --m_used[2].second;
            break;
        case 's':
            j=std::rand()%m_special_chars.size();
            tmp=m_special_chars[j];
            password[index]=QChar(tmp);
            m_special_chars.erase(m_special_chars.begin()+j);
            if(ca==simple)
                ++m_used[3].second;
            else if(ca==specific)
                --m_used[3].second;
            break;
        }
    }
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_passwordLength_actionTriggered(int action);

    void on_charSpecial_stateChanged(int arg1);

    void on_charUpperCase_stateChanged(int arg1);

    void on_charNumbers_stateChanged(int arg1);

    void on_charLowerCase_stateChanged(int arg1);

    void on_commandLinkButton_clicked();

    void on_passwordLength_valueChanged(int value);

    void on_actionAbout_triggered();

    void on_actionReset_triggered();

    void on_actionExit_triggered();

    void on_lengthSpin2_valueChanged(int arg1);

    void on_lengthSlider2_valueChanged(int value);

    void on_charNumbers2_valueChanged(int arg1);

    void on_charUpper2_valueChanged(int arg1);

    void on_charLower2_valueChanged(int arg1);

    void on_charSpecial2_valueChanged(int arg1);

    void on_executeSpecific_clicked();

private:
    Ui::MainWindow *ui;
    int numbers=0, lower_case_letters=0,upper_case_letters=0,special=0;
    int length=8;
    Password generated;
};

#endif // MAINWINDOW_H
