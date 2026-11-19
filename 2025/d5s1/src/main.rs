use std::{collections::HashSet, fs};

fn main() {
    let input = fs::read_to_string("input.txt").expect("failed to read input.txt");

    // Ranges and IDs are separated by a blank line.
    let (range_section, id_section) = input
        .split_once("\n\n")
        .expect("expected a blank line between ranges and ids");

    let ranges: Vec<(u64, u64)> = range_section
        .lines()
        .map(|line| {
            let (lo, hi) = line.split_once('-').expect("range missing '-'");
            (lo.trim().parse().unwrap(), hi.trim().parse().unwrap())
        })
        .collect();

    let mut fresh = HashSet::new();
    for line in id_section.lines().filter(|l| !l.trim().is_empty()) {
        let id: u64 = line.trim().parse().unwrap();
        for range in &ranges {
            if id >= range.0 && id <= range.1 {
                fresh.insert(id);
            } 
        }
    }

    println!("total {}", fresh.len());
}
