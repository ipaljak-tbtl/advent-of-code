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
    let ns = [("red", 12u32), ("green", 13u32), ("blue", 14u32)];

    let mut result = 0u32;

    for line in reader.lines().map(Result::unwrap) {
        let mut valid = true;

        for (color, n_color) in ns {
            let mut i = 0;
            while let Some(i_found) = line[i..].find(color) {
                i += i_found + 1;

                let n = get_backwards_unsigned(&line, i - 3);

                if n > n_color {
                    valid = false;
                    break;
                }
            }

            if !valid {
                break;
            }
        }

        if valid {
            let i_game = line.find(':').unwrap() - 1;
            let game = get_backwards_unsigned(&line, i_game);

            result += game;
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
    fn test_d02p1() {
        let reader = BufReader::new(File::open("d02/test_input.txt").unwrap());
        let result = solve(reader);
        assert_eq!(result, 8);
    }
}
