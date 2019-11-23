#include <iostream>
#include <vector>
#include <map>
#include <string>

template<typename T>
std::ostream& operator<< (std::ostream& os, const std::vector<T>& vec) {
    // Custom printing operator overloading for vectors
    typename std::vector<T>::const_iterator it;
    for(it = vec.begin(); it != vec.end(); ++it) {
        os << " " << *it;
    }
    return os;
}


int main()
{
    // Expects student names and grades as input.
    // Collects the grades from the same student to their vector

    const std::string ESC = "quit";
    std::string name;
    std::vector<std::string> names;
    double grade;
    std::vector<double> grades;

    typedef std::vector<std::string>::iterator string_it;
    std::map<std::string, std::vector<double>> mean_grades;

    std::cout << std::endl << "Enter Student Name:" << std::endl;
    while(std::cin >> name)
    {
        if(name != ESC)
        {
            names.push_back(name);
            std::cout << "Hello " << name << "! Please enter grade: " << std::endl;
            std::cin >> grade;
            grades.push_back(grade);
            std::cout << std::endl << "Enter Student Name:" << std::endl;
        }
        else
        {
            break;
        }
    }
    std::cout << std::endl << std::endl;

    int count = 0;
    for(string_it it = names.begin(); it != names.end(); ++it)
    {
        mean_grades[*it].push_back(grades[count]);
        ++count;
    }

    for(std::map<std::string, std::vector<double>>::iterator map_it = mean_grades.begin(); map_it != mean_grades.end(); ++map_it)
    {
        std::cout << "Grades of " << map_it->first << std::endl;
        std::cout << map_it->second << std::endl;
    }
    return 0;
}