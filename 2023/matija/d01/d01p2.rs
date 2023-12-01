fn main() {
    let in_lines: Vec<String> = std::io::stdin().lines().collect::<Result<_, _>>().unwrap();

    let numbers = [
        "1", "2", "3", "4", "5", "6", "7", "8", "9", "one", "two", "three", "four", "five", "six",
        "seven", "eight", "nine",
    ];

    let mut sum = 0u32;

    for line in in_lines {
        let mut first_found = false;
        let mut last = 0u32;

        let mut i = 0;
        while i < line.len() {
            for (idx, num) in numbers.into_iter().enumerate() {
                let num_len = num.len();

                if i + num_len > line.len() {
                    continue;
                }

                if &line[i..(i + num_len)] == num {
                    let n = (idx % 9 + 1) as u32;

                    if !first_found {
                        sum += 10 * n;
                        first_found = true;
                    }

                    last = n;
                }
            }

            i += 1;
        }

        sum += last;
    }

    println!("{sum}");
}
