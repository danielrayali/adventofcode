use std::fs;

fn main() {
    let input = fs::read_to_string("input.txt").expect("failed to read input.txt");

    let mut total = 0;
    for line in input.lines() {
        let line = line.trim();
        if line.is_empty() {
            continue;
        }

        let digits: Vec<u32> = line.chars().filter_map(|c| c.to_digit(10)).collect();
        if digits.len() < 2 {
            continue;
        }

        // The first digit can't be the last one in the line (needs a digit to its right).
        let first = *digits[..digits.len() - 1].iter().max().unwrap();

        // For each instance of the largest first digit, find the largest digit to its right.
        let mut best = 0;
        for (i, &d) in digits[..digits.len() - 1].iter().enumerate() {
            if d == first {
                let second = *digits[i + 1..].iter().max().unwrap();
                best = best.max(first * 10 + second);
            }
        }

        println!("{}", best);
        total += best;
    }
    println!("total {}", total);
}
