pub fn solve(input: &[String]) -> usize {
    let mut visited = std::collections::HashSet::new();
    let mut knots = vec![(0, 0); 10];

    visited.insert((0, 0));

    for line in input {
        let s: u32 = line[2..].parse().unwrap();
        let (di, dj) = match line.chars().next().unwrap() {
            'U' => (1, 0),
            'D' => (-1, 0),
            'R' => (0, 1),
            'L' => (0, -1),
            _ => panic!(),
        };

        for _ in 0..s {
            let (hi, hj) = knots[0];

            let (mut pi, mut pj) = (hi + di, hj + dj);
            knots[0] = (pi, pj);

            for (ci, cj) in knots.iter_mut().skip(1) {
                let (di, dj) = match (*ci, *cj) {
                    (x, y) if (x, y) == (pi - 2, pj) => (1, 0),
                    (x, y) if (x, y) == (pi + 2, pj) => (-1, 0),
                    (x, y) if (x, y) == (pi, pj - 2) => (0, 1),
                    (x, y) if (x, y) == (pi, pj + 2) => (0, -1),
                    (x, y) if (x, y) == (pi + 2, pj + 1) => (-1, -1),
                    (x, y) if (x, y) == (pi + 2, pj - 1) => (-1, 1),
                    (x, y) if (x, y) == (pi - 2, pj + 1) => (1, -1),
                    (x, y) if (x, y) == (pi - 2, pj - 1) => (1, 1),
                    (x, y) if (x, y) == (pi + 1, pj + 2) => (-1, -1),
                    (x, y) if (x, y) == (pi + 1, pj - 2) => (-1, 1),
                    (x, y) if (x, y) == (pi - 1, pj + 2) => (1, -1),
                    (x, y) if (x, y) == (pi - 1, pj - 2) => (1, 1),
                    (x, y) if (x, y) == (pi + 2, pj + 2) => (-1, -1),
                    (x, y) if (x, y) == (pi + 2, pj - 2) => (-1, 1),
                    (x, y) if (x, y) == (pi - 2, pj + 2) => (1, -1),
                    (x, y) if (x, y) == (pi - 2, pj - 2) => (1, 1),
                    _ => (0, 0),
                };

                *ci += di;
                *cj += dj;

                pi = *ci;
                pj = *cj;
            }

            visited.insert(*knots.last().unwrap());
        }
    }

    visited.len()
}
