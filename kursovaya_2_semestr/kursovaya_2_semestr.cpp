// kursovaya_2_semestr.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"



typedef struct student
{
	char* surname;      //фамилия
	char* name;         //имя
	char* patr;         //отчество
	int group;          //номер группы
	int mark;           //оценка
} STUDENT;

typedef struct list
{
	STUDENT inital_data;             //Информация о студенте
	struct list* next;               //указатель на следующий элемент списка
} LIST;

int menu(int);                                                      //прототип функции вывода меню и выбора пункта меню
void select_method_of_input(LIST**);                                //прототип функции выбора способа ввода данных
LIST* select_where_student_add(LIST*);                              //прототип функции выбора способа добавления студента в список
LIST* input_student(LIST*, LIST*, bool);                            //прототип функции добавления студента в список
LIST* set_info_about_student(LIST*);                                //прототип функции ввода информации о студенте
char* set_x_name(bool);                                             //прототип функции ввода фамилии/имени/отчества студента
char* imitate_backspace(char*, int*);                               //прототип функции имитации нажатия клавиши backspace
bool check_true_symbols(char*, int);                                //прототип функции порверки корректности введенного символа
char* clean(char*);                                                 //прототип функции освобождения памяти из под строки символов
int set_x_number(bool);                                             //прототип функции ввода номера группы студента
LIST* create_list(LIST*);                                           //прототип функции создания списка
LIST* input_to_selected_pos(LIST*);                                 //прототип Функции добавления студента в определенное место списка
LIST* search_student(LIST*, LIST*);                                 //прототип функции нахождения студента в списке, предыдущего искомому
bool compare_student(LIST*, LIST*);                                 //прототип функции сравнения по всем полям двух структур
bool compare_string(char*, char*);                                  //прототип функции сравнения двух строк
int string_length(char*);                                           //прототип функции определения длины строки
LIST* cleanlist(LIST*);                                             //прототип функции освобождения памяти из-под списка
void clean_base_struct(LIST*);                                      //прототип функции освобождения памяти из-под полей базовой структуры
LIST* select_file_to_read(LIST*);                                   //прототип функции выбора файла для чтения и способа чтения
LIST* read_from_file(FILE*);                                        //прототип функции чтения информации о студентах из файла
char* get_current_string_from_file(char*, FILE*);                   //прототип функции считывания и копирования строки с информацией из файла
LIST* cpy_student_from_file_to_list(LIST*, char*);                  //прототип функции копирования информации из файла в элемент списка
char* cpy_string_from_file(char*, int*);                            //прототип функции для записи фио студента в базовую структуру элемента списка
int cpy_int_from_file(char*, int*);                                 //прототип функции для записи номера группы и оценки студента в базовую структру элемента списка
void select_show_students(LIST*);                                   //прототип функции выбора способа вывода списка студентов
void show_students(LIST*);                                          //прототип функции вывода списка студентов
void set_file_to_write(LIST*, bool, bool*);                         //прототип функции выбора файла для записи списка студентов
void write_to_file(FILE*, LIST*);                                   //прототип функции записи списка студентов в файл
LIST* card_index_processing(LIST*);                                 //прототип функции выбора способа обработки содержимого картотеки
LIST* edit_student_in_list(LIST*);                                  //прототип функции изменения информации о студенте в списке
void output_division();                                             //прототип Функции вывода строки тире(для наглядности)
void edit_student_in_file(FILE*);                                   //прототип функции изменения информации о студенте в файле
LIST* set_delete(LIST*);                                            //прототип функции выбора способа удаления студента из картотеки
LIST* delete_student(LIST*, LIST*, bool);                           //прототип функции удаления студента из картотеки
LIST* del_from_selected_pos(LIST*);                                 //прототип функции удаления определенного студента из картотеки
void select_cell_to_filtr(LIST*);                                   //прототип функции выбора поля фильтрации списка студентов
void set_student_to_search(LIST*);                                  //прототип функции ввода инфо о студенте для поиска
LIST* get_result(LIST*, LIST*, int, char*, int);                    //прототип функции формирования результата
LIST* copy_student(LIST*, LIST*, LIST**);                           //прототип функции копирования студента из одного списка в другой
char* copy_string(char*);                                           //прототип функции копирования строки
void sort_two_element(LIST**, bool*, LIST**, LIST**);               //прототип функции перемены местами двух студентов списка
int compare_string_to_sort(char*, char*);                           //прототип функции сравнения полей с фамилиями/именами/отчествами студентов для сортировки
void select_method_of_sort(LIST*);                                  //прототип функции выбора способа сортировки списка студентов
void show_result_of_processing(LIST*, LIST*, int, char*, int);      //прототип функции вывода результата
void select_show_result(LIST*, int, char*, int);                    //прототип функции выбора способа вывода результата
void show_one_element(LIST*);                                       //прототип функции вывода на экран одного элемента списка
void userhelp();                                                    //прототип функции вывода справки пользователю


int main()
{
	LIST* head_list = nullptr;     //указатель на начальный элемент исходного списка
	int c;                         //номер пункта меню

	setlocale(LC_ALL, "rus");
	do      //цикл, работающий до нажатия клавиши 5(выход)
	{
		system("cls");
		c = menu(1);
		system("cls");
		switch (c)
		{

		case 1:       //Ввод картотеки
			select_method_of_input(&head_list);
			break;

		case 2:       //Вывод картотеки
			select_show_students(head_list);
			break;

		case 3:       //Работа с картотекой
			head_list = card_index_processing(head_list);
			break;

		case 4:       //Справка
			userhelp();
			break;

		case 5:       //Выход
			head_list = cleanlist(head_list);
			break;

		default:      //некорректный ввод номера пункта меню
			puts("Такого пункта не существует!");
			system("pause");
			break;
		}
	} while (c != 5);
	return 0;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//Функция вывода меню и выбора пункта меню
//возвращает номер пункта меню
//принимает номер меню, которое необходимо вывести
int menu(int num)
{
	int c;   //номер пункта меню

	switch (num)
	{
	case 1:
		printf("%-6c%s\n\n", ' ', "ГЛАВНОЕ МЕНЮ");
		puts("1 - Ввод картотеки");
		puts("2 - Вывод картотеки");
		puts("3 - Работа с картотекой");
		puts("4 - Справка");
		puts("5 - Завершение работы");
		break;

	case 2:
		printf("%-3c%s\n\n", ' ', "МЕНЮ ВЫБОРА СПОСОБА ВВОДА");
		puts("1 - Ввод данных с клавиатуры");
		puts("2 - Ввод данных из файла");
		puts("3 - Выход");
		break;

	case 3:
		printf("%-3c%s\n\n", ' ', "МЕНЮ ВЫБОРА МЕСТА ДОБАВЛЕНИЯ СТУДЕНТА");
		puts("1 - В начало картотеки");
		puts("2 - В конец картотеки");
		puts("3 - После определенного элемента в картотеке");
		puts("4 - Выход");
		break;

	case 4:
		puts("1 - Демонстрационный файл");
		puts("2 - Файл с определенным именем");
		puts("3 - Выход");
		break;

	case 5:
		printf("%-3c%s\n\n", ' ', "МЕНЮ ВЫБОРА СПОСОБА ВВОДА ИЗ ФАЙЛА");
		puts("1 - Полностью заменить список студентов");
		puts("2 - Добавить в конец всех студентов из файла");
		puts("3 - Выход");
		break;

	case 6:
		puts("1 - Вывод на экран");
		puts("2 - Вывод в файл");
		puts("3 - Выход");
		break;

	case 7:
		printf("%-3c%s\n\n", ' ', "МЕНЮ ВЫБОРА ФАЙЛА ДЛЯ ВЫВОДА");
		puts("1 - В демонстрационный файл");
		puts("2 - В файл с определенным именем");
		puts("3 - Выход");
		break;

	case 8:
		printf("%-3c%s\n\n", ' ', "МЕНЮ ВЫБОРА МЕСТА ДОБАВЛЕНИЯ В ФАЙЛ");
		puts("1 - Заменить содержимое файла полностью");
		puts("2 - Дозаписать информацию  в конец файла");
		puts("3 - Выход");
		break;

	case 9:
		printf("\t%-3c%s\n\n", ' ', "РАБОТА С КАРТОТЕКОЙ");
		puts("1 - Изменение элемента картотеки");
		puts("2 - Удаление элемента из картотеки");
		puts("3 - Фильтрация картотеки по ключевому полю");
		puts("4 - Поиск конкретного элемента в картотеке");
		puts("5 - Сотировка картотеки по ключевому полю");
		puts("6 - Выход");
		break;

	case 10:
		printf("\t%-3c%s\n\n", ' ', "МЕНЮ ВЫБОРА СПОСОБА ИЗМЕНЕНИЯ ЭЛЕМЕНТА");
		puts("1 - Изменение элемента в оперативной памяти компьютера");
		puts("2 - Изменение элемента в файле");
		puts("3 - Выход");
		break;

	case 11:
		printf("\t%-3c%s\n\n", ' ', "МЕНЮ ВЫБОРА СПОСОБА УДАЛЕНИЯ ЭЛЕМЕНТА ИЗ КАРТОТЕКИ");
		puts("1 - Удаление начального элемента из картотеки");
		puts("2 - Удаление последнего элемента из картотеки");
		puts("3 - Удаление определенного элемента из картотеки");
		puts("4 - Выход");
		break;

	case 12:
		printf("\t%-3c%s\n\n", ' ', "МЕНЮ ВЫБОРА ПОЛЯ ДЛЯ ФИЛЬТРАЦИИ КАРТОТЕКИ");
		puts("1 - Фильтрация по фамилии");
		puts("2 - Фильтрация по имени");
		puts("3 - Фильтрация по отчеству");
		puts("4 - Фильтрация по номеру группы");
		puts("5 - Фильтрация по оценке");
		puts("6 - Выход");
		break;

	case 13:
		printf("\t\t%s\n\n", "ВЫХОД БЕЗ ПРОСМОТРА РЕЗУЛЬТАТА");
		puts("Вы уверены? Если Вы не сохранили данные, то результат обработки будет утерян!\n");
		puts("1 - Все равно выйти");
		puts("2 - Вернуться");
		break;

	case 14:
		printf("\t%-3c%s\n\n", ' ', "МЕНЮ ВЫБОРА СПОСОБА СОРТИРОВКИ ЭЛЕМЕНТОВ КАРТОТЕКИ");
		puts("1  - По фамилии по возрастанию");
		puts("2  - По имени по возрастанию");
		puts("3  - По отчеству по возрастанию");
		puts("4  - По номеру группы по возрастанию");
		puts("5  - По оценке по возрастанию");
		puts("6  - По фамилии по убыванию");
		puts("7  - По имени по убыванию");
		puts("8  - По отчеству по убыванию");
		puts("9  - По номеру группы по убыванию");
		puts("10 - По оценке по убыванию");
		puts("11 - Выход");
		break;
	}

	printf("\nВаш выбор: ");
	if (scanf_s("%d", &c) != 1)
	{
		while (fgetc(stdin) != '\n')
		{
		}
		c = -1;
	}
	return c;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//функция выбора способа ввода данных
//принимает адрес указателя на голову списка
void select_method_of_input(LIST** head)
{
	int c;     //номер пункта меню

	do
	{
		c = menu(2);
		system("cls");
		switch (c)
		{
		case 1:
			*head = select_where_student_add(*head);
			break;

		case 2:
			*head = select_file_to_read(*head);
			break;

		case 3:
			break;

		default:
			puts("Такого пункта не существует!");
			system("pause");
			break;
		}
		system("cls");
	} while (c != 3);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Функция выбора способа добавления элемента в список
//возвращает указатель на голову списка
//принимает указатель на голову списка
LIST* select_where_student_add(LIST* head)
{
	int с;                //номер пункта меню
	LIST* ptr;            //вспомогательный указатель

	do
	{
		system("cls");
		с = menu(3);
		system("cls");
		switch (с)
		{
		case 1:
			printf("\t\t%-7c%s\n\n", ' ', "Добавление студента в начало картотеки");
			if (head)
			{
				ptr = head;
				while (ptr->next != head)
					ptr = ptr->next;
				head = input_student(head, ptr, true);
			}
			else
				head = create_list(head);
			output_division();
			puts("\nВведенный Вами студент успешно добавлен!\n");
			output_division();
			system("pause");
			break;

		case 2:
			printf("\t\t%-7c%s\n\n", ' ', "Добавление студента в конец картотеки");
			if (head)
			{
				ptr = head;
				while (ptr->next != head)
					ptr = ptr->next;
				head = input_student(head, ptr, false);
			}
			else
				head = create_list(head);
			output_division();
			puts("\nВведенный Вами студент успешно добавлен!\n");
			output_division();
			system("pause");
			break;

		case 3:
			printf("\t%s\n\n", "Добавление студента после определенного элемента в картотеке");
			if (head)
				head = input_to_selected_pos(head);
			else
				puts("В картотеке еще нет ни одного элемента!\n");
			system("pause");
			break;

		case 4:
			break;

		default:
			puts("Такого пункта не существует!");
			system("pause");
			break;
		}
	} while (с != 4);
	return head;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Функция добавления студента в список
//возвращает указатель на голову списка
//принимает указатель на голову списка,
//указатель на элемент, после которого необходимо добавить новый
//и индикатор места добавления
LIST* input_student(LIST* head, LIST* previous_element, bool b)
{
	LIST* new_element;  //указатель на новый элемент в списке

	new_element = (LIST*)malloc(sizeof(LIST));
	new_element->next = previous_element->next;
	previous_element->next = new_element;
	new_element = set_info_about_student(new_element);
	if (b)
		return new_element;
	else
		return head;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//функция ввода информации о студенте
//возвращает указатель на элемент с инфо о студенте
//принимает указатель на элемент, инфо о котором
//необходимо ввести
LIST* set_info_about_student(LIST* data)
{
	puts("Ввод данных:");
	puts("\n-Введите фамилию студента:");
	data->inital_data.surname = set_x_name(true);
	puts("-Введите имя студента:");
	data->inital_data.name = set_x_name(true);
	puts("-Введите отчество студента:");
	data->inital_data.patr = set_x_name(true);
	data->inital_data.group = set_x_number(true);
	data->inital_data.mark = set_x_number(false);
	return data;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Функция ввода фамилии/имени/отчества студента
//возвращает указатель на начальный символ строки
//принимает индикатор проведения проверки корректности символов
char* set_x_name(bool flag)
{
	char* x_name = nullptr;     //указатель на начальный символ строки(среда просила поставить nullptr)
	int i = 0;                  //вспомогательная переменная
	bool flag_to_check_symbols; //индикатор корректности текущего символа

	do
	{
		flag_to_check_symbols = true;
		do
		{
			x_name = (char*)realloc(x_name, (i + 1) * sizeof(char));
			*(x_name + i) = _getche();
			if (*(x_name + i) == 8)
				x_name = imitate_backspace(x_name, &i);
			else
				if (flag)
					flag_to_check_symbols = check_true_symbols(x_name, i);
			i++;
		} while (flag_to_check_symbols && i < 18 && *(x_name + i - 1) != 13);

		if (!flag_to_check_symbols)
		{
			if (*(x_name + i - 1) == 32)
				puts("\nВведен недопустимый символ - пробел!\n\nНачните ввод этого поля заново:");
			else
			{
				puts("\nВы можете использовать только строчные и заглавные буквы латинского алфавита!\n");
				puts("Начните ввод этого поля заново:");
			}
			x_name = clean(x_name);
			i = 0;
		}
		else
		{
			if (*(x_name + i - 1) == 13 && i == 1)
			{
				if (!flag)
					puts("Вы ничего не ввели.\n\nНачните ввод этого поля заново:");
				x_name = clean(x_name);
				i = 0;
			}
			else
			{
				if (*(x_name + i - 1) == 13)
					(*(x_name + i - 1)) = '\0';
				else
				{
					x_name = (char*)realloc(x_name, (i + 1) * sizeof(char));
					*(x_name + i) = '\0';
				}
				if (flag)
					puts("\nВвод прошел успешно!\n");
			}
		}
	} while (x_name == NULL);
	return x_name;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//функция имитации нажатия клавиши backspace
//возвращает указатель на начальный символ строки
//принимает указатель на начальный символ строки
//и указатель на индекс текущего элемента в строке
char* imitate_backspace(char* x_name, int* i)
{
	printf("\r%18c\r", ' ');
	printf("\b");
	if (*i == 0)
		(*i)--;
	else
		if (*i == 1)
			(*i) -= 2;
		else
		{
			(*i) -= 2;
			x_name = (char*)realloc(x_name, (*i + 1) * sizeof(char));
			for (int j = 0; j <= *i; j++)
				printf("%c", *(x_name + j));
		}

	return x_name;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//функция порверки корректности введенного символа
//возвращает true - символ корректен, false - не корректен
//принимает указатель на начальный символ строки
//и номер позиции которую необходимо проверить
bool check_true_symbols(char* x_name, int i)
{
	if (*(x_name + i) == 13 || ('a' <= *(x_name + i) && *(x_name + i) <= 'z') || ('A' <= *(x_name + i) && *(x_name + i) <= 'Z'))
		return true;
	else
		return false;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//функция освобождения памяти из-под строки символов
//возвращает нулевой указатель
//принимает указатель на начальный символ строки
char* clean(char* str)
{
	if (str)
		free(str);
	return NULL;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//функция ввода номера группы/оценки студента
//возвращает номер группы/оценку
//принимает индикатор: true - вводим номер группы,
//false - вводим оценку
int set_x_number(bool flag)
{
	int number;            //число - результат
	bool exit_code;        //индикатор некорректного ввода

	if (flag)
		puts("Номер группы может содержать не более 4 цифр!");
	else
		puts("Оценка может быть от 2 до 5!");
	do
	{
		exit_code = true;

		if (flag)
			puts("\n-Вводите номер группы:");
		else
			puts("\n-Вводите оценку студента:");

		if (scanf_s("%d", &number) != 1)
		{
			while (fgetc(stdin) != '\n')
			{
			}
			puts("\nДолжно быть введено число!");
			exit_code = false;
		}
		else
		{
			if (flag)
			{
				if (number < 1 || number > 9999)
				{
					puts("\nНомер группы должен быть не меньше 1 и не больше 9999!");
					exit_code = false;
				}
			}
			else
			{
				if (number < 2 || number > 5)
				{
					puts("\nОценка должна быть не меньше 2 и не больше 5!");
					exit_code = false;
				}
			}
		}
	} while (!exit_code);
	if (flag)
		puts("\nВвод номера группы прошел успешно!\n");
	else
		puts("\nВвод оценки прошел успешно!\n");
	return number;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Функция создания списка
//возвращает указатель на голову списка
//принимает указатель на голову списка
LIST* create_list(LIST* head)
{
	head = (LIST*)malloc(sizeof(LIST));
	head = set_info_about_student(head);
	head->next = head;
	return head;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Функция добавления элемента в определенное место списка
//возвращает указатель на голову списка
//принимает указатель на голову списка
LIST* input_to_selected_pos(LIST* head)
{
	LIST* ptr;         //вспомогательный указатель на элемент списка
	LIST* search_stud; //Указатель на элемент с инфо о студенте, после которого нужно добавить нового

	puts("\nВведите информацию о студенте, после которого необходимо добавить нового\nстудента:\n");
	search_stud = (LIST*)malloc(sizeof(LIST));
	search_stud->next = search_stud;
	search_stud = set_info_about_student(search_stud);
	ptr = search_student(head, search_stud);
	if (ptr)
	{
		ptr = ptr->next; //так как предыдущий нашли
		output_division();
		puts("Студент, введенный Вами, был найден!\n");
		show_one_element(ptr);
		output_division();
		puts("Введите информацию о студенте, которого необходимо добавить:");
		head = input_student(head, ptr, false);
		output_division();
		puts("\nВведенный Вами студент успешно добавлен!\n");
		output_division();
	}
	else
	{
		output_division();
		puts("\n\nВведенный вами студент не был найден!\n\n");
		output_division();
	}
	search_stud = cleanlist(search_stud);

	return head;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//функция нахождения элемента в списке
//возвращает указатель на элемент списка, предыдущий искомому
//принимает указатель на голову списка
//и указатель на элемент с инфо об искомом студенте
LIST* search_student(LIST* head, LIST* stud_search)
{
	LIST* ptr = head;    //вспомогательный указатель
	bool flag = false;   //индикатор наличия искомого студента в списке
	do
	{
		if (compare_student(ptr->next, stud_search))
			flag = true;
		else
		{
			if (ptr->next->next == head->next)
				return NULL;
			else
				ptr = ptr->next;
		}
	} while (!flag);
	return ptr;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//функция сравнения информационных полей двух элементов списка
//возвращает true - если их поля равны, false - не равны
//принимает два указателя на элементы, информационные поля которых необходимо сравнить
bool compare_student(LIST* data1, LIST* data2)
{
	if (compare_string(data1->inital_data.surname, data2->inital_data.surname) && compare_string(data1->inital_data.name, data2->inital_data.name) &&
		compare_string(data1->inital_data.patr, data2->inital_data.patr) && data1->inital_data.group == data2->inital_data.group && data1->inital_data.mark == data2->inital_data.mark)
		return true;
	else
		return false;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Функция сравнения двух строк
//возвращает true - если строки равны, false - не равны
//принимает два указателя на начальный символы строк, которые необходимо сравнить
bool compare_string(char* str1, char* str2)
{
	int i = 0;        //вспомогательная переменная
	bool flag = true; //индикатор равенства строк

	if (string_length(str1) == string_length(str2))
		do
		{
			if (str1[i] != str2[i])
				flag = false;
			i++;
		} while (flag && str1[i] != '\0');
	else
		flag = false;
	return flag;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//функция определения длины строки
//возвращает длину строки
//принимает указатель на начальный символ строки
int string_length(char* str)
{
	int i = 0;  //вспомогательная переменная
	if (!str)
		return 0;
	while (str[i] != '\0')
		i++;
	return i;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//функция освобождения памяти из-под списка
//возвращает указатель на голову списка
//принимает указатель на голову списка
LIST* cleanlist(LIST* head)
{
	LIST* ptr; //вспомогательный указатель

	if (head)
	{
		if (head->next != head)
		{
			ptr = head->next;
			while (ptr != head)
			{
				clean_base_struct(ptr);
				head->next = ptr->next;
				free(ptr);
				ptr = head->next;
			}
		}
		clean_base_struct(head);
		free(head);
	}
	return NULL;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//функция освобождения памяти из-под полей базовой структуры
//принимает указатель на элемент списка
void clean_base_struct(LIST* ptr)
{
	free(ptr->inital_data.surname);
	free(ptr->inital_data.name);
	free(ptr->inital_data.patr);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//функция выбора файла для чтения и способа чтения
//возвращает указатель на голову списка
//принимает указатель на голову списка
LIST* select_file_to_read(LIST* head)
{
	LIST* ptr = NULL;          //указатель на голову считанного списка
	LIST* help_ptr;            //вспомогательный указатель
	int c1,                    //номер пункта меню
		c2;                    //номер пункта меню
	char* name_of_file = NULL; //указатель на начальный символ строки - имени файла
	FILE* ptr_to_file = NULL;  //указатель на файл
							   //среда просила инициализировать

	do
	{
		system("cls");
		printf("%-3c%s\n\n", ' ', "МЕНЮ ВЫБОРА ФАЙЛА ДЛЯ ВВОДА");
		c1 = menu(4);
		system("cls");
		if (c1 == 1 || c1 == 2)
		{
			do
			{
				system("cls");
				c2 = menu(5);
				system("cls");
				if (c2 == 1 || c2 == 2)
				{
					if (c1 == 2)
					{
						printf("\t\t%s\n\n", "ВВОД ИЗ ФАЙЛА С ОПРЕДЕЛЕННЫМ ИМЕНЕМ");
						puts("! Необходимо указаывать расширение файла.\nПример ввода: Myfile.txt\n");
						puts("Введите имя файла из которого будет происходить запись:");
						name_of_file = set_x_name(false);
						puts("\n");
						ptr_to_file = fopen(name_of_file, "r");
						ptr = read_from_file(ptr_to_file);
					}
					else
					{
						printf("\t\t%s\n\n", "ВВОД ИЗ ДЕМОНСТРАЦИОННОГО ФАЙЛА");
						ptr_to_file = fopen("input-output.txt", "r");
						ptr = read_from_file(ptr_to_file);
					}
				}
				switch (c2)
				{
				case 1:
					if (ptr)
					{
						head = cleanlist(head);
						head = ptr;
						output_division();
						puts("\nЗапись данных из файла прошла успешно!\n");
						output_division();
					}
					system("pause");
					break;

				case 2:
					if (ptr)
					{
						if (head)
						{
							help_ptr = head;
							while (help_ptr->next != head)
								help_ptr = help_ptr->next;
							help_ptr->next = ptr;
							help_ptr = help_ptr->next;
							while (help_ptr->next != ptr)
								help_ptr = help_ptr->next;
							help_ptr->next = head;
						}
						else
							head = ptr;
						output_division();
						puts("\nЗапись данных из файла прошла успешно!\n");
						output_division();
					}
					system("pause");
					break;

				case 3:
					if (c1 == 2)
						name_of_file = clean(name_of_file);
					break;

				default:
					system("cls");
					puts("Такого пункта не существует!");
					system("pause");
					break;
				}
			} while (c2 != 3);
		}
		else
			if (c1 != 3)
			{
				system("cls");
				puts("Такого пункта не существует!");
				system("pause");
			}
	} while (c1 != 3);

	return head;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//функция чтения информации о студентах из файла
//возвращает указатель на голову списка
//принимает указатель на файл
LIST* read_from_file(FILE* ptr_to_file)
{
	LIST* head = nullptr;                     //указатель на голову нового(считанного) списка
	LIST* ptr = nullptr;                      //вспомогательный указатель
											  //среда просила инициализировать
	char symbol;                              //текущий символ в файле
	char* current_string_from_file;           //указатель на начальный символ текущей строки из файла

	if (ptr_to_file)
	{
		if (fgetc(ptr_to_file) == EOF)
		{
			output_division();
			puts("\nВыбранный файл пуст!\n");
			output_division();
		}
		else
		{
			rewind(ptr_to_file);
			do
			{
				current_string_from_file = get_current_string_from_file(&symbol, ptr_to_file);

				if (symbol != EOF)
				{
					if (!head)
					{
						ptr = (LIST*)malloc(sizeof(LIST));
						head = ptr;
					}
					else
					{
						ptr->next = (LIST*)malloc(sizeof(LIST));
						ptr = ptr->next;
					}
					ptr = cpy_student_from_file_to_list(ptr, current_string_from_file);
					current_string_from_file = clean(current_string_from_file);
				}
			} while (symbol != EOF);
			ptr->next = head;
		}
	}
	else
	{
		output_division();
		puts("\nВыбранный файл не найден!\n");
		output_division();
	}

	if (ptr_to_file)
		fclose(ptr_to_file);

	return head;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//функция считывания и копирования строки с информацией из файла
//возвращает указатель на начальный символ текущей строки из файла
//принимает указатель на текущий символ в строке, указатель на файл 
char* get_current_string_from_file(char* symbol, FILE* ptr_to_file)
{
	char* current_string_from_file = NULL;//указатель на начальный символ текущей строки, считанной из файла
										  //среда просила инициализировать
	int i = 0;                            //вспомогательная переменная

	while ((*symbol = fgetc(ptr_to_file)) != EOF && *symbol != '\n')
	{
		current_string_from_file = (char*)realloc(current_string_from_file, (i + 1) * sizeof(char));
		current_string_from_file[i++] = *symbol;
	}
	current_string_from_file = (char*)realloc(current_string_from_file, (i + 1) * sizeof(char));
	current_string_from_file[i] = '\0';

	return current_string_from_file;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//функция копирования информации из файла в элемент списка
//возвращает указатель на элемент списка с инфо, считанной из файла
//принимает указатель на элемент списка, в котрый будет происходить запись
//и указатель на начальный символ текущей строки, считанной из файла
LIST* cpy_student_from_file_to_list(LIST* new_student, char* current_string_from_file)
{
	int i = 0;   //текущая позиция в скопированной строке из файла
	new_student->inital_data.surname = cpy_string_from_file(current_string_from_file, &i);
	new_student->inital_data.name = cpy_string_from_file(current_string_from_file, &i);
	new_student->inital_data.patr = cpy_string_from_file(current_string_from_file, &i);
	new_student->inital_data.group = cpy_int_from_file(current_string_from_file, &i);
	new_student->inital_data.mark = cpy_int_from_file(current_string_from_file, &i);
	return new_student;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//функция для записи фио студента в базовую структуру элемента списка
//возвращает указатель на начальный символ строки
//принимает указатель на начальный символ текущей строки из файла
//и указатель на индекс текущего элемента в строке
char* cpy_string_from_file(char* current_string_from_file, int* i)
{
	char* string_field = nullptr;  //указатель на начальный символ в строке
	int j = 0;                     //вспомогательная переменная

	while (current_string_from_file[*i] != ' ')
	{
		string_field = (char*)realloc(string_field, (j + 1) * sizeof(char));
		string_field[j++] = current_string_from_file[(*i)++];
	}
	string_field = (char*)realloc(string_field, (j + 1) * sizeof(char));
	string_field[j] = '\0';

	while (current_string_from_file[*i] == ' ')
		(*i)++;

	return string_field;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//функция для записи номера группы и оценки студента в базовую структру элемента списка
//возвращает число(номер группы/оценка)
//принимает указатель на начальный символ текущей строки, считанной из файла
//и указатель на индекс текущего элемента в строке
int cpy_int_from_file(char* current_string_from_file, int* i)
{
	int number = 0;         //число - результат
	int help_namber = 1;    //вспомогательная переменная
	int help_value = 1;     //вспомогательная переменная

	while (*(current_string_from_file + *i + help_namber) != ' ' && *(current_string_from_file + *i + help_namber) != '\0')
	{
		help_namber++;
		help_value *= 10;
	}

	while (help_value != 0)
	{
		number += (current_string_from_file[(*i)++] - 48) * help_value;
		help_value /= 10;
	}

	while (current_string_from_file[*i] == ' ')
		(*i)++;
	return number;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//функция выбора способа вывода списка
//принимает указатель на голову списка
void select_show_students(LIST* head)
{
	int c;  //номер пункта меню

	if (head)
	{
		do
		{
			system("cls");
			printf("%-3c%s\n\n", ' ', "МЕНЮ ВЫБОРА СПОСОБА ВЫВОДА КАРТОТЕКИ");
			c = menu(6);
			system("cls");
			switch (c)
			{
			case 1:
				printf("\t\t\t%s\n\n", "ВЫВОД КАРТОТЕКИ НА ЭКРАН");
				show_students(head);
				system("pause");
				break;

			case 2:
				printf("\t\t\t%s\n\n", "ВЫВОД В ФАЙЛ");
				set_file_to_write(head, false, nullptr);
				break;

			case 3:
				break;

			default:
				puts("Такого пункта не существует!");
				system("pause");
				break;
			}
		} while (c != 3);
	}
	else
	{
		printf("%-3c%s\n\n", ' ', "МЕНЮ ВЫБОРА СПОСОБА ВЫВОДА КАРТОТЕКИ");
		puts("В картотеке нет ни одного элемента!\n");
		system("pause");
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Функция вывода элементов списка на экран
//принимает указатель на голову списка
void show_students(LIST* head)
{
	LIST* help_ptr = head;  //вспомогательный указатель

	if (help_ptr == NULL)
		puts("В картотеке нет ни одного элемента!");
	else
	{
		printf("Фамилия             Имя                 Отчество           Группа  Оценка\n");
		do
		{
			printf("%-18s  %-18s  %-18s  %-5d    %d\n", help_ptr->inital_data.surname, help_ptr->inital_data.name, help_ptr->inital_data.patr, help_ptr->inital_data.group, help_ptr->inital_data.mark);
			help_ptr = help_ptr->next;
		} while (help_ptr != head);
		puts("");
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//функция выбора файла для записи списка в него
//принимает указатель на голову списка,
//индикатор необходимости выполнения некоторых действий,
//указатель на индикатор вывода сообщения
void set_file_to_write(LIST* head, bool flag, bool* result_code)
{
	FILE* ptr_to_file;            //указатель на файл
	int c1,                       //номер пункта меню
		c2;                       //номер пункта меню
	char* name_of_file = NULL;    //указатель на начальный символ строки - имени файла
								  //среда просила инициализировать

	if (head)
	{
		do
		{
			system("cls");
			c1 = menu(7);
			system("cls");
			if (c1 == 1 || c1 == 2)
			{
				do
				{
					system("cls");
					c2 = menu(8);
					system("cls");
					if (c2 == 1 || c2 == 2)
					{
						if (c1 == 2)
						{
							printf("\t\t%-5c%s\n\n", ' ', "ВЫВОД В ФАЙЛ С ОПРЕДЕЛЕННЫМ ИМЕНЕМ");
							puts("! Необходимо указаывать расширение файла.\nПример ввода: Myfile.txt\n");
							puts("Введите имя файла в который будет происходить запись:");
							name_of_file = set_x_name(false);
							puts("\n");
						}
						else
							printf("\t\t%s\n\n", "ВЫВОД В ДЕМОНСТРАЦИОННЫЙ ФАЙЛ");
					}
					switch (c2)
					{
					case 1:
						if (c1 == 1)
							ptr_to_file = fopen("input-output.txt", "w");
						else
							ptr_to_file = fopen(name_of_file, "w");

						write_to_file(ptr_to_file, head);

						if (flag)
						{
							c1 = 3;
							c2 = 3;
							*result_code = false;
						}
						system("pause");
						break;

					case 2:
						if (c1 == 1)
							ptr_to_file = fopen("input-output.txt", "a");
						else
							ptr_to_file = fopen(name_of_file, "a");

						write_to_file(ptr_to_file, head);

						if (flag)
						{
							c1 = 3;
							c2 = 3;
							*result_code = false;
						}
						system("pause");
						break;

					case 3:
						if (c1 == 2)
							name_of_file = clean(name_of_file);
						break;

					default:
						puts("Такого пункта не существует!");
						system("pause");
						break;
					}
				} while (c2 != 3);
			}
			else
				if (c1 != 3)
				{
					puts("Такого пункта не существует!");
					system("pause");
				}
		} while (c1 != 3);
	}
	else
	{
		puts("В картотеке нет ни одного элемента!");
		system("pause");
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//функция записи списка в файл
//принимает указатель на файл,
//указатель на голову списка
void write_to_file(FILE* ptr_to_file, LIST* head)
{
	LIST* ptr = head;  //вспомогательный указатель
	int exit_code;    //индикатор корректной записи в файл

	if (ptr_to_file)
	{
		do
		{
			exit_code = fprintf(ptr_to_file, "%-18s %-18s %-18s %-6d %d\n", ptr->inital_data.surname, ptr->inital_data.name, ptr->inital_data.patr, ptr->inital_data.group, ptr->inital_data.mark);
			ptr = ptr->next;
		} while (ptr != head && exit_code == 66);
		output_division();
		if (exit_code == 66)
			puts("\nЗапись в файл прошла успешно!\n");
		else
			puts("\nВо время записи в файл произошла ошибка!\n");
		output_division();
		fclose(ptr_to_file);
	}
	else
		puts("\nВо время отрытия файла произошла ошибка!\n");
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//функция выбора способа обработки содержимого картотеки
//возвращает указатель на голову списка
//принимает указатель на голову списка
LIST* card_index_processing(LIST* head)
{
	int c1,              //номер пункта меню
		c2,              //номер пункта меню
		c3;              //номер пункта меню
	FILE* ptr_to_file;   //указатель на файл

	do
	{
		system("cls");
		c1 = menu(9);
		system("cls");
		switch (c1)
		{
		case 1:
			do
			{
				system("cls");
				c2 = menu(10);
				system("cls");
				switch (c2)
				{
				case 1:
					printf("\t%-2c%s\n\n", ' ', "ИЗМЕНЕНИЕ ЭЛЕМЕНТА КАРТОТЕКИ В ОПЕРАТИВНОЙ ПАМЯТИ\n");
					head = edit_student_in_list(head);
					break;

				case 2:
					do
					{
						system("cls");
						printf("\t%s\n\n", "МЕНЮ ВЫБОРА ФАЙЛА ДЛЯ ИЗМЕНЕНИЯ ЭЛЕМЕНТА");
						c3 = menu(4);
						system("cls");
						switch (c3)
						{
						case 1:
							printf("\t%s\n\n", "ИЗМЕНЕНИЕ ЭЛЕМЕНТА В ДЕМОНСТРАЦИОННОМ ФАЙЛЕ");
							ptr_to_file = fopen("input-output.txt", "r+");
							edit_student_in_file(ptr_to_file);
							break;

						case 2:
							printf("\t\t%-5c%s\n\n", ' ', "ИЗМЕНЕНИЕ ЭЛЕМЕНТА В ФАЙЛЕ С ОПРЕДЕЛЕННЫМ ИМЕНЕМ");
							puts("! Необходимо указаывать расширение файла.\nПример ввода: Myfile.txt\n");
							puts("Введите имя файла в который будет происходить запись:");
							ptr_to_file = fopen(set_x_name(false), "r+");
							edit_student_in_file(ptr_to_file);
							break;

						case 3:
							break;

						default:
							system("cls");
							puts("Такого пункта не существует!");
							system("pause");
							break;
						}
					} while (c3 != 3);
					break;

				case 3:
					break;

				default:
					system("cls");
					puts("Такого пункта не существует!");
					system("pause");
					break;
				}
			} while (c2 != 3);
			break;

		case 2:
			head = set_delete(head);
			break;

		case 3:
			select_cell_to_filtr(head);
			break;

		case 4:
			set_student_to_search(head);
			break;

		case 5:
			select_method_of_sort(head);
			break;

		case 6:
			break;

		default:
			system("cls");
			puts("Такого пункта не существует!");
			system("pause");
			break;
		}
	} while (c1 != 6);

	return head;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//функция изменения информации о студенте в списке
//возвращает указатель на голову списка
//принимает указатель на голову списка
LIST* edit_student_in_list(LIST* head)
{
	LIST* searched_element;     //указатель на вспомогательный элемент, который необходимо найти в списке
	LIST* result_of_search;     //указатель на элемент списка, в котором записано инфо об искомом студенте

	if (head)
	{
		puts("Введите информацию о студенте, данные о котором хотите изменить:\n");
		searched_element = (LIST*)malloc(sizeof(LIST));
		searched_element->next = searched_element;
		searched_element = set_info_about_student(searched_element);
		result_of_search = search_student(head, searched_element);
		if (result_of_search)
		{
			output_division();
			result_of_search = result_of_search->next;//так как нашли предыдущий
			printf("\t\t\t%s\n", "Результат поиска\n");
			show_one_element(result_of_search);
			puts("\nДанный студент, введенный Вами, был найден!");
			output_division();
			puts("\nВводите новую информацию об этом студенте:\n");
			clean_base_struct(result_of_search);
			result_of_search = set_info_about_student(result_of_search);
			output_division();
			puts("\nИзменение прошло успешно!\n");
			output_division();
		}
		else
		{
			output_division();
			printf("\t\t\t%s\n", "Результат поиска\n");
			puts("\nВведенный Вами студент не был найден!");
			output_division();
		}
		searched_element = cleanlist(searched_element);
	}
	else
		puts("В картотеке нет ни одного элемента!\n");

	system("pause");

	return head;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Функция вывода строки тире(для наглядности)
//ничего не принимает и ничего не возвращает
void output_division()
{
	for (int i = 0; i < 80; i++)
		printf("%c", '-');
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//функция изменения информации о студенте в файле
//принимает указатель на файл,
void edit_student_in_file(FILE* ptr_to_file)
{
	LIST* info_about_current_stud;           //указатель на элемент, хранящий инфо о текущем считываемом студенте из файла
	LIST* searched_student;                  //указатель на элемент, хранящий инфо об искомом студенте
	LIST* new_info = NULL;                   //указатель на элемент, хранящий измененную информация о выбранном студенте
											 //среда просила инициализировать
	char* current_string_from_file;          //указатель на начальный символ текущей строки, считанной из файла
	char symbol;                             //вспомогательная переменная для считывания информации из файла
	bool flag;                               //индикатор равенства искомого студента и текущего, считованного из файла
	int exit_code;                           //индикатор корректной записи в файл

	if (ptr_to_file)
	{
		if (fgetc(ptr_to_file) == EOF)
		{
			puts("");
			output_division();
			puts("\nВыбранный файл пуст!\n");
			output_division();
		}
		else
		{
			rewind(ptr_to_file);
			puts("");
			output_division();
			puts("\nФайл, выбранный Вами, найден!\n");
			output_division();
			puts("Введите информацию о студенте, данные о котором хотите изменить:\n");
			searched_student = (LIST*)malloc(sizeof(LIST));
			searched_student->next = searched_student;
			searched_student = set_info_about_student(searched_student);
			do
			{
				current_string_from_file = get_current_string_from_file(&symbol, ptr_to_file);
				info_about_current_stud = (LIST*)malloc(sizeof(LIST));
				info_about_current_stud->next = info_about_current_stud;
				info_about_current_stud = cpy_student_from_file_to_list(info_about_current_stud, current_string_from_file);
				flag = compare_student(info_about_current_stud, searched_student);
				current_string_from_file = clean(current_string_from_file);
				info_about_current_stud = cleanlist(info_about_current_stud);
			} while (symbol != EOF && !flag);

			if (flag)
			{
				output_division();
				printf("\t\t\t%s\n", "Результат поиска\n");
				puts("\nДанный студент, введенный Вами, был найден!");
				output_division();
				puts("Вводите новую информацию об этом студенте:\n");
				new_info = (LIST*)malloc(sizeof(LIST));
				new_info->next = new_info;
				new_info = set_info_about_student(new_info);
				fseek(ptr_to_file, -(long)(67 * sizeof(char)), 1);
				exit_code = fprintf(ptr_to_file, "%-18s %-18s %-18s %-6d %d", new_info->inital_data.surname, new_info->inital_data.name, new_info->inital_data.patr, new_info->inital_data.group, new_info->inital_data.mark);
				output_division();
				if (exit_code == 65)
					puts("\nИзменение прошло успешно!\n");
				else
					puts("\nОшибка при изменении содержимого файла!\n");
				output_division();
			}
			else
			{
				output_division();
				printf("\t\t\t%s\n", "Результат поиска\n");
				puts("\nВведенный Вами студент не был найден!\n");
				output_division();
			}
			searched_student = cleanlist(searched_student);
			new_info = cleanlist(new_info);
		}
	}
	else
	{
		puts("");
		output_division();
		puts("\nВыбранный Вами файл не найден!\n");
		output_division();
	}

	if (ptr_to_file)
		fclose(ptr_to_file);

	system("pause");
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Функция выбора способа удаления элемента из списка
//возвращает указатель на голову списка
//принимает указатель на голову списка
LIST* set_delete(LIST* head)
{
	int с;          //номер пункта меню
	LIST* help_ptr; //вспомогательный указатель

	if (head == NULL)
	{
		printf("\t%-3c%s\n\n", ' ', "МЕНЮ ВЫБОРА СПОСОБА УДАЛЕНИЯ ЭЛЕМЕНТА ИЗ КАРТОТЕКИ");
		puts("\nВ картотеке нет ни одного элемента!\n");
		system("pause");
	}
	else
	{
		do
		{
			system("cls");
			с = menu(11);
			system("cls");
			switch (с)
			{
			case 1:
				printf("\t\t%-5c%s\n\n", ' ', "УДАЛЕНИЕ НАЧАЛЬНОГО ЭЛЕМЕНТА ИЗ КАРТОТЕКИ");
				if (head)
				{
					help_ptr = head;
					while (help_ptr->next != head)
						help_ptr = help_ptr->next;
					head = delete_student(head, help_ptr, true);
				}
				else
					puts("\nВ картотеке нет ни одного элемента!\n");
				system("pause");
				break;

			case 2:
				printf("\t\t%-5c%s\n\n", ' ', "УДАЛЕНИЕ ПОСЛЕДНЕГО ЭЛЕМЕНТА ИЗ КАРТОТЕКИ");
				if (head)
				{
					help_ptr = head;
					while (help_ptr->next->next != head)
						help_ptr = help_ptr->next;
					head = delete_student(head, help_ptr, false);
				}
				else
					puts("\nВ картотеке нет ни одного элемента!\n");
				system("pause");
				break;

			case 3:
				printf("\t\t%-5c%s\n\n", ' ', "УДАЛЕНИЕ ОПРЕДЕЛЕННОГО ЭЛЕМЕНТА ИЗ КАРТОТЕКИ");
				if (head)
					head = del_from_selected_pos(head);
				else
					puts("\nВ картотеке нет ни одного элемента!\n");
				system("pause");
				break;

			case 4:
				break;

			default:
				system("cls");
				puts("Такого пункта не существует!");
				system("pause");
				break;
			}
		} while (с != 4);
	}

	return head;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Функция удаления элемента из списка
//возвращает указатель на голову списка
//принимает указатель на голову списка,
//указатель на элемент списка предшествующий удаляемому, индикатор
LIST* delete_student(LIST* head, LIST* ptr1, bool flag)
{
	LIST* ptr2 = ptr1->next;  //вспомогательный указатель

	if (ptr1 == ptr2)
	{
		ptr2 = cleanlist(ptr2);
		output_division();
		puts("Удаление прошло успешно!\n");
		output_division();
		return NULL;
	}
	else
	{
		ptr1->next = ptr2->next;
		ptr2->next = ptr2;
		ptr2 = cleanlist(ptr2);
		output_division();
		puts("Удаление прошло успешно!\n");
		output_division();
		if (flag)
			return ptr1->next;
		return head;
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Функция удаления определенного элемента из списка
//возвращает указатель на голову списка
//принимает указатель на голову списка
LIST* del_from_selected_pos(LIST* head)
{
	LIST* ptr;                //вспомогательный указатель
	LIST* stud_search;        //указатель на элемент, хранящий инфо об искомом студенте

	puts("Введите информацию о студенте, которго необходимо удалить:\n");
	stud_search = (LIST*)malloc(sizeof(LIST));
	stud_search->next = stud_search;
	stud_search = set_info_about_student(stud_search);
	ptr = search_student(head, stud_search);
	if (ptr)
	{
		output_division();
		puts("\n\nДанный студент, введенный Вами, был найден!\n\n");
		if (ptr->next == head)
			head = delete_student(head, ptr, true);
		else
			head = delete_student(head, ptr, false);
	}
	else
	{
		output_division();
		puts("\n\nВведенный Вами студент не был найден!\n\n");
		output_division();
	}
	stud_search = cleanlist(stud_search);

	return head;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//функция выбора поля фильтрации списка студентов
//принимает указатель на голову списка
void select_cell_to_filtr(LIST* head)
{
	int c;               //номер пункта меню
	char* str = NULL;    //указатель на начальный символ строки
	int number;          //номер поля

	if (head)
	{
		do
		{
			system("cls");
			c = menu(12);
			system("cls");
			switch (c)
			{
			case 1:
				printf("\t\t%s\n\n", "ФИЛЬТРАЦИЯ ЭЛЕМЕНТОВ КАРТОТЕКИ ПО ЗАДАННОЙ ФАМИЛИИ");
				puts("Введите фамилию, по которой необходимо выполнить фильтрацию:");
				str = set_x_name(true);
				system("pause");
				output_division();
				puts("\nФильтрация элементов картотеки по фамилии прошла успешно!\n");
				output_division();
				printf("Для перехода к меню просмотра результата нажмите любую клавишу");
				_getche();
				show_result_of_processing(get_result(head, nullptr, 1, str, -1), nullptr, 1, str, -1);
				c = 6;
				break;

			case 2:
				printf("\t\t%s\n\n", "ФИЛЬТРАЦИЯ ЭЛЕМЕНТОВ КАРТОТЕКИ ПО ЗАДАННОМУ ИМЕНИ");
				puts("Введите имя, по которому необходимо выполнить фильтрацию:");
				str = set_x_name(true);
				system("pause");
				output_division();
				puts("\nФильтрация элементов картотеки по имени прошла успешно!\n");
				output_division();
				printf("Для перехода к меню просмотра результата нажмите любую клавишу");
				_getche();
				show_result_of_processing(get_result(head, nullptr, 2, str, -1), nullptr, 2, str, -1);
				c = 6;
				break;

			case 3:
				printf("\t\t%s\n\n", "ФИЛЬТРАЦИЯ ЭЛЕМЕНТОВ КАРТОТЕКИ ПО ЗАДАННОМУ ОТЧЕСТВУ");
				puts("Введите отчество, по которому необходимо выполнить фильтрацию:");
				str = set_x_name(true);
				system("pause");
				output_division();
				puts("\nФильтрация элементов картотеки по отчеству прошла успешно!\n");
				output_division();
				printf("Для перехода к меню просмотра результата нажмите любую клавишу");
				_getche();
				show_result_of_processing(get_result(head, nullptr, 3, str, -1), nullptr, 3, str, -1);
				c = 6;
				break;

			case 4:
				printf("\t\t%s\n\n", "ФИЛЬТРАЦИЯ ЭЛЕМЕНТОВ КАРТОТЕКИ ПО ЗАДАННОМУ НОМЕРУ ГРУППЫ");
				puts("Введите номер группы, по которому необходимо выполнить фильтрацию:");
				number = set_x_number(true);
				system("pause");
				output_division();
				puts("\nФильтрация элементов картотеки по номеру группы прошла успешно!\n");
				output_division();
				printf("Для перехода к меню просмотра результата нажмите любую клавишу");
				_getche();
				show_result_of_processing(get_result(head, nullptr, 4, nullptr, number), nullptr, 4, nullptr, number);
				c = 6;
				break;

			case 5:
				printf("\t\t%s\n\n", "ФИЛЬТРАЦИЯ ЭЛЕМЕНТОВ КАРТОТЕКИ ПО ЗАДАННОЙ ОЦЕНКЕ");
				puts("Введите оценку, по которой необходимо выполнить фильтрацию:");
				number = set_x_number(false);
				system("pause");
				output_division();
				puts("\nФильтрация элементов картотеки по оценке прошла успешно!\n");
				output_division();
				printf("Для перехода к меню просмотра результата нажмите любую клавишу");
				_getche();
				show_result_of_processing(get_result(head, nullptr, 5, nullptr, number), nullptr, 5, nullptr, number);
				c = 6;
				break;

			case 6:
				break;

			default:
				system("cls");
				puts("Такого пункта не существует!");
				system("pause");
				break;
			}
			str = clean(str);
		} while (c != 6);
	}
	else
	{
		printf("\t%-3c%s\n\n", ' ', "МЕНЮ ВЫБОРА ПОЛЯ ДЛЯ ФИЛЬТРАЦИИ КАРТОТЕКИ");
		puts("В картотеке нет ни одного элемента!\n");
		system("pause");
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//функция ввода инфо о студенте для поиска
//принимает указатель на голову списка
void set_student_to_search(LIST* head)
{
	LIST* key_student; //указатель на элемент, хранящий инфо об искомом студенте

	printf("\t\t%s\n\n", "ВВОД ИНФОРОМАЦИИ О СТУДЕНТЕ ДЛЯ ПОИСКА");
	if (head)
	{
		puts("Введите информацию о студенте, которого необходимо найти:\n");
		key_student = (LIST*)malloc(sizeof(LIST));
		key_student->next = key_student;
		key_student = set_info_about_student(key_student);
		output_division();
		puts("\nПоиск элемента в картотеке прошел успешно!\n");
		output_division();
		printf("Для перехода к меню просмотра результата нажмите любую клавишу");
		_getche();
		show_result_of_processing(get_result(head, key_student, -1, nullptr, -1), key_student, -1, nullptr, -1);
		key_student = cleanlist(key_student);
	}
	else
		puts("В картотеке нет ни одного элемента!\n");
	system("pause");
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Функция выбора способа сортировки списка
//принимает указатель на голову списка
void select_method_of_sort(LIST* head)
{
	int c; //номер пункта меню

	if (head)
	{
		do
		{
			system("cls");
			c = menu(14);
			system("cls");
			switch (c)
			{
			case 1:
				printf("\t\t%s\n\n", "СОРТИРОВКА ПО ФАМИЛИИ ПО ВОЗРАСТАНИЮ");
				output_division();
				puts("\nСортировка элементов картотеки по фамилии по возрастанию прошла успешно!\n");
				output_division();
				printf("Для перехода к меню просмотра результата нажмите любую клавишу");
				_getche();
				show_result_of_processing(get_result(head, nullptr, 1, nullptr, -1), nullptr, 1, nullptr, -1);
				c = 11;
				break;

			case 2:
				printf("\t\t%s\n\n", "СОРТИРОВКА ПО ИМЕНИ ПО ВОЗРАСТАНИЮ");
				output_division();
				puts("\nСортировка элементов картотеки по имени по возрастанию прошла успешно!\n");
				output_division();
				printf("Для перехода к меню просмотра результата нажмите любую клавишу");
				_getche();
				show_result_of_processing(get_result(head, nullptr, 2, nullptr, -1), nullptr, 2, nullptr, -1);
				c = 11;
				break;

			case 3:
				printf("\t\t%s\n\n", "СОРТИРОВКА ПО ОТЧЕСТВУ ПО ВОЗРАСТАНИЮ");
				output_division();
				puts("\nСортировка элементов картотеки по имени по отчеству прошла успешно!\n");
				output_division();
				printf("Для перехода к меню просмотра результата нажмите любую клавишу");
				_getche();
				show_result_of_processing(get_result(head, nullptr, 3, nullptr, -1), nullptr, 3, nullptr, -1);
				c = 11;
				break;

			case 4:
				printf("\t\t%s\n\n", "СОРТИРОВКА ПО НОМЕРУ ГРУППЫ ПО ВОЗРАСТАНИЮ");
				output_division();
				puts("\nСортировка элементов картотеки по номеру группы по возрастанию прошла успешно!\n");
				output_division();
				printf("Для перехода к меню просмотра результата нажмите любую клавишу");
				_getche();
				show_result_of_processing(get_result(head, nullptr, 4, nullptr, -1), nullptr, 4, nullptr, -1);
				c = 11;
				break;

			case 5:
				printf("\t\t%s\n\n", "СОРТИРОВКА ПО ОЦЕНКЕ ПО ВОЗРАСТАНИЮ");
				output_division();
				puts("\nСортировка элементов картотеки по оценке по возрастанию прошла успешно!\n");
				output_division();
				printf("Для перехода к меню просмотра результата нажмите любую клавишу");
				_getche();
				show_result_of_processing(get_result(head, nullptr, 5, nullptr, -1), nullptr, 5, nullptr, -1);
				c = 11;
				break;

			case 6:
				printf("\t\t%s\n\n", "СОРТИРОВКА ПО ФАМИЛИИ ПО УБЫВАНИЮ");
				output_division();
				puts("\nСортировка элементов картотеки по фамилии по убыванию прошла успешно!\n");
				output_division();
				printf("Для перехода к меню просмотра результата нажмите любую клавишу");
				_getche();
				show_result_of_processing(get_result(head, nullptr, 6, nullptr, -1), nullptr, 6, nullptr, -1);
				c = 11;
				break;

			case 7:
				printf("\t\t%s\n\n", "СОРТИРОВКА ПО ИМЕНИ ПО УБЫВАНИЮ");
				output_division();
				puts("\nСортировка элементов картотеки по имени по убыванию прошла успешно!\n");
				output_division();
				printf("Для перехода к меню просмотра результата нажмите любую клавишу");
				_getche();
				show_result_of_processing(get_result(head, nullptr, 7, nullptr, -1), nullptr, 7, nullptr, -1);
				c = 11;
				break;

			case 8:
				printf("\t\t%s\n\n", "СОРТИРОВКА ПО ОТЧЕСТВУ ПО УБЫВАНИЮ");
				output_division();
				puts("\nСортировка элементов картотеки по отчеству по убыванию прошла успешно!\n");
				output_division();
				printf("Для перехода к меню просмотра результата нажмите любую клавишу");
				_getche();
				show_result_of_processing(get_result(head, nullptr, 8, nullptr, -1), nullptr, 8, nullptr, -1);
				c = 11;
				break;

			case 9:
				printf("\t\t%s\n\n", "СОРТИРОВКА ПО НОМЕРУ ГРУППЫ ПО УБЫВАНИЮ");
				output_division();
				puts("\nСортировка элементов картотеки по номеру группы по убыванию прошла успешно!\n");
				output_division();
				printf("Для перехода к меню просмотра результата нажмите любую клавишу");
				_getche();
				show_result_of_processing(get_result(head, nullptr, 9, nullptr, -1), nullptr, 9, nullptr, -1);
				c = 11;
				break;

			case 10:
				printf("\t\t%s\n\n", "СОРТИРОВКА ПО ОЦЕНКЕ ПО УБЫВАНИЮ");
				output_division();
				puts("\nСортировка элементов картотеки по оценке по убыванию прошла успешно!\n");
				output_division();
				printf("Для перехода к меню просмотра результата нажмите любую клавишу");
				_getche();
				show_result_of_processing(get_result(head, nullptr, 10, nullptr, -1), nullptr, 10, nullptr, -1);
				c = 11;
				break;

			case 11:
				break;

			default:
				system("cls");
				puts("Такого пункта не существует!");
				system("pause");
				break;
			}
		} while (c != 11);
	}
	else
	{
		printf("\t%-3c%s\n\n", ' ', "МЕНЮ ВЫБОРА СПОСОБА СОРТИРОВКИ ЭЛЕМЕНТОВ КАРТОТЕКИ");
		puts("В картотеке нет ни одного элемента!\n");
		system("pause");
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//функция формирования результата
//возвращает указатель на голову списка результата
//принимает указатель на голову исходного списка,
//указатель на элемент для поиска,
//подномер обработки, указатель на начальный символ
//ключевого слова фильтрации, ключевое число фильтрации
LIST* get_result(LIST* head, LIST* head_core, int type_of_process, char* key_string, int key_number)
{
	LIST* help_ptr1 = head;      //вспомогательный указатель
	LIST* help_ptr2 = nullptr;   //вспомогательный указатель
	LIST* head_result = nullptr; //указатель на голову списка - результата
	bool sort_flag;              //индикатор конца сортировки

	system("cls");
	if (key_string || key_number != -1) //означает, что должна произойти фильтрация
	{
		help_ptr2 = head_result;
		do
		{
			if ((compare_string(key_string, (*help_ptr1).inital_data.surname) && type_of_process == 1) || (compare_string(key_string, (*help_ptr1).inital_data.name) && type_of_process == 2) ||
				(compare_string(key_string, (*help_ptr1).inital_data.patr) && type_of_process == 3) || ((key_number == (*help_ptr1).inital_data.group) && type_of_process == 4) ||
				((key_number == (*help_ptr1).inital_data.mark) && type_of_process == 5))
				head_result = copy_student(help_ptr1, head_result, &help_ptr2);
			help_ptr1 = help_ptr1->next;
		} while (help_ptr1 != head);
	}
	else
		if (head_core)     //означает, что должен произойти поиск
		{
			help_ptr1 = search_student(head, head_core);
			if (help_ptr1)
				head_result = copy_student(help_ptr1->next, head_result, &help_ptr2);
		}
		else              //означает, что должна пройти сортировка
		{
			do
			{
				head_result = copy_student(help_ptr1, head_result, &help_ptr2);
				help_ptr1 = help_ptr1->next;
			} while (help_ptr1 != head);
			do
			{
				sort_flag = true;
				help_ptr1 = head_result;
				help_ptr2 = nullptr;
				do
				{
					if (compare_string_to_sort((*help_ptr1).inital_data.surname, (*(help_ptr1->next)).inital_data.surname) == 2 && type_of_process == 1)
						sort_two_element(&head_result, &sort_flag, &help_ptr1, &help_ptr2);
					else
						if (compare_string_to_sort((*help_ptr1).inital_data.name, (*(help_ptr1->next)).inital_data.name) == 2 && type_of_process == 2)
							sort_two_element(&head_result, &sort_flag, &help_ptr1, &help_ptr2);
						else
							if (compare_string_to_sort((*help_ptr1).inital_data.patr, (*(help_ptr1->next)).inital_data.patr) == 2 && type_of_process == 3)
								sort_two_element(&head_result, &sort_flag, &help_ptr1, &help_ptr2);
							else
								if ((*help_ptr1).inital_data.group > (*(help_ptr1->next)).inital_data.group && type_of_process == 4)
									sort_two_element(&head_result, &sort_flag, &help_ptr1, &help_ptr2);
								else
									if ((*help_ptr1).inital_data.mark > (*(help_ptr1->next)).inital_data.mark && type_of_process == 5)
										sort_two_element(&head_result, &sort_flag, &help_ptr1, &help_ptr2);
									else
										if (compare_string_to_sort((*help_ptr1).inital_data.surname, (*(help_ptr1->next)).inital_data.surname) == 1 && type_of_process == 6)
											sort_two_element(&head_result, &sort_flag, &help_ptr1, &help_ptr2);
										else
											if (compare_string_to_sort((*help_ptr1).inital_data.name, (*(help_ptr1->next)).inital_data.name) == 1 && type_of_process == 7)
												sort_two_element(&head_result, &sort_flag, &help_ptr1, &help_ptr2);
											else
												if (compare_string_to_sort((*help_ptr1).inital_data.patr, (*(help_ptr1->next)).inital_data.patr) == 1 && type_of_process == 8)
													sort_two_element(&head_result, &sort_flag, &help_ptr1, &help_ptr2);
												else
													if ((*help_ptr1).inital_data.group < (*(help_ptr1->next)).inital_data.group && type_of_process == 9)
														sort_two_element(&head_result, &sort_flag, &help_ptr1, &help_ptr2);
													else
														if ((*help_ptr1).inital_data.mark < (*(help_ptr1->next)).inital_data.mark && type_of_process == 10)
															sort_two_element(&head_result, &sort_flag, &help_ptr1, &help_ptr2);
														else
														{
															help_ptr2 = help_ptr1;
															help_ptr1 = help_ptr1->next;
														}
				} while (help_ptr1->next != head_result);
			} while (!sort_flag);
		}
	return head_result;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//функция копирования элемента из одного списка в другой
//возвращает указатель на голову списка
//принимает указатель на текущий элемент в исходном списке,
//указатель на голову списка результата и адрес указателя
//на текущий элемент в списке результате
LIST* copy_student(LIST* start, LIST* head_res, LIST** start_res)
{
	if (head_res != NULL)
	{
		(**start_res).next = (LIST*)malloc(sizeof(LIST));
		*start_res = (**start_res).next;
	}
	else
	{
		*start_res = (LIST*)malloc(sizeof(LIST));
		head_res = *start_res;
	}
	(**start_res).next = head_res;
	(**start_res).inital_data.surname = copy_string((*start).inital_data.surname);
	(**start_res).inital_data.name = copy_string((*start).inital_data.name);
	(**start_res).inital_data.patr = copy_string((*start).inital_data.patr);
	(**start_res).inital_data.group = (*start).inital_data.group;
	(**start_res).inital_data.mark = (*start).inital_data.mark;
	return head_res;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//функция копирования строки
//возвращает указатель на начальный символ копии строки
//принимает указатель на начальный символ строки
char* copy_string(char* str1)
{
	char* str2;                  //указатель на начальный символ строки
	int l = string_length(str1); //длина строки 

	str2 = (char*)malloc((l + 1) * sizeof(char));
	for (int i = 0; i < l; i++)
		str2[i] = str1[i];
	str2[l] = '\0';
	return str2;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//функция перемены местами двух элементов списка
//принимает адрес указателя на голову списка,
//указатель на индикатор конца сортировки,
//адрес указателя на текущий элемент списка,
//адрес указателя на предыдущий элемент списка
void sort_two_element(LIST** head_res, bool* flag, LIST** ptr1, LIST** ptr2)
{
	LIST* ptr3; //вспомогательный указатель

	*flag = false;
	ptr3 = (*(ptr1))->next;
	(*(ptr1))->next = (*(ptr1))->next->next;
	ptr3->next = *ptr1;
	if (*head_res == *ptr1)
	{
		*ptr2 = *head_res;
		while ((*ptr2)->next != *head_res)
			(*ptr2) = (*ptr2)->next;
		(*ptr2)->next = ptr3;
		*head_res = ptr3;
		*ptr2 = ptr3;
	}
	else
	{
		(*ptr2)->next = ptr3;
		*ptr2 = ptr3;
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//функция сравнения полей с фамилиями/именами/отчествами студентов для сортировки
//возвращает число, отвечающее лексикографическому расположению строк:
//2 - второе должно быть раньше первого, 1 - первое должно быть раньше второго,
//0 - строки равны
//принимает указатель на начальный символ первой строки
//и указатель на начальный символ второй строки
int compare_string_to_sort(char* str1, char* str2)
{
	int minimal_length,  //длина наименьшей строки
		i;               //вспомогательная переменная

	if (compare_string(str1, str2))
		return 0;
	else
	{
		if (string_length(str1) > string_length(str2))
			minimal_length = string_length(str2);
		else
			minimal_length = string_length(str1);
		for (i = 0; i < minimal_length; i++)
		{
			if ((str2[i] < str1[i] && str1[i] <= 'Z') || ('a' <= str2[i] && str2[i] < str1[i]) ||
				(str2[i] <= 'Z' && str1[i] >= 'a' && (str1[i] - str2[i]) >= 'a' - 'A') || (str2[i] >= 'a' && str1[i] <= 'Z' && (str2[i] - str1[i]) < 'a' - 'A'))
				return 2;
			else
				if (str1[i] != str2[i])
					return 1;
		}
	}
	if (string_length(str2) < string_length(str1))
		return 2;
	else
		return 1;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Функция вывода результата
//принимает указатель на голову списка,
//указатель на элемент списка для поиска, подномер обработки,
//указатель на начальный символ
//ключевого слова фильтрации, ключевое число фильтрации
void show_result_of_processing(LIST* head_result, LIST* head_core, int type_of_process, char* key_string, int key_number)
{
	if (key_string || key_number != -1)
	{
		if (!head_result)
		{
			system("cls");
			printf("\t\t\t%s\n\n", "ВЫВОД РЕЗУЛЬТАТА ФИЛЬТРАЦИИ");
			output_division();
			if (type_of_process == 1)
				printf("По фамилии %s студентов не было найдено!\n\n", key_string);
			if (type_of_process == 2)
				printf("По имени %s студентов не было найдено\n\n", key_string);
			if (type_of_process == 3)
				printf("По отчеству %s студентов не было найдено\n\n", key_string);
			if (type_of_process == 4)
				printf("По номеру группы %d студентов не было найдено\n\n", key_number);
			if (type_of_process == 5)
				printf("По оценке %d студентов не было найдено\n\n", key_number);
			output_division();
			system("pause");
		}
		else
			select_show_result(head_result, type_of_process, key_string, key_number);
	}
	else
		if (head_core)
		{
			system("cls");
			printf("\t\t\t%s\n\n", "ВЫВОД РЕЗУЛЬТАТА ПОИСКА");
			show_one_element(head_core);
			if (head_result)
				puts("\nДанный студент БЫЛ НАЙДЕН!\n");
			else
				puts("\nДанный студент НЕ БЫЛ НАЙДЕН!\n");
		}
		else
		{
			select_show_result(head_result, type_of_process, key_string, key_number);
		}
	head_result = cleanlist(head_result);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//функция выбора способа вывода результата
//принимает указатель на голову списка,
//подномер обработки,
//указатель на начальный символ
//ключевого слова фильтрации, ключевое число фильтрации
void select_show_result(LIST* head_result, int type_of_process, char* key_string, int key_number)
{
	int c1,                //номер пункта меню
		c2;                //номер пункта меню
	bool exit_code = true; //индикатор вывода сообщения
	do
	{
		system("cls");
		printf("%-3c%s\n\n", ' ', "МЕНЮ ВЫБОРА СПОСОБА ВЫВОДА РЕЗУЛЬТАТА");
		c1 = menu(6);
		system("cls");
		switch (c1)
		{
		case 1:
			printf("\t\t\t%s\n\n", "ВЫВОД РЕЗУЛЬТАТА НА ЭКРАН");
			if (key_string || key_number != -1)
			{
				if (type_of_process == 1)
					printf("Результат фильтрации картотеки по фамилии %s:\n\n", key_string);
				if (type_of_process == 2)
					printf("Результат фильтрации картотеки по имени %s:\n\n", key_string);
				if (type_of_process == 3)
					printf("Результат фильтрации картотеки по отчеству %s:\n\n", key_string);
				if (type_of_process == 4)
					printf("Результат фильтрации картотеки по номеру группы %d:\n\n", key_number);
				if (type_of_process == 5)
					printf("Результат фильтрации картотеки по оценке %d:\n\n", key_number);
			}
			else
			{
				if (type_of_process == 1)
					puts("Результат сортировки элементов картотеки по фамилии по возрастанию:\n");
				if (type_of_process == 2)
					puts("Результат сортировки элементов картотеки по имени по возрастанию:\n");
				if (type_of_process == 3)
					puts("Результат сортировки элементов картотеки по отчеству по возрастанию:\n");
				if (type_of_process == 4)
					puts("Результат сортировки элементов картотеки по номеру группы по возрастанию:\n");
				if (type_of_process == 5)
					puts("Результат сортировки элементов картотеки по оценке по возрастанию:\n");
				if (type_of_process == 6)
					puts("Результат сортировки элементов картотеки по фамилии по убыванию:\n");
				if (type_of_process == 7)
					puts("Результат сортировки элементов картотеки по имени по убыванию:\n");
				if (type_of_process == 8)
					puts("Результат сортировки элементов картотеки по отчеству по убыванию:\n");
				if (type_of_process == 9)
					puts("Результат сортировки элементов картотеки по номеру группы по убыванию:\n");
				if (type_of_process == 10)
					puts("Результат сортировки элементов картотеки по оценке по убыванию:\n");
			}
			show_students(head_result);
			c1 = 3;
			system("pause");
			break;

		case 2:
			printf("\t\t\t%s\n\n", "ВЫВОД РЕЗУЛЬТАТА В ФАЙЛ");
			set_file_to_write(head_result, true, &exit_code);
			if (!exit_code)
				c1 = 3;
			break;

		case 3:
			if (exit_code)
			{
				do
				{
					system("cls");
					c2 = menu(13);
					if (c2 == 2)
						c1 = -1;
					else
						if (c2 != 1)
						{
							system("cls");
							puts("Такого пункта не существует");
							system("pause");
						}
				} while (c2 < 1 || c2 > 2);
			}
			break;

		default:
			puts("Такого пункта не существует!");
			system("pause");
			break;
		}
	} while (c1 != 3);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//функция вывода на экран одного элемента списка
//принимает указатель на элемент списка, инфо о котором надо вывести на экран
void show_one_element(LIST* data)
{
	printf("Фамилия             Имя                 Отчество           Группа  Оценка\n");
	printf("%-18s  %-18s  %-18s  %-5d    %d\n", data->inital_data.surname, data->inital_data.name, data->inital_data.patr, data->inital_data.group, data->inital_data.mark);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//прототип функции вывода справки
//ничего не принимает и ничего не возвращает
void userhelp()
{
	printf("\t\t\t\t%s\n\n", "СПРАВКА");
	puts("-Данная программа предназначена для ведения списка/ведомости(эказаменационной) со студентами.");
	puts("Студент в программе имеет пять необходимых характристик - фамилия, имя, отчество, номер группы, отметка");
	puts("-В главном меню, выбрав пункт 1, Вы перейдете в меню выбора способа ввода инфо о студентах.");
	puts("Сделать это можно путем чтения из файла, либо вводом с клавиатуры.");
	puts("В первом случае будет предложено выбрать файл для чтения и способ записи - в конец текущего списка или перезапись");
	puts(", во втором - выбрать куда именно добавлять: ");
	puts("в начало,в конец, в определенное место списка студентов.\n-Вывести текущий список можно нажав 2 в главном меню.");
	puts("Есть два способа для этого: вывод на экран, вывод в файл(какой именно - пользователь выбирает сам).");
	puts("Записать инфо в файл можно как в его конец, так и удалив все предыдущие в нем записи.");
	puts("-Для работы с картотекой необходимо выбрать 3 пункт главного меню. Изменить инфо о студенте можно как в файле, ");
	puts("так и в оперативной памяти компьютера. Удалить студента можно либо из начала/конца, либо определенного студента.");
	puts("Отфильтровать картотеку можно по любомц из полей, главное задать ключевое слово. Можно организовать поиск студента");
	puts("нужно лишь только ввести данные о нем. Также список студентов можно отсортировать по любому полю либо по возрастанию, ");
	puts("либо по убыванию.\n-Номер 4 главного меню это вывод справки, которую вы сейчас читаете.");
	puts("-Номер 5 - это завершение работы программы.");
	puts("Удачи:(!");
	system("pause");
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++