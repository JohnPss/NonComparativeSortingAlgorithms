package Benchmarks

import (
    "fmt"
    "ordenacao-go/Algorithms"
    "ordenacao-go/Structures"
    "ordenacao-go/Utils"
    "time"
)

type BenchmarkResult struct {
    StructureType string
    Algorithm     string
    Size          int
    Time          time.Duration
    MemoryUsed    int64
}

func measureTime(fn func()) time.Duration {
    start := time.Now()
    fn()
    return time.Since(start)
}

func benchmarkStructure(name string, ds Utils.DataStructure, data []int) BenchmarkResult {
    // Carregar dados na estrutura
    ds.FromArray(data)
    
    var duration time.Duration
    
    // Medir tempo de ordenação
    duration = measureTime(func() {
        // Converter para array
        arr := ds.ToArray()
        
        // Ordenar com Counting Sort
        sorted := Algorithms.CountingSort(arr)
        
        // Converter de volta para estrutura
        ds.FromArray(sorted)
    })
    
    return BenchmarkResult{
        StructureType: name,
        Algorithm:     "counting",
        Size:          len(data),
        Time:          duration,
    }
}

func RunAllBenchmarks(data []int) {
    fmt.Println("\n=== Executando Benchmarks ===")
    fmt.Printf("Tamanho dos dados: %d elementos\n\n", len(data))
    
    fmt.Printf("\n--- Algoritmo: Counting Sort ---\n")
    
    // Lista Linear
    listLinear := Structures.NewListLinear(len(data) + 100)
    result := benchmarkStructure("Lista Linear", listLinear, data)
    fmt.Printf("%-20s: %v\n", result.StructureType, result.Time)
    
    // Lista Dinâmica
    listDynamic := Structures.NewListDynamic()
    result = benchmarkStructure("Lista Dinâmica", listDynamic, data)
    fmt.Printf("%-20s: %v\n", result.StructureType, result.Time)
    
    // Fila Linear
    queueLinear := Structures.NewQueueLinear(len(data) + 100)
    result = benchmarkStructure("Fila Linear", queueLinear, data)
    fmt.Printf("%-20s: %v\n", result.StructureType, result.Time)
    
    // Fila Dinâmica
    queueDynamic := Structures.NewQueueDynamic()
    result = benchmarkStructure("Fila Dinâmica", queueDynamic, data)
    fmt.Printf("%-20s: %v\n", result.StructureType, result.Time)
    
    // Pilha Linear
    stackLinear := Structures.NewStackLinear(len(data) + 100)
    result = benchmarkStructure("Pilha Linear", stackLinear, data)
    fmt.Printf("%-20s: %v\n", result.StructureType, result.Time)
    
    // Pilha Dinâmica
    stackDynamic := Structures.NewStackDynamic()
    result = benchmarkStructure("Pilha Dinâmica", stackDynamic, data)
    fmt.Printf("%-20s: %v\n", result.StructureType, result.Time)
}

func RunBenchmarkWithSizes(csvFile string, sizes []int) {
    fmt.Println("=== Benchmark com Diferentes Tamanhos ===")
    
    for _, size := range sizes {
        fmt.Printf("\n--- Tamanho: %d elementos ---\n", size)
        
        data, err := Utils.LoadRatingsCSV(csvFile, size)
        if err != nil {
            fmt.Printf("Erro ao carregar dados: %v\n", err)
            continue
        }
        
        RunAllBenchmarks(data)
    }
}