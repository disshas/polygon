#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm> // Для std::is_sorted
using namespace std;

// Реализация шейкерной сортировки
void shakerSort(vector<int>& arr) {
    int left = 0;                      // Левая граница неотсортированной части массива
    int right = arr.size() - 1;        // Правая граница неотсортированной части массива
    bool swapped;                      // Флаг для проверки наличия перестановок

    do {
        swapped = false;

        // Проход слева направо: сдвигаем наибольший элемент в конец массива
        for (int i = left; i < right; ++i) {
            if (arr[i] > arr[i + 1]) { // Если текущий элемент больше следующего
                swap(arr[i], arr[i + 1]); // Меняем их местами
                swapped = true; // Отмечаем, что была перестановка
            }
        }
        --right; // Сужаем правую границу, так как последний элемент на своём месте

        // Проход справа налево: сдвигаем наименьший элемент в начало массива
        for (int i = right; i > left; --i) {
            if (arr[i] < arr[i - 1]) { // Если текущий элемент меньше предыдущего
                swap(arr[i], arr[i - 1]); // Меняем их местами
                swapped = true; // Отмечаем, что была перестановка
            }
        }
        ++left; // Сужаем левую границу, так как первый элемент на своём месте

    } while (swapped); // Продолжаем, пока происходят перестановки
}





// Функция для создания кучи с искусственным ухудшением производительности
void inefficientHeapify(vector<int>& arr, int n, int i) {
    int largest = i; // Корень
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Находим наибольший элемент среди корня, левого и правого потомков
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // Если наибольший элемент не корень
    if (largest != i) {
        swap(arr[i], arr[largest]);

        // Искусственно создаём неэффективность: пересоздаём кучу целиком
        for (int j = n / 2 - 1; j >= 0; --j) {
            inefficientHeapify(arr, n, j);
        }
    }
}

// Основная функция пирамидальной сортировки
void heapSort(vector<int>& arr) {
    int n = arr.size();

    // Построение начальной кучи
    for (int i = n / 2 - 1; i >= 0; --i) {
        inefficientHeapify(arr, n, i);
    }

    // Извлечение элементов из кучи
    for (int i = n - 1; i >= 0; --i) {
        // Перемещаем текущий корень в конец
        swap(arr[0], arr[i]);

        // Восстанавливаем кучу на уменьшенном массиве
        inefficientHeapify(arr, i, 0);
    }
}





// Реализация блочной сортировки
void bucketSort(vector<int>& arr, int bucketSize) {
    if (arr.empty()) {
        return;
    }

    // Находим минимальное и максимальное значение в массиве
    int minValue = *min_element(arr.begin(), arr.end());
    int maxValue = *max_element(arr.begin(), arr.end());

    // Количество корзин
    int bucketCount = (maxValue - minValue) / bucketSize + 1;
    vector<vector<int>> buckets(bucketCount);

    // Распределяем элементы массива по корзинам
    for (int num : arr) {
        int bucketIndex = (num - minValue) / bucketSize;
        buckets[bucketIndex].push_back(num);
    }

    // Сортируем каждую корзину и объединяем результат
    arr.clear();
    for (vector<int>& bucket : buckets) {
        sort(bucket.begin(), bucket.end()); // Внутренняя сортировка корзины
        arr.insert(arr.end(), bucket.begin(), bucket.end());
    }
}





// Функция для тестирования лучшего случая
void testBestCase() {
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> expected = arr; // Массив уже отсортирован
    shakerSort(arr);
    heapSort(arr);
    bucketSort(arr, 2);
    assert(arr == expected && "Test Best Case Failed!");
}

// Функция для тестирования среднего случая
void testAverageCase() {
    vector<int> arr = {5, 3, 8, 4, 2, 7, 1, 6};
    vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8}; // Ожидаемый результат
    shakerSort(arr);
    heapSort(arr);
    bucketSort(arr, 2);
    assert(arr == expected && "Test Average Case Failed!");
}

// Функция для тестирования худшего случая
void testWorstCase() {
    vector<int> arr = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // Ожидаемый результат
    shakerSort(arr);
    heapSort(arr);
    bucketSort(arr, 2);
    assert(arr == expected && "Test Worst Case Failed!");
}

// Тест для пустого массива
void testEmptyArray() {
    vector<int> arr = {};
    vector<int> expected = {};
    shakerSort(arr);
    heapSort(arr);
    bucketSort(arr, 2);
    assert(arr == expected && "Test Empty Array Failed!");
}

// Тест для массива с одним элементом
void testSingleElement() {
    vector<int> arr = {42};
    vector<int> expected = {42};
    shakerSort(arr);
    heapSort(arr);
    bucketSort(arr, 2);
    assert(arr == expected && "Test Single Element Failed!");
}

// Тест для массива с одинаковыми элементами
void testAllElementsSame() {
    vector<int> arr = {5, 5, 5, 5, 5};
    vector<int> expected = arr; // Массив остаётся неизменным
    shakerSort(arr);
    heapSort(arr);
    bucketSort(arr, 2);
    assert(arr == expected && "Test All Elements Same Failed!");
}

// Тест для массива с отрицательными числами
void testNegativeNumbers() {
    vector<int> arr = {-3, -1, -7, -4, -5, -2};
    vector<int> expected = {-7, -5, -4, -3, -2, -1}; // Ожидаемый результат
    shakerSort(arr);
    heapSort(arr);
    bucketSort(arr, 2);
    assert(arr == expected && "Test Negative Numbers Failed!");
}


void measureTime() {
    for (int size = 1000; size <= 10000; size += 1000) {
        vector<int> arr(size);

        // Заполнение массива случайными числами
        for (int i = 0; i < size; ++i) {
            arr[i] = rand() % 10000;  // Генерация случайных чисел
        }

        // Засекаем время начала
        clock_t start1 = clock();
        // Выполняем шейкерную сортировку
        shakerSort(arr);
        // Засекаем время окончания
        clock_t end1 = clock();
        
        // Засекаем время начала
        clock_t start2 = clock();
        // Выполняем пирамидальную сортировку
        heapSort(arr);
        // Засекаем время окончания
        clock_t end2 = clock();
        
        // Засекаем время начала
        clock_t start3 = clock();
        // Выполняем блочную сортировку
        bucketSort(arr, 50);
        // Засекаем время окончания
        clock_t end3 = clock();
        
        // Вычисляем время выполнения
        double duration1 = double(end1 - start1) / CLOCKS_PER_SEC;
        double duration2 = double(end2 - start2) / CLOCKS_PER_SEC;
        double duration3 = double(end3 - start3) / CLOCKS_PER_SEC;
        // Выводим размер массива и время выполнения
        cout << "Array size: " << size << " Time1: " << duration1 << " Time2: " << duration2 << " Time3: " << duration3 << " seconds" << endl;
    }
}

// Главная функция для запуска тестов
int main() {
    testBestCase();
    testAverageCase();
    testWorstCase();
    testEmptyArray();
    testSingleElement();
    testAllElementsSame();
    testNegativeNumbers();
    measureTime();

    cout << "Все тесты успешно пройдены!" << endl;
    return 0;
}
