open System
open System.Collections.Generic

// Функция для подсчета частоты символов
let charFreq(str: string) =
    let freqMap = Dictionary<char, int>()
    for c in str do
        if freqMap.ContainsKey(c) then
            freqMap.[c] <- freqMap.[c] + 1
        else
            freqMap.[c] <- 1
    freqMap

// Функция для поиска символов с максимальной частотой
let maxFreqChars(str: string) =
    let freqMap = charFreq str
    let maxFreq = freqMap.Values |> Seq.max
    freqMap
    |> Seq.filter (fun kvp -> kvp.Value = maxFreq)
    |> Seq.map (fun kvp -> kvp.Key)
    |> Seq.toList

// Тестирование
[<EntryPoint>]
let main argv =
    let word = "барабан"
    let result = maxFreqChars word
    printfn "Наиболее часто встречающиеся символы: %A" result
    0