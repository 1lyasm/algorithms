package main

import (
	"fmt"
	"log"
	"os"
	"os/exec"
	"time"
)

type BenchRes struct {
	name string
	dur  time.Duration
}

func bench(runCount int, dir string, cmd string, args ...string) time.Duration {
	err := os.Chdir(dir)
	if err != nil {
		log.Fatalf("bench: os.Chdir failed for %s: %v", cmd, err)
	}
	_, err = exec.Command(cmd, args...).Output()
	if err != nil {
		log.Fatalf("bench: %s failed: %v", cmd, err)
	}
	var dur time.Duration = 0
	for i := 0; i < runCount; i += 1 {
		start := time.Now()
		_, err = exec.Command("./main").Output()
		if err != nil {
			log.Fatalf("bench: binary failed: %v", err)
		}
		dur += time.Since(start)
	}
	return dur
}

func findMinDur(results []BenchRes) time.Duration {
	var minDur time.Duration = time.Hour
	for _, result := range results {
		minDur = min(result.dur, minDur)
	}
	return minDur
}

func printAsRatio(results []BenchRes) {
	fmt.Printf("total time used as ratios\n")
	minDur := findMinDur(results)
	for _, result := range results {
		fmt.Printf("\t%s: %.2fx\n", result.name,
			float32(result.dur.Microseconds())/float32(minDur.Microseconds()))
	}
}

func printResults(results []BenchRes) {
	fmt.Printf("total time used\n")
	for _, result := range results {
		fmt.Printf("\t%s: %v\n", result.name, result.dur)
	}
	printAsRatio(results)
}

func main() {
	runCount := 10000
	results := []BenchRes{
		{name: "go", dur: bench(runCount, "../go", "go", "build", "-ldflags", "-s", "-o", "main")},
		{name: "rust", dur: bench(runCount, "../rust", "cargo", "build", "-r", "-Z", "unstable-options",
			"--out-dir", ".", "--bin", "main")},
		// {name: "zig", dur: bench(runCount, "../zig", "zig", "build-exe",
		//    "-O", "ReleaseFast", "-femit-bin=main", "src/main.zig")},
		{name: "c", dur: bench(runCount, "../c", "make")}}
	printResults(results)
}
