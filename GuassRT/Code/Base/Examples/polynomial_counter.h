#include "../Count.h"
#include "../equation.h"
namespace Example
{
    //一个小小的多项式计算器;
    //#q
    inline void polynomial_counter()
    {
        std::cout << "polynomial counter 1.0\nby Htto 2017\n";
        std::string str_input;
        Htto::Count::UniversalCount<Htto::Polynomial> ct;
        while (1)
        {
            std::cin >> str_input;
            while (str_input == "#q")
            {
                return;
            }
            //这一步很重要,可以转换表达式比如(x+1)(x-1) 这样的式子UniversalCount是无法识别的需要变为(x+1)*(x-1)
            //警告:VS 2015 在debug模式下convert_expression函数会崩溃,具体原因不明请使用release模式.在Linux 下没有问题
            str_input = Htto::StringTools::convert_expression(str_input);
            try
            {
                ct.InfixToPostfix(Htto::Count::SimpleCount::PushToListP(str_input));
                std::cout << "=" + ct.Count().ToString() << std::endl;
            }
            catch (const std::exception&e)
            {
                std::cout << e.what() << std::endl;
                return;
            }
        }
    }
    inline void simple_equation()
    {
        std::cout << "simple equation 1.0\nby Htto 2017\n";
        std::string str_temp;
        std::vector<Htto::Fraction> result;
        while (1)
        {
            int index = 1;
            std::cin >> str_temp;
            if (str_temp == "#q")
                return;
            result = Htto::Count::Equation::solve(str_temp);
            if (result.size() == 0)
            {
                std::cout << "方程无实数根\n";
                continue;
            }
            for (const auto & a : result)
            {
                std::cout << std::string("x") << index << '=' << a.ToString() << "    ";
                index++;
            }
            std::cout << std::endl;
        }
    }
    //多元方程
    inline void polyv_equation()
    {
        std::cout << "mutiple variable equation 1.0\nby Htto 2017\n";
        std::vector<std::string> input;
        std::map<std::string, Htto::Fraction> result;
        std::string str_temp;
        while (1)
        {
            std::cin >> str_temp;
            if (str_temp == "#")
            {
                result = Htto::Count::Equation2::solve(input);
                break;
            }
            input.push_back(str_temp);
        }
        for (std::map<std::string, Htto::Fraction>::const_iterator it = result.begin(); it != result.end(); it++)
        {
            std::cout << it->first << "=" << it->second.ToString() << std::endl;
        }
    }
}