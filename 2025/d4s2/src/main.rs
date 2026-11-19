use std::fs;

fn find_total_under_four(grid: &mut Vec<Vec<u8>>) -> i32 {
    let mut total = 0;
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
                if total == 0 { grid[row][column] = 0; }
                print!("x");
                total += 1;
            } else {
                print!("@");
            }

        }
        print!("\n");
    }
    total
}

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

    let mut total = 0;
    while find_total_under_four(&mut grid) > 0 {
        total += 1;
    }
    
    println!("total removed {}", total);
}
