#include <iostream>
#include <Windows.h>
#include <io.h>

using namespace std;

// 1 копирование одного файла в другой
//для вывода строки в консоль
void RussianMessage(const char* str) {
	char message[100];
	CharToOemA(str, message);
	cout << message;
}

//копирование файла
bool CopyFile(char* source, char* destination) {
	const int size = 65536;
	FILE* src, * dest;

	if (!fopen_s(&src, source, "rb")) {
		long handle = _fileno(src); // получение дескриптора файла
		char* data = new char[size]; // выделение памяти под буфер

		if (!fopen_s(&dest, destination, "wb")) {
			int realsize;
			while (!feof(src)) {
				realsize = fread(data, sizeof(char), size, src); // чтение файла
				fwrite(data, sizeof(char), realsize, dest); //запись файла
			}
		}
		else {
			delete[] data;
			return false;
		}
	}
	else return false;

	fclose(src);
	fclose(dest);
	return true;

}

int main()
{
	char source[_MAX_PATH];
	char destination[_MAX_PATH];
	char answer[20];

	RussianMessage("\nВведите путь и название копируемого файла\n");
	cin.getline(source, _MAX_PATH);
	if (_access(source, 00) == -1) {
		RussianMessage("\nУказан неверный путь к файлу и его название");
		return;
	}

	RussianMessage("\nВведите путь и название нового файла\n");
	cin.getline(destination, _MAX_PATH);
	if (_access(source, 00) == 0) {
		RussianMessage("\nТакой файл уже создан. Перезаписать?(1- Да, 2 - Нет)\n");
		cin.getline(answer, 20);
		if (!strcmp(answer, "2")) {
			RussianMessage("\nСтрока отменена\n");
			return;
		}
		else if (!strcmp(answer, "1")) {
			if (_access(destination, 02) == -1) {
				RussianMessage("\nНет доступа к записи\n");
				return;
			}
			
		}
		else {
			RussianMessage("\nНеправильный Ввод\n");
			return;
		}
	}
	if (!CopyFile(source, destination)) {
		RussianMessage("\nОшибка при работе с файлом\n");
		return;
	}
	return;
}
// FILE* fopen(char* path, char* mode)
// fopen_s(FILE **f, char* path, char* mode) - открытие доступ к файлу

//fclose(FILE* f) - закрытие доступа к файлу 
//if(fclose(f) == EOF)

//fgets(char* string, int n, FILE* f) - построчное чтение
//fgetc() - посимвольное чтение
//fscanf() - чтение форматированной строки

//fputs(char* string, FILE* f) - построчная запись
//fputc() - посимвольная запись
//fprintf() - запись форматированной строки

//feof(FILE* f) - определение конца метода

//fread(void* buffer, size_t size, size_t count, FILE* f)
// чтение бинарного файла
//fwread(const void* buffer, size_t size, size_t count, FILE* f)
// запись в бинарный файл

//fseek(FILE* f, int offset [, int origin])
// устанавливает смещение в файле

// include<io.h>
// int _access(const char* path, int mode)
// определяет разрешение файлов или директорий
	// 00 - проверка на существование
	// 02 - проверка разрешения на запись
	// 04 - проверка разрешения на чтение
	// 06 - проверка на чтение и на запись

// long _filelenght(int handle)
// возвращает размер файла в байтах

//int _locking(int handle, int mode, long nBytes)    <sys/locking.h>
// блокирует\разблокирует байти файла начиная с текущей позиции
	//_LK_LOCK (_LK_RLCK)- блокировка байт (10 попыток)
	//_LK_NBLCK (_LK_NBRLCK) - блок (без попыток)
	//_LK_UNLCK - разблок





