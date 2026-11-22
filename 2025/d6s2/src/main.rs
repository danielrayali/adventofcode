use std::fs;

fn main() {
    let input = fs::read_to_string("input.txt").expect("failed to read input.txt");

    let lines: Vec<Vec<u8>> = input.lines().map(|l| l.as_bytes().to_vec()).collect();
    let (op_line, digit_lines) = lines.split_last().expect("input is empty");

    // Every line is treated as being as wide as the widest one (missing chars are spaces)
    let width = lines.iter().map(|l| l.len()).max().unwrap_or(0);
    let char_at = |line: &Vec<u8>, col: usize| line.get(col).copied().unwrap_or(b' ');

    // Column positions of each operator. A problem starts at its operator's column and
    // runs up to the single separator space before the next operator (or to the line end).
    let op_cols: Vec<usize> = (0..op_line.len())
        .filter(|&c| op_line[c] == b'+' || op_line[c] == b'*')
        .collect();

    let mut grand_total: u128 = 0;

    for (i, &start) in op_cols.iter().enumerate() {
        let end = match op_cols.get(i + 1) {
            Some(&next) => next - 1, // skip the separator space
            None => width,
        };

        // Each column is one number: top row is the most significant digit, spaces are skipped
        let numbers: Vec<u128> = (start..end)
            .map(|col| {
                digit_lines.iter().fold(0u128, |n, line| match char_at(line, col) {
                    b' ' => n,
                    c => n * 10 + (c - b'0') as u128,
                })
            })
            .collect();

        let result: u128 = match op_line[start] {
            b'+' => numbers.iter().sum(),
            _ => numbers.iter().product(),
        };

        println!("{} {:?} = {}", op_line[start] as char, numbers, result);
        grand_total += result;
    }

    println!("Grand total: {}", grand_total);
}
