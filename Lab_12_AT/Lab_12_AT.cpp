#include <iostream>
#include <chrono>
#include <cstdlib>
#include <string>
#include <Windows.h>
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

void generateArray(int* A, int n) {
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 100;
    }
}

void printArray(const int* A, int n) {
    for (int i = 0; i < n; i++) {
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;
}

void BubbleSort(int* A, int n) {
    for (int i = n - 1; i >= 1; i--) {
        for (int j = 0; j < i; j++) {
            if (A[j] > A[j + 1]) {
                std::swap(A[j], A[j + 1]);
            }
        }
    }
}

void InsertionSort(int* A, int n) {
    for (int i = 1; i < n; i++) {
        int key = A[i];
        int j = i - 1;
        while (j >= 0 && A[j] > key) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = key;
    }
}

void Merge(int* A, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) L[i] = A[left + i];
    for (int j = 0; j < n2; j++) R[j] = A[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            A[k++] = L[i++];
        }
        else {
            A[k++] = R[j++];
        }
    }
    while (i < n1) A[k++] = L[i++];
    while (j < n2) A[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void MergeSort(int* A, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        MergeSort(A, left, mid);
        MergeSort(A, mid + 1, right);
        Merge(A, left, mid, right);
    }
}

void SelectionSort(int* A, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (A[j] < A[minIdx]) {
                minIdx = j;
            }
        }
        std::swap(A[i], A[minIdx]);
    }
}

void ShellSort(int* A, int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = A[i];
            int j;
            for (j = i; j >= gap && A[j - gap] > temp; j -= gap) {
                A[j] = A[j - gap];
            }
            A[j] = temp;
        }
    }
}

void Heapify(int* A, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && A[left] > A[largest]) largest = left;
    if (right < n && A[right] > A[largest]) largest = right;
    if (largest != i) {
        std::swap(A[i], A[largest]);
        Heapify(A, n, largest);
    }
}

void HeapSort(int* A, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        Heapify(A, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        std::swap(A[0], A[i]);
        Heapify(A, i, 0);
    }
}

int Partition(int* A, int low, int high) {
    int pivot = A[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (A[j] < pivot) {
            i++;
            std::swap(A[i], A[j]);
        }
    }
    std::swap(A[i + 1], A[high]);
    return i + 1;
}

void QuickSort(int* A, int low, int high) {
    if (low < high) {
        int pi = Partition(A, low, high);
        QuickSort(A, low, pi - 1);
        QuickSort(A, pi + 1, high);
    }
}

void measureSortTime(void (*sortFunc)(int*, int), int* A, int n, const std::string& sortName) {
    generateArray(A, n);

    auto start = std::chrono::high_resolution_clock::now();
    sortFunc(A, n);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << sortName << ": " << duration.count() << " секунд" << std::endl;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int choice, n;
    int* A = nullptr;

    do {
        system(CLEAR);  

        std::cout << "Оберіть алгоритм сортування:\n";
        std::cout << "1. Сортування бульбашкою\n";
        std::cout << "2. Сортування вставками\n";
        std::cout << "3. Сортування злиттям\n";
        std::cout << "4. Сортування вибором\n";
        std::cout << "5. Сортування Шелла\n";
        std::cout << "6. Пірамідальне сортування\n";
        std::cout << "7. Швидке сортування\n";
        std::cout << "0. Вийти\n";
        std::cout << "Ваш вибір: ";
        std::cin >> choice;

        if (choice >= 1 && choice <= 7) {
            std::cout << "Введіть розмір масиву: ";
            std::cin >> n;
            A = new int[n];
        }

        switch (choice) {
        case 1:
            measureSortTime(BubbleSort, A, n, "Сортування бульбашкою");
            break;
        case 2:
            measureSortTime(InsertionSort, A, n, "Сортування вставками");
            break;
        case 3:
            measureSortTime([](int* A, int n) { MergeSort(A, 0, n - 1); }, A, n, "Сортування злиттям");
            break;
        case 4:
            measureSortTime(SelectionSort, A, n, "Сортування вибором");
            break;
        case 5:
            measureSortTime(ShellSort, A, n, "Сортування Шелла");
            break;
        case 6:
            measureSortTime(HeapSort, A, n, "Пірамідальне сортування");
            break;
        case 7:
            measureSortTime([](int* A, int n) { QuickSort(A, 0, n - 1); }, A, n, "Швидке сортування");
            break;
        case 0:
            std::cout << "Вихід з програми." << std::endl;
            break;
        default:
            std::cout << "Невірний вибір. Спробуйте ще раз." << std::endl;
        }

        delete[] A;
        A = nullptr;

        if (choice != 0) {
            std::cout << "Натисніть Enter, щоб повернутися до меню...";
            std::cin.ignore();
            std::cin.get();
        }

    } while (choice != 0);

    return 0;
}
