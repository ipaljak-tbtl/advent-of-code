use std::collections::HashMap;

fn count(
    i: usize,
    j: usize,
    input: &[char],
    sizes: &[usize],
    mem: &mut HashMap<(usize, usize), u64>,
) -> u64 {
    if mem.contains_key(&(i, j)) {
        return *mem.get(&(i, j)).unwrap();
    }

    if i >= input.len() {
        if j >= sizes.len() {
            return 1;
        } else {
            return 0;
        }
    } else if j >= sizes.len() {
        if input[i..].contains(&'#') {
            return 0;
        } else {
            return 1;
        }
    }

    let target = sizes[j];

    let mut result = 0;

    for (ci, &c) in input[i..].iter().enumerate() {
        if c == '.' {
            continue;
        }

        let si = i + ci;
        let ei = si + target;

        if ei > input.len() {
            break;
        }

        if (ei == input.len() || input[ei] != '#') && input[si..ei].iter().all(|&c| c != '.') {
            result += count(ei + 1, j + 1, input, sizes, mem);
        }

        if c == '#' {
            break;
        }
    }

    mem.insert((i, j), result);

    result
}

fn solve(reader: impl std::io::BufRead) -> u64 {
    let mut result = 0;

    for line in reader.lines().map(Result::unwrap) {
        let i_space = line.find(' ').unwrap();

        let input: Vec<char> = line[..i_space].chars().collect();
        let sizes: Vec<usize> = line[(i_space + 1)..]
            .split(',')
            .map(|s| s.parse().unwrap())
            .collect();

        let mut mem = HashMap::<(usize, usize), u64>::new();

        result += count(0, 0, &input, &sizes, &mut mem);
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
    fn test_d12p1() {
        let reader = BufReader::new(File::open("d12/test_input.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 21);
    }
}
