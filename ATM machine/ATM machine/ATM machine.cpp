#include <iostream>
#include <algorithm>

using namespace std;

int nominal[] = { 100,200,500,1000,5000 }; // Различные номиналы купюр в банкомате
int kolichestvo[] = { 10,10,10,10,10 }; // Количество купюр каждого номинала в банкомате
int used[] = { 0,0,0,0,0 }; // Количество выданных купюр каждого номинала
const int j = 5; // Количество номиналов купюр
const int t = 3; // Количество возможных стандартных сумм для снятия
int sum = 0; // Текущая сумма в банкомате
int Standard_sum[] = { 7000,13000,17000 }; // Стандартные суммы для снятия, отличающаяся от текущих номиналов
int Standard_user;
int input;
int cash;
int check = 100;
int one_time_limit = 23000; // Разовый лимит выдачи наличных
int daily_limit = 65000; // Дневной лимит выдачи наличных
int bills_limit;
int max_bills_limit = 10; // Лимит разовой выдачи купюр 

// Предупреждение для возможности добавления других команд
void ComingSoon()
{
	cout << "Feature is will be available soon.\n";
}
// Окно вывода главного меню
void main_menu()
{
	cout << "Press '1' to withdraw your own sum \n"
		<< "Press '2' to withdraw a standard sum \n"
		<< "Press '3' to check your balance \n"
		<< "Press '-1' to exit \n";
}
// Окно вывода для перехода в главное меню
void return_main_menu()
{
	cout << "Press '0' to return to the main menu \n";
}


// Выдача введённой пользователем суммы денег крупными купюрами
int WithdrawalOwnSumLargeBills()
{
	sum = 0;
	bills_limit = 0;
	// Определение текущей суммы в банкомате
	for (int i = 0; i < j; i++) {
		sum = sum + (nominal[i] * kolichestvo[i]);
		used[i] = 0;
	}
	cout << "\nCurrently available for withdrawals sum is:\n";
	cout << sum;
	int cash;
	int BanknotesNumber[] = { 0,0,0,0,0 };
	cout << "\nEnter a sum for withdrawal:\n";
	// Ввод пользователем суммы для вывода
	cin >> cash;
	// Если требуемой суммы нет в банкомате, и она не может быть выдана - вывод на экран предупреждения
	if ((cash > sum) || (cash % check != 0))
	{
		cout << "Sorry, this sum is unavailable for withdrawal" << '\n';
		exit(10);
	}
	// Проверка соблюдения разового лимита снятия наличных
	if (cash > one_time_limit)
	{
		cash = min(cash, one_time_limit);
		cout << "Your cash request is over then one time withdrawal and now you will get " << one_time_limit << " rubles\n";
	}
	// Проверка соблюдения дневного лимита снятия наличных
	if (cash > daily_limit)
	{
		cash = min(cash, daily_limit);
		cout << "Your cash request is over then daily withdrawal and now you will get " << daily_limit << " rubles\n";
	}
	daily_limit = daily_limit - cash;
	// // Определение необходимого количества купюр каждого номинала для снятия требуемой суммы
	for (int i = j - 1; i >= 0; --i)
	{
		while (cash >= nominal[i])
		{
			if (bills_limit >= max_bills_limit) cash = 0;
			if (cash / nominal[i] <= kolichestvo[i])
			{
				used[i] = cash / nominal[i];
				cash = cash - nominal[i] * used[i];
				sum = sum - nominal[i] * used[i];
				bills_limit += used[i];
			}
			else
			{
				used[i] = kolichestvo[i];
				cash = cash - nominal[i] * used[i];
				sum = sum - nominal[i] * used[i];
				bills_limit += used[i];
				i--;
			}
		}
		// Определение необходимого количества купюр каждого номинала для снятия требуемой суммы
		kolichestvo[i] = kolichestvo[i] - used[i];
	}
	// В случае, если превышен разовый лимит на количество выданных купюр - вывод сообщения об этом 
	if (bills_limit >= max_bills_limit)
		cout << "\nSorry, bill limit of one withdrawal is " << max_bills_limit << "\n";
	// Вывод на экран информации о том, сколько купюр каждого номинала было выдано
	for (int i = j - 1; i >= 0; --i) {

		for (int i = 0; i < j; i++) {
			if (used[i] == 0) continue;
			cout << "Payed " << used[i] << " bills of nominal " << nominal[i] << endl;
		}
		// Определение текущей суммы в банкомате после снятия наличных
		cout << "Currently available for withdrawals sum is:\n";
		cout << sum;
		return sum;
	}
}

// Выдача стандартной суммы денег, отличающейся от текущих номиналов купюр
int WithdrawalStandardSum()
{
	int choice;
	sum = 0;
	bills_limit = 0;
	for (int i = 0; i < j; i++) {
		sum = sum + (nominal[i] * kolichestvo[i]);
	}
	cout << "\nCurrently available for withdrawals sum is:\n";
	// Определение текущей суммы в банкомате
	cout << sum;
	cout << '\n';
	int BanknotesNumber[] = { 0,0,0,0,0 };
	for (int i = 0; i < t; i++)
	{
		if (Standard_sum[i] != 0)
			cout << "Press '" << i << "' to withdrawal a " << Standard_sum[i] << " rubles\n";
	}
	cin >> choice;
	cash = Standard_sum[choice]; // Определение желаемой стандартной суммы для снятия
	// Если требуемой суммы нет в банкомате, и она не может быть выдана - вывод на экран предупреждения
	if ((cash > sum) || (cash % check != 0))
	{
		cout << "Sorry, this sum is unavailable for withdrawal" << '\n';
		exit(0);
	}
	// Проверка соблюдения разового лимита снятия наличных
	if (cash > one_time_limit)
	{
		cash = min(cash, one_time_limit);
		cout << "Your cash request is over then one time withdrawal and now you will get " << one_time_limit << " rubles\n";
	}
	// Проверка соблюдения дневного лимита снятия наличных
	if (cash > daily_limit)
	{
		cash = min(cash, daily_limit);
		cout << "Your cash request is over then daily withdrawal and now you will get " << daily_limit << " rubles\n";
	}
	daily_limit = daily_limit - cash;
	// Определение необходимого количества купюр каждого номинала для снятия требуемой суммы
	for (int i = j - 1; i >= 0; --i)
	{
		while (cash >= nominal[i])
		{
			if (bills_limit >= max_bills_limit) cash = 0;
			if (cash / nominal[i] <= kolichestvo[i])
			{
				used[i] = cash / nominal[i];
				cash = cash - nominal[i] * used[i];
				sum = sum - nominal[i] * used[i];
				bills_limit += used[i];
			}
			else
			{
				used[i] = kolichestvo[i];
				cash = cash - nominal[i] * used[i];
				sum = sum - nominal[i] * used[i];
				bills_limit += used[i];
				i--;
			}
		}

		kolichestvo[i] = kolichestvo[i] - used[i];
	}
	// В случае, если превышен разовый лимит на количество выданных купюр - вывод сообщения об этом 
	if (bills_limit >= max_bills_limit)
		cout << "\nSorry, bill limit of one withdrawal is " << max_bills_limit << "\n";
	// Вывод на экран информации о том, сколько купюр каждого номинала было выдано
	for (int i = j - 1; i >= 0; --i) {
		for (int i = 0; i < j; i++) {
			if (used[i] == 0) continue;
			cout << "Payed " << used[i] << " bills of nominal " << nominal[i] << endl;
		}
		// Определение текущей суммы в банкомате после снятия наличных
		cout << "\nCurrently available for withdrawals sum is:\n";
		cout << sum;
		return sum;
	}
}
// Выдача введённой пользователем суммы денег с разменом
int WithdrawalMoneyWithChange()
{
	sum = 0;
	bills_limit = 0;
	// Определение текущей суммы в банкомате
	for (int i = 0; i < j; i++) {
		sum = sum + (nominal[i] * kolichestvo[i]);
		used[i] = 0;
	}
	cout << "\nCurrently available for withdrawals sum is:\n";
	cout << sum;
	int cash;
	int BanknotesNumber[] = { 0,0,0,0,0 };
	cout << "\nEnter a sum for withdrawal:\n";
	// Ввод пользователем суммы для вывода
	cin >> cash;
	// Если требуемой суммы нет в банкомате, и она не может быть выдана - вывод на экран предупреждения
	if ((cash > sum) || (cash % check != 0))
	{
		cout << "Sorry, this sum is unavailable for withdrawal" << '\n';
		exit(0);
	}
	// Проверка соблюдения разового лимита снятия наличных
	if (cash > one_time_limit)
	{
		cash = min(cash, one_time_limit);
		cout << "Your cash request is over then one time withdrawal and now you will get " << one_time_limit << " rubles\n";
	}
	// Проверка соблюдения дневного лимита снятия наличных
	if (cash > daily_limit)
	{
		cash = min(cash, daily_limit);
		cout << "Your cash request is over then daily withdrawal and now you will get " << daily_limit << " rubles\n";
	}
	daily_limit = daily_limit - cash;
	// Определение необходимого количества купюр каждого номинала для снятия требуемой суммы
	for (int i = j - 1; i >= 0; --i)
	{
		if (cash >= nominal[j - 1])
		{
			used[i] = used[i] + 1;
			cash = cash - nominal[i] * used[i];
			sum = sum - nominal[i] * used[i];
			//kolichestvo[i]--;
			kolichestvo[i]--;
			i--;
		}
		while (cash >= nominal[i])
		{
			if (bills_limit >= max_bills_limit) cash = 0;
			if (cash / nominal[i] <= kolichestvo[i])
			{
				used[i] = cash / nominal[i];
				cash = cash - nominal[i] * used[i];
				sum = sum - nominal[i] * used[i];
				bills_limit += used[i];
			}
			else
			{
				used[i] = kolichestvo[i];
				cash = cash - nominal[i] * used[i];
				sum = sum - nominal[i] * used[i];
				bills_limit += used[i];
				i--;
			}
		}
		kolichestvo[i] = kolichestvo[i] - used[i];
	}
	// В случае, если превышен разовый лимит на количество выданных купюр - вывод сообщения об этом 
	if (bills_limit >= max_bills_limit)
		cout << "\nSorry, bill limit of one withdrawal is " << max_bills_limit << "\n";
	// Вывод на экран информации о том, сколько купюр каждого номинала было выдано
	for (int i = 0; i <= j - 1; ++i) {
		for (int i = 0; i < j; i++) {
			if (used[i] == 0) continue;
			cout << "Payed " << used[i] << " bills of nominal " << nominal[i] << endl;
		}
		cout << "\nCurrently available for withdrawals sum is:\n";
		// Определение текущей суммы в банкомате после снятия наличных
		cout << sum;
		return sum;
	}
}
// Основное тело работы банкомата
int cycle(int input, bool pin_flag)
{
	enum Variants { close = -1, mainmenu = 0, ownsum = 1, standardsum = 2, future = 3, largebills = 41, change = 55 };
	Variants enter;
	cin >> input; // Выбор пользователем дальнейших действий
	enter << input;
	while ((pin_flag == true) && (input != -1))
	{
		if (pin_flag == false) exit(0);
		switch (input)
		{
		case close: pin_flag = false;
			exit(10);
			break;
		case mainmenu:
			main_menu();
			cycle(input, pin_flag);
			break;
		case ownsum: cout << "Do you want to withdrawal a sum in large bills or with change?\n"
			<< "Press '41' to withdrawal a sum in large bills\n"
			<< "Press '55' to withdrawal a sum with change\n";
			cycle(input, pin_flag);
			break;
		case standardsum: WithdrawalStandardSum();
			cout << '\n';
			return_main_menu();
			cycle(input, pin_flag);
			break;
			cycle(input, pin_flag);
			cycle(input, pin_flag);
			break;
		case future:
			ComingSoon();
			return_main_menu();
			cycle(input, pin_flag);
			break;
		case largebills:  WithdrawalOwnSumLargeBills();
			cout << '\n';
			return_main_menu();
			cycle(input, pin_flag);
			break;
		case change:  WithdrawalMoneyWithChange();
			cout << '\n';
			return_main_menu();
			cycle(input, pin_flag);
			break;
			// Если пользователем выбран вариант, не соответствующий заданным программой - вывод сообщения об этом на экран
		default: cout << "Input error."; exit(10);
		}
	}
}


int main()
{
	int pin = 7777; // Значение ПИН-кода
	int pin_code;
	bool pin_flag = false; // Проверка правильности ПИН-кода
	cout << "Please, enter a PIN-code:" << '\n';
	// Ввод пользователем ПИН-кода
	cin >> pin_code;
	// В случае если ПИН-код введён неверно - вывод сообщения об этом
	if (pin != pin_code) { cout << "Your PIN-code is incorrect!"; exit(10); }
	else
	{
		pin_flag = true;
		main_menu(); // Вывод на экран главного меню банкомата
	}
	cycle(input, pin_flag); // Функция работы банкомата
}