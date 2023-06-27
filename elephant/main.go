package main

import "fmt"

func main() {
	var inp int
	fmt.Scanf("%d", &inp)
	res := inp / 5
	if inp%5 != 0 {
		res += 1
	}
	fmt.Printf("%d", res)
}
