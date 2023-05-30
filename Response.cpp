#include <iostream>
#include <vector>
#include <string>
#include <cpr\cpr.h>

/* 
https://github.com/libcpr/ 

Запрос к сервису httpbin.org, отправив несколько дополнительных аргументов с данными.
    Все названия аргументов и их значения строковые и принимаются от пользователя.
 Пользователь последовательно вводит их названия вместе со значениями, пока не встретится
 аргумент с названием “post” или “get”, что будет означать, что ввод аргументов закончен
 и требуется отправить их на сервер выбранным способом.
    Если пользователь выбрал “post”, то выполняется POST-запрос и аргументы отправляются
 POST-способом (как форма). Если “get”, то выполняется GET-запрос с GET-аргументами (прямо в URL).
    По результатам выполнения запроса выведится ответ сервера в стандартную консоль, поля form или args,
 в зависимости от типа запроса в которых  перечислены введённые  аргументы.
 */

template <class T>
void getValue(std::string prompt, T& value) {
//input data through  std::cin
    do {
        std::cout << prompt;
        std::cin >> value;
        if (!std::cin.fail()) break;

        std::cin.clear();
        std::cin.ignore(32767, '\n');
        std::cout << "Try again\n";

    } while (1);

    std::string endLine;
    std::getline(std::cin, endLine);
}


int main() {

    std::string key, val;
    std::vector<cpr::Pair> uparams;
    do {
        getValue("Enter key: ", key);
        if(key == "get" or key == "post") break;
        getValue("Enter value: ", val);
        uparams.push_back(cpr::Pair((std::string)key, (std::string)val));
    } while(1);

    std::cout << "\n";
    for(auto pr : uparams)
        std::cout << pr.key <<" : "<<pr.value <<"\n";

    cpr::Response r;
    std::string paramrq;
    for(auto p : uparams)

    if(key == "get") {
        paramrq = "http://httpbin.org/get?";
        for(auto p : uparams)
            paramrq = paramrq + p.key + "=" +p.value + "&";
        r = cpr::Get(cpr::Url(paramrq.substr (0,paramrq.size()-1)));
    }

    if(key == "post") {

        std::vector<cpr::Pair>::iterator itBegin = uparams.begin();
        std::vector<cpr::Pair>::iterator itEnd = uparams.end();

        r = cpr::Post(cpr::Url("http://httpbin.org/post"),
                      cpr::Payload( itBegin, itEnd));
    }

    std::cout << r.text;

    return 0;
}
