use std::collections::{HashMap, HashSet, VecDeque};

type Brick = ((u32, u32, u32), (u32, u32, u32));

fn parse_input(reader: impl std::io::BufRead) -> Vec<Brick> {
    let mut bricks = Vec::new();
    for line in reader.lines().map(Result::unwrap) {
        let b: Vec<Vec<u32>> = line
            .split('~')
            .map(|s| s.split(',').map(|s| s.parse().unwrap()).collect())
            .collect();
        bricks.push(((b[0][0], b[0][1], b[0][2]), (b[1][0], b[1][1], b[1][2])));
    }
    bricks
}

fn solve(reader: impl std::io::BufRead) -> usize {
    let mut bricks = parse_input(reader);
    bricks.sort_by(|a, b| a.0 .2.cmp(&b.0 .2));

    let mut positions = HashMap::<(u32, u32), (u32, usize)>::new();

    let mut fixed = HashSet::<usize>::new();

    let mut holder_of = HashMap::<usize, Vec<usize>>::new();
    let mut holds_me = HashMap::<usize, Vec<usize>>::new();

    for (i, &((x1, y1, z1), (x2, y2, z2))) in bricks.iter().enumerate() {
        let mut z_below = 0;

        let mut below = HashSet::<usize>::new();

        for x in x1..(x2 + 1) {
            for y in y1..(y2 + 1) {
                let &(z, b) = positions.get(&(x, y)).unwrap_or(&(0, 0));
                if z > z_below {
                    z_below = z;
                    below.clear();
                    below.insert(b);
                } else if z == z_below && b != 0 {
                    below.insert(b);
                }
            }
        }

        for x in x1..(x2 + 1) {
            for y in y1..(y2 + 1) {
                positions.insert((x, y), (z_below + z2 - z1 + 1, i + 1));
            }
        }

        for &b in &below {
            holder_of.entry(b).or_default().push(i + 1);
        }

        holds_me.insert(i + 1, below.iter().copied().collect());

        if below.len() == 1 {
            fixed.insert(below.into_iter().next().unwrap());
        }
    }

    let mut result = 0;

    for f in fixed {
        let mut removed = HashSet::<usize>::new();
        removed.insert(f);

        let mut open = VecDeque::<usize>::new();
        open.push_front(f);

        while let Some(b) = open.pop_front() {
            if !holder_of.contains_key(&b) {
                continue;
            }

            for &h in holder_of.get(&b).unwrap() {
                if !removed.contains(&h)
                    && holds_me
                        .get(&h)
                        .unwrap()
                        .iter()
                        .all(|x| removed.contains(x))
                {
                    result += 1;
                    removed.insert(h);
                    open.push_back(h);
                }
            }
        }
    }

    result
}

fn main() {
    println!("{}", solve(std::io::stdin().lock()));
}

#[cfg(test)]
mod tests {
    use super::solve;
    use std::{fs::File, io::BufReader};

    #[test]
    fn test_d22p2() {
        let reader = BufReader::new(File::open("d22/test_input.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 7);
    }
}
