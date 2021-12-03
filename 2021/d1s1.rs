use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;

fn main() {
    // File hosts must exist in current path before this produces output
    let mut increases = 0;
    if let Ok(lines) = read_lines("d1s1.txt") {
        // Consumes the iterator, returns an (Optional) String
        let mut prev_depth = std::u32::MAX;
        for line in lines {
            if let Ok(depth) = line {
                let depth_int = depth.parse::<u32>().unwrap();
                if prev_depth < depth_int {
                    increases += 1;
                }
                prev_depth = depth_int;
            }
        }
    }

    println!("Number of increases: {}", increases);
}

// The output is wrapped in a Result to allow matching on errors
// Returns an Iterator to the Reader of the lines of the file.
fn read_lines<P>(filename: P) -> io::Result<io::Lines<io::BufReader<File>>>
where P: AsRef<Path>, {
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file).lines())
}
