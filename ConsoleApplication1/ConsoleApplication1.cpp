// ConsoleApplication1.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
using namespace std;
#include <fstream>
#define SIZE_MINI 1
#include <iostream>

int length_of_int(int num) {
    if (num == 0) return 1; 
    int length = 0;
    while (num != 0) {
        num /= 10;
        length++;
    }
    return length;
}
int get_index(char* array, int start, int end)
{
    int rez = 0;
    for (int i = start; i < end; ++i) {
        rez += array[i] * pow(128,abs( i-start));
    }
    return rez;
}
int main()
{
    ifstream myfile("exel.xlsx", ios::binary | ios::ate);

    int size = myfile.tellg();
    myfile.seekg(0, ios::beg);
    char* buffer = new char[size];


    myfile.read(buffer, size);

    for (int i = 0; i < size; i++)
    {
        cout << buffer[i];
    }
    int size_min = SIZE_MINI;
    int iter = size / size_min;
    char** buffers = new char* [iter + 1];
    for (int i = 0; i <= iter; i++)
    {
        buffers[i] = new char[size_min];
        for (int j = 0; j < size_min; j++)
        {
            if (i * size_min + j < size)
                buffers[i][j] = buffer[i * size_min + j];
            else buffers[i][j] = 0;
        }

    }
    cout << "\n\n\n\n\n\n\n";



    char** send_buffers = new char* [iter + 1];
    for (int i = 0; i <= iter; i++)
    {
        send_buffers[i] = new char[size_min + length_of_int(iter)];
        for (int j = 0; j < size_min + length_of_int(iter); j++) {
            if (j < size_min) send_buffers[i][j] = buffers[i][j];
            else {
                send_buffers[i][j] = i % static_cast<int>(pow(128, j - size_min+1)) / static_cast<int>(pow(128, j - size_min)); cout << i % static_cast<int>(pow(128, j - size_min + 1)) / static_cast<int>(pow(128, j - size_min)) << "\n";
            }
        }
        cout << "\n\n\n";
    }



    char** get_buffer = new char* [iter + 1];

    for (int i = 0; i <= iter; i++) {
        get_buffer[get_index(send_buffers[i], size_min, size_min + length_of_int(iter))] = new char[size_min];
        get_buffer[get_index(send_buffers[i], size_min, size_min + length_of_int(iter))] = send_buffers[i];
    }


    for (int i = 0; i <= iter; i++)
        for (int j = 0; j < size_min; j++)
            cout << get_buffer[i][j];
    myfile.close();
    cout << "\n\n\n\n\n\n\n";
    ofstream print("example.xlsx", ios::binary);
    char* rezult = new char[size];



    for (int i = 0; i <= iter; i++)
        for (int j = 0; j < size_min; j++)
            if (i * size_min + j < size)
                rezult[i * size_min + j] = get_buffer[i][j];



    for (int i = 0; i <= size; i++)
        cout << rezult[i];


    print.write(rezult, size);
    print.close();
    delete[] rezult, get_buffer, send_buffers, buffers, buffer;
    return 0;
}
