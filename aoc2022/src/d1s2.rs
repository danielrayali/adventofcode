use std::fs::File;
use std::io::BufRead;
use std::io::BufReader;

pub fn d1s2() {
    let f = File::open("input/day1.txt").expect("Unable to open file");
    let reader = BufReader::new(f);
    let mut all_calories: Vec<i32> = Vec::new();
    let mut current_calories = 0;
    for line_result in reader.lines() {
        let line = line_result.unwrap();
        if line.is_empty() {
            all_calories.push(current_calories);
            current_calories = 0;
        } else {
            current_calories += line.parse::<i32>().unwrap();
        }
    }
    all_calories.sort();
    all_calories.reverse();
    println!("Top calories: {} {} {}", all_calories[0], all_calories[1], all_calories[2]);
    println!("Total: {}", all_calories[0] + all_calories[1] + all_calories[2]);
}
