pub fn solve(input: &[String]) -> usize {
    let mut visited = std::collections::HashSet::new();
    let (mut hi, mut hj) = (0, 0);
    let (mut ti, mut tj) = (0, 0);

    visited.insert((ti, tj));

    for line in input {
        let s: u32 = line[2..].parse().unwrap();
        let (dhi, dhj) = match line.chars().next().unwrap() {
            'U' => (1, 0),
            'D' => (-1, 0),
            'R' => (0, 1),
            'L' => (0, -1),
            _ => panic!(),
        };

        for _ in 0..s {
            hi += dhi;
            hj += dhj;

            let (dti, dtj) = match (ti, tj) {
                (x, y) if (x, y) == (hi - 2, hj) => (1, 0),
                (x, y) if (x, y) == (hi + 2, hj) => (-1, 0),
                (x, y) if (x, y) == (hi, hj - 2) => (0, 1),
                (x, y) if (x, y) == (hi, hj + 2) => (0, -1),
                (x, y) if (x, y) == (hi + 2, hj + 1) => (-1, -1),
                (x, y) if (x, y) == (hi + 2, hj - 1) => (-1, 1),
                (x, y) if (x, y) == (hi - 2, hj + 1) => (1, -1),
                (x, y) if (x, y) == (hi - 2, hj - 1) => (1, 1),
                (x, y) if (x, y) == (hi + 1, hj + 2) => (-1, -1),
                (x, y) if (x, y) == (hi + 1, hj - 2) => (-1, 1),
                (x, y) if (x, y) == (hi - 1, hj + 2) => (1, -1),
                (x, y) if (x, y) == (hi - 1, hj - 2) => (1, 1),
                _ => (0, 0),
            };

            ti += dti;
            tj += dtj;

            visited.insert((ti, tj));
        }
    }

    visited.len()
}
