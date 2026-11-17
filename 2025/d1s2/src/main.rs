use std::env;
use std::error::Error;
use std::fs::File;
use std::io::{BufRead, BufReader};

fn mod_100(dial: i32) -> (i32, i32) {
    let result = dial.rem_euclid(100);
    let mut rotations = dial.div_euclid(100).abs();
    println!("dial: {}, result: {}, rotations: {}", dial, result, rotations);
    (result, rotations)
}

fn main() -> Result<(), Box<dyn Error>> {
    // Take the file path from the command line, e.g. `cargo run -- src/main.rs`
    let path = env::args().nth(1).expect("usage: print_lines <file>");

    let file = File::open(&path)?;
    let reader = BufReader::new(file);
    let mut dial = 50;
    let mut total_rotations = 0;
    let mut last_rotations = 0;
    println!("The dial stars by point at {}", dial);
    for line in reader.lines() {
        let line = line?;
        let mut chars = line.chars();

        match chars.next() {
            Some('L') => {
                let n: i32 = chars.as_str().parse().unwrap();
                let mirrored = (100 - dial) % 100;
                total_rotations += (mirrored + n) / 100;
                dial = (dial - n).rem_euclid(100);
            },
            Some('R') => {
                let rest = chars.as_str();
                let n: i32 = rest.parse().unwrap();
                // dial = (dial + n).rem_euclid(100);
                let (new_dial, rotations) = mod_100(dial + n);
                dial = new_dial;
                total_rotations += rotations;
            },
            Some(c) => {
                return Err(format!("Unknown prefix: {}", c).into());
            },
            None => {
                return Err(format!("No characters matched").into());
            }
        }

        print!("The dial is rotated {} to point at {}", line, dial);
        
        if last_rotations != total_rotations {
            println!("; during this rotation, it points at 0 {} times.", total_rotations - last_rotations);
            last_rotations = total_rotations;
        } else {
            println!(".");
        }
    }

    println!("Number of times on zero: {}", total_rotations);

    Ok(())
}

