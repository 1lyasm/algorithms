package main

import "os"
import "log"
import "strings"
import "strconv"
import "fmt"
import "io"

func readCount(str string) (int, int) {
	count, factor := 0, 1
	firstNewline := strings.Index(str, "\n")
	index := firstNewline - 1
	for index >= 0 {
		count += int(str[index] - '0') * factor
		factor *= 10
		index -= 1
	}
	return count, firstNewline + 1
}

func readWord(str string, startIndex int) (string, int) {
	curIndex := startIndex
	for str[curIndex] != ',' && str[curIndex] != '\n' {
		curIndex += 1
	}
	return str[startIndex:curIndex], curIndex + 1
}

func contains(bytes []byte, target byte) bool {
	found := false
	for i := 0; i < len(bytes) && !found; i += 1 {
		if (target == bytes[i]) {
			found = true
		}
	}
	return found
}

func countUnique(str string) int {
	seen, count := make([]byte, 1), 0
	for i := 0; i < len(str); i += 1 {
		char := str[i]
		if !contains(seen, char) {
			seen = append(seen, char)
			count += 1
		}
	}
	return count
}

func sumDigits(str string) int {
	sum := 0
	for i := 0; i < len(str); i += 1 {
		sum += int(str[i] - '0')
	}
	return sum
}

func printCipher(str string, startIndex int) int {
	curIndex := startIndex
	name, curIndex := readWord(str, curIndex)
	middle, curIndex := readWord(str, curIndex)
	lastname, curIndex := readWord(str, curIndex)
	dayStr, curIndex := readWord(str, curIndex)
	monthStr, curIndex := readWord(str, curIndex)
	yearStr, curIndex := readWord(str, curIndex)
	day, _ := strconv.Atoi(dayStr)
	month, _ := strconv.Atoi(monthStr)
	year, _ := strconv.Atoi(yearStr)
	log.Printf("printCipher: name: %s, middle: %s, lastname: %s, day: %d, month: %d, year: %d",
		name, middle, lastname, day, month, year)
	uniqCount := countUnique(name + middle + lastname)
	log.Printf("printCipher: uniqCount: %d", uniqCount)
	digitSum := sumDigits(dayStr) + sumDigits(monthStr)
	log.Printf("printCipher: digitSum: %d", digitSum)
	firstLetter := int(name[0] - 'A' + 1)
	log.Printf("printCipher: firstLetter: %d", firstLetter)
	asDecimal := uniqCount + 64 * digitSum + 256 * firstLetter
	log.Printf("printCipher: asDecimal: %d", asDecimal)
	asHexStr := strconv.FormatInt(int64(asDecimal), 16)
	fmt.Printf("%s ", asHexStr[len(asHexStr) - 3:])
	return curIndex
}

func main() {
	log.SetOutput(io.Discard)
	bytes, err := os.ReadFile("input.txt")
	if err != nil {
		log.Fatalf("main: os.ReadFile failed :%v", err)
	}
	str := string(bytes)
	count, curIndex := readCount(str)
	for i := 0; i < count; i += 1 {
		curIndex = printCipher(str, curIndex)
	}
	fmt.Printf("\n")
}

