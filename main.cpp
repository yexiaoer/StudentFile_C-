#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Student{

private:
    string name;
    string ID;
    string year;
    string gender;

public:
    Student(string n, string id, string y, string g)
    {
        name = n;
        ID = id;
        year = y;
        gender = g;
    }

    string getName() {return name;}
    string getID() {return ID;}
    string getYear() {return year;}
    string getGender() {return gender;}

    void setName(string n) {name = n;}
    void setID(string n) {ID = n;}
    void setYear(string y) {year = y;}
    void setGender(string g) {gender = g;}
};


vector<Student> list;
int sizeLimitID = 20;
int sizeLimitName = 20;
int sizeLimitYear = 20;
int sizeLimitGender = 20;


string fillStringWithSpace(string temp, int length)
{
    string filledString = temp;

    for(int i = 0; i < (length - temp.size()); i++){
        filledString += " ";
    }

    return filledString;
}

string getValidID()
{
    string ID = "";
    bool validID = false;

    while (!validID){
        cout << "\tEnter Student ID (9 digits) :=> ";
        //ID = cin.get();
        cin >> ID;
        bool containNotInt = true;
        for(int i = 0;  i < ID.size(); ++i)
        {
            if(!isdigit(ID.at(i)))
                containNotInt = false;
        }

        if (ID.size() > 9)
            cout << "\tID too long (9 digits)" << endl;
        if (ID.size() < 9)
            cout << "\tID too short (9 digits) " << endl;
        if (containNotInt == false)
            cout << "\tID contain non integer " << endl;
        int findID = 0;
        for(int i = 0;  i <list.size(); ++i)
        {
            if(list[i].getID() == ID){
                findID = 1;
                break;
            }
        }
        if (findID)
            cout<< "\tStudent already exist" << endl;

        if(ID.size() == 9 && containNotInt == true && !findID)
            return ID;
    }
    return ID;
}

string getValidName()
{
    string name = "";
    bool validName = false;

    while (!validName){
        cout << "\tEnter Student Name (first,last) :=> ";
        //ID = cin.get();
        cin >> name;
        bool containNonChar = false;

        if(name.length() > sizeLimitName - 1)
        {
            cout << "\tName too long, invalid :=> ";
        }
        else
        {
            for(int i = 0;  i < name.size(); ++i)
            {
                int temp = name.at(i);
                if (name.at(i) ==' ')
                {
                    containNonChar = true;
                    break;
                }
                else if ((temp >= 65 && temp <= 90) || (temp >= 97 && temp <= 122) || temp == 44)
                    containNonChar = false;
                else{
                    containNonChar = true;
                    break;
                }
            }
            if (containNonChar == true)
                cout << "\tName contain non character " << endl;

            if(containNonChar == false)
                return name;
        }
    }
    return name;
}

string getValidGender()
{
    string gender = "";
    bool validGender = false;

    while (!validGender){

        cout << "\tEnter Student Gender (female or male) :=> " ;
        cin >> gender;

        if(gender == "female" || gender =="male")
            return gender;

        cout << "\tWrong input \n";
    }
    return gender;
}

string getValidYear()
{
    string year = "";
    bool validYear = false;

    while (!validYear){
        cout << "\tEnter Student Year (freshman,sophomore,junior or senior):=> ";
        //ID = cin.get();
        cin >> year;

        if((year == "freshman") || year == "sophomore" || year == "junior" || year == "senior")
            return year;

        cout << "\tWrong input \n";
    }
    return year;

}

bool checkIfStudentAlreadyExist(string ID)
{
    int findID = 0;
    for(int i = 0;  i <list.size(); ++i)
    {
        if(list[i].getID() == ID){
            findID = 1;
            break;
        }
    }
    if (findID)
    {
        cout<< "\tStudent already exist " << endl;
        cout<< "\tStudent ID: " << ID << endl;

        return true;
    }
    return false;
}

void saveFile()
{
    string input;
    ofstream studentFile;

    cout << "\n \tEnter the name of file you want to save:=> " ;
    //input = cin.get();
    cin >> input;
    cout << "\n Your choice: " << input << endl;

    studentFile.open(input);
    studentFile << fillStringWithSpace("Students ID", sizeLimitID)
                << fillStringWithSpace("Student Name", sizeLimitName)
                << fillStringWithSpace("Student Year", sizeLimitYear)
                << fillStringWithSpace("Student Gender", sizeLimitGender) << endl;
    for(int i = 0;  i <list.size(); ++i)
    {
        studentFile << "" << fillStringWithSpace(list[i].getID(), sizeLimitID) << ""
                    << "" << fillStringWithSpace(list[i].getName(), sizeLimitName) << ""
                    << "" << fillStringWithSpace(list[i].getYear(), sizeLimitYear) << ""
                    << "" << fillStringWithSpace(list[i].getGender(), sizeLimitGender) << endl;
    }
    studentFile.close();
    cout<< "\tFile Saved " << endl;

}



void loadFile()
{
    string input;
    string line;
    string name;
    string ID;
    string year;
    string gender;

    cout << "\n \tEnter the name of file you want to open:=> " ;
    //input = cin.get();
    cin >> input;
    cout << "\n Your choice: " << input << endl;
    ifstream studentFile (input);

    if (studentFile.is_open())
    {
        getline(studentFile, line);
        while (getline(studentFile, line))
        {

            int pos = 0;
            string temp = "";

            while (pos < line.length() && line.at(pos) != ' ')
            {
                temp += line.at(pos);
                pos++;
            }
            //cout << temp << '\n';
            ID = temp;
            temp = "";
            if (checkIfStudentAlreadyExist(ID))
                cout << "\tWill not add this student" << '\n';
            else{

                while (pos < line.length() && line.at(pos) == ' '){
                    pos++;
                }
                while (pos < line.length() && line.at(pos) != ' ')
                {
                    temp += line.at(pos);
                    pos++;
                }
                //cout << temp << '\n';
                name = temp;
                temp = "";
                while (pos < line.length() && line.at(pos) == ' '){
                    pos++;
                }
                while (pos < line.length() &&  line.at(pos) != ' ')
                {
                    temp += line.at(pos);
                    pos++;
                }
                //cout << temp << '\n';
                year = temp;
                temp = "";
                while (pos < line.length() && line.at(pos) == ' '){
                    pos++;
                }
                while (pos < line.length() && line.at(pos) != ' ')
                {
                    temp += line.at(pos);
                    pos++;
                }
                gender = temp;

                Student s(name, ID, year, gender);

                list.push_back(s);
                cout << "\tStudent ID :=> " << ID << " added! "<< endl;
            }
        }
    }
    studentFile.close();
}

void printAllStudentsByYear()
{
    string year;
    cout << "\n \tEnter Student Year(freshman,sophomores,juniors or senior) :=> " ;
    cin >> year;

    if((year == "freshman") || year == "sophomore" || year == "junior" || year == "senior")
    {
        cout << "\t--------------------- " << year << "---------------------" << endl;
        cout << "\t" << fillStringWithSpace("Students ID", sizeLimitID)
         << "\t" << fillStringWithSpace("Student Name", sizeLimitName)<< endl;
        for(int i = 0;  i <list.size(); ++i)
        {
            if(list[i].getYear() == year)
            {
                cout << "\t" << fillStringWithSpace(list[i].getID(), sizeLimitID) << ""
                     << "\t" << fillStringWithSpace(list[i].getName(), sizeLimitName) << endl;
            }
        }
    }
    else
        cout << "\tWrong year of study! " << endl;
}

void printAllStudents()
{
    //string input;
    //cout << "\n \tEnter Student Year :=> " ;
    //input = cin.get();
   // cin >> input;

    cout << "\t---------------------freshman list---------------------" << endl;
    cout << "\t" << fillStringWithSpace("Students ID", sizeLimitID)
         << "\t" << fillStringWithSpace("Student Name", sizeLimitName)<< endl;

    for(int i = 0;  i <list.size(); ++i)
    {
        if(list[i].getYear() == "freshman")
        {
            cout << "\t" << fillStringWithSpace(list[i].getID(), sizeLimitID) << ""
                 << "\t" << fillStringWithSpace(list[i].getName(), sizeLimitName) << endl;
        }
    }

    cout << "\n\t--------------------sophomore list---------------------" << endl;
    cout << "\t" << fillStringWithSpace("Students ID", sizeLimitID)
         << "\t" << fillStringWithSpace("Student Name", sizeLimitName)<< endl;

    for(int i = 0;  i <list.size(); ++i)
    {
        if(list[i].getYear() == "sophomore")
        {
            cout << "\t" << fillStringWithSpace(list[i].getID(), sizeLimitID) << ""
                 << "\t" << fillStringWithSpace(list[i].getName(), sizeLimitName) << endl;
        }
    }

    cout << "\n\t--------------------junior list--------------------------" << endl;
    cout << "\t" << fillStringWithSpace("Students ID", sizeLimitID)
         << "\t" << fillStringWithSpace("Student Name", sizeLimitName)<< endl;

    for(int i = 0;  i <list.size(); ++i)
    {
        if(list[i].getYear() == "junior")
        {
            cout << "\t" << fillStringWithSpace(list[i].getID(), sizeLimitID) << ""
                 << "\t" << fillStringWithSpace(list[i].getName(), sizeLimitName) << endl;
        }
    }

    cout << "\n\t---------------------senior list-------------------------" << endl;
    cout << "\t" << fillStringWithSpace("Students ID", sizeLimitID)
         << "\t" << fillStringWithSpace("Student Name", sizeLimitName)<< endl;

    for(int i = 0;  i <list.size(); ++i)
    {
        if(list[i].getYear() == "senior")
        {
            cout << "\t" << fillStringWithSpace(list[i].getID(), sizeLimitID) << ""
                 << "\t" << fillStringWithSpace(list[i].getName(), sizeLimitName) << endl;
        }
    }

}

void printVector()
{

    cout << "\t" <<fillStringWithSpace("Students ID", sizeLimitID)
         << fillStringWithSpace("Student Name", sizeLimitName)
         << fillStringWithSpace("Student Year", sizeLimitYear)
         << fillStringWithSpace("Student Gender", sizeLimitGender) << endl;
    for(int i = 0;  i <list.size(); ++i)
    {
        cout  << "\t" << fillStringWithSpace(list[i].getID(), sizeLimitID) << ""
              << fillStringWithSpace(list[i].getName(), sizeLimitName) << ""
              << fillStringWithSpace(list[i].getYear(), sizeLimitYear) << ""
              << fillStringWithSpace(list[i].getGender(), sizeLimitGender) << endl;
    }
}

void printStudentInfo()
{
    string input;
    cout << "\n \tEnter Student ID :=> " ;
    //input = cin.get();
    cin >> input;
    int findID = 0;
    cout << "\t" << fillStringWithSpace("Students ID", sizeLimitID)
         << fillStringWithSpace("Student Name", sizeLimitName)
         << fillStringWithSpace("Student Year", sizeLimitYear)
         << fillStringWithSpace("Student Gender", sizeLimitGender) << endl;
    for(int i = 0;  i <list.size(); ++i)
    {
        if(list[i].getID() == input)
        {
            cout << "\t" << fillStringWithSpace(list[i].getID(), sizeLimitID) << ""
                 << "" << fillStringWithSpace(list[i].getName(), sizeLimitName) << ""
                 << "" << fillStringWithSpace(list[i].getYear(), sizeLimitYear) << ""
                << "" << fillStringWithSpace(list[i].getGender(), sizeLimitGender) << endl;
            findID = 1;
            break;
        }
    }
    if (!findID)
        cout<< "\tCan't find this Student" << endl;
}

void editStudent()
{
    string name;
    string ID;
    string year;
    string gender;
    string input;
    cout << "\n \tEnter Student ID :=> " ;
    cin >> input;
    //input = cin.get();
    int findID = 0;
    int i;
    for(i = 0;  i <list.size(); ++i)
    {
        if(list[i].getID() == input){
            findID = 1;
            break;
        }
    }
    int reset = -1;
    if (findID)
    {
        cout << "\t Student Found! " << endl;
        while (reset != 5)
        {
            cout << "\tStudent ID :=> " << list[i].getID() << endl;
            cout << "\tStudent name :=> " << list[i].getName() << endl;
            cout << "\tStudent year :=> " << list[i].getYear() << endl;
            cout << "\tStudent gender :=> " << list[i].getGender() << endl;

            cout << "\n\t 1. Reset Name" << endl;
            cout << "\t 2. Reset ID" << endl;
            cout << "\t 3. Reset Year" << endl;
            cout << "\t 4. Reset Gender" << endl;
            cout << "\t 5. Finish Reset" << endl;
            cout << "\tSelect Your Choice :=> " ;
            cin >> reset;
            //reset = cin.get();
            cout << "\tYour choice: " << reset << endl;

            switch(reset)
            {
                case 1: name = getValidName();
                        list[i].setName(name);
                        cout << "\tData changed" << endl;
                        break;
                case 2: ID = getValidID();
                        list[i].setID(ID);
                        cout << "\tData changed" << endl;
                        break;
                case 3: year = getValidYear();
                        list[i].setYear(year);
                        cout << "\tData changed" << endl;
                        break;
                case 4: gender = getValidGender();
                        list[i].setGender(gender);
                        cout << "\tData changed" << endl;
                        break;
                case 5: cout << "\tStudent updated! " ;
                        break;
                default: cout << "Wrong inputs";
                        break;
          }
        }
    }
    else
        cout<< "\t Cannot find student!" << endl;
}

void deleteStudent()
{
    string input;
    cout << "\n \tEnter Student ID :=> " ;
    cin >> input;
    //input = cin.get();
    int findID = 0;
    for(int i = 0;  i <list.size(); ++i)
    {
        if(list[i].getID() == input)
        {
            list.erase(list.begin()+i);
            cout << "\tStudent found and deleted" << endl;
            findID = 1;
            break;
        }
    }
    if (!findID)
        cout<< "\tCan't find this Student" << endl;
}

void addStudent()
{
    string name;
    string ID;
    string year;
    string gender;

    ID = getValidID();
    name = getValidName();
    year = getValidYear();
    gender = getValidGender();

    Student s(name, ID, year, gender);

    list.push_back(s);

    cout << "\tStudent added" << endl;

}

int main()
{
    bool t = true;
    while (t)
    {
        cout << "\n====== STUDENT DATABASE MANAGEMENT SYSTEM ======\n" << endl;
        cout << "\t 1. Add Student                                                    " << endl;
        cout << "\t 2. Delete Student                                                 " << endl;
        cout << "\t 3. Modify Student Info                                            " << endl;
        cout << "\t 4. Print Student Info                                             " << endl;
        cout << "\t 5. Print All Students from (freshman,sophomores,juniors and senior)" << endl;
        cout << "\t 6. Print All Students from (freshman,sophomores,juniors or senior)" << endl;
        cout << "\t 7. Load a File                                                    " << endl;
        cout << "\t 8. Print all Student                                              " << endl;
        cout << "\t 9. Save the Students to the file                                  " << endl;
        cout << "\t 10. Exit the Program                                  " << endl;
        cout << "\t Select Your Choice :=> " ;

        int input;

        while (!(cin >> input))
        {
            cin.clear();

            while(cin.get() != '\n')
                continue;

            cout << "\n\t Wrong Inputs, please enter again";
            cout << "\n\t Select Your Choice :=> " ;
        }

        switch(input)
        {
            case 1: addStudent();
                    break;
            case 2: deleteStudent();
                    break;
            case 3: editStudent();
                    break;
            case 4: printStudentInfo();
                    break;
            case 5: printAllStudents();
                    break;
            case 6: printAllStudentsByYear();
                    break;
            case 7: loadFile();
                    break;
            case 8: printVector();
                    break;
            case 9: saveFile();
                    break;
            case 10: t = false;
                     break;
            default: cout << "\t Wrong Inputs";
                    break;

        }
    }
}
