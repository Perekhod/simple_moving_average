#include <iostream>
#include <vector>
#include <numeric>
#include <chrono>
#include <fstream>
#include <cstdlib>

template <typename T>
std::vector<T> simple_moving_average(const std::vector<T>& data, int window_size) {
    // ��������� ������ ��� �������� ����������� ���������� SMA
    std::vector<T> sma;
    // ���� �� ������� data
    for (int i = 0; i <= data.size() - window_size; i++) {
        // ��������� ����� ��������� � ����
        T sum = std::accumulate(data.begin() + i, data.begin() + i + window_size, 0.0);
        // ��������� ������� �������� � ��������� ��� � ������ sma
        sma.push_back(sum / window_size);
    }
    return sma;
}

int main() {
    // ������ ��������
    std::vector<double> data = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    // ��������� SMA � �������� ���� 4
    std::vector<double> sma = simple_moving_average(data, 4);
    // ������� ����������
    for (double val : sma) {
        std::cout << val << " ";
    }

    // ������� ������� � ��������� ����
    std::vector<int> window_sizes = { 4, 8, 16, 32, 64, 128 };

    // ������� ������� ������ ���� float � double
    std::vector<float>  data_float  (1000000);
    std::vector<double> data_double (1000000);

    // ���������� ��������� ������
    for (int i = 0; i < 1000000; i++) {
        data_float[i]   = static_cast <float>   (rand()) / static_cast <float>  (RAND_MAX);
        data_double[i]  = static_cast <double>  (rand()) / static_cast <double> (RAND_MAX);
    }

    // ������� ���� CSV
    std::ofstream file("performance.csv");
    // ���������� ��������� ��������
    file << "��� ������;������ ����;����� ����������;\n";

    // ��� ������� ������� ����
    for (int window_size : window_sizes) {
        // �������� ����� ���������� ��� float
        // ���������� ������� ����� ����� ������� ���������� �������
        auto start = std::chrono::high_resolution_clock::now();

        // �������� ������� simple_moving_average � �������� data_float � ������� �������� ����
        simple_moving_average(data_float, window_size);

        // ���������� ������� ����� ����� ���������� �������
        auto end = std::chrono::high_resolution_clock::now();

        // ��������� ������� ����� �������� ��������� � �������� ������,
        // ����� �������� ����� ���������� �������
        std::chrono::duration<double> diff = end - start;
        // ���������� ���������� � ����
        file << "Float;" << window_size << ";" << diff.count() << "\n";

        // ����������� �������� ��� double
        start = std::chrono::high_resolution_clock::now();
        simple_moving_average(data_double, window_size);
        end  = std::chrono::high_resolution_clock::now();
        diff = end - start;
        file << "Double;" << window_size << ";" << diff.count() << "\n";
    }
    file.close();

    return 0;
}