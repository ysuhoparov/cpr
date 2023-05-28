#include <iostream>
#include <string>
#include <cpr\cpr.h>


/* Запросите с сервера HTML-страницу. Для этого изучите документацию о запросах, поддерживаемых
сервисом httpbin.org/html. Найдите там запрос, который выдаёт именно HTML-страницу.
    Затем сделайте запрос, явным образом используя заголовок accept: text/html. В полученном ответе
найдите заголовок статьи и выведите его в консоль.
    Рекомендации:
Заголовок статьи размещается между HTML-тегами <h1></h1>.
Для доступа к тексту ответа вам потребуется метод text класса cpr::Response.
Для поиска по тексту нужных HTML-тегов лучше использовать метод find. */



int main() {
    cpr::Response r;
    r = cpr::Get(cpr::Url("http://httpbin.org/html"),
                 cpr::Header({{"accept","text/html"}}));

       //std::cout << r.text;
//    std::string s(r.text);
//    size_t begH1 = s.find("<h1>")+4;
//    size_t endH1 = s.find("</h1", begH1 );
//    std::cout << s.substr(begH1 ,endH1- begH1);

    size_t begH1 = r.text.find("<h1>")+4;
    size_t endH1 = r.text.find("</h1", begH1 );
    std::cout << r.text.substr(begH1 ,endH1- begH1);


    return 0;
}
