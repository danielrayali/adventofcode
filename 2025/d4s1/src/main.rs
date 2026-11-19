use std::fs;

fn main() {
    let input = fs::read_to_string("input.txt").expect("failed to read input.txt");

    let mut grid: Vec<Vec<u8>> = input
        .lines()
        .map(|line| line.trim())
        .filter(|line| !line.is_empty())
        .map(|line| {
            let mut row = vec![0];
            row.extend(line.chars().map(|c| match c {
                '@' => 1,
                '.' => 0,
                _ => panic!("unexpected character: {}", c),
            }));
            row.push(0);
            row
        })
        .collect();

    let width = grid[0].len();
    grid.insert(0, vec![0; width]);
    grid.push(vec![0; width]);

    let mut total_under_four = 0;
    for row in 1..grid.len()-1 {
        for column in 1..grid[row].len()-1 {
            if grid[row][column] == 0 {
                print!(".");
                continue;
            }

            let neighbors = 0

            // Upper left
            + grid[row-1][column-1]

            // Upper middle
            + grid[row-1][column]

            // Upper right
            + grid[row-1][column+1]

            // Left middle
            + grid[row][column-1]

            // Right middle
            + grid[row][column+1]

            // Lower left
            + grid[row+1][column-1]

            // Lower middle
            + grid[row+1][column]

            // Lower right
            + grid[row+1][column+1];

            if neighbors < 4 {
                total_under_four += 1;
                print!("x");
            } else {
                print!("@");
            }

        }
        print!("\n");
    }

    println!("total under four: {}", total_under_four);
}
