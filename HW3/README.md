# Pthreads, OpemMP  



1. [Демонстрационные файлы](demo) – работающие примеры кодов для понимания OpenMP.  
    ``` text
    Скачайте код, скомпилируйте:
    $ <cc> <codefile.c> -o <executable> -fopenmp
    Укажите компилятор (cc), например, gcc для .c файлов в Ubuntu.
    Как запустить код:
    $ ./<executable>
    ```
    ``` text
    omp_hello.c – простейшая программа печатающая ‘Hello world’. Введение в конструкцию ‘parallel’.  
    Задание:  
    а) научитесь вручную менять кол-во нитей, исполняемых в программе путем изменения переменной окружения:  
    $ export OMP_NUM_THREADS=<number you want>.  
    b) научитесь задавать кол-во нитей внутри программы.  

    omp_outmes.cpp – сравнение параллельного I/O C и C++. Пример на понимания понятия “threadsafe”. Пример конструкции critical.  
    Компиляция: $ g++ omp_outmes.cpp -o <executable> -fopenmp  

    omp_privateshared.c – пример общих и приватных переменных, конструкции ‘for’.  
    Задание: запустите программу, разберитесь, что делают все команды с #pragma.  

    omp_parsec.c – пример использования конструкции section.  
    Задание: перед запуском, попытайтесь угадать вывод программы, потом проверьте.  

    omp_sumarray.c – пример использования редукции.  
    Обратите внимание на конструкцию #pragma omp parallel for –  
    в чем разница между этой конструкцией и #pragma omp parallel … #pragma omp for  
    ```

2. Программы с багами – примеры программ, которые надо починить.  
    ``` text
    omp_bugreduction.c – код для скалярного произведения двух векторов. Дополнить функцию dotprod, проверить баги в #pragma omp, проверить результат.

    omp_bugparfor.c – Найти и устранить ошибки.
    ```
3. Написать параллельную программу, использующую метод Монте-Карло для оценки числа pi. Случайным образом (аккуратнее с генератором случайных чисел!) кидаете точку в единичный квадрат. В этот же квадрат вписан круг. Если точка попала в круг, увеличиваете счетчик. Затем находите отношение точек, попавших в круг к общему числу точек. Зная площади квадрата и круга, находите приблизительно число pi.  

# Решение  

1. Примеры кода OpenMP изучены.  

2. Исправленные версии программ [omp_reduction.c](fixed_bugs/omp_reduction.c) и [omp_parfor.c](fixed_bugs/omp_parfor.c) находятся в директории [/fixed_bugs](fixed_bugs)  

3. Реализован метод Монте-Карло для оценки числа pi - [main](main.c)  
    Сборка:  
    g++ main.c -o run -fopenmp  

    Запуск:  
    ./run n_exp n_threads need_print_x_y  
    n_exp - число экспериментов метода (default = 500000),  
    n_threads - число тредов (default = 4),  
    need_print_x_y - флаг для вывода seeds и всех значений X, Y (default = False).  