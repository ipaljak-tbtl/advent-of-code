pub fn solve(input: &[String]) -> u32 {
    let mut max_sum = 0;
    let mut current_sum = 0;

    for line in input {
        if line.is_empty() {
            max_sum = std::cmp::max(current_sum, max_sum);
            current_sum = 0;
            continue;
        }

        current_sum += line.parse::<u32>().unwrap();
    }

    std::cmp::max(current_sum, max_sum)
}
