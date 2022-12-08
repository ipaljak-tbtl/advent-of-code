pub fn solve(input: &[String]) -> u32 {
    let mut trees: Vec<Vec<u32>> = Vec::new();

    for line in input {
        let mut row = Vec::new();

        for c in line.chars() {
            row.push(c.to_digit(10).unwrap());
        }

        trees.push(row);
    }

    let mut cnt = 0;

    for (i, row) in trees.iter().enumerate() {
        for (j, size) in row.iter().enumerate() {
            let mut found = true;
            for ti in 0..j {
                if &trees[i][ti] >= size {
                    found = false;
                }
            }
            if found {
                cnt += 1;
                continue;
            }

            found = true;
            for ti in (j + 1)..row.len() {
                if &trees[i][ti] >= size {
                    found = false;
                }
            }
            if found {
                cnt += 1;
                continue;
            }

            found = true;
            for ti in 0..i {
                if &trees[ti][j] >= size {
                    found = false;
                }
            }
            if found {
                cnt += 1;
                continue;
            }

            found = true;
            for ti in (i + 1)..trees.len() {
                if &trees[ti][j] >= size {
                    found = false;
                }
            }
            if found {
                cnt += 1;
                continue;
            }
        }
    }

    cnt
}
