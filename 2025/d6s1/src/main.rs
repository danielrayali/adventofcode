use std::fs;

fn main() {
    let input = fs::read_to_string("src/input.txt").expect("failed to read src/input.txt");

    // matrix[row][column], same layout as the input
    let mut matrix: Vec<Vec<u64>> = Vec::new();
    let mut ops: Vec<String> = Vec::new();

    for line in input.lines() {
        let tokens: Vec<&str> = line.split_whitespace().collect();
        if tokens.is_empty() {
            continue;
        }

        // The first line that isn't all numbers is the operator line (the last row)
        let numbers: Result<Vec<u64>, _> = tokens.iter().map(|t| t.parse::<u64>()).collect();
        let Ok(numbers) = numbers else {
            ops = tokens.iter().map(|t| t.to_string()).collect();
            break;
        };

        matrix.push(numbers);
    }

    let mut result = vec![0u64; ops.len()];
    for row in 0..matrix.len() {
        for column in 0..matrix[row].len() {
            if ops[column] == "+" {
                result[column] = 0;
            } else {
                result[column] = 1;
            }
        }
    }

    println!("{:?}", matrix);
    for row in 0..matrix.len() {
        for column in 0..matrix[row].len() {
            if ops[column] == "+" {
                result[column] += matrix[row][column];
            } else {
                result[column] *= matrix[row][column];
            }
        }
    }

    println!("{:?}", result);
    println!("{:?}", ops);

    println!("sum {}", result.iter().sum::<u64>());
}
