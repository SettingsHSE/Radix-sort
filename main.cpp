#include "ReadWriter.h"
//iostream, fstream включены в ReadWriter.h
using namespace std;

//Функция для вычисления нужного байта
int get_byte(int number, int num_byte)
{
    for (int i = 0; i < 3 - num_byte; i++)
    {
        number /= 256;
    }
    return (number - ((number/256)*256));
}

//Функция сортировки подсчета
void countingSort(int *numbers, int array_size, int num_byte)
{
    int *tmp = new int[256];

    for (int i = 0; i <= 255; i++)
    {
        tmp[i] = 0;
    }

    for (int i = 0;  i < array_size; i++)
    {
        tmp[get_byte(numbers[i], num_byte)] ++;
    }

    for (int i = 1; i <= 255; i++)
    {
        tmp[i] += tmp[i - 1];
    }

    int *a = new int[array_size];
    for (int i = 0; i < array_size; i++)
    {
        a[i] = numbers[i];
    }

    for (int i = array_size - 1; i >= 0; i--)
    {
        numbers[tmp[get_byte(a[i], num_byte)] - 1] = a[i];
        tmp[get_byte(a[i], num_byte)] --;
    }

    delete[] a;
    delete[] tmp;
}

// Функция цифровой сортировки
void radixSort(int *numbers, int array_size)
{
    for (int i = 3; i > 0; i--)
    {
        countingSort(numbers, array_size, i);
    }
}

//Не удалять и не изменять метод main без крайней необходимости.
//Необходимо добавить комментарии, если все же пришлось изменить метод main.
int main()
{
    //Объект для работы с файлами
    ReadWriter rw;

    int *brr = nullptr;
    int n;

    //Ввод из файла
    n = rw.readInt();

    brr = new int[n];
    rw.readArray(brr, n);

    //Запуск сортировки, ответ в том же массиве (brr)
    radixSort(brr, n);

    //Запись в файл
    rw.writeArray(brr, n);

    //освобождаем память
    delete[] brr;

    return 0;
}
