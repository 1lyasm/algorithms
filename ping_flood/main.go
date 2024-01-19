package main

import (
	"os/exec"
	"sync"
)

func main() {
	ip := "192.168.1.6"
	wg := new(sync.WaitGroup)
	iter_count := 100
	for i := 0; i < iter_count; i += 1 {
		wg.Add(1)
		go func() {
			cmd := exec.Command("ping", ip)
			cmd.StdoutPipe()
			cmd.Run()
			wg.Done()
		}()
	}
	wg.Wait()
}
