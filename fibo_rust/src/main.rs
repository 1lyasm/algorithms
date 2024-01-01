fn fibo(num: i64) -> i64 {
    // println!("fibo: num: {}", num);
    if num == 0 {
        return 0;
    } else if num == 1 {
        return 1;
    } else if num == 2 {
        return 1;
    } else if num == 3 {
        return 2;
    } else if num == 4 {
        return 3;
    }
    return fibo(num - 1) + fibo(num - 2);
}

fn main() {
    for i in 0..15 {
        println!("n[{0}]: {1}", i, fibo(i));
    }
}

