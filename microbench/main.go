package main

import (
	"log"
	"os"
	"os/exec"
	"time"
)

func bench(dir string, cmd string, args ...string) time.Duration {
	err := os.Chdir(dir)
	if err != nil {
		log.Fatalf("run: os.Chdir failed for %s: %v", cmd, err)
	}
	start := time.Now()
	_, err = exec.Command(cmd, args...).Output()
	if err != nil {
		log.Fatalf("run: %s failed: %v", cmd, err)
	}
	dur := time.Since(start)
	return dur
}

func main() {
	runCount := 20
	var goDur, rustDur time.Duration = 0, 0
	for i := 0; i < runCount; i += 1 {
		goDur += bench("../calorie_counting", "go", "run", "main.go")
		rustDur += bench("../calorie_counting_rust", "cargo", "run")
	}
	log.Printf("microbench: total time used by\n\tgo: %v\n\trust: %v",
		goDur, rustDur)
}
