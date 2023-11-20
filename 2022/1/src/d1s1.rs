use std::fs::File;
use std::io::BufRead;
use std::io::BufReader;

pub fn d1s1() {
    let f = File::open("input/day1.txt").expect("Unable to open file");
    let reader = BufReader::new(f);
    let mut max_calories = 0;
    let mut elf_calories = 0;
    for line_result in reader.lines() {
        let line = line_result.unwrap();
        if line.is_empty() {
            if elf_calories > max_calories {
                max_calories = elf_calories;
            }
            elf_calories = 0;
        } else {
            elf_calories += line.parse::<i32>().unwrap();
        }
    }
    println!("Max calories: {}", max_calories);
}
