fn main() {
    let in_lines: Vec<String> = std::io::stdin().lines().collect::<Result<_, _>>().unwrap();

    let mut sum = 0u32;

    for line in in_lines {
        for c in line.chars() {
            if let Some(d) = c.to_digit(10) {
                sum += 10 * d;
                break;
            }
        }

        for c in line.chars().rev() {
            if let Some(d) = c.to_digit(10) {
                sum += d;
                break;
            }
        }
    }

    println!("{sum}");
}
