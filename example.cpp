#include <iostream>
#include <string>
#include "long_jmper.hpp"

corof::long_jmper suspend_one_integer()
{
    std::cout<< "                   suspend_one_integer in\n";
    co_await std::suspend_always();
    std::cout<< "                   suspend_one_integer return\n";
    co_return 1;
}

corof::long_jmper suspend_one_string()
{
    std::cout<< "               suspend_one_string in\n";
    co_await std::suspend_always();
    std::cout<< "               suspend_one_string return\n";
    co_return std::string("1");
}

corof::long_jmper suspend_two()
{
    std::cout<< "           suspend_two -> suspend_one_integer #1\n";
    auto a = co_await suspend_one_integer().eval<int>();
    std::cout<< "           suspend_two -> suspend_one_string #2\n";
    auto b = co_await suspend_one_string().eval<std::string>();
    std::cout<< "           suspend_two return\n";
    co_return a + std::stoi(b);
}

corof::long_jmper suspend_five()
{
    std::cout<< "       suspend_five -> suspend_two #1\n";
    auto a = co_await suspend_two().eval<int>();
    std::cout<< "       suspend_five -> suspend_one_integer #2\n";
    auto b = co_await suspend_one_integer().eval<int>();
    std::cout<< "       suspend_five -> suspend_two #3\n";
    auto c = co_await suspend_two().eval<int>();
    std::cout<< "       suspend_five return\n";
    co_return a + b + c;
}

corof::long_jmper run()
{
    std::cout<< "   run -> suspend_two #1\n";
    auto a = co_await suspend_two().eval<int>();
    std::cout<< "   run -> suspend_one_integer #2\n";
    auto b = co_await suspend_one_integer().eval<int>();
    std::cout<< "   run -> suspend_five #3\n";
    auto c = co_await suspend_five().eval<int>();
    std::cout<< "   run -> suspend_one_integer #4\n";
    auto d = co_await suspend_one_integer().eval<int>();
    std::cout<< "   run -> suspend_two #5\n";
    auto e = co_await suspend_two().eval<int>();
    std::cout<< "   run return\n";
    co_return a + b + c + d + e;
}

int main()
{
    std::cout<< "main in\n";
    auto r = run();

    std::cout<< "main -> while\n";
    while(!r.poll_one()){
        std::cout<< "while loop->\n";
    }
    std::cout<< "r:" << r.eval<int>().await_resume() << "\n";

    std::cout<< "main out\n";
    return 0;
}
