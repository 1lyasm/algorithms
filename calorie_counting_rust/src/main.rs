fn read_int(bytes: &[u8], start: i32) -> (i32, i32) {
    let (mut number, mut end, mut factor) = (0, start, 1);
    while end >= 0 && bytes[end as usize] != '\n' as u8 {
        number += factor * (bytes[end as usize] - '0' as u8) as i32;
        factor *= 10;
        end -= 1;
    }
    end -= 1;
    return (number, end);
}

fn sum_group(bytes: &[u8], start: i32) -> (i32, i32) {
    let (mut sum, mut end) = (0, start);
    let mut number: i32;
    while end >= 0 && bytes[end as usize] != '\n' as u8 {
        (number, end) = read_int(bytes, end);
        sum += number;
    }
    end -= 1;
    return (sum, end);
}

fn find_max_calories(bytes: &[u8]) -> i32 {
    let (mut cur_index, mut max_sum) = ((bytes.len() - 1) as i32, -1);
    let mut sum: i32;
    while cur_index >= 0 {
        (sum, cur_index) = sum_group(bytes, cur_index);
        max_sum = std::cmp::max(sum, max_sum);
    }
    return max_sum;
}

fn main() {
    let str = std::fs::read_to_string("src/input.txt").unwrap();
    println!("{}", find_max_calories(&str.as_bytes()))
}
