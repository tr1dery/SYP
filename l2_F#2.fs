open System
open System.Collections.Generic

// Функция для выполнения арифметической операции
let performOperation (a: int) (b: int) (op: char) =
    match op with
    | '+' -> a + b
    | '-' -> a - b
    | '*' -> a * b
    | '/' when b <> 0 -> a / b // Деление с проверкой на ноль
    | '/' -> failwith "Ошибка: деление на ноль" // Ошибка деления на ноль
    | _ -> failwith "Неверная операция"

// Функция для вычисления выражения в обратной польской записи
let evaluateRPN (expression: string) =
    let stack = Stack<int>() // Создание стека для хранения операндов
    for c in expression do
        if Char.IsDigit(c) then
            stack.Push(int(c) - int('0')) // Если символ - цифра, добавляем её в стек
        else
            if stack.Count < 2 then
                failwith "Ошибка: недостаточно операндов" // Проверка на наличие достаточного количества операндов
            let b = stack.Pop() // Извлечение операндов
            let a = stack.Pop() 
            let result = performOperation a b c
            stack.Push(result) // Добавление результата обратно в стек
    if stack.Count = 1 then
        stack.Pop() // Если в стеке остался один элемент, это и есть результат
    else
        failwith "Ошибка: неправильное выражение"

[<EntryPoint>]
let main argv =
    let expression = "23+5*" 
    let result = evaluateRPN expression 
    printfn "Результат выражения: %d" result 
    0 
