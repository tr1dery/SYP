open System

// Функция проверки монотонности булевой функции
let rec isMonoton(booleanVector: list<int>) =
    match booleanVector with
    | [] | [_] -> true  // Если список пуст или содержит один элемент, он монотонен
    | x::y::tail ->
    if x > y then
        false  // Если текущий элемент больше следующего, функция не монотонна
    else
        isMonoton(y::tail)  // Рекурсивная проверка остальных элементов

[<EntryPoint>]
let main argv =
// Пример булевого вектора
    let booleanVector = [0; 1; 1; 0; 1; 0; 0; 1]

    let result = isMonoton booleanVector

// Вывод результата
    printfn "Булева функция монотонна: %b" result

    0 // Возвращаем целочисленное значение для выхода
