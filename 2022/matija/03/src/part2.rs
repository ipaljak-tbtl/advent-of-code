pub fn solve(input: &[String]) -> u32 {
    let mut sum = 0;

    for i in 0..(input.len() / 3) {
        let count = &mut [0; 53];

        for rucksack in input.iter().skip(3 * i).take(3) {
            let found = &mut [false; 53];

            for c in rucksack.chars() {
                let priority = 1 + c as usize - if c >= 'a' { b'a' } else { b'A' - 26 } as usize;

                if !found[priority] {
                    count[priority] += 1;
                    found[priority] = true;
                }
            }
        }

        for (i, cnt) in count.iter().enumerate() {
            if cnt == &3 {
                sum += i as u32;
                break;
            }
        }
    }

    sum
}
