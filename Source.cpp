#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>


std::string lower(std::string name)
{
	for (int i = 1; i < name.size(); i++)
	{
		if (name[i] == 'Ё')
			name[i] += 16;
		else if (name[i] <= -33 && name[i] >= -64)
			name[i] += 32;
	}
	if (name[0] == 'ё')
		name[0] -= 16;
	else if (name[0] >= -32 && name[0] <= -1)
		name[0] -= 32;
	return name;
}

bool tryname(std::string std)
{
	int count = 0;
	if (std.size() < 2)
		return 0;
	while ((std[0] == ' ') && (std.size() > 1))
		std.erase(0, 1);
	if (std.size() < 2)
		return 0;
	while ((std[std.size() - 1] == ' ') && (std.size() > 1))
		std.erase(std.size() - 1, 1);
	if (std.size() < 2)
		return 0;
	else
	{
		for (int i = 0; i < std.size(); i++)
		{
			if (((std[i] > -65) && (std[i] < 0)) || (std[i] == -88) || (std[i] == -72) || (std[i] == 32))
			{
				count++;
			}
			else
			{
				return 0;
			}
			if (count == std.size())
			{
				std = lower(std);
				return 1;
			}
		}
	}
	return 0;
}

std::string schit(std::string& buff, char ch)
{
	std::string newbuff;
	if (buff.size() == 0)
		return "";
	while ((buff[0] != ch) && (buff.size() > 0))
	{
		newbuff += buff[0];
		buff.erase(0, 1);
	}
	if (newbuff.size() == 0)
		return "";
	buff.erase(0, 1);
	return newbuff;
}

int vvod()
{
	int x;
	while ((!(std::cin >> (x))) || (std::cin.get() != '\n'))
	{
		std::cin.clear();
		std::cin.ignore(32767, '\n');
		std::cout << "Не число! Повторите ввод\n";
	}
	return x;
}

bool nameorsurname(std::string std)
{
	int count=0;
	int num;
	if (std.size() < 2)
	{
		std::cout << "Длинна не может быть меньше 2!\n";
		return 0;
	}
	else
	{
		for (int i = 0; i < std.size(); i++)
		{
			num = std[i];
			if (((num > -65) && (num < 0)) || (num == -88) || (num == -72)||(num==32))
			{
				count++;
			}
			else
			{
				std::cout << "В строке присутсвуют символы, которые не могут тут быть!\n";
				return 0;
			}
			if (count == std.size())
				return 1;
		}
	}
	return 0;
}

bool checkpassport(std::string passport, int& serial, int& number)
{
	if (passport.size() == 11)
		if ((passport[0] > 47) && (passport[0] < 58) &&
			(passport[1] > 47) && (passport[1] < 58) &&
			(passport[2] > 47) && (passport[2] < 58) &&
			(passport[3] > 47) && (passport[3] < 58) &&
			(passport[4] == '-') &&
			(passport[5] > 47) && (passport[5] < 58) &&
			(passport[6] > 47) && (passport[6] < 58) &&
			(passport[7] > 47) && (passport[7] < 58) &&
			(passport[8] > 47) && (passport[8] < 58) &&
			(passport[9] > 47) && (passport[9] < 58) &&
			(passport[10] > 47) && (passport[10] < 58))
		{
			serial = (passport[0]-'0') * 1000 + (passport[1] - '0') * 100 + (passport[2] - '0') * 10 + passport[3] - '0';
			number = (passport[5] - '0') * 100000 + (passport[6] - '0') * 10000 + (passport[7] - '0') * 1000 + (passport[8] - '0') * 100 + (passport[9] - '0') * 10 + passport[10] - '0';
			return 1;
		}
	return 0;
}

class date
{
public:
	date();
	~date();
	std::string showstr();
	int inicialisation(int year, int month, int day, int hour, int min);
	void GetAll(int& first, int& second, int& third, int& four, int& five);
	int InputData(int num);
	int InputMonth(int num);
	void InputYear(int num);
	bool InputMin(int num);
	bool InputHour(int num);
	int ForExel(int datenew, int monthnew, int yearnew, int num);
	friend int operator!=(date num1, date num2);
private:
	int data;
	int month;
	int year;
	int hour;
	int min;
};

int operator!=(date num1, date num2)
{
	if ((num1.year == num2.year) && (num1.month == num2.month) && (num1.data == num2.data))
	{
		if ((num1.hour == num1.hour) && (num1.min == num2.min))
			return 0;
		else
			if (num1.hour > num2.hour)
				return 0;
			else
				if (num1.hour == num2.hour)
					if (num1.min > num1.min)
						return 0;
					else
						return 1;
				else
					return 1;
	}
	else
		if (num1.year > num2.year)
			return 0;
		else
			if (num1.year == num2.year)
				if (num1.month > num2.month)
					return 0;
				else
					if (num1.month == num2.month)
						if (num1.data > num2.data)
							return 0;
						else
							return 1;
					else
						return 1;
			else
				return 1;
}

int date::inicialisation(int year, int month, int day, int hour, int min)
{
		if(year>1900)
			InputYear(year);
		else
			return 1;
		if (InputMonth(month))
			return 2;
		if (InputData(day))
			return 3;
		if (InputHour(hour))
			return 4;
		if (InputMin(min))
			return 5;
		return 0;

}

int date::ForExel(int datenew, int monthnew, int yearnew, int num)
{
	if (yearnew < 0)
	{
		std::cout << "Некорректрная дата в строке номер " << num << '\n';
		return 1;
	}
	else
	{
		if ((monthnew > 12) || (monthnew < 1))
		{
			std::cout << "Некорректрная дата в строке номер " << num << '\n';
			return 1;
		}
		else
		{
			if ((datenew > 0) && (((yearnew % 4 != 0) && (monthnew == 2) && (datenew > 28)) || (datenew > 31) || ((datenew > 30) && ((monthnew == 6) || (monthnew == 4) || (monthnew == 9) || (monthnew == 11)))))
			{
				std::cout << "Некорректрная дата в строке номер " << num << '\n';
				return 1;
			}
			else
			{

				data = datenew;
				month = monthnew;
				year = yearnew;
				return 0;
			}
		}
	}

}

date::~date()
{
	//деструктор
}

std::string date::showstr()
{
	std::string strmonth;
	std::string strdata;
	if (month < 10)
		strmonth = '0' + std::to_string(month);
	else
		strmonth = std::to_string(month);
	if (data < 10)
		strdata = '0' + std::to_string(data);
	else
		strdata = std::to_string(data);
	std::string str = strdata + "." + strmonth + "." + std::to_string(year);
	if (hour < 10)
		str = str + " 0" + std::to_string(hour);
	else
		str = str + " " + std::to_string(hour);
	if (min < 10)
		str = str + ":0" + std::to_string(min);
	else
		str = str + ":" + std::to_string(min);
	return str;
}

void date::GetAll(int& first, int& second, int& third, int &four, int &five)
{
	first = year;
	second = month;
	third = data;
	four = hour;
	five = min;
}

date::date()
{
	data = 0;
	month = 0;
	year = 0;
	hour = 0;
	min = 0;
}

void date::InputYear(int num)
{
	this->year = num;
}

int date::InputMonth(int num)
{
	if ((num > 12) || (num < 1))
	{
		return 1;
	}
	else
	{
		this->month = num;
		return 0;
	}
}

int date::InputData(int num)
{
	if (((year % 4 != 0) && (month == 2) && (num > 28)) || (num > 31) || ((num > 30) && ((month == 6) || (month == 4) || (month == 9) || (month == 11))))
		return 1;
	else
	{
		this->data = num;
		return 0;
	}
}

bool date::InputHour(int num)
{
	if ((num < 0) || (num > 23))
		return 1;
	else
	{
		hour = num;
		return 0;
	}
}

bool date::InputMin(int num)
{
	if ((num < 0) || (num > 59))
		return 1;
	else
	{
		min = num;
		return 0;
	}
}

struct Airplaine//для списка
{
	std::string Otkuda;
	std::string Kuda;
	date time;
	int num;//всего мест
	int usage = 0;//используется мест
	int cost;//стоимость билета
	Airplaine* next=NULL;
	Airplaine* prev=NULL;
};

struct Bilet//для хеш таблицы
{
	std::string FIO;//имя покупателя
	int number;
	int ser;
	Airplaine* plane=NULL;
	Bilet* next;
	Bilet* prev;
};

struct cell
{
	Bilet* bilet;
	date time;
	date timereturn;
	int flag; //1 - Выдан, 2 - Возвращён
	int height;
	cell* previous;
	cell* left;
	cell* right;
	cell()
	{
		bilet = 0;
		flag = 0;
		left = 0;
		right = 0;
		height = -1;
		previous = 0;
	}
};

//дерево (для хранения информации о покупке и сдаче билетов и времени этого действия)


int Height(cell* element)
{
	if (element)
		return element->height;
	else
		return 0;
}

void OutTree(cell* element, int hig)
{
	if (element)
	{
		OutTree(element->left, hig + 1);
		OutTree(element->right, hig + 1);
		if (element->flag == 1)
			std::cout << element->bilet->FIO << " с паспортом: " << element->bilet->ser << "-" << element->bilet->number << " Получил билет на рейс " << element->bilet->plane->Otkuda << "-" << element->bilet->plane->Kuda << " отправляющийся " << element->bilet->plane->time.showstr() << " в " << element->time.showstr() << "\n";
		else
			if (element->flag == 2)
				std::cout << element->bilet->FIO << " с паспортом: " << element->bilet->ser << "-" << element->bilet->number << " Получил билет на рейс " << element->bilet->plane->Otkuda << "-" << element->bilet->plane->Kuda << " отправляющийся " << element->bilet->plane->time.showstr() << " в " << element->time.showstr() << " и сдал его в " << element->timereturn.showstr() << "\n";
	}
}

int Bfactor(cell* element)
{
	return (Height(element->right) - Height(element->left));
}

void ReHeight(cell* element)
{
	int heightL = Height(element->left);
	int heightR = Height(element->right);
	if (heightL > heightR)
		element->height = heightL + 1;
	else
		element->height = heightR + 1;
}

cell* RotateR(cell* element)
{
	cell* element_2 = element->left;
	element_2->previous = element->previous;
	element->left = element_2->right;
	element_2->right = element;
	element->previous = element_2;
	ReHeight(element);
	ReHeight(element_2);
	return element_2;
}

cell* RotateL(cell* element)
{
	cell* element_2 = element->right;
	element_2->previous = element->previous;
	element->right = element_2->left;
	element_2->left = element;
	element->previous = element_2;
	ReHeight(element);
	ReHeight(element_2);
	return element_2;
}

cell* ReBalance(cell* element)
{
	ReHeight(element);
	if (Bfactor(element) == 2)
	{
		if (Bfactor(element->right) < 0)
			element->right = RotateR(element->right);
		return RotateL(element);
	}
	if (Bfactor(element) == -2)
	{
		if (Bfactor(element->left) > 0)
			element->left = RotateL(element->left);
		return RotateR(element);
	}
	return element;
}

cell* AddSecond(cell* element, date now, Bilet* ticket, cell* prev, int flag)
{
	if ((!element)||(element==NULL))
	{
		cell* yacheika = new cell();
		yacheika->time = now;
		yacheika->flag = flag;
		yacheika->previous = prev;
		yacheika->bilet = ticket;
		return yacheika;
	}
	if ((ticket == element->bilet) && (element->flag < 2))
	{
		element->flag = flag;
		element->timereturn = now;
	}
	else
	{
		if (ticket->plane->time != element->bilet->plane->time)
			element->left = AddSecond(element->left, now, ticket, element, flag);
		else
			element->right = AddSecond(element->right, now, ticket, element, flag);
	}
	return ReBalance(element);
}

date getnowdate()
{
	time_t t;
	struct tm* t_m;
	t = time(NULL);
	t_m = localtime(&t);
	int year = t_m->tm_year+1900;
	int month = t_m->tm_mon+1;
	int day = t_m->tm_mday;
	int hour = t_m->tm_hour;
	int min = t_m->tm_min;
	date time;
	time.inicialisation(year, month, day, hour, min);
	return time;
}

class Spisok
{
private:
	int colvo=0;
	Airplaine* first;
	Airplaine* last;
public:
	Spisok() :first(NULL), last(NULL) {};
	~Spisok();
	void OutputAll();
	int OutputDost();
	Airplaine* Next(Airplaine* p);
	Airplaine* Prev(Airplaine* p);
	Spisok searchlist(int year, int month, int date);
	Spisok searchlist(std::string name, int flag);
	Bilet* buyticket(int num);
	Airplaine* getFirst();
	Airplaine* getLast();
	Airplaine* del(Airplaine* pos);
	Airplaine* execute(Airplaine* pos);
	void sort(Airplaine* data, Airplaine* endptr);
	void sorting();
	void save();
	void downld();
	void search();
	int col();
	Airplaine* partition(Airplaine* fir, Airplaine* sec);
	void swap(Airplaine* one, Airplaine* two);
	void addready(Airplaine* p);
	int Add(int c, int mesta, std::string first, std::string second, int y, int m, int d, int h, int mi, int used = 0);
};

Spisok::~Spisok()
{
	//деструктор списка
}

Bilet* Spisok::buyticket(int num)
{
	Airplaine* p;
	Bilet* human= new Bilet;
	std::cout << "\n\n\n";
	std::cout << "Введите ФИО в любом формате\n";
	std::string name;
	std::getline(std::cin, name);
	while (nameorsurname(name) == 0)
	{
		std::cout << "Некорректное ФИО! Повторите ввод\n";
		std::getline(std::cin,name);
	}
	human->FIO = name;

	std::cout << "Введите серию и номер пасспорта в формате XXXX-XXXXXX\n";
	std::string passport;
	getline(std::cin, passport);
	int serial;
	int number;
	while (!checkpassport(passport, serial, number))
	{
		std::cout << "Формат паспорта должен быть XXXX-XXXXXX! Повторите ввод!\n";
		getline(std::cin, passport);
	}
	human->ser = serial;
	human->number = number;
	int k = 0;
	p=getFirst();

	for (int i = 0; i < colvo; i++)
	{
		if (p->num - p->usage > 0)
			k++;
		if (k == num)
			break;
		p = p->next;
	}
	p->usage++;
	if (k == num)
	{
		human->plane = p;
	}
	else
		std::cout << "Ошибка поиска рейса!\n";
	return human;

}

int Spisok::OutputDost()
{
	int k = 0;
	Airplaine* element = first;
	while (element != NULL)
	{
		if ((element->num - element->usage) > 0)
		{
			k++;
			std::cout<<k<<": " << element->Otkuda << "-" << element->Kuda << " в " << element->time.showstr() << ". Занято " << element->usage << " из " << element->num << " мест. Стоимость билета: " << element->cost << "\n";
		}
		element = element->next;
	}
	return k;
}

Airplaine* Spisok::getFirst()
{
	return first;
}

void Spisok::swap(Airplaine* one, Airplaine* two)
{
	if (one == NULL || one->next == NULL)
		return;
	int flag1=0, flag2 = 0;

	Airplaine* temp;
	temp = one->next;
	if (one == first)
		flag1 = 1;
	if (two = last)
		flag2 = 1;
	one->next = two->next;
	two->next = temp;

	if (one->next != NULL)
		one->next->prev = one;
	if (two->next != NULL)
		two->next->prev = two;
	temp = one->prev;
	one->prev = two->prev;
	two->prev = temp;
	if (one->prev != NULL)
		one->prev->next = one;
	if (two->prev != NULL)
		two->prev->next = two;
	if (flag1 == 1)
		first = two;
	if (flag2 == 1)
		last = one;
}

Airplaine* Spisok::partition(Airplaine* fir, Airplaine* sec)
{
	Airplaine* pivot = fir;
	Airplaine* front = sec;
	int temp = 0;
	while (front != NULL && front != sec) {
		if (front->time != sec->time) {
			pivot = fir;

			swap(fir, sec);
			fir = fir->next;
		}
		front = front->next;
	}

	swap(fir,sec);
	return pivot;
}

void Spisok::sort(Airplaine* fir, Airplaine* sec)
{
	if (fir == sec) {
		return;
	}
	Airplaine* pivot = partition(fir, sec);

	if (pivot != NULL && pivot->next != NULL) {
		sort(pivot->next, sec);
	}

	if (pivot != NULL && fir != pivot) {
		sort(fir, pivot);
	}
}

void Spisok::addready(Airplaine* p)
{
	p->next = p->prev = NULL;

	if (first != NULL)
	{
		p->prev = last;
		last->next = p;
		last = p;
		colvo++;
	}
	else
	{
		colvo++;
		p->prev = NULL;
		first = last = p;
	}
}

void Spisok::sorting()
{
	if (colvo > 0)
	{
		Airplaine* sec = NULL;
		sort(first, last);
		std::cout << "\n\n\n";
		OutputAll();
	}
	else
		std::cout << "\n\n\nСписок пуст, нечего сортировать!\n";

}

void Spisok::downld()
{
	std::ifstream fin;
	std::string name;
	std::cout << "Введите название файла (без разрешения. оно будет добавленно автоматически - формат:xls).\nВ случае ввода разрешения оно будет принято как часть названия файла!\n";
	while (1)
	{
		getline(std::cin, name);
		if (name.size() < 1)
			std::cout << "Введена пустая строка. Повторите ввод!\n";
		else
			break;
	}
	name += ".xls";
	fin.open(name);
	if (fin.is_open() == 1)
	{
		std::cout << "Файл успешно открыт. Произвожу чтение...\n";
		std::string firstname, surname, buff, str;
		bool flag;
		int num = 0;
		int FlagForName = 0, FlagForSurname = 0, FlagForalldate = 0;
		int data, month, year, hour, minut, cost, mest, use;
		while (!fin.eof())
		{
			flag = 0;
			num++;
			firstname = "", surname = "";
			data = 0, month = 0; year = 0, hour=0, minut=0,cost=0,mest=0,use=0;
			std::getline(fin, str, '\n');
			{
				if (str.size() != 0)
				{
					buff = schit(str, '\t');
					flag = tryname(buff);
				}
				else
					flag = 0;
				if (flag == 0)
					std::cout << "Ошибка чтения места отправления в строке номер " << num << '\n';
				else
				{
					firstname = buff;
					buff.clear();
					if (str.size() != 0)
					{
						buff = schit(str, '\t');
						flag = tryname(buff);
					}
					else
						flag = 0;
					if (flag == 0)
						std::cout << "Ошибка чтения места назначения в строке номер " << num << '\n';
					else
					{	
						surname = buff;
						buff.clear();
						if (str.size() != 0)
						{
							buff = schit(str, '\t');//чтение стоимости
						}
						int counter = 0;
						while ((buff.size() > 0) && ((buff[0] > 47) && (buff[0] < 58)))
						{
							counter++;
							cost = cost * 10 + buff[0] - '0';
							buff.erase(0, 1);
						}
						if (counter!=0)
						{
							counter = 0;
							buff.clear();
							if (str.size() != 0)
							{
								buff = schit(str, '\t');//чтение мест
							}
							while ((buff.size() > 0) && ((buff[0] > 47) && (buff[0] < 58)))
							{
								counter++;
								mest = mest * 10 + buff[0] - '0';
								buff.erase(0, 1);
							}
							if (counter != 0)
							{
								counter = 0;
								buff.clear();
								if (str.size() != 0)
								{
									buff = schit(str, '\t');//чтение занятых мест
								}
								while ((buff.size() > 0) && ((buff[0] > 47) && (buff[0] < 58)))
								{
									counter++;
									use = use * 10 + buff[0] - '0';
									buff.erase(0, 1);
								}
								if (counter!=0)
								{
									buff.clear();
									if (str.size() != 0)
									{
										buff = schit(str, ' ');
									}
									if (buff.size() > 7)
										if ((buff[0] < 58) && (buff[0] > 47) && (buff[1] < 58) && (buff[1] > 47) && (buff[3] < 58) && (buff[3] > 47) && (buff[4] < 58) && (buff[4] > 47) && (buff[2] == '.') && (buff[5] == '.'))
										{
											data = (buff[0] - '0') * 10 + buff[1] - '0';
											month = (buff[3] - '0') * 10 + buff[4] - '0';
											int count = 0;
											while ((buff.size() > 6) && ((buff[6] > 47) && (buff[6] < 58)))
											{
												count++;
												year = year * 10 + buff[6] - '0';
												buff.erase(6, 1);
											}
											if (count != 0)
											{
												if (buff.size() > 6)
													std::cout << "Ошибка чтения даты из файла в строке номер " << num << '\n';
												else
												{
													//читаем время
													buff.clear();
													buff = str;
													if ((buff[0] < 58) && (buff[0] > 47) && (buff[1] < 58) && (buff[1] > 47) && (buff[3] < 58) && (buff[3] > 47) && (buff[4] < 58) && (buff[4] > 47) && (buff[2] == ':'))
													{
														hour = (buff[0] - '0') * 10 + buff[1] - '0';
														minut = (buff[3] - '0') * 10 + buff[4] - '0';
														if (buff.size() > 7)
															std::cout << "Ошибка чтения даты из файла в строке номер " << num << "! В конце строки присутсвуют лишние символы" << '\n';
														else
														{
															Add(cost, mest, firstname, surname, year, month, data, hour, minut, use);
														}
													}
													else
														std::cout << "Ошибка чтения даты из файла в строке номер " << num << '\n';
												}
											}
											else
												std::cout << "Ошибка чтения даты в строке номер " << num << '\n';
										}
										else
											std::cout << "Ошибка чтения даты в строке номер " << num << '\n';
									else
										std::cout << "Ошибка чтения даты в строке номер " << num << '\n';
								}
								else
									std::cout << "Ошибка чтения количества занятых мест в строке номер " << num << '\n';
							}
							else
								std::cout << "Ошибка чтения количества мест в строке номер " << num << '\n';
						}
						else
							std::cout<<"Ошибка чтения стоимости в строке номер " << num << '\n';
					}


				}
			}
		}
		fin.close();
	}
	else
		std::cout << "Не удалось открыть файл. Повторите попытку позже\n";

}

Airplaine* Spisok::getLast()
{
	return last;
}

Airplaine* Spisok::execute(Airplaine* pos)
{
	if (pos == NULL)
	{
		std::cout << "Список уже пуст." << std::endl;
		return NULL;
	}
	colvo--;
	if (pos == first)
	{
		first = pos->next;
		if (colvo != 0)
			first->prev = NULL;
		return pos;
	}
	if (pos == last)
	{
		last = pos->prev;
		last->next = NULL;
		return pos;

	}
	Airplaine* prev = Prev(pos);
	prev->next = pos->next;
	prev->next->prev = prev;
	return pos;
}

Airplaine* Spisok::del(Airplaine* pos)
{
	if (pos == NULL)
	{
		std::cout << "Список уже пуст." << std::endl;
		return NULL;
	}
	colvo--;
	if (pos == first)
	{
		first = pos->next;
		if (colvo != 0)
			first->prev = NULL;
		delete pos;
		return first;
	}
	if (pos == last)
	{
		last = pos->prev;
		delete pos;
		last->next = NULL;
		return last;
	}
	Airplaine* prev = Prev(pos);
	prev->next = pos->next;
	prev->next->prev = prev;
	delete pos;
	return prev;

}

void Spisok::save()
{
	std::cout << "Вы хотите открыть файл в режиме перезаписи (старые данные в файле будут очищены)?\n1 - Да\n2 - Нет\n0 - Выход\n";
	int variant = vvod();
	while ((variant > 2) || (variant < 0))
	{
		std::cout << "Значение не соотвествует ни одному из вариантов. Повторите ввод\n";
		variant = vvod();
	}
	if (variant == 0)
	{
		std::cout << "Выхожу...\n";
		return;
	}
	std::string name;
	std::cout << "Введите название файла (без разрешения. оно будет добавленно автоматически - формат:xls).\nВ случае ввода разрешения оно будет принято как часть названия файла!\n";
	while (1)
	{
		getline(std::cin, name);
		if (name.size() < 1)
			std::cout << "Введена пустая строка. Повторите ввод!\n";
		else
			break;
	}
	name += ".xls";
	std::fstream fout;
	if (variant == 1)
		fout.open(name, std::ios::out);
	else
		fout.open(name, std::ios::app);
	if (fout.is_open() == 1)
	{
		std::cout << "Файл успешно открыт\n";
		int num = 0;
		Airplaine* p = first;
		while (p != NULL)
		{
			num++;
			fout << p->Otkuda << '\t' << p->Kuda << '\t' << p->cost <<'\t' <<p->num <<'\t'<<p->usage <<'\t'<<p->time.showstr() << '\n';
			p = Next(p);
		}
		if (num == 0)
			std::cout << "Нечего сохранять. Список пуст\n";
		else
			std::cout << "\nУспешно!\n";
		fout.close();
	}
	else
		std::cout << "Не получилось открыть файл. Повторите попытку позже\n";
}

int Spisok::col()
{
	return (colvo);
}

Airplaine* Spisok::Next(Airplaine* p)
{
	return (p->next);
}

Airplaine* Spisok::Prev(Airplaine* p)
{
	return (p->prev);
}

int Spisok::Add(int c, int mesta, std::string fir, std::string second, int y, int m, int d, int h, int mi, int used)
{
	Airplaine* elem= new Airplaine;
	elem->next = elem->prev = NULL;
	elem->usage = used;
	if (c >= 1)
		elem->cost = c;
	else 
		return 1;
	if (nameorsurname(fir))
		elem->Otkuda = fir;
	else
		return 2;
	if (nameorsurname(second))
		elem->Kuda = second;
	else
		return 3;
	if (mesta > 0)
		elem->num = mesta;
	else
		return 4;
	if (elem->time.inicialisation(y, m, d, h, mi) == 0)
		if (first != NULL)
		{
			elem->prev = last;
			last->next = elem;
			last = elem;
			colvo++;
			return 0;
		}
		else
		{
			colvo++;
			elem->prev = NULL;
			first = last = elem;
			return 0;
		}

	else
		return (5);
}

void Spisok::OutputAll()
{
	int k = 0;
	Airplaine* element = first;
	if (element != NULL)
		std::cout << "Список:\n";
	while (element != NULL)
	{
		k++;
		std::cout << element->Otkuda << "-" << element->Kuda << " в " << element->time.showstr() << ". Занято " << element->usage<<" из "<<element->num<<" мест. Стоимость билета: "<< element->cost<<"\n";
		element = element->next;
	}
	if (k == 0)
		std::cout << "Список пуст";
	std::cout << '\n';

}

Spisok Spisok::searchlist(int year, int month, int date)
{
	Spisok newlist;
	Airplaine* p = first;
	Airplaine* d;
	int searchdata, searchmonth, searchyear, searchhour, searchmin;
	for (int i = 0; i < colvo; i++)
	{
		p->time.GetAll(searchyear, searchmonth, searchdata, searchhour, searchmin);
		if ((date == searchdata) && (month == searchmonth) && (year == searchyear))
		{
			newlist.Add(p->cost, p->num,p->Otkuda,p->Kuda, year, month, date, searchhour, searchmin, p->usage);
			d = p->next;
			del(p);
			p = d;
		}
		else
			p = p->next;
	}
	if (newlist.colvo == 0)
		std::cout << "В списке отсутсвуют рейсы с заданной датой отправления!\n";
	return newlist;
}

Spisok Spisok::searchlist(std::string name, int flag)
{
	Spisok newlist;
	Airplaine* p = first;
	Airplaine* d;
	int data, month, year, hour, min;
	for (int i = 0; i < colvo; i++)
	{
		if (((lower(p->Otkuda) == name) && (flag == 1)) || ((lower(p->Kuda) == name) && (flag == 2)))
		{
			p->time.GetAll(year, month, data, hour, min);
			newlist.Add(p->cost, p->num,p->Otkuda, p->Kuda, year, month, data, hour, min, p->usage);
			d = p->next;
			del(p);
			p = d;
		}
		else
			p = p->next;
	}
	if (newlist.colvo == 0)
		std::cout << "В списке отсутсвуют рейсы с заданным местом отправления/назначения!\n";
	return newlist;
}

void Spisok::search()
{
	Spisok newlist;
	date timed;
	int year = -1, month = -1, day = -1, hour = -1, minut = -1;
	if (colvo == 0)
	{
		std::cout << "Список пуст, невозможно осуществить поиск\n";
		return;
	}
	std::string fir;
	Airplaine* p=NULL;
	Airplaine* d = NULL;
	int var = -1;
	while (var != 0)
	{
		std::cout << "\n\n\n\n\n";
		std::cout << "1 - Поиск по месту отправления\n";
		std::cout << "2 - Поиск по месту назначения\n";
		std::cout << "3 - Поиск по дате отправления\n";
		std::cout << "0 - Выход\n";
		var = vvod();
		switch (var)
		{
		case 1:
			std::cout << "Введите место отправления: ";
			getline(std::cin, fir);
			while (nameorsurname(fir) == 0)
			{
				std::cout << "Некорректное место отправления! Повторите ввод\n";
				getline(std::cin, fir);
			}
			newlist = searchlist(lower(fir), 1);
			if (newlist.col() != 0)
				newlist.OutputAll();
			break;
		case 2:
			std::cout << "Введите место назначения: ";
			getline(std::cin, fir);
			while (nameorsurname(fir) == 0)
			{
				std::cout << "Некорректное место назначений! Повторите ввод\n";
				getline(std::cin, fir);
			}
			newlist = searchlist(lower(fir), 2);
			if (newlist.col() != 0)
				newlist.OutputAll();

			break;
		case 3:
			year = -1, month = -1, day = -1, hour = -1, minut = -1;
			while (timed.inicialisation(year, month, day, hour, minut)!=4)
			{
				std::cout << "Введите год отправления: ";
				year = vvod();
				while ((timed.inicialisation(year, month, day, hour, minut)) == 1)
				{
					std::cout << "Некорректный год отправления\n";
					year = vvod();
				}
				std::cout << "Введите месяц отправления: ";
				month = vvod();
				while ((timed.inicialisation(year, month, day, hour, minut)) == 2)
				{
					std::cout << "Некорректный месяц отправления!\n";
					month = vvod();
				}
				std::cout << "Введите дату отправления: ";
				day = vvod();
				while ((timed.inicialisation(year, month, day, hour, minut)) == 3)
				{
					std::cout << "Некорректная дата отправления!\n";
					day = vvod();
				}
			}
			newlist = searchlist(year, month, day);
			if (newlist.col() != 0)
				newlist.OutputAll();
			break;
		case 0:
			std::cout << "Выхожу...\n";
			break;
		default:
			std::cout << "Введено число, не соответсвующее ни одному из вариантов. Повторите ввод!\n";
			break;
		}
		if (newlist.col() != 0)
		{

			int var_2 = -1;
			while ((var_2 != 0)&&(newlist.col()!=0))
			{
				std::cout << "\n\n\n0 - Выход\n";
				std::cout << "1 - " << newlist.col() << " - Выбор соответсвующего элемента\n";
				var_2 = vvod();
				if (var_2 == 0)
				{
					p = newlist.getFirst();
					for (int i = 0; i < newlist.col(); i++)
					{
						newlist.execute(p);
						addready(p);
						p = p->next;
					}
					std::cout << "Выхожу...\n";
				}
				else
				{
					if ((var_2 > 0) && (var_2 <= newlist.col()))
					{
						p = newlist.getFirst();
						for (int i = 1; i < var_2; i++)
						{
							p = p->next;
						}
						var = -1;
						while ((var != 0)&&(var !=4))
						{
							std::cout << "\n\n\n";
							std::cout << "1 - Изменить место отправления\n";
							std::cout << "2 - Изменить место назначения\n";
							std::cout << "3 - Изменить время отправления\n";
							std::cout << "4 - Удалить рейс\n";
							std::cout << "0 - Выход\n";
							var = vvod();
							switch (var)
							{
							case 0:
								std::cout << "Выхожу...\n";
								p = newlist.getFirst();
								for (int i = 0; i < newlist.col(); i++)
								{
									newlist.execute(p);
									addready(p);
									p = p->next;
								}
								break;
							case 1:
								std::cout << "Введите место отправления: ";
								getline(std::cin, fir);
								while (nameorsurname(fir) == 0)
								{
									std::cout << "Некорректное место отправления! Повторите ввод\n";
									getline(std::cin, fir);
								}
								p->Otkuda = fir;
								break;
							case 2:
								std::cout << "Введите место назначения: ";
								getline(std::cin, fir);
								while (nameorsurname(fir) == 0)
								{
									std::cout << "Некорректное место назначения! Повторите ввод\n";
									getline(std::cin, fir);
								}
								p->Kuda = fir;
								break;
							case 3:
								year = -1, month = -1, day = -1, hour = -1, minut = -1;
								while (p->time.inicialisation(year, month, day, hour, minut))
								{
									std::cout << "Введите год отправления: ";
									year = vvod();
									while ((p->time.inicialisation(year, month, day, hour, minut)) == 1)
									{
										std::cout << "Некорректный год отправления\n";
										year = vvod();
									}
									std::cout << "Введите месяц отправления: ";
									month = vvod();
									while ((p->time.inicialisation(year, month, day, hour, minut)) == 2)
									{
										std::cout << "Некорректный месяц отправления!\n";
										month = vvod();
									}
									std::cout << "Введите дату отправления: ";
									day = vvod();
									while ((p->time.inicialisation(year, month, day, hour, minut)) == 3)
									{
										std::cout << "Некорректная дата отправления!\n";
										day = vvod();
									}
									std::cout << "Введите час отправления: ";
									hour = vvod();
									while ((p->time.inicialisation(year, month, day, hour, minut)) == 4)
									{
										std::cout << "Некорректный час отправления!\n";
										hour = vvod();
									}
									std::cout << "Введите минуту отправления: ";
									minut = vvod();
									while ((p->time.inicialisation(year, month, day, hour, minut)) == 5)
									{
										std::cout << "Некорректное время отправления в минутах!\n";
										minut = vvod();
									}
								}
								break;
							case 4:
								newlist.del(p);
								break;
							default:
								std::cout << "Такой вариант отсутсвует. Повторите ввод!\n";
								break;
							}
							if (newlist.col()!=0)
								newlist.OutputAll();
							std::cout << "\n";
						}
					}
					else
						std::cout << "Такого элемента нет в списке! Повторите ввод!\n";
					
				}
			}




		}
		else
			std::cout << "Возвращаюсь в главное меню...\n";
	}

}




//Алгоритм БМ

int maximum(int a, int b)
{
	return (a > b) ? a : b;
}

bool BouMur(std::string stroka, std::string name)
{
	//алгоритм боуэра мура
	int m = name.size();
	int n = stroka.size();

	int badchar[256];

	for (int i = 0; i < 256; i++)
		badchar[i] = -1;

	for (int i = 0; i < name.size(); i++)
		badchar[name[i]] = i;

	int s = 0; // s is shift of the pattern with respect to text
	while (s <= (n - m))
	{
		int j = m - 1;

		while (j >= 0 && name[j] == stroka[s + j])
			j--;

		if (j < 0)
		{
			return 1;

			s += (s + m < n) ? m - badchar[stroka[s + m]] : 1;

		}

		else
			s += maximum(1, j - badchar[stroka[s + j]]);
	}
	return 0;
}


//Список для разрешения коллизий в хеш-таблице

class HashSpisok
{
private:
	Bilet* first=NULL;
	Bilet* last=NULL;
	int colvo = 0;
public:
	Bilet* Next(Bilet* p);
	Bilet* Prev(Bilet* p);
	cell* del(Bilet* pos, cell* boshka);
	void Search(std::string name, int &k);
	Bilet* SearchElem(std::string name, int& k, int var);
	int col();
	int OutputDost();
	int Output();
	cell* add(Bilet* p, cell* boska);
};

int HashSpisok::col()
{
	return colvo;
}

Bilet* HashSpisok::Next(Bilet* p)
{
	if (p)
		return p->next;
	else
		return NULL;
}

Bilet* HashSpisok::Prev(Bilet* p)
{
	if (p)
		return p->prev;
	else
		return NULL;
}

cell* HashSpisok::del(Bilet* pos, cell* boshka)
{
	if (pos == NULL)
	{
		std::cout << "Список уже пуст." << std::endl;
		return NULL;
	}
	colvo--;
	if (pos == first)
	{
		pos->plane->usage--;
		boshka=AddSecond(boshka, getnowdate(), pos, NULL, 2);
		first = pos->next;
		if (colvo != 0)
			first->prev = NULL;
		return boshka;
	}
	if (pos == last)
	{
		boshka=AddSecond(boshka, getnowdate(), pos, NULL, 2);
		pos->plane->usage--;
		last = pos->prev;
		last->next = NULL;
		return boshka;
	}
	boshka=AddSecond(boshka, getnowdate(), pos, NULL, 2);
	Bilet* prev = Prev(pos);
	prev->next = pos->next;
	prev->next->prev = prev;
	return boshka;

}

int HashSpisok::OutputDost()
{
	int k = 0;
	Bilet* element = first;
	while (element != NULL)
	{
		k++;
		std::cout << k << ": " <<
			element->plane->Otkuda << "-" << element->plane->Kuda << " в " << element->plane->time.showstr() 
			<< ". Стоимость билета: " << element->plane->cost <<". Паспорт: "<<element->ser
			<<"-"<<element->number<< ". ФИО: "<<element->FIO << "\n";
		element = element->next;
	}
	return k;
}

int HashSpisok::Output()
{
	int k = 0;
	Bilet* element = first;
	while (element != NULL)
	{
		k++;
		std::cout << element->plane->Otkuda << "-" << element->plane->Kuda << " в " << element->plane->time.showstr()
			<< ". Стоимость билета: " << element->plane->cost << ". Паспорт: " << element->ser
			<< "-" << element->number << ". ФИО: " << element->FIO << "\n";
		element = element->next;
	}
	return k;
}

cell* HashSpisok::add(Bilet* p, cell* boshka)
{
	p->next = p->prev = NULL;

	if (first != NULL)
	{
		p->prev = last;
		last->next = p;
		last = p;
		colvo++;
	}
	else
	{
		colvo++;
		p->prev = NULL;
		first = last = p;
	}
	return (AddSecond(boshka, getnowdate(), p, NULL, 1));
}

void HashSpisok::Search(std::string name, int &k)
{
	Bilet* element = first;
	while (element != NULL)
	{
		if ((BouMur(element->FIO, name)) || (BouMur(element->plane->Otkuda, name)) || (BouMur(element->plane->Kuda, name)))
		{
			k++;
			std::cout << k << ": " << element->plane->Otkuda << "-" << element->plane->Kuda << " в " << element->plane->time.showstr()
				<< ". Стоимость билета: " << element->plane->cost << ". Паспорт: " << element->ser
				<< "-" << element->number << ". ФИО: " << element->FIO << "\n";
		}
		element = element->next;
	}
}

Bilet* HashSpisok::SearchElem(std::string name, int& k, int var)
{
	Bilet* element = first;
	while (element != NULL)
	{
		if ((BouMur(element->FIO, name)) || (BouMur(element->plane->Otkuda, name)) || (BouMur(element->plane->Kuda, name)))
		{
			std::cout << k << ": " << element->plane->Otkuda << "-" << element->plane->Kuda << " в " << element->plane->time.showstr()
				<< ". Стоимость билета: " << element->plane->cost << ". Паспорт: " << element->ser
				<< "-" << element->number << ". ФИО: " << element->FIO << "\n";
			k++;
			if (k == var)
				return element;
		}
		element = element->next;
	}
	return NULL;
}


int hashtable_code(int serial, int number, int num)
{
	return ((10 * serial + number ) % num);//заменить на:какая то хеш функция
}

cell* Bought(Spisok airpl,int n, HashSpisok* table, cell* firstelem)
{
	int col = airpl.OutputDost();
	if (col==0)
	{
		std::cout << "Нет рейсов с доступными билетами!\n";
		return firstelem;
	}
	std::cout << "1 - " << col<<" - Выбор соответсвующего рейса\n";
	int num = vvod();
	while ((num > col) || (num < 1))
	{
		std::cout << "Такой вариант отсутствует. Повторите ввод!\n";
		std::cout << "1 - " << col << " - Выбор соответсвующего рейса\n";
		num = vvod();
	}
	Bilet* elem = airpl.buyticket(num);
	std::cout << "\nСтоимость билета составит " << elem->plane->cost << "\n";
	int code = hashtable_code(elem->ser,elem->number, n);
	return (table[code].add(elem, firstelem));
}

void OutputHash(HashSpisok* table, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (table[i].col() != 0)
			table[i].Output();
	}
}

cell* SearchHash(HashSpisok* table, int n, cell* firstelem)
{
	int index = 0;
	Bilet* p = NULL;
	std::cout << "Введите ключевое слово\n";
	std::string name;
	getline(std::cin,name);
	while (!nameorsurname(name))
	{
		std::cout << "Строка должна содержать лишь русские символы. Повторите ввод!\n";
		getline(std::cin, name);
	}
	int k = 0;
	for (int i = 0; i < n; i++)
	{
		if (table[i].col() != 0)
			table[i].Search(name, k);
	}
	if (k == 0)
	{
		std::cout << "\nНе найдено ни одного совпадения!\n";
		return firstelem;
	}
	else
	{
		std::cout << "1 - " << k << " - Соотсветсвующий билет\n";
		int var = vvod();
		while ((var > k) || (var < 1))
		{
			var = vvod();
			std::cout << "Такой вариант отсутсвует. Повторите ввод!\n";
		}
		k = 0;
		for (int i = 0; i < n; i++)
		{
			if (table[i].col() != 0)
			{
				p = table[i].SearchElem(name, k, var);
				if (p != NULL)
				{
					index = i;
					break;
				}
			}
					
		}
		///
		if (p != NULL)
		{
			var = -1;
			while (var != 0)
			{
				std::cout << "\n\n\n";
				std::cout << "1 - Удалить\n";
				std::cout << "2 - Редактировать ФИО\n";
				std::cout << "0 - Выход\n";
				var = vvod();
				switch (var)
				{
				case 0:
					std::cout << "Выхожу...\n\n\n";
					return firstelem;
					break;
				case 1:
					return (table[index].del(p,firstelem));
					var = 0;
					break;
				case 2:
					std::cout << "Введите новое ФИО: ";
					std::getline(std::cin, name);
					while (nameorsurname(name) == 0)
					{
						std::cout << "Некорректное ФИО! Повторите ввод\n";
						std::getline(std::cin, name);
					}
					p->FIO = name;
					break;
				default:
					std::cout << "Число не соответсвует ни одному из вариантов! Повторите ввод!\n";
					break;
				}
			}
		}
		else
			std::cout << "Ошибка поиска элемента!\n";

	}
	return firstelem;
}








int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	cell* firstelem=NULL;
	int forpass = 10000;
	HashSpisok* hash = new HashSpisok[forpass];
	Spisok planes;
	int var = -1;
	std::string fir, sec;
	int hour = 0, month = 0, year = 0, minut = 0, day = 0, cost = 0, mesta = 0;
	date data;
	while (var != 0)
	{
		std::cout << "1 - Рейсы\n";
		std::cout << "2 - Билеты\n";
		std::cout << "3 - Информация о покупке/сдачи билетов\n";
		std::cout << "0 - Выход\n";
		var = vvod();
		switch (var)
		{
		case 1:
		{
			while (var != 0)
			{
				std::cout << "1 - Добавить рейс\n";
				std::cout << "2 - Вывести список рейсов\n";
				std::cout << "3 - Поиск рейса\n";
				std::cout << "4 - Сохранить в файл\n";
				std::cout << "5 - Загрузка из файла\n";
				std::cout << "6 - Сортировка по дате отправления\n";
				std::cout << "0 - Выход\n";
				switch (var = vvod())
				{
				case 1:
				{
					hour = -1;
					year = -1;
					minut = -1;
					day = -1;
					cost = -1;
					mesta = -1;
					std::cout << "Введите место отправления: ";
					getline(std::cin, fir);
					while (nameorsurname(fir) == 0)
					{
						std::cout << "Некорректное место отправления! Повторите ввод\n";
						getline(std::cin, fir);
					}
					std::cout << "Введите место назначения: ";
					getline(std::cin, sec);
					while (nameorsurname(sec) == 0)
					{
						std::cout << "Некорректное место назначения! Повторите ввод\n";
						getline(std::cin, sec);
					}
					std::cout << "Введите стоимость билета: ";
					cost = vvod();
					while (cost < 1)
					{
						std::cout << "Стоимотсть билета не может быть меньше 1, повторите ввод!\n";
						cost = vvod();
					}
					std::cout << "Введите количество мест на рейсе: ";
					mesta = vvod();
					while (mesta < 10)
					{
						std::cout << "Количество мест не может быть меньше 10, повторите ввод!\n";
						mesta = vvod();
					}
					while (data.inicialisation(year, month, day, hour, minut))
					{
						std::cout << "Введите год отправления: ";
						year = vvod();
						while ((data.inicialisation(year, month, day, hour, minut)) == 1)
						{
							std::cout << "Некорректный год отправления\n";
							year = vvod();
						}
						std::cout << "Введите месяц отправления: ";
						month = vvod();
						while ((data.inicialisation(year, month, day, hour, minut)) == 2)
						{
							std::cout << "Некорректный месяц отправления!\n";
							month = vvod();
						}
						std::cout << "Введите дату отправления: ";
						day = vvod();
						while ((data.inicialisation(year, month, day, hour, minut)) == 3)
						{
							std::cout << "Некорректная дата отправления!\n";
							day = vvod();
						}
						std::cout << "Введите час отправления: ";
						hour = vvod();
						while ((data.inicialisation(year, month, day, hour, minut)) == 4)
						{
							std::cout << "Некорректный час отправления!\n";
							hour = vvod();
						}
						std::cout << "Введите минуту отправления: ";
						minut = vvod();
						while ((data.inicialisation(year, month, day, hour, minut)) == 5)
						{
							std::cout << "Некорректное время отправления в минутах!\n";
							minut = vvod();
						}
					}
					planes.Add(cost, mesta, fir, sec, year, month, day, hour, minut);
					break;
				}
				case 2:
					planes.OutputAll();
					break;
				case 3:
					planes.search();
					break;
				case 4:
					planes.save();
					break;
				case 5:
					planes.downld();
					break;
				case 6:
					planes.sorting();
					break;
				case 0:
					std::cout << "Выход...";
					break;
				default:
					std::cout << "Введено число, не соответствующее ни одному варианту. Повторите ввод!\n";
					break;
				}
				std::cout << "\n\n\n";
			}
			var = -1;
			break;
		}
		case 2:
		{
			while (var != 0)
			{
				std::cout << "\n\n\n";
				std::cout << "1 - Купить билет\n";
				std::cout << "2 - Вывести список купленных билетов\n";
				std::cout << "3 - Поиск по ключевому слову\n";
				std::cout << "0 - Выход\n";
				var = vvod();
				switch (var)
				{
				case 1:
					firstelem=Bought(planes,forpass, hash, firstelem);
					break;
				case 2:
					OutputHash(hash, forpass);
					break;
				case 3:
					firstelem=SearchHash(hash, forpass,firstelem);
					break;
				case 0:
					std::cout << "Выхожу...\n\n\n\n";
					break;
				default:
					std::cout << "Введено число, не соответсвующее ни одному из вариантов! Повторите ввод!\n";
					break;
				}
			}
			var = -1;
			break;
		}
		case 3:
			if (firstelem)
				OutTree(firstelem, firstelem->height);
			else
				std::cout << "Записи о покупке/продаже билетов отсутсвуют!\n";
			break;
		case 0:
			std::cout << "Завершаю работу...\n";
			break;
		default:
			std::cout << "Введено число, не соответсвующее ни одному из вариантов! Повторите ввод!\n";
			break;
		}
}
}
