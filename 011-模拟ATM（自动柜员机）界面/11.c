#include <stdio.h>
#include <conio.h> // _getch
#include <stdlib.h> // system
void clrscr() { system("cls"); }

int main() {
  char SelectKey, CreditMoney, DebitMoney;
  while (1) {
    do {
      clrscr();
      puts("=========================");
      puts("|  Please select key:   |");
      puts("|  1. Quary             |");
      puts("|  2. Credit            |");
      puts("|  3. Debit             |");
      puts("|  4. Return            |");
      puts("=========================");
      SelectKey = _getch();
    } while (
      SelectKey != '1' &&
      SelectKey != '2' &&
      SelectKey != '3' &&
      SelectKey != '4'
    );
    switch (SelectKey) {
      case '1': // Quary
        clrscr();
        puts("================================");
        puts("|    Your balance is $1000.    |");
        puts("|  Press any key to return...  |");
        puts("================================");
        _getch();
        break;

      case '2': // Credit
        do {
          clrscr();
          puts("==================================");
          puts("|   Please select Credit money:  |");
          puts("|   1. $50                       |");
          puts("|   2. $100                      |");
          puts("|   3. Return                    |");
          puts("==================================");
          CreditMoney = _getch();
        } while (
          CreditMoney != '1' &&
          CreditMoney != '2' &&
          CreditMoney != '3'
        );
        switch (CreditMoney) {
          case '1':
              clrscr();
              puts("=========================================");
              puts("|  Your Credit money is $50,Thank you!  |");
              puts("|         Press any key to return...    |");
              puts("=========================================");
              _getch();
              break;
          case '2':
              clrscr();
              puts("==========================================");
              puts("|  Your Credit money is $100,Thank you!  |");
              puts("|         Press any key to return...     |");
              puts("==========================================");
              _getch();
              break;
          case '3':
              break;
        } // CreditMoney
        break;

      case '3': // Debit
        do {
          clrscr();
          puts("====================================");
          puts("|   Please select Debit money:     |");
          puts("|   1. $50                         |");
          puts("|   2. $100                        |");
          puts("|   3. $500                        |");
          puts("|   4. $1000                       |");
          puts("|   5. Return                      |");
          puts("====================================");
          DebitMoney = _getch();
        } while (
          DebitMoney != '1' &&
          DebitMoney != '2' &&
          DebitMoney != '3' &&
          DebitMoney != '4' &&
          DebitMoney != '5'
        );
        switch (DebitMoney) {
          case '1':
            clrscr();
            puts("===========================================");
            puts("|   Your Debit money is $50,Thank you!    |");
            puts("|        Press any key to return...       |");
            puts("===========================================");
            _getch();
            break;
          case '2':
            clrscr();
            puts("===========================================");
            puts("|   Your Debit money is $100,Thank you!   |");
            puts("|        Press any key to return...       |");
            puts("===========================================");
            _getch();
            break;
          case '3':
            clrscr();
            puts("===========================================");
            puts("|   Your Debit money is $500,Thank you!   |");
            puts("|        Press any key to return...       |");
            puts("===========================================");
            _getch();
            break;
          case '4':
            clrscr();
            puts("===========================================");
            puts("|   Your Debit money is $1000,Thank you!  |");
            puts("|        Press any key to return...       |");
            puts("===========================================");
            _getch();
            break;
          case '5':
            break;
        } // DebitMoney
        break;

      case '4': // return
        clrscr();
        puts("================================");
        puts("|   Thank you for your using!  |");
        puts("|            Good bye!         |");
        puts("================================");
        return 0;
    } // switch (SelectKey)
  } // while (1)

  return 0;
} // main()