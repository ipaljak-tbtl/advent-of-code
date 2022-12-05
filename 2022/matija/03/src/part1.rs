pub fn solve(input: &[String]) -> u32 {
    let mut sum = 0;

    for line in input {
        let comp_size = line.len() / 2;
        let count = &mut [false; 53];

        for (i, c) in line.chars().enumerate() {
            let priority = 1 + c as usize - if c >= 'a' { b'a' } else { b'A' - 26 } as usize;

            if i < comp_size {
                count[priority] = true
            } else if count[priority] {
                sum += priority as u32;
                break;
            }
        }
    }

    sum
}
