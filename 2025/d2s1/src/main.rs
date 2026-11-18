use std::fs;

fn get_next_suitable(num: u64) -> u64 {
    if num < 11 {
        return 11;
    }

    let num_str = num.to_string();
    let len = num_str.len();
    if (len & 0x1) > 0 {
        return 10u64.pow(len as u32);
    }

    let left = num / 10u64.pow((len >> 1) as u32);
    let right = num % 10u64.pow((len >> 1) as u32);
    if right < left {
        left * 10u64.pow((len >> 1) as u32) + left
    } else {
        (left + 1) * 10u64.pow((len >> 1) as u32) + left + 1
    }
}

fn is_invalid(num: u64) -> bool {
    let num_str = num.to_string();
    let len = num_str.len();
    if (len & 0x1) > 0 {
        return false;
    }

    let (left, right) = num_str.split_at(len / 2);
    left == right 
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
