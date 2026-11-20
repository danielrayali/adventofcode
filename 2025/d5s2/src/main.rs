use std::fs;

fn consolidate(ranges: &mut Vec<(u64, u64)>) -> bool {
    let mut i = 0;
    while i < ranges.len() {
        let mut j = 0;
        while j < ranges.len() {
            if i == j {
                j += 1;
                continue;
            }

            let left = ranges[i];
            let right = ranges[j];

            if left.0 >= right.0 && left.1 <= right.1 {
                // delete left
                ranges.remove(i);
                return true;
            }

            if right.0 >= left.0 && right.1 <= left.1 {
                // delete right
                ranges.remove(j);
                return true;
            }

            if left.0 >= right.0 && left.0 <= right.1 {
                //new range
                ranges.push((left.0.min(right.0), left.1.max(right.1)));

                // delete both
                let first = i.min(j);
                let second = i.max(j);
                ranges.remove(second);
                ranges.remove(first);

                return true;
            }

            if left.1 <= right.1 && left.1 >= right.0 {
                //new range
                ranges.push((left.0.min(right.0), left.1.max(right.1)));

                // delete both
                let first = i.min(j);
                let second = i.max(j);
                ranges.remove(second);
                ranges.remove(first);

                return true;
            }
            j += 1;
        }
        i += 1;
    }
    false
}

fn calculate_total(ranges: &mut Vec<(u64, u64)>) -> u64 {
    let mut total = 0;
    for range in ranges {
        total += range.1 - range.0 + 1;
    }
    total
}

fn main() {
    let input = fs::read_to_string("input.txt").expect("failed to read input.txt");

    // Ranges and IDs are separated by a blank line.
    let (range_section, _) = input
        .split_once("\n\n")
        .expect("expected a blank line between ranges and ids");

    let mut ranges: Vec<(u64, u64)> = range_section
        .lines()
        .map(|line| {
            let (lo, hi) = line.split_once('-').expect("range missing '-'");
            (lo.trim().parse().unwrap(), hi.trim().parse().unwrap())
        })
        .collect();

    println!("{:?}", ranges);
    while consolidate(&mut ranges) {
        println!("{:?}", ranges);
    }

    println!("total {}", calculate_total(&mut ranges));
}
