#pragma once

#include <locale>
#include <iomanip>
#include <chrono>
#include <algorithm>

namespace recipe_7_03
{
   void execute()
   {
      {
         auto loc_def = std::locale{};
#ifdef _WIN32
         auto loc_us = std::locale{ "English_US.1252" };
#else
         auto loc_us = std::locale{ "en_US.utf8" };
#endif
         auto loc1 = std::locale{ loc_def, new std::collate<wchar_t> };
         auto loc2 = std::locale{ loc_def, loc_us, std::locale::collate };
      }

      auto now = std::chrono::system_clock::now();
      auto stime = std::chrono::system_clock::to_time_t(now);
      auto ltime = std::localtime(&stime);

      std::vector<std::string> names{ "John", "adele", "�ivind", "Fran�ois", "Robert", "�ke" };
      auto sort_and_print = [](std::vector<std::string> v, std::locale const & loc)
      {
         std::sort(v.begin(), v.end(), loc);
         for (auto const & s : v) std::cout << s << ' ';
         std::cout << std::endl;
      };

      {
#ifdef _WIN32
         auto loc = std::locale("German_Germany.1252");
#else
         auto loc = std::locale("de_DE.utf8");
#endif
         std::cout.imbue(loc);

         std::cout << 1000.50 << std::endl; // 1.000,5
         std::cout << std::showbase << std::put_money(1050) << std::endl; // 10,50 �
         std::cout << std::put_time(ltime, "%c") << std::endl; // So 04 Dez 2016 17:54:06 JST

         sort_and_print(names, loc); // adele �ke Fran�ois John �ivind Robert
      }

      {
         auto loc = std::locale("");
         std::cout.imbue(loc);

         std::cout << 1000.50 << std::endl; // 1,000.5
         std::cout << std::showbase << std::put_money(1050) << std::endl; // $10.50
         std::cout << std::put_time(ltime, "%c") << std::endl; // Sun 04 Dec 2016 05:54:06 PM JST

         sort_and_print(names, loc); // adele �ke Fran�ois John �ivind Robert
      }

      {
#ifdef _WIN32
         std::locale::global(std::locale("Swedish_Sweden.1252"));
#else
         std::locale::global(std::locale("sv_SE.utf8"));
#endif

         auto loc = std::locale{};
         std::cout.imbue(loc);

         std::cout << 1000.50 << std::endl; // 1 000,5
         std::cout << std::showbase << std::put_money(1050) << std::endl; // 10,50 kr
         std::cout << std::put_time(ltime, "%c") << std::endl; // s�n  4 dec 2016 18:02:29

         sort_and_print(names, loc); // adele Fran�ois John Robert �ke �ivind
      }

      {
         auto loc = std::locale::classic();
         std::cout.imbue(loc);

         std::cout << 1000.50 << std::endl; // 1000.5
         std::cout << std::showbase << std::put_money(1050) << std::endl; // 1050
         std::cout << std::put_time(ltime, "%c") << std::endl; // Sun Dec  4 17:55:14 2016

         sort_and_print(names, loc); // Fran�ois John Robert adele �ke �ivind
      }
   }
}