use std::fs;

fn get_next_suitable(num: u64) -> u64 {
    num + 1
}

fn is_invalid(num: u64) -> bool {
    let num_str = num.to_string();
    let len = num_str.len();
    (1..=len / 2).any(|chunk| len % chunk == 0 && num_str[..chunk].repeat(len / chunk) == num_str)
}

fn process_range(start: u64, end: u64) -> u64 {
    let mut total = 0;
    let mut num = start;
    while num <= end {
        if is_invalid(num) {
            println!("invalid: {}", num);
            total += num;
        }
        num = get_next_suitable(num);
    }

    total
}

fn main() {
    let input = fs::read_to_string("input.txt").expect("could not read input.txt");
    let mut total = 0;
    for range in input.trim().split(',') {
        let (start, end) = range.split_once('-').expect("range should look like a-b");
        let start: u64 = start.parse().unwrap();
        let end: u64 = end.parse().unwrap();
        total += process_range(start, end)
    }
    println!("total {}", total);
}
