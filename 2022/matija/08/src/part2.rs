pub fn solve(input: &[String]) -> u32 {
    let mut trees: Vec<Vec<u32>> = Vec::new();

    for line in input {
        let mut row = Vec::new();

        for c in line.chars() {
            row.push(c.to_digit(10).unwrap());
        }

        trees.push(row);
    }

    let mut max_score = 0;

    for (i, row) in trees.iter().enumerate() {
        for (j, size) in row.iter().enumerate() {
            let mut score_left = 0;
            for ti in (0..j).rev() {
                if &trees[i][ti] < size {
                    score_left += 1;
                } else if &trees[i][ti] == size {
                    score_left += 1;
                    break;
                }
            }

            let mut score_right = 0;
            for ti in (j + 1)..row.len() {
                if &trees[i][ti] < size {
                    score_right += 1;
                } else if &trees[i][ti] == size {
                    score_right += 1;
                    break;
                }
            }

            let mut score_up = 0;
            for ti in (0..i).rev() {
                if &trees[ti][j] < size {
                    score_up += 1;
                } else if &trees[ti][j] == size {
                    score_up += 1;
                    break;
                }
            }

            let mut score_down = 0;
            for ti in (i + 1)..trees.len() {
                if &trees[ti][j] < size {
                    score_down += 1;
                } else if &trees[ti][j] == size {
                    score_down += 1;
                    break;
                }
            }

            let score = score_left * score_right * score_up * score_down;

            if score > max_score {
                max_score = score;
            }
        }
    }

    max_score
}
