use std::env;
use std::error::Error;
use std::fs::File;
use std::io::{BufRead, BufReader};

fn main() -> Result<(), Box<dyn Error>> {
    // Take the file path from the command line, e.g. `cargo run -- src/main.rs`
    let path = env::args().nth(1).expect("usage: print_lines <file>");

    let file = File::open(&path)?;
    let reader = BufReader::new(file);
    let mut dial = 50;
    println!("The dial stars by point at {}", dial);
    let mut zero_count = 0;
    for line in reader.lines() {
        let line = line?;
        let mut chars = line.chars();

        match chars.next() {
            Some('L') => {
                let rest = chars.as_str();
                let n: i32 = rest.parse().unwrap();
                dial = (dial - n).rem_euclid(100);
            },
            Some('R') => {
                let rest = chars.as_str();
                let n: i32 = rest.parse().unwrap();
                dial = (dial + n).rem_euclid(100);
            },
            Some(c) => {
                return Err(format!("Unknown prefix: {}", c).into());
            },
            None => {
                return Err(format!("No characters matched").into());
            }
        }

        if dial == 0 {
            zero_count += 1;
        }

        println!("The dial is rotated {} to point at {}.", line, dial);
    }

    println!("Number of times ending at 0: {}", zero_count);

    Ok(())
}

