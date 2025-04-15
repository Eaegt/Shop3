#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
#include <map>
//база данных

int userSize = 2;
bool isAdmin = false;
std::string* loginArr = new std::string[userSize]{ "Admin","Seller" };
std::string* passArr = new std::string[userSize]{ "pass","123" };
double* sellsArr = new double[userSize] {0.0, 0.0};

//-----------------------------------------------------------------
// Склад
int size = 10;
int* idArr = new int[size];
std::string* nameArr = new std::string[size];
double* priceArr = new double[size];
int* countArr = new int[size];

//Функции

void Start();
bool Login();
void Getline(std::string& stringName);
void CreateStorage();
void ShowAdminMenu();
void ShowStorage(int mode = 0);
void RefillProduct();
int GetID(int mode = 0);
bool IsNumber(std::string& number);
void RemoveProduct();
void ChangePrice();
void ChangeStorage();
void Error();
void AddNewProduct();
void RenameProduct();
void DeleteProduct();

//=================

void ChangeStaff();
void ShowEmployee();
void AddNewEmployee();
void DeleteEmployee();
void EditEmployee();

//================
int sizeCheck = 1;
double cashbox = rand() % 5000 + 5000;
double eIncome = 0;
double cashIncome = 0;

std::string* nameArrCheck = new std::string[sizeCheck];
double* priceArrCheck = new double[sizeCheck];
int* countArrCheck = new int[sizeCheck];
double* totalArrCheck = new double[sizeCheck];

void Selling();
void IncreaseCheckArr();
void PrintCheck();

template<typename ArrType>
void FillArray(ArrType staticArr[], ArrType dynamicArr[]);

int main()
{

	Start();
	delete[] loginArr;
	delete[] passArr;
	delete[] idArr;
	delete[] nameArr;
	delete[] priceArr;
	delete[] countArr;
	delete[] sellsArr;
	delete[] nameArrCheck;
	delete[] priceArrCheck;
	delete[] countArrCheck;
	delete[] totalArrCheck;

	return 0;
}

void Start()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::cout << "\n\n\t\t\t Black tires\n\n";
	if (Login())
	{
		if (isAdmin == true)
		{
			std::string choose;
			while (true)
			{
				std::cout << "1 - Использовать готовый склад\n2 - Создать свой склад\nВвод: ";
				Getline(choose);
				if (choose == "1")
				{
					//готовый склад админ
					CreateStorage();
					ShowAdminMenu();
					break;
				}
				else if (choose == "2")
				{
					// динамический склад админ
					// ShowAdminMenu();
					break;
				}
				else
				{
					std::system("cls");
					std::cout << "Ошибка ввода\n\n";
				}
			}
		}
		else
		{
			//готовый склад. Продавец
			CreateStorage();
			// меню
		}
	}
	else
	{
		std::cerr << "Login Err\n";
	}
}

bool Login()
{
	std::string login, pass;
	while (true)
	{
		std::cout << "Введите логин: ";
		Getline(login);
		std::cout << "Введите пароль: ";
		Getline(pass);
		if (login == loginArr[0] && pass == passArr[0])
		{
			isAdmin = true;
			std::cout << "Пользователь" << loginArr[0] << " - Добро пожаловать!\nСтатус: Админ\n\n";
			return true;
		}

		for (int i = 1; i < userSize; i++)
		{
			if (login == loginArr[i] && pass == passArr[i])
			{
				isAdmin = false;
				std::cout << "Пользователь" << loginArr[i] << " - Добро пожаловать!\nСтатус: Продавец\n\n";
				return true;
			}
		}
		std::system("cls");
		std::cout << "Неправильный логин или пароль\n\n";
		if (Login())
		{

		}
	}
}

void Getline(std::string& stringName)
{
	std::getline(std::cin, stringName, '\n');
}

void CreateStorage()
{
	const int staticSize = 10;
	int id[staticSize]{ 1,2,3,4,5,6,7,8,9,10 };
	std::string name[staticSize]
	{
		"Pirelli Powergy", "Yokohama bluEarth-Es",
		"Cordiant Sport 3", "Sailun ATREZZO",
		"Prelli Scorpion", "Triangle Group TR646",
		"Hankook Ventus Prime 4", "Yokohama lce Guard",
		"Nokian Tyres", "Tunga Nordway"
	};
	double price[staticSize]{ 16053.7, 31083.4, 4532.1, 9377.6, 17256.8, 28327.2, 14830.4, 12102.3, 12729.9, 8256.7 };
	int count[staticSize]{ 13,15,9,18,27,19,9,22,16,6 };
	FillArray(id, idArr);
	FillArray(name, nameArr);
	FillArray(count, countArr);
	FillArray(price, priceArr);
	ShowStorage();

}

void ShowAdminMenu()
{
	std::string choose;

	while (true)
	{
		system("cls");
		std::cout << "1) Начать продажу\n";
		std::cout << "2) Показать склад\n";
		std::cout << "3) Пополнить склад\n";
		std::cout << "4) Списание товара\n";
		std::cout << "5) Изменение цены\n";
		std::cout << "6) Изменение склада\n";
		std::cout << "7) Изменение персонала\n";
		std::cout << "8) Отчёт о прибыли\n";
		std::cout << "0) Закрыть смену\n";
		std::cout << "Ввод: ";
		Getline(choose);
		if (choose == "1")
		{
			Selling();
		}
		else if (choose == "2")
		{
			ShowStorage();
		}
		else if (choose == "3")
		{
			RefillProduct();
		}
		else if (choose == "4")
		{
			RemoveProduct();
		}
		else if (choose == "5")
		{
			ChangePrice();
		}
		else if (choose == "6")
		{
			ChangeStorage();
		}
		else if (choose == "7")
		{

		}
		else if (choose == "8")
		{

		}
		else if (choose == "0")
		{

			break;
		}
		else
		{

		}

	}
}

void ShowStorage(int mode)
{
	if (mode == 0)
	{
		std::cout << "ID\t" << std::left << std::setw(25) << "Название товара\t\t" << "Кол-во\n";
		for (int i = 0; i < size; i++)
		{
			std::cout << idArr[i] << "\t" << std::left << std::setw(25) << nameArr[i] << "\t\t" << countArr[i] << "\n";
		}
		std::cout << "\n\n";
	}
	else if (mode == 1)
	{
		std::cout << "ID\t" << std::left << std::setw(25) << "Название товара\t" << "Цена\t" << "\n";
		for (int i = 0; i < size; i++)
		{
			std::cout << idArr[i] << "\t" << std::left << std::setw(25) << nameArr[i] << "\t\t" << priceArr[i] << "\n";
		}
		std::cout << "\n\n";
	}

	system("pause");
}

void RefillProduct()
{
	std::string choose, chooseCount;
	int id = 0, count = 0;
	while (true)
	{
		system("cls");
		std::cout << "Пополнить товар?\n1) Да\n2) Выход\nВвод: ";
		Getline(choose);
		if (choose == "1")
		{
			ShowStorage(1);
			id = GetID();
			while (true)
			{
				std::cout << "Введите кол-во товара для пополнения: ";
				Getline(chooseCount);
				if (IsNumber(chooseCount))
				{
					count = std::stoi(chooseCount);
					if (count >= 0 && count <= 1000 && countArr[size - 1] < 1000)
					{
						countArr[size - 1] = count;
						std::cout << "Товар успешно пополнен\n";
						Sleep(800);
						break;
					}
					else
					{
						std::cout << "\n\nНекорректное кол-во\n\n";
					}
				}
				else
				{
					std::cout << "\n\nОшибка ввода\n\n";
				}
			}
		}
		else if (choose == "2")
		{
			break;
		}
		else
		{
			std::cout << "\n\nОшибка ввода\n\n";
			Sleep(1000);
		}
	}
}

int GetID(int mode)
{
	std::string stringId;
	int result = 0;
	int currentSize = 0;
	if (mode == 0)
	{
		currentSize = size;
	}
	else if (mode == 1)
	{
		currentSize = userSize;
	}

	while (true)
	{
		std::cout << "Введите ID: ";
		Getline(stringId);
		if (IsNumber(stringId))
		{
			result = std::stoi(stringId);
			if (currentSize == userSize && result <= 0)
			{
				std::cout << "\n\nОшибка ввода ID\n\n";
				continue;
			}
			if (result > 0 && result <= currentSize)
			{
				return result;
			}
		}
		else
		{
			std::cout << "\n\nОшибка ввода\n\n";
		}
	}
}

bool IsNumber(std::string& number)
{
	if (number.size() <= 0 || number.size() >= 10)
	{
		return false;
	}
	for (int i = 0; i < number.size(); i++)
	{
		if (!std::isdigit((unsigned char)number[i]))
		{
			return false;
		}
	}
	return true;
}

void RemoveProduct()
{
	{
		std::string choose, chooseCount;
		int id = 0, count = 0;
		while (true)
		{
			system("cls");
			std::cout << "Пополнить товар?\n1) Да\n2) Выход\nВвод: ";
			Getline(choose);
			if (choose == "1")
			{
				ShowStorage(1);
				id = GetID();
				while (true)
				{
					std::cout << "Введите кол-во товара для пополнения: ";
					Getline(chooseCount);
					if (IsNumber(chooseCount))
					{
						count = std::stoi(chooseCount);
						if (count >= 0 && count <= 1000)
						{
							countArr[id - 1] += count;
							std::cout << "Товар успешно пополнен\n";
							Sleep(800);
							break;
						}
						else
						{
							std::cout << "\n\nНекорректное кол-во\n\n";
						}
					}
					else
					{
						std::cout << "\n\nОшибка ввода\n\n";
					}
				}
			}
			else if (choose == "2")
			{
				break;
			}
			else
			{
				std::cout << "\n\nОшибка ввода\n\n";
				Sleep(1000);
			}
		}
	}
}

void ChangePrice()
{
	std::string choose, choosePrice;
	int id = 0;
	double price = 0;
	while (true)
	{
		system("cls");
		std::cout << "Изменить цену?\n1) Да\n2) Выход\nВвод: ";
		Getline(choosePrice);
		if (choose == "1")
		{
			ShowStorage(2);
			id = GetID();
			while (true)
			{
				std::cout << "Введите новую цену: ";
				Getline(choosePrice);
				if (IsNumber(choosePrice))
				{
					price = std::stoi(choosePrice);
					if (price >= 0 && price <= 999999)
					{
						countArr[id - 1] += price;
						std::cout << "Цена изменена\n";
						Sleep(800);
						break;
					}
					else
					{
						std::cout << "\n\nНекорректная цена\n\n";
					}
				}
				else
				{
					std::cout << "\n\nОшибка ввода\n\n";
				}
			}
		}
		else if (choose == "2")
		{
			break;
		}
		else
		{
			std::cout << "\n\nОшибка ввода\n\n";
			Sleep(1000);
		}
	}
}

void ChangeStorage()
{
	std::string choose;
	while (true)
	{
		std::cout << "1 - Добавить новый товар\n2 - Редактировать название товара\n3 - Удалить товар\n0 - Выход\nВвод: ";
		Getline(choose);
		if (choose == "1")
		{
			AddNewProduct();
		}
		else if (choose == "2")
		{
			RenameProduct();
		}
		else if (choose == "3")
		{
			if (size > 1)
			{
				DeleteProduct();
			}
			else
			{
				std::cout << "Остался последний товар! Удаление запрещено\n\n";
			}
		}
		else if (choose == "0")
		{
			break;
		}
		else
		{
			Error();
		}
	}
}

void Error()
{
	std::string choose;
	while (true)
	{
		std::cout << "1 - Добавить новый товар\n2 - Редактировать название товара\n3 - Удалить товар\n0 - Выход\nВвод: ";
		Getline(choose);
		if (choose == "1")
		{

		}
		else if (choose == "2")
		{

		}
		else if (choose == "3")
		{

		}
		else if (choose == "0")
		{
			break;
		}
		else
		{
			Error();
		}
	}
}

void AddNewProduct()
{
	++size;

	int* idArrTemp = new int[size];
	std::string* nameArrTemp = new std::string[size];
	double* priceArrTemp = new double[size];
	int* countArrTemp = new int[size];

	for (int i = 0; i < size - 1; i++)
	{
		idArrTemp[i] = idArr[i];
		nameArrTemp[i] = nameArr[i];
		priceArrTemp[i] = priceArr[i];
		countArrTemp[i] = countArr[i];
	}

	std::string choose;

	idArrTemp[size - 1] = size;

	while (true)
	{
		system("cls");
		std::cout << "Введите название нового товара: ";
		Getline(choose);
		if (choose.size() <= 20 && choose.size() >= 3)
		{
			nameArrTemp[size - 1] = choose;
			break;
		}
		else
		{
			std::cout << "\nОшибка длины названия\n";
			Sleep(1000);
		}
	}
	int count = 0;

	while (true)
	{
		system("cls");
		std::cout << "Введите кол-во нового товара: ";
		Getline(choose);
		if (IsNumber(choose))
		{
			count = std::stoi(choose);
			if (count >= 0 && count <= 1000)
			{
				countArr[size - 1] = count;
				break;
			}
			else
			{
				std::cout << "\n\nНекорректное кол-во. Максимум 1000\n\n";
			}
		}
		else
		{
			Error();
		}
	}

	double price = 0;
	while (true)
	{
		system("cls");
		std::cout << "Введите цену нового товара: ";
		Getline(choose);
		if (IsNumber(choose))
		{
			price = std::stoi(choose);
			if (count >= 0 && price <= 999999)
			{
				countArr[size - 1] = count;
				break;
			}
			else
			{
				std::cout << "\n\nНекорректная цена. Максимум 999999\n\n";
			}
		}
		else
		{
			Error();
			Sleep(1000);
		}
	}

	std::swap(idArr, idArrTemp);
	std::swap(nameArr, nameArrTemp);
	std::swap(priceArr, priceArrTemp);
	std::swap(countArr, countArrTemp);

	system("cls");
	std::cout << "ID\t" << std::left << std::setw(25) << "Название товара\t\t" << "Кол-во\n";
	std::cout << idArr[size - 1] << "\t" << std::left << std::setw(25) << nameArr[size - 1] << "\t" << priceArr[size - 1]
		<< "\t" << countArr[size - 1] << "\n";
	std::cout << "\n\n";
	system("pause");
	delete[] idArrTemp;
	delete[] nameArrTemp;
	delete[] priceArrTemp;
	delete[] countArrTemp;

	idArr = new int[size];
	nameArr = new std::string[size];
	priceArr = new double[size];
	countArr = new int[size];

	std::swap(idArr, idArrTemp);
	std::swap(nameArr, nameArrTemp);
	std::swap(priceArr, priceArrTemp);
	std::swap(countArr, countArrTemp);

	delete[] idArrTemp;
	delete[] nameArrTemp;
	delete[] priceArrTemp;
	delete[] countArrTemp;
}

void RenameProduct()
{
	std::string choose;
	int id = 0;
	while (true)
	{
		system("cls");
		ShowStorage(3);
		id = GetID();
		std::cout << "Введите название для нового товара: ";
		Getline(choose);
		if (choose.size() <= 20 && choose.size() >= 3)
		{
			nameArr[id - 1] = choose;
			std::cout << "Название изменено\n\n";
			break;
		}
		else
		{
			std::cout << "\nОшибка длины названия\n";
			Sleep(1000);
		}
	}
}

void DeleteProduct()
{
	system("cls");
	ShowStorage();
	int id = GetID();
	--size;

	int* idArrTemp = new int[size];
	std::string* nameArrTemp = new std::string[size];
	double* priceArrTemp = new double[size];
	int* countArrTemp = new int[size];

	for (int i = 0; i < size; i++)
	{
		idArrTemp[i] = idArr[i];
	}

	for (int i = 0, j = 0; i < size; i++, j++)
	{
		if (j != id - 1)
		{
			nameArrTemp[i] = nameArr[j];
			priceArrTemp[i] = priceArr[j];
			countArrTemp[i] = countArr[j];
		}
		else
		{
			j++;
			nameArrTemp[i] = nameArr[j];
			priceArrTemp[i] = priceArr[j];
			countArrTemp[i] = countArr[j];
		}
	}

	system("cls");
	std::cout << "ID\t" << std::left << std::setw(25) << "Название товара\t\t" << "Кол-во\n";
	std::cout << idArr[size - 1] << "\t" << std::left << std::setw(25) << nameArr[size - 1] << "\t" << priceArr[size - 1]
		<< "\t" << countArr[size - 1] << "\n";
	std::cout << "\n\n";
	system("pause");

	std::swap(idArr, idArrTemp);
	std::swap(nameArr, nameArrTemp);
	std::swap(priceArr, priceArrTemp);
	std::swap(countArr, countArrTemp);

	delete[] idArrTemp;
	delete[] nameArrTemp;
	delete[] priceArrTemp;
	delete[] countArrTemp;

}

void ChangeStaff()
{
	std::string choose;
	while (true)
	{
		std::cout << "Посмотреть список сотрудников\n2 - Добавить нового сотрудника\n3 - Редактировать сотрудника\n4 - Уволить сотрудника\n0 - Выход\nВвод: ";
		Getline(choose);
		if (choose == "1")
		{
			ShowEmployee();
		}
		else if (choose == "2")
		{
			AddNewEmployee();
		}
		else if (choose == "3")
		{
			EditEmployee();
		}
		else if (choose == "4")
		{
			if (userSize > 2)
			{
				DeleteEmployee();
			}
			else
			{
				std::cout << "Остался последний товар! Удаление запрещено\n\n";
			}
		}
		else if (choose == "0")
		{
			break;
		}
		else
		{
			Error();
		}
	}
}

void ShowEmployee()
{
	std::cout << "ID1\t" << std::left << std::setw(20) << "Логин сотрудника\t" << "Пароль\t\t" << "Продажи\n";
	for (int i = 1; i < userSize; i++)
	{
		std::cout << i << "\t" << std::left << std::setw(20) << loginArr[i] << "\t\t" << passArr[i] << "\t" << sellsArr[i] << "\n";
	}
	std::cout << "\n\n";
	system("pause");
}

void AddNewEmployee()
{
	++userSize;

	std::string* loginArrTemp = new std::string[userSize];
	std::string* passArrTemp = new std::string[userSize];
	double* sellsArrTemp = new double[userSize];


	for (int i = 0; i < userSize - 1; i++)
	{
		loginArrTemp[i] = loginArr[i];
		passArrTemp[i] = passArr[i];
		sellsArrTemp[i] = sellsArr[i];
	}

	std::string choose;

	sellsArrTemp[userSize - 1] = 0.0;

	while (true)
	{
		system("cls");
		std::cout << "Введите логин нового сотрудника: ";
		Getline(choose);
		if (choose.size() <= 15 && choose.size() >= 5)
		{
			loginArrTemp[userSize - 1] = choose;
			break;
		}
		else
		{
			std::cout << "\nОшибка длины названия. Минимум 5 символов. Максимум 15 символов\n";
			Sleep(1000);
		}
	}
	int count = 0;

	while (true)
	{
		system("cls");
		std::cout << "Введите пароль нового сотрудника: ";
		Getline(choose);
		if (choose.size() <= 15 && choose.size() >= 5)
		{
			passArrTemp[userSize - 1] = choose;
			break;
		}
		else
		{
			std::cout << "\nОшибка длины названия. Минимум 5 символов. Максимум 15 символов\n";
			Sleep(1000);
		}
	}

	std::swap(loginArr, loginArrTemp);
	std::swap(passArr, passArrTemp);
	std::swap(sellsArr, sellsArrTemp);

	system("cls");
	std::cout << "ID1\t" << std::left << std::setw(25) << "Логин сотрудника\t" << "Пароль\t" << "Продажи\n";
	std::cout << idArr[size - 1] << "\t" << std::left << std::setw(20) << loginArr[userSize - 1] << "\t" << passArr[userSize - 1]
		<< "\t\t" << sellsArr[userSize - 1] << "\n";
	std::cout << "\n\n";

	system("pause");
	delete[] loginArrTemp;
	delete[] passArrTemp;
	delete[] sellsArrTemp;
}

void DeleteEmployee()
{
	system("cls");
	ShowEmployee();
	int id = GetID(1);
	--userSize;

	std::string* loginArrTemp = new std::string[userSize];
	std::string* passArrTemp = new std::string[userSize];
	double* sellsArrTemp = new double[userSize];

	for (int i = 1, j = 1; i < userSize; i++, j++)
	{
		if (j != id)
		{
			loginArrTemp[i] = loginArr[j];
			passArrTemp[i] = passArr[j];
			sellsArrTemp[i] = sellsArr[j];
		}
		else
		{
			j++;
			loginArrTemp[i] = loginArr[j];
			passArrTemp[i] = passArr[j];
			sellsArrTemp[i] = sellsArr[j];
		}
	}

	system("cls");
	std::cout << "Пользователь удалён\n\n";
	std::cout << "ID1\t" << std::left << std::setw(25) << "Логин сотрудника\t" << "Пароль\t\t" << "Продажи\n";
	for (int i = 1; i < userSize; i++)
	{
		std::cout << i << "\t" << std::left << std::setw(20) << loginArr[id] << "\t\t" << passArr[id] << "\t" << sellsArr[id] << "\n";
	}
	std::cout << "\n\n";

	std::swap(loginArr, loginArrTemp);
	std::swap(passArr, passArrTemp);
	std::swap(sellsArr, sellsArrTemp);

	system("pause");
	delete[] loginArrTemp;
	delete[] passArrTemp;
	delete[] sellsArrTemp;
}

void EditEmployee()
{
	std::string choose;
	ShowEmployee();
	int id = GetID(1);
	std::cout << "Выберите пункт для рекдактирования\n1 - Логин\n2 - Пароль\nВвод: ";
	Getline(choose);
	if (choose == "1")
	{
		while (true)
		{
			system("cls");
			std::cout << "Введите новый логин: ";
			Getline(choose);
			if (choose.size() <= 15 && choose.size() >= 5)
			{
				passArr[id] = choose;
				std::cout << "Пароль успешно изменён\n\n";
				Sleep(1000);
				break;
			}
			else
			{
				std::cout << "\nОшибка длины названия. Минимум 5 символов. Максимум 15 символов\n";
				Sleep(1000);
			}
		}
	}
	else if (choose == "2")
	{

	}
	else
	{

	}
}

void Selling()
{
	system("cls");
	ShowStorage();

	//Выбор кол-во товара
	std::string choose;
	int id = 0, count = 0;
	bool isFirst = true, isBuy = false;
	while (true)
	{
		system("cls");
		ShowStorage();
		id = GetID();

		while (true)
		{

			std::cout << "Введите кол-во товара для покупки: ";
			Getline(choose);
			if (IsNumber(choose)) //Проверить
			{
				count = std::stoi(choose);
				if (count > countArr[id - 1] || count < 1)
				{
					std::cout << "\n\nНекорректное кол-во\n\n";
					Sleep(1000);
				}
				else
				{
					break;
				}
			}
			else
			{
				Error();
			}
		}

		if (isFirst)
		{

			nameArrCheck[sizeCheck - 1] = nameArr[id - 1];
			countArrCheck[sizeCheck - 1] = count;
			priceArrCheck[sizeCheck - 1] = priceArr[id - 1];
			totalArrCheck[sizeCheck - 1] = count * priceArr[id - 1];
			isFirst = false;
		}
		else
		{
			IncreaseCheckArr();
			nameArrCheck[sizeCheck - 1] = nameArr[id - 1];
			countArrCheck[sizeCheck - 1] = count;
			priceArrCheck[sizeCheck - 1] = priceArr[id - 1];
			totalArrCheck[sizeCheck - 1] = count * priceArr[id - 1];
		}

		std::cout << "Купить ещё один товар?\n1 - Да\n2 - нет\nВвод: ";
		Getline(choose);
		if (choose == "1")
		{
			continue;
		}
		else if (choose == "2")
		{
			isBuy = false;
			break;
		}
		else
		{
			Error();
		}
	}

	std::cout << "TEST!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n"; //!!!!!
	PrintCheck();
	system("pause");
}

void IncreaseCheckArr()
{
	++sizeCheck;
	std::string* nameArrCheckTemp = new std::string[sizeCheck];
	double* priceArrCheckTemp = new double[sizeCheck];
	int* countArrCheckTemp = new int[sizeCheck];
	double* totalArrCheckTemp = new double[sizeCheck];

	for (int i = 0; i < sizeCheck - 1; i++)
	{
		nameArrCheck[i] = nameArr[i];
		countArrCheck[i] = countArr[i];
		priceArrCheck[i] = priceArr[i];
		totalArrCheck[i] = totalArrCheck[i];
	}

	std::swap(nameArrCheck, nameArrCheckTemp);
	std::swap(countArrCheck, countArrCheckTemp);
	std::swap(priceArrCheck, priceArrCheckTemp);
	std::swap(totalArrCheck, totalArrCheckTemp);

	delete[] nameArrCheckTemp, priceArrCheckTemp, countArrCheckTemp, totalArrCheckTemp;

}

void PrintCheck()
{
	std::cout << "ID\t" << std::left << std::setw(25) << "Название товара\t\t" << "Цена за ед\t" << "Кол-во\n";
	for (int i = 0; i < sizeCheck; i++)
	{
		std::cout << i + 1 << "\t" << std::left << std::setw(25) << nameArrCheck[i] << "\t" << priceArrCheck[i] << "\t" << countArrCheck[i] << "\n" << totalArrCheck[i] << "\n";
	}
	std::cout << "\n\n";
}

template<typename ArrType>
void FillArray(ArrType staticArr[], ArrType dynamicArr[])
{
	for (int i = 0; i < size; i++)
	{
		dynamicArr[i] = staticArr[i];
	}
}
