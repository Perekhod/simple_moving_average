#include <iostream>
#include <vector>
#include <numeric>
#include <chrono>
#include <fstream>
#include <cstdlib>

template <typename T>
std::vector<T> simple_moving_average(const std::vector<T>& data, int window_size) {
    // Объявляем вектор для хранения результатов вычисления SMA
    std::vector<T> sma;
    // Цикл по вектору data
    for (int i = 0; i <= data.size() - window_size; i++) {
        // Вычисляем сумму элементов в окне
        T sum = std::accumulate(data.begin() + i, data.begin() + i + window_size, 0.0);
        // Вычисляем среднее значение и добавляем его в вектор sma
        sma.push_back(sum / window_size);
    }
    return sma;
}

int main() {
    // Ручная проверка
    std::vector<double> data = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    // Вычисляем SMA с размером окна 4
    std::vector<double> sma = simple_moving_average(data, 4);
    // Выводим результаты
    for (double val : sma) {
        std::cout << val << " ";
    }

    // Создаем векторы с размерами окон
    std::vector<int> window_sizes = { 4, 8, 16, 32, 64, 128 };

    // Создаем векторы данных типа float и double
    std::vector<float>  data_float  (1000000);
    std::vector<double> data_double (1000000);

    // Генерируем случайные данные
    for (int i = 0; i < 1000000; i++) {
        data_float[i]   = static_cast <float>   (rand()) / static_cast <float>  (RAND_MAX);
        data_double[i]  = static_cast <double>  (rand()) / static_cast <double> (RAND_MAX);
    }

    // Создаем файл CSV
    std::ofstream file("performance.csv");
    // Записываем заголовки столбцов
    file << "Тип данных;Размер окна;Время выполнения;\n";

    // Для каждого размера окна
    for (int window_size : window_sizes) {
        // Измеряем время выполнения для float
        // Запоминаем текущее время перед началом выполнения функции
        auto start = std::chrono::high_resolution_clock::now();

        // Вызываем функцию simple_moving_average с вектором data_float и текущим размером окна
        simple_moving_average(data_float, window_size);

        // Запоминаем текущее время после выполнения функции
        auto end = std::chrono::high_resolution_clock::now();

        // Вычисляем разницу между временем окончания и временем начала,
        // чтобы получить время выполнения функции
        std::chrono::duration<double> diff = end - start;
        // Записываем результаты в файл
        file << "Float;" << window_size << ";" << diff.count() << "\n";

        // Аналогичные действия для double
        start = std::chrono::high_resolution_clock::now();
        simple_moving_average(data_double, window_size);
        end  = std::chrono::high_resolution_clock::now();
        diff = end - start;
        file << "Double;" << window_size << ";" << diff.count() << "\n";
    }
    file.close();

    return 0;
}