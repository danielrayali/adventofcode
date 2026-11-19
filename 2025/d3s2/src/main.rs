use std::fs;

fn find_max_in_line(line: &str) -> u64 {
    println!("{}", line);

    let mut start = 0;
    let mut end = line.len() - 12;
    let mut max = vec![];

    while end < line.len() {

        let (offset, &max_digit) = line[start..=end].as_bytes()
            .iter()
            .enumerate()
            .rev()
            .max_by_key(|&(_, &b)| b)
            .unwrap();
        
        max.push(max_digit - b'0');
        println!("start: {}, end: {}, max: {:?}", start, end, max);
        start = start + offset +1;
        end += 1;
    }

    assert_eq!(max.len(), 12);
    max.iter().fold(0u64, |acc, &d| acc * 10 + d as u64)
}

fn main() {
    let input = fs::read_to_string("input.txt").expect("failed to read input.txt");

    let mut total = 0;
    for line in input.lines() {
        let line = line.trim();
        if line.is_empty() {
            continue;
        }

        let max = find_max_in_line(line);

        println!("{}", max);
        total += max;
    }
    println!("total {}", total);
}
