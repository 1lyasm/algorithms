package main

import (
	"fmt"
	"log"
	"os"
)

func readInt(str string, start int) (int, int) {
	number, end, factor := 0, start, 1
	for end >= 0 && str[end] != '\n' {
		number += factor * int(str[end]-'0')
		factor *= 10
		end -= 1
	}
	end -= 1
	return number, end
}

func sumGroup(str string, start int) (int, int) {
	sum, end := 0, start
	var number int
	for end >= 0 && str[end] != '\n' {
		number, end = readInt(str, end)
		sum += number
	}
	end -= 1
	return sum, end
}

func findMaxCalories(str string) int {
	curIndex, maxSum := len(str)-1, -1
	var sum int
	for curIndex >= 0 {
		sum, curIndex = sumGroup(str, curIndex)
		if sum > maxSum {
			maxSum = sum
		}
	}
	return maxSum
}

func main() {
	bytes, err := os.ReadFile("input.txt")
	if err != nil {
		log.Fatalf("main: os.ReadFile failed: %v", err)
	}
	str := string(bytes)
	fmt.Printf("%d\n", findMaxCalories(str))
}
