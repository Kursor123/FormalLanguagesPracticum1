# FormalLanguagesPracticum1
Данный алгоритм делает следующее: он поэтапно вычисляет вхождения всех подстрок данной строки из языка. Вычисление происходит при помощи стека. Далее, в итоговом языке ищется максимум длины по всем подстрокам и выводится ответ.
Какова сложность алгоритма?
Пусть L -- длина выражения в обратной польской записи, задающего язык, а T -- длина строки, в которой мы ищем вхождения.
Сначала предпосчитываются все вхождения букв a, b и c по отдельности в текст. Получается O(T).
Далее каждая последующая операция -- это либо сумма или произведение языков L1 и L2, либо итерация языка L1. Множество вхождений для каждого языка хранится как std::set<std::pair<size_t, size_t>>. Сложение выполняется за O(L2 * log(L1 + L2)). Умножение выполняется за O(L1 * L2 + log(L1 * L2)).
Итерация выполняется за O(L1 * L1 + log(L1)). Получается, что итоговая асимптотика это O(L * T^2).
Чтобы запустить проверку, достаточно передать хоть что-нибудь в аргументы командной строки.
