pub fn solve(input: &[String]) -> u32 {
    let mut sums = Vec::new();
    let mut current_sum = 0;

    for line in input {
        if line.is_empty() {
            sums.push(current_sum);
            current_sum = 0;
            continue;
        }

        current_sum += line.parse::<u32>().unwrap();
    }

    sums.push(current_sum);

    sums.sort_unstable();

    sums.iter().rev().take(3).sum()
}
