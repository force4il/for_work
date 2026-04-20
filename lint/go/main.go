package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

// бесконечная рекурсия
// func rec() {
// 	rec()
// }

func main() {
	tasks := make([]string, 0)
	completed := make([]bool, 0)
	// rec()
	// arr := [3]int{1, 2, 3}
	// fmt.Println(arr[3])	

	//deadlock блокировка потоков 
	// ch := make(chan int)
	// ch <- 5

	scanner := bufio.NewScanner(os.Stdin)
	fmt.Println("To-Do List (команды: add, list, done, del, exit)")

	for {
		scanner.Scan()
		input := scanner.Text()
		parts := strings.Fields(input)
		
		if len(parts) == 0 {
			continue
		}
		
		switch parts[0] {
			case "exit":
				fmt.Println("Выход из программы")
				return
				
			case "add":
				if len(parts) < 2 {
					fmt.Println("Укажите задачу")
					continue
				}
				
				task := strings.Join(parts[1:], " ")
				tasks = append(tasks, task)
				completed = append(completed, false)
				fmt.Printf("Добавлено: %s (ID: %d)\n", task, len(tasks))
			
			case "list":
				if len(tasks) == 0 {
					fmt.Println("Нет задач")
					continue
				}
				fmt.Println("\nСписок задач:")

				for i, task := range tasks {
					status := "-"
					if completed[i] {
						status = "+"
					}

					fmt.Printf("%s %d. %s\n", status, i+1, task)
				}

				fmt.Println()
				
			case "done":
				if len(parts) != 2 {
					fmt.Println("Укажите ID")
					continue
				}

				id, err := strconv.Atoi(parts[1])
				if err != nil || id < 1 || id > len(tasks) {
					fmt.Println("Неверный ID")
					continue
				}
				completed[id-1] = true
				fmt.Printf("Задача %d выполнена!\n", id)
				
			case "del":
				if len(parts) != 2 {
					fmt.Println("Укажите ID")
					continue
				}

				id, err := strconv.Atoi(parts[1])
				if err != nil || id < 1 || id > len(tasks) {
					fmt.Println("Неверный ID")
					continue
				}

				tasks = append(tasks[:id-1], tasks[id:]...)
				completed = append(completed[:id-1], completed[id:]...)
				fmt.Printf("Задача %d удалена\n", id)
				
			default:
				fmt.Println("Неизвестная команда. Доступно: add, list, done, del, exit")
			}
	}
}