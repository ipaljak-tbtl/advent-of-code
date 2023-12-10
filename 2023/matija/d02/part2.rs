fn get_backwards_unsigned(input: &str, start: usize) -> u32 {
    let mut result = 0u32;

    let mut mul = 1;

    for c in input[..=start].chars().rev() {
        if let Some(d) = c.to_digit(10) {
            result += mul * d;
            mul *= 10;
        } else {
            break;
        }
    }

    result
}

fn solve(reader: impl std::io::BufRead) -> u32 {
    let colors = ["red", "green", "blue"];

    let mut result = 0u32;

    for line in reader.lines().map(Result::unwrap) {
        let mut power = 1u32;

        for color in colors {
            let mut n_max = 0u32;
            let mut i = 0;
            while let Some(i_found) = line[i..].find(color) {
                i += i_found + 1;

                let n = get_backwards_unsigned(&line, i - 3);

                if n > n_max {
                    n_max = n;
                }
            }

            power *= n_max;
        }

        result += power;
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
    fn test_d02p2() {
        let reader = BufReader::new(File::open("d02/test_input.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 2286);
    }
}
