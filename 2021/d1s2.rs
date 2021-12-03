use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;

fn main() {
    // File hosts must exist in current path before this produces output
    let mut increases = 0;
    if let Ok(lines) = read_lines("d1s1.txt") {
        for line_iter in lines.skip(3) {
            let mut en_iter = line_iter.enumerate();
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
